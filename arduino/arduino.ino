/**
Tesis.ino
Este archivo será el punto de entrada del proyecto, controlará todo el funcionamiento total
del proyecto.

*/

#include "math.h"

// #include <Adafruit_ADS1X15.h>
// Adafruit_ADS1115 ads1;
#include <Wire.h>
int var = 10;
int SAL = 7 ;
boolean estado = true;
const int ledPIN = 13;
bool monutitoreo_cont;
String entrada;


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
      //Serial.println("2");
      estado = false;

      }
  else
    {
      digitalWrite(SAL, estado);

      }

  delay(5);
  }
  
  ///



/**
 * @brief Esperará a que haya información en el puerto serie para continuar la ejecución
 * 
 */
void testProject(){
  Serial.println("{\"accion\":\"test\",\"message\":\"successful\"}");
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
void serialEvent(){
  entrada = Serial.readString();
  entrada.trim();
    // Control de flujo
  if(entrada.equals("sensores")){

    enviarSensores();
  } 

  if(entrada.equals("sensor_1_inf")){
    sensor_1();
  }

  if(entrada.equals("sensor_0")){

    sensor_0();
  } 

  if(entrada.equals("probar")){
    testProject();
  }

  Serial.flush();
  Serial.print("{");
  Serial.print("\"accion\":\"changeMenu\",");
  Serial.print("\"menu\":\"home\"");
  Serial.println("}");

  delay(10);                       // wait for a second

}

void enviarSensores(){
  monutitoreo_cont = true;
  while (true)
  {
    digitalWrite(ledPIN,HIGH);
    Serial.print("{");
    Serial.print("\"accion\":\"monitoreo\",");
    Serial.print("\"sensor1\":");
    Serial.print(read_data(0));
    Serial.print(",\"sensor2\":");
    Serial.print(read_data(1));
    Serial.print(",\"sensor3\":");
    Serial.print(read_data(2));
    Serial.print(",\"sensor4\":");
    Serial.print(read_data(3));
    Serial.println("}");


    digitalWrite(ledPIN,HIGH);
    Serial.print("{");
    Serial.print("\"accion\":\"monitoreo\",");
    Serial.print("\"sensor1\":");
    Serial.print(read_data(0));
    Serial.print(",\"sensor2\":");
    Serial.print(read_data(1));
    Serial.print(",\"sensor3\":");
    Serial.print(read_data(2));
    Serial.print(",\"sensor4\":");
    Serial.print(read_data(3));
    Serial.println("}");
    if (Serial.available())
    {
      entrada = Serial.readString();
      Serial.println(entrada);
      entrada.trim();
      if (entrada=="salir")
      {
        //monutitoreo_cont = false;
        Serial.println("ENTRE AL WHILE");
        break;
      }
    }

    delay(300);

  }
  
}

long read_data(int sensor){
  if (prod==true){
    //return ads1.readADC_SingleEnded(sensor);
    return analogRead(A0);
  }
  else{
    return random(62000,64000);
  }
}

long read_data_ph(){
  if (prod==true){
    //return ads1.readADC_SingleEnded(sensor);
    delay(100);
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

void get_data_array(int &quantity, String &string_c){
  string_c = "\"[";
  long b;
  for (int i = 0; i<quantity;i++){
    b = read_data(0);
    delay(150);
    string_c = string_c + String(b) + ",";
  }
  string_c = string_c + String(b);
  string_c = string_c + "]\",";
  // return string_c;
}



void get_json(int &quantity){
  String string_c;
  Serial.print("{");
  Serial.print("\"accion\":\"monitoreo\",");
  Serial.print("\"sensor1\":");
  get_data_array(quantity, string_c);
  Serial.print(string_c);
  Serial.print("\"sensor_ph\":");
  Serial.print(String(read_data_ph()) + "," );
  Serial.print("\"sensor_orp\":");
  Serial.print(String(read_data_orp()) + "," );
  Serial.print("\"sensor_nivel\":");
  int V1_ADC=read_data_nivel();
  Serial.print(String(V1_ADC) + ",");
  bomba(V1_ADC, SAL, estado);
  Serial.print("\"estado\":");
  Serial.print(String(estado));
  Serial.println("}");
}

void sensor_1(){

  while (true){
    
    digitalWrite(ledPIN,HIGH);
    get_json(var);

    digitalWrite(ledPIN,LOW);
    get_json(var);

    if (Serial.available())
    {
      entrada = Serial.readString();
      entrada.trim();
      if (entrada=="salir")
      {
        break;
      }
    }

    delay(50);

  }
  
}


void sensor_0(){
  while (true)
  {
    delay(3000);
    //digitalWrite(ledPIN,HIGH);
    get_json(var);
    //digitalWrite(ledPIN,LOW);
    get_json(var);
    get_json(var);
    get_json(var);
    Serial.println("END");
    if (Serial.available())
      {
        entrada = Serial.readString();
        Serial.println(entrada);
        entrada.trim();
        if (entrada=="salir")
        {
          //monutitoreo_cont = false;
          Serial.println("ENTRE AL WHILE");
          break;
        }
    }

  }
}




