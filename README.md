# Controle de LEDs e Buzzer com Teclado Matricial

Este projeto implementa um sistema de controle de LEDs e um buzzer utilizando um teclado matricial com o microcontrolador Raspberry Pi Pico. O código foi escrito em C utilizando a biblioteca Pico SDK.

### Funcionalidades
- **Controle de LEDs**: Quando teclas específicas (A, B, C ou D) são pressionadas, diferentes LEDs são acesos:
  - Tecla `A`: Acende o LED verde.
  - Tecla `B`: Acende o LED azul.
  - Tecla `C`: Acende o LED vermelho.
  - Tecla `D`: Acende todos os LEDs.
  
- **Controle do Buzzer**: 
  - Tecla `#`: Ativa o buzzer por 1 segundo.
  - Tecla `*`: Desliga qualquer LED ativo e/ou buzzer.

### Requisitos
- Raspberry Pi Pico
- Teclado matricial 4x4
- LEDs (verde, azul, vermelho)
- Buzzer
- Pico SDK

### Conexões de Hardware
- **LEDs**:
  - LED Verde: GPIO 11
  - LED Azul: GPIO 12
  - LED Vermelho: GPIO 13
- **Buzzer**: GPIO 21
- **Teclado Matricial**:
  - LINHAS: GPIOs 2, 3, 4, 5
  - COLUNAS: GPIOs 6, 7, 8, 9

### Como usar
1. Conecte os LEDs, o buzzer e o teclado matricial aos pinos do Raspberry Pi Pico conforme a descrição acima.
2. Compile o código utilizando o Pico SDK e carregue-o no seu Raspberry Pi Pico.
3. Ao pressionar as teclas do teclado, o sistema irá acionar os LEDs e o buzzer conforme o mapeamento das teclas.

### Projeto no Wokwi
Você pode visualizar e testar o projeto no simulador online Wokwi através deste [link para o projeto no Wokwi](https://wokwi.com/projects/420174053898719233).

### Licença
Este projeto é de código aberto e pode ser utilizado sob a licença MIT.
