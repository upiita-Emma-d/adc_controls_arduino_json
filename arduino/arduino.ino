/**
Tesis.ino
Este archivo será el punto de entrada del proyecto, controlará todo el funcionamiento total
del proyecto.

*/

#include "math.h"

// #include <Adafruit_ADS1X15.h>
// Adafruit_ADS1115 ads1;
#include <Wire.h>
int var = 20;
int SAL = 8 ;
boolean estado = true;
const int ledPIN = 13;
const int ambar = 12;
const int red  = 11;
const int blue = 10;
const int green = 9;
String entrada;
String dato_c;


bool prod = true;

void setup() {
  pinMode(SAL,OUTPUT);
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);


}

  
void waitForSerial(){
  // Serial.flush();
  while (!Serial.available()){
    // Wait
  }
}


void loop() {

  //waitForSerial();
  sensor_0();
  
}


long read_data_led(uint8_t inputPin){
  if (prod==true){
    //return ads1.readADC_SingleEnded(sensor);
    return analogRead(inputPin);
  }
  else{
    return random(62000,64000);
  }
}





long read_data_ph(){
  if (prod==true){
    //return ads1.readADC_SingleEnded(sensor);
    delay(300);
    return analogRead(A1);
  }
  else{
    return random(62000,64000);
  }
}

long read_data_orp(){
  if (prod==true){
    //return ads1.readADC_SingleEnded(sensor);
    return analogRead(A2);
  }
  else{
    return random(62000,64000);
  }
}



void get_data_array(int &quantity, String &string_c, uint8_t inputADCpint, String label){

  string_c = "\"[";
  long b;
  for (int i = 0; i<quantity;i++){
    b = read_data_led(inputADCpint);
    delay(150);
    string_c = string_c + String(b) + ",";
  }
  string_c = string_c + String(b);
  string_c = string_c + "]\"";
  Serial.print("{");
  Serial.print("\""+ label + "\"" + ":");
  Serial.print(String(string_c));
  Serial.println("}");
}



void get_json_leds(int &quantity, String label, int inputPin){
  String string_c;
  uint8_t pin;
  if (inputPin == 0) {
    pin = A0;
  } else if (inputPin == 1) {
    pin = A1;

  } else if (inputPin == 2) {
    pin = A2;
  } else if (inputPin == 3) {
    pin = A3;
  } else if (inputPin == 4) {
    pin = A4;
  } else if (inputPin == 5) {
    pin = A5;
  } else if (inputPin == 6) {
    pin = A6;
  }else if (inputPin == 7) {
    pin = A7;
  }
  //Serial.println(String(pin));
  get_data_array(quantity, string_c, pin, label);
  } 

void espacios(String mensaje){
  Serial.print("{");
  Serial.print("\"accion\":");
  Serial.print("\"" +String(mensaje) + "\"");
  Serial.println("}");
}

void sensor_0(){
  while (true)
  { 
    espacios("led_ambar");
    get_json_leds(var, "sensor_0_amb", 0);
    espacios("led_ambar");
    get_json_leds(var, "sensor_1_amb", 1);
    espacios("uv_1");
    get_json_leds(var, "sensor_uv_0", 2);
    espacios("uv_2");
    get_json_leds(var, "sensor_uv_1", 3);

    espacios("led_rojo");
    get_json_leds(var, "sensor_4_r", 4);
    espacios("led_verde");
    get_json_leds(var, "sensor_4_v", 4);
    espacios("led_azul");
    get_json_leds(var, "sensor_4_a", 4);

    espacios("led_rojo");
    get_json_leds(var, "sensor_5_r", 5);
    espacios("led_verde");
    get_json_leds(var, "sensor_5_v", 5);
    espacios("led_azul");
    get_json_leds(var, "sensor_5_a", 5);

    digitalWrite(SAL , HIGH);   // poner el Pin en HIGH
    delay(2000);                   // esperar un segundo
    digitalWrite(SAL , LOW);    // poner el Pin en LOW
    delay(50); 
    Serial.println("END");


  
  }
}




