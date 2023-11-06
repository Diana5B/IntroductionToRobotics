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

<summary>
      <h2>Homework 3: 7 segment display drawing</h2>
  </summary>
  <br>
  
### Task:
#### You want to use a joystick to control the position of the active segment and effectively "draw" on a 7-segment display. The segment movement should feel natural, allowing segments to transition only to neighboring positions without passing through any "walls" or off-limits areas. This means that the segments will move smoothly from one position to an adjacent one, making the interaction intuitive and user-friendly.

For this project, I employed a joystick connected to digital pin 2 and analog pins A0 and A1 to manipulate a 7-segment display. Additionally, I integrated eight 220-ohm resistors, assigning one to each LED segment of the 7-segment display.

 ### ![schema](https://github.com/Diana5B/IntroductionToRobotics/assets/115624763/f13c6cc4-6900-47b9-b249-0851c884f0bc)

 ### [Code](https://github.com/Diana5B/IntroductionToRobotics/blob/main/levator_simulator_wannabe.io)
 ### [Video](https://youtu.be/HcUUxy2D1f8?si=vF2vCRgjEZgWoLeg)
 ### ![t2_R](https://github.com/Diana5B/IntroductionToRobotics/assets/115624763/1fff4266-e7b1-4b4d-a747-9191be724cfa)
