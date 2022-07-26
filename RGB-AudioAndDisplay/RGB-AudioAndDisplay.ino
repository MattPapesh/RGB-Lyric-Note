#include <LCD_Interface.h>
#include <SD.h>
#include <TMRpcm.h>

  TMRpcm audio = TMRpcm();
  LCD_Interface interface = LCD_Interface();

  int const AUDIO_CHIP_SELECT = 4, AUDIO_SPEAKER_PIN = 9, AUDIO_DEFAULT_VOLUME = 6;

  // If the slave arduino is sent this value, it knows that the following data is the command
  char const SEND_SERIAL_ID = (char)58;
  // If the slave arduino is sent this value, it knows that the entire command has been sent
  char const SENT_SERIAL_ID = (char)59;

  namespace RGB
  {
    int const num_of_files = 10; 

    // RGB high variation animations
    file* stripes = new file("Stripes");
    file* rainbow = new file("Rainbow");
    file* custom = new file("Custom");
    file* polarized = new file("Polarized");

    // Monochromatic RGB animations
    /*file* red = new file("Red");
    file* green = new file("Green");
    file* blue = new file("Blue");
    file* yellow = new file("Yellow");
    file* cyan = new file("Cyan");
    file* violet = new file("Violet");*/

    file* RGB_files[num_of_files] = 
    {
      polarized, stripes, rainbow, custom//, 
      //red, green, blue, yellow, cyan, violet
    }; 

    // Add animation file parameters
    void fileSetup()
    {
      stripes->addParameter("Flow Rate", 10);
      stripes->addParameter("Hue", 30);
      stripes->addParameter("Brightness", 40); 

      rainbow->addParameter("Flow Rate", 0);

      custom->addParameter("Hue", 0);
      custom->addParameter("Brightness", 0);

      polarized->addParameter("Flow Rate", 0);
      polarized->addParameter("Prim Hue", 0);
      polarized->addParameter("Brightness", 0);
      polarized->addParameter("Sec Hue", 0);
      polarized->addParameter("Brightness", 0);     
    }  
  }
  
  namespace songs
  {
    int const num_of_files = 3; 

    file* fall_out_boy = new file("FallOutBoy");
    file* imagine_dragons = new file("ImagineDragons");
    file* avicii = new file("Avicii");

    file* song_files[num_of_files] = {fall_out_boy, imagine_dragons, avicii};  

    void fileSetup()
    {
      fall_out_boy->addParameter("A~Song", 0);
      imagine_dragons->addParameter("B~Song", 0);
      avicii->addParameter("C~Song", 0);
    }
  }

  // assume any folder not associated with "parent" is a child folder relative to its namespace
  namespace lights_folder
  {
    folder* parent_folder = new folder("[] Lights");

    void folderSetup()
    {
      parent_folder->addFiles(RGB::RGB_files, RGB::num_of_files);
    }
  }

  namespace music_folder
  {
    folder* parent_folder = new folder("[] Music");

    void folderSetup()
    {
      parent_folder->addFiles(songs::song_files, songs::num_of_files);
    }
  }
  
  namespace base_folder
  {
    folder* parent_folder = new folder("**RBG Music**");
    
    int const num_of_child_folders = 2;
    folder* child_folders[num_of_child_folders] = {lights_folder::parent_folder, music_folder::parent_folder};
    
    void folderSetup()
    {
      parent_folder->addFolders(child_folders, num_of_child_folders);
    }
  }

  void setup()
  { 
    Serial.begin(9600);  
    audio.speakerPin = AUDIO_SPEAKER_PIN;   
    SD.begin(AUDIO_CHIP_SELECT);
    audio.volume(AUDIO_DEFAULT_VOLUME);
  
    RGB::fileSetup();
    songs::fileSetup();
    lights_folder::folderSetup();
    music_folder::folderSetup();
    base_folder::folderSetup();
    interface.begin(base_folder::parent_folder);
  }

  void sendSerialTransmission(char* transmission)
  {
    Serial.write(SEND_SERIAL_ID);
    Serial.write(transmission);
    Serial.write(SENT_SERIAL_ID);
  }

  void RGB_Command(char* command)
  {
    for(int file_index = 0; file_index < lights_folder::parent_folder->getNumOfFiles(); file_index++)
    {
      file* current_file_ptr = lights_folder::parent_folder->getFilePTR(file_index);
      
      if(current_file_ptr->getFileName() == command && current_file_ptr->getFileActive())
      {
        sendSerialTransmission(command);
        sendSerialTransmission(((String)current_file_ptr->getNumOfParameters()).c_str());

        for(int i = 0; i < current_file_ptr->getNumOfParameters(); i++)
        {
          sendSerialTransmission(((String)(current_file_ptr->getParameterPTRs() + i)->getData()).c_str());
        } 
      }
      else if(current_file_ptr->getFileName() != command && current_file_ptr->getFileActive())
      {
        current_file_ptr->setFileActive(false);
      }
    }
  }
 
  void runAudio()
  {
    static String song_playing = "";
    String FILE_TYPE = ".wav";

    for(int i = 0; i < songs::num_of_files; i++)
    {
      String temp_song = music_folder::parent_folder->getFilePTR(i)->getParameterPTRs()->getParameterName() + (String)((int)(music_folder::parent_folder->getFilePTR(i)->getParameterPTRs()->getData()));
      boolean temp_active = music_folder::parent_folder->getFilePTR(i)->getFileActive();
      
      if(song_playing != temp_song && temp_active)
      {
        audio.disable();
        audio.play((temp_song + FILE_TYPE).c_str());     
        song_playing = temp_song;
        
        Serial.println("SP: " + song_playing + FILE_TYPE);
        break;
      }
      else if(song_playing == temp_song && !temp_active)
      {
        audio.disable(); 
        song_playing = "";
      }
    }
  }

void loop()
{
   interface.interface(); 
   runAudio();
   
   RGB_Command("Stripes");
   RGB_Command("Rainbow");
   RGB_Command("Custom");
   RGB_Command("Polarized");
}
