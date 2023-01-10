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
int SAL = 7 ;
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

  // if (prod == true ){
  //   if (!ads1.begin(0x48)) {
  //     Serial.println("Failed to initialize ADS1.");
  //     while (1); 
  //   }

  //   ads1.begin();
  // }  


}

void bomba(int V1_ADC, int SAL, boolean &estado){
  float V1_AN=5*(float)V1_ADC/1023;
  if (V1_AN<0.45)
    {
      digitalWrite(SAL, HIGH);
      estado = true;
    }
  else if (V1_AN>0.29)
    {
      digitalWrite(SAL, LOW);
      estado = false;
      }
  else
    {
      digitalWrite(SAL, estado);
      }

  delay(5);
  }
  
void waitForSerial(){
  // Serial.flush();
  while (!Serial.available()){
    // Wait
  }
}


void loop() {

  waitForSerial();
  
}

void serialEvent()
  {
    entrada = Serial.readString();
    entrada.trim();
    // Control de flujo

    if(entrada.equals("sensor_0")){
      sensor_0();
    }  

    Serial.flush();
    delay(10);                       // wait for a second

  }




long read_data_led(const uint8_t* inputPin){
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


long read_data_nivel(){
  if (prod==true){
    //return ads1.readADC_SingleEnded(sensor);
    delay(100);
    return analogRead(A3);
  }
  else{
    return random(62000,64000);
  }
}


void get_data_array(int &quantity, String &string_c, const uint8_t inputADCpint, String label){

  string_c = "\"[";
  long b;
  for (int i = 0; i<quantity;i++){
    b = read_data_led(&A0);
    delay(150);
    string_c = string_c + String(b) + ",";
  }
  string_c = string_c + String(b);
  string_c = string_c + "]\"";
  Serial.print("{");
  //Serial.print("\"accion\":\"nefelometria\",");
  Serial.print("\""+ label + "\"" + ":");
  Serial.print(String(string_c));
  Serial.println("}");

  // return string_c;
}



void get_json_leds(int &quantity, String label, const uint8_t* inputPin){
  String string_c;
 
  get_data_array(quantity, string_c, inputPin, label);
}

void get_json(int &quantity){
  int V1_ADC;
  Serial.print("{");
  Serial.print("\"accion\":\"monitoreo_fisico_quimico\",");
  Serial.print("\"sensor_ph\":");
  Serial.print(String(read_data_ph()) + "," );
  delay(100);

  Serial.print("\"sensor_orp\":");
  Serial.print(String(read_data_orp()) + "," );

  Serial.print("\"sensor_nivel\":");
  V1_ADC=read_data_nivel();
  Serial.print(String(V1_ADC) + ",");

  bomba(V1_ADC, SAL, estado);

  Serial.print("\"estado\":");
  Serial.print(String(estado));
  Serial.println("}");
  
}

void news_sensor(String sensor, int espera){
  Serial.println(sensor);
  delay(espera);
}


void sensor_0(){
  while (true)
  { 
    //news_sensor("sensor_0",50);
    get_json_leds(var, "sensor_0", &A0);

    //news_sensor("sensor_1",50);
    get_json_leds(var, "sensor_1", &A5);

    //news_sensor("sensor_2",50);
    get_json_leds(var, "sensor_2", &A6);

    //news_sensor("sensor_3",50);
    get_json_leds(var, "sensor_3", &A7);

    get_json(var);
    get_json(var);
    get_json(var);
    get_json(var);
    Serial.println("END");
    if (Serial.available())
      {
        entrada = Serial.readString();
        Serial.println(entrada);
        entrada.trim();
        if (entrada=="salir"){
          break;
        }
    }

  
  }
}




