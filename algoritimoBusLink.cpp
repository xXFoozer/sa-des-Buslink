#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd(0);

const int PIN_ECHO = 5;
const int PIN_TRIGG = 6;
const int PIN_PING = 3;
const float VALOR_REFERENCIA_HC= 0.01723;
const int NEXT =9 ;
const int PREV =8 ;

bool objetoPresente = false;
bool objetoPresente2 = false;


int qtaDoDia = 0;
int qtaDoDia2 = 0; 
int qtaAtualPessoas = 0;

int nextState = 0;
int prevState = 0;
int tela = 0;
int lotado = 50;
int test = 0;




void setup(){
	Serial.begin(9600);
    pinMode(8, INPUT);
  	pinMode(9, INPUT);
	pinMode(PIN_TRIGG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
	pinMode(2,OUTPUT);
	
  
 
  lcd.begin(16,2);
}

void loop(){
   nextState = digitalRead(NEXT);
   prevState = digitalRead(PREV);
   
   if(nextState == HIGH){
  	tela++;
    if(tela >= 5){
		tela = 4;
    }}
    if(prevState == HIGH){
  	tela--;
    if(tela < 0){
		tela = 0;
    }}
  mostrar();
  sensorPing(); 
  sensorHC();
  valorPerdido(); 
  passageirosPerdidos(); 
  valorArrecadado();
  destinoLinha();
  
  
  
  test = digitalRead(2);
  //Serial.println(test);
  
}



void sensorHC(){
   digitalWrite(PIN_TRIGG, HIGH);
   delayMicroseconds(10);
   digitalWrite(PIN_TRIGG, LOW);
   long duracao = pulseIn(PIN_ECHO, HIGH);
  
   float distancia = VALOR_REFERENCIA_HC * duracao;
   
  if(distancia < 330 && objetoPresente == false){
      objetoPresente = true;
   
  }else if(distancia >= 330 && objetoPresente == true){
      objetoPresente = false;
      qtaAtualPessoas--;
      
  }
  
}



void sensorPing(){
  	pinMode(PIN_PING, OUTPUT);
	digitalWrite(PIN_PING, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(PIN_PING, LOW);
  	pinMode(PIN_PING, INPUT);
  	long duracao = pulseIn(PIN_PING, HIGH);
  		
  	float distancia =VALOR_REFERENCIA_HC * duracao;
	
    if(distancia < 330&& objetoPresente2 == false) {
		objetoPresente2 = true;
    }else if(distancia >= 330 && objetoPresente2 == true) {
    	objetoPresente2 = false;
       	qtaAtualPessoas++;
      	qtaDoDia++;
        qtaDoDia2++;
    }
}

int valorPerdido(){
  int perdendo = 0;
  if(qtaDoDia > lotado && lotado == perdendo){
  	perdendo +5;
  }

}

int destinoLinha(){
  if(qtaDoDia > lotado){
   	lcd.setCursor(0,1);
    lcd.print("troque");
  }else if(qtaDoDia == lotado){
    lcd.setCursor(0,1);
    lcd.print("manter");
  }else if (qtaDoDia < lotado){
  	lcd.setCursor(0,1);
    lcd.print("diminuir");
  }





}




int passageirosPerdidos(){
  int passouLimite = qtaDoDia;
  if(qtaDoDia > lotado){
    passouLimite++;
  }
 return passouLimite; 
}

int valorArrecadado(){
   int valor = qtaDoDia*5;
  if(test == HIGH){
    int valorCrianca= 0;
    
    valorCrianca = qtaDoDia2*3;
    
    
    Serial.println(valorCrianca);
    return valorCrianca;
  }
  
   Serial.println(valor);
 
   return valor;

}

 void mostrar(){
  if(tela == 0) {
    lcd.setCursor(1,0);
    lcd.print("Passageiros");
    lcd.setCursor(1,1);
    lcd.print(":" + String(qtaDoDia));
    delay(1500);
    lcd.noBlink();
    lcd.clear();
    
  }else if(tela == 1){
    lcd.setCursor(1,0);
    lcd.print("ValorArrecadado");
    lcd.setCursor(1,1);
    lcd.print(valorArrecadado());
    delay(1500);
    lcd.noBlink();
    lcd.clear();
    
  }else if(tela == 2) {
  	lcd.setCursor(1,0);
    lcd.print("Pass.Perdidos");
    lcd.setCursor(1,1);
    lcd.print(":"+ passageirosPerdidos());
    delay(1500);
    lcd.noBlink();
    lcd.clear();
    
  }else if(tela == 3) {
  	lcd.setCursor(1,0);
    lcd.print("Valor Perdido");
    lcd.setCursor(1,1);
    lcd.print(":" + valorPerdido());
    delay(1500);
    lcd.noBlink();
    lcd.clear();
    
  } if(tela == 4) {
    delay(10000);
  	lcd.setCursor(1,0);
    lcd.print("destinoLinha");
    lcd.setCursor(1,1);
    lcd.print(destinoLinha());
    delay(1500);
    lcd.noBlink();
    lcd.clear();
    
  
  }
}	
 