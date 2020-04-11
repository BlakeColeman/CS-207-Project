Once it is running the project is easy to use. However a fair bit of setup is required. The code must be downloaded and uploaded onto the Arduino and a new library Arduino-IRremote must be downloaded from github (if another IRremote library is installed it may be necessary to remove it from the library). The setup for the IR receiver may depend on the model used but for the one used in this project. the 5V goes on the farthest side, the ground in the middle and the data wire on the near side, the data wire should attach to pin 2. Because the push button uses the INPUT_PULLUP function of the Arduino no resistor is required to make it work and it should be attached to pin 4. The potentiometer should be attached to pin 4. The RGB LED should be attached to pins 9,10 and 11 through three 220 ohm resistors. Once the circuit is set up some code adjustments will be required to get the project to work with the remote. The user should run the program on the Arduino and open the Serial Port. The user should then press the buttons they want to use for power and the colour presets on the remote (The default code uses three but more can be added by copying and pasting the switch case). The user should then record the hexadecimal number provided by the computer for each number then scroll to the RemoteButtons function and switch the appropriate hexadecimal number they were given for the one in the program preceded by 0x.

Repository Contents: 
/src - The source code to run the project
/img - Image of what completed project looks like 
/libraries - IRremote library 
/README.md
Requirement and Materials:
Dependencies: 
IRremote library
Bill of materials: 
1 push button 
1 RGB LED 
1 potentiometer 
1 IR sensor
3 220 ohm resistors 
1 Arduino UNO
Usage:
To use this project upload the code then set the remote codes as described above. Then the light can be turned on or off using the push button or power button on the remote. The speed of colour change can be adjusted using the potentiometer and the colour can be changed using the presets on the remote
Credits: 
Alex Clarke 
jbumstead 
Krishna Pattabiramin
