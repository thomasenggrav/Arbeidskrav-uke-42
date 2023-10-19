int intervalLong = 1000;	//Blinke intervaller
int intervalShort = 166;  

const int ledPin = 13;  //Deklaerer LedPin
int sensorPin = A0;		//Setter inputPin til A0

const int numMalinger = 5;		//Vil ha gjennomsnitt av 5 målinger
int malinger[numMalinger];		//Lager array til målinger
int readIndex = 0;			
int total = 0;					//Totalen til målingene
int average = 0;				//Gjennomsnittet til målingene

unsigned long previousMillis = 0;	//Forrige millis

int blinkState = LOW;  //Holde styr på led state


void setup()
{
  pinMode(ledPin, OUTPUT);  //Pin mode
  Serial.begin(9600);       // Starter serial kommuniskasjon
  for (int thisReading = 0; thisReading < numMalinger; thisReading++) {		//Initialiserer alle målinger til 0
    malinger[thisReading] = 0;
  }
}

void loop()
{
  smoothing();				// Kall på smoothing
  blinkeFart();       // Kall på blinkeFart
}

void smoothing() {
  total = total - malinger[readIndex];			//Trekk ifra siste verdi
  malinger[readIndex] = analogRead(sensorPin);	//Les fra sensor
  total = total + malinger[readIndex];			//Legg til verdi til totalen
  readIndex = readIndex + 1;					//Gå videre til neste posisjon i array

  if (readIndex >= numMalinger) {				//På slutten av array går vi tilbake til starten
    readIndex = 0;
  }

  average = total / numMalinger;				//Regn ut gj.snitt
  Serial.println(average);						//Print til Serial
  delay(1);	
}

void blinky(unsigned long currentMillis, int interval) {
  if (currentMillis - previousMillis >= interval) {			//Sjekker om nok tid har passert
    previousMillis = currentMillis;							//Oppdaterer previousMillis
    if (blinkState == LOW) {								//Endrer på BlinkState, basert på tidligere state
      digitalWrite(ledPin, HIGH);
      blinkState = HIGH;
    } else {
      digitalWrite(ledPin, LOW);
      blinkState = LOW;
    }
  }
}

void blinkeFart(){
  unsigned long currentMillis = millis();
   if (average >= 100) {
    blinky(currentMillis, intervalLong);	//Kaller på blinky funksjonen og bruker den med intervalLong som er satt til 1000
  } 										//hvis average er større enn eller lik 100
  else {
    blinky(currentMillis, intervalShort); 	//Kaller på blinky og bruker den med intervalShort som er satt til 166
  }											//hvis average er mindre enn 100
}
