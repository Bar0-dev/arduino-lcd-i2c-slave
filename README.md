# Arduino as i2c slave LCD controller
This module is to translate i2c commands into LCD parallel functions
## How to use
MicroPython I2C host implementation
```
from machine import Pin, I2C

led = Pin(2, Pin.OUT)
i2c = I2C(1, scl=Pin(22), sda=Pin(21))

screenAdress = 80

def lcdCmd(command):
    i2c.writeto(screenAdress, command)

def lcdPrint(message):
    command = 'print({})'.format(message)
    i2c.writeto(screenAdress, command)
```