
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

#### Overload Frame

* Used to notify all nodes on the bus that the transmitting node is currently over loaded with the data and unable to process any new messages.
*  An Overload frame indicates that its transmitter require delay before receiving next data or remote frame The overload flag consists of six dominant bits. The overload delimiter consists of eight recessive bits. 

![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/0da74759-4938-4899-bbe8-6c2884f5cf9e)


