const int buzzerPin = 9;  // pinul pentru buzzer
bool buzzerActive = false;  // starea buzzer-ului
unsigned long buzzerStartTime = 0; // timpul de pornire al buzzer-ului
unsigned long buzzerDuration = 1000; // durata pentru care trebuie să sune buzzer-ul
 
unsigned long stopTime = 0; // timpul de oprire pentru etajul curent
 
const int ledPin = 13;  // pinul LED-ului
int ledState = LOW; 
unsigned long previousMillis = 0; // ultima stare a ledului
const long interval = 1000; // intervalul la care palpaie LED-ul
 
unsigned long currentMillis = 0; // timpul curent
 
const int buttonPin0 = 2; 
const int buttonPin1 = 3;
const int buttonPin2 = 4;
 
const int ledPin0 = 10; 
const int ledPin1 = 11; 
const int ledPin2 = 12; 
 
byte buttonState0 = LOW;
byte buttonState1 = LOW;
byte buttonState2 = LOW;
 
byte ledState0 = HIGH;
byte ledState1 = HIGH;
byte ledState2 = HIGH;
 
//counter pt apasari
int buttonPushCounter0 = 0;
int buttonPushCounter1 = 0;
int buttonPushCounter2 = 0;
 
byte reading0 = LOW;
byte reading1 = LOW;
byte reading2 = LOW;
 
byte lastReading0 = LOW;
byte lastReading1 = LOW;
byte lastReading2 = LOW;
 
unsigned int lastDebounceTime0 = 0;
unsigned int lastDebounceTime1 = 0;
unsigned int lastDebounceTime2 = 0;
 
int targetFloor = -1;  // etajul la care vrem sa ajungem
int currentFloor = 0;  //  etajul la care suntem
 
unsigned int debounceDelay = 50;


byte startClosingDoors=0;
unsigned long initialMillis;
const int blinkDuration=500; //pt palpaitul ledului
// folosim un counter pt a adapta currentFloor: 5(de la un et la altul), 10(0->2 sau 2->0) 
int counter=0;
 
void setup() { 
  pinMode(buttonPin0, INPUT_PULLUP); 
  pinMode(buttonPin1, INPUT_PULLUP); 
  pinMode(buttonPin2, INPUT_PULLUP); 
 
  pinMode(ledPin0, OUTPUT); 
  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT); 
 
  Serial.begin(9600); 
 
  pinMode(buzzerPin, OUTPUT);
 
  pinMode(ledPin, OUTPUT);
} 
 
void loop() { 
  reading0 = digitalRead(buttonPin0);
  reading1 = digitalRead(buttonPin1);
  reading2 = digitalRead(buttonPin2);

 //debounce
  if (reading0 != lastReading0) {
    lastDebounceTime0 = millis();
  }
 
  if (reading1 != lastReading1) {
    lastDebounceTime1 = millis();
  }
 
  if (reading2 != lastReading2) {
    lastDebounceTime2 = millis();
  }
 
  if ((millis() - lastDebounceTime0) > debounceDelay) {
    if (reading0 != buttonState0) {
      buttonState0 = reading0;
      if (buttonState0 == LOW) {
        ledState0 = !ledState0;
        buttonPushCounter0++;
        targetFloor = 0; // setam targetFloor pt nr butonului
        Serial.println(buttonPushCounter0);
      }
    }
  }
 
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      if (buttonState1 == LOW) {
        ledState1 = !ledState1;
        buttonPushCounter1++;
        targetFloor = 1;
        Serial.println(buttonPushCounter1);
      }
    }
  }
 
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      if (buttonState2 == LOW) {
        ledState2 = !ledState2;
        buttonPushCounter2++;
        targetFloor = 2;
        Serial.println(buttonPushCounter2);
      }
    }
  }
  
  lastReading0 = reading0;
 
  //digitalWrite(ledPin1, ledState1);
  lastReading1 = reading1;
 
  //digitalWrite(ledPin2, ledState2);
  lastReading2 = reading2;
 
 
  digitalWrite(ledPin, ledState);
  //proces inchidere usi
  if (targetFloor!=-1) {  //verificam daca exista targetFloor
    if(startClosingDoors==0){
      counter=0;

      tone(buzzerPin, 100, 1000); // sunet pt "se inchid/deschid usile"

      startClosingDoors=1;
      initialMillis=millis();
//inchidem restul becurilor
      if (currentFloor == 0) {
        digitalWrite(ledPin0, LOW);
      } else if (currentFloor == 1) {
        digitalWrite(ledPin1, LOW);
      } else if (currentFloor == 2) {
        digitalWrite(ledPin2, LOW);
      }
    }

   
    if(millis() - initialMillis > buzzerDuration){  //verif daca s-a terminat timerul de inchis usi
    //incepem sa miscam liftul
      currentMillis=millis();
      if(currentMillis - previousMillis > blinkDuration){
        previousMillis=currentMillis;
        ledState=!ledState;//negam starea becului: daca e off devine on si invrs
        counter++;
      }
      if(abs(currentFloor - targetFloor) == 2){
        if(counter>5 && counter<9){
          digitalWrite(ledPin1, HIGH);
        }
        else if(counter >=10){
          currentFloor=targetFloor;
          targetFloor=-1;
          startClosingDoors=0;
          tone(buzzerPin, 100, 1000);
        }
      }
      else{
        if(counter>5){
          currentFloor=targetFloor;
          targetFloor=-1;
          startClosingDoors=0;
          tone(buzzerPin, 100, 1000);
        }
      }
 
 
 
    }
 
    //previousMillis = currentMillis;
  }
  else{  //pt a aprinde ledul de la etajul curent
    switch(currentFloor){ 
    case 0:
      digitalWrite(ledPin0, HIGH);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      break;
    case 1:
      digitalWrite(ledPin0, LOW);
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      break;
    case 2:
      digitalWrite(ledPin0, LOW);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      break;
  }
  }
 
 
}
