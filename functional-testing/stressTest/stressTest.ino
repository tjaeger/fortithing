/**
 * StressTest for Fortithing V2 board
 * 
 * Phil 2020/10/31
 *
 */

//define

#define WIFI_SSID "Your2.4GHZSSID"
#define WIFI_PASSWORD "YourWPA/WPA2Password"
#define SERVER "192.168.0.23"
#define PATH "/file/file.php"


//needed lib: FastLED, Adafruit LIS3DH, Adafruit BMP280 Library 

// WARNING: after installing libs, patch Adafruit BMP280 LIB to correctly read the BMP280
// Open this file https://github.com/adafruit/Adafruit_BMP280_Library/blob/master/Adafruit_BMP280.cpp
// comment those 2 lines:
// 99:   if (read8(BMP280_REGISTER_CHIPID) != chipid)
//100:    return false;

//serial
#include <Arduino.h>
#define USE_SERIAL Serial

//Wifi+http
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

//Accelerometer
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

//LED
#include <FastLED.h>

//Temp
//#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_BMP280.h>


//Wifi
WiFiMulti wifiMulti;

//Accelerometer
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
sensors_event_t event;

//LED
#define DATA_PIN 13
#define CLOCK_PIN 14
// #define DATA_PIN 23
// #define CLOCK_PIN 22
#define NUM_LEDS    4
#define BRIGHTNESS  80
#define LED_TYPE    APA102
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

#define UPDATES_PER_SECOND 1

//Temp
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

void setupTemp() {
  USE_SERIAL.println(F("BMP280 Sensor event test"));

  if (!bmp.begin(0x76)) {
    USE_SERIAL.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    return;
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();
}

void setupLED() {
    FastLED.addLeds<LED_TYPE, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}

void setupAccelerometer() {
  
  USE_SERIAL.println("LIS3DH test!");

  if (! lis.begin(0x19)) {   // change this to 0x19 for alternative i2c address
    USE_SERIAL.println("Couldnt start");
    while (1) yield();
  }
  USE_SERIAL.println("LIS3DH found!");

  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

  USE_SERIAL.print("Range = "); Serial.print(2 << lis.getRange());
  USE_SERIAL.println("G");

  // lis.setDataRate(LIS3DH_DATARATE_50_HZ);
  USE_SERIAL.print("Data rate set to: ");
  switch (lis.getDataRate()) {
    case LIS3DH_DATARATE_1_HZ: USE_SERIAL.println("1 Hz"); break;
    case LIS3DH_DATARATE_10_HZ: USE_SERIAL.println("10 Hz"); break;
    case LIS3DH_DATARATE_25_HZ: USE_SERIAL.println("25 Hz"); break;
    case LIS3DH_DATARATE_50_HZ: USE_SERIAL.println("50 Hz"); break;
    case LIS3DH_DATARATE_100_HZ: USE_SERIAL.println("100 Hz"); break;
    case LIS3DH_DATARATE_200_HZ: USE_SERIAL.println("200 Hz"); break;
    case LIS3DH_DATARATE_400_HZ: USE_SERIAL.println("400 Hz"); break;

    case LIS3DH_DATARATE_POWERDOWN: USE_SERIAL.println("Powered Down"); break;
    case LIS3DH_DATARATE_LOWPOWER_5KHZ: USE_SERIAL.println("5 Khz Low Power"); break;
    case LIS3DH_DATARATE_LOWPOWER_1K6HZ: USE_SERIAL.println("16 Khz Low Power"); break;
  }
}

void setupWifi() {
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
}


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};



// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.

void findreplace(char* ptr, char c1, char c2) {

    while (1) {
      if (*ptr == '\0')
        return;
      if (*ptr == c1)
        *ptr=c2;
      ptr++;
    }
}

void setup() {

    USE_SERIAL.begin(115200);
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] Wait for %d second(s)\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    setupWifi();
    setupLED();
    setupAccelerometer();
    setupTemp();
}


uint8_t order = '0';

void loop() {

    USE_SERIAL.print("[MAIN] begin...\n");

    //LED
    ChangePalettePeriodically();
    static uint8_t startIndex = 0;
    startIndex++;
    FillLEDsFromPaletteColors(startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    // end LED

    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;
        char urlFormated[400];

        switch (order) {
          
          case '0':   // send accelerometer
            char  x[8],y[8],z[8];
    
            lis.read();
            lis.getEvent(&event);
    
            dtostrf(event.acceleration.x, 7, 2, x);
            dtostrf(event.acceleration.y, 7, 2, y);
            dtostrf(event.acceleration.x, 7, 2, z);
    
            sprintf(urlFormated,"http://%s%s?data=acc%%3B%d%%3B%d%%3B%d%%3B%s%%3B%s%%3B%s\0",SERVER,PATH,lis.x,lis.y,lis.z,x,y,z);
            findreplace(urlFormated,' ','_');   // no space in URL
            break;
            
          case '1':   // send temperature pressure
            char  temp[8],pres[8];

            sensors_event_t temp_event, pressure_event;
            bmp_temp->getEvent(&temp_event);
            bmp_pressure->getEvent(&pressure_event);

            dtostrf(temp_event.temperature, 7, 2, temp);
            dtostrf(pressure_event.pressure, 7, 2, pres);

            sprintf(urlFormated,"http://%s%s?data=temp%%3B%s%%3B%s\0",SERVER,PATH,temp,pres);
            findreplace(urlFormated,' ','_');   // no space in URL
            break;

          default:
            sprintf(urlFormated,"http://%s%s?data=err%%3Bfound nothing to do\0",SERVER,PATH);
            findreplace(urlFormated,' ','_');   // no space in URL
            break;
        }

        USE_SERIAL.print("[HTTP] begin...\n");

        USE_SERIAL.print("[HTTP] url: ");
        USE_SERIAL.print(urlFormated);
        USE_SERIAL.print("\n");

        http.begin(urlFormated); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
                order=payload.c_str()[0];
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    USE_SERIAL.print("[MAIN] end.\n");

    delay(1000);
}
