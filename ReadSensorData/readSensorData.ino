#include <Wire.h>

const float voltageToNTU_Slope = -1.8;
const float voltageToNTU_Intercept = 8.5;


float calibration_value = 21.34 + 0.4;
int buffer_arr[10];

void setup() {
  Serial.begin(9600);  // Initialize Serial communication
}

void loop() {
  int temp = 0;
  int avgval = 0;

  // PH Sensor Reading
  for (int i = 0; i < 10; i++) {
    buffer_arr[i] = analogRead(A0);
    delay(30);
  }

  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }

  for (int i = 2; i < 8; i++) {
    avgval += buffer_arr[i];
  }

  float volt = (float)avgval * 5.0 / 1024 / 6;
  float ph_act = -5.70 * volt + calibration_value;

  // Turbidity Sensor Reading
  int turbidityValue = analogRead(A1);
  float voltage = turbidityValue * (5.0 / 1024.0);
  float turbidityNTU = voltage * voltageToNTU_Slope + voltageToNTU_Intercept;
  turbidityNTU = constrain(turbidityNTU, 0, 10);

  // Print sensor values to Serial
  Serial.print("pH:");
  Serial.print(ph_act);
  Serial.print(",Turbidity:");
  Serial.println(turbidityNTU);

  delay(1000);
}
