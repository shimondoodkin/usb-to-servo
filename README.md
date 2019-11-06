# usb-to-servo
This helps to control servos from PC.
To control an educational robot arm from a PC.

To use with any programming language that supports writing to serial port.

The arduino is used as Serial port (with a text protocol) as an adapter to i2c to control the pwm controller.

hardware: 

ATMEGA32U4

<img width="200" height="200" src="https://ae01.alicdn.com/kf/HTB1KzU3UCzqK1RjSZFjq6zlCFXaF/Beetle-Virtual-Keyboard-BadUSB-Pro-Micro-ATMEGA32U4-Module-Mini-Development-Expansion-Board-For-Arduino-Leonardo-R3.jpg">

https://www.aliexpress.com/wholesale?catId=0&initiative_id=SB_20191106110733&SearchText=ATMEGA32U4

16 pwm PCA9685

<img width="200" height="200" src="https://ae01.alicdn.com/kf/HTB1tWaCXUvrK1RjSszfq6xJNVXaS/16-Channel-12-bit-PWM-Servo-Driver-I2C-interface-PCA9685-module-for-arduino-or-Raspberry-pi.jpg">

https://www.aliexpress.com/wholesale?catId=0&initiative_id=SB_20191106111154&SearchText=16+pwm+PCA9685

i2c wireing:
leonardo SLC to SLC in PCA9685: slave clock
leonardo SDA to SDA in PCA9685: slave data
leonardo GND to GND in PCA9685: ground
leonardo 5V to VCC in PCA9685: power for chip

connect external power as required by servos, to "power" in PCA9685, usually larger middle connector.

software:

install library inside arduino: https://learn.adafruit.com/16-channel-pwm-servo-driver/using-the-adafruit-library

load the source to arduino board

develop some software that writes to serial port using any programming language
