class DCMotor {  
  int spd = 150, pin1, pin2;
  
  public:    
  //Pinout: metodo para a declaração dos pinos que vão controlar o objeto motor
    void Pinout(int in1, int in2) { 
      pin1 = in1;
      pin2 = in2;
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
    }   
  //Speed: metodo que irá ser responsável por salvar a velocidade de atuação do motor
    void Speed(int in1) {
      spd = in1;
    }     
  //Forward: metodo para fazer o motor girar para frente
    void Forward() {
      analogWrite(pin1, spd);
      digitalWrite(pin2, LOW);
    }   
  //Backward: metodo para fazer o motor girar para trás  
    void Backward() { 
      digitalWrite(pin1, LOW);
      analogWrite(pin2, spd);
    }
  //Stop: metodo para fazer o motor ficar parado  
    void Stop() { 
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
    }
  //ToTurn: metodo para fazer o robo girar
    void ToTurn(String direction, int time) {
      if(direction == "Esquerda") {
      //Girar para a esquerda
        analogWrite(pin1, 0);
        analogWrite(pin2, spd);
        delay(time);
        Stop();
      } else if(direction == "Direita") {
      //Girar para a direita
        analogWrite(pin1, spd);
        analogWrite(pin2, 0);
        delay(time);
        Stop();
      } else {
      //Direção inválida
        Serial.println("Use 'Esquerda' ou 'Direita'");
      }
    } 
};

int gatilho = 11, echo = 10, luzEsq = 8, luzDir = 9;
float tempo, dist;
bool estadoSensorEsq, estadoSensorDir;

//Criação de dois objetos motores
DCMotor Motor1, Motor2;  

void setup() {
  Serial.begin(9600);  
  pinMode(gatilho, OUTPUT);
  digitalWrite(gatilho,LOW);
  delayMicroseconds(10);
  pinMode(echo, INPUT);
  pinMode(luzEsq, INPUT);
  pinMode(luzDir, INPUT);
//Seleção dos pinos que cada motor usará
  Motor1.Pinout(7,6); 
  Motor2.Pinout(4,5); 
}

void loop() {
    Motor1.Forward();
    Motor2.Forward();
    
    /*if (Ultrassonico() <= 10.0){
      Motor1.Speed(255); //A velocidade do motor pode variar de 0 a 255, onde 255 é a velocidade máxima.
      Motor2.Speed(255);
      Motor1.Forward(); //Comando para ir para frente
      Motor2.Forward();
    } 
    else {  
      Motor1.Speed(50); //A velocidade do motor pode variar de 0 a 255, onde 255 é a velocidade máxima.
      Motor2.Speed(50);
      Motor1.Forward(); //Se ele não estiver numa dist menor igual a 10, ele vai continuar andando, porém numa velocidade reduzida
      Motor2.Forward();
    }
    Motor1.Forward();
    Motor2.Forward();*/
    if(!lerLuzEsq()){ //Comando para o motor parar
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

/*
  girar para direita
  Motor1.Forward();
  Motor2.Backward();
  delay(1000);
  
  girar para esquerda
  Motor1.Backward();
  Motor2.Forward();
  delay(1000);
  
//Comando para o motor ir para trás
  Motor1.Backward();
  Motor2.Backward();
  delay(1000);
*/
  
float Ultrassonico(){
  digitalWrite(gatilho, HIGH);
  delayMicroseconds(10);
  digitalWrite(gatilho, LOW);

//medir tempo de ida e volta do pulso ultrassônico
  tempo = pulseIn(echo, HIGH);

//calcular as distâncias em centímetros e polegadas
  dist = (tempo/29.4)/2;
  Serial.println(dist);

//aguardar um pouquinho antes de começar tudo de novo
  delayMicroseconds(600);
  return dist; 
}

//Retorna *True* se o sensor detectar *Preto* e *False* se detectar *Branco*
bool lerLuzEsq() {
  bool estadoSensorEsq = digitalRead(luzEsq);
  #ifdef DEBUG
  Serial.print("Sensor Esquerdo: ");
  Serial.println(estadoSensorEsq ? "Preto" : "Branco");
  #endif
  return estadoSensorEsq;
}
bool lerLuzDir() {
  bool estadoSensorDir = digitalRead(luzDir);
  #ifdef DEBUG
  Serial.print("Sensor Direito: ");
  Serial.println(estadoSensorDir ? "Preto" : "Branco");
  #endif
  return estadoSensorDir;
}