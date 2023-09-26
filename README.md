# Cellular-Based-DC-DC-Converter-Controller
This project is based on controlling the duty cycle of a DC-DC Converter using cloud. The converter is connected to Cloud using Celluar Technology. In this project, 2G GPRS/GSM is used to connect to cloud. This project is used to make DC-DC Converter Cloud connected which can be used to control a cluster of DC-DC Conveters by a central server.

The project can drive DC-DC Bulk Converter, DC-DC Boost Converter & DC-DC Bidirectional Converter.

### Components Used
  - AVR ATMEGA328P
  - DC-DC Bidirection Convertor
  - Optocoupler Based Driver Circuit
  - SIM800L GSM/GPRS
  - Oscilliscopes
  - Differential Probes
  - Multimeter
  - Wires With Suitable Diameters

### Connections
1. A bootloaded, ATMEGA328P is programmed with the code.
2. The ATMEGA328P connection with GSM/GPRS Module.
   - Pin 4 is connected to TX of SIM800L
   - Pin 5 is connected to RX of SIM800L
   - Ground of ATMEGA328P and SIM800L is made common.
3. Connect the Driver circuit with the DC-DC Converter appropriately.
4. The ATMEGA328P connection with the Driver Circuit.
   - Pin 15 is connected to BOOST Conventer Gate Pulse Optocoupler Input.
   - Pin 16 is connected to BUCK Conventer Gate Pulse Optocoupler Input.
   - Ground of Driver Circuit and ATMEGA328P is common.
