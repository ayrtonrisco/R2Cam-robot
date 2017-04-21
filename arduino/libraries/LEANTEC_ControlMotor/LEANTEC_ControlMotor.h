//LEANTEC_ControlMotor es una librería para el control de 2 motores CC con el driver L298
//Desarrollada por LEANTEC ROBOTICS&ELECTRONICS
//Queda permitido el uso de esta librería por cualquier usuario. 
//Queda prohibido el uso de esta líbreria con ánimo de lucro
/*************************************************************************************************************************************************/
/*
/* Esta librería controla la velocidad y la dirección de los motores del robot.
/* La forma de usarla es de la siguiente manera.
/*
/* En esta primera parte agregamos la librería y configuramos los pines.
/*------------------------------------------------------------------------------------------------------
/* #include <ControlMotor.h>
/* ControlMotor control(2,3,7,4,5,6);   // MotorDer1,MotorDer2,MotorIzq1,MotorIzq2,PWM_Derecho,PWM_Izquierdo
/*------------------------------------------------------------------------------------------------------
/*
/* - MotorDer1: Enable 1 del motor Derecho
/* - MotorDer2: Enable 2 del motor Derecho
/* - MotorIzq1: Enable 1 del motor Izquierdo
/* - MotorIzq2: Enable 2 del motor Izquierdo
/* - PWM_Derecho: PWM del motor derecho (Debe ser un pin que admita PWM de arduinov
/* - PWM_Izquierdo: PWM del motor Izquierdo (Debe ser un pin que admita PWM de arduino
/*
/*-------------------------------------------------------------------------------------------------------
/* 
/* En esta segunda parte, controlamos el motor. La primera varaible es la velocidad que va de 0 a 255 y la segunda el % de giro que va de 0 a 100.
/* Si la velocidad es positiva el robot avanza, si la velocidad es negativa el robot retrocede.
/* Si el giro es positivo, el robot va recto (0%) o a la derecha (>0%), si es negativo el robot va recto (0%) o a la izquierda (<0%),
// Si el giro es 100, el robot en vez de avanzar girando, gira sobre su propio eje (Una rueda avanza y otra retrocede.
/*-------------------------------------------------------------------------------------------------------
/*
/* control.Motor(255, 0);   // Velocidad 255 (Máxima y positiva por lo que avanza) y 0% de giro, por lo que va recto.
/* control.Motor(220, -20); // Velocidad 220 (Positiva por lo que avanza) y giro -20% por lo que va girando levemente a la izquierda.
/* control.Motor(130, 100); // Velocidad 130 (Positivo por lo que avanza) y giro 100, el robot gira sobre su eje.
/* control.Motor(-255, 0);  // Velocidad 255 (Máxima y negativa por lo que retrocede) y 0% de giro, por lo que va recto.
/*
/*************************************************************************************************************************************************/

#ifndef LEANTEC_ControlMotor_h
#define LEANTEC_ControlMotor_h

// Incluimos las librerías necesarias según el arduino que estemos utilizando
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class ControlMotor
{
  public:
    ControlMotor(int MD1,int MD2,int MI1,int MI2,int PWMD,int PWMI);  // Asignamos los pines
    void Motor(int velocidad, int giro);  // Carga los valores en los motores
  private:
    void CalcularVelocidad(int velocidad, int giro, int *vel_izq, int *vel_der );  // Calcula la velocidad de cada motor
    int MotDer1;    // Esta variable la usa internamente la librería para el enable 1 motor derecho
    int MotDer2;    // Esta variable la usa internamente la librería para el enable 2 motor derecho
    int MotIzq1;    // Esta variable la usa internamente la librería para el enable 1 motor izquierdo
    int MotIzq2;    // Esta variable la usa internamente la librería para el enable 2 motor izquierdo
    int pwmD;       // Esta variable la usa internamente la librería para el PWM del motor Derecho
    int pwmI;       // Esta variable la usa internamente la librería para el PWM del motor Izquierdo
};

#endif
