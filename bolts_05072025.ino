#define dirPin 8
#define stepPin 9

const int botonPins[6] = {2, 3, 4, 5, 6, 7};  // Pines para los botones
const int posiciones[6] = {0, 67, 133, 200, 267, 333}; // Posiciones en pasos

int posicionActual = 0;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  for (int i = 0; i < 6; i++) {
    pinMode(botonPins[i], INPUT_PULLUP);  // Usamos INPUT_PULLUP
  }
}

void loop() {
  for (int i = 0; i < 6; i++) {
    if (digitalRead(botonPins[i]) == LOW) {
      moverAMotor(posiciones[i]);
      delay(500); // Evitar múltiples lecturas por rebote
    }
  }
}

void moverAMotor(int nuevaPosicion) {
  int pasos = nuevaPosicion - posicionActual;

  if (pasos == 0) return;  // Ya está en la posición

  // Dirección: HIGH si va en sentido horario
  digitalWrite(dirPin, pasos > 0 ? HIGH : LOW);

  for (int i = 0; i < abs(pasos); i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);  // Puedes ajustar la velocidad aquí
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }

  posicionActual = nuevaPosicion;
}
