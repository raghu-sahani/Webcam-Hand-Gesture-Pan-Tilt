# Troubleshooting

## Webpage says "Use Chrome or Edge"

The project uses Web Serial. Open the webpage in Google Chrome or Microsoft Edge.

## Camera does not start

- Allow camera permission in the browser.
- Close any other app using the webcam.
- Reload the page.
- Run the webpage through localhost, not by double-clicking the HTML file.

Use:

```bash
python -m http.server 8000
```

Then open:

```text
http://localhost:8000/web/pan_tilt_hand_control.html
```

## Arduino does not appear in the port list

- Check the USB cable.
- Try another USB port.
- Confirm the COM port appears in Arduino IDE.
- Close Arduino Serial Monitor before connecting from the webpage.

## Arduino connects but servos do not move

Check:

1. Click Enable Servo Motion.
2. PAN signal wire is on D3.
3. TILT signal wire is on D5.
4. Servos have external 5 V power.
5. External GND is connected to Arduino GND.
6. The power supply can provide enough current.

## Servo moves in the wrong direction

Use:

- Reverse PAN
- Reverse TILT

No Arduino code change is required.

## PAN gesture is not detected

Show only the index finger.

Keep:

- index extended
- middle folded
- ring folded
- pinky folded

Move the index finger left and right.

## TILT gesture is not detected

Show index and middle fingers.

Keep:

- index extended
- middle extended
- ring folded
- pinky folded

Move the two fingers up and down.

## Motion is too slow

Increase this value in the Arduino sketch:

```cpp
const float SMOOTH_FACTOR = 0.09;
```

Try:

```cpp
const float SMOOTH_FACTOR = 0.12;
```

## Motion is too jerky

Reduce:

```cpp
const float SMOOTH_FACTOR = 0.07;
```

and/or reduce browser smoothing to:

```javascript
const CONTROL_SMOOTHING = 0.12;
```

## Servo shakes while your hand is still

Possible causes:

- weak or noisy servo power supply
- missing common ground
- poor lighting
- hand too far from camera
- servo under mechanical stress

Improve lighting and power stability first.

## Arduino resets when servo moves

This usually means the servos are drawing too much current.

Use an external regulated 5 V supply for the servos and connect its GND to Arduino GND.
