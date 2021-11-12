# 1 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
# 2 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino" 2
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);
int val;
int tempPin = 1;

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(A1, 0x0);

  // Ping of LED
  pinMode(13, 0x1);

  // Ping of refrigeration
  pinMode(12, 0x1);
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
    digitalWrite(13, 0x1);
    digitalWrite(12, 0x0);
    lcd.setCursor(0, 5);
    lcd.print("Stable 😃");
    delay(1000);
    lcd.clear();
  }

  // ALERT increase of temperature
  if (temp > 40 && temp < 60)
  {
    digitalWrite(12, 0x0);
    digitalWrite(13, 0x1);
    lcd.setCursor(0, 5);
    lcd.print("Alert");
    delay(1000);
    lcd.clear();
  }

  // FIRE ALERT
  if (temp > 60)
  {
    digitalWrite(13, 0x0);
    digitalWrite(12, 0x0);
    lcd.setCursor(0, 5);
    lcd.print("FIRE ALERT !!!");
    delay(1000);
    lcd.clear();
    /*callFireMan() 📲*/
  }
  delay(200);
}
