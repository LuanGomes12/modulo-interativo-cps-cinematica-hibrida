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

/cad/ inventor: pças 3D, modelo completo e exportações do plug-in Simscape Multibody Link

/modelo simulink/ Modelo Simscape Multibody do manipulador e interface gráfica

/esp32_firmware/ Código do ESP32 (TCP server + controle)

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
- Autodesk Inventor 2022 ou superior  
- Plugin **Simscape Multibody Link** instalado e configurado

**OBS:** o plugin deve ser na mesma versão do MATLAB!!!  

### ESP32
- PlatformIO ou Arduino IDE  
- Bibliotecas utilizadas:
  - WiFi  
  - ESP32Servo

---

## 4. Como Executar

### 4.1. Abrir a interface (GUI)

Abra o arquivo: "modelo simulink/Graphic_Interface.m"

Em seguida, execute o arquivo no MATLAB clicando em **Run** ou usando:

```matlab
run Graphic_Interface.m
```

Dentro da interface você encontrará três janelas principais:

- Real-Time Video
- Forward Kinematics
- Control Mode

Em seguida, na janela **Control Mode**, pressione **Start**. Isso irá abrir o modelo **Montagem1.slx** no Simulink.

**OBS:** caso o modelo não execute, você precisará alterar o caminho do diretório responsável por carregar as informações do modelo. Para isso, siga as instruções abaixo:
1. Vá em: **MODELING** -> **DESIGN** -> **Model Explorer**
2. Na janela que abrir, acesse:
  **Montagem1** -> **Model Workspace** -> **Filename**

3. Altere o caminho
   ```matlab
   C:\Users\luanl\Documents\Matlab\Proj_BracoRobotico\BracoCompleto\Prototipo4\Montagem_DataFile.mat
   ```
    para o diretório correspondente onde está localizado o arquivo **Montagem_DataFile.mat** que você baixou. 

4. Feche o MATLAB, abra novamente, execute a interface e pressione **Start**.

**Caso ainda não funcione, utilize o método alternativo:**

1. Abra o arquivo:
modelo simulink/Montagem1.slx

2. Vá em: **MODELING** -> **SETUP** -> **Model Properties** → **Callbacks**
   
3. Clique em **PreLoadFcn**
Aparece uma caixa de texto em branco.

4. Insira exatamente o seguinte conteúdo:
```matlab
Montagem_DataFile
```

5. Clique **Apply** e salve o modelo.
   
6. Feche o MATLAB e abra novamente. Execute a interface e pressione **Start**.

### 4.2. Executar apenas o modelo virtual (Simulação)
Para executar somente o modelo virtual sem abrir a interface:
```matlab
modelo simulink/Montagem1.slx
```

E clique em **Run** no Simulink.

---

### 4.3. Modo Hardware (ESP32)

1. Suba o firmware localizado em:
```matlab
/esp32_firmware/
```

2. Configure o IP e a porta gerados pelo ESP32 dentro do modelo:
```matlab
modelo simulink/montagem1.slx
```

3. No bloco **TCP/IP Send**, configure o endereço IP e as portas geradas pelo access point do ESP32.

4. Após configurado, o manipulador físico começará a responder aos comandos enviados pelo Simulink.

## 5. Comunicação TCP/IP

MATLAB → ESP32 (comandos)
{ "cmd": "setAngles", "theta": [t1, t2, t3, t4, t5] }

ESP32 → MATLAB (telemetria)
{ "t": 123.4, "angles": [...], "pos": [x, y, z] }

O protocolo segue formato JSON para simplicidade e depuração.

## 6. Status do Projeto

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
