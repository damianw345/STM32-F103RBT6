# STM32-F103RBT6
Repository includes codes for popular NUCLEO board based on STM32 F103RBT6 written with use of Standard Peripheral Library from ST. Thanks to this software NUCLEO became an on board computer of a robot. Peripheral modules used in this project include: 

-DC motor driver Pololu 713 Toshiba TB6612FNG <br />
https://www.pololu.com/product/713 <br />
Two channel motor driver can control direction of the rotation of each motor and change the motors' <br />
speed by setting up the PWM value<br />

-2x Micro DC Motor with Encoder-SJ01 SKU: FIT0450<br />
https://www.dfrobot.com/wiki/index.php/Micro_DC_Motor_with_Encoder-SJ01_SKU:_FIT0450<br />
Encoders are used to measure the speed of the motor's rotation<br />

-Servo controller Pololu Micro Maestro<br />
https://www.pololu.com/product/1350<br />
Servo controller has the ability to control up to 6 servos at the time<br />

-Digital infrared thermometer MLX90615<br />
https://www.melexis.com/en/product/mlx90615/digital-plug-play-infrared-thermometer-ultra-small-to-can<br />
Thermometer measures object's temperature on small distances <br />

-4x Ultrasonic distance sensors HC-SR04<br />
http://www.micropik.com/PDF/HCSR04.pdf<br />
Four distance sensors provide the ability to measure distance from 2 cm - 150 cm in four directions at the time<br />

-3x Reflective Optical Sensor with Transistor Output CNY70<br />
http://www.micropik.com/PDF/HCSR04.pdf<br />
CNY70 are used for recognizing changes in the colour of the surface which can be black or white<br />

-Adafruit Bluefruit BLE UART Friend<br />
https://learn.adafruit.com/introducing-the-adafruit-bluefruit-le-uart-friend<br />

Module communicates via Bluetooth Low Energy with Adafruits' Android application "Bluefruit LE" running on smartphone.<br />
You can get the app from the Play store<br />

