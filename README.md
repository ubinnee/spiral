# SPIRAL: A Biomimetic Haptic Altar 🌀

**Project Status:** Active Prototyping (Collaboration: B21 McGill, Artch Festival)  
**Focus:** Human-Robot Interaction (HRI), Soft Robotics, Diasporic Memory

## The Vision
SPIRAL is a kinetic art installation that functions as a "living" entity. It explores diaspora not as a static category, but as a sensory condition—a layering of sounds, rhythms, and "missing pieces" carried in the body. 

In my practice as a "baby researcher" and "baby artist," I treat academic theory as a material to be softened and shared. SPIRAL uses computer vision to "inhale" physical offerings, triggering a synchronized response of haptic feedback (heartbeat) and respiratory motion (breathing) to communicate with the year 3333.

## Technical Architecture

### 👁️ Perception (The Eye)
* **Hardware:** USB Webcam 
* **Software:** Python + OpenCV
* **Logic:** Computer vision identifies the placement of an artifact, transitioning the system from "Idle" to "Active Ritual" mode.

### 🧠 Logic (The Brain)
* **Generative AI:** Google Gemini API (Visual-to-Text)
* **Translation:** A custom Python hub translates "3333 transmissions" into speculative narratives and serial commands for the hardware.

### 🫀 Actuation (The Body)
* **Microcontroller:** Arduino Uno / ESP32
* **Haptics:** An array of vibration motors creating a rhythmic "pulse" for non-visual interaction.
* **Kinetics:** A servo-actuated "lung" mechanism for biomorphic expansion and contraction.
* **Output:** Thermal printer (ESC/POS) delivering tangible, thermal-printed transmissions.

## Engineering Goals for Robotica
As a researcher moving into hardware, my goals at Robotica are to:
1. **Refine Biomorphic Motion:** Engineer a durable, silent servo-cam system for the breathing mechanism.
2. **Haptic Accessibility:** Develop a "tactile map" on the sculpture's surface to guide visually impaired users through the ritual.
3. **Hardware Integration:** Move from a breadboard prototype to a custom-soldered internal "nervous system."

## Tech Stack
* **Code:** Python, C++ (Arduino)
* **Libraries:** `opencv-python`, `google-generativeai`, `pyserial`
* **Fabrication:** 3D Printing (FDM), Mixed Media Sculpture

---
*“Just as we learn from our ancestors, they also learn from us.”*
