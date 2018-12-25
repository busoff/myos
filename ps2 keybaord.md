# PS/2 keyboard
You can write a byte to or receive a byte from keyboard. It uses *IRQ2* in 8025 PIC to signal a keyboard event to CPU. 
Then you can read the scan code in such interrupt to know which key is pressed/released.

You can send a command (one byte) to keyboard. Then the keyboard either 
1. acknowledges the command by sending *ACK*
2. or sending a *RESEND* when it's busy or even hardware fault. In this case, you at least retries 3 times then give up

For some commands which have data bytes, they require the data bytes should be sent after their command byte.

## Scan code
Keyboard use scan code to represent an keybobard event that which key is pressed or released. A scan code is 8 bit value.

## Reference
- https://wiki.osdev.org/Keyboard
