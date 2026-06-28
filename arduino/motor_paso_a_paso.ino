 #include <neotimer.h>

int marcha = 2;
int paro = 3;
int emergencia = 4;
int acelerar = 5;
int frenar = 6;
int conmutador_inv = 13;
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;

int vel = 5000;
int valor_vel = 5000;
int flanco_marcha;
int flanco_paro;
int flanco_acelerar;
int flanco_frenar;
int contador = 1;

int marca_bloqueo_marcha;
int marca_bloqueo_marcha_izq;
int marca_bloqueo_paro = 0;
int marca_secuencia_izq = 0;
int marca_secuencia_der = 0;
int marca_cambio;
int vel_paro;
int vel_cambio;
int marca_acel_fre;
int cambio_a_izq = 0;
int cambio_a_der = 0;

Neotimer T1;
Neotimer T2;
Neotimer T3;
Neotimer T4;

void setup() {
  Serial.begin(9600);
  pinMode(marcha, INPUT);
  pinMode(paro, INPUT);
  pinMode(emergencia, INPUT);
  pinMode(acelerar, INPUT);
  pinMode(frenar, INPUT);
  pinMode(conmutador_inv, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  T1.set(vel);
  T2.set(valor_vel);
  T3.set(vel);
  vel_cambio = 100;

}

void loop() {
  if ((digitalRead(marcha) == HIGH) && (flanco_marcha == 0)) {  // MARCHA
    Serial.println("Marcha");
    T1.start();
    T2.start();
    flanco_marcha = 1;
    vel_cambio = 100;
    contador=0;
    if (digitalRead(conmutador_inv) == LOW) {
      marca_bloqueo_marcha = 1;
      marca_secuencia_izq = 1;
      marca_secuencia_der = 0;
      Serial.println("der");
    }
    if (digitalRead(conmutador_inv) == HIGH) {
      marca_bloqueo_marcha = 1;
      marca_secuencia_der = 1;
      marca_secuencia_izq = 0;
      Serial.println("izq");
    }
  }
  if ((digitalRead(marcha) == LOW) && (flanco_marcha == 1)) {
    flanco_marcha = 0;
  }

  if (marca_bloqueo_marcha == 1) {

    if (T1.getEllapsed() <= T1.get()) {
      valor_vel = map(T1.getEllapsed(), 0, T1.get(), vel, vel_cambio);
      T2.set(valor_vel);
    }

    if ((valor_vel) <= vel_cambio) {
      marca_acel_fre = 1;
      //valor_vel = 100;
    }

    if (marca_acel_fre == 1) {

      if ((digitalRead(acelerar) == HIGH) && (flanco_acelerar == 0) && (valor_vel < 190)) {  //FRENAR
        valor_vel = valor_vel + 10;
        flanco_acelerar = 1;
        Serial.println("Frenar");
        Serial.println(valor_vel);
      }

      if ((digitalRead(acelerar) == LOW) && (flanco_acelerar = 1)) {
        flanco_acelerar = 0;
      }

      if ((digitalRead(frenar) == HIGH) && (flanco_frenar == 0) && (valor_vel > 10)) {  //ACELERAR
        valor_vel = valor_vel - 10;
        flanco_frenar = 1;
        Serial.println("Acelerar");
        Serial.println(valor_vel);
      }

      if ((digitalRead(frenar) == LOW) && (flanco_frenar = 1)) {
        flanco_frenar = 0;
      }
    }
  }

    if (digitalRead(emergencia) == HIGH) {  // EMERGENCIA
      Serial.println("Emergencia");
      marca_bloqueo_marcha = 0;
      marca_bloqueo_paro = 0;
      valor_vel = 5000;
      marca_secuencia_izq = 0;
      marca_secuencia_der = 0;
      marca_acel_fre = 0;
      cambio_a_der = 0;
      cambio_a_izq = 0;
      vel_cambio = 100;
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
  }

    if ((digitalRead(paro) == HIGH) && (flanco_paro == 0) && ((marca_bloqueo_paro == 0) || (marca_cambio == 1))) {    //PARO
    Serial.println("Paro");
    flanco_paro = 1;
    marca_bloqueo_paro = 1;
    marca_bloqueo_marcha = 0;
    marca_acel_fre = 0;
    vel_paro = valor_vel;
    T3.start();
    T2.start();
    marca_cambio = 0;
  }

    if ((digitalRead(paro) == LOW) && (flanco_paro == 1)) {
    flanco_paro = 0;
  }

  if ((cambio_a_der == 1) || (cambio_a_izq == 1)){  //CAMBIO GIRO
    Serial.println("Cambio de giro");
    marca_bloqueo_paro = 1;
    marca_bloqueo_marcha = 0;
    marca_acel_fre = 0;
    vel_paro = valor_vel;
    vel_cambio = vel_paro;
    T3.start();
    T2.start();
    cambio_a_der = 0;
    cambio_a_izq = 0;
    marca_cambio = 1;
  }

    if ((marca_bloqueo_paro) == 1) {

    if (T3.getEllapsed() <= T3.get()) {
      valor_vel = map(T3.getEllapsed(), 0, T3.get(), vel_paro, vel);
      Serial.println(valor_vel);
    }

    if ((valor_vel) >= 4990) {
      marca_bloqueo_paro = 0;
      marca_secuencia_izq = 0;
      marca_secuencia_der = 0;
      valor_vel = 5000;
      if (marca_cambio == 1) {
        if (digitalRead(conmutador_inv) == HIGH) {
          marca_secuencia_der = 1;
          T1.start();
          T2.start();
          marca_bloqueo_marcha = 1;
        }
        else if (digitalRead(conmutador_inv) == LOW) {
          marca_secuencia_izq = 1;
          T1.start();
          T2.start();
          marca_bloqueo_marcha = 1;
        }
      }
    }

  }

    if ((marca_secuencia_izq) == 1) {

    
      if (T2.repeat()) {  // SECUENCIA
      T2.set(valor_vel);
      contador++;
    }

      if (contador == 1) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      //Serial.println("IN1");
    }

      else if (contador == 2) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      //Serial.println("IN2");
    }

      else if (contador == 3) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      //Serial.println("IN3");
    }

      else if (contador == 4) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      contador = 0;
      //Serial.println("IN4");
    }
    if ((digitalRead(conmutador_inv) == HIGH) && (marca_bloqueo_paro == 0)) {
      cambio_a_der = 1;
      Serial.println("Cambio a der");
    }
  }

  if ((marca_secuencia_der) == 1) {

    
      if (T2.repeat()) {  // SECUENCIA
      T2.set(valor_vel);
      contador++;
    }

      if (contador == 1) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      //Serial.println("IN4");
    }

      else if (contador == 2) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      //Serial.println("IN3");
    }

      else if (contador == 3) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      //Serial.println("IN2");
    }

      else if (contador == 4) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      //Serial.println("IN1");
      contador = 0;
    }
    if ((digitalRead(conmutador_inv) == LOW) && (marca_bloqueo_paro == 0)) {
      cambio_a_izq = 1;
      Serial.println("Cambio a der");
    }
  }
  //Serial.println(vel_cambio);
}
