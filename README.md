##AVR Programming using avr-gcc
This is BLDC (Brushless DC) motor PID control system program. I am using ESC, so I just need to send a high pulse (between 1 ms to 2 ms) in a signal which has 20 ms period. It is similar to servo driving pulse. In **Makefile** I use ATMega328P, 16MHz clock frequency, and USBTiny programmer. That is spec for Arduino UNO, so it is easier for me to switch framework between Arduino IDE and avr-gcc. You can change it for you board/environtment.

##Building program with Makefile
Compiling program
`sudo make`

Upload a HEX file to board
`sudo make program`

Cleaning compiled file
`sudo make clean`
