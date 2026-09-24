# Wiring Guide

## PAN Servo

- Signal wire -> Arduino D3
- Red / V+ wire -> External regulated 5 V
- Brown/Black / GND wire -> External power-supply GND

## TILT Servo

- Signal wire -> Arduino D5
- Red / V+ wire -> External regulated 5 V
- Brown/Black / GND wire -> External power-supply GND

## Common Ground

Connect:

- External power-supply GND -> Arduino GND

This connection is required.

## Simple Diagram

```text
External 5 V
   |
   +---- PAN servo V+
   |
   +---- TILT servo V+

External GND
   |
   +---- PAN servo GND
   |
   +---- TILT servo GND
   |
   +---- Arduino GND

Arduino D3  ---- PAN servo signal
Arduino D5  ---- TILT servo signal
```

## Important Power Note

Do not rely on the Arduino 5 V pin to power two servos under load.

Use a separate regulated 5 V supply with enough current for your servos.
