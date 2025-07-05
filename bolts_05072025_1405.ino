#define dirPin 8
#define stepPin 9
#define botonHoming 11  // Botón para homing

const int posiciones[6] = {0, 67, 133, 200, 267, 333};

int posicionActual = 0;
bool homingCompletado = false;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(botonHoming, INPUT_PULLUP);
  Serial.begin(9600);

  hacerHoming();
}

void loop() {
  if (!homingCompletado) return;

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    int nuevaPos = input.toInt();

    if (nuevaPos >= 0 && nuevaPos <= 5) {
      moverAPosicion(posiciones[nuevaPos]);
    }
  }
}

void hacerHoming() {
  digitalWrite(dirPin, LOW);

  while (digitalRead(botonHoming) == HIGH) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(6000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(6000);
  }

  posicionActual = 0;
  homingCompletado = true;
  delay(500);
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

  // ✅ Respuesta al Python
  Serial.print("Movido a posicion: ");
  Serial.println(nuevaPosicion);
}

