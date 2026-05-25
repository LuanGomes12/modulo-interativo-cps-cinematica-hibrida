#include <WiFi.h>
#include <ESP32Servo.h>

// ======= CONFIGURAÇÃO DA REDE =======
const char* ssid = [NOME_REDE];
const char* password = [SENHA_REDE];

// Porta TCP que o servidor vai escutar
WiFiServer server(5000);

// ======= CONFIGURAÇÃO DO SERVO =======
Servo servoA, servoB, servoC, servoD, servoE;
const int pinA = 13;
const int pinB = 12;
const int pinC = 14;
const int pinD = 27;
const int pinE = 26;

// Limites padrão de PWM para a maioria dos servos (ex: MG995, MG90S). 
const int minUs = 500;
const int maxUs = 2400;

// Tamanho do buffer: 26 bytes (1 Sync + 5 juntas * (1 ID + 4 bytes Float))
const int buffer_size = 26;
byte buf[buffer_size];

const byte HEADER_SYNC = 0xAA; 

union BtoF {
  byte b[4];
  float fval;
} u;

void setup() {
  Serial.begin(115200);

  // 1. ALOCAÇÃO DE TIMERS DE HARDWARE
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // 2. CONFIGURAÇÃO DE FREQUÊNCIA (50Hz)
  servoA.setPeriodHertz(50);
  servoB.setPeriodHertz(50);
  servoC.setPeriodHertz(50);
  servoD.setPeriodHertz(50);
  servoE.setPeriodHertz(50);

  // 3. ATTACH COM LIMITES DE PULSO DEFINIDOS
  servoA.attach(pinA, minUs, maxUs);
  servoB.attach(pinB, minUs, maxUs);
  servoC.attach(pinC, minUs, maxUs);
  servoD.attach(pinD, minUs, maxUs);
  servoE.attach(pinE, minUs, maxUs);

  // Configuração do Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point criado: ");
  Serial.println(ssid);
  Serial.print("IP do ESP32: ");
  Serial.println(IP);

  server.begin();
  Serial.println("Servidor TCP iniciado na porta 5000");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    while (client.connected()) {
      
      if (client.available() >= buffer_size) {
        client.readBytes(buf, buffer_size);

        if (buf[0] != HEADER_SYNC) {
          Serial.println("Erro de sincronização. Descartando pacote.");
          while(client.available()) client.read();
          continue; 
        }

        Serial.print("[RAW PAYLOAD]: ");
        for(int k = 0; k < buffer_size; k++) {
          if(buf[k] < 0x10) Serial.print("0"); 
          Serial.print(buf[k], HEX);
          Serial.print(" ");
        }
        Serial.println("\n[DECODIFICADO]:");

        for (int i = 0; i < 5; i++) {
          
          int offset = 1 + (i * 5); 
          char comando = (char)buf[offset];

          for (int j = 0; j < 4; j++) {
            u.b[j] = buf[offset + 1 + j];
          }
          
          float val = u.fval;
          
          // 1. Restrição Lógica: Garante que os limites do digital twin sejam respeitados
          int angulo_logico = (int)val;
          if (comando == 'E') {
            angulo_logico = constrain(angulo_logico, 0, 180);
          } else {
            angulo_logico = constrain(angulo_logico, 0, 120);
          }

          // 2. Preparação do Ângulo Físico (Motor)
          int angulo_motor = angulo_logico;

          // ======= CORREÇÃO DE REFERENCIAL FÍSICO =======
          // A Junta A está montada invertida mecanicamente.
          // O terminal mostrará o valor lógico, mas o motor receberá o valor invertido.
          if (comando == 'A') {
            angulo_motor = 120 - angulo_logico; 
          }
          // ============================================

          // 3. Acionamento do hardware com os ângulos já corrigidos e limitados
          switch (comando) {
            case 'A': servoA.write(angulo_motor); break;
            case 'B': servoB.write(angulo_motor); break;
            case 'C': servoC.write(angulo_motor); break;
            case 'D': servoD.write(angulo_motor); break;
            case 'E': servoE.write(angulo_motor); break;
            default:
              Serial.print("  Comando desconhecido: ");
              Serial.println(comando);
              break;
          }

          // 4. Impressão focada no terminal: exibe apenas o valor lógico para manter a 
          // paridade visual com os valores gerados na simulação do Simulink.
          Serial.print("  Junta ");
          Serial.print(comando);
          Serial.print(" -> Angulo: ");
          Serial.print(angulo_logico);
          
          Serial.println();
        }
        
        Serial.println("------------------------------------------------"); 
        client.println("OK"); 
      }
    }
    client.stop();
    Serial.println("Cliente desconectado");
  }
}
