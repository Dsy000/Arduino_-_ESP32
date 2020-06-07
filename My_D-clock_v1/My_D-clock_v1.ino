#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <Fonts/FreeSerifBold12pt7b.h>

#define OLED_WIDTH 128 // OLED display width, in pixels
#define OLED_HEIGHT 64 // OLED display height, in pixels
#define OLED_ADDR 0x3c
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
tmElements_t tm;

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
String amp;
int piezoPin = 3;


void setup() {
  //Setup Display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setFont(&FreeSerif12pt7b);
  display.setCursor(20, 20);
  display.println("Google-D");
  tone(piezoPin, 1000, 100);
  display.display();
  delay(1000);
  display.setFont();
  display.print("Booting..");
  tone(piezoPin, 1000, 100);
  display.display();
  delay(1000);
  display.print("..");
  tone(piezoPin, 1000, 100);
  display.display();
  delay(1000);
  display.print("..");
  tone(piezoPin, 1000, 100);
  delay(100);
  display.print("...");
  tone(piezoPin, 1000, 200);
  display.display();




}

void loop() {
  //Temperature Calculation----------------------------
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);

  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0) / 5.0 + 32.0;
  delay(1000);
  //Temperature Calculation----------------------------

  if (RTC.read(tm)) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1.5);
    //display.setFont(&FreeSerif12pt7b);
    display.setFont(&FreeSerifBold12pt7b);
    display.setCursor(15, 15);
    //display.print(tm.Hour);
    if (tm.Hour > 12)
    {
      tm.Hour = tm.Hour - 12;
      display.print(tm.Hour);
      amp = "PM";
    }
    else
    {
      display.print(tm.Hour);
      amp = "AM";
    }
    //Hour Sound
    if (tm.Minute == 0 ) {
      if (tm.Second == 0) {
        tone(piezoPin, 1000, 900);
      }

    }
    display.print(':');
    display.print(tm.Minute);
    display.print(':');
    display.print(tm.Second);

    display.setFont();
    display.setCursor(115, 10);
    display.print(amp);

    display.setFont();
    display.setCursor(27, 25);
    display.print(tm.Day);
    display.print('/');
    display.print(tm.Month);
    display.print('/');
    display.print(tmYearToCalendar(tm.Year));

    display.setFont();
    display.setCursor(0, 56);
    display.print("Temperature: ");
    display.print(Tc);
    display.print(" 'C");

    display.display();

  } else {
    if (RTC.chipPresent()) {
      display.clearDisplay();
      display.setFont();
      display.setCursor(0, 5);
      display.println("--! Warning !--");
      display.println(" ");
      display.println("[+]The DS1307 is stopped!!");
      display.println("[+]Please run the SetTime");
      display.display();
    } else {
      display.clearDisplay();
      display.setFont();
      display.setCursor(0, 5);
      display.println("--! Warning !--");
      display.println(" ");
      display.println("DS1307 read error!");
      display.println("Please check the I2c Cables connections.");
      display.display();
    }
    delay(960);
  }

}
