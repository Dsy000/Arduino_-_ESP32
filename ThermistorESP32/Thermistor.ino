#
# Created by DY

#define thermiPin 15 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  int adcValue = analogRead(thermiPin);
  double voltage = (float)adcValue / 4095.0 * 3.3;
  double Rt = 10 * voltage / (3.3 - voltage);
  double tempK = 1 / (1 / (273.15 + 25) + log(Rt / 10) / 3950.0);
  double tempC = tempK - 273.15;

  Serial.printf("ADC value : %d,\tVoltage : %.2fV, \tTemptature : %.2fC \n", adcValue, voltage, tempC);
  delay(1000);
}
