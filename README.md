# --- SPIRAL: A Ritual for Diasporic Grief and Radical Hope ---

# Setup Gemini AI
# Make sure your API Key is set in your system environment variables
genai.configure(api_key=os.getenv("GEMINI_API_KEY"))
model = genai.GenerativeModel('gemini-1.5-flash')

# Hardware Connection (Arduino)
# Change 'COM3' to your specific port (e.g., '/dev/tty.usbmodem...' on Mac)
try:
    arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1)
    print("SPIRAL Hardware: Connected.")
except:
    print("SPIRAL Hardware: Not found. Running in Simulation Mode.")
    arduino = None

def run_spiral_ritual():
    cap = cv2.VideoCapture(0) # Open the system camera
    print("SPIRAL is in a rest state. Press 'S' to begin a ritual.")

    while True:
        ret, frame = cap.read()
        if not ret: break
        
        cv2.imshow("SPIRAL Eye", frame)
        
        key = cv2.waitKey(1)
        if key == ord('s'): 
            print("Initiating Knowledge Translation...")
            
            # 1. Trigger 'Breathing' and 'Heartbeat' on Arduino
            if arduino: 
                arduino.write(b'B') 
            
            # 2. Capture the offering for the Descendants
            img_path = "offering.jpg"
            cv2.imwrite(img_path, frame)
            
            # 3. Generate the 3333 Transmission via Gemini
            print("Accessing the year 3333...")
            transmission = get_3333_transmission(img_path)
            
            print(f"\n[3333 TRANSMISSION]:\n{transmission}\n")
            
            # 4. Return to Rest
            if arduino: 
                arduino.write(b'I')
            print("Ritual complete. SPIRAL returns to rest.")
            
        elif key == ord('q'): # Press 'Q' to exit the program
            break

    cap.release()
    cv2.destroyAllWindows()

def get_3333_transmission(image_path):
    # Upload image to Google's servers
    sample_file = genai.upload_file(path=image_path)
    
    # AI Prompt reflects your B21 research and the SPIRAL theme
    prompt = (
        "You are a descendant from the year 3333. An ancestor has offered this object "
        "as part of a ritual of diasporic grief and radical hope. "
        "Describe the cultural translation of this object in your time. "
        "How has this object helped bridge the gap between generations? "
        "Be poetic, hopeful, and concise (max 60 words)."
    )
    
    response = model.generate_content([sample_file, prompt])
    return response.text

if __name__ == "__main__":
    run_spiral_ritual()
