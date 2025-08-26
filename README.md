# Arduino_Door_Lock
This is a Arduino-powered smart door lock system using a keypad to enhance user experience.


This Arduino-powered electronic door lock project demonstrates the implementation of embedded hardware and software integrated in order to create a secure, lows cost, and customizable user experience. The system permits users to unlock the smart door lock by entering a desired predefined 4 digit PIN with the help of the 4x4 keyapd. On of the off chances that a user inputs the wrong set of digits, it will trigger a security mechanism with a louckout feature preventing brute force entry. Additionally the system permits users to update their passwords on the spot without the need to alter the code, as long as they are able to pass the verification process of inputting their most current 4 digit PIN code. 

# Components
- **Arduino Uno** – microcontroller board 
- **4×4 Keypad** – for user PIN entry  
- **Micro Servo Motor** – for simple lock/unlock control  
- **16×2 LCD Display (I²C type)** – to display status messages 
- **Relay Module** – to control high-power devices like the solenoid lock  
- **Male-to-Female Jumper Wires / Connectors** – for circuit connections  
- **Solenoid Door Lock (12V DC)** – the actual locking mechanism  
- **9V Battery** – portable power source
  
# Features
- **PIN-based access** – door unlocks only when the correct PIN is entered
- **Real-time display** – LCD shows prompts and system status  
- **Relay-driven solenoid lock** – enables secure electronic locking  
- **Lockout mechanism (optional)** – disables input after multiple wrong attempts  
- **Low power consumption** – runs on a 9V battery or USB supply

# How it works
1. User enters a PIN on the keypad.  
2. Arduino checks if the entered PIN matches the stored one.  
3. If correct → LCD shows “Access Granted”, relay activates, and solenoid lock opens.  
4. If incorrect → LCD shows “Wrong PIN”, system stays locked.  
5. (Optional) After 3 wrong attempts, system can disable further input for security.

