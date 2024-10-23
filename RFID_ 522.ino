//librerias para el lector rfid
#include<SPI.h> 
#include<MFRC522.h>

//librerias para la pantalla oled
#include <Wire.h> 
#include<Adafruit_GFX.h> 
#include<Adafruit_SSD1306.h>

//definimos el numero de pixeles de la pantalla oled
#define ANCHO 128
#define ALTO 64
#define OLED_RESET 4 //lo necesitamos por cuestiones del fabricante

//creamos el objeto(ancho,alto,referencia de la libreria Wire,pin de reset);
Adafruit_SSD1306 oled(ANCHO,ALTO,&Wire,OLED_RESET);

//definimos pines para el lector RFID
#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);

byte LecturaUID[4]; //creamos un array del tipo byte con un tamaño de 4
byte Usuario1[4] = {0x59, 0x63, 0x8F, 0xC2}; //Creamos otro array con los valores de nuestros tags 
byte Usuario2[4] = {0xA3, 0xEB, 0xB4, 0x03};// USUARIO 2 
byte Usuario3[4] = {0xD3, 0x4E, 0xBF, 0x03};// USUARIO 3
byte Usuario4[4] = {0x24, 0x2A, 0xCB, 0x73};// USUARIO 4
byte Usuario5[4] = {0x00, 0x00, 0x00, 0x00};// USUARIO 5

int relay = 2; //pin del relevador

void setup() {
  Serial.begin(9600); 
  Wire.begin(); //inicializamos la comunicacion por bus i2c
  oled.begin(SSD1306_SWITCHCAPVCC,0x3C); //inicializamos el oled (constante definida del oled, direcion i2c del dispositivo);
  pinMode(relay, OUTPUT); // Configurar relay como salida  
  
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Listo");
  digitalWrite(relay, LOW); // envia señal de apagado al relay
 //"Relay accionado"
  Serial.println("Cerrado");
  oled.clearDisplay();
}

void loop() {
   
  
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

Serial.print("UID: ");
for(byte i=0;i<mfrc522.uid.size;i++){
  if(mfrc522.uid.uidByte[i] < 0x10){
    Serial.print(" 0");
  }
  else{
    Serial.print(" ");
  }
  Serial.print(mfrc522.uid.uidByte[i], HEX);
  LecturaUID[i]=mfrc522.uid.uidByte[i];
}
Serial.print("\t");

//PRIMER USUARIO/////////////////////////////////////////
if(comparaUID(LecturaUID,Usuario1)){  //realizaMos la comparacion entre la lectura y el usuario con acceso
Serial.println("Bienvenido INSAMT1"); 
pantalla_conocido1(); //llamamos a la funcion para mostrar en oled
digitalWrite(relay, HIGH);  // envia señal alta al relay y la cerradura se abre
  //"Relay accionado"
Serial.println("Abierto"); 
delay(5000); //esperamos 10 segundos para entrar por la puerta 
oled.clearDisplay(); //limpiamos la pantalla
oled.display();
  //Relay no Accionado
digitalWrite(relay,LOW); //volvemos a cerrar la cerradura
Serial.println("Cerrado");
}


//AÑADIR USUARIO 2/////////////////////////////////////////

else if(comparaUID(LecturaUID,Usuario2)){  //realizaMos la comparacion entre la lectura y el usuario con acceso
Serial.println("Bienvenido INSAMT2"); 
pantalla_conocido2(); //llamamos a la funcion para mostrar en oled
digitalWrite(relay, HIGH);  // envia señal ALTA al relay y la cerradura se abre
  //"Relay no accionado"
Serial.println("Abierto"); 
delay(5000); //esperamos 10 segundos para entrar por la puerta 
oled.clearDisplay(); //limpiamos la pantalla
oled.display();
  //Relay Accionado
digitalWrite(relay,LOW); //volvemos a cerrar la cerradura
Serial.println("Cerrado");
}

//AÑADIR USUARIO 3/////////////////////////////////////////

else if(comparaUID(LecturaUID,Usuario3)){  //realizaMos la comparacion entre la lectura y el usuario con acceso
Serial.println("Bienvenido INSAMT3"); 
pantalla_conocido3(); //llamamos a la funcion para mostrar en oled
digitalWrite(relay, HIGH);  // envia señal ALTA al relay y la cerradura se abre
  //"Relay no accionado"
Serial.println("Abierto"); 
delay(5000); //esperamos 10 segundos para entrar por la puerta 
oled.clearDisplay(); //limpiamos la pantalla
oled.display();
  //Relay Accionado
digitalWrite(relay,LOW); //volvemos a cerrar la cerradura
Serial.println("Cerrado");
}

//AÑADIR USUARIO 4/////////////////////////////////////////

else if(comparaUID(LecturaUID,Usuario4)){  //realizaMos la comparacion entre la lectura y el usuario con acceso
Serial.println("Bienvenido INSAMT4"); 
pantalla_conocido4(); //llamamos a la funcion para mostrar en oled
digitalWrite(relay, HIGH);  // envia señal ALTA al relay y la cerradura se abre
  //"Relay no accionado"
Serial.println("Abierto"); 
delay(5000); //esperamos 10 segundos para entrar por la puerta 
oled.clearDisplay(); //limpiamos la pantalla
oled.display();
  //Relay Accionado
digitalWrite(relay,LOW); //volvemos a cerrar la cerradura
Serial.println("Cerrado");
}

//AÑADIR USUARIO 5/////////////////////////////////////////

else if(comparaUID(LecturaUID,Usuario5)){  //realizaMos la comparacion entre la lectura y el usuario con acceso
Serial.println("Bienvenido INSAMT5"); 
pantalla_conocido5(); //llamamos a la funcion para mostrar en oled
digitalWrite(relay, HIGH);  // envia señal ALTA al relay y la cerradura se abre
  //"Relay no accionado"
Serial.println("Abierto"); 
delay(5000); //esperamos 10 segundos para entrar por la puerta 
oled.clearDisplay(); //limpiamos la pantalla
oled.display();
  //Relay Accionado
digitalWrite(relay,LOW); //volvemos a cerrar la cerradura
Serial.println("Cerrado");
}


else{
Serial.println("Usuario desconocido"); 
pantalla_desconocido(); //llamamos a la funcion 
delay(2000); //esperamos 2 segundos y limpiamos la pantalla
oled.clearDisplay();
oled.display();
}

mfrc522.PICC_HaltA(); //finaliza la comunicacion con la tarjeta
}

boolean comparaUID(byte lectura[], byte usuario[]){
  for(byte i=0;i<mfrc522.uid.size;i++){
    if(lectura[i] != usuario[i])
    return(false);
  }
  return (true);

}



void pantalla_conocido1(){ //creamos la funcion 
   oled.setTextColor(WHITE); //establecemos el color
   oled.setTextSize(2); //establecemos el tamaño de la letra
   oled.setCursor(25,25); //establecemos la posicion inicial del cursor

  oled.print("HOLA!!!"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
   delay(500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla

   oled.setCursor(0,25); //establecemos la posicion inicial del cursor
   oled.print(" PROFESOR  JC"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
   delay(1500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla

   oled.setCursor(0,25); //y establecemos nuevo mensaje en nueva posicion
   oled.print("BIEVENIDO");
   
   oled.print("    A");
   oled.display();
   delay(1500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla
   
   oled.setCursor(0,25); //establecemos la posicion inicial del cursor
   oled.print(" SOFTWARE"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
  
}


void pantalla_conocido2(){ //creamos la funcion 
   oled.setTextColor(WHITE); //establecemos el color
   oled.setTextSize(2); //establecemos el tamaño de la letra
   oled.setCursor(25,25); //establecemos la posicion inicial del cursor

  oled.print("HOLA!!!"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
   delay(500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla

   oled.setCursor(0,25); //establecemos la posicion inicial del cursor
   oled.print(" PROFESOR  WILLIAM"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
   delay(1500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla

   oled.setCursor(0,25); //y establecemos nuevo mensaje en nueva posicion
   oled.print("BIEVENIDO");
   
   oled.print("    A");
   oled.display();
   delay(1500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla
   
   oled.setCursor(0,25); //establecemos la posicion inicial del cursor
   oled.print(" SOFTWARE"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
  
}


void pantalla_conocido3(){ //creamos la funcion 
   oled.setTextColor(WHITE); //establecemos el color
   oled.setTextSize(2); //establecemos el tamaño de la letra
   oled.setCursor(25,25); //establecemos la posicion inicial del cursor

  oled.print("HOLA!!!"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
   delay(500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla

   oled.setCursor(0,25); //establecemos la posicion inicial del cursor
   oled.print(" PROFESOR  WILLIAM"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
   delay(1500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla

   oled.setCursor(0,25); //y establecemos nuevo mensaje en nueva posicion
   oled.print("BIEVENIDO");
   
   oled.print("    A");
   oled.display();
   delay(1500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla
   
   oled.setCursor(0,25); //establecemos la posicion inicial del cursor
   oled.print(" SOFTWARE"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
  
}


void pantalla_conocido4(){ //creamos la funcion 
   oled.setTextColor(WHITE); //establecemos el color
   oled.setTextSize(2); //establecemos el tamaño de la letra
   oled.setCursor(25,25); //establecemos la posicion inicial del cursor

  oled.print("HOLA!!!"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
   delay(500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla

   oled.setCursor(0,25); //establecemos la posicion inicial del cursor
   oled.print(" PROFESOR  WILLIAM"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
   delay(1500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla

   oled.setCursor(0,25); //y establecemos nuevo mensaje en nueva posicion
   oled.print("BIEVENIDO");
   
   oled.print("    A");
   oled.display();
   delay(1500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla
   
   oled.setCursor(0,25); //establecemos la posicion inicial del cursor
   oled.print(" SOFTWARE"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
  
}


void pantalla_conocido5(){ //creamos la funcion 
   oled.setTextColor(WHITE); //establecemos el color
   oled.setTextSize(2); //establecemos el tamaño de la letra
   oled.setCursor(25,25); //establecemos la posicion inicial del cursor

  oled.print("HOLA!!!"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
   delay(500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla

   oled.setCursor(0,25); //establecemos la posicion inicial del cursor
   oled.print(" PROFESOR  WILLIAM"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
   delay(1500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla

   oled.setCursor(0,25); //y establecemos nuevo mensaje en nueva posicion
   oled.print("BIEVENIDO");
   
   oled.print("    A");
   oled.display();
   delay(1500); //esperamos medio segundo
   oled.clearDisplay(); //limpiamos pantalla
   
   oled.setCursor(0,25); //establecemos la posicion inicial del cursor
   oled.print(" SOFTWARE"); //mensaje a imprimir
   oled.display();  //funcion para mostrar en pantalla lo anterior
  
}



void pantalla_desconocido(){
   oled.setTextColor(WHITE);
   oled.setCursor(25,10);
   oled.setTextSize(2);
   oled.print("Usuario"); 
   oled.setCursor(30,35);
   oled.setTextSize(1);
   oled.print("desconocido");
   oled.display();
}
