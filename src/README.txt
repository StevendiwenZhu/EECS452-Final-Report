There are three source code files: gesture_recognition.py running on the PC side, main.py running on the Pi side, control.ino running on the MCU (ESP32), and a library SparkFun for controlling the motor.

After turning on the Pi, connect the Pi and the PC to the same LAN. First, open the Arduino at the Pi end, configure the serial port and board, and upload the control.ino to ESP32. Then run the main.py file on the Pi side, and when the terminal shows that it is listening, run gesture_recognition.py on the PC.

When the PC and Pi end display the real-time image of the camera and the Pi terminal shows a successful connection, the code runs successfully.