#include <Servo.h>

/* * COIL Altar - Hardware Control Script
 * Developed for Robotica Residency Application
 * This script manages the "Living" state of the altar via:
 * 1. A Servo motor for respiratory (breathing) motion.
 * 2. A Vibration motor for tactile (heartbeat) pulses.
 */

// --- PIN DEFINITIONS ---
const int vibrationPin = 3;  // Digital output for vibration motor
const int servoPin = 9;      // PWM output for servo
Servo lungServo;             

// --- STATE VARIABLES ---
char incomingByte;           // Stores command from Python ('B' = Begin, 'I' = Idle)
int restingPos = 90;         // Neutral position of the servo
int maxExpansion = 160;      // Fully "inhaled" position

void setup() {
  Serial.begin(9600);        // Initialize USB serial communication
  lungServo.attach(servoPin); 
  pinMode(vibrationPin, OUTPUT);
  
  // Initialization: Return to resting state
  lungServo.write(restingPos);
  digitalWrite(vibrationPin, LOW);
  
  Serial.println("Altar Hardware Ready.");
}

void loop() {
  // Check if Python sent a command
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if (incomingByte == 'B') {
      // Initiate the "Breathing" and "Pulsing" loop
      runActiveRitual();
    } 
    else if (incomingByte == 'I') {
      // Return to low-power idle state
      digitalWrite(vibrationPin, LOW);
      lungServo.write(restingPos);
    }
  }
}

// --- MOTION LOGIC ---

void runActiveRitual() {
  // Executes 3 complete "Breath" cycles
  for (int cycle = 0; cycle < 3; cycle++) {
    
    // INHALE (Expansion)
    for (int pos = restingPos; pos <= maxExpansion; pos += 1) {
      lungServo.write(pos);
      
      // Trigger a heartbeat pulse at the peak of the inhale
      if (pos == 130) {
        triggerHeartbeat();
      }
      delay(40); // Controls inhale speed
    }

    // EXHALE (Contraction)
    for (int pos = maxExpansion; pos >= restingPos; pos -= 1) {
      lungServo.write(pos);
      delay(50); // Controls exhale speed (slightly slower for natural feel)
    }
    
    delay(400); // Pause between breaths
  }
}

// --- HAPTIC LOGIC ---

void triggerHeartbeat() {
  // A double-pulse vibration ("Thump-Thump")
  digitalWrite(vibrationPin, HIGH);
  delay(80);
  digitalWrite(vibrationPin, LOW);
  delay(120);
  digitalWrite(vibrationPin, HIGH);
  delay(80);
  digitalWrite(vibrationPin, LOW);
}
