#include <Servo.h>
// Define pins for motor control
#define PWMA 5    //Right motor on/off
#define PWMB 6    //Left motor on/off
#define L_IN_1 8  //Left motor direction
#define R_IN_1 7  //Right motor direction
#define STBY 3    //Standby pin

//Define pins for ultrasonic sensor
#define TRIG_PIN 13
#define ECHO_PIN 12

//Define pin for servo motor
#define SERVO_PIN 10

Servo sensorServo;

// Function to initialize motor pins
void motorInit() {
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(R_IN_1, OUTPUT);
  pinMode(L_IN_1, OUTPUT);
  pinMode(STBY, OUTPUT);
}

// Function to initialize ultrasonic sensor pins
void sensorInit() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

// Function to measure distance 
long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

// Converts speed value from a percentage to the actual value
int percent(float speed) {
  if (speed == 0) {
    stop();
  } else {
      int speed_val = ((speed/100)*220)+30; // Adds 30 as speeds below 30 are not enough to allow the car to move
      Serial.print("speed_val: ");
      Serial.println(speed_val);
      return speed_val;
    }
}

// Moves car forward
void forward(float speed) {
  int actSpeed = percent(speed);
  digitalWrite(R_IN_1, HIGH);
  analogWrite(PWMA, actSpeed);
  digitalWrite(L_IN_1, HIGH);
  analogWrite(PWMB, actSpeed);
  Serial.print("Forward:-  ");
  Serial.print("speed: ");
  Serial.println(actSpeed);
}

// Moves car bakward
void back(float speed) {
  int actSpeed = percent(speed);
  digitalWrite(R_IN_1, LOW);
  analogWrite(PWMA, actSpeed);
  digitalWrite(L_IN_1, LOW);
  analogWrite(PWMB, actSpeed);
  Serial.print("Back:-  ");
  Serial.print("speed: ");
  Serial.println(actSpeed);
}

// Turns car to the right
void right(float speed) {
  int actSpeed = percent(speed);
  digitalWrite(R_IN_1, LOW);
  analogWrite(PWMA, actSpeed);
  digitalWrite(L_IN_1, HIGH);
  analogWrite(PWMB, actSpeed);
  Serial.print("Right:-  ");
  Serial.print("speed: ");
  Serial.println(actSpeed);
}

// Turns car to the left
void left(float speed) {
  int actSpeed = percent(speed);
  digitalWrite(R_IN_1, HIGH);
  analogWrite(PWMA, actSpeed);
  digitalWrite(L_IN_1, LOW);
  analogWrite(PWMB, actSpeed);
  Serial.print("Left:-  ");
  Serial.print("speed: ");
  Serial.println(actSpeed);
}

// Stops the car
void stop() {
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  Serial.println("Stop");
}

// Servo turns the ultrasonic sensor to the left and to the right, measures the distance on either side and turns
// the car in the direction with greater distance from the sensor
void servoCtrl() {
  sensorServo.write(90);
  delay(500);
  long distanceCenter = measureDistance();
  delay(500);
  if (distanceCenter < 50) {
    stop();
    //Rotate servo to left, right, center
    sensorServo.write(30);  //Left
    delay(500);
    long distanceLeft = measureDistance();
    delay(500);

    sensorServo.write(150); //Right
    delay(500);
    long distanceRight = measureDistance();
    delay(500);

    sensorServo.write(90);  //Center
    delay(500);

    if (distanceLeft < distanceRight) {
      left(10);
      delay(30);
    } else {
      right(10);
      delay(30);
    }
  } else {
    forward(20);
  }
  delay(500);
}

// Test function to ensure the directions are working properly
void direction_test() {
  forward(20);
  delay(1000);

  back(20);
  delay(1000);

  left(20);
  delay(1000);

  right(20);
  delay(1000);

  stop();
}

void setup() {
  Serial.begin(9600);
  motorInit();
  sensorInit();
  sensorServo.attach(SERVO_PIN);
  digitalWrite(STBY, HIGH); //Enable motor driver
  direction_test();
}

void loop() {
  Serial.println("START");
  servoCtrl();
}
