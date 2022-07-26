#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver RGB_DRIVER_1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver RGB_DRIVER_2 = Adafruit_PWMServoDriver(0x41);
int const max_duty_cycle = 30;
int const max_driver_PWM_cycle = 4095;

struct RGB_Pin
{
  Adafruit_PWMServoDriver* pin_driver_PTR = nullptr;
  int pin;

  RGB_Pin(Adafruit_PWMServoDriver* pin_driver_PTR, int pin)
  {
    this->pin_driver_PTR = pin_driver_PTR;
    this->pin = pin;

    if (pin_driver_PTR == nullptr)
    {
      pinMode(pin, OUTPUT);
    }
  }
};

struct Cavity
{
  RGB_Pin* red_pin_PTR = nullptr;
  RGB_Pin* green_pin_PTR = nullptr;
  RGB_Pin* blue_pin_PTR = nullptr;

  float pct_red, pct_green, pct_blue;

  Cavity(RGB_Pin* blue_pin_PTR, RGB_Pin* green_pin_PTR, RGB_Pin* red_pin_PTR)
  {
    this->red_pin_PTR = red_pin_PTR;
    this->green_pin_PTR = green_pin_PTR;
    this->blue_pin_PTR = blue_pin_PTR;
  }
};

class Cavities
{
private: public:

    Cavity** cavity_PTR_PTRs = nullptr;
    int num_of_cavities = 0;

    void interfaceLEDs(Cavity* cavity_PTR)
    {
      if ( (cavity_PTR->red_pin_PTR)->pin_driver_PTR != nullptr)
      {
        ( (cavity_PTR->red_pin_PTR)->pin_driver_PTR)->setPWM( (cavity_PTR->red_pin_PTR)->pin, 0, ( (cavity_PTR->pct_red) / 100) * max_driver_PWM_cycle);
      }
      else if ( (cavity_PTR->red_pin_PTR)->pin_driver_PTR == nullptr)
      {
        analogWrite( (cavity_PTR->red_pin_PTR)->pin, ( (cavity_PTR->pct_red) / 100) * max_duty_cycle);
      }

      if ( (cavity_PTR->green_pin_PTR)->pin_driver_PTR != nullptr)
      {
        ( (cavity_PTR->green_pin_PTR)->pin_driver_PTR)->setPWM( (cavity_PTR->green_pin_PTR)->pin, 0, ( (cavity_PTR->pct_green) / 100) * max_driver_PWM_cycle);
      }
      else if ( (cavity_PTR->green_pin_PTR)->pin_driver_PTR == nullptr)
      {
        analogWrite( (cavity_PTR->green_pin_PTR)->pin, ( (cavity_PTR->pct_green) / 100) * max_duty_cycle);
      }

      if ( (cavity_PTR->blue_pin_PTR)->pin_driver_PTR != nullptr)
      {
        ( (cavity_PTR->blue_pin_PTR)->pin_driver_PTR)->setPWM( (cavity_PTR->blue_pin_PTR)->pin, 0, ( (cavity_PTR->pct_blue) / 100) * max_driver_PWM_cycle);
      }
      else if ( (cavity_PTR->blue_pin_PTR)->pin_driver_PTR == nullptr)
      {
        analogWrite( (cavity_PTR->blue_pin_PTR)->pin, ( (cavity_PTR->pct_blue) / 100) * max_duty_cycle);
      }
    }

  public:

    Cavities(Cavity* cavity_PTRs[], int num_of_cavities)
    {
      cavity_PTR_PTRs = new Cavity*[num_of_cavities];
      *cavity_PTR_PTRs = cavity_PTRs[0];
      this->num_of_cavities = num_of_cavities;
    }

    ~Cavities()
    {
      delete[] cavity_PTR_PTRs;
      cavity_PTR_PTRs = nullptr;
    }

    void interfaceCavity(Cavity* cavity_PTR, float pct_red, float pct_green, float pct_blue)
    {
      cavity_PTR->pct_red = pct_red;
      cavity_PTR->pct_green = pct_green;
      cavity_PTR->pct_blue = pct_blue;
    }

    void interfaceAllCavities(float pct_red, float pct_green, float pct_blue)
    {
      for (int i = 0; i < num_of_cavities; i++)
      {
        interfaceCavity(*(cavity_PTR_PTRs + i), pct_red, pct_green, pct_blue);
      }
    }

    void updateLyricNote()
    {
      for (int i = 0; i < num_of_cavities; i++)
      {
        interfaceLEDs(*(cavity_PTR_PTRs + i));
      }
    }
};

struct Hue
{
  float pct_red;
  float pct_green;
  float pct_blue;

  Hue(float pct_red, float pct_green, float pct_blue)
  {
    this->pct_red = pct_red;
    this->pct_green = pct_green;
    this->pct_blue = pct_blue;
  }
};

//Servo Driver #1 Pins
RGB_Pin p0 = RGB_Pin(&RGB_DRIVER_1, 0); RGB_Pin p1 = RGB_Pin(&RGB_DRIVER_1, 1); RGB_Pin p2 = RGB_Pin(&RGB_DRIVER_1, 2);
RGB_Pin p3 = RGB_Pin(&RGB_DRIVER_1, 3); RGB_Pin p4 = RGB_Pin(&RGB_DRIVER_1, 4); RGB_Pin p5 = RGB_Pin(&RGB_DRIVER_1, 5);
RGB_Pin p6 = RGB_Pin(&RGB_DRIVER_1, 6); RGB_Pin p7 = RGB_Pin(&RGB_DRIVER_1, 7); RGB_Pin p8 = RGB_Pin(&RGB_DRIVER_1, 8);
RGB_Pin p9 = RGB_Pin(&RGB_DRIVER_1, 9); RGB_Pin p10 = RGB_Pin(&RGB_DRIVER_1, 10); RGB_Pin p11 = RGB_Pin(&RGB_DRIVER_1, 11);
RGB_Pin p12 = RGB_Pin(&RGB_DRIVER_1, 12); RGB_Pin p13 = RGB_Pin(&RGB_DRIVER_1, 13); RGB_Pin p14 = RGB_Pin(&RGB_DRIVER_1, 14);
RGB_Pin p15 = RGB_Pin(&RGB_DRIVER_1, 15);

//Servo Driver #2 Pins
RGB_Pin p16 = RGB_Pin(&RGB_DRIVER_2, 0); RGB_Pin p17 = RGB_Pin(&RGB_DRIVER_2, 1); RGB_Pin p18 = RGB_Pin(&RGB_DRIVER_2, 2);
RGB_Pin p19 = RGB_Pin(&RGB_DRIVER_2, 3); RGB_Pin p20 = RGB_Pin(&RGB_DRIVER_2, 4); RGB_Pin p21 = RGB_Pin(&RGB_DRIVER_2, 5);
RGB_Pin p22 = RGB_Pin(&RGB_DRIVER_2, 6); RGB_Pin p23 = RGB_Pin(&RGB_DRIVER_2, 7); RGB_Pin p24 = RGB_Pin(&RGB_DRIVER_2, 8);
RGB_Pin p25 = RGB_Pin(&RGB_DRIVER_2, 9); RGB_Pin p26 = RGB_Pin(&RGB_DRIVER_2, 10); RGB_Pin p27 = RGB_Pin(&RGB_DRIVER_2, 11);
RGB_Pin p28 = RGB_Pin(&RGB_DRIVER_2, 12); RGB_Pin p29 = RGB_Pin(&RGB_DRIVER_2, 13); RGB_Pin p30 = RGB_Pin(&RGB_DRIVER_2, 14);
RGB_Pin p31 = RGB_Pin(&RGB_DRIVER_2, 15);

//Pins Without Driver (Arduino PWM Pins)
RGB_Pin p32 = RGB_Pin(nullptr, 3);
RGB_Pin p33 = RGB_Pin(nullptr, 5); RGB_Pin p34 = RGB_Pin(nullptr, 6); RGB_Pin p35 = RGB_Pin(nullptr, 9);

Cavity c0 = Cavity(&p0, &p1, &p2); Cavity c1 = Cavity(&p3, &p4, &p5); Cavity c2 = Cavity(&p6, &p7, &p8);
Cavity c3 = Cavity(&p9, &p10, &p11); Cavity c4 = Cavity(&p12, &p13, &p14); Cavity c5 = Cavity(&p15, &p16, &p17);
Cavity c6 = Cavity(&p18, &p19, &p20); Cavity c7 = Cavity(&p21, &p22, &p23); Cavity c8 = Cavity(&p24, &p25, &p26);
Cavity c9 = Cavity(&p27, &p28, &p29); Cavity c10 = Cavity(&p30, &p31, &p32); Cavity c11 = Cavity(&p33, &p34, &p35);

Cavity* cavity_PTRs[12] = {&c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10, &c11};
Cavities lyricNote = Cavities(cavity_PTRs, 12);

Hue red = Hue(100, 0, 0), purple = Hue(100, 0, 100), green = Hue(0, 100, 0), cyan = Hue(0, 100, 100), blue = Hue(0, 0, 100), yellow = Hue(100, 100, 0), orange = Hue(100, 15, 0);
Hue hue[7] = {red, purple, green, cyan, blue, yellow, orange};

// If the slave arduino is sent this value, it knows that the following data is the command
char const SEND_SERIAL_ID = (char)58;
// If the slave arduino is sent this value, it knows that the entire command has been sent
char const SENT_SERIAL_ID = (char)59;

namespace RGB_command
{
String command = "";
int num_of_parameters = 0;
int* parameter_ptrs = nullptr;
}

void setup()
{
  Serial.begin(9600);
  RGB_DRIVER_1.begin();
  RGB_DRIVER_2.begin();
  RGB_DRIVER_1.setPWMFreq(200);
  RGB_DRIVER_2.setPWMFreq(200);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
}

bool transmit(char byte_sent)
{
  static bool transmitting = false;

  if (byte_sent == SEND_SERIAL_ID && !transmitting)
  {
    transmitting = true;
  }
  else if (byte_sent == SENT_SERIAL_ID && transmitting)
  {
    transmitting = false;
  }

  return transmitting;
}

char getChar()
{
  if (Serial.available())
  {
    return (char)Serial.read();
  }
}

String getSerialTransmission()
{
  String transmission = "";
  char character = getChar();

  while (transmit(character))
  {
    if (character != NULL && character != SEND_SERIAL_ID && character != SENT_SERIAL_ID)
    {
      transmission += character;
    }

    character = getChar();
  }

  return transmission;
}

void serialEvent()
{
  delay(100);
  
  if (Serial && Serial.available())
  {
    RGB_command::command = getSerialTransmission();
    RGB_command::num_of_parameters = getSerialTransmission().toInt();

    if (RGB_command::parameter_ptrs != nullptr)
    {
      delete[] RGB_command::parameter_ptrs;
    }

    RGB_command::parameter_ptrs = new int[RGB_command::num_of_parameters];

    for (int i = 0; i < RGB_command::num_of_parameters; i++)
    {
      *(RGB_command::parameter_ptrs + i) = getSerialTransmission().toInt();
    }

    Serial.print("command: "); Serial.println(RGB_command::command);
    for (int i = 0; i < RGB_command::num_of_parameters; i++)
    {
      Serial.print("parameter: "); Serial.println(*(RGB_command::parameter_ptrs + i));
    }
  }
}

void loop()
{
  delay(500);

}
