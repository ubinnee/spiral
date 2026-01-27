# COIL: A Biomimetic Haptic Interface

**Project Status:** Active Development / Prototyping
**Focus:** Soft Robotics, Haptics, Computer Vision, Human-Robot Interaction (HRI)

## Project Overview
COIL is a kinetic art installation that functions as a "living" altar. It explores the intersection of diasporic memory and affective computing. The system utilizes computer vision to detect physical offerings, triggering a synchronized response of haptic feedback (vibration) and respiratory motion (soft robotics expansion/contraction).

## System Architecture

### 1. Perception (The Eye)
* **Hardware:** USB Webcam (Top-down view)
* **Software:** Python + OpenCV
* **Logic:** Object detection triggers the state change from "Idle" to "Active."

### 2. Logic (The Brain)
* **Generative AI:** Google Gemini API analyzes the visual input to generate a speculative narrative ("The 3333 Transmission").
* **Controller:** Python script acts as the central hub, sending serial data to the microcontroller.

### 3. Actuation (The Body)
* **Microcontroller:** Arduino Uno / ESP32
* **Haptics:** Vibration motors providing a "heartbeat" feedback loop.
* **Kinetics:** Servo-driven mechanism simulating biological breathing (expansion/contraction).
* **Output:** Thermal Printer (ESC/POS protocol) providing a physical artifact.

## Roadmap for Robotica Residency
* [ ] Design and 3D print the internal brackets for the servo mechanism.
* [ ] Solder and test the vibration motor array.
* [ ] Write the Python-to-Arduino serial communication script.
* [ ] Integrate the thermal printer with the "Oracle" AI script.

## Tech Stack
* **Languages:** Python, C++ (Arduino)
* **Libraries:** `opencv-python`, `google-generativeai`, `pyserial`
* **Hardware:** Arduino, Prusa/Bambu 3D Printers, Vibration Motors
