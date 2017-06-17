#Se requiere de la instalacion de la libreria "serial" y "requests"
import serial
import requests
import time
URL = 'http://r2cam.me:8081/r2cam'
ser = serial.Serial(port='/dev/ttyACM0',baudrate=9600)
time.sleep(23)
while True:
   r = requests.get(URL)
   respuesta = str(r.json()['direccion']
   ser.write(respuesta)
   time.sleep(.100)
