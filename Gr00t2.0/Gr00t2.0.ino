class DCMotor {  
  int spd = 150, pin1, pin2;
  
  public:    
    void Pinout(int in1, int in2){ // Pinout é o método para a declaração dos pinos que vão controlar o objeto motor
      pin1 = in1;
      pin2 = in2;
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
    }   
    
    void Speed(int in1){ // Speed é o método que irá ser responsável por salvar a velocidade de atuação do motor
      spd = in1;
    }     
    
    void Forward(){ // Forward é o método para fazer o motor girar para frente
      analogWrite(pin1, spd);
      digitalWrite(pin2, LOW);
    }   
    
    void Backward(){ // Backward é o método para fazer o motor girar para trás
      digitalWrite(pin1, LOW);
      analogWrite(pin2, spd);
    }
    
    void Stop(){ // Stop é o metodo para fazer o motor ficar parado.
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
    }
};

int gatilho = 11, echo = 10, luzEsq = 8, luzDir = 9;
float tempo, dist;
bool estadoSensorEsq, estadoSensorDir;

DCMotor Motor1, Motor2; // Criação de dois objetos motores 

void setup() {
  Serial.begin(9600);  
  pinMode(gatilho, OUTPUT);
  digitalWrite(gatilho,LOW);
  delayMicroseconds(10);
  pinMode(echo, INPUT);
  pinMode(luzEsq, INPUT);
  pinMode(luzDir, INPUT);

  Motor1.Pinout(7,6); // Seleção dos pinos que cada motor usará
  Motor2.Pinout(4,5); 
}

void loop() {
    Motor1.Forward();
    Motor2.Forward();
    
  /*if (Ultrassonico() <= 10.0){
    Motor1.Speed(255); // A velocidade do motor pode variar de 0 a 255, onde 255 é a velocidade máxima.
    Motor2.Speed(255);
    Motor1.Forward(); //Comando para ir para frente
    Motor2.Forward();
  } else {  
    Motor1.Speed(50); // A velocidade do motor pode variar de 0 a 255, onde 255 é a velocidade máxima.
    Motor2.Speed(50);
    Motor1.Forward(); // Se ele não estiver numa dist menor igual a 10, ele vai continuar andando, porém numa velocidade reduzida
    Motor2.Forward();
  }
    Motor1.Forward();
    Motor2.Forward();*/
    if(lerLuzEsq() == 0){ // Comando para o motor parar
    Motor1.Stop();
    Motor2.Stop();
    delay(50);
    //Motor1.Backward(); //Ele vai dar ré, parar rapidao, virar para direita e voltar ao looping
    //Motor2.Backward();
    //delay(50);
    //Motor1.Forward();
    //Motor2.Backward();
  } 

  
}

  /*girar para direita
  Motor1.Forward();
  Motor2.Backward();
  delay(1000);
  
  girar para esquerda
  Motor1.Backward();
  Motor2.Forward();
  delay(1000);
  
  Motor1.Backward(); // Comando para o motor ir para trás
  Motor2.Backward();
  delay(1000);
*/
  


float Ultrassonico(){
  digitalWrite(gatilho, HIGH);
  delayMicroseconds(10);
  digitalWrite(gatilho, LOW);

  // medir tempo de ida e volta do pulso ultrassônico
  tempo = pulseIn(echo, HIGH);
  // calcular as distâncias em centímetros e polegadas
  dist = (tempo/29.4)/2;
  Serial.println(dist);
  // aguardar um pouquinho antes de começar tudo de novo
  delayMicroseconds(600);
  return dist; 
}

int lerLuzEsq() {
  estadoSensorEsq = digitalRead(luzEsq);
  if(estadoSensorEsq) {
    Serial.println(1); // Ler Preto
    return 1;
  } else {
    Serial.println(0); // Ler Branco
    return 0;
  }
}

int lerLuzDir() {
  estadoSensorDir = digitalRead(luzDir);
  if(estadoSensorDir) {
    Serial.println(1); preto 
    return 1;
  } else {
    Serial.println(0); // Branco
    return 0;
  }
}