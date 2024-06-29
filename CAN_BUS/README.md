
## In-Vehicle Network 

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/2cc7dcfd-96ae-4868-9d5d-a567119f8ad8)

* Gateway Architecture: there's main centeral gateway ECU
* Domain Architecture: There's a gateway for each logical domain
* Zonal Architecture: ECUs are separated according to physical location. 

## CAN Protocol
### CAN Pros
* Low cost
* Network multiple microcontrollers with 1 pair of wires support high speed data transfer 
* Efficient
* Reliable Means There are five mechanisms for detecting errors in the CAN protocol:
  1) Bit monitoring
  2) Bit stuffing
  3) Frame check
  4) Acknowledgment check
  5) Cyclic redundancy check
* ROBUST: High speed data lines are resistant to Electromagnetic interface and electrical disturbances

### Bus Characteristic
* CAN bus uses a bit-wise arbitration mechanism to ensure that data is transmitted without conflict between multiple nodes.
  *  `arbitration mechanism:` the identifier is included in the message determines the priority the CAN bus controller compares the bits of each message id and take the logic AND of the signals. 
* CAN bus also supports error detection and a `cyclic redundancy check (CRC)` that mechanism ensures that data is transmitted and received correctly.
* the most common baud rates for CAN bus are 1 MHz, 500 KHz and 125 KHZ.

### CAN Layers
1) Link Layer
   
  *  Responsible for ensureing message reliability and error detection. It includes features such as message acknowledgment, retransmission and CRC error detection.
  *  defines the message format includeing the identifier, data length code and data field.

2) Pysical Layer

  * Responsible for transmitting and receiving the data over the communication channel includes features such as signal modulation, bit timing and electrical signaling.
  * the Specification for transmission medium such as cable impedance, voltage level and termination.

### CAN Messages

#### Data Frame

* A type of message used for transmitting data in the can bus network. It contains up to 8 bytess of data and an 11-bit or 29-bit Id, depending on the version of CAN Protocol used.

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/49a2c40c-9292-42a9-a61e-133ec21a5bae)


* Start of frame
  * A single dominant bit to mark the beginning of a data frame

*  Identifier ID
   * Contains the id of the message, which can be either 11 or 29 bits.

* Remote Transmission Request (RTR)
  * Indicates whether the message is remote transmission of data or an actual data.
 
* Data Length Code
  * Specifies the number of bytes of data being transmitted.
 
* Data Field
   * Contains the actual data being transmitted
  
* CRC
  * Provides error detection for the message.

* ACK / End of the Frame bit
  * Indicates the end of the message transmission 


#### Remote Frame

* CAN message that is used to request data from another node on the network.
* It does not contain any data payload but instead, it contains an id that specifies which node to request data from.

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/2e9747fe-04da-490b-b9dd-fb57fb62d267)

#### Error Frame

* Special message that a CAN node sends on the bus when it detects an error in the received message or during transmission.
* the error frame consists of two parts:
  * `The Error Flag:` is a dominant bit that indicates that start of an Error Frame.
  * `Error Delimiter:` is a recessive bit that indicates the end of frame.
  * In between the frame contains six or more bits of dominant error signaling. 

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/4c1112aa-f23d-4112-88a4-fb20aff57d28)

* Acknowledgment error: When node transmitting a message does not receive an acknowledgment bit from the receiving node, indicated that the message wan not successfully recieved.

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/85edeb9d-df74-4be5-b41a-1215ab72bae6)

##### CAN error detection and fault confinement
* when the node detects an eror on the CAN bus, it increments its error counter and transmits an error flag.
* It the error counter exceeds a certain threshold, the node enters an error `Active state` where it countinues to transmit error flags but does not transmit any message.
* If the error Counter continues to increase, the node enter an error `Passive state` where it no longer transmits any messages or error flags, Instead it listens to the bus to determine when it can resume normal operation.

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/f60d37f6-866f-4d90-8c12-03f1085e138d)

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/946702db-e0f9-4845-839d-0d91d3af59ce)

#### Overload Frame

* Used to notify all nodes on the bus that the transmitting node is currently over loaded with the data and unable to process any new messages.
*  An Overload frame indicates that its transmitter require delay before receiving next data or remote frame The overload flag consists of six dominant bits. The overload delimiter consists of eight recessive bits. 

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/0da74759-4938-4899-bbe8-6c2884f5cf9e)

### CAN Hardware Interface
* CAN Intereface include two main components:
  * CAN Controller: Responsible for handling the communication functions defined by the CAN protocal. It manages the message transmission and reception on the bus, the controller generates error frames and overload frames.
  * CAN Transceiver: Responsible for transmitting and recieving data on the CAN bus. It converts the digiital data generated by the CAN controller into an electrical signal that can be transmitted over the bus.  
* CAN Bus uses twisted pair cable to overcome EMI and differential voltage which applied one signall to line and the inverse signal to another.
* Logic 1 known as a Ressive bit -> The differntial is zero
* Logic 0 known as a Dominant bit -> The differntial is Maximum

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/684c2da2-f24b-4d8b-bb94-755c5c0df058)

#### CAN bit timing calculation
* To determine the values for the bit timing register (BTR)
* Calculated based on the desired bit rate and the oscillator frequency of the CAN controller.

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/89b9df6d-113a-42f1-880e-c0b4266f1f65)

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/66f15343-d259-4bad-bc0e-888abee4faaf)


* The values for Sync_Seg, Prop_Seg, Phase_Seg1 and Phase_Seg2 are typically chosen based on the requirments of the CAN protocal being used.

 ![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/fb26dc88-8d2c-4c01-9a8c-cde357c71758)

### CAN-FD 
That used to increase the data rate up to 5 Mbps and allows messages up to 64 bytes, also due to increase demand for higher bandwidth 
`What are the new feature in CAN-FD?`
* Increase data rate
* Using more effiecient frame format
* Have multiple data rate on the same bus

There's No Remote frame in CAN-FD.
the arbritration field remains the same as CAN 2.0.

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/1c87a8c0-7f84-420e-bd7f-ae3aded7cf01)
