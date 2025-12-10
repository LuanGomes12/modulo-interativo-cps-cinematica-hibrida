#include <WiFi.h>
#include <ESP32Servo.h>

// ======= CONFIGURAÇÃO DA REDE =======
const char* ssid = "BracoRobot_AP";
const char* password = "12345678";

// Porta TCP que o servidor vai escutar
WiFiServer server(5000);

// ======= CONFIGURAÇÃO DO SERVO =======
Servo servoA, servoB, servoC, servoD, servoE;
const int pinA = 13;
const int pinB = 12;
const int pinC = 14;
const int pinD = 27;
const int pinE = 26;

// O tamanho do buffer é 5 (1 byte para o comando + 4 bytes para o float)
const int buffer_size = 5; 
byte buf[buffer_size];

union BtoF {
  byte b[4];
  float fval;
} u;

void setup() {
  Serial.begin(115200);

  servoA.setPeriodHertz(50);
  servoA.attach(pinA);
  servoB.attach(pinB);
  servoC.attach(pinC);
  servoD.attach(pinD);
  servoE.attach(pinE);

  // ... (Configuração do Access Point) ...
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point criado: ");
  Serial.println(ssid);
  Serial.print("IP do ESP32 (use esse no Simulink): ");
  Serial.println(IP);

  server.begin();
  Serial.println("Servidor TCP iniciado na porta 5000");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    //Serial.println("Cliente conectado");
    while (client.connected()) {
      
      // *** LÓGICA DE LEITURA SÍNCRONA: ESPERA POR EXATOS 5 BYTES ***
      if (client.available() >= buffer_size) {
        client.readBytes(buf, buffer_size);

        // 1. O primeiro byte (índice 0) é o comando (A, B, C, D, E)
        char comando = (char)buf[0];

        // 2. Os próximos 4 bytes (índices 1 a 4) são o valor float
        for (int j = 0; j < 4; j++) {
          u.b[j] = buf[1 + j]; // Armazena os bytes do float na união
        }

        float val = u.fval;
        // Manteve o constrain em 0-120 como no seu código Arduino original.
        int angle = constrain((int)val, 0, 120); 

        // 3. Controle do Servo
        Serial.print("Comando ");
        Serial.print(comando);
        Serial.print(" -> Angulo: ");
        Serial.println(angle);

        switch (comando) {
          case 'A': servoA.write(angle); break;
          case 'B': servoB.write(angle); break;
          case 'C': servoC.write(angle); break;
          case 'D': servoD.write(angle); break;
          case 'E': servoE.write(angle); break;
          default:
            Serial.print("Comando inválido: ");
            Serial.println(comando);
            break;
        }

        client.println("OK"); // Responde após processar o pacote de 5 bytes
      }
    }
    client.stop();
    Serial.println("Cliente desconectado");
  }
}