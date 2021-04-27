/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  PWM test - this will drive 16 PWMs in a 'wave'

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define FANOFF 1 //1 is yes fans turn off after iterations 0 is they stay on
#define DELAYSPEED 1000
#define DEBUG 0 //Turns print statements on/off, 1 is on 0 is off

#define OSCILLATORFREQUENCY 27000000
#define PWMFREQ 1600


Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40, Wire);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41, Wire);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x42, Wire);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(0x43, Wire);
Adafruit_PWMServoDriver pwm5 = Adafruit_PWMServoDriver(0x44, Wire);
Adafruit_PWMServoDriver pwm6 = Adafruit_PWMServoDriver(0x45, Wire);
Adafruit_PWMServoDriver pwm7 = Adafruit_PWMServoDriver(0x46, Wire);
Adafruit_PWMServoDriver pwm8 = Adafruit_PWMServoDriver(0x47, Wire);
Adafruit_PWMServoDriver pwm9 = Adafruit_PWMServoDriver(0x48, Wire);
Adafruit_PWMServoDriver pwm10 = Adafruit_PWMServoDriver(0x49, Wire);
Adafruit_PWMServoDriver pwm11 = Adafruit_PWMServoDriver(0x50, Wire);
Adafruit_PWMServoDriver pwm12 = Adafruit_PWMServoDriver(0x51, Wire);
Adafruit_PWMServoDriver pwm13 = Adafruit_PWMServoDriver(0x52, Wire);

Adafruit_PWMServoDriver pwmArray[13] = {pwm1, pwm2, pwm3, pwm4, pwm5, pwm6, pwm7, pwm8, pwm9, pwm10, pwm11, pwm12, pwm13};

bool allFansOff = false;
void allOff() {
  for (uint8_t boardNum=0; boardNum < 13; boardNum++) {
    for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++) {
       pwmArray[boardNum].setPWM(pwmnum, 0, 4096);
       Serial.println("All PWM Channels Off");
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("16 channel PWM test!");

  for (uint8_t boardNum=0; boardNum < 13; boardNum++) {
      pwmArray[boardNum].begin();
      pwmArray[boardNum].setOscillatorFrequency(27000000);
      pwmArray[boardNum].setPWMFreq(1600);
    }
  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't
   * that precise. You can 'calibrate' this by tweaking this number until
   * you get the PWM update frequency you're expecting!
   * The int.osc. for the PCA9685 chip is a range between about 23-27MHz and
   * is used for calculating things like writeMicroseconds()
   * Analog servos run at ~50 Hz updates, It is importaint to use an
   * oscilloscope in setting the int.osc frequency for the I2C PCA9685 chip.
   * 1) Attach the oscilloscope to one of the PWM signal pins and ground on
   *    the I2C PCA9685 chip you are setting the value for.
   * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the
   *    expected value (50Hz for most ESCs)
   * Setting the value here is specific to each individual I2C PCA9685 chip and
   * affects the calculations for the PWM update frequency. 
   * Failure to correctly set the int.osc value will cause unexpected PWM results
   */


  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);

}

void loop() {
  if (!allFansOff) {
    allOff;
    allFansOff = true;
  }


for (uint8_t boardNum=0; boardNum < 13; boardNum++) {
  if (boardNum !=12) {
  for (uint8_t pwmnum=0; pwmnum < 8; pwmnum++) {
       pwmArray[boardNum].setPWM(pwmnum, 4096, 0);
       if (DEBUG) {
       Serial.print("Board ");
       Serial.print(boardNum+1);
       Serial.print(" PWM Channel #");
       Serial.println(pwmnum+1);
       }
    }
      if (FANOFF) {
        for (uint8_t pwmnum =0; pwmnum < 8; pwmnum++) {
        pwmArray[boardNum].setPWM(pwmnum, 0, 4096);
      }
    }

        delay(DELAYSPEED);
        for (uint8_t pwmnum=8; pwmnum < 16; pwmnum++) {
          pwmArray[boardNum].setPWM(pwmnum, 4096, 0);
          if (DEBUG) {
          Serial.print("Board ");
          Serial.print(boardNum+1);
          Serial.print(" PWM Channel #");
          Serial.println(pwmnum+1);
       }
    }
    if (FANOFF) {
        for (uint8_t pwmnum =8; pwmnum < 16; pwmnum++) {
        pwmArray[boardNum].setPWM(pwmnum, 0, 4096);
      }
    }
    delay(DELAYSPEED);
    }
  
  else {
    for (uint8_t pwmnum=0; pwmnum < 8; pwmnum++) {
       pwmArray[boardNum].setPWM(pwmnum, 4096, 0);
       if (DEBUG) {
       Serial.print("Board ");
       Serial.print(boardNum+1);
       Serial.print(" PWM Channel #");
       Serial.println(pwmnum+1);
      }
    }
  }
}



#ifdef ESP8266 
    yield();  // take a breather, required for ESP8266
#endif
}
