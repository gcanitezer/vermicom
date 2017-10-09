/**
 *kaynaklar
 *
 *chip resmi pinout
http://www.instructables.com/id/ESP32-With-Integrated-OLED-WEMOSLolin-Getting-Star/
 *röle
 *
 *
 *ekran 5 ve 4 ü kullanıyor
 *SSD1306  display(0x3c, 5, 4);
 *
 *sensorler 13 26 ama belli değil
 *
 *
 *
 *
 *
 */

// Include the correct display library
// For a connection via I2C using Wire include
//#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
// or #include "SH1106.h" alis for `#include "SH1106Wire.h"`

// Include custom images
#include "images.h"

// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS
// SSD1306Spi        display(D0, D2, D8);
// or
// SH1106Spi         display(D0, D2);

// Initialize the OLED display using brzo_i2c
// D3 -> SDA
// D5 -> SCL
// SSD1306Brzo display(0x3c, D3, D5);
// or
// SH1106Brzo  display(0x3c, D3, D5);

#define DISPLAY_SDA 5 
#define DISPLAY_SCL 4

#define RELAY_HEATER  0
#define RELAY_PUMP  2
#define RELAY_3  14
#define RELAY_4  12

#define TEMPRATURE_SENSOR 13
#define SOIL_HUMIDITY_SENSOR 26
#define AIR_TEMP_HUM_SENSOR 25

//pin up for giving energy to humidity reader to minimize electrolize
#define SOIL_HUMIDITY_OPEN 16



// Initialize the OLED display using Wire library 5/4
SSD1306  display(0x3c, DISPLAY_SDA, DISPLAY_SCL);
// SH1106 display(0x3c, D3, D5);


#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;
 

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  //int a = GPIO12;
  
 pinMode(RELAY_HEATER, OUTPUT);
 pinMode(RELAY_PUMP, OUTPUT);
 pinMode(RELAY_3, OUTPUT);
 pinMode(RELAY_4, OUTPUT);

  pinMode(SOIL_HUMIDITY_SENSOR,INPUT);
  pinMode(TEMPRATURE_SENSOR,INPUT);

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

}

void drawFontFaceDemo() {
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hello world");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Hello world");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello world");
}

void drawTextFlowDemo() {
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(0, 0, 128,
      "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
}

void drawTextAlignmentDemo() {
    // Text alignment demo
  display.setFont(ArialMT_Plain_10);

  // The coordinates define the left starting point of the text
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 10, "Left aligned (0,10)");

  // The coordinates define the center of the text
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 22, "Center aligned (64,22)");

  // The coordinates define the right end of the text
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 33, "Right aligned (128,33)");
}

void drawRectDemo() {
      // Draw a pixel at given position
    for (int i = 0; i < 10; i++) {
      display.setPixel(i, i);
      display.setPixel(10 - i, i);
    }
    display.drawRect(12, 12, 20, 20);

    // Fill the rectangle
    display.fillRect(14, 14, 17, 17);

    // Draw a line horizontally
    display.drawHorizontalLine(0, 40, 20);

    // Draw a line horizontally
    display.drawVerticalLine(40, 0, 20);
}

void drawCircleDemo() {
  for (int i=1; i < 8; i++) {
    display.setColor(WHITE);
    display.drawCircle(32, 32, i*3);
    if (i % 2 == 0) {
      display.setColor(BLACK);
    }
    display.fillCircle(96, 32, 32 - i* 3);
  }
}

void drawProgressBarDemo() {
  int progress = (counter / 5) % 100;
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
}

void drawImageDemo() {
    // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
    // on how to create xbm files
    display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}

Demo demos[] = {drawFontFaceDemo, drawTextFlowDemo, drawTextAlignmentDemo, drawRectDemo, drawCircleDemo, drawProgressBarDemo, drawImageDemo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;

void loop() {



//role olayı
//digitalWrite( role1,HIGH );
//digitalWrite( role2,HIGH );
//digitalWrite( role3,HIGH );
//digitalWrite( role4,HIGH );
//delay(1111);
//digitalWrite( role1,LOW );
//digitalWrite( role2,LOW );
//digitalWrite( role3,LOW );
//digitalWrite( role4,LOW );
//delay(1111);



// clear the display
  display.clear();
  
  // read the analog in value:
  int nem_value = analogRead(SOIL_HUMIDITY_SENSOR);
  Serial.print("nem_sensoru giris=");Serial.println(nem_value);
  display.drawString(0, 10, "nem_sensoru giris="+String(nem_value));
  //Serial.print("nem_sensoru map=");Serial.println(  map(nem_value, 1200, 4096, 0, 100) ) ;
  Serial.println("");
  int sicaklik_value = analogRead(TEMPRATURE_SENSOR);
  Serial.print("sicaklik_sensoru giris=");Serial.println(sicaklik_value);
  //Serial.print("sicaklik_sensoru map=");Serial.println( map(sicaklik_value, 1200, 4096, 0, 100) ) ;
 
 Serial.println("hello");
  // wait 1 seconds before the next loop to minimise corrosion on the rain detector.

  display.display();
  
  delay(4000);


  /*
  
  // draw the current demo method
  demos[demoMode]();

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  display.display();

  if (millis() - timeSinceLastModeSwitch > DEMO_DURATION) {
    demoMode = (demoMode + 1)  % demoLength;
    timeSinceLastModeSwitch = millis();
  }
  counter++;
  */
  delay(10);
  
}
