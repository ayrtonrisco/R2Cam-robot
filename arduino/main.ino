#include <LEANTEC_ControlMotor.h>//Incluimos la librería control de motores
// Configuramos los pines que vamos a usar
ControlMotor control(2,3,7,4,5,6);
int MotorDer1=2;//El pin 2 de arduino se conecta con el pin In1 del L298N
int MotorDer2=3;//El pin 3 de arduino se conecta con el pin In2 del L298N
int MotorIzq1=7;//El pin 7 de arduino se conecta con el pin In3 del L298N
int MotorIzq2=4;//El pin 4 de arduino se conecta con el pin In4 del L298N
int PWM_Derecho=5;//El pin 5 de arduino se conecta con el pin EnA del L298N
int PWM_Izquierdo=6;//El pin 6 de arduino se conecta con el pin EnB del L298N
int respuesta = 0;
int velocidad=150;//Declaramos una variable para guardar la velocidad

void setup() {
  Serial.begin(9600);
  //Configuramos los pines como salida
  pinMode(MotorDer1, OUTPUT);
  pinMode(MotorDer2, OUTPUT);
  pinMode(MotorIzq1, OUTPUT);
  pinMode(MotorIzq2, OUTPUT);
  pinMode(PWM_Derecho, OUTPUT);
  pinMode(PWM_Izquierdo, OUTPUT);
}

void loop() {
        if (Serial.available() > 0) {
          respuesta = Serial.read();
          switch(respuesta){
            case 49:
              retroceder();
              break;
            case 50:
              avanzar();
              break;
            case 51:
              giroIzq();
              break;
            case 52:
              giroDer();
              break;
            case 53:
              parar();
              break;
            default:
              parar();
              break;
          }
        }
}
//DECLARACION DE METODOS QUE CONTROLAN EL MOVIMIENTO DE LAS RUEDAS
void parar(){ 
/*Función para que las ruedas paren*/
  digitalWrite(MotorDer1,LOW);
  digitalWrite(MotorDer2,LOW);
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorIzq2,LOW);
}
void avanzar(){
  digitalWrite(MotorDer1,LOW); 
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorDer2,HIGH); 
  digitalWrite(MotorIzq2,HIGH);
}
void giroDer(){
  digitalWrite(MotorDer1,LOW); 
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorDer2,LOW); 
  digitalWrite(MotorIzq2,HIGH);
}
void giroIzq(){
  digitalWrite(MotorDer1,LOW); 
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorDer2,HIGH); 
  digitalWrite(MotorIzq2,LOW);
}
void retroIzq(){
  digitalWrite(MotorDer1,LOW); 
  digitalWrite(MotorIzq1,HIGH);
  digitalWrite(MotorDer2,LOW);
  digitalWrite(MotorIzq2,LOW);
}
void retroDer(){
  digitalWrite(MotorDer1,HIGH); 
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorDer2,LOW);
  digitalWrite(MotorIzq2,LOW);
}
void retroceder(){
  digitalWrite(MotorDer2,LOW);
  digitalWrite(MotorIzq2,LOW);
  digitalWrite(MotorDer1,HIGH); 
  digitalWrite(MotorIzq1,HIGH);
}
void giroEjeDer(){
  digitalWrite(MotorDer1,LOW); 
  digitalWrite(MotorDer2,LOW); 
  digitalWrite(MotorIzq1,HIGH);
  digitalWrite(MotorIzq2,HIGH);
}
void giroEjeIzq(){
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorIzq2,LOW);
  digitalWrite(MotorDer2,HIGH); 
  digitalWrite(MotorDer1,HIGH); 
}