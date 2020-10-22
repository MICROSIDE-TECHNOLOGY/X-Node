from microbit import *

uart.init(baudrate=115200, tx = pin8, rx = pin1)

display.scroll('ok')

while True:
    uart.write('XN001A+G\n')
    mess = ""
    if uart.any():
        mess=uart.read()
        display.scroll(mess)
   
    
    
    sleep(1000)
    uart.write('XN002A+G\n')
    mess = ""
    if uart.any():
        mess=uart.read()
        display.scroll(mess)
