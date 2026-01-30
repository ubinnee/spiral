import cv2
import serial
import time
import os
import google.generativeai as genai
import mido 
import speech_recognition as sr  # <--- NEW: For Voice Trigger

# --- SPIRAL: A Ritual for Diasporic Grief and Radical Hope ---

genai.configure(api_key=os.getenv("GEMINI_API_KEY"))
model = genai.GenerativeModel('gemini-1.5-flash')

# Hardware Connection
try:
    arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1)
    print("SPIRAL Hardware: Connected.")
except:
    arduino = None

# MIDI / TouchMe Setup
try:
    inport = mido.open_input('TouchMe') 
    print("TouchMe Bio-Sensor: Connected.")
except:
    inport = None

def listen_to_ancestor():
    """Activates the microphone to capture the user's message."""
    r = sr.Recognizer()
    with sr.Microphone() as source:
        print("SPIRAL is listening to your voice...")
        audio = r.listen(source, timeout=5, phrase_time_limit=10)
    try:
        return r.recognize_google(audio)
    except:
        return "A silent offering."

def run_spiral_ritual():
    cap = cv2.VideoCapture(0)
    print("SPIRAL is resting. Place both hands on the spheres to begin.")

    while True:
        ret, frame = cap.read()
        cv2.imshow("SPIRAL Eye", frame)
        
        # Logic for the "Half-Ball" Embrace
        # Using MIDI velocity as a proxy for 'Contact'
        if inport:
            for msg in inport.iter_pending():
                if msg.type == 'note_on' and msg.velocity > 100:
                    print("Embrace detected. Warming up...")
                    
                    # 1. Tell Arduino to start HEAT and VIBRATION
                    if arduino: arduino.write(b'H') 
                    
                    # 2. Trigger Voice Recognition
                    user_speech = listen_to_ancestor()
                    print(f"Ancestor said: {user_speech}")
                    
                    # 3. Process the visual offering + the voice message
                    process_transmission(frame, user_speech)
                    break

        if cv2.waitKey(1) == ord('q'):
            break

def process_transmission(frame, speech_text):
    img_path = "offering.jpg"
    cv2.imwrite(img_path, frame)
    
    # Send both the image and the voice text to Gemini
    transmission = get_3333_transmission(img_path, speech_text)
    print(f"\n[3333 TRANSMISSION]:\n{transmission}\n")
    
    if arduino: arduino.write(b'I') # Return to Idle

def get_3333_transmission(image_path, user_text):
    sample_file = genai.upload_file(path=image_path)
    prompt = (
        f"An ancestor has approached the SPIRAL. They have offered an object and said: '{user_text}'. "
        "As a descendant from 3333, respond to their grief and hope. "
        "Translate this moment into a poetic, 50-word transmission."
    )
    response = model.generate_content([sample_file, prompt])
    return response.text

if __name__ == "__main__":
    run_spiral_ritual()
