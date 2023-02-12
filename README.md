This repository contains codes for the prelabs of Embedded System (CMPE443) course. We worked with different kinds of sensors and actors such as ultrasound, RTD, LED etc.

We read manuals to find necessary registers and to modify them in accurate ways. We had labs each week.


## Technical Details
- The board used was [STM32 NUCLEO-L552ZE-Q](https://www.st.com/en/evaluation-tools/nucleo-l552ze-q.html#overview)
- IDE we used was  [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) and for monitoring we used [STM32CubeMonitor](https://www.st.com/en/development-tools/stm32cubemonitor.html).


## Explanation per File

### Prelab 3
The aim is to turn on/off the red LED **on the board**.

### Prelab 4
The aim is to turn on blue LED and turn off green LED when push button is not pressed. When pressed, turn off blue LED and turn on green LED.

### Prelab 5
_**Additional Hardware:** SPDT switch, breadboard, female cable, resistor_

When the SPDT switch is on left, red - blue - green LEDs will be turned on in sequence with 1 second intervals. When switch is on right, it will freeze at the state it was at the moment when switching and continnue until switching to the other side.

### Prelab 6
_**Additional Hardware:** [HC - SR04 Ultrasonic sensor](https://www.robotistan.com/Data/EditorFiles/HCSR04-datasheet-version-1.pdf), breadboard_

The aim is to measure distance data through the ultrasonic sensor and based on this, to turn on/off red LED on the board. More spesifically, when an object closer than 10cm is detected, the red LED will be turned on, otherwise turned off.

### Prelab 7
_**Additional Hardware:** RGB LED, breadboard, 4 female cables, 1K resistor_

At every second, the RGB LED changes colour, the sequence being White - Cyan - Magenta - Blue - Yellow - Green - Red - Black atomically. The lower level detail was that we were to use 4 TIM, 3 for the purpose of managing LEDs and 1 to organize swithes per second.

### Prelab 9
_**Additional Hardware:** potentiometer, 3 female cables, breadboard_

Patterns of R, G, B LEDs will be observed on board according to spesific value intervals and ADC interrupt will be utilized for this. In more detail:
-	**R - G - B LEDs are ON** when _Potentiometer Value > 3/4 Max Value_
-	**G - B LEDs are ON, R LED is OFF** when _3/4 Max Value >= Potentiometer Value > 2/4 Max Value_
-	**B LED is ON, R - G LEDs are OFF** when _2/4 Max Value >= Potentiometer Value > 1/4 Max Value_
- **R - G - B LEDs are OFF** when _1/4 Max Value >= Potentiometer Value_

### Prelab 10
_**Additional Hardware:** potentiometer, 3 female cables, breadboard_

The aim is to practice serial communication via UART(for the interrupts). The ADC value gathered from data through potentiometer will be sent to our PC with \r\n appended, data flow with 500ms frequency. I used [putty](https://www.putty.org/) (for windows OS) as PC interface of communication.

- _**Serial Communication configuration:**_
    -	9600 Baud
    -	8 Data Bits
    -	1 Bit Stop
    -	No Parity


