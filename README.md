# 3-Channel_EMG_PCB
A forearm-focused EMG sensor with 3 channels. Useful for identifying finger or general forearm muscle movements. 

**System Architecture**
The design bridges a high-gain, low-noise analog front-end with real-time embedded C++ digital signal processing.

# 1. Analog Front-End (Hardware)
Bio-Amplification: An INA630 instrumentation amplifier interfaces directly with surface electrodes to capture raw muscle action potentials.

Active Precision Rectification: A TLV9354 operational amplifier drives a full active precision wave rectifier. This mathematically eliminates the forward voltage drop typical of passive Schottky diode envelopes, ensuring extremely weak muscle signals are not lost.

Total System Gain: Fixed hardware gain of ~1729x designed to pull isolated bio-signals out of the noise floor before hitting the ADC.

Form Factor: Heavily utilizes 0805 surface-mount technology (SMT) to minimize footprint and reduce parasitic trace inductance.

# 2. Digital Signal Processing (Firmware)
Microcontroller: ESP32 operating with a 12-bit ADC configured to ADC_0db (0V - 1.1V range) for maximum microvolt resolution.

Filtering: A real-time C++ Exponential Moving Average (EMA) algorithm processes the raw rectified wave at ~500 Hz.

Software Scaling: Applies a digital multiplier to map the filtered biological signal to a constrained 0-3.3V logic output for external interfacing or data logging.

# Repository Structure
├── Firmware/
│   └── EMG_DSP_Filter/
│       └── EMG_DSP_Filter.ino         # ESP32 EMA filtering and multi-channel serial plotting code
├── Hardware/
│   ├── Libraries/
│   │   └── EMG2_Stuff.pretty/         # Custom footprint library (INA630, MAX660, audio jacks)
│   ├── EMG_Mainboard.kicad_sch        # KiCad Schematic
│   ├── EMG_Mainboard.kicad_pcb        # KiCad PCB Layout
│   └── EMG_Mainboard.kicad_pro        # KiCad Project File
├── Simulations/
│   └── Transient_Analysis.ms14        # Multisim active filter and rectifier simulation files
└── Assets/
    ├── Schematic_Overview.pdf         # High-res export of the circuit design
    ├── PCB_Layout.png                 # Top/Bottom routing view
    └── plotter_test.gif               # Hardware demonstration media
