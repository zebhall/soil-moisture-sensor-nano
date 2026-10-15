#include <Adafruit_SH110X.h>
#include <splash.h>

#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // px
#define SCREEN_HEIGHT 64

// SSD1306 display, using SPI
#define OLED_MOSI   10 // soldered these the wrong way around lol
#define OLED_CLK   9 // soldered these the wrong way around lol
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

// Soil moisture sensor connected to analog pin A5
#define SENSOR_PIN A5 

#define MIN_SENS_VAL 0
#define MAX_SENS_VAL 750


// create display
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
// important stuff
Serial.begin(9600);
display.begin(0, true);
// say hi to wade
display.clearDisplay();
display.setTextSize(3); 
display.setCursor(0, 0);
display.setTextColor(SH110X_WHITE);
display.println("HI WADE");
display.display();
delay(500);
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);
  printMoistureToScreen(sensorValue);
  delay(300);
}

void printMoistureToScreen(int sensorVal){
// output to serial console debug
// Serial.println(wetPct, 2);

// calculate moisture val
float wetPct = ((float)sensorVal / MAX_SENS_VAL) * 100.0f;

// print the moisture to the screen
display.clearDisplay();
display.setTextSize(2); 
display.setCursor(0, 0);
display.setTextColor(SH110X_WHITE);
display.println("MOISTURE");
// space-pad the % value
if (wetPct < 10) {
  display.print("  ");
} else if (wetPct < 100) {
  display.print(" ");
}
display.print(wetPct, 2);
display.print(" %\n\n");
// also print the raw sensor output value
display.print("RAW ");
display.print(sensorVal);
display.display();
}

