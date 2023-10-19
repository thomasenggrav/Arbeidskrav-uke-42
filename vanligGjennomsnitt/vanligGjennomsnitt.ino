int ledPin = 13;    // Pin for led
int sensorPin = A0;   //Pin for sensor
int sensorValue = 0;  // Variabel for sensorValue
int interval = 100;   // Variabel for interval
unsigned long previousMillis = 0;	//Forrige millis
int blinkState = LOW;  //Holde styr på led state


void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT); //sensor input
  pinMode(ledPin, OUTPUT); //led input
}
void loop() {
    sensorReading();    // Kall på sensorReading
  	blink();            // Kall på blink
}


void sensorReading(){           
  for (int i=0; i < 5; i++) {                               //Tar inn data fra sensorPin og regner gjennomsnittet.
  sensorValue = sensorValue + analogRead(sensorPin);
 }
  sensorValue = sensorValue/5;                              // Finner gjennomsnittet
  Serial.println(sensorValue);                              //Printer gjennomsnittet
}

void blink(){
    unsigned long currentMillis = millis();
    int intervalLong = 1000;	//Blinke intervaller
    int intervalShort = 166;  
    if (currentMillis - previousMillis >= intervalLong && sensorValue >= 100) {			//Sjekker om nok tid har passert og sensorReading
        previousMillis = currentMillis;	                                                //Blinker i intervalLong intervallet
        if (blinkState == LOW) {								//Endrer på BlinkState, basert på tidligere state
        digitalWrite(ledPin, HIGH);
        blinkState = HIGH;
        } 
    else {
      digitalWrite(ledPin, LOW);
      blinkState = LOW;
    }
    }
    if(currentMillis - previousMillis >= intervalShort && sensorValue < 100){         //Sjekker om nok tid har passert og sensorReading
        previousMillis = currentMillis;                                     //Blinker i intervalShort intervallet
        if (blinkState == LOW) {								//Endrer på BlinkState, basert på tidligere state
        digitalWrite(ledPin, HIGH);
        blinkState = HIGH;
        } 
    else {
      digitalWrite(ledPin, LOW);
      blinkState = LOW;
    }
    }
}
