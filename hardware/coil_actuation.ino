#include <Servo.h>

/* SPIRAL: A Ritual for Diasporic Grief and Radical Hope
 * Hardware Control: Pulse (Vibration), Breath (Servo), and Heat (Thermal)
 */

// --- PIN DEFINITIONS ---
const int vibrationPin = 3;  
const int servoPin = 9;   
const int heaterPin = 5;     // Placeholder for your heating element relay/transistor
Servo lungServo;             

// --- STATE VARIABLES ---
char command;                
int restingPos = 90;         
int maxExpansion = 160;      

void setup() {
  Serial.begin(9600);        
  lungServo.attach(servoPin); 
  pinMode(vibrationPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
  
  // Initial state: Resting and Cold
  lungServo.write(restingPos);
  digitalWrite(vibrationPin, LOW);
  digitalWrite(heaterPin, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();

    if (command == 'B') {
      // MODE: BREATHE (The Ritual is active)
      digitalWrite(heaterPin, LOW); // Heat off for movement
      runActiveRitual();
    } 
    else if (command == 'H') {
      // MODE: HOT & HEARTBEAT (The Embrace / Voice Trigger)
      // This is triggered when both hands touch the spheres
      initiateEmbrace();
    }
    else if (command == 'I') {
      // MODE: IDLE (Reset to rest)
      digitalWrite(vibrationPin, LOW);
      digitalWrite(heaterPin, LOW);
      lungServo.write(restingPos);
    }
  }
}

// --- RITUAL LOGIC ---

void runActiveRitual() {
  // Execute 3 deep breathing cycles with haptic pulses
  for (int cycle = 0; cycle < 3; cycle++) {
    // Inhale
    for (int pos = restingPos; pos <= maxExpansion; pos += 1) {
      lungServo.write(pos);
      if (pos == 125) heartbeatPulse(); 
      delay(40); 
    }
    // Exhale
    for (int pos = maxExpansion; pos >= restingPos; pos -= 1) {
      lungServo.write(pos);
      delay(50); 
    }
    delay(500); 
  }
}

void initiateEmbrace() {
  // Constant low-level vibration (the "purr") and heating
  // This tells the user: "I am warm and I am listening"
  digitalWrite(heaterPin, HIGH);
  
  // Rapid pulsing to indicate the mic is active
  for(int i = 0; i < 5; i++) {
    digitalWrite(vibrationPin, HIGH);
    delay(100);
    digitalWrite(vibrationPin, LOW);
    delay(100);
  }
  // Keep vibration at a steady low hum (PWM) if possible, or simple HIGH
  digitalWrite(vibrationPin, HIGH);
}

void heartbeatPulse() {
  // Traditional double-thump haptic
  digitalWrite(vibrationPin, HIGH);
  delay(80);
  digitalWrite(vibrationPin, LOW);
  delay(120);
  digitalWrite(vibrationPin, HIGH);
  delay(80);
  digitalWrite(vibrationPin, LOW);
}
