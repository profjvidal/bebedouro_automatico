#include <Servo.h>
Servo servoMain; // Define Servo motor
//Pinos de conexão do sensor ultrassônico
#define trigPin  10
#define echoPin 11

int range = 5; // Alcance em polegadas

void setup() {
  // Inicializa comunicação serial:
  Serial.begin(9600);
  // Inicializa a comunicação entre o servo e o pino digital ao qual o servo está conectado.
  servoMain.attach(9); 
  // Inicializa a comunicação entre o sensor ultrassônico e os pinos digitais ao qual o sensor está conectado.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  // estabelecer variáveis ​​para duração do pulso de som,
  // e o resultado da distância medido em polegadas e centímetros:
  long duracao, polegadas, cm;

  // O pulso de som))) é acionado por um pulso ALTO de 2 ou mais microssegundos.
  // Define o pino de controle do trigger (pino de disparo do sensor) para o nível lógico BAIXO. 
  // Isso é feito para garantir que o sensor comece em um estado de inatividade, eliminando possíveis sinais residuais.
  digitalWrite(trigPin, LOW);
  // Aguarda 2 microssegundos (um microssegundo é um milionésimo de segundo). 
  // Essa pequena pausa é para garantir que o sensor reconheça corretamente a transição para o estado BAIXO antes de disparar o pulso em ALTO.
  delayMicroseconds(2);
  // Define o pino de trigger para o nível lógico ALTO, o que faz o sensor ultrassônico emitir o pulso de som. Esse pulso é enviado pelo sensor para medir a distância.
  digitalWrite(trigPin, HIGH);
  // Aguarda 5 microssegundos para garantir que o pulso no estado ALTO seja longo o suficiente para ser reconhecido pelo sensor.
  delayMicroseconds(5);
  // Define o pino de trigger novamente para o nível lógico BAIXO, encerrando o pulso. 
  // Isso significa que o pulso de som foi enviado pelo sensor, e agora ele estará pronto para esperar o sinal de retorno (eco) para calcular a distância.
  digitalWrite(trigPin, LOW);

  // Realiza a leitura no pino echo
  duracao = pulseIn(echoPin, HIGH);

  // Converte o tempo do eco (medido em microssegundos) em distância
  polegadas = microssegundosParaPolegadas(duracao);
  cm = microssegundosParaCentemetro(duracao);
  
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();

  if(polegadas < 5)
  {
   Serial.println("Copo identificado!");
   servoMain.write(90);  // Gira o Servo de volta para a posição central (90 graus)
   delay(7000); 
  }
  else{
   Serial.println("Nenhum copo identificado!");
   servoMain.write(0);
   delay(50);
   }
  delay(200);
}

long microssegundosParaPolegadas(long microssegundos)
{
  return microssegundos / 74 / 2;
}

long microssegundosParaCentemetro(long microssegundos)
{
  // A velocidade do som é 340 m/s ou 29 microssegundos por centímetro.
  // O pulso vai até o objeto e volta, então a distância real é metade do percurso total medido.
  return microssegundos / 29 / 2;
}
