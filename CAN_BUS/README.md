
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
