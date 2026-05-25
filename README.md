# Integração de um Modelo Digital Baseado em Cinemática Híbrida e Aprendizado de Máquina em um Manipulador Robótico Didático de 5 Juntas Rotativas
[![MATLAB](https://img.shields.io/badge/MATLAB-R2021a%2B-blue.svg)](https://www.mathworks.com/products/matlab.html)
[![ESP32](https://img.shields.io/badge/ESP32-C%2B%2B-green.svg)](https://www.espressif.com/)
[![Status](https://img.shields.io/badge/Status-Operacional-success.svg)]()

Este repositório contém o código-fonte, os modelos 3D e o *firmware* referentes ao desenvolvimento de um sistema ciber-físico interativo para controle, visualização e telemetria de um manipulador robótico didático. 

Este trabalho foi desenvolvido para a dissertação de mestrado do **Programa de Pós-Graduação em Engenharia Elétrica e de Computação (PPGEEC)** da Universidade Federal do Ceará (UFC), campus Sobral.

O objetivo principal é fornecer uma plataforma educacional e experimental (**Manipula.EDU**) que una simulação, controle, visualização e execução física em um único sistema modular, solucionando a subdeterminação da Cinemática Inversa por meio de Redes Neurais.

---

## 🚀 O Projeto Integra:

- **Modelo Mecânico CAD:** Desenvolvido e montado no Autodesk Inventor.
- **Modelo Digital (Simulação Dinâmica):** Construído no Simscape Multibody.
- **Interface Gráfica Interativa:** Desenvolvida em MATLAB (App Designer).
- **Inteligência Artificial:** Resolução da Cinemática Inversa Híbrida utilizando o modelo Perceptron de Múltiplas Camadas (MLP).
- **Comunicação Sem Fio:** Protocolo TCP/IP assíncrono entre o PC (*Host*) e o microcontrolador ESP32 (*Edge Device*).
- **Atuação Física:** Controle multiplexado de servomotores MG995 e MG90S.

---

## 📐 Arquitetura Geral do Sistema

<img width="821" height="511" alt="Arquitetura_Metodologia" src="https://github.com/user-attachments/assets/3650f28d-e755-4a0a-954d-fe0b25f18a89" />

A comunicação ocorre via rede local sem fio (WLAN) estabelecida pelo próprio ESP32 em modo *Access Point* (AP), garantindo baixa latência e sincronização contínua entre o hardware de acrílico e o modelo virtual no Simulink.

---

## 📁 Estrutura do Repositório

```
├── /cad_inventor/       # Peças 3D, montagem completa e exportações do Simscape Multibody Link
├── /modelo_simulink/    # Modelo Simscape Multibody do manipulador e arquivos .mlapp (Interface)
├── /esp32_firmware/     # Código C++ do ESP32 (Servidor TCP, Parsing de bytes e Controle PWM)
└── README.md
```

---

## 💻 Requisitos de Software e Hardware

### MATLAB (Host)
- Versão: R2021a ou superior  
- Toolboxes necessárias:
  - Simulink  
  - Simscape  
  - Simscape Multibody  
  - Instrument Control Toolbox (para TCP/IP)  

### Autodesk Inventor
- Versão: 2022  
- Plugin **Simscape Multibody Link** instalado e configurado

**OBS:** o plugin deve ser na mesma versão do MATLAB!!!  

### ESP32
- Ambiente: PlatformIO ou Arduino IDE  
- Bibliotecas utilizadas:
  - WiFi  
  - ESP32Servo

---

## 📡 Protocolo de Comunicação TCP/IP

Para garantir desempenho e evitar overhead na rede educacional, a comunicação não utiliza strings ou JSON. O Simulink empacota as variáveis em ponto flutuante e transmite um payload bruto (vetor de bytes).

- Estrutura do Pacote de Envio (26 Bytes - MATLAB → ESP32):
  - [1 byte] Cabeçalho de sincronização (0xAA).
  - [25 bytes] 5 blocos correspondentes às 5 juntas, onde cada bloco contém:
    - [1 byte] ASCII ID da junta (ex: 'A', 'B').
    - [4 bytes] Valor angular em float (single IEEE 754).

O ESP32 recebe o pacote e utiliza uma estrutura de dados union em C++ para remontar os bytes diretamente na memória e aplicar o sinal aos servomotores, respeitando as restrições físicas (travas lógicas) da estrutura de acrílico.

## 📊 Status do Projeto

| Módulo                                      | Status                 |
|--------------------------------------------|------------------------|
| Modelo CAD (Inventor)                      | ✅ Concluído           |
| Exportação SMBL                            | ✅ Concluído           |
| Modelo Digital (Simscape)                  | ✅ Concluído           |
| App Designer (Manipula.EDU)                | ✅ Concluído           |
| IA (Predição de Pitch via MLP)             | ✅ Concluído           |
| Comunicação TCP MATLAB ↔ ESP32             | ✅ Testada/Operacional |
| Execução Física (Sincronismo)              | ✅ Operacional         |
| Implementação de Sensores (Malha Fechada)  | ⏳ Trabalhos Futuros   |

## 👤 Autor

- Luan Gomes Magalhães Lima
