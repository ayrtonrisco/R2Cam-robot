#Se requiere de la instalacion de la libreria "serial" y "requests"
import serial
import requests
import time
URL = 'http://r2cam.me:8081/r2cam'
ser = serial.Serial(port='/dev/cu.usbmodemFA131',baudrate=9600)
time.sleep(3)
while True:
   r = requests.get(URL)
   print(r.json()['direccion'])
   ser.write(r.json()['direccion'])
   time.sleep(.100)
