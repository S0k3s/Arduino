import serial
arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

import mido
port = mido.open_input('wavetable', virtual=True)

for message in port:
    print(message)
    if message.type == "note_on":
        arduino.write(bytes([message.note]))
    if message.type == "note_off":
        arduino.write(bytes([128]))
