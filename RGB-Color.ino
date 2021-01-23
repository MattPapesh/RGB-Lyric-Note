#include <Adafruit_PWMServoDriver.h>

#include <Wire.h>

Adafruit_PWMServoDriver RGB_DRIVER1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver RGB_DRIVER2 = Adafruit_PWMServoDriver(0x41);

int const maxDutyCycle = 30;
int const maxDriverPWM_Cycle = 4095;

void setup() 
{
    Serial.begin(9600);

    RGB_DRIVER1.begin();
    RGB_DRIVER2.begin();

    RGB_DRIVER1.setPWMFreq(200);
    RGB_DRIVER2.setPWMFreq(200);
}

struct RGB_Pin
{
    Adafruit_PWMServoDriver* pinDriver_PTR = nullptr; 

    int pin;
  
   RGB_Pin(Adafruit_PWMServoDriver* tempPinDriver_PTR, int tempPin)
   {
        pinDriver_PTR = tempPinDriver_PTR;

        pin = tempPin; 

        if (tempPinDriver_PTR == nullptr)
        {
            pinMode(pin, OUTPUT);
        }
   }
};

//Servo Driver #1 Pins
RGB_Pin p0 = RGB_Pin(&RGB_DRIVER1, 0); RGB_Pin p1 = RGB_Pin(&RGB_DRIVER1, 1); RGB_Pin p2 = RGB_Pin(&RGB_DRIVER1, 2);
RGB_Pin p3 = RGB_Pin(&RGB_DRIVER1, 3); RGB_Pin p4 = RGB_Pin(&RGB_DRIVER1, 4); RGB_Pin p5 = RGB_Pin(&RGB_DRIVER1, 5);
RGB_Pin p6 = RGB_Pin(&RGB_DRIVER1, 6); RGB_Pin p7 = RGB_Pin(&RGB_DRIVER1, 7); RGB_Pin p8 = RGB_Pin(&RGB_DRIVER1, 8);
RGB_Pin p9 = RGB_Pin(&RGB_DRIVER1, 9); RGB_Pin p10 = RGB_Pin(&RGB_DRIVER1, 10); RGB_Pin p11 = RGB_Pin(&RGB_DRIVER1, 11);
RGB_Pin p12 = RGB_Pin(&RGB_DRIVER1, 12); RGB_Pin p13 = RGB_Pin(&RGB_DRIVER1, 13); RGB_Pin p14 = RGB_Pin(&RGB_DRIVER1, 14);
RGB_Pin p15 = RGB_Pin(&RGB_DRIVER1, 15);

//Servo Driver #2 Pins
RGB_Pin p16 = RGB_Pin(&RGB_DRIVER2, 0); RGB_Pin p17 = RGB_Pin(&RGB_DRIVER2, 1); RGB_Pin p18 = RGB_Pin(&RGB_DRIVER2, 2);
RGB_Pin p19 = RGB_Pin(&RGB_DRIVER2, 3); RGB_Pin p20 = RGB_Pin(&RGB_DRIVER2, 4); RGB_Pin p21 = RGB_Pin(&RGB_DRIVER2, 5);
RGB_Pin p22 = RGB_Pin(&RGB_DRIVER2, 6); RGB_Pin p23 = RGB_Pin(&RGB_DRIVER2, 7); RGB_Pin p24 = RGB_Pin(&RGB_DRIVER2, 8);
RGB_Pin p25 = RGB_Pin(&RGB_DRIVER2, 9); RGB_Pin p26 = RGB_Pin(&RGB_DRIVER2, 10); RGB_Pin p27 = RGB_Pin(&RGB_DRIVER2, 11);
RGB_Pin p28 = RGB_Pin(&RGB_DRIVER2, 12); RGB_Pin p29 = RGB_Pin(&RGB_DRIVER2, 13); RGB_Pin p30 = RGB_Pin(&RGB_DRIVER2, 14);
RGB_Pin p31 = RGB_Pin(&RGB_DRIVER2, 15);

//Pins Without Driver (Arduino PWM Pins)
RGB_Pin p32 = RGB_Pin(nullptr, 3);
RGB_Pin p33 = RGB_Pin(nullptr, 5); RGB_Pin p34 = RGB_Pin(nullptr, 6); RGB_Pin p35 = RGB_Pin(nullptr, 9);

struct Cavity
{
    RGB_Pin* redPin_PTR = nullptr;
    RGB_Pin* greenPin_PTR = nullptr;
    RGB_Pin* bluePin_PTR = nullptr;

    float pctRed, pctGreen, pctBlue; 

    Cavity(RGB_Pin* tempBluePin_PTR, RGB_Pin* tempGreenPin_PTR, RGB_Pin* tempRedPin_PTR)
    {
        redPin_PTR = tempRedPin_PTR;
        greenPin_PTR = tempGreenPin_PTR;
        bluePin_PTR = tempBluePin_PTR;        
    }
};

Cavity c0 = Cavity(&p0, &p1, &p2); Cavity c1 = Cavity(&p3, &p4, &p5); Cavity c2 = Cavity(&p6, &p7, &p8);
Cavity c3 = Cavity(&p9, &p10, &p11); Cavity c4 = Cavity(&p12, &p13, &p14); Cavity c5 = Cavity(&p15, &p16, &p17);
Cavity c6 = Cavity(&p18, &p19, &p20); Cavity c7 = Cavity(&p21, &p22, &p23); Cavity c8 = Cavity(&p24, &p25, &p26);
Cavity c9 = Cavity(&p27, &p28, &p29); Cavity c10 = Cavity(&p30, &p31, &p32); Cavity c11 = Cavity(&p33, &p34, &p35);

Cavity* listOfCavities[12] = {&c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10, &c11};

class Cavities
{
    private:public:

    Cavity** listOfCavities_PTR = nullptr;

    int amountOfCavities;
    
    void interfaceLEDs(Cavity* tempCavity_PTR)
    {
        if ( (tempCavity_PTR->redPin_PTR)->pinDriver_PTR != nullptr)
        { 
            ( (tempCavity_PTR->redPin_PTR)->pinDriver_PTR)->setPWM( (tempCavity_PTR->redPin_PTR)->pin, 0, ( (tempCavity_PTR->pctRed)/100) * maxDriverPWM_Cycle );
        }
        else if ( (tempCavity_PTR->redPin_PTR)->pinDriver_PTR == nullptr)
        {
            analogWrite( (tempCavity_PTR->redPin_PTR)->pin, ( (tempCavity_PTR->pctRed)/100) * maxDutyCycle);
        }

        if ( (tempCavity_PTR->greenPin_PTR)->pinDriver_PTR != nullptr)
        {
            ( (tempCavity_PTR->greenPin_PTR)->pinDriver_PTR)->setPWM( (tempCavity_PTR->greenPin_PTR)->pin, 0, ( (tempCavity_PTR->pctGreen)/100) * maxDriverPWM_Cycle );
        }
        else if ( (tempCavity_PTR->greenPin_PTR)->pinDriver_PTR == nullptr)
        {
            analogWrite( (tempCavity_PTR->greenPin_PTR)->pin, ( (tempCavity_PTR->pctGreen)/100) * maxDutyCycle);
        }

        if ( (tempCavity_PTR->bluePin_PTR)->pinDriver_PTR != nullptr)
        {
            ( (tempCavity_PTR->bluePin_PTR)->pinDriver_PTR)->setPWM( (tempCavity_PTR->bluePin_PTR)->pin, 0, ( (tempCavity_PTR->pctBlue)/100) * maxDriverPWM_Cycle );
        }
        else if ( (tempCavity_PTR->bluePin_PTR)->pinDriver_PTR == nullptr)
        {
            analogWrite( (tempCavity_PTR->bluePin_PTR)->pin, ( (tempCavity_PTR->pctBlue)/100) * maxDutyCycle);
        } 
    }

    public:

    Cavities(Cavity* tempListOfCavity_PTRs[], int tempAmountOfCavities)
    {
        listOfCavities_PTR = new Cavity*[tempAmountOfCavities];
        
        for (int i = 0; i < tempAmountOfCavities; i++)
        {
            *(listOfCavities_PTR + i) = tempListOfCavity_PTRs[i];
        }

        amountOfCavities = tempAmountOfCavities;
    }

    ~Cavities()
    {
      delete[] listOfCavities_PTR;

      listOfCavities_PTR = nullptr;
    }
  
    void interfaceCavity(Cavity* tempCavity_PTR, float temp_pctRed, float temp_pctGreen, float temp_pctBlue )
    {
       tempCavity_PTR->pctRed = temp_pctRed;
       tempCavity_PTR->pctGreen = temp_pctGreen;
       tempCavity_PTR->pctBlue = temp_pctBlue;
    }

    void interfaceAllCavities(float temp_pctRed, float temp_pctGreen, float temp_pctBlue)
    {
        for (int i = 0; i < amountOfCavities; i++)
        {
            interfaceCavity(*(listOfCavities_PTR + i), temp_pctRed, temp_pctGreen, temp_pctBlue);
        }
    }

    void updateLyricNote()
    {
         for (int i = 0; i < amountOfCavities; i++)
         {
             interfaceLEDs(*(listOfCavities_PTR + i) );
         }
    }
};

Cavities lyricNote = Cavities(listOfCavities, 12);
bool ONCE = true;
void loop() 
{
  if (ONCE)
  {
    for (int i = 0; i < 100; i++)
    {
       lyricNote.interfaceAllCavities(i, 0, 0);
       lyricNote.updateLyricNote();

       delay(3);
    }

    ONCE = false;
  }
    
    for (int i = 100; i > 0; i--)
    {
       lyricNote.interfaceAllCavities(i, (100-i), 0);
       lyricNote.updateLyricNote();

       delay(3);
    }
  for (int i = 100; i > 0; i--)
    {
       lyricNote.interfaceAllCavities(0, i, (100-i) );
       lyricNote.updateLyricNote();

       delay(3);
    }
    for (int i = 100; i > 0; i--)
    {
       lyricNote.interfaceAllCavities( (100-i) , 0, i);
       lyricNote.updateLyricNote();

       delay(3);
    }
  
   
}
