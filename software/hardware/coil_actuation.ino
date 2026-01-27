#include <Servo.h>

// --- HARDWARE PIN SETUP ---
const int vibrationPin = 3;  // Connect your vibration motor module to Digital Pin 3
const int servoPin = 9;      // Connect your Servo signal wire to Digital Pin 9
Servo lungServo;             // Create a servo object to control the 'breathing'

// --- VARIABLES ---
char command;                // Stores the instruction sent from your Python script
int servoPos = 90;           // Starting position (neutral)

void setup() {
  Serial.begin(9600);        // Open serial communication at 9600 baud
  lungServo.attach(servoPin); 
  pinMode(vibrationPin, OUTPUT);
  
  // Set the altar to a "resting" position on startup
  lungServo.write(90);
  digitalWrite(vibrationPin, LOW);
  
  Serial.println("COIL Altar Hardware Initialized.");
}

void loop() {
  // Check if Python has sent a command over the USB cable
  if (Serial.available() > 0) {
    command = Serial.read();

    if (command == 'B') {
      // 'B' for Begin Ritual: Start the living cycle
      runLivingCycle();
    } 
    else if (command == 'I') {
      // 'I' for Idle: Return to a quiet, resting state
      goToRest();
    }
  }
}

// --- RITUAL BEHAVIOR ---
void runLivingCycle() {
  // This simulates 3 deep, rhythmic breaths
  for (int breath = 0; breath < 3; breath++) {
    
    // 1. INHALE: The servo moves slowly to expand the structure
    for (int pos = 90; pos <= 160; pos += 1) {
      lungServo.write(pos);
      
      // Add a heartbeat pulse halfway through the inhale
      if (pos == 125) {
        heartbeat();
      }
      delay(35); // Controls the "speed" of the breath
    }

    // 2. EXHALE: The servo moves back to contract the structure
    for (int pos = 160; pos >= 90; pos -= 1) {
      lungServo.write(pos);
      delay(45); // Exhaling is usually slightly slower/longer
    }
    
    delay(500); // Brief pause between breaths
  }
}

// --- SENSORY FUNCTIONS ---
void heartbeat() {
  // A quick "thump-thump" vibration pattern
  digitalWrite(vibrationPin, HIGH);
  delay(80);
  digitalWrite(vibrationPin, LOW);
  delay(100);
  digitalWrite(vibrationPin, HIGH);
  delay(80);
  digitalWrite(vibrationPin, LOW);
}

void goToRest() {
  digitalWrite(vibrationPin, LOW);
  lungServo.write(90); // Return to neutral "flat" position
}
