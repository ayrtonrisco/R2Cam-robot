//LEANTEC_ControlMotor es una librería para el control de 2 motores CC con el driver L298
//Desarrollada por LEANTEC ROBOTICS&ELECTRONICS
//Queda permitido el uso de esta librería por cualquier usuario. 
//Queda prohibido el uso de esta líbreria con ánimo de lucro

// Incluimos las librerías necesarias según el arduino que estemos utilizando
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

// Incluimos la librería cabecera
#include "LEANTEC_ControlMotor.h"


// Estos defines cargan los valores directamente en los motores por los pines que hemos seleccinado anteriormente.
#define MOT_IZQ_DELANTE digitalWrite(MotIzq1,HIGH);digitalWrite(MotIzq2, LOW)
#define MOT_IZQ_DETRAS  digitalWrite(MotIzq1, LOW);digitalWrite(MotIzq2, HIGH)

#define MOT_DER_DELANTE digitalWrite(MotDer1,HIGH);digitalWrite(MotDer2, LOW)
#define MOT_DER_DETRAS  digitalWrite(MotDer1, LOW);digitalWrite(MotDer2, HIGH)



// Con esta función configuramos los pines seleccionamos para que funcione el driver motor.
ControlMotor::ControlMotor(int MD1,int MD2,int MI1,int MI2,int PWMD,int PWMI)
{
   pinMode(MD1,OUTPUT);  // Configuramos como salida el Enable 1 del Derecho
   pinMode(MD2,OUTPUT);  // Configuramos como salida el Enable 2 del Derecho
   pinMode(MI1,OUTPUT);  // Configuramos como salida el Enable 1 del Izquierdo
   pinMode(MI2,OUTPUT);  // Configuramos como salida el Enable 2 del Izquierdo
   pinMode(PWMD,OUTPUT); // PWM usado para el motor Derecho
   pinMode(PWMI,OUTPUT); // PWM usado para el motor Izquierdo

   MotDer1=MD1;  // Almacenamos el pin seleccionado para el motor Derecho Enable 1 en la variable correspondiente para su posterior uso
   MotDer2=MD2;  // Almacenamos el pin seleccionado para el motor Derecho Enable 2 en la variable correspondiente para su posterior uso
   MotIzq1=MI1;  // Almacenamos el pin seleccionado para el motor Izquierdo Enable 1 en la variable correspondiente para su posterior uso
   MotIzq2=MI2;  // Almacenamos el pin seleccionado para el motor Izquierdo Enable 2 en la variable correspondiente para su posterior uso
   pwmD=PWMD;    // Almacenamos el pin seleccionado para el PWM Derecho en la variable correspondiente para su posterior uso  
   pwmI=PWMI;    // Almacenamos el pin seleccionado para el PWM Izquierdo en la variable correspondiente para su posterior uso  
}

// Esta función se encarga de calcular la velocidad de los motores según el ángulo que seleccionemos y la velocidad.
void ControlMotor::CalcularVelocidad(int velocidad, int giro, int *vel_izq, int *vel_der ){
  
    if( velocidad < 0 ){velocidad *= -1;}  // Pasamos a positivo el valor velocidad para hacer los c�lculos
    
    if((giro>=100)||(giro<=-100)){ // Al 100% o al -100% el robot solo gira, por lo que ambas ruedas van al 100% de velocidad
      *vel_izq=velocidad;
      *vel_der=velocidad;
    }
    else{ // Si no est� al 100% de giro, realizamos los c�lculos
      // Realizamos los c�lculos
      if(giro >= 0){       // El robot retrocede o avanza recto o a la derecha seg�n la variable giro
        giro = 100 - giro; // Invertimos los valores para hacer la regla de 3 ya que 0� el 100% de los motores y 100� es 0% de los motores
        *vel_izq= velocidad; // Como el giro es para la derecha si la variable es mayor que 0, el motor izquierdo va a la vecodidad m�xima que le marquemos
        *vel_der= (giro*velocidad)/100; // Hacemos una regla de tres y calculamos, si 255(m�xima velocidad) es el 100%(del giro), "variable giro" ser� X
      }
      else{                // El robot avanza recto o a la izquierda seg�n la variable giro
        giro += 100;       // Invertimos los valores y lo pasamos a positivo para hacer la regla de 3 ya que 0� el 100% de los motores y -100� es 0% de los motores
        *vel_der=velocidad;// Como el giro es para la izquierda si la variable es menor que 0, el motor derecho va a la vecodidad m�xima que le marquemos
        *vel_izq=(giro*velocidad)/100; // Hacemos una regla de tres, pasando el valor de giro a positivo y calculamos, si 255(m�xima velocidad) es el 100%(del giro), "variable giro" ser� X
      }
    }
    
}

// Esta función carga los valores correspondientes en cada motor
void ControlMotor::Motor(int velocidad, int giro){
  int  vel_izq,vel_der;  // Almacenamos las variables una vez procesada para cargarla despu�s a los motores.
   
  //------------------------------- Nos aseguramos que la variable giro no sobrepasa del 100% o del -100% --------------------------------------------//
  if(giro > 100){giro=100;}
  if(giro < -100){giro = -100;}
  //---------------------------- Nos aseguramos que la variable velocidad no sobrepasa del 255 o del -255 --------------------------------------------//
  if(velocidad > 255){velocidad=255;}
  if(velocidad < -255){velocidad = -255;}
  
  CalcularVelocidad(velocidad,giro,&vel_izq,&vel_der);  // Realizamos los calculos y almacemos los valores en las variables que mandamos por puntero
  analogWrite(pwmI,vel_izq);  // Cargamos el valor de la velocidad en el motor izquierdo
  analogWrite(pwmD,vel_der);  // Cargamos el valor de la velocidad en el motor derecho

  //-------------------------------- Realizamos los c�lculos para los motores seg�n las variables recibidas ------------------------------------------//
  if (velocidad >= 0){   // En este caso se entiende que el robot debe avanzar  
    if(giro >= 100){        // Giramos a la derecha completamente al 100% por lo que el motor derecho gira en sentido contrario (El robot no avanza, solo gira)
      MOT_IZQ_DELANTE;
      MOT_DER_DETRAS;
    }
    else if( giro <= -100){ // Giramos a la izquierda completamente al 100% por lo que el motor izquierdo gira en sentido contrario (El robot no avanza, solo gira)
      MOT_IZQ_DETRAS;
      MOT_DER_DELANTE;
    }
    else{                   // El robot avanza o gira mientras continua hacia delante por lo que ambos motores van giran en sentido positivo.
      MOT_IZQ_DELANTE;
      MOT_DER_DELANTE;
    }
  }
  else{                  // En este caso se entiende que el robot debe retroceder
    if(giro >= 100){        // Giramos a la derecha (Visto desde atr�s) completamente al 100% por lo que el motor derecho gira en sentido contrario (El robot no retrocede, solo gira)
      MOT_IZQ_DETRAS;
      MOT_DER_DELANTE;
    }
    else if( giro <= -100){ // Giramos a la izquierda (Visto desde atr�s) completamente al 100% por lo que el motor izquierdo gira en sentido contrario (El robot no retrocede, solo gira)
      MOT_IZQ_DELANTE;
      MOT_DER_DETRAS;
    }
    else{                   // El robot retrocede o gira continua hacia atr�s por lo que ambos motores van giran en sentido negativo.
      MOT_IZQ_DETRAS;
      MOT_DER_DETRAS;
    }
  }
}
