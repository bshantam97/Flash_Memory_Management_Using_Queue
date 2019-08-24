# Flash_Memory_Management_Using_Queue

* In this project I implemented a Queue to recieve data Asynchronously and kept a tab of newlines in the input data for line extraction from Queue.
* Using the HC-05 Bluetooth Module the Serial Communication is taking place between the smartphone user and the microcontroller.
* If the microcontroller detects there is a "WRITE DATA:" Command being passed in the Serial Terminal , then the incoming data should be parsed and written in the Flash Memory of the microcontroller.
* Else if the microcontroller detects there is a "READ DATA:" Command being passed in the Serial terminal , then the previously stored data in the Flash Memory is displayed on the Serial terminal of the users smartphone.
* The data was recieved byte by byte in the Interrupt Mode , which would generate a callback upon successful reception of the byte and the process continues till the whole stream has been recieved 
* The size of the Flash memory is 1MB Which was partitioned into 64K for the Code and 960K to store incoming data.

# Hardware Required 

* STM32F407 Development Board 
* HC-05 Bluetooth Module
* Jumper Wires

# Drivers Used

* The HAL driver library for STM32F4 was used in the project 

# Partitioned memory region 

* The regions were partitioned into Flash and UpFlash Region 

![Memory_Partition](https://user-images.githubusercontent.com/51986101/63640528-7221d480-c66f-11e9-8a82-e08347818919.png)

# Output of the Serial Terminal 

![Flash_Output](https://user-images.githubusercontent.com/51986101/63640525-6cc48a00-c66f-11e9-853a-7fa82a164297.png)

# Flash Memory Contents

![Flash_output_contents](https://user-images.githubusercontent.com/51986101/63640530-73eb9800-c66f-11e9-9224-fb6ab9e7b792.png)

# Software used 

* The project was developed using the CubeMX Software by STMicroelectronics and an eclipse based IDE TrueStudio developed for STM32 Dev Board.
