# Simple Heater Control System – Embedded Systems Assignment

**Author:** Suraj Naiku Satwar  
**Platform:** Arduino Uno (Simulated on Wokwi)  
**Language:** Embedded C (Arduino-style)  
**Sensor:** DHT22  
**UI:** 16x2 I²C LCD  
**Simulation:** [Wokwi Link](https://wokwi.com/projects/437174775546135553)

---

## Project Overview

This project implements a temperature-based heater control system that:
- Reads **real ambient temperature** using a **DHT22 sensor**
- Controls a **simulated heater** (LED) and an **overheat alert** (buzzer)
- Displays live temperature and system **state** on a **16x2 I²C LCD**
- Tracks and switches between **five operational states**



## System States

| State             | Condition                          | Heater | Buzzer | LCD Message  |
|------------------|-------------------------------------|--------|--------|--------------|
| `IDLE`           | On startup                          | OFF    | OFF    | IDLE         |
| `HEATING`        | Temp < Target − 2°C                 | ON     | OFF    | HEATING      |
| `STABILIZING`    | Target − 2°C ≤ Temp < Target        | ON     | OFF    | STABILIZING  |
| `TARGET REACHED` | Target ≤ Temp < Overheat            | OFF    | OFF    | TARGET OK    |
| `OVERHEAT`       | Temp ≥ Overheat threshold (50°C)    | OFF    | ON     | OVERHEAT!!   |



## Components Used

- Arduino Uno (Wokwi simulated)
- DHT22 Temperature Sensor (Pin D2)
- 16x2 LCD with I²C module (SDA → A4, SCL → A5)
- LED (Heater output) → Pin D3
- Buzzer (Overheat alert) → Pin D4
- 10kΩ resistor between DHT22 data & VCC (pull-up)

## Links

- Simulation (Wokwi):
  [https://wokwi.com/projects/437174775546135553](https://wokwi.com/projects/437174775546135553)

- Design Document (PDF):  
  Located in `/Heater Control System.pdf`

## How to Use

1. Open the Wokwi simulation link.
2. Click Start Simulation.
3. Use the DHT22 temperature slider (left panel) to adjust temperature.
4. Observe:
   - LCD shows live temperature and system state.
   - LED turns ON/OFF based on state.
   - Buzzer activates when temperature crosses 50°C.
