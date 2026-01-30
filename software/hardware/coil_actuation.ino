#include <Servo.h>

/* 🌀 SPIRAL: A Ritual for Diasporic Grief and Radical Hope
 * Hardware Control: The Body (Actuation, Haptics, and Thermal)
 * Commands: 
 * 'H' - Embrace: Heat on + Constant Purr
 * 'W' - Wake-up: Sharp double-pulse to signal Mic is active
 * 'B' - Ritual: Biomorphic breathing cycles with heartbeat thumps
 * 'I' - Idle: All systems off / Resting position
 */

// --- PIN DEFINITIONS ---
const int vibrationPin = 3;  // Haptic Feedback
const int servoPin = 9;      // Breathing Mechanism
const int heaterPin = 5;     // Thermal Element
Servo lungServo;             

// --- STATE VARIABLES ---
char command;                
int restingPos = 90;         // Neutral state
int maxExpansion = 160;      // Full inhale

void setup() {
  Serial.begin(9600);        
  lungServo.attach(servoPin); 
  pinMode(vibrationPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
  
  // Initial state: Silent and Cold
  lungServo.write(restingPos);
  digitalWrite(vibrationPin, LOW);
  digitalWrite(heaterPin, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();

    if (command == 'H') {
      // THE EMBRACE: Start heating and low-level purring
      digitalWrite(heaterPin, HIGH);
      digitalWrite(vibrationPin, HIGH); // Constant hum
    } 
    
    else if (command == 'W') {
      // THE WAKE-UP: Sharp signal that AI is now listening
      wakeUpSignal();
      // Keep vibration on after signal to indicate "Listening" state
      digitalWrite(vibrationPin, HIGH); 
    }

    else if (command == 'B') {
      // THE RITUAL: Movement and breathing
      digitalWrite(heaterPin, LOW); // Cool down during movement
      runActiveRitual();
    } 

    else if (command == 'I') {
      // IDLE: Reset all
      digitalWrite(vibrationPin, LOW);
      digitalWrite(heaterPin, LOW);
      lungServo.write(restingPos);
    }
  }
}

// --- HAPTIC SIGNATURES ---

void wakeUpSignal() {
  // A crisp, mechanical double-tap
  for(int i = 0; i < 2; i++) {
    digitalWrite(vibrationPin, HIGH);
    delay(150);
    digitalWrite(vibrationPin, LOW);
    delay(100);
  }
}

void heartbeatThump() {
  // The biomorphic "Lub-Dub"
  digitalWrite(vibrationPin, HIGH);
  delay(80);
  digitalWrite(vibrationPin, LOW);
  delay(120);
  digitalWrite(vibrationPin, HIGH);
  delay(80);
  digitalWrite(vibrationPin, LOW);
}

// --- KINETIC LOGIC ---

void runActiveRitual() {
  // Executes 3 complete breathing cycles
  for (int cycle = 0; cycle < 3; cycle++) {
    
    // INHALE
    for (int pos = restingPos; pos <= maxExpansion; pos += 1) {
      lungServo.write(pos);
      if (pos == 130) heartbeatThump(); // Pulse at the peak
      delay(40); 
    }

    // EXHALE
    for (int pos = maxExpansion; pos >= restingPos; pos -= 1) {
      lungServo.write(pos);
      delay(50); 
    }
    
    delay(600); // Pause for breath
  }
}
