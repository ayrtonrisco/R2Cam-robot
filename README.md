# R2Cam-robot
> Parte del proyecto que se encarga de gestionar el robot. Es decir, en este proyecto podremos encontrar dos carpetas. Una orientada al desarrollo del codigo para la placa Arduino, y otro para el desarrollo del codigo que ejecutara la Raspberry
## Arduino
Dentro tenemos un archivo .ino que contendra el codigo que ira ejecutando la placa arduino.
### Por hacer:
- [x] Escuchar a la Raspberry
- [x] Movimiento de las ruedas
## Raspberry Pi
Dentro tendremos las aplicaciones que ejectura la Raspberry(la cual llamaremos cliente).
### Por hacer:
- [x] Hablar a arduino
- [x] Preguntar al servidor acerca de las ordenes
- [x] Capturar video
- [x] Stream del video
### Realizar el streaming
Para realizar el streaming de video hemos ejecutado el siguiente comando
> avconv -f video4linux2 -s 500x500 -i /dev/video0 -vcodec libx264 -preset ultrafast -f flv rtmp://r2cam.me/live/directo