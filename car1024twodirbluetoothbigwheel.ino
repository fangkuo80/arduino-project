char junk;
String inputString="";
const int stepPin = 3; 
const int dirPin = 4; //moter left direction
const int stepPina = 5; 
const int dirPina = 6; //motor right direction
const int dirl = 2; //left sensor normal HIGH 
const int dirr = 12; //right sensor normal HIGH 
const int dirf = 7; //forword
const int dirb = 8; //backword
const int stopbt = 13; //motor controller ON:HIGH/OFF:LOW
const int LED1=9;
int dirll ;
int dirrr ;
int direc ;
int val11; 
void setup()
{
  pinMode(LED1,OUTPUT);   
  pinMode(stopbt,OUTPUT);
  pinMode(stepPin,OUTPUT); //motor left 
  pinMode(dirPin,OUTPUT); //motor left 
  pinMode(stepPina,OUTPUT); //motor right
  pinMode(dirPina,OUTPUT); //motor right
  pinMode(dirl,INPUT); 
  pinMode(dirr,INPUT); 
  pinMode(dirf,INPUT);
  pinMode(dirb,INPUT);
  Serial.begin(9600);
  digitalWrite(stopbt,LOW);
    digitalWrite(LED1,LOW)  ;
}
void left(int a) {
 for(int y = 0; y < a; y++) {
//        digitalWrite(stepPin,HIGH); 
//    digitalWrite(stepPina,HIGH); 
//    delayMicroseconds(900);
//    digitalWrite(stepPin,LOW); 
//    digitalWrite(stepPina,LOW); 
//    delayMicroseconds(700);
    digitalWrite(stepPin,HIGH); 
 //   digitalWrite(stepPina,HIGH); 
    delayMicroseconds(700);
    digitalWrite(stepPin,LOW); 
 //   digitalWrite(stepPina,LOW); 
    delayMicroseconds(700);
    digitalWrite(stepPin,HIGH); 
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(700);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(700);
    digitalWrite(stepPin,HIGH); 
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(700);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(700);
  }
}
void middle(int a) {
       for(int y = 0; y < a; y++) {//132
    digitalWrite(stepPin,HIGH); 
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(500);
  }
}  
void back(int a) {
       for(int y = 0; y < a; y++) {//132
    digitalWrite(stepPin,HIGH); 
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(500);
  }
}  

void middlea(int a) {
       for(int y = 0; y < a ; y++) {//80
    digitalWrite(stepPin,HIGH); 
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(1000);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(1000);
  }
}  
  void right(int a) {
     for(int y = 0; y < a; y++) {//32
//          digitalWrite(stepPin,HIGH); 
//    digitalWrite(stepPina,HIGH); 
//    delayMicroseconds(1700);
//    digitalWrite(stepPin,LOW); 
//    digitalWrite(stepPina,LOW); 
//    delayMicroseconds(1700);
 //    digitalWrite(stepPin,HIGH); 
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(700);
 //   digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(700);
    digitalWrite(stepPin,HIGH); 
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(700);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(700);
    digitalWrite(stepPin,HIGH); 
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(700);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(700);
  }
  }
void forward(){
     digitalWrite(stopbt,HIGH);  //LOW stop 
    digitalWrite(dirPin,LOW); 
    digitalWrite(dirPina,HIGH); 
    if (dirll == HIGH & dirrr == HIGH)   
    middlea(200);
    if (dirll == HIGH & dirrr == HIGH)   
    middlea(200);
    if (dirll == HIGH & dirrr == HIGH)   
    middlea(200);        
 //   middlea(600);        
 for(int x = 0; x < 2500; x++) { 

dirll = digitalRead(dirl); 
dirrr =  digitalRead(dirr);
if (dirll == HIGH & dirrr == HIGH) { 
    middle(16);
//    middle(132); 
}
if (dirll == HIGH & dirrr == LOW) { 
    right(40);//right
    left(40);//32
//    middlea(400);
}
if (dirll == LOW & dirrr == HIGH) { 
    left(40);
    right(40);//32
//    middlea(400);
 }
if (dirll == LOW & dirrr == LOW) {     
//  middle(132);
//     middle(132);
x = 2500;
   digitalWrite(stopbt,LOW);  ////LOW stop
}
}
}
void backward(){
    digitalWrite(stopbt,HIGH); //LOW stop
    digitalWrite(dirPin,HIGH); 
    digitalWrite(dirPina,LOW); 
    if (dirll == HIGH & dirrr == HIGH)   
    middlea(200);
    if (dirll == HIGH & dirrr == HIGH)   
    middlea(200);
    if (dirll == HIGH & dirrr == HIGH)   
    middlea(200);        
 //   middlea(600);

for(int x = 0; x < 2500; x++) {
     digitalWrite(stopbt,HIGH); //LOW stop
dirll = digitalRead(dirl); 
dirrr =  digitalRead(dirr);
if (dirll == HIGH & dirrr == HIGH) { 
     middle(16); //add two cycles to repeat move
//     middle(132);

}
if (dirll == HIGH & dirrr == LOW) { 
    right(40);
    left(40);//32
 //   middlea(40);
}
if (dirll == LOW & dirrr == HIGH) { 
    left(40);
    right(40);//32
//    middlea(40);
 }
//    delay(500);
if (dirll == LOW & dirrr == LOW) {     
//  middle(132);
//     middle(132);
   digitalWrite(stopbt,LOW);  //LOW stop
   x = 2500 ;
}
}
}
void loop() {
// val11=analogRead(1);  
// if (val11 > 500) {  //511(11/15);500:12.6V; 460:11.15V; 480:11.8V org 490
//  digitalWrite(LED1,HIGH)  ;
  direc = digitalRead(dirf); 
  if (direc == LOW) {
     forward(); 
    }
 direc = digitalRead(dirb); 
 if (direc == LOW) {
  backward();
 }
//}
// val11=analogRead(1);  
// if (val11 < 501)  digitalWrite(LED1,LOW) ; //512(11/15); 460:11.15
// else digitalWrite(LED1,HIGH);
if (Serial.available()){
  while(Serial.available())
  {
    char inChar=(char)Serial.read();
    inputString +=inChar;}
    Serial.println(inputString);
    while (Serial.available()>0)
    {junk = Serial.read();}
    if (inputString == "4"){
      digitalWrite(stopbt,HIGH);  //LOW stop 
      digitalWrite(dirPin,HIGH); 
      digitalWrite(dirPina,LOW); 
      left(200);
          digitalWrite(stopbt,LOW); //LOW stop
      }
     else if (inputString == "6"){
       digitalWrite(stopbt,HIGH);  //LOW stop 
       digitalWrite(dirPin,HIGH); 
       digitalWrite(dirPina,LOW); 
       right(200) ;
       digitalWrite(stopbt,LOW); //LOW stop
       }
     else if (inputString == "2"){
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,LOW); 
        digitalWrite(dirPina,HIGH); 
        middle(500) ;
        digitalWrite(stopbt,LOW); //LOW stop
        }
     else if (inputString == "8"){
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,LOW); 
        digitalWrite(dirPina,HIGH); 
        back(500) ;
        digitalWrite(stopbt,LOW); //LOW stop
        }
     else if (inputString == "f"){
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); 
        forward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        }
     else if (inputString == "b"){
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); 
        backward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        }    
        else if (inputString == "1"){
      digitalWrite(stopbt,HIGH);  //LOW stop 
      digitalWrite(dirPin,LOW); 
      digitalWrite(dirPina,HIGH); 
      left(200);
      digitalWrite(stopbt,LOW); //LOW stop
      }
     else if (inputString == "7"){
       digitalWrite(stopbt,HIGH);  //LOW stop 
       digitalWrite(dirPin,LOW); 
       digitalWrite(dirPina,HIGH); 
       right(200) ;
       digitalWrite(stopbt,LOW); //LOW stop
       }
     else if (inputString == "3"){
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,LOW); 
        digitalWrite(dirPina,HIGH); 
        middle(500) ;
        digitalWrite(stopbt,LOW); //LOW stop
        }
     else if (inputString == "9"){
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); 
        back(500) ;
        digitalWrite(stopbt,LOW); //LOW stop
        }   
     else if (inputString == "a"){
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); 
        forward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(10000);
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); 
        backward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(30000);
        }  
     else if (inputString == "b"){
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW);  //1
        forward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(10000);
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW);   //2
        backward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(30000);
                digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); //3
        forward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(10000);
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); //4
        backward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(30000);
                digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); //5
        forward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(10000);
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); //1
        backward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(30000);
                digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); //2
        forward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(10000);
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); //3
        backward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(30000);
                digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); //4
        forward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(10000);
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); //5
        backward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(30000);
        }           
     else if (inputString == "c"){
       for(int s = 0; s < 10; s++) {
//       for i=1 to 6 do {
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); 
        forward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(30000);
        digitalWrite(stopbt,HIGH);  //LOW stop 
        digitalWrite(dirPin,HIGH); 
        digitalWrite(dirPina,LOW); 
        backward() ;
        digitalWrite(stopbt,LOW); //LOW stop
        delay(30000);
        }       
     }
        inputString ="" ;
}
}
