#define dirPin 8
#define stepPin 9

const int botonPins[6] = {2, 3, 4, 5, 6, 7};
const int posiciones[6] = {0, 67, 133, 200, 267, 333};

int posicionActual = 0;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  for (int i = 0; i < 6; i++) {
    pinMode(botonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < 6; i++) {
    if (digitalRead(botonPins[i]) == LOW) {
      moverAPosicion(posiciones[i]);
      delay(500);
    }
  }
}

void moverAPosicion(int nuevaPosicion) {
  int pasos = nuevaPosicion - posicionActual;

  // 🔁 Movimiento circular optimizado
  if (pasos < -200) {
    pasos = 400 + pasos;
  } else if (pasos > 200) {
    pasos = pasos - 400;
  }

  if (pasos == 0) return;

  digitalWrite(dirPin, pasos > 0 ? HIGH : LOW);

  for (int i = 0; i < abs(pasos); i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

  posicionActual = nuevaPosicion;
}
