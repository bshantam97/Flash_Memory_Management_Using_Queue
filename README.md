# Flash_Memory_Management_Using_Queue

In this project I have implemented a Queue to reecieve data Asynchronously and have kept a tab of newlines in data for line extraction from Queue.
Using the HC-05 Bluetooth Module the Serial Communication is taking place between the smartphone user and the microcontroller.
If the microcontroller detects there is a "WRITE DATA:" Command being passed in the Serial Terminal , then the incoming data should be parsed and written in the Flash Memory of the microcontroller.
Else if the microcontroller detects there is a "READ DATA:" Command being passed in the Serial terminal , then the previously stored data in the Flash Memory is displayed on the Serial terminal of the users smartphone.
The size of the Flash memory is 1MB Which was partitioned into 64K for the Code and 960K to store incoming data.

# Output

