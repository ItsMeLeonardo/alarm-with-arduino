# 1 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
# 2 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino" 2
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);

const int timeDelay = 1000;
const int refrigerationMotor = 12;
const int ledOfNormalTemperature = 13;

void setup()
{
  // define 16col and 2row
  lcd.begin(16, 2);

  // define the bit transfer speed per second
  Serial.begin(9600); // 9600 baud/s

  // input of temperature sensor
  pinMode(A1, 0x0);

  // Ping of refrigeration
  pinMode(refrigerationMotor, 0x1);

  // Ping of LED
  pinMode(ledOfNormalTemperature, 0x1);
}

void loop()
{
  const int valueOfSensor = analogRead(A1);
  lcd.setCursor(0, 0);

  // transform the input value into a C°
  float mv = (valueOfSensor / 1024.0) * 5000.0;
  float temperature = mv / 10;

  // this print in virtual terminal
  Serial.print("Temperature = ");
  Serial.print(temperature);

  // print in LCD
  lcd.print("Temperature: ");
  lcd.print(temperature);

  // NORMAL TEMPERATURE range is 0-40
  if (temperature < 40)
  {
    digitalWrite(ledOfNormalTemperature, 0x1);
    digitalWrite(refrigerationMotor, 0x0);
    lcd.setCursor(0, 5);
    lcd.print("Stable 😃");
    delay(timeDelay);
    lcd.clear();
    /*do nothing() 📲*/
  }

  // ALERT increase of temperature
  if (temperature >= 40 && temperature <= 60)
  {
    digitalWrite(ledOfNormalTemperature, 0x0);
    digitalWrite(refrigerationMotor, 0x1);
    lcd.setCursor(0, 5);
    lcd.print("Alert!! 🥵");
    delay(timeDelay);
    lcd.clear();
    /*send alert() 📲*/
  }

  // FIRE ALERT
  if (temperature > 60)
  {
    digitalWrite(ledOfNormalTemperature, 0x0);
    digitalWrite(refrigerationMotor, 0x0);
    lcd.setCursor(0, 5);
    lcd.print("FIRE ALERT !!!");
    delay(timeDelay);
    lcd.clear();
    /*callFireMan() 📲*/
  }
  delay(200);
}
