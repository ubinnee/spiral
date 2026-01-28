import cv2
import serial
import time
import os
import google.generativeai as genai

# --- SPIRAL: A Ritual for Diasporic Grief and Radical Hope ---

# Setup Gemini (Ensure your API Key is set in your environment variables)
genai.configure(api_key=os.getenv("GEMINI_API_KEY"))
model = genai.GenerativeModel('gemini-1.5-flash')

# Hardware Connection
try:
    arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1)
    print("SPIRAL Hardware Connected.")
except:
    print("Running in Simulation Mode (Hardware not found).")
    arduino = None

def run_spiral_ritual():
    cap = cv2.VideoCapture(0)
    print("SPIRAL is in rest state. Waiting for an offering...")

    while True:
        ret, frame = cap.read()
        cv2.imshow("SPIRAL Eye", frame)
        
        key = cv2.waitKey(1)
        if key == ord('s'): # Press 'S' to start the ritual
            print("Initiating Knowledge Translation...")
            
            # Trigger 'Breathing' and 'Heartbeat' on Arduino
            if arduino: arduino.write(b'B') 
            
            # Capture the offering for the Descendants
            img_path = "offering.jpg"
            cv2.imwrite(img_path, frame)
            
            # Generate the 3333 Transmission
            transmission = get_3333_transmission(img_path)
            print(f"\n[3333 TRANSMISSION]:\n{transmission}\n")
            
            # Reset to Idle
            if arduino: arduino.write(b'I')
            print("SPIRAL returns to rest.")
            
        elif key == ord('q'):
            break

def get_3333_transmission(image_path):
    # Uploading image for AI analysis
    raw_image = genai.upload_file(path=image_path)
    
    # The prompt reflects your B21 research and the theme of Radical Hope
    prompt = (
        "You are a descendant from the year 3333. An ancestor has offered this object "
        "as part of a ritual of diasporic grief and radical hope. "
        "Describe the cultural translation of this object in your time. "
        "How has this object helped bridge the gap between generations? "
        "Be poetic, hopeful, and concise (max 60 words)."
    )
    
    response = model.generate_content([raw_image, prompt])
    return response.text

if __name__ == "__main__":
    run_spiral_ritual()
---
*“Just as we learn from our ancestors, they also learn from us.”*
