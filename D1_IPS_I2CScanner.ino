/***************************************************
  This is a library for the ST7789 IPS SPI display.
https://github.com/wilmsn/Arduino-ST7789-Library
  Written by Ananev Ilya.

   Rui Santos
  Complete project details at https://randomnerdtutorials.com
 ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library by Adafruit
#include <Arduino_ST7789.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <SPI.h>
#include <Wire.h>
/*
   Attention: If you use blue "D1 Arduino compatible" Board use "LOLIN(WEMOS) D1 R2 &mini" as board in ARDUINO IDE.
              Pins are labeled wrong on Bord!!!!
              Label on board   |   Use in programm  | Connect to Display
              D2               |   D0               | RES
              D15/SCL/D3       |   D1               | DC
              D13/SCK/D5       |   D5               | SCL
              D1/MOSI/D7       |   D7               | SDA
*/
#define TFT_DC    D0
#define TFT_RST   D6 
//#define TFT_CS    10 // only for displays with CS pin
#define TFT_MOSI  D7   // for hardware SPI data pin (all of available pins)
#define TFT_SCLK  D5   // for hardware SPI sclk pin (all of available pins)

//You can use different type of hardware initialization
//using hardware SPI (11, 13 on UNO; 51, 52 on MEGA; ICSP-4, ICSP-3 on DUE and etc)
Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST); //for display without CS pin
//Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_CS); //for display with CS pin
//or you can use software SPI on all available pins (slow)
//Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK); //for display without CS pin
//Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_CS); //for display with CS pin

//*********
// create variables

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.print("Hello! ST7789 TFT Test");
  Serial.println("\nI2C Scanner");
  

  tft.init(240, 240);   // initialize a ST7789 chip, 240x240 pixels
  tft.setRotation(3);   // rotate display to landscape
  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  tft.fillScreen(BLACK);
  
  // tft print function
  //tftPrintTest();
  //Serial.println("TFT Printtest");
  //delay(4000);

  
}

void loop() {
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  tft.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      tft.setTextSize(3);
      tft.println("I2C device  ");
      
      tft.println(" ");
      tft.setTextSize(4);
      tft.print("0x");
      if (address<16) {
        Serial.print("0");
        tft.print("0");
      }
      Serial.println(address,HEX);
       tft.println(address,HEX);
      nDevices++;
    }
    else if (error==4) {
      Serial.print("Unknow error at address 0x");
      tft.println("Unknow error at address 0x");
      if (address<16) {
        Serial.print("0");
         tft.println("0");
      }
      Serial.println(address,HEX);
      tft.println(address,HEX);
    }    
  }
  if (nDevices == 0) {
    tft.setTextSize(2);
    Serial.println("No I2C devices found\n");
    tft.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
    tft.setTextSize(2);
     tft.println("done\n");
  }
  delay(2000); 
  tft.fillScreen(BLACK);         
}


void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(BLACK);
 
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("Hello World!");
 
  tft.setTextColor(WHITE);
  
  //tft.println(I2C_address);
}
