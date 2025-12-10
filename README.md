# Módulo Interativo para Controle de Movimento de um Manipulador Robótico Didático

Este repositório contém o desenvolvimento completo de um sistema interativo para controle, visualização e telemetria de um manipulador robótico didático.  
O projeto integra:

- Modelo mecânico 3D desenvolvido no **Autodesk Inventor**
- Gêmeo digital construído no **Simscape Multibody**
- Interface interativa desenvolvida em **MATLAB (GUIDE)**
- Comunicação **Wi-Fi TCP/IP** com um microcontrolador **ESP32**
- Controle de servos/motores do manipulador físico

O objetivo é fornecer uma plataforma educacional e experimental que una **simulação**, **controle**, **visualização** e **execução física** em um único sistema modular.

---

## 1. Arquitetura Geral do Sistema

![Diagrama_BDD_2](https://github.com/user-attachments/assets/806d89f0-12b0-4a41-96a4-ec408c504df7)

A comunicação ocorre por TCP/IP, permitindo sincronização entre o robô real e o modelo virtual.

---

## 2. Conteúdo do Repositório

/docs/ Documentação, diagramas e imagens

/cad/ Arquivos CAD (Inventor) e exportações do Simscape

/simulink_model/ Modelo Simscape Multibody do manipulador

/matlab_interface/ Interface GUIDE (fig/m-files) + funções auxiliares

/esp32_firmware/ Código do ESP32 (TCP server + controle)

/tests/ Scripts de teste para simulação e hardware real


---

## 3. Requisitos de Software

### MATLAB
- MATLAB R2021a ou superior  
- Toolboxes necessárias:
  - Simulink  
  - Simscape  
  - Simscape Multibody  
  - Instrument Control Toolbox (para TCP/IP)  

### Autodesk Inventor
- Autodesk Inventor 2020 ou superior  
- Plugin **Simscape Multibody Link** instalado e configurado  

### ESP32
- PlatformIO ou Arduino IDE  
- Bibliotecas utilizadas:
  - WiFi  
  - AsyncTCP (opcional)

---

## 4. Como Executar

### 4.1. Executar apenas o modelo virtual (Simulação)
Abra o modelo: "simulink_model/robot_multibody.slx"


E clique em **Run** no Simulink.

---

### 4.2. Abrir a interface (GUI)

```matlab
run matlab_interface/mainInterface.m
```

Dentro da interface você encontrará três modos principais:

- Real-Time Video/Telemetry
- Forward Kinematics (FK)
- Control Mode (PID + Trajetórias)

### 4.3. Modo Hardware (ESP32)

1. Suba o firmware da pasta /esp32_firmware/ para o ESP32

2. Configure IP e porta no arquivo: matlab_interface/utils/tcp_setup.m

3. Na GUI, clique em Connect para estabelecer comunicação

4. O manipulador físico começará a responder aos comandos enviados

## 5. Comunicação TCP/IP

MATLAB → ESP32 (comandos)
{ "cmd": "setAngles", "theta": [t1, t2, t3, t4, t5] }

ESP32 → MATLAB (telemetria)
{ "t": 123.4, "angles": [...], "pos": [x, y, z] }

O protocolo segue formato JSON para simplicidade e depuração.

## 5. Status do Projeto

| Módulo                         | Status             |
| ------------------------------ | ------------------ |
| Modelo CAD                     | Concluído          |
| Exportação SMBL                | Concluído          |
| Gêmeo Digital no Simscape      | Concluído          |
| Interface GUIDE                | Funcional          |
| Comunicação TCP MATLAB ↔ ESP32 | Testada            |
| Controle Físico                | Operacional        |
| Melhorias Educacionais         | Em desenvolvimento |

## 7. Próximos Passos

- Adicionar visualização 3D interativa na GUI
- Criar laboratórios didáticos (cinemática, controle, trajetória)
- Implementar geração automática de relatórios
- Integrar métricas de desempenho e telemetria avançada
- Preparar documentação final para submissão ao desafio

## 8. Equipe

- Luan Gomes — Interface MATLAB, Simscape, comunicação TCP/IP
- Matheus Soares — Firmware ESP32, controle físico em tempo real
