//This My MultiButtone Code
//All Buttone Connect with Serial connectio
//

int analogPin = A1;         
int val = 0;
void setup() {
  Serial.begin(9600);          
}

void loop() {
  val = analogRead(analogPin);  
  //Serial.println(val);   
  //delay(1000); 
   if (val>=500 && val<=520){
     Serial.println("Press Buttone_1");
   }else if (val>=650 && val<=700){
     Serial.println("Press Buttone_2");
   }else if (val>=740 && val<=770){
     Serial.println("Press Buttone_3");
   }else if (val>=790 && val<=805){
     Serial.println("Press Buttone_4");
   }else if (val>=820 && val<=890){
     Serial.println("Press Buttone_5");
   }
      
}
