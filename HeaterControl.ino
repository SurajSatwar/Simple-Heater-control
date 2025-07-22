#include "DHT.h"

#define DHTPIN 2         // Data pin connected to DHT22
#define DHTTYPE DHT22
#define HEATER_PIN 3     // Heater simulated by LED
#define BUZZER_PIN 4     // Overheat buzzer

DHT dht(DHTPIN, DHTTYPE);

enum HeaterState {
  IDLE,
  HEATING,
  STABILIZING,
  TARGET_REACHED,
  OVERHEAT
};

HeaterState currentState;

const float TARGET_TEMP = 40.0;
const float OVERHEAT_TEMP = 50.0;
float temp = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(HEATER_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  currentState = IDLE;
}

void loop() {
  delay(2000); // DHT22 reads every 2 sec
  temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // State transition logic
  if (temp < TARGET_TEMP - 2) {
    currentState = HEATING;
  } else if (temp >= TARGET_TEMP - 2 && temp < TARGET_TEMP) {
    currentState = STABILIZING;
  } else if (temp >= TARGET_TEMP && temp < OVERHEAT_TEMP) {
    currentState = TARGET_REACHED;
  } else if (temp >= OVERHEAT_TEMP) {
    currentState = OVERHEAT;
  }

  // Actuator and feedback
  switch (currentState) {
    case IDLE:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      break;

    case HEATING:
      digitalWrite(HEATER_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
      break;

    case STABILIZING:
      digitalWrite(HEATER_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
      break;

    case TARGET_REACHED:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      break;

    case OVERHEAT:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
      break;
  }

  // Log data
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C\tState: ");
  printState(currentState);
}

void printState(HeaterState s) {
  switch (s) {
    case IDLE: Serial.println("IDLE"); break;
    case HEATING: Serial.println("HEATING"); break;
    case STABILIZING: Serial.println("STABILIZING"); break;
    case TARGET_REACHED: Serial.println("TARGET REACHED"); break;
    case OVERHEAT: Serial.println("OVERHEAT"); break;
  }
}
