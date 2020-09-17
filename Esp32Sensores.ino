//si usas esp32
#include <HTTPClient.h>
#include <WiFi.h>
#include "DHT.h"

//si usas esp8266
//#include <ESP8266WiFiMulti.h>
//#include <ESP8266HTTPClient.h>

//incluir sensor
#define DHTTYPE DHT11   // DHT 11
// El Sensor DHT en que puerto se conecta
uint8_t DHTPin = 15; 
// Inicializar sensor DHT.
DHT dht(DHTPin, DHTTYPE);  
float Tempe;
float Hum;

const char* ssid = "JALIVAJUMAX";
const char* password =  "oxwhtehf8";

String userId = "5ec48f036d860f31384b9a74";
String pass = "emilio";
//String valor = "31";

void setup() {
  delay(100);
  Serial.begin(115200);
  
  pinMode(DHTPin, INPUT);
  dht.begin();

  WiFi.begin(ssid, password);

  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.print(".");
  }

  Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());

}

void loop() {

  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

    Tempe = dht.readTemperature(); // Retorna los valores de la temperatura
    Hum = dht.readHumidity(); // Retorna los valores de la humedad
    Serial.println(Tempe);
    Serial.println(Hum);
    
    
    HTTPClient http;
    

    
    String datos_a_enviar = "http://192.168.1.5:4000/sensores/edit/" + userId + "," + pass + "," + Tempe + "," + Hum;

    http.begin(datos_a_enviar);        //Indicamos el destino
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Preparamos el header text/plain si solo vamos a enviar texto plano sin un paradigma llave:valor.
    //String datos_a_enviar = "http://192.168.1.12:4000/sensores/edit/"+"&user=" + user + "&pass=" + pass;
    Serial.println(datos_a_enviar);

    
    int codigo_respuesta = http.GET();   //Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)

    if(codigo_respuesta>0){
      Serial.println("Código HTTP ► " + String(codigo_respuesta));   //Print return code

      if(codigo_respuesta == 200){
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);

      }

    }else{

     Serial.print("Error enviando POST, código: ");
     Serial.println(codigo_respuesta);

    }

    http.end();  //libero recursos

  }else{

     Serial.println("Error en la conexión WIFI");

  }

   delay(2000);
}
