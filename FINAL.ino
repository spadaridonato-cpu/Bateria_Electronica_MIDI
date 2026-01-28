const int hithat = A8; //piezoelectrico
const int redo = A9; //piezoelectrico
const int bombo = A10; //piezoelectrico
const int crash1 = A11; //piezoelectrico
const int crash2 = A12; //piezoelectrico
const int ride = A13; //piezoelectrico
const int tom1 = A14; //piezoelectrico
const int tom2 = A15; //piezoelectrico
const int tompiso = A7; //piezoelectrico


int threshold = 160;            // umbral para ignorar golpes débiles
int velocityMax = 80;           // velocidad máxima en MIDI
int velocityMin = 3;            // golpes suaves suenen más fuerte
int debounceTime = 50;          // evitar múltiples lecturas (en ms)
unsigned long lastHitTime = 0;  // último golpe registrado

const int hallPin = 3;  // sensor de efecto Hall
bool hallDetected = false;

void setup() {
  pinMode(hithat, INPUT);
  pinMode(redo, INPUT);
  pinMode(bombo, INPUT);
  pinMode(crash1, INPUT);
  pinMode(crash2, INPUT);
  pinMode(ride, INPUT);
  pinMode(tom1, INPUT);
  pinMode(tom2, INPUT);
  pinMode(tompiso, INPUT);
  pinMode(hallPin, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(hithat);  // Leemos el valor del piezoeléctrico
  unsigned long currentTime = millis();


  if (sensorValue > threshold && (currentTime - lastHitTime > debounceTime)) {
    int velocity = map(sensorValue, threshold, 1023, velocityMin, velocityMax);
    velocity = constrain(velocity, velocityMin, velocityMax);
    hallDetected = digitalRead(hallPin);

    if (hallDetected) {
      sendNoteOn(54, velocity);  // envía la nota 54 del MIDI (HitHat cerrado) si el imán está cerca
      delay(10);
      sendNoteOff(54, 0);
    } else {
      sendNoteOn(58, velocity);   // enviamos la señal MIDI (58 = HitHat abierto)
      delay(10);                
      sendNoteOff(58, 0);
      lastHitTime = currentTime;
    }
  }
  // Redoblante (A1)
  sensorValue = analogRead(redo);
  if (sensorValue > threshold && (currentTime - lastHitTime > debounceTime)) {
    int velocity = map(sensorValue, threshold, 1023, velocityMin, velocityMax);
    velocity = constrain(velocity, velocityMin, velocityMax);
    sendNoteOn(50, velocity);  // Enviamos la señal MIDI (Redoblante)
    delay(10);
    sendNoteOff(50, 0);        
    lastHitTime = currentTime;  
  }


  // Bombo (A2)
  sensorValue = analogRead(bombo);  //Bombo
  if (sensorValue > threshold && (currentTime - lastHitTime > debounceTime)) {
    int velocity = map(sensorValue, threshold, 1023, velocityMin, velocityMax);
    velocity = constrain(velocity, velocityMin, velocityMax);
    sendNoteOn(48, velocity);  // Enviamos la señal MIDI (Bombo)
    delay(10);
    sendNoteOff(48, 0);        
    lastHitTime = currentTime;  
  }

  // Crash 1 (A3)
  sensorValue = analogRead(crash1);  //Crash 1
  if (sensorValue > threshold && (currentTime - lastHitTime > debounceTime)) {
    int velocity = map(sensorValue, threshold, 1023, velocityMin, velocityMax);
    velocity = constrain(velocity, velocityMin, velocityMax);
    sendNoteOn(61, velocity);  // Enviamos la señal MIDI (Crash 1)
    delay(10);
    sendNoteOff(61, 0);        
    lastHitTime = currentTime;  
  }

  // Crash 2 (A4)
  sensorValue = analogRead(crash2);  //Crash 2
  if (sensorValue > threshold && (currentTime - lastHitTime > debounceTime)) {
    int velocity = map(sensorValue, threshold, 1023, velocityMin, velocityMax);
    velocity = constrain(velocity, velocityMin, velocityMax);
    sendNoteOn(67, velocity);  // Enviamos la señal MIDI (Crash 2)
    delay(10);
    sendNoteOff(67, 0);        
    lastHitTime = currentTime;  
  }

  //Ride (A5)
  sensorValue = analogRead(ride);  //Ride
  if (sensorValue > threshold && (currentTime - lastHitTime > debounceTime)) {
    int velocity = map(sensorValue, threshold, 1023, velocityMin, velocityMax);
    velocity = constrain(velocity, velocityMin, velocityMax);
    sendNoteOn(63, velocity);  // Enviamos la señal MIDI (Ride)
    delay(10);
    sendNoteOff(63, 0);        
    lastHitTime = currentTime;  // Actualizamos el tiempo del último golpe
  }

  //tom1 (A6)
  sensorValue = analogRead(tom1);  //Ride
  if (sensorValue > threshold && (currentTime - lastHitTime > debounceTime)) {
    int velocity = map(sensorValue, threshold, 1023, velocityMin, velocityMax);
    velocity = constrain(velocity, velocityMin, velocityMax);
    sendNoteOn(55, velocity);  // Enviamos la señal MIDI (Ride)
    delay(10);
    sendNoteOff(55, 0);        
    lastHitTime = currentTime;  // Actualizamos el tiempo del último golpe
  }

    //tom2 (A7)
  sensorValue = analogRead(tom2);  //Ride
  if (sensorValue > threshold && (currentTime - lastHitTime > debounceTime)) {
    int velocity = map(sensorValue, threshold, 1023, velocityMin, velocityMax);
    velocity = constrain(velocity, velocityMin, velocityMax);
    sendNoteOn(60, velocity);  // Enviamos la señal MIDI (Ride)
    delay(10);
    sendNoteOff(60, 0); 
    lastHitTime = currentTime;  // Actualizamos el tiempo del último golpe
  }

    //tompiso (A8)
  sensorValue = analogRead(tompiso);  //Ride
  if (sensorValue > threshold && (currentTime - lastHitTime > debounceTime)) {
    int velocity = map(sensorValue, threshold, 1023, velocityMin, velocityMax);
    velocity = constrain(velocity, velocityMin, velocityMax);
    sendNoteOn(57, velocity);  // Enviamos la señal MIDI (Ride)
    delay(10);
    sendNoteOff(57, 0); 
    lastHitTime = currentTime;  
  }
}

// Función para enviar la señal de Note On
void sendNoteOn(byte pitch, byte velocity) {
  Serial.write(0x90);      // Note On en el canal 1
  Serial.write(pitch);     // Nota MIDI
  Serial.write(velocity);  // Intensidad del golpe
}

// Función para enviar la señal de Note Off
void sendNoteOff(byte pitch, byte velocity) {
  Serial.write(0x80);      // Note Off en el canal 1
  Serial.write(pitch);     // Nota MIDI
  Serial.write(velocity);  // Intensidad 0 para apagar la nota
}