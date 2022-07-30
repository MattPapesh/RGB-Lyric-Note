#ifndef RGB_LyricNoteLights_h
#define RGB_LyricNoteLights_h

#include <Arduino.h>
#include<Adafruit_PWMServoDriver.h>

#include "RGB_Pin.h"
#include "src/RGB_Cavity.h"
#include "src/RGB_Cavities.h"
#include "src/RGB_CommandReceiver.h"
#include "src/RGB_CommandScheduler.h"

#include "src/rgb_commands/RainbowCommand.h"

class RGB_LyricNoteLights
{
    private:

    const int SERIAL_BAUD_RATE = 9600;
    Adafruit_PWMServoDriver RGB_DRIVER_1 = Adafruit_PWMServoDriver(0x40);
    Adafruit_PWMServoDriver RGB_DRIVER_2 = Adafruit_PWMServoDriver(0x41);

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

    RGB_Cavity c0 = RGB_Cavity(&p0, &p1, &p2); RGB_Cavity c1 = RGB_Cavity(&p3, &p4, &p5); RGB_Cavity c2 = RGB_Cavity(&p6, &p7, &p8);
    RGB_Cavity c3 = RGB_Cavity(&p9, &p10, &p11); RGB_Cavity c4 = RGB_Cavity(&p12, &p13, &p14); RGB_Cavity c5 = RGB_Cavity(&p15, &p16, &p17);
    RGB_Cavity c6 = RGB_Cavity(&p18, &p19, &p20); RGB_Cavity c7 = RGB_Cavity(&p21, &p22, &p23); RGB_Cavity c8 = RGB_Cavity(&p24, &p25, &p26);
    RGB_Cavity c9 = RGB_Cavity(&p27, &p28, &p29); RGB_Cavity c10 = RGB_Cavity(&p30, &p31, &p32); RGB_Cavity c11 = RGB_Cavity(&p33, &p34, &p35);

    RGB_Cavity* cavity_PTRs[12] = {&c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10, &c11};
    RGB_Cavities lyric_note_cavities = RGB_Cavities(cavity_PTRs, 12);

    // Instantiate RGBCommandReceiver:
    RGB_CommandReceiver command_receiver = RGB_CommandReceiver();

    // Instantiate RGB Commands:
    RainbowCommand rainbow_lights_command = RainbowCommand(&command_receiver, "Rainbow");

    public:

    void begin();
    void run();

    void interfaceCavity(int cavity_index, float red_pct, float green_pct, float blue_pct);
    void interfaceAllCavities(float red_pct, float green_pct, float blue_pct);
};

#endif