// Define connections to the shift register
const int latchPin = 11;  // Connects to STCP (latch pin) on the shift register
const int clockPin = 10;  // Connects to SHCP (clock pin) on the shift register
const int dataPin = 12;   // Connects to DS (data pin) on the shift register

// Define connections to the buttons
const int startStopButtonPin = 2;  // Connect the start/stop button to digital pin 2
const int resetButtonPin = 9;      // Connect the reset button to digital pin 9
const int lapButtonPin=8;          // Connect the lap button to digital pin 8
 
 
// Define connections to the digit control pins for a 4-digit display
const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;
 
// Store the digits in an array for easy access
int displayDigits[] = { segD1, segD2, segD3, segD4 };
const int displayCount = 4;  // Number of digits in the display
 
// Define the number of unique encodings (0-9, A-F for hexadecimal)
const int encodingsNumber = 16;
 
// Define byte encodings for the hexadecimal characters 0-F
byte byteEncodings[encodingsNumber] = {
  //A B C D E F G DP
  B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11110110,  // 9
  B11101110,  // A
  B00111110,  // b
  B10011100,  // C
  B01111010,  // d
  B10011110,  // E
  B10001110   // F
};
// Variables for controlling the display update timing
 
unsigned long lastIncrement = 0;
unsigned long delayCount = 100;  // Delay between updates (milliseconds)
unsigned long number = 0;       // The number being displayed

int buttonState = HIGH;
int lastButtonState = HIGH;
int lastResetButtonState = HIGH;  // previous state of the reset button
int lastLapButtonState=HIGH;
int lapViewMode=0;
 
int laps[5]={0};
int lapAddCounter=1;
int lapCounter=1;
 
void setup() {
  // Initialize the pins connected to the shift register as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
 
  // Initialize the pins connected to the buttons as inputs
  pinMode(startStopButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(lapButtonPin,INPUT_PULLUP);
 
 
  // Initialize digit control pins and set them to LOW (off)
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
 
  lastButtonState = digitalRead(startStopButtonPin);
  lastResetButtonState = digitalRead(resetButtonPin);
 
  // Begin serial communication for debugging purposes
  Serial.begin(9600);
}
 
void loop() {
 
  // Display the incremented number on the 7-segment display using multiplexing
    if(!lapViewMode){
    writeNumber(number);
  }
  else{
    writeNumber(laps[lapCounter]);
  }
 
  static bool isTimerRunning = false;  // Track whether the timer is running or not
 
  // Read the state of the start/stop button
  buttonState = digitalRead(startStopButtonPin);
 
  // Check for a state change in the start/stop button
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      isTimerRunning = !isTimerRunning;
      lapViewMode=0;
      lapCounter=0;
      if (isTimerRunning) {
        lastIncrement = millis();
      }
    }
  }
 
  lastButtonState = buttonState;
 
  // If the timer is running, increment the number
  if (isTimerRunning) {
    if (millis() - lastIncrement > delayCount) {
      number++;
      number %= 10000;  // Wrap around after 9999
      lastIncrement = millis();
    }
  }
 
  // Read the state of the reset button
  int resetButtonState = digitalRead(resetButtonPin);
  
 
  // Check for a state change in the reset button
  if (resetButtonState != lastResetButtonState) {
    // If the reset button is pressed, reset the timer back to 0
    if (resetButtonState == LOW) {
      if(lapViewMode==1){
        lapViewMode=0;
        lapAddCounter=1;
        lapCounter=1;
        Serial.println("test");
        for(int i=0;i<5;i++){
          laps[i]=0;
        }
 
      }
      if(!isTimerRunning){
        number = 0;
        lapViewMode=1;
      }
 
    }
    lastResetButtonState=resetButtonState;
  }
  // Read the state of the lap button
  int lapButtonState=digitalRead(lapButtonPin);
  // Check for a state change in the lap button
  if (lapButtonState!=lastLapButtonState){
    if (lapButtonState == LOW) {
      if(isTimerRunning){
        laps[lapAddCounter]=number;
        lapAddCounter++;
        if(lapAddCounter==5){
          lapAddCounter=1;
        }
      }
      else{
        if(lapViewMode){
          lapCounter++;
          if(lapCounter==5){
            lapCounter=1;
          }
        }
      }
    }
    lastLapButtonState=lapButtonState;
  }
 
}

void writeReg(int digit) {
  // Prepare to shift data by setting the latch pin low
  digitalWrite(latchPin, LOW);
  // Shift out the byte representing the current digit to the shift register
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  // Latch the data onto the output pins by setting the latch pin high
  digitalWrite(latchPin, HIGH);
}
 
void activateDisplay(int displayNumber) {
  // Turn off all digit control pins to avoid ghosting
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  // Turn on the current digit control pin
  digitalWrite(displayDigits[displayNumber], LOW);
}
 
void writeNumber(int number) {
  // DONE: Initialize necessary variables for tracking the current number and digit position
  int currentNumber = number;
  int displayDigit = 3;  // Start with the least significant digit
  int lastDigit = 0;
  // DONE: Loop through each digit of the current number
  while (currentNumber != 0) {
    // DONE: Extract the last digit of the current number
    lastDigit = currentNumber % 10;
    // DONE: Activate the current digit on the display
    activateDisplay(displayDigit);
    // DONE: Output the byte encoding for the last digit to the display
    if(displayDigit==2){
      writeReg(byteEncodings[lastDigit]+1);
    }
    else{
      writeReg(byteEncodings[lastDigit]);
    }
    // DONE: Implement a delay if needed for multiplexing visibility
    delay(0);  // A delay can be increased to visualize multiplexing
    // DONE: Move to the next digit
    displayDigit--;
    // DONE: Update 'currentNumber' by removing the last digit
    currentNumber /= 10;
    // DONE: Clear the display to prevent ghosting between digit activations
    writeReg(B00000000);  // Clear the register to avoid ghosting
  }
  //To display "020.4", not "20.4"
  while(displayDigit>=0){
    activateDisplay(displayDigit);
    //Dot is gonna be on the second display
    if(displayDigit==2){  //
      writeReg(byteEncodings[0]+1); //The last byte of the 7-segment display is the dot; by adding 1 it lights up 
    }
    else{
      writeReg(byteEncodings[0]);
    }
 
    writeReg(B00000000); 
    displayDigit--;
  }
}
