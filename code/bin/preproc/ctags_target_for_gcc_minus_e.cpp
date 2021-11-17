# 1 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
/**

 * @file test.ino

 * @author your name (grupaso electronica 😎)

 * @brief 

 * @version 0.1

 * @date 2021-11-16

 * 

 * @copyright Copyright (c) 2021

 * 

 */
# 12 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
/* ======= LCD🚥 ======= */
// Se importa la libreria de para poder manejar el LCD[LM016L]
# 15 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino" 2
// Definimos los pines de la salida del LCD
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

const int timeDelay = 500;

/* ======= BOTON DE INICIO ▶ ======= */
// Número de pin de entrada, que representa el encendido inicio del arduino
int buttonStart = 13;

/* ======= BLUETOOH EMISOR 📶 ======= */
// usamos un pin de salida al LED
const int port0 = 0;
const int port1 = 1;

/* ======= SENSORES 🔌 ======= */
// definimos los pines de salido y/o entrada de los sensores que se utilizaran
const int speaker = 12;
const int sensorGas = 10;
const int sensorFlame = 11;
// Leds informativos ⬇
const int greenLed = 3; // Todo normal
const int redLed = 2; // Algun problema [gas - flama - temperatura]

/**

 * @brief Aqui se definen los pines de entrada y salida de los sensores 

 * también los estados iniciales de alguonos sensores o componentes

 * 

 */
# 43 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
void setup()
{
  /* ======= BOTON DE INICIO ▶ ======= */
  // definos el pin de entrada, para que el circuito pueda funcionar
  pinMode(buttonStart, 0x0);

  /* ======= LCD🚥 ======= */
  // se define el tamaño de pixeles del LCD, en este caso de 16x2
  lcd.begin(16, 2);

  // se define el número de bits que se transfieren por segundo al LCD, para poder pintar el texto
  Serial.begin(9600); // 9600 baud/S

  /* ======= SENSOR DE TEMPERATURA 🥵 ======= */
  // definimos el pin de entrada, por el cual el sensor de temperatura esta conectado
  pinMode(A1, 0x0);

  /* ======= SENSOR DE FLAMA Y GAS 🔥⛽======= */
  // definimos un pin de entrada para ambos sensores
  // El INPUT_PULLUP nos sirve para poder manipular el estado sensor [0, 1], en este caso el sensor de flama y gas estan conectados a un LOGICSTATE cada uno
  pinMode(sensorGas, 0x2);
  pinMode(sensorFlame, 0x2);

  /* ======= SPEAKER 🔊  ======= */
  // definimos el pin de salida, por el cual el speaker esta conectado
  pinMode(speaker, 0x1);

  /* ======= BLUETOOH EMISOR 📶 ======= */

  // definimos los puertos de salida, por el cual el bluetooth esta conectado, que comparten con un [VIRTUAL-TERMINAL]
  digitalWrite(port0, 0x0);
  digitalWrite(port1, 0x0);
}

/**

 * @brief Esta funcion se encarga de pintar en LCD o el VIRTUAL-TERMINAL un mensaje de ALERTA

 *  Esto se ejecutara tanto el LCD, VIRTUAL-TERMINAL y SPEAKER

 * @param messageLCD esto es imprime en el LCD 

 * @param messageBT esto se muestra en el VIRTUAL-TERMINAL

 */
# 83 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
void showAlertMessage(String messageLCD, String messageBT)
{
  // al ser un mensaje de alerta apagamos el led verde y prendemos el rojo
  digitalWrite(redLed, 0x1);
  digitalWrite(greenLed, 0x0);

  // para evitar que se pierda la temperatura en la trasición de mensajes
  if (messageLCD == "")
  {
    messageLCD = "Estable";
  }
  // se imprime en el LCD
  lcd.setCursor(0, 5);
  lcd.print(messageLCD);

  /* ======= SPEAKER 🔊  ======= */
  // definimos la frecuencia del sonido
  int frecuency = map(200, 0, 1024, 100, 5000);

  // el tiempo de emicion del sonido
  int duration = 1000;

  // usamos la funcion tone para emitir el sonido en el componente
  tone(speaker, frecuency, duration);

  delay(timeDelay);
  lcd.clear();

  /* ======= BLUETOOH EMISOR 📶 ======= */
  // se imprime en el VIRTUAL-TERMINAL en caso los puertos de salida para el bluetooth esten conectados
  if (digitalRead(port0) != 
# 113 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino" 3 4
                           __null 
# 113 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
                                && digitalRead(port1) != 
# 113 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino" 3 4
                                                         __null
# 113 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
                                                             )
  {
    Serial.println(messageBT + "Se a conectado BLUETOOH");
    // Serial.println("");
  }
}

/**

 * @brief Aqui ocurre la ejecucion del algoritmo 

 * 

 */
# 124 "e:\\University\\Ciclo IV\\electronic\\project\\code-circuit\\code\\alarm.ino"
void loop()
{

  /* ======= BOTON DE INICIO ▶ ======= */
  // si el pin conectado al boton de inicio ▶ esta en estado de bajo[0], entonces se ejecuta el algoritmo
  if (digitalRead(buttonStart) == 0x0)
  {
    // Apagamos los Leds que nos indican si hay algun problema
    digitalWrite(redLed, 0x0);
    digitalWrite(greenLed, 0x0);

    // Limpiamos el LCD en caso de que haya algun texto previo
    lcd.clear();

    // y retornamos, haci evitamos que lo que esta abajo se ejecute
    return;
  }

  /* ======= SENSOR DE TEMPERATURA 🥵 ======= */
  // obetemos la informacion del sensor de temperatura
  int valueOfSensor = analogRead(A1);

  // transformamos el valor devuelto por el sensor de temperatura a un valor de temperatura C°
  float mv = (valueOfSensor / 1024.0) * 5000.0;

  // valor inicial para que se muestre en el LCD
  float temperature = mv / 10;

  /* ======= LCD🚥 ======= */
  // posicionamos el cursor en la primera linea
  lcd.setCursor(0, 0);

  // primero se escribe un texto en el LCD
  lcd.println("Temp: ");

  // se escribe el valor de la temperatura en el LCD
  lcd.print(temperature);

  // si hay algun problema con [TEMPERATURA, GAS, FLAMA]
  if (digitalRead(sensorGas) == 0x1 || digitalRead(sensorFlame) == 0x1 || temperature >= 40)
  {

    if (temperature >= 40 && temperature <= 60)
    {
      showAlertMessage("ALERTA!", "ALERTA! Temperatura excesiva");
    }

    if (temperature > 60)
    {
      showAlertMessage("Incendio", "ALERTA! incendio 🔥");
    }

    /* ======= SENSOR DE FLAMA Y GAS 🔥⛽======= */

    if (digitalRead(sensorGas) == 0x1)
    {
      // showAlertMessage("Gas Detected", "Gas Detected");
      showAlertMessage("", "Gas Detected");
    }

    if (digitalRead(sensorFlame) == 0x1)
    {
      showAlertMessage("Flame Detected", "Flame Detected");
    }

    // para que no se ejecute el resto del codigo
    return;
  }

  /* ======= VALORES ESTANDAR ======= */
  // Todos los valores son estables
  digitalWrite(greenLed, 0x1);
  digitalWrite(redLed, 0x0);

  lcd.setCursor(0, 5);

  lcd.print("Estable ");

  delay(timeDelay);
  lcd.clear();
}
