#define trigPin 12
#define echoPin 13
#define Dist_LED 7
#define Dist_LED2 8
boolean Dist_LEDSwitchON;
boolean LDR_LEDSwitchON;
boolean SendToSerial;
boolean SendToSerial_LDR;
   
int lightPin = 0;  //define a pin for Photo resistor
int LDR_ledPin=5;     //define a pin for LED
int LDR_ledPin1=6;     //define a pin for LED

void setup() {
  Serial.begin(9600);  //Begin serial communcation
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Dist_LED, OUTPUT);
  pinMode(Dist_LED2, OUTPUT);

   
  pinMode( LDR_ledPin, OUTPUT );
  pinMode( LDR_ledPin1, OUTPUT );
  
}

void loop() {

    // Entire Code Below for Distance Measurement and Send to Serial Port - START
    long duration, distance;  
    
    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    if (distance < 10) {  // This is where the Dist_LED On/Off happens    
      if(Dist_LEDSwitchON == HIGH ){ SendToSerial = false;} else {SendToSerial = true;}
      Dist_LEDSwitchON = HIGH; 
      setDist_LED(Dist_LED,Dist_LED2,Dist_LEDSwitchON); 
      
      if(SendToSerial ==true) { Serial.println("DST:"+String(distance));}     
    }
    else {
      if(Dist_LEDSwitchON == LOW ){ SendToSerial = false;} else {SendToSerial = true;}
      Dist_LEDSwitchON = LOW;
      setDist_LED(Dist_LED,Dist_LED2,Dist_LEDSwitchON);    
      
      if(SendToSerial ==true) { Serial.println("DST:"+String(distance));}
      }     
    
    delay(500); // Might have to remove depending on the performance
    // Entire Code Below for Distance Measurement and Send to Serial Port - END
    //------------------------------------------------------------------------------------------
    // Below Code for LDR Read and Send to Serial - START
    int val;
    int percent;
    val = analogRead(analogRead(lightPin));
    //Serial.println('VAL= '+val); //Write the value of the photoresistor to the serial monitor.
    percent = map(val,0,1023,0,100);
    
    //Serial.println(percent);
    if (percent <80){
      if(LDR_LEDSwitchON == true ){ SendToSerial_LDR = false;} else {SendToSerial_LDR = true;}
      LDR_LEDSwitchON = true;
      digitalWrite(LDR_ledPin, HIGH);
      digitalWrite(LDR_ledPin1, HIGH);
      if(SendToSerial_LDR ==true) { Serial.println("LDR:"+String(percent));}
    }
    else{
      if(LDR_LEDSwitchON == false ){ SendToSerial_LDR = false;} else {SendToSerial_LDR = true;}
      LDR_LEDSwitchON = false;
      digitalWrite(LDR_ledPin, LOW);
      digitalWrite(LDR_ledPin1, LOW);
      if(SendToSerial_LDR ==true) { Serial.println("LDR:"+String(percent));}
    }
    // Below Code for LDR Read and Send to Serial - End
}
void setDist_LED(int Dist_LEDx,int Dist_LEDy,bool v)
  {
    digitalWrite(Dist_LEDx, v); 
    digitalWrite(Dist_LEDy, !v); 
  }
 

