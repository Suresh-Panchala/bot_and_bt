const int currentPin = A0;
int sensitivity = 100;// w.r.t 185 or 66
int adcValue = 0;
int adc = 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;
 
void setup() 
{
  Serial.begin(9600);
  delay(1000);
}
 
void loop()
{
  for(int i = 0; i<10; i++){
    adc = analogRead(currentPin);
    adcValue = adcValue + adc;
  }
  adcValue =  adcValue/9;
  adcVoltage = (adcValue / 1024.0) * 5200;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  currentValue = currentValue/1000;
  adcVoltage = (adcVoltage - 1300)/1000; 
  Serial.print("Raw Sensor Value = " );
  Serial.print(adcValue);
  Serial.print("\t Voltage(mV) = ");
  Serial.print(adcVoltage,3);
  Serial.print("\t Current = ");
  Serial.println(currentValue,3);
  delay(300);
}
