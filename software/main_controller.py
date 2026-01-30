import cv2
import serial
import time
import os
import google.generativeai as genai
import mido 
import speech_recognition as sr 

# --- SPIRAL: Touch-Triggered Ritual with Haptic Confirmation ---

genai.configure(api_key=os.getenv("GEMINI_API_KEY"))
model = genai.GenerativeModel('gemini-1.5-flash')

# Hardware Connection
try:
    arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1)
except:
    arduino = None

# MIDI Setup
try:
    inport = mido.open_input('TouchMe') 
except:
    inport = None

def run_spiral_ritual():
    cap = cv2.VideoCapture(0)
    touch_start_time = None
    ritual_triggered = False

    print("SPIRAL: Resting. Hold spheres for 2 seconds to begin...")

    while True:
        ret, frame = cap.read()
        cv2.imshow("SPIRAL Eye", frame)
        
        # 1. Check for Active Touch
        is_touching = False
        if inport:
            for msg in inport.iter_pending():
                if msg.type == 'note_on' and msg.velocity > 100:
                    is_touching = True

        # 2. Timer Logic for the "Handshake"
        if is_touching:
            if touch_start_time is None:
                touch_start_time = time.time()
                # Start Heat immediately on touch
                if arduino: arduino.write(b'H') 
            
            # Check if 2 seconds have passed
            elif (time.time() - touch_start_time) >= 2.0 and not ritual_triggered:
                print("Wake-up triggered. Signaling user...")
                
                # SEND WAKE-UP VIBRATION COMMAND
                if arduino: arduino.write(b'W') 
                
                # Start Voice Recognition
                user_speech = capture_voice_ritual()
                process_ritual(frame, user_speech)
                
                # Reset states for next time
                ritual_triggered = True 
        else:
            # User let go
            touch_start_time = None
            ritual_triggered = False
            if arduino: arduino.write(b'I') # Return to Idle

        if cv2.waitKey(1) == ord('q'):
            break

def capture_voice_ritual():
    r = sr.Recognizer()
    with sr.Microphone() as source:
        r.adjust_for_ambient_noise(source)
        audio = r.listen(source, timeout=7)
    try:
        return r.recognize_google(audio)
    except:
        return "A silent offering."

# ... rest of your process_ritual and AI logic ...
