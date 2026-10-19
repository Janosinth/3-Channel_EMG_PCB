// --- PIN DEFINITIONS ---
const int emgPin1 = 33; // Channel 1 (e.g., Finger Flexors)
const int emgPin2 = 32; // Channel 2 (e.g., Wrist Flexors / Extensors)
const int emgPin3 = 35; // Channel 3 (e.g., Bicep or third muscle group)

// --- GLOBAL SETTINGS ---
float alpha = 0.05;
float softwareGain = 66.0;

// --- STATE VARIABLES ---
float softwareEnvelope1 = 0.0;
float softwareEnvelope2 = 0.0;
float softwareEnvelope3 = 0.0;

void setup() {
  Serial.begin(115200);
  // Compresses range to 0-1.1V for maximum sensitivity
  analogSetAttenuation(ADC_0db);
}

void loop() {
  // 1. Read raw ADC values
  int rawADC1 = analogRead(emgPin1);
  int rawADC2 = analogRead(emgPin2);
  int rawADC3 = analogRead(emgPin3);
 
  // 2. Calculate physical voltages (0V to 1.1V max)
  float physicalVoltage1 = (rawADC1 / 4095.0) * 1.1;
  float physicalVoltage2 = (rawADC2 / 4095.0) * 1.1;
  float physicalVoltage3 = (rawADC3 / 4095.0) * 1.1;
 
  // 3. Generate the smooth digital envelopes directly from the raw voltages
  softwareEnvelope1 = (alpha * physicalVoltage1) + ((1.0 - alpha) * softwareEnvelope1);
  softwareEnvelope2 = (alpha * physicalVoltage2) + ((1.0 - alpha) * softwareEnvelope2);
  softwareEnvelope3 = (alpha * physicalVoltage3) + ((1.0 - alpha) * softwareEnvelope3);

  // 4. Scale and constrain the outputs
  float scaledEnvelope1 = constrain(softwareEnvelope1 * softwareGain, 0.0, 3.3);
  float scaledEnvelope2 = constrain(softwareEnvelope2 * softwareGain, 0.0, 3.3);
  float scaledEnvelope3 = constrain(softwareEnvelope3 * softwareGain, 0.0, 3.3);

  // 5. Plot all three channels
  Serial.print(scaledEnvelope1);
  Serial.print(",");
  Serial.print(scaledEnvelope2);
  Serial.print(",");
  Serial.println(scaledEnvelope3);
 
  // delay maintains the sampling rate
  delay(50);
}