//
#define motorNTH_en    5 //11 
#define motorNTH_in1   2 //12
#define motorNTH_in2   1 //13
#define motorSTH_en    6 //10
#define motorSTH_in3   4 //8
#define motorSTH_in4   3 //9
#define motorEST_en    11 //6
#define motorEST_in1   8 //4 
#define motorEST_in2   9 //3
#define motorWEST_en   10 //5
#define motorWEST_in3  12 //2
#define motorWEST_in4  13 //1
#include <Wire.h>

byte pwm_motor1 = 11, pwm_motor2 = 11, pwm_motor3 = 11, pwm_motor4 = 11;
byte val = 0;
int canal3 = 0, canal4 = 0, canal2 = 0, devolver = 0, PWMNS = 0, PWMEOE = 0, PWGIRO = 0;


void setup() {
  // par de motores Norte/Sur
  pinMode(motorNTH_en,  OUTPUT);
  pinMode(motorNTH_in1, OUTPUT);
  pinMode(motorNTH_in2, OUTPUT);
  pinMode(motorSTH_en,  OUTPUT);
  pinMode(motorSTH_in3, OUTPUT);
  pinMode(motorSTH_in4, OUTPUT);

  // par de motores Este/Oeste
  pinMode(motorEST_en,  OUTPUT);
  pinMode(motorEST_in1, OUTPUT);
  pinMode(motorEST_in2, OUTPUT);
  pinMode(motorWEST_en, OUTPUT);
  pinMode(motorWEST_in3, OUTPUT);
  pinMode(motorWEST_in4, OUTPUT);

  Serial.begin(9600);
  Wire.begin(9);
  Wire.onReceive(leer);
}

void loop() {
  //info_canales();
  escalaPWM();
}




//void info_canales() {
//  Serial.print("  Canal 3:");
//  canal3 = (int) canal3;
//  Serial.print(canal3);
//
//  canal4 = (int) canal4;
//  Serial.print("  Canal 4:");
//  Serial.print(canal4);
//}
//





void escalaPWM() {
//      PWMNS = escala(canal3); // se define el vector de pwm. canal 3 rige a motor Norte y Sur. y canal 4 a Este y Oeste.
//      PWGIRO = escala(canal2);
//    
//      if (PWGIRO < 5) {
//            if (PWMNS > 0) {
//              digitalWrite(motorNTH_in1, HIGH);
//              digitalWrite(motorNTH_in2, LOW);
//              digitalWrite(motorSTH_in4, HIGH);
//              digitalWrite(motorSTH_in3, LOW);
//            } else {
//        
//              digitalWrite(motorNTH_in2, HIGH);
//              digitalWrite(motorNTH_in1, LOW);
//              digitalWrite(motorSTH_in3, HIGH);
//              digitalWrite(motorSTH_in4, LOW);
//            }
//      } else {        
//            if (PWMNS > 0) {
//              digitalWrite(motorNTH_in1, HIGH);
//              digitalWrite(motorNTH_in2, LOW);
//              digitalWrite(motorSTH_in4, LOW);
//              digitalWrite(motorSTH_in3, HIGH);
//            } else {
//        
//              digitalWrite(motorNTH_in2, HIGH);
//              digitalWrite(motorNTH_in1, LOW);
//              digitalWrite(motorSTH_in3, LOW);
//              digitalWrite(motorSTH_in4, HIGH);
//            }
//      }

        PWMNS = escala(canal3); // se define el vector de pwm. canal 3 rige a motor Norte y Sur. y canal 4 a Este y Oeste.
        if (PWMNS > 0) {
          digitalWrite(motorNTH_in1, HIGH);
          digitalWrite(motorNTH_in2, LOW);
          digitalWrite(motorSTH_in4, LOW);
          digitalWrite(motorSTH_in3, HIGH);
        } else {
    
          digitalWrite(motorNTH_in2, HIGH);
          digitalWrite(motorNTH_in1, LOW);
          digitalWrite(motorSTH_in3, LOW);
          digitalWrite(motorSTH_in4, HIGH);
        }
        if (abs(PWMNS) > 10) {
              analogWrite(motorNTH_en, abs(PWMNS));
              analogWrite(motorSTH_en, abs(PWMNS));
        } else {
              analogWrite(motorNTH_en, 0);
              analogWrite(motorSTH_en, 0);
        }

        PWMEOE = escala(canal4);
        if (PWMEOE > 0) {
              digitalWrite(motorEST_in2, HIGH);
              digitalWrite(motorEST_in1, LOW);
              digitalWrite(motorWEST_in3, HIGH);
              digitalWrite(motorWEST_in4, LOW);
        } else {
              digitalWrite(motorEST_in1, HIGH);
              digitalWrite(motorEST_in2, LOW);
              digitalWrite(motorWEST_in4, HIGH);
              digitalWrite(motorWEST_in3, LOW);
        }
        if (abs(PWMEOE) > 10) {
          analogWrite(motorEST_en,  abs(PWMEOE));
          analogWrite(motorWEST_en, abs(PWMEOE));
        } else {
          analogWrite(motorEST_en,  0);
          analogWrite(motorWEST_en, 0);
        }
}






int escala(int solicitud_canal) {
  devolver =  0.51 * (solicitud_canal - 1500.0);
  return devolver;
}







// comunicacion i2c
void leer(int cuantos_bytes) {
      if (cuantos_bytes == 6) {
        canal3 = Wire.read();
        canal3 <<= 8;
        canal3 |= Wire.read();
        
        canal4 = Wire.read();    // receive high byte (overwrites previous reading)
        canal4 = canal4 << 8;    // shift high byte to be high 8 bits
        canal4 |= Wire.read();
        
        canal2 = Wire.read();
        canal2 <<= 8;
        canal2 |= Wire.read();
        
        Serial.println("Canal 4: ");
        Serial.print(canal4);
      }
}
