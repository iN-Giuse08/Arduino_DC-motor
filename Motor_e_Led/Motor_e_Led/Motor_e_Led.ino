// Definizione del pin di controllo del motore
const int motorPin = 3; // Pin per il controllo del motore

// Definizione dei pin di controllo dei LED
const int ledPin1 = 4; // Pin per il primo LED
const int ledPin2 = 5; // Pin per il secondo LED
const int ledPin3 = 6; // Pin per il terzo LED
const int ledPin4 = 7; // Pin per il quarto LED

void setup() {
  // Inizializza la comunicazione seriale a 9600 bps
  Serial.begin(9600);
  
  // Imposta i pin del motore e dei LED come output
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) { // Verifica se ci sono dati disponibili sulla porta seriale
    String command = Serial.readStringUntil('\n'); // Leggi il comando fornito tramite il monitor seriale
    
    if (command == "stop") { // Se il comando è "stop"
      // Ferma il motore e spegni i LED
      analogWrite(motorPin, 0);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);
      
      Serial.println("Motore e LED fermati.");
    } else { // Altrimenti, se il comando è un numero
      int intensity = command.toInt(); // Converti il comando in un numero
      
      // Assicura che l'intensità sia compresa tra 0 e 255
      if (intensity >= 0 && intensity <= 255) {
        // Accendi il motore con l'intensità fornita
        analogWrite(motorPin, intensity);
        
        // Accendi i LED in base all'intensità fornita
        if (intensity >= 0 && intensity <= 120) {
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, LOW);
          digitalWrite(ledPin3, LOW);
          digitalWrite(ledPin4, LOW);
        } else if (intensity > 120 && intensity <= 150) {
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin3, LOW);
          digitalWrite(ledPin4, LOW);
        } else if (intensity > 150 && intensity <= 200) {
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin3, HIGH);
          digitalWrite(ledPin4, LOW);
        } else {
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin3, HIGH);
          digitalWrite(ledPin4, HIGH);
        }
        
        // Stampa l'intensità sulla porta seriale
        Serial.print("Intensita' impostata a: ");
        Serial.println(intensity);
      } else {
        // Se l'intensità non è compresa tra 0 e 255, stampa un messaggio di errore
        Serial.println("Errore: l'intensita' deve essere compresa tra 0 e 255");
      }
    }
  }
}
