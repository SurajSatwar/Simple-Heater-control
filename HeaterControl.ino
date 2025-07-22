#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin configuration
#define DHTPIN 2
#define DHTTYPE DHT22
#define HEATER_PIN 3
#define BUZZER_PIN 4

// Thresholds
#define TARGET_TEMP 40
#define OVERHEAT_TEMP 50

DHT dht(DHTPIN, DHTTYPE);

// Enum-style constants for states
#define STATE_IDLE 0
#define STATE_HEATING 1
#define STATE_STABILIZING 2
#define STATE_TARGET_REACHED 3
#define STATE_OVERHEAT 4

int currentState = STATE_IDLE;

void initPins() {
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(HEATER_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void initLCD() {
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Heater System");
}

void printState(int state) {
  switch (state) {
    case STATE_IDLE:
      lcd.print("IDLE       ");
      break;
    case STATE_HEATING:
      lcd.print("HEATING    ");
      break;
    case STATE_STABILIZING:
      lcd.print("STABILIZING");
      break;
    case STATE_TARGET_REACHED:
      lcd.print("TARGET OK  ");
      break;
    case STATE_OVERHEAT:
      lcd.print("OVERHEAT!! ");
      break;
  }
}

void controlLogic(float temp) {
  // State transition
  if (temp < TARGET_TEMP - 2) {
    currentState = STATE_HEATING;
  }
  else if (temp >= TARGET_TEMP - 2 && temp < TARGET_TEMP) {
    currentState = STATE_STABILIZING;
  }
  else if (temp >= TARGET_TEMP && temp < OVERHEAT_TEMP) {
    currentState = STATE_TARGET_REACHED;
  }
  else if (temp >= OVERHEAT_TEMP) {
    currentState = STATE_OVERHEAT;
  }

  // Actuation + LCD display
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("C ");

  switch (currentState) {
    case STATE_IDLE:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      printState(STATE_IDLE);
      break;

    case STATE_HEATING:
      digitalWrite(HEATER_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
      printState(STATE_HEATING);
      break;

    case STATE_STABILIZING:
      digitalWrite(HEATER_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
      printState(STATE_STABILIZING);
      break;

    case STATE_TARGET_REACHED:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      printState(STATE_TARGET_REACHED);
      break;

    case STATE_OVERHEAT:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
      printState(STATE_OVERHEAT);
      break;
  }
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  dht.begin();
  initPins();
  initLCD();
  currentState = STATE_IDLE;
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Sensor Error");
    lcd.setCursor(0, 1);
    lcd.print("Sensor Error    ");
    delay(2000);
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C, State: ");
  Serial.println(currentState);

  controlLogic(temp);
  delay(2000);  // Wait 2 seconds between readings
}
