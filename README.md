# Smart Robot Car Control - README

## Overview

This project controls a simple autonomous robot car using an Arduino, motor driver, ultrasonic sensor, and servo motor. The robot can detect obstacles using the ultrasonic sensor and adjust its direction to avoid them, using the servo motor to scan its surroundings. It can move forward, backward, turn left, turn right, and stop as needed.

## Components

1. **Arduino Board (Elegoo UNO or similar)**
2. **Motor Driver (SmartCar-Shield-V1.1)**
3. **DC Motors (for left and right wheels)**
4. **Ultrasonic Sensor (HC-SR04)**
5. **Servo Motor (for controlling the ultrasonic sensor)**
6. **Power supply**
7. **Chassis for the robot (including wheels and motor mount)**

## Pin Configuration

- **Motor Control Pins**:
  - `PWMA (Pin 5)`: Speed control for the right motor
  - `PWMB (Pin 6)`: Speed control for the left motor
  - `R_IN_1 (Pin 7)`: Direction control for the right motor
  - `L_IN_1 (Pin 8)`: Direction control for the left motor
  - `STBY (Pin 3)`: Standby pin for the motor driver

- **Ultrasonic Sensor**:
  - `TRIG_PIN (Pin 13)`: Triggers ultrasonic pulse
  - `ECHO_PIN (Pin 12)`: Receives the reflected pulse

- **Servo Motor**:
  - `SERVO_PIN (Pin 10)`: Controls the servo motor

## Functionality

### Motor Control
- `motorInit()`: Initializes the motor control pins.
- Functions to move the car:
  - `forward(speed)`: Moves the car forward at the specified speed.
  - `back(speed)`: Moves the car backward.
  - `left(speed)`: Turns the car to the left.
  - `right(speed)`: Turns the car to the right.
  - `stop()`: Stops the car.

### Ultrasonic Sensor
- `sensorInit()`: Initializes the ultrasonic sensor pins.
- `measureDistance()`: Sends out an ultrasonic pulse and measures the distance to an object by calculating the time taken for the echo to return.

### Servo Control & Obstacle Avoidance
- `servoCtrl()`: Rotates the servo motor to scan left and right for obstacles. The car turns toward the direction with the greater distance to avoid obstacles when one is detected ahead.

### Speed Calculation
- `percent(speed)`: Converts a percentage-based speed input into the appropriate motor control value for the `analogWrite` function.

### Debugging/Test Function
- `direction_test()`: Tests the car's ability to move in all directions (forward, backward, left, right) and stop.

## Usage

1. **Setup**:
   - Upload the provided code ('obstacle_avoid.ino') to the Arduino.
   - Connect the motors, sensors, and servo according to the pin configuration mentioned above.
   - Ensure the motor driver is powered and the robot chassis is assembled.

2. **Running**:
   - The car will automatically test its directional movements on startup (`direction_test()`).
   - In the `loop()`, the robot continuously uses the ultrasonic sensor to detect obstacles and adjust its direction accordingly using the servo motor.

3. **Obstacle Avoidance**:
   - If the ultrasonic sensor detects an obstacle within 50 cm, the servo will rotate to measure distances to the left and right.
   - The car will turn in the direction with more space.

4. **Serial Monitor**:
   - Use the Arduino IDE's Serial Monitor to observe the robot's status and debug the movement commands. The car's speed, movement direction, and obstacle distances are printed for reference.
   - Note: The serial monitor will not display anything when disconnected from the laptop.
## Customization

- You can adjust the speed of the car by passing different values to the `forward()`, `back()`, `left()`, and `right()` functions (e.g., `forward(30)` for 30% speed).
- The obstacle detection range can be modified by changing the condition in `servoCtrl()` (currently set at 50 cm).

---
