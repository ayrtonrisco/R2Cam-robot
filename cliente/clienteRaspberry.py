#Se requiere de la instalacion de la libreria "serial"
#El puerto actual por el que se comunica es el visualizado desde el portatil, se requiere el de la Raspi
import serial
ser = serial.Serial(port='/dev/cu.usbmodemFA131',baudrate=9600)
print ("Introduce un caracter (0 para salir):" )
entrada = int(input())
while entrada != 0:  
   ser.write(entrada)   
   print ("Introduce un caracter (0' para salir): ") 
   entrada = int(input())
