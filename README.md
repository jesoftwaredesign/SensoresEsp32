# SensoresEsp32
Arduino con ESP32, toma señales de sensores y envia a servidor mediante http.GET()


Codigo para Arduino funcionando con un ESP32.
Envia los datos con
datos_a_enviar = "http://192.168.1.5:4000/sensores/edit/" + userId + "," + pass + "," + Tempe + "," + Hum;
Incluye un identificador de usuario, una clave, y las variables de temperatura y humedad. Se pueden colocar nuevas señales, separandolas por coma.
