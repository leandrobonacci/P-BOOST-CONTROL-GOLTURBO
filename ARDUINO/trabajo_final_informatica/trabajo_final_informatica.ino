#include <LiquidCrystal.h>    // importa libreria
const int iny1 = 12;
const int iny2 = 11;
int c=0,a=0,len=0,tps=0,tpsp=0;
float map1,pote,pbar,bar,histeresis2=25;



int interruptor,ab;


LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  // pines RS, E, D4, D5, D6, D7 de modulo 1602A

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);     // inicializa a display de 16 columnas y 2 lineas 
pinMode(iny1, OUTPUT);
pinMode(iny2, OUTPUT);
pinMode(10, INPUT);
pinMode(13, OUTPUT);
}

void loop() {


lcdmuestra();

serialimpreso();

serial();

if(interruptor == HIGH)
{
  boostcontrol();
}
 if(interruptor == LOW ){
limpieza();

  }
  


}

void boostcontrol(){
  //ALGORITMO DE BOOST CONTROL

if(pote>map1+histeresis2 && pote<map1-histeresis2){
 lcdmuestra();
serialimpreso();
serial();

}
else
{
  lcd.clear();
   do{
    lcdmuestra();
serialimpreso();
serial();

    digitalWrite(iny1,HIGH);
  }while(pote<=map1 && interruptor == HIGH );
  digitalWrite(iny1,LOW);
}
if(pote<map1+histeresis2 && pote>map1-histeresis2){
lcdmuestra();
serialimpreso();
serial();

}
else
{
  lcd.clear();
   do{
lcdmuestra();
serialimpreso();
serial();

    digitalWrite(iny2,HIGH);
  }while(pote>=map1 && interruptor == HIGH );
  digitalWrite(iny2,LOW);
  
  
}
 

}
void lcdmuestra(){
// CONTROL DE PANTALLA

lcd.print("P.OBJ: ");  // escribe el texto en pantalla
lcd.print(pbar);
lcd.setCursor(0, 2);      // ubica cursor en columna 0, linea 0
lcd.print("P.WG:");  // escribe el texto en pantalla
lcd.print(bar);
if(interruptor == HIGH)
{
lcd.setCursor(13, 1);      // ubica cursor en columna 0, linea 0
lcd.print("ON");
}
if(interruptor == LOW)
{
lcd.setCursor(13, 1);      // ubica cursor en columna 0, linea 0
lcd.print("OFF");
}
}





void limpieza(){
 do{
   lcdmuestra();
   serialimpreso();
   serial();
      digitalWrite(iny2,HIGH);
 }while(0.2<=bar && interruptor == LOW );
digitalWrite(iny2,LOW);
}


void serialimpreso(){
// LECTURA DE VARIABLES Y COMUNICACION SERIAL
interruptor=digitalRead(10);

map1=analogRead(A0);
pote=analogRead(A1);
tps=analogRead(A1);
bar = ((map1 * (400 / (1023.0)))/100)-0.98;   // 400kpa to 4.0BAR
pbar = ((pote * (400 / (1023.0)))/100)-1;   // 400kpa to 4.0BAR
tpsp = map(tps, 0, 1023, 0, 100);
lcd.setCursor(0, 0);      // ubica cursor en columna 0, linea 0
c=c+1;
}
void serial(){
c=c+1;
if(c==200){

Serial.print(bar);
Serial.print('@');
Serial.print(pbar);
Serial.print('/');
Serial.print(tpsp);
Serial.print('%');
if(interruptor == HIGH)
{
Serial.print('|');
Serial.print('O');
Serial.print('n');
}
if(interruptor == LOW)
{
Serial.print('O');
Serial.print('F');
Serial.print('F');
Serial.print('|');
            }
c=0;
}
}
