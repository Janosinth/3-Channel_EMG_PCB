# 3-Channel_EMG_PCB
A forearm-focused EMG sensor with 3 channels. Useful for identifying finger or general forearm muscle movements.

![Working EMG PCB Demonstration](Video%20and%20Image%20Assets/Demo%20Video.gif)

# Photos 
3D Render of PCB
![Working EMG PCB Demonstration](Video%20and%20Image%20Assets/3D%20Render.png)

# System Architecture

The design bridges a high-gain, low-noise analog front-end with real-time embedded C++ digital signal processing.

# 1. Analog Front-End (Hardware)
Bio-Amplification: An INA630 instrumentation amplifier interfaces directly with surface electrodes to capture raw muscle action potentials.

Bandpass Filter: Using a TLV9354 operational amplifier, the circuit drives 3 (1 per channel) active bandpass filters with a bandpass of 20 - 500Hz. The bandpass is a combination of a 2nd-order high-pass filter and a first-order low-pass filter. 

Active Precision Rectification: The TLV9354 operational amplifier also drives a full active precision wave rectifier. This mathematically eliminates the forward voltage drop typical of passive Schottky diode envelopes, ensuring extremely weak muscle signals are not lost.

Total System Gain: Fixed hardware gain of ~600x designed to pull isolated bio-signals out of the noise floor before hitting the ADC.

# 2. Digital Signal Processing (Firmware)
Microcontroller: ESP32 operating with a 12-bit ADC configured to ADC_0db (0V - 1.1V range) for maximum microvolt resolution.

Filtering: A real-time C++ Exponential Moving Average (EMA) algorithm processes the raw rectified wave.

Software Scaling: Applies a digital multiplier to map the filtered biological signal to a constrained 0-3.3V logic output for external interfacing or data logging.

# Repository structure
*   `Firmware/` — ESP32 C++ code for digital signal processing. 
    *   `ESP32_Code.ino` — Arduino IDE project folder.
*   `Hardware/` — KiCad 10.0 project files and custom footprints.
    *   `Kicad_Files` — All main KiCad files to open the project.
    *   `EMG2_Stuff.pretty/` — Project-specific dependencies (Custom footprint library (INA630, MAX660, audio jacks).
    *   `Gerbers/` — Prerendered Gerber files from KiCad files ready for use with JLCPCB manufacturing tolerances. 
*   `Simulations/` — Analog circuit verification.
    *   `EMG_Circuit_Simulation.ms14` — Multisim active filter and precision rectifier simulation files.
*   `Video and Image Assets/` — Media and visual documentation.
    *   `KiCad PCB schematic.png` — PCB schematic inside KiCad. 
    *   `Bare PCB.png` — Bare manufactured PCB with no soldered components.
    *   `Full PCB Top Down View.jpg` — Top-down view of fully assembled PCB.
    *   `3D Render.png` — 3D render of the PCB in KiCad.
    *   `Demo Video.gif` — GIF of a portion of the demo video. 

# Setup & Installation
Firmware Deployment:
1. Clone this repository.

2. Open Firmware/ESP32_Code.ino in the Arduino IDE.

3. Select the ESP32 Dev Module board and compile/upload. 

Hardware Viewing:

1. Install KiCad 9.0+.

2. Open the Hardware/EMG2.kicad_pro file using KiCad, ensuring that the EMG2_Stuff.pretty EMG2.kicad_pro file is under the Hardware file directory. 

Note: Ensure the Libraries/EMG2_Stuff.pretty footprint directory is properly linked in your KiCad Footprint Library configuration to prevent "missing footprint" errors when viewing the PCB layout.
