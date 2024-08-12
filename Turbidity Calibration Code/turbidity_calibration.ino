#include <Wire.h> 

int Turbidity_Sensor_Pin = A1;
float Turbidity_Sensor_Voltage;
int samples = 600;
float ntu; // Nephelometric Turbidity Units
 
void setup()
{
  Serial.begin(9600); // for debugging purposes
  pinMode(Turbidity_Sensor_Pin, INPUT);
}
 
void loop()
{
    Turbidity_Sensor_Voltage = 0;
    // Take 600 samples and compute the average value
    for(int i = 0; i < samples; i++)
    {
        Turbidity_Sensor_Voltage += ((float)analogRead(Turbidity_Sensor_Pin) / 1023) * 5;
    }
    
    Turbidity_Sensor_Voltage = Turbidity_Sensor_Voltage / samples;

    
    Serial.print("Voltage: ");
    Serial.println(Turbidity_Sensor_Voltage);
    
    Turbidity_Sensor_Voltage = round_to_dp(Turbidity_Sensor_Voltage, 2);
    
    if(Turbidity_Sensor_Voltage < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4 * square(Turbidity_Sensor_Voltage) + 5742.3 * Turbidity_Sensor_Voltage - 4352.9; 
    }
    
    Serial.print("NTU: ");
    Serial.println(ntu);
    
    delay(1000); // Adjust the delay as needed
}
 
float round_to_dp(float in_value, int decimal_place)
{
  float multiplier = powf(10.0f, decimal_place);
  in_value = roundf(in_value * multiplier) / multiplier;
  return in_value;
}
