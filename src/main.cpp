#include <Arduino.h>
#include <bits/stdc++.h>
#include <hardware/gpio.h>
#include "hardware/pio.h"
#include <strings.h>
#include <EEPROM.h>

#include <TFT_eSPI.h>

#include "globals.h"

TFT_eSPI tft = TFT_eSPI();
bool toggle = false;

// Code to run a screen calibration, not needed when calibration values set in setup()
void touch_calibrate()
{
  uint16_t calData[6];
  uint8_t calDataOK = 0;

  // Calibrate
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 0);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.println("Touch corners as indicated");

  tft.setTextFont(1);
  tft.println();

  tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
 
  Serial.println(); Serial.println();
  Serial.println("// Use this calibration code in setup():");
  Serial.print("  uint16_t calData[5] = ");
  Serial.print("{ ");
  calData[5] = 4;
  
  EEPROM.begin(sizeof(calData));
  EEPROM.put(EEPROM_ADDR, calData);  
  EEPROM.commit();
  EEPROM.end();

  tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("Calibration complete!");
  tft.println("Calibration code sent to Serial port.");

  delay(4000);
}

void setup()
{
  uint16_t calData[6];
  EEPROM.begin(sizeof(calData));
  delay(2000);
  Serial.begin(115200);

  EEPROM.get(EEPROM_ADDR, calData);
  EEPROM.end();


  gpio_init(15);
  gpio_set_drive_strength(15, GPIO_DRIVE_STRENGTH_8MA);
  gpio_set_dir(15, GPIO_OUT);

  tft.init();

  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  tft.println(calData[5]);

  delay(5000);
  //if (calData[5] != 4)
  {
    touch_calibrate();
  }

  tft.fillScreen(TFT_BLACK);

  tft.println("test");
  tft.println(calData[0]);
  tft.println(calData[1]);
  tft.println(calData[2]);
  tft.println(calData[3]);
  tft.println(calData[4]);
  tft.println(calData[5]);
  tft.println("test");


  Serial.println("Setup done");
}

void loop()
{
  while (true)
  {
        gpio_put(15, toggle);
        toggle = !toggle;
        sleep_ms(500);
  }
}
