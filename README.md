 AutoBin – Smart Waste Bin

AutoBin is a microcontroller-based smart waste bin concept designed to improve hygiene and waste management.  
It uses ultrasonic sensors for **contactless lid operation** and **waste level monitoring**, RGB LEDs for bin status indication, and a motor driver for lid movement.  
This repository contains simulation code, block diagrams, and design documentation.

---

## Features
- **Contactless Lid Operation**  
  Detects a user's hand within ~20 cm and automatically opens/closes the lid.
- **Waste Level Monitoring**  
  Measures bin fill level using a second ultrasonic sensor.
- **Visual Status Indication**  
  RGB LED indicates:
  - Green: Low fill
  - Yellow: Moderate fill
  - Red: Full bin
- **Simulation-Friendly**  
  Developed and tested using a simulated environment with an 8051 microcontroller.

---

## Repository Structure
/autobin
│── autobin.ino # Main control code (C for 8051-based simulation)
│── block diagram.png # Functional block diagram
│── circuit.png # Circuit schematic
│── flowchart.png # Control logic flowchart

## Simulation Preview
Added as a png file named circuit.png






