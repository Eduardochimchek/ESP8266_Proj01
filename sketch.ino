// Defina os pinos dos LEDs RGB
#define RED_PIN D8
#define GREEN_PIN D9
#define BLUE_PIN D10

// Defina os pinos dos botões
#define BUTTON_GREEN D3
#define BUTTON_BLUE D4

// Defina as variáveis para armazenar o estado dos botões
bool greenButtonState = false;
bool blueButtonState = false;
bool lastGreenButtonState = false;
bool lastBlueButtonState = false;
bool blueLedState = false;
bool redLedBlink = true;

// Defina as variáveis para controlar o tempo
unsigned long previousMillis = 0;
const long interval = 200;

void setup() {
  // Inicialize os pinos como saídas
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Inicialize os pinos dos botões como entradas com resistência de pull-up interna
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);

  // Inicie a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Verifique se o botão verde foi pressionado
  greenButtonState = digitalRead(BUTTON_GREEN);
  if (greenButtonState != lastGreenButtonState) {
    if (greenButtonState == LOW) {
      digitalWrite(GREEN_PIN, HIGH); // Ligar LED verde quando o botão é pressionado
      redLedBlink = false; // Parar de piscar o LED vermelho
    } else {
      digitalWrite(GREEN_PIN, LOW); // Desligar LED verde quando o botão é solto
      redLedBlink = true; // Voltar a piscar o LED vermelho
    }
    delay(50);
  }
  lastGreenButtonState = greenButtonState;

  // Verifique se o botão azul foi pressionado
  blueButtonState = digitalRead(BUTTON_BLUE);
  if (blueButtonState != lastBlueButtonState) {
    if (blueButtonState == LOW) {
      blueLedState = !blueLedState; // Inverter o estado do LED azul quando o botão é pressionado
      redLedBlink = !redLedBlink; // Desligar o LED vermelho quando o botão azul é pressionado
    }
    delay(50);
  }
  lastBlueButtonState = blueButtonState;

  // Atualizar o estado do LED azul
  digitalWrite(BLUE_PIN, blueLedState);

  // Faça o LED vermelho piscar se nenhum botão estiver sendo pressionado
  if (redLedBlink) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(RED_PIN, !digitalRead(RED_PIN));
    }
  }
}
