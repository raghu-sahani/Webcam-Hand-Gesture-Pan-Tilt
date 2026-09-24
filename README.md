# Webcam Hand Gesture Pan-Tilt Controller

Control a 2-axis pan-tilt mechanism using only your hand and a laptop webcam.

The browser tracks your hand with MediaPipe, shows only a hand skeleton on a black screen, and sends smooth PAN/TILT angles to an Arduino UNO through USB using Web Serial.

## Gesture Controls

| Gesture | Movement | Servo |
| --- | --- | --- |
| Index finger only | Move left/right | PAN servo on D3 |
| Index + middle fingers | Move up/down | TILT servo on D5 |

The other gestures are ignored.

## Features

- Webcam-based hand tracking
- Black display with only the hand skeleton visible
- Smooth and responsive servo movement
- PAN reverse option
- TILT reverse option
- Center button sends both servos to 90 degrees
- Gesture locking to reduce accidental mode switching
- No ESP32 required
- Beginner-friendly wiring and setup

## Hardware Required

- Arduino UNO
- 2 servo motors
- Pan-tilt bracket or your own mechanical mount
- Laptop or desktop with webcam
- USB cable for Arduino
- External regulated 5 V supply for the servos
- Jumper wires

## Pin Connections

| Device | Connection |
| --- | --- |
| PAN servo signal | Arduino D3 |
| TILT servo signal | Arduino D5 |
| PAN servo positive | External 5 V |
| TILT servo positive | External 5 V |
| PAN servo GND | External GND |
| TILT servo GND | External GND |
| Arduino GND | External GND |

Important: Arduino GND and the external servo power-supply GND must be connected together.

Do not power two high-current servos directly from the Arduino 5 V pin.

## Repository Structure

```text
Webcam-Hand-Gesture-Pan-Tilt/
|
|-- README.md
|
|-- arduino/
|   `-- PanTiltHandControl/
|       `-- PanTiltHandControl.ino
|
|-- web/
|   `-- pan_tilt_hand_control.html
|
`-- docs/
    |-- WIRING.md
    `-- TROUBLESHOOTING.md
```

## Software Required

1. Arduino IDE
2. Google Chrome or Microsoft Edge
3. Python 3
4. Internet connection while loading the MediaPipe libraries

## Step 1 - Upload the Arduino Code

1. Connect the Arduino UNO to your computer using USB.
2. Open Arduino IDE.
3. Open:

```text
arduino/PanTiltHandControl/PanTiltHandControl.ino
```

4. Go to **Tools > Board > Arduino Uno**.
5. Select the correct COM port.
6. Click **Upload**.
7. Wait for the upload to complete.
8. Close Arduino Serial Monitor if it is open.

The webpage cannot connect to the Arduino while Serial Monitor is using the same serial port.

## Step 2 - Connect the Servos

### PAN Servo

```text
Signal -> Arduino D3
V+     -> External 5 V
GND    -> External GND
```

### TILT Servo

```text
Signal -> Arduino D5
V+     -> External 5 V
GND    -> External GND
```

Then connect:

```text
External GND -> Arduino GND
```

This common ground is required.

## Step 3 - Start the Web Controller

Open PowerShell, Command Prompt, or Terminal inside the repository folder.

Run:

```bash
python -m http.server 8000
```

Then open Chrome or Edge and visit:

```text
http://localhost:8000/web/pan_tilt_hand_control.html
```

Do not simply double-click the HTML file. Running it through localhost gives the browser the correct environment for camera access and Web Serial.

## Step 4 - Start the Camera

Click:

```text
Start Camera
```

Allow camera permission.

You should see:

- a black screen
- a green hand skeleton
- no normal webcam video

## Step 5 - Connect the Arduino

Click:

```text
Connect Arduino
```

Select the Arduino COM port.

Then click:

```text
Enable Servo Motion
```

## How to Control PAN

Show only your index finger.

```text
      INDEX
        |
        |
        v

Move LEFT <------> RIGHT
```

The PAN servo on D3 follows the horizontal finger position.

## How to Control TILT

Show your index and middle fingers.

```text
     INDEX   MIDDLE
        |      |
        |      |
        v      v

          Move UP
             ^
             |
             v
          Move DOWN
```

The TILT servo on D5 follows the vertical position.

## Reverse Motor Direction

If the PAN servo moves opposite to your hand:

```text
Enable: Reverse PAN
```

If the TILT servo moves opposite to your hand:

```text
Enable: Reverse TILT
```

No Arduino code changes are required.

## Center Button

Click:

```text
Center
```

Both servos are sent to:

```text
PAN  = 90 degrees
TILT = 90 degrees
```

## Smoothness Settings

The system uses two stages of smoothing.

### Browser smoothing

```javascript
const CONTROL_SMOOTHING = 0.16;
const CONTROL_DEADBAND = 0.7;
```

### Arduino smoothing

```cpp
const float SMOOTH_FACTOR = 0.09;
const float DEAD_BAND = 0.20;
```

For faster movement, increase `SMOOTH_FACTOR` slightly.

For softer/slower movement, decrease it slightly.

Recommended range:

```text
0.06  -> softer
0.09  -> current balanced setting
0.12  -> faster
```

## Recommended Camera Setup

For best tracking:

- Keep your complete hand visible.
- Use good lighting.
- Keep the hand reasonably close to the camera.
- Avoid covering fingers with each other.
- Use a simple background if possible.
- Keep the webcam roughly in front of your hand.

## Power Warning

Servo motors can draw significantly more current than the Arduino can safely provide.

Use a suitable external regulated 5 V supply for the servos.

Always connect:

```text
External GND <-> Arduino GND
```

## Quick Start

```text
1. Wire PAN servo to D3
2. Wire TILT servo to D5
3. Use external 5 V servo power
4. Upload Arduino firmware
5. Close Serial Monitor
6. Run: python -m http.server 8000
7. Open the webpage in Chrome/Edge
8. Start Camera
9. Connect Arduino
10. Enable Servo Motion
11. Index only = PAN
12. Index + Middle = TILT
```

## Troubleshooting

See:

```text
docs/TROUBLESHOOTING.md
```

for common setup and tracking problems.

## Project Idea

This project demonstrates a simple vision-based human-machine interface where a normal webcam becomes a contactless controller for a robotic pan-tilt mechanism.
