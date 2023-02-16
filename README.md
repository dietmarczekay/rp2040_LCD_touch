this is my playground fro the Raspberry Pico rp2040

it uses to following hardware

MSH-4.0inch Display B

4x4 keypad

The goal is
- get the dispaly to work
- react on touch
- read keypad via PIO

Interaction with LCD is done with the help of https://github.com/Bodmer/TFT_eSPI.
After calibration, the cal data are stored in the EEPROM of the rp2040 and can be reloaded on startup.
