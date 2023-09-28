                                    /***************** Automatic Smart Vehicles Parking ****************/
![Screenshot 2023-09-09 144443](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/14103645-b726-43e8-8ffa-995a2c44950e)

User Story:

Design and Development a parking System forvehicles
has Features of:
* You can enter it using specific IDs read by a QR code reader.
* IDs are Set By the System Admin.
* LCD to tell the user to show his ID to The QR Reader.
* Green and Red Leds to indicate the Validation of the entered ID.
* Big 7 segment to Show how many availableSlots.
* An Enter Gate Controlled by Servo motor open if the User enter a valid ID.
* for Safety there is PIR sensor near to the Gate which will not close until the PIR Sensor make Sure that the car has completely passed.
* At The Exit Gate there is PIR Sensor to Sense there is car want to exit the Exit Gate open and Close if PIR make Sure that the car has completely passed.

Technical Details:

The Project Cosists of 3 ECU (STM32F103C6) .

1) The Frist Microcontroller (ECU1) is responsible for Setting the valid IDs by the Admin and receive The Entered ID From ECU3 Through SPI Communication Protocol and Check if the enter ID is valid one or not.

  if it's valid one this ECU will Turn on Green Led which indicate that  ID is valid after the That the 'o' Command( open gate command)  will Send   through UART to ECU2 which control the Servo motors to open the enter Gate.

  if it isn't valid one the Turn on Red Led which indicate that ID is valid and 'c' command ( close Gate Command ) will send through UART to ECU2

2) The Second Microcontroller (ECU2) is responsible for Control The Enter and Exit Gates by two Servo motors according to the receiving Command from ECU1.also count the number of avilable Slots and Display it on Big Sevent Segment  
3) The Third Microcontroller (ECU3) is responsible for Taking The ID from user and Send it through SPI to ECU1 which will identify is it valid or not ? , also connected to LCD to welcome by users and tell them to show them IDs ,about the Exit Gate there is an PIR Sensor connected as External interrupt which will open the Exit Gate if The PIR Sense a Car want to Exit.

Driver: 

MCAL
1) GPIO
2) EXTI
3) TIMER
4) UART
5) SPI
6) RCC

HAL
1) LCD
2) Keyped
3) 7 segment
4) Servo motor

Link For Simulation : https://drive.google.com/drive/folders/1yevIup0NM9SU5S6gC43kUXZtqyWPmv_Z 
