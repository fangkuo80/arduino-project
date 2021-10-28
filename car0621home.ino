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
        digitalWrite(stepPin,HIGH);  //1 
//    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW); 
//    digitalWrite(stepPina,LOW); 
    delayMicroseconds(500);
    digitalWrite(stepPin,HIGH); 
 //   digitalWrite(stepPina,HIGH);   //2
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW); 
 //   digitalWrite(stepPina,LOW); 
    delayMicroseconds(500);
    digitalWrite(stepPin,HIGH);   //3
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(500);
    digitalWrite(stepPin,HIGH);   //4
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(500);
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
void middlea(int a) {
       for(int y = 0; y < a ; y++) {//80
    digitalWrite(stepPin,HIGH); 
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(1100);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(1100);
  }
}  
  void right(int a) {
     for(int y = 0; y < a; y++) {//32
//    digitalWrite(stepPin,HIGH); //1
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(500);
//    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(500);
 //    digitalWrite(stepPin,HIGH); //2
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(500);
 //   digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(500);
    digitalWrite(stepPin,HIGH); //3
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(500);
    digitalWrite(stepPin,HIGH); //4
    digitalWrite(stepPina,HIGH); 
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW); 
    digitalWrite(stepPina,LOW); 
    delayMicroseconds(500);
  }
  }
void forward(){
     digitalWrite(stopbt,HIGH);  //LOW stop 
    digitalWrite(dirPin,LOW); 
    digitalWrite(dirPina,HIGH); 
      if (dirll == LOW & dirrr == LOW) {  
    middlea(450);}
    if (dirll == LOW & dirrr == LOW) { 
    middlea(50);}
    if (dirll == LOW & dirrr == LOW) {  
    middlea(50); }    //  middlea(480);
 for(int x = 0; x < 25000; x++) { 
dirll = digitalRead(dirl); 
dirrr =  digitalRead(dirr);
if (dirll == HIGH & dirrr == HIGH) { 
    middle(1);
}
if (dirll == HIGH & dirrr == LOW) { 
    right(50);//right
    left(40);//32
}
if (dirll == LOW & dirrr == HIGH) { 
   left(50);
   right(40);//32
 }
if (dirll == LOW & dirrr == LOW) {     
x = 25000;
delayMicroseconds(2800);
   digitalWrite(stopbt,LOW);  ////LOW stop
}
}
}
void backward(){
    digitalWrite(stopbt,HIGH); //LOW stop
    digitalWrite(dirPin,HIGH); 
    digitalWrite(dirPina,LOW); 
      if (dirll == LOW & dirrr == LOW) {  
    middlea(450);}
    if (dirll == LOW & dirrr == LOW) { 
    middlea(50);}
    if (dirll == LOW & dirrr == LOW) {  
    middlea(50); }    //  middlea(480);
for(int x = 0; x < 25000; x++) {
     digitalWrite(stopbt,HIGH); //LOW stop
dirll = digitalRead(dirl); 
dirrr =  digitalRead(dirr);
if (dirll == HIGH & dirrr == HIGH) { 
     middle(1); //add two cycles to repeat move
}
if (dirll == HIGH & dirrr == LOW) { 
//  left(40) ;
    right(50);//32
//    right(40);
    left(40);//32
}
if (dirll == LOW & dirrr == HIGH) { 
  //    right(40);
    left(50);//32
//    left(40) ;
    right(40);//32
 }
//    delay(500);
if (dirll == LOW & dirrr == LOW) {     
    x = 25000 ;
  delayMicroseconds(2800);
   digitalWrite(stopbt,LOW);
//   digitalWrite(stopbt,LOW);  //LOW stop
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
    if (inputString == "b"){
      forward();}
      else if (inputString == "f"){
        backward() ;}
        inputString ="" ;
}
}
