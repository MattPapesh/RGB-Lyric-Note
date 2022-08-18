#include <LCD_Interface.h>
#include <SD.h>
#include <TMRpcm.h>

  TMRpcm audio = TMRpcm();
  LCD_Interface lcd_interface = LCD_Interface();

  int const AUDIO_CHIP_SELECT PROGMEM = 4;
  int const AUDIO_SPEAKER_PIN PROGMEM = 9;
  int const AUDIO_DEFAULT_VOLUME PROGMEM = 6;

  // If the slave arduino is sent this value, it knows that the following data is the command
  char const SEND_SERIAL_ID PROGMEM = (char)58;
  // If the slave arduino is sent this value, it knows that the entire command has been sent
  char const SENT_SERIAL_ID PROGMEM = (char)59;

  namespace RGB_CommandFiles
  {
    int const num_of_files PROGMEM = 4; 
    file* stripes = new file("Stripes");
    file* rainbow = new file("Rainbow");
    file* secret = new file("Secret");
    file* chaos = new file("Chaos");
    file* RGB_command_file_ptrs[num_of_files] = {rainbow, stripes, secret, chaos}; 

    // Add animation file parameters
    void fileSetup()
    {
      stripes->addParameter("Speed", 3);
      stripes->addParameter("Prim Hue", 0); 
      stripes->addParameter("Sec Hue", 0); 
      stripes->addParameter("Mode", 0);

      rainbow->addParameter("Speed", 3);
      rainbow->addParameter("Mode", 0);

      chaos->addParameter("Delay", 3);

      secret->addParameter("Speed", 3);
      secret->addParameter("Mode", 0);
    }  
  }
  
  namespace ArtistFiles
  {
    int const num_of_files = 3; 
    file* late_night = new file("Late Night");
    file* lauren_daigle = new file("Lauren Daigle");;
    file* misc = new file("Misc");
    file* artist_file_ptrs[num_of_files] = {late_night, lauren_daigle, misc};  

    void fileSetup()
    {
      late_night->addParameter("A", 0);
      lauren_daigle->addParameter("B", 0);
      misc->addParameter("C", 0);
    }
  }

  // Assume any folder not associated with "parent" is a child folder relative to its namespace
  namespace RGB_CommandsFolder
  {
    folder* parent_folder_ptr = new folder("[] Lights");

    void folderSetup()
    {
      parent_folder_ptr->addFiles(RGB_CommandFiles::RGB_command_file_ptrs, RGB_CommandFiles::num_of_files);
    }
  }

  namespace ArtistsFolder
  {
    folder* parent_folder_ptr = new folder("[] Music");

    void folderSetup()
    {
      parent_folder_ptr->addFiles(ArtistFiles::artist_file_ptrs, ArtistFiles::num_of_files);
    }
  }
  
  namespace BaseFolder
  {
    folder* parent_folder_ptr = new folder("**RGB Music**");
    int const num_of_child_folders PROGMEM = 2;
    folder* child_folder_ptrs[num_of_child_folders] = {RGB_CommandsFolder::parent_folder_ptr, ArtistsFolder::parent_folder_ptr};
    
    void folderSetup()
    {
      parent_folder_ptr->addFolders(child_folder_ptrs, num_of_child_folders);
    }
  }

  void sendSerialTransmission(char* transmission)
  {
    Serial.write(SEND_SERIAL_ID);
    Serial.write(transmission);
    Serial.write(SENT_SERIAL_ID);
  }
  
  file null_file = file("off");
  file* active_file_ptr = &null_file;
  double active_file_params[4] = {}; 
     
  void runRGB_Commands()
  {  
    file* initial_file_ptr = active_file_ptr;
    
    for(int i = 0; i < RGB_CommandFiles::num_of_files; i++)
    {
      file* current_file_ptr = RGB_CommandFiles::RGB_command_file_ptrs[i];
    
      if(initial_file_ptr->getFileName() == null_file.getFileName() && current_file_ptr->getFileActive())
      {
        //transmit current_file
        runSerialTransmission(current_file_ptr);
        active_file_ptr = current_file_ptr;

        for(int param_index = 0; param_index < current_file_ptr->getNumOfParameters(); param_index++)
        {
          active_file_params[param_index] = (current_file_ptr->getParameterPTR(param_index))->getData();
        }
        
        break;
      }
      else if(initial_file_ptr->getFileName() != null_file.getFileName() && current_file_ptr->getFileName() == initial_file_ptr->getFileName() && 
      !current_file_ptr->getFileActive())
      {
        //transmit null file
        runSerialTransmission(&null_file);
        active_file_ptr = &null_file;

        for(int param_index = 0; param_index < current_file_ptr->getNumOfParameters(); param_index++)
        {
          active_file_params[param_index] = (current_file_ptr->getParameterPTR(param_index))->getData();
        }
        
        break;
      }
      else if(initial_file_ptr->getFileName() != null_file.getFileName() && current_file_ptr->getFileName() != initial_file_ptr->getFileName() &&
      current_file_ptr->getFileActive())
      {
        //transmit new active file
        runSerialTransmission(current_file_ptr);
        active_file_ptr->setFileActive(false);
        active_file_ptr = current_file_ptr;

        for(int param_index = 0; param_index < current_file_ptr->getNumOfParameters(); param_index++)
        {
          active_file_params[param_index] = (current_file_ptr->getParameterPTR(param_index))->getData();
        }
        
        break;
      }
      else if(initial_file_ptr->getFileName() != null_file.getFileName() && current_file_ptr->getFileName() == initial_file_ptr->getFileName() &&
      current_file_ptr->getFileActive() && updatedParameters(current_file_ptr, active_file_params))
      {
        //transmit active file with new parameters
        runSerialTransmission(current_file_ptr);

        for(int param_index = 0; param_index < current_file_ptr->getNumOfParameters(); param_index++)
        {
          active_file_params[param_index] = (current_file_ptr->getParameterPTR(param_index))->getData();
        }

        break;
      }  
    }
  }

// Both files passed in must have the same parameters in the same order!
  bool updatedParameters(file* file_ptr, double expected_parameters[])
  {
    for(int i = 0; i < file_ptr->getNumOfParameters(); i++)
    {
      if((file_ptr->getParameterPTR(i))->getData() != expected_parameters[i])
      {
        return true;
      }
    }
   
    return false;
  }

  void runSerialTransmission(file* RGB_command_file_ptr)
  {
    if(RGB_command_file_ptr != nullptr)
    {        
      sendSerialTransmission(RGB_command_file_ptr->getFileName());
      sendSerialTransmission(((String)RGB_command_file_ptr->getNumOfParameters()).c_str());
        
      for(int i = 0; i < RGB_command_file_ptr->getNumOfParameters(); i++)
      {
        sendSerialTransmission(((String)((RGB_command_file_ptr->getParameterPTR(i))->getData())).c_str());
      } 
    }
  }
 
  void runAudio()
  {
    static String current_audio_file_playing = "";
    const String AUDIO_FILE_TYPE PROGMEM = ".wav";

    for(int i = 0; i < ArtistFiles::num_of_files; i++)
    {
        String temp_audio_file = ArtistFiles::artist_file_ptrs[i]->getParameterPTR(0)->getParameterName() + 
        (String)((int)(ArtistFiles::artist_file_ptrs[i]->getParameterPTR(0)->getData()));
      
        boolean temp_is_active = ArtistFiles::artist_file_ptrs[i]->getFileActive();
      
        if(current_audio_file_playing != temp_audio_file && temp_is_active)
        {
            audio.disable();
            audio.play((temp_audio_file + AUDIO_FILE_TYPE).c_str());     
            current_audio_file_playing = temp_audio_file;
        
            break;
        }
        else if(current_audio_file_playing == temp_audio_file && !temp_is_active)
        {
            audio.disable(); 
            current_audio_file_playing = "";
        }
     }
  }

  void setup()
  { 
    Serial.begin(9600);  
    audio.speakerPin = AUDIO_SPEAKER_PIN;   
    SD.begin(AUDIO_CHIP_SELECT);
    audio.volume(AUDIO_DEFAULT_VOLUME);
  
    RGB_CommandFiles::fileSetup();
    ArtistFiles::fileSetup();
    RGB_CommandsFolder::folderSetup();
    ArtistsFolder::folderSetup();
    BaseFolder::folderSetup();
    lcd_interface.begin(BaseFolder::parent_folder_ptr);
  }

  void loop()
  {
    lcd_interface.run();
    runRGB_Commands(); 
    runAudio();
  }
