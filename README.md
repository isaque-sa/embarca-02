# Controle de LEDs e Buzzer com Teclado Matricial no Raspberry Pi Pico

Este projeto implementa o controle de LEDs e um buzzer utilizando um teclado matricial no Raspberry Pi Pico. Dependendo da tecla pressionada, diferentes LEDs são ativados, o buzzer pode emitir som, ou o dispositivo pode ser reiniciado em modo USB.

---

## ⚙️ Funcionalidades

1. **Controle de LEDs:**
   - Tecla `A`: Liga o LED verde.
   - Tecla `B`: Liga o LED azul.
   - Tecla `C`: Liga o LED vermelho.
   - Tecla `D`: Liga todos os LEDs simultaneamente.

2. **Controle do Buzzer:**
   - Tecla `#`: Ativa o buzzer por 1 segundo e desliga todos os LEDs.

3. **Reinicialização:**
   - Tecla `*`: Reinicia o Raspberry Pi Pico em modo USB Boot.

4. **Leitura de Teclado Matricial:**
   - Lê teclas pressionadas no teclado matricial 4x4 e executa ações correspondentes.

---

## 🛠️ Configuração de Hardware

### Pinos Utilizados

- **LEDs:**
  - LED Verde: GPIO 11
  - LED Azul: GPIO 12
  - LED Vermelho: GPIO 13
- **Buzzer:**
  - GPIO 21
- **Teclado Matricial:**
  - Linhas: GPIOs 2, 3, 4, 5
  - Colunas: GPIOs 6, 7, 8, 9

### Esquema de Conexão
1. Conecte os LEDs e o buzzer nos pinos especificados.
2. Conecte o teclado matricial aos GPIOs configurados.
3. Certifique-se de utilizar resistores para os LEDs e um resistor pull-down/pull-up para o teclado, se necessário.

---

## 📋 Requisitos de Software

- **SDK do Raspberry Pi Pico**
  - Instale e configure o SDK do Pico conforme a [documentação oficial](https://github.com/raspberrypi/pico-sdk).

- **Bibliotecas Incluídas:**
  - `pico/stdlib.h`: Fornece funções básicas para GPIO.
  - `hardware/gpio.h`: Para manipulação de pinos GPIO.
  - `pico/bootrom.h`: Para reinicializar o Pico em modo USB Boot.

---
