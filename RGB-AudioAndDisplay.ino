#include <Encoder.h>
#include <LCD_interface.h>

#include <SD.h>
#include <TMRpcm.h>

    ENCODER dial = ENCODER(NULL, NULL, 2);

    TMRpcm audio;

    LCD_INTERFACE manager;

    folder mainMenu, musicMenu, lightsMenu, modesMenu, brightnessMenu;
    
    int const sSize = 9, mSize = 5, bSize = 5;
    int const audioChipSelect = 4, audioSpeakerPin = 9, audioDefaultVolume = 6;

    int const elapsedMillisForDoublePress = 1000;
    int prevMillis; 

    char* tempAudioFile;
    char* prevFolderSelected;

    bool disableAudio = false;

void setup()
{ 
    Serial.begin(9600);
    
    char* songs[sSize] = {"Champion","Holiday","StJimmy","Levels","Light","Stars","You","Top","Hold"};
    char* modes[mSize] = {"Idle Change", "Idle Red", "Idle Green", "Idle Blue", "Stripes"};
    char* brightness[bSize] = {"Lowest", "Low", "Medium", "High", "Maximum"}; 

    mainMenu.folderName = "**RGB Music**";
    musicMenu.folderName = "[] Music";
    lightsMenu.folderName = "[] Lights";
    modesMenu.folderName = "[] Modes";
    brightnessMenu.folderName = "[] Brightness";

    mainMenu.createFolder(NULL, 0);
    musicMenu.createFolder(songs, sSize);
    lightsMenu.createFolder(NULL, 0);
    modesMenu.createFolder(modes,mSize);
    brightnessMenu.createFolder(brightness, bSize);

    manager.includeFolder(&mainMenu, &musicMenu, true);
    manager.includeFolder(&mainMenu, &lightsMenu, true);
    manager.includeFolder(&lightsMenu, &brightnessMenu, true);
    manager.includeFolder(&lightsMenu, &modesMenu, true);

    manager.interfaceTitle = mainMenu.folderName; 

    manager.begin(&mainMenu);

    audio.speakerPin = audioSpeakerPin; 
    
    SD.begin(audioChipSelect); 
    
    audio.volume(audioDefaultVolume);
}

void playSong()
{
  String FILE_TYPE = ".wav";
  
  if ( (manager.currentFolderOpen)->folderName == musicMenu.folderName && dial.buttonPress() && manager.currentFolderSelected != manager.BACK)
  {     
    String tempAudioFile_STR = manager.currentFolderSelected + FILE_TYPE;
    
    tempAudioFile = tempAudioFile_STR.c_str();

    if (manager.currentFolderSelected == prevFolderSelected)
    {
       audio.disable();
       
       disableAudio = (!disableAudio);
    }
    
    if (!disableAudio || manager.currentFolderSelected != prevFolderSelected)
    {
      audio.play(tempAudioFile);
      
      prevFolderSelected = manager.currentFolderSelected; 
    }
  }
}

void loop()
{
    manager.interface(); 

    playSong();
    
    
}
