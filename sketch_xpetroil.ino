#include <SPI.h>
#include <SD.h>

const int chipSelect = 9; // Pin utilizado para la tarjeta SD
const int sensorTemp = A0; // Pin analógico utilizado para el sensor de temperatura
const int sensorPresion = A1; // Pin analógico utilizado para el sensor de presión
const int sensorCaudal = A2; // Pin analógico utilizado para el sensor de caudal
const int sensorAceleracion = A3; // Pin analógico utilizado para el sensor de aceleración

void setup() {
  Serial.begin(9600);
  
  // Inicialización de la tarjeta SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Error al inicializar la tarjeta SD");
    return;
  }
  
  Serial.println("Tarjeta SD inicializada correctamente");
}

void loop() {
  // Lectura del tiempo y los sensores
  unsigned long tiempo = millis();
  float temp = leerSensorTemp();
  float presion = leerSensorPresion();
  float caudal = leerSensorCaudal();
  float aceleracion = leerSensorAceleracion();
  
  // Registro de los datos en la tarjeta SD
  File dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(tiempo);
    dataFile.print(",");
    dataFile.print(temp);
    dataFile.print(",");
    dataFile.print(presion);
    dataFile.print(",");
    dataFile.print(caudal);
    dataFile.print(",");
    dataFile.print(aceleracion);
    dataFile.println();
    dataFile.close();
    Serial.println("Datos registrados correctamente");
  } else {
    Serial.println("Error al abrir el archivo");
  }
  
  delay(300000); // Espera 5 minutos antes de leer y registrar los datos nuevamente
}

// Funciones para la lectura de los sensores
float leerSensorTemp() {
  int lectura = analogRead(sensorTemp);
  float voltaje = (lectura * 5.0) / 1023.0;
  float temperatura = (voltaje - 1.25) / 0.005;
  return temperatura;
}

float leerSensorPresion() {
  int lectura = analogRead(sensorPresion);
  float presion = (lectura * 5.0) / 1023.0;
  return presion;
}

float leerSensorCaudal() {
  int lectura = analogRead(sensorCaudal);
  float voltaje = (lectura * 5.0) / 1023.0;
  float caudal = voltaje / 5.0 * 100.0; // Sensor de caudal tiene una salida de 0 a 5 voltios y mide un flujo máximo del 100%
  return caudal;
}

float leerSensorAceleracion() {
  int lectura = analogRead(sensorAceleracion);
  float voltaje = (lectura * 5.0) / 1023.0;
  float aceleracion = voltaje / 0.1; // Sensor detiene una sensibilidad de 0.1 V/g
  return aceleracion;
}

