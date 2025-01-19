## Controle de pinos GPIO com o emprego de um teclado matricial.


Descrição: O projeto implementa um sistema de controle de LEDs e um buzzer utilizando um teclado matricial com o microcontrolador Raspberry Pi Pico. O código foi escrito em C utilizando a biblioteca Pico SDK.

## Funcionalidades:
- Tecla A: Acende o LED azul.
- Tecla B: Acende o LED verde.
- Tecla C: Acende o LED vermelho.
- Tecla D: Acende o LED azul.
- Tecla #: Aciona o buzzer e desliga demais leds.
## Componentes:
- Teclado matricial 4x4.
- 03 LEDs – tipo RGB.
- Componente Buzzer.
- Microcontrolador Raspberry Pi Pico W.
## Conexões:
- LED Azul: GPIO 11;
- LED Verde: GPIO 12;
- LED Vermelho: GPIO 13;
- Buzzer: GPIO 21;
- Teclado Matricial:
- LINHAS: GPIOs = {0, 1, 2, 3};
- COLUNAS: GPIOs = {4, 5, 6, 7};
## Modo de uso
Faça a conexão dos LEDs, o buzzer e o teclado matricial aos pinos do Raspberry Pi Pico W conforme a descrição. Compile o código utilizando o Pico SDK e carregue-o no seu Raspberry Pi Pico W. Ao pressionar as teclas do teclado, o sistema irá acionar os LEDs e o buzzer conforme o mapeamento das teclas.

## Projeto Workwi:
https://wokwi.com/projects/420451409076869121

## Projeto VS Code
![image](https://github.com/user-attachments/assets/6385b470-3f1b-4eba-ba73-b170f0932c5a)
