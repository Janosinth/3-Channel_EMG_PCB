# 3-Channel_EMG_PCB
A forearm focused EMG sensor with 3 channels. Useful for identifying finger or general muscle movements in the forearm. 

**System Architecture**
The design bridges a high-gain, low-noise analog front-end with real-time embedded C++ digital signal processing.

# 1. Analog Front-End (Hardware)
Bio-Amplification: An INA630 instrumentation amplifier interfaces directly with surface electrodes to capture raw muscle action potentials.

Active Precision Rectification: A TLV9354 operational amplifier drives a full active precision wave rectifier. This mathematically eliminates the forward voltage drop typical of passive Schottky diode envelopes, ensuring extremely weak muscle signals are not lost.

Total System Gain: Fixed hardware gain of ~1729x designed to pull isolated bio-signals out of the noise floor before hitting the ADC.

Form Factor: Heavily utilizes 0805 surface-mount technology (SMT) to minimize footprint and reduce parasitic trace inductance.

## 2. Digital Signal Processing (Firmware)
Microcontroller: ESP32 operating with a 12-bit ADC configured to ADC_0db (0V - 1.1V range) for maximum microvolt resolution.

Filtering: A real-time C++ Exponential Moving Average (EMA) algorithm processes the raw rectified wave at ~500 Hz.

Software Scaling: Applies a digital multiplier to map the filtered biological envelope to a constrained 0-3.3V logic output for external interfacing or data logging.
