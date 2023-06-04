#include <Servo.h>

const int analogPin = A0;           // Analog input pin
const int numSamples = 181;        // Number of samples (0-180 degrees)
int samples[numSamples];           // Array to store samples
const int threshold = 500;         // Threshold value for peak detection

Servo servoMotor;                  // Servo motor object
int maxPeakAngle = 0;               // Angle with maximum peak point value

void setup() {
  Serial.begin(9600);              // Initialize serial communication
  pinMode(analogPin, INPUT);       // Set analog pin as input
  servoMotor.attach(9);            // Attach servo to pin 9
  servoMotor.write(0);             // Set initial position of servo
}

void loop() {
  for (int angle = 0; angle <= 180; angle++) {
    int sensorValue = analogRead(analogPin); // Read analog input
    samples[angle] = sensorValue;             // Store value in array
    delay(10);                               // Delay for stability

    // Print angle and corresponding sensor value
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" degrees, Sensor value: ");
    Serial.println(sensorValue);
  }

  // Print the stored array values
  for (int i = 0; i < numSamples; i++) {
    Serial.print("Sample ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(samples[i]);

    // Find angle with maximum peak point value
    if (samples[i] > samples[maxPeakAngle]) {
      maxPeakAngle = i;
    }
  }

  // Drive servo motor to the angle with maximum peak point value
  int servoAngle = map(maxPeakAngle, 0, 180, 0, 180);
  servoMotor.write(servoAngle);
  delay(1000);

  while (1) continue;  // Stop execution after printing samples and driving the servo motor
}
