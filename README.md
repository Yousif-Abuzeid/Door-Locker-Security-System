# Door Locker Security System

This project implements a Door Locker Security System that uses a password to unlock a door. The system is designed using two ATmega32 Microcontrollers and follows a layered architecture model. The Human Machine Interface (HMI) is managed by one microcontroller, while the control logic and hardware interaction are handled by another.

## System Overview

### Components
1. **HMI_ECU (Human Machine Interface)**
   - **2x16 LCD Display**
   - **4x4 Keypad**

2. **Control_ECU**
   - **EEPROM**
   - **Buzzer**
   - **DC Motor**

### Features
- **Password Management**
  - Create and store a system password.
  - Enter password to unlock the door.
  - Change the system password.
  
- **Security Mechanism**
  - Three attempts to enter the correct password before triggering an alarm.
  - Activation of a buzzer for 1 minute after three incorrect attempts.

### System Sequence
1. **Password Creation**
   - Prompt user to enter and confirm a 5-digit password.
   - Save the password to EEPROM if matched.
   
2. **Main Menu Options**
   - Display main options on LCD.
   
3. **Unlock Door**
   - Prompt user to enter the password.
   - If correct, rotate motor to unlock and lock the door with corresponding messages on the LCD.
   
4. **Change Password**
   - Follow the password creation sequence to set a new password.
   
5. **Security Alarm**
   - Activate buzzer and display error message on three consecutive incorrect password attempts.
   - Lock the system for 1 minute.

## Drivers
- **GPIO Driver**: Common driver for both ECUs.
- **LCD Driver**: Used in 8-bit or 4-bit mode, connected to HMI_ECU.
- **Keypad Driver**: Connected to HMI_ECU.
- **DC Motor Driver**: Connected to CONTROL_ECU, controlled using Timer0 PWM.
- **EEPROM Driver**: External EEPROM controlled by I2C, connected to CONTROL_ECU.
- **I2C Driver**: Used in CONTROL_ECU for EEPROM communication.
- **UART Driver**: Facilitates communication between the two ECUs.
- **Timer Driver**: Full driver for TIMER1 with interrupt and callback techniques, used in both ECUs.
- **Buzzer Driver**: Controls the buzzer connected to CONTROL_ECU.

## How to Use
1. **Setting Up the System**
   - Connect the components as per the design.
   - Initialize the system and create a password.

2. **Operating the System**
   - Use the keypad to enter the password and unlock the door.
   - Access the main menu to change the password or lock the door.

3. **Handling Security Alerts**
   - Enter the correct password within three attempts to avoid the alarm.
   - Wait for 1 minute if the system is locked due to consecutive incorrect attempts.

## Project Files
- **Source Code**: Implementation of the drivers and main system logic.
- **Schematics**: Circuit diagrams for connecting the components.
- **Documentation**: Detailed explanation of the system and usage instructions.
