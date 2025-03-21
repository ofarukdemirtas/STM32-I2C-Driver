# STM32 Bare-Metal I2C

This repository contains a bare-metal implementation of I2C communication for STM32 microcontrollers. The project is developed using **STM32CubeIDE** and is designed to demonstrate how to use I2C peripherals without relying on HAL or other abstraction layers.

## Features
- Bare-metal implementation of I2C communication
- Configurable for different STM32 microcontrollers
- Example code for master/slave communication
- Lightweight and efficient

## Project Structure
    STM32-BareMetal-I2C/
    ├── Core/
    │ ├── Inc/ # Header files (registers, configurations)
    │ └── Src/ # Source code (I2C driver, application logic)
    ├── Drivers/ # Empty (HAL/LL not used - retained for IDE compatibility)
    ├── .gitignore # Excludes build artifacts and IDE files
    └── README.md # Project documentation



## Prerequisites
- **STM32CubeIDE** (version 1.17.0 or later)
- STM32 microcontroller development board
- Basic knowledge of I2C protocol

## Getting Started

### Clone the Repository
    git clone https://github.com/ofarukdemirtas/STM32-BareMetal-I2C.git
    cd STM32-BareMetal-I2C

# STM32 I2C Project

## Open the Project
1. Launch STM32CubeIDE.
2. Open the project by navigating to `File > Open Projects from File System...` and selecting the repository folder.

## Build and Flash
1. Connect your STM32 development board to your computer.
2. Build the project by clicking the **Build** button in STM32CubeIDE.
3. Flash the firmware to the board using the **Debug** or **Run** button.

## Usage
1. Modify the `main.c` file to configure the I2C settings (e.g., clock speed, master/slave mode).
2. Connect the I2C pins (SCL and SDA) to the appropriate devices.
3. Monitor the communication using a logic analyzer or oscilloscope.

## Example
The project includes an example of I2C communication:
- **Master Mode**: Sends data to a slave device.
- **Slave Mode**: Receives data from a master device.

Refer to the `main.c` file for implementation details.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Contributing
Contributions are welcome! Feel free to open issues or submit pull requests.

## Contact
For any questions or feedback, please contact **ofarukdemirtas**.

