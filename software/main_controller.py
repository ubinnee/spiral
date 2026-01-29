import cv2
import serial
import time
import os
import google.generativeai as genai
import mido # Library to listen to MIDI from TouchMe

# --- SPIRAL: A Ritual for Diasporic Grief and Radical Hope ---

# Setup Gemini AI
genai.configure(api_key=os.getenv("GEMINI_API_KEY"))
model = genai.GenerativeModel('gemini-1.5-flash')

# Hardware Connection
try:
    arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1)
    print("SPIRAL Hardware: Connected.")
except:
    print("Hardware not found. Running Simulation.")
    arduino = None

# MIDI / TouchMe Setup
# The TouchMe usually shows up as a MIDI input device
try:
    inport = mido.open_input('TouchMe') 
    print("TouchMe Bio-Sensor: Connected.")
except:
    print("TouchMe not found. Touch sensing disabled.")
    inport = None

def run_spiral_ritual():
    cap = cv2.VideoCapture(0)
    print("SPIRAL is resting. Touch the water or press 'S' to begin.")

    while True:
        ret, frame = cap.read()
        cv2.imshow("SPIRAL Eye", frame)
        
        # Check for MIDI touch input
        if inport:
            for msg in inport.iter_pending():
                if msg.type == 'note_on':
                    print(f"Touch Detected! Intensity: {msg.velocity}")
                    # Tell Arduino to 'Breathe' faster/harder based on touch
                    if arduino: arduino.write(b'B') 

        key = cv2.waitKey(1)
        if key == ord('s'): 
            process_transmission(frame)
        elif key == ord('q'):
            break

def process_transmission(frame):
    print("Initiating Knowledge Translation...")
    img_path = "offering.jpg"
    cv2.imwrite(img_path, frame)
    
    transmission = get_3333_transmission(img_path)
    print(f"\n[3333 TRANSMISSION]:\n{transmission}\n")
    
    if arduino: arduino.write(b'I')

def get_3333_transmission(image_path):
    sample_file = genai.upload_file(path=image_path)
    prompt = (
        "You are a descendant from the year 3333. An ancestor has touched the ritual "
        "water of the SPIRAL. Describe the sensation of this connection across time. "
        "Be poetic, hopeful, and concise (max 50 words)."
    )
    response = model.generate_content([sample_file, prompt])
    return response.text

if __name__ == "__main__":
    run_spiral_ritual()
