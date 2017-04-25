#Se requiere de la instalacion de la libreria "serial" y "requests"
#El puerto actual por el que se comunica es el visualizado desde el portatil, se requiere el de la Raspi
import time

import requests

URL = 'http://192.168.168.197:8080/r2cam'
# Lo siguiente funciona
# ser = serial.Serial(port='/dev/cu.usbmodemFA131',baudrate=9600)

#Introduce un caracter para empezar a hacer peticiones
print ("Introduce un caracter (0 para salir):" )
entrada = int(input())
while entrada != 0:
   #ser.write(entrada)
   r = requests.get(URL)
   print(r.json()['direccion'])
   #Un sleep de 0.100 segundos. El valor dentro de sleep() es en segundos
   time.sleep(.100)
   # print ("Introduce un caracter (0' para salir): ")
   # entrada = int(input())