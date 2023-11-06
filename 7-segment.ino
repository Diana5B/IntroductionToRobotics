const int pinSW = 2; // Digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

byte swState = LOW;
int xValue = 0;
int yValue = 0;

// Declare all the segments pins
const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

const int segSize = 8;
int index = 0;

bool commonAnode = false; // Modify if you have common anode
const int noOfSegments = 8;  // Number of segments

int joystickState = 0;
int DeadZone = 80;
int currentSegment = 0;
int joystickCenter = 512;

bool buttonState = LOW;
bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long blinkInterval = 500; 
unsigned long lastBlinkTime = 0;

// Declare dpState as a global variable
bool dpState = LOW;

// Define constants for joystick states
const int RIGHT_STATE = 0;
const int LEFT_STATE = 1;
const int DOWN_STATE = 2;
const int UP_STATE = 3;
const int IDLE_STATE = 4;

const int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

// Define your custom segment matrix
byte digitMatrix[segSize][noOfSegments] = {
    // a b c d e f g DP
    {1, 0, 0, 0, 0, 0, 0, 0}, // Segment a
    {0, 1, 0, 0, 0, 0, 0, 0}, // Segment b
    {0, 0, 1, 0, 0, 0, 0, 0}, // Segment c
    {0, 0, 0, 1, 0, 0, 0, 0}, // Segment d
    {0, 0, 0, 0, 1, 0, 0, 0}, // Segment e
    {0, 0, 0, 0, 0, 1, 0, 0}, // Segment f
    {0, 0, 0, 0, 0, 0, 1, 0}, // Segment g
    {0, 0, 0, 0, 0, 0, 0, 1}  // Decimal Point (DP)
};

bool buttonPressed = false;

byte segmentState[segSize] = {0, 0, 0, 0, 0, 0, 0, 0}; // Initialize all segments to OFF

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define DP 7

const int numSegments = 8;
bool blinkState[numSegments] = {false, false, false, false, false, false, false, false};



int moveMatrix[segSize][4] = { // 4 directions: Up, Down, Left, Right
    {A, G, F, B},
    {A, G, F, B},
    {G, D, E, DP},
    {G, D, E, C},
    {G, D, E, C},
    {A, G, F, B},
    {A, D, G, G},
    {DP, DP, C, DP}
};

void handleMovement() {
    int xValue = analogRead(pinX); // Read X-axis value
    int yValue = analogRead(pinY); // Read Y-axis value

    // Check if the joystick is in the UP state
    if (yValue > joystickCenter + DeadZone) {
        if (joystickState != RIGHT_STATE) {
            Serial.println("RIGHT");
            joystickState = RIGHT_STATE;
            digitalWrite(segments[currentSegment], segmentState[currentSegment]);
            currentSegment = moveMatrix[currentSegment][RIGHT_STATE];
        }
    }
    // Check if the joystick is in the DOWN state
    else if (yValue < joystickCenter - DeadZone) {
        if (joystickState != LEFT_STATE) {
            Serial.println("LEFT");
            joystickState = LEFT_STATE;
            digitalWrite(segments[currentSegment], segmentState[currentSegment]);
            currentSegment = moveMatrix[currentSegment][LEFT_STATE];
        }
    }
    // Check if the joystick is in the LEFT state
    else if (xValue < joystickCenter - DeadZone) {
        if (joystickState != DOWN_STATE) {
            Serial.println("DOWN");
            joystickState = DOWN_STATE;
            digitalWrite(segments[currentSegment], segmentState[currentSegment]);
            currentSegment = moveMatrix[currentSegment][DOWN_STATE];
        }
    }
    // Check if the joystick is in the RIGHT state
    else if (xValue > joystickCenter + DeadZone) {
        if (joystickState != UP_STATE) {
            Serial.println("UP");
            joystickState = UP_STATE;
            
            digitalWrite(segments[currentSegment], segmentState[currentSegment]);
            currentSegment = moveMatrix[currentSegment][UP_STATE];
        }
    }
    // Check if the joystick is in the IDLE state (center)
    else if (xValue > joystickCenter - DeadZone && xValue < joystickCenter + DeadZone &&
             yValue > joystickCenter - DeadZone && yValue < joystickCenter + DeadZone) {
        if (joystickState != IDLE_STATE) {
            joystickState = IDLE_STATE;
        }
    }

    if (currentSegment > 7) {
        currentSegment = 0;
    }
    if (currentSegment < 0) {
        currentSegment = 7;
    }
}

void setup() {
    // Set the initial index to DP
    currentSegment = DP; // Set the initial segment to DP
    index = currentSegment; // Set the index to the initial segment

    pinMode(pinSW, INPUT_PULLUP);
    // Set the segment pins as OUTPUT
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinD, OUTPUT);
    pinMode(pinE, OUTPUT);
    pinMode(pinF, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinDP, OUTPUT);

    Serial.begin(9600);
}

void displayNumber(byte digit, byte decimalPoint) {
    // Your code to display the given digit on the 7-segment display
    for (int i = 0; i < segSize - 1; i++) {
        digitalWrite(segments[i], digitMatrix[digit][i]);
    }
    digitalWrite(segments[segSize - 1], decimalPoint);
}

void loop() {
    xValue = analogRead(pinX);
    yValue = analogRead(pinY);

    // Handle button press (toggle segment state)
    int reading = digitalRead(pinSW);
    if (reading == LOW && !buttonPressed) {
        // Short button press to toggle segment state
        dpState = !dpState;
        buttonPressed = true;
    } else if (reading == HIGH) {
        buttonPressed = false;
    }

    // Call handleMovement to update the current segment
    handleMovement();

    // Display the current segment with the joystick control
    displaySegment(currentSegment, dpState);
}

void displaySegment(int segment, bool blink) {
    for (int i = 0; i < numSegments; i++) {
        if (i == segment && blink) {
            digitalWrite(segments[i], HIGH); // Turn on the segment
        } else {
            digitalWrite(segments[i], digitMatrix[segment][i]);
        }
    }
}
