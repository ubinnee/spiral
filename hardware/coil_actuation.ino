#include <Servo.h>

/* SPIRAL: A Ritual for Diasporic Grief and Radical Hope
 * Hardware Control: Pulse (Vibration) & Breath (Servo)
 */

// Pins
const int vibrationPin = 3;  
const int servoPin = 9;      
Servo lungServo;             

// Variables
char command;                
int restingPos = 90;         
int maxExpansion = 160;      

void setup() {
  Serial.begin(9600);        
  lungServo.attach(servoPin); 
  pinMode(vibrationPin, OUTPUT);
  
  // Initial state: Resting
  lungServo.write(restingPos);
  digitalWrite(vibrationPin, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();

    if (command == 'B') {
      // Begin the Ritual: Breathe and Pulse
      runActiveRitual();
    } 
    else if (command == 'I') {
      // Idle: Stop vibration and return to resting position
      digitalWrite(vibrationPin, LOW);
      lungServo.write(restingPos);
    }
  }
}

void runActiveRitual() {
  // Execute 3 deep breathing cycles
  for (int cycle = 0; cycle < 3; cycle++) {
    
    // Inhale (Expand)
    for (int pos = restingPos; pos <= maxExpansion; pos += 1) {
      lungServo.write(pos);
      if (pos == 125) heartbeat(); // Pulse at mid-inhale
      delay(40); 
    }

    // Exhale (Contract)
    for (int pos = maxExpansion; pos >= restingPos; pos -= 1) {
      lungServo.write(pos);
      delay(50); 
    }
    
    delay(500); 
  }
}

void heartbeat() {
  // Double-thump haptic feedback
  digitalWrite(vibrationPin, HIGH);
  delay(80);
  digitalWrite(vibrationPin, LOW);
  delay(120);
  digitalWrite(vibrationPin, HIGH);
  delay(80);
  digitalWrite(vibrationPin, LOW);
}
