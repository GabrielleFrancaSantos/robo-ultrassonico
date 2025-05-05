
// Definindo os pinos dos motores
#define motorDF 7   // Motor direito na frente
#define motorDT 6   // Motor direito atrás
#define motorEF 9   // Motor esquerdo na frente
#define motorET 8   // Motor esquerdo atrás

// Definindo os pinos para controlar a velocidade
#define velocidade1 10
#define velocidade2 5

// Definindo os pinos do sensor ultrassônico
#define trig 11
#define echo 12

// Definindo o pino para a buzina
#define buzina 4

// Definindo os pinos dos LEDs
#define led_verde 2
#define led_vermelho A4

// Variáveis para o sensor ultrassônico
long duration; // Duração do pulso ultrassônico
int distance;  // Distância medida pelo ultrassônico

// Definindo os pinos dos sensores de linha
#define sensor_direita 3
#define sensor_esquerda 13

// Função para mover os motores para frente
void andar() {
  digitalWrite(motorDF, HIGH); // Motor direito frente ligado
  digitalWrite(motorDT, LOW);
  digitalWrite(motorEF, HIGH); // Motor esquerdo frente ligado
  digitalWrite(motorET, LOW);
}

// Função para parar os motores
void parar() {
  digitalWrite(motorDF, LOW); 
  digitalWrite(motorDT, LOW); 
  digitalWrite(motorEF, LOW); 
  digitalWrite(motorET, LOW);
}

// Função para ajustar a direção do robô para a esquerda
void ajustar_esquerda() {
  digitalWrite(motorEF, LOW);
  digitalWrite(motorDF, HIGH);
}

// Função para ajustar a direção do robô para a direita
void ajustar_direita() {
  digitalWrite(motorEF, HIGH);
  digitalWrite(motorDF, LOW);
}

// Função para ajustar a velocidade dos motores
void velocidade(int vel) {
  analogWrite(velocidade1, vel);
  analogWrite(velocidade2, vel);
}

// Função para indicar que algo foi detectado
void detectar() {
  digitalWrite(led_vermelho, HIGH);
  delay(100);
  digitalWrite(led_vermelho, LOW);
}

// Função para indicar que nada foi detectado
void nao_detectar() {
  digitalWrite(led_verde, HIGH);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(buzina, HIGH);
}

// Função para ativar a buzina por 100ms
void buzinar() {
  digitalWrite(buzina, LOW);
  delay(100);
  digitalWrite(buzina, HIGH);
}

void setup() {
  parar();
  delay(5000);
  velocidade(98);
  digitalWrite(buzina, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_verde, LOW);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  pinMode(motorDF, OUTPUT);
  pinMode(motorDT, OUTPUT);
  pinMode(motorEF, OUTPUT);
  pinMode(motorET, OUTPUT);
  pinMode(sensor_direita, INPUT);
  pinMode(sensor_esquerda, INPUT);
  pinMode(buzina, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_verde, OUTPUT);
}

void loop() {
  int leitura_direita = digitalRead(sensor_direita);
  int leitura_esquerda = digitalRead(sensor_esquerda);

  if (leitura_direita == LOW && leitura_esquerda == HIGH) {
    ajustar_direita();
  } else if (leitura_esquerda == LOW && leitura_direita == HIGH) {
    ajustar_esquerda();
  } else if (leitura_direita == HIGH && leitura_esquerda == HIGH) {
    andar();
  } else {
    parar();
  }

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= 10) {
    parar();
    buzinar();
    detectar();
  } else {
    nao_detectar();
  }
}
