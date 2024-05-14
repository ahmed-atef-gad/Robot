# Control Project Course: Auto Guided Vehicle

Welcome to the Control Project Course.

## Project Overview

The Auto Guided Vehicle (AGV) is a small-scale autonomous vehicle designed to navigate predefined paths and execute commands wirelessly via Bluetooth communication. The project integrates hardware components with software control to achieve autonomous movement and user interaction.

## Components Used

### 1. HC-05 Bluetooth Module

- **Function**: Enables wireless communication between the AGV and external devices such as a computer or smartphone.
- **Role**: Facilitates control commands transmission and data exchange.

### 2. L298 Motor Driver Module

- **Function**: Provides motor control for the AGV's movement.
- **Role**: Regulates the speed and direction of the motors based on input commands.

### 3. MPU6050 IMU (Inertial Measurement Unit)

- **Function**: Measures motion, orientation, and acceleration of the AGV.
- **Role**: Provides feedback on the AGV's orientation, aiding in navigation and control.

### 4. JavaFX Application

- **Function**: User interface for controlling the AGV.
- **Role**: Allows users to send commands, monitor AGV status, and adjust parameters for autonomous operation.

### 5. Line Follower Tracking Module
- **Function**: Detects intersections and tracks lines on the predefined path.
- **Role**: Provides input for navigation decisions, enhancing AGV's navigation capabilities.

## Project Structure

The project consists of both hardware and software components, organized as follows:

1. **Hardware Setup**:

   - Assemble the chassis and mount motors, wheels, and sensors according to the design specifications.
   - Connect the HC-05 Bluetooth module, L298 Motor Driver Module, and MPU6050 IMU to the microcontroller (e.g., Arduino) as per the circuit diagram.

## Getting Started

To get started with the project, follow these steps:

1. **Hardware Assembly**: Set up the AGV chassis and connect the electronic components according to the provided circuit diagram.

2. **Software Installation**: Install the necessary development tools for programming the microcontroller and JavaFX application.

3. **Firmware Upload**: Upload the firmware to the microcontroller, ensuring proper communication with the HC-05 Bluetooth module and motor control via the L298 Motor Driver Module.

4. **JavaFX Application Setup**: Run the JavaFX application on your computer and establish a Bluetooth connection with the AGV.

5. **Control and Testing**: Use the JavaFX interface to send control commands to the AGV, testing both manual and autonomous operation modes.

## Circuit Diagram

 ![Sizzling Krunk-Trug](https://github.com/ahmed-atef-gad/Robot/assets/89663624/d9aa9871-af7a-48b0-bf35-0a65706cf42c)

 ## Demo


https://github.com/ahmed-atef-gad/Robot/assets/89663624/c31d5175-bbac-49aa-84a4-fb65e46cb46b



### This project was developed as part of Control Course.
