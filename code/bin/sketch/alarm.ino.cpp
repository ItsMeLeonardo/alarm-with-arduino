#include <Arduino.h>
#line 1 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
#include <LiquidCrystal.h>
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);
int val;
int tempPin = 1;

#line 6 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
void setup();
#line 19 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
void loop();
#line 6 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(A1, INPUT);

  // Ping of LED
  pinMode(13, OUTPUT);

  // Ping of refrigeration
  pinMode(12, OUTPUT);
}

void loop()
{
  val = analogRead(A1);
  lcd.setCursor(0, 0);

  // transform the input value into a C°
  float mv = (val / 1024.0) * 5000.0;
  float temp = mv / 10;

  // this print in virtual terminal
  Serial.print("Temperature = ");
  Serial.print(temp);
  lcd.print("Temp C°: ");
  lcd.print(temp);
  // lcd.noBlink();

  // NORMAL TEMPERATURE range is 0-40
  if (temp < 40)
  {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    lcd.setCursor(0, 5);
    lcd.print("Stable 😃");
    delay(1000);
    lcd.clear();
  }

  // ALERT increase of temperature
  if (temp > 40 && temp < 60)
  {
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    lcd.setCursor(0, 5);
    lcd.print("Alert");
    delay(1000);
    lcd.clear();
  }

  // FIRE ALERT
  if (temp > 60)
  {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    lcd.setCursor(0, 5);
    lcd.print("FIRE ALERT !!!");
    delay(1000);
    lcd.clear();
    /*callFireMan() 📲*/
  }
  delay(200);
}

