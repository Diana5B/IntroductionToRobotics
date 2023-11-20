# IntroductionToRobotics
This repository contains all the resources and materials associated with the robotics laboratory held at the Faculty of Mathematics and Computer Science. The laboratory focuses on exploring weekly homework assignments, projects, and enhancing our skills in the field of robotics.


# Homework
 
<details>
  <summary>
      <h2>Homework 1: Controlling an RGB LED using 3 potentiometers</h2>
  </summary>
  <br>
 
  ### Task:
  #### Use a separate potentiometer for controlling each color of the RGB LED: Red,Green, and Blue. This control must leverage digital electronics. Specifically, you need to read the potentiometer’s value with Arduino and then write a mapped value to the LED pins.
  
  I utilized three potentiometers, allocating one for each color channel, along with three resistors, each with a value of 330 ohms.
 
  ### [Code](https://github.com/Diana5B/IntroductionToRobotics/blob/main/controlling_RBG_with_3_Potentiometers.ino)
  ### [Video](https://youtube.com/shorts/4DI-YE8W-8I?si=Qd2odoNIk8rZXYd7)
  ### ![Led](https://github.com/Diana5B/IntroductionToRobotics/assets/115624763/c4b9e31a-9edc-45ad-b81a-a7d5cc8db585)
  
</details>

 <details>
 <summary>
      <h2>Homework 2: levator simulator wannabe</h2>
  </summary>
  <br>
 
  ### Task:
  #### This project entails creating a 3-floor elevator control system using an Arduino, which integrates LEDs, buttons, and a buzzer. Each of the three LEDs signifies a specific floor, with the LED associated with the current floor illuminated. Furthermore, there's an additional LED representing the elevator's operational state. It flashes when the elevator is in motion and stays steady when it's stationary. The buttons on each floor serve as call buttons. When pressed, the elevator will emulate movement towards the corresponding floor after a brief delay.

  For this project, I employed three red LEDs (connected to pins 10, 11, and 12) to symbolize three different floors (0, 1, and 2), and each LED is accompanied by a 330-ohm resistor. Additionally, there are buttons for each floor, connected to pins 2, 3, and 4, which are used to call the elevator when pressed. Another green LED (linked to pin 13) blinks when the elevator is in motion and is also paired with a 330-ohm resistor. To produce sound effects during the opening or closing of the elevator doors, a buzzer connected to pin 9 is utilized, along with a 100-ohm resistor.

 ### ![schema](https://github.com/Diana5B/IntroductionToRobotics/assets/115624763/f13c6cc4-6900-47b9-b249-0851c884f0bc)

 ### [Code](https://github.com/Diana5B/IntroductionToRobotics/blob/main/levator_simulator_wannabe.io)
 ### [Video](https://youtu.be/ucYN62i3QiE?si=VxGs4HqVFmv4JSM7)
 ### ![t2_R](https://github.com/Diana5B/IntroductionToRobotics/assets/115624763/1fff4266-e7b1-4b4d-a747-9191be724cfa)
### ![tema2_R](https://github.com/Diana5B/IntroductionToRobotics/assets/115624763/41828110-d72b-4577-8aaa-85c9c93fc9f7)
 
</details>

<details>
<summary>
      <h2>Homework 3: 7 segment display drawing</h2>
  </summary>
  <br>
  
### Task:
#### You want to use a joystick to control the position of the active segment and effectively "draw" on a 7-segment display. The segment movement should feel natural, allowing segments to transition only to neighboring positions without passing through any "walls" or off-limits areas. This means that the segments will move smoothly from one position to an adjacent one, making the interaction intuitive and user-friendly.

For this project, I employed a joystick connected to digital pin 2 and analog pins A0 and A1 to manipulate a 7-segment display. Additionally, I integrated eight 220-ohm resistors, assigning one to each LED segment of the 7-segment display.


 ### ![7-seg](https://github.com/Diana5B/IntroductionToRobotics/assets/115624763/e5db910a-e8be-4ded-b855-bac80eb435b1)

 ### [Code](https://github.com/Diana5B/IntroductionToRobotics/blob/main/7-segment.ino)
 ### [Video](https://youtu.be/HcUUxy2D1f8?si=vF2vCRgjEZgWoLeg)
 ### ![7-segment](https://github.com/Diana5B/IntroductionToRobotics/assets/115624763/8c95c285-3510-45fd-8853-f7552d150b63)
</details>


<details>
  <summary>
      <h2>Homework 4: Stopwatch Timer</h2>
  </summary>
  <br>
 
  ### Task:
  #### Utilize a 4-digit 7-segment display along with three buttons to create a stopwatch timer with functionality similar to basic stopwatch features found on most phones. Pressing the Start button initiates the timer. While the timer is counting, pressing the lap button records the current timer value in memory. Following a reset, you can use the flag buttons to cycle through the saved lap times.
  
  For this assignment, I used a 7-segment display along with three buttons (start/stop, reset, and save lap), along with resistors and wires.
Button 1: Start/Pause (Display shows "000.0"). When the Start button is pressed, the timer initiates. In Pause Mode, the lap flag button becomes inactive.
Button 2: Reset (if in pause mode). Reset saved laps (if in lap viewing mode). Pressing the reset button resets the timer to 000.0.
Button 3: Save Lap (if in counting mode), cycle through the last saved laps (up to 4 laps).

 
  ### [Code](https://github.com/Diana5B/IntroductionToRobotics/blob/main/StopWatchTimer.ino)
  ### [Video](https://youtu.be/91JSriiT5e8?si=pvMcWtq4HIFvse0P)
  ### ![stopwatch](https://github.com/Diana5B/IntroductionToRobotics/assets/115624763/f6b71af1-bf70-4f25-92f5-56a82d8dee6c)
  
</details>




<details>
<summary>
      <h2>Homework 5: Pseudo-Smart Environment Monitor and Logger</h2>
  </summary>
  <br>
  
### Task:
#### Design a "Smart Environment Monitor and Logger" with Arduino. This project involves employing a range of sensors to collect environmental data, storing this information in EEPROM, and presenting visual feedback through an RGB LED. Additionally, user interaction is facilitated through a Serial Menu. The primary emphasis of this project lies in the seamless integration of sensor readings, efficient memory management, Serial Communication, and achieving the overarching goal of constructing a user-friendly menu system.

For accomplishing this task, I employed the following components: arduino Uno Board, ultrasonic Sensor (HC-SR04), LDR (Light-Dependent Resistor), also known as Photocell, Photoresistor or Light Sensor, RGB LED, appropriate resistors, breadboard and connecting wires

 ### [Code](https://github.com/Diana5B/IntroductionToRobotics/blob/main/Pseudo-SmartEnvironmentMonitorandLogger.ino)
 ### [Video]()
 ### ![Pseudo-Smart Environment Monitor and Logger](https://github.com/Diana5B/IntroductionToRobotics/assets/115624763/59c2aac1-5e07-4211-b73b-c60524d141e5)
</details>
