#include <LiquidCrystal.h>
#include <Adafruit_HMC5883_U.h>

/*
  The circuit:
   LCD RS pin to digital pin 8
   LCD Enable pin to digital pin 9
   LCD D4 pin to digital pin 4
   LCD D5 pin to digital pin 5
   LCD D6 pin to digital pin 6
   LCD D7 pin to digital pin 7
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
*/

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(15883);

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define LCD_LIGHT 10
#define KEYBOARD A0

void setup()
{
  Serial.begin(9600);
  if (!mag.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor!");
  }
  delay(1000);
  pinMode(LCD_LIGHT, OUTPUT);
  digitalWrite(LCD_LIGHT, true);
  lcd.begin(16, 2);
}

void loop()
{
  sensors_event_t m_event;
  mag.getEvent(&m_event);
  float mx = m_event.magnetic.x;
  float my = m_event.magnetic.y;
  float mz = m_event.magnetic.z;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X=" + String(mx, 1) + " Y=" + String(my, 1));
  lcd.setCursor(0, 1);
  lcd.print("Z=" + String(mz, 1) + " uT");
  delay(1000);
}

int read_keyboard()
{
  int sensor_data = analogRead(KEYBOARD);
  if (sensor_data < 20) {
    return 1;
  } else if ((sensor_data > 120) && (sensor_data < 160)) {
    return 2;
  } else if ((sensor_data > 290) && (sensor_data < 330)) {
    return 3;
  } else if ((sensor_data > 460) && (sensor_data < 510)) {
    return 4;
  } else if ((sensor_data > 700) && (sensor_data < 750)) {
    return 5;
  } else {
    return 0;
  }
}

