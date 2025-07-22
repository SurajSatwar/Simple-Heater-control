# Basic Heater Control System -  Assignment

##  Project Overview
This project simulates a heater control system using an Arduino Uno and a DHT22 temperature sensor. It transitions through various states based on the temperature and controls an LED (heater) and buzzer accordingly.

## Components Used
- Arduino Uno
- DHT22 Temperature Sensor
- LED (simulated heater)
- Buzzer (overheat alert)

## System States
- IDLE: Initial state
- HEATING: Temp < Target - 2°C
- STABILIZING: Temp slightly below target
- TARGET REACHED: Target temp reached
- OVERHEAT: Temp > Overheat threshold (buzzer ON)

## Communication
- Sensor: Digital GPIO
- Logging: Serial Monitor

## Features
- Real-time temperature monitoring
- Heater (LED) control logic
- Overheat warning via buzzer
- Logs all data to Serial

##  Wokwi Simulation
[(https://wokwi.com/projects/437174775546135553](https://wokwi.com/projects/437174775546135553)

## How to Run
1. Open Wokwi link
2. Click Start Simulation
3. Adjust DHT22 temp via slider
4. Observe Serial monitor, LED, and buzzer behavior

