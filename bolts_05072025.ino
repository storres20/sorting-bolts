#define dirPin 8
#define stepPin 9
#define botonHoming 11  // Botón usado para definir posición 0 al iniciar

const int botonPins[6] = {2, 3, 4, 5, 6, 7};
const int posiciones[6] = {0, 67, 133, 200, 267, 333};

int posicionActual = 0;
bool homingCompletado = false;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(botonHoming, INPUT_PULLUP);  // Botón para homing

  for (int i = 0; i < 6; i++) {
    pinMode(botonPins[i], INPUT_PULLUP);
  }

  // 🔁 Iniciar homing manual
  hacerHoming();
}

void loop() {
  if (!homingCompletado) return;  // No hacer nada hasta que se haga homing

  for (int i = 0; i < 6; i++) {
    if (digitalRead(botonPins[i]) == LOW) {
      moverAPosicion(posiciones[i]);
      delay(500);
    }
  }
}

void hacerHoming() {
  digitalWrite(dirPin, LOW);  // Puedes cambiar a HIGH si prefieres otro sentido

  while (digitalRead(botonHoming) == HIGH) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(6000);  // Giro lento
    digitalWrite(stepPin, LOW);
    delayMicroseconds(6000);
  }

  // Botón presionado → se detiene y define posición 0
  posicionActual = 0;
  homingCompletado = true;
  delay(500);  // Evita rebote
}

void moverAPosicion(int nuevaPosicion) {
  int pasos = nuevaPosicion - posicionActual;

  if (pasos < -200) pasos = 400 + pasos;
  else if (pasos > 200) pasos = pasos - 400;

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
