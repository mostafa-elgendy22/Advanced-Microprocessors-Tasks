# Advanced-Microprocessors-Tasks

This repo includes my solution to the Advanced Microprocessors course midterm (this solution earned the full grade "20/20"). It consists of four tasks (their details can be found in "MidtermAssessment.pdf" document). It covers various topics: Arduino uno GPIO, Interrupts, Stepper motor interfacing (implemented from scratch), LCD interfacing, Non-blocking delays, Keypad (implemented from scratch). All the simulations are done using <a href="https://www.simulide.com/p/home.html">SimuLIDE</a>.

## Task 1

### Problem Statement

It is required to connect a LED to pin 8 of Arduino uno board. Use one tact switch ("Fixed Volt" in the
SimuLIDE) connected to pin 10 to control it. This LED should be turned off at tact high and turned on at tact low

### Simulation

![Simulation](https://github.com/mostafa-elgendy22/Advanced-Microprocessors-Midterm-Assessment/blob/main/Task1/9190608_1_V1.gif)

## Task 2

### Problem Statement

It is required to build a light circle. It contains 12 LEDs and is controlled using a push button. Each time the button is pressed, the system changes LED sequence direction with three seconds between each LED and the next one in the clockwise case and one second for the anticlockwise case.

### Simulation

![Simulation](https://github.com/mostafa-elgendy22/Advanced-Microprocessors-Midterm-Assessment/blob/main/Task2/9190608_2_V1.gif)

## Task 3

### Problem Statement

It is required to build an automatic kitchen ventilation fan that works also as kitchen hood. If there is smoke it works as a kitchen hood to absorb it. If there is no smoke and the temperature is more than 25 degrees, it works as a fan. Otherwise, the motor is stopped. An always on LCD is used to display the current temperature. This system contains:

<ol>
    <li>A stepper motor that is rotating clockwise with 2 rpm to work as a fan and anticlockwise with 4 rpm to absorb smoke.</li>
    <li>Digital smoke detector sensor to detect smoke. Zero means no smoke while one indicates smoke existence. It is replaced by a tact switch ("Fixed Volt" in the SimuLIDE) for simulation. If there is smoke, the motor rotates anticlockwise to start absorbing smoke. The motor keeps rotating anticlockwise for extra 3 seconds after there is no smoke (the tact switch is tact low).</li>
    <li>LM35 temperature sensor. To sense the kitchen temperature. It is replaced by potentiometer.</li>
    <li>LCD to display the current temperature.</li>
    <li>Arduino uno.</li>
</ol>

![Simulation](https://github.com/mostafa-elgendy22/Advanced-Microprocessors-Midterm-Assessment/blob/main/Task3/9190608_3_V1.gif)

## Task 4

### Problem Statement

Instead of programming Arduino uno to do certain tasks, it is required to program Arduino uno to be user programmable. You need to develop a very simple programming language. A 4x4 keypad is connected to 8 pins of the Arduino containing numbers from 0 to F. To start programming the user has to press 0. You allow the user to use two internal variables Var1 and Var2. Two digital output pins connected to two LEDs Yellow and Red.
This system contains:

<ol>
    <li>4x4 keypad.</li>
    <li>2 LEDs (Yellow and Red) the yellow LED is connected to pin 8 and the Red LED is connected to pin 9. Called output 1 and output 2.</li>
    <li>2 tact switches (“Fixed Volt” in the SimuLIDE) – Switch 1 is connected to pin 10 and switch 2 is connected to pin 11. Called input 1 and input 2.</li>
    <li>2 potentiometers connected to pins A1 and A2 called analog input 1 and analog input 2.</li>
    <li>Arduino uno.</li>
</ol>

The rules of the programming language can be found in the document.

### Test case 1

**Input** = "0911F"
<br>
**Program behavior**: output1 (pin 8 - yellow LED) should be turned on.

![Simulation](https://github.com/mostafa-elgendy22/Advanced-Microprocessors-Midterm-Assessment/blob/main/Task4/9190608_4_V1_1.gif)

### Test case 2

**Input** = "125420A115309E11531900C1F"
<br>
**Program behavior**: the system will act exactly like the "simple LED" system described on task 1.

![Simulation](https://github.com/mostafa-elgendy22/Advanced-Microprocessors-Midterm-Assessment/blob/main/Task4/9190608_4_V1_2.gif)

### Test case 3

**Input** = "5426A50217223116911D210B21803312519911529912519902529901539901539902F"
<br>
**Program behavior**: After pressing the execution button (F), the system will keep reading the potentiometer value. If it is more than 3 then only the yellow LED will be turned on. If the potentiometer value is less than 3 then only the red LED will be turned on. If it is equal to 3 then both of them will be turned off.

Note that this GIF is trimmed while entering the input because it is huge.

![Simulation](https://github.com/mostafa-elgendy22/Advanced-Microprocessors-Midterm-Assessment/blob/main/Task4/9190608_4_V1_3.gif)
