#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definição dos pinos dos LEDs
#define LED_VERMELHO_PINO 13
#define LED_VERDE_PINO 12
#define LED_AZUL_PINO 11

// Definição do pino do buzzer
#define BUZZER_PINO 21 

// Definição dos pinos do teclado matricial
#define LINHAS 4
#define COLUNAS 4

int linha_pinos[LINHAS] = {0, 1, 2, 3};  // Pinos de linhas (GPIO 0 a 3)
int coluna_pinos[COLUNAS] = {4, 5, 6, 7}; // Pinos de colunas (GPIO 4 a 7)

// Mapeamento do teclado 4x4
char tecla_matriz[LINHAS][COLUNAS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Função para inicializar os pinos do teclado
void configurar_teclado() {
    for (int i = 0; i < LINHAS; i++) {
        gpio_init(linha_pinos[i]);
        gpio_set_dir(linha_pinos[i], GPIO_OUT);
        gpio_put(linha_pinos[i], 1);  // Inicia as linhas com nível alto
    }

    for (int i = 0; i < COLUNAS; i++) {
        gpio_init(coluna_pinos[i]);
        gpio_set_dir(coluna_pinos[i], GPIO_IN);
        gpio_pull_up(coluna_pinos[i]); // Configura as colunas com pull-up
    }
}

// Função para ler o teclado
char ler_tecla() {
    for (int i = 0; i < LINHAS; i++) {
        // Coloca a linha em baixo (LOW)
        gpio_put(linha_pinos[i], 0);

        for (int j = 0; j < COLUNAS; j++) {
            if (!gpio_get(coluna_pinos[j])) {
                // Se a tecla for pressionada, retorna o caractere correspondente
                return tecla_matriz[i][j];
            }
        }

        // Retorna a linha para o estado alto
        gpio_put(linha_pinos[i], 1);
    }

    return 0;  // Nenhuma tecla pressionada
}

// Função para acionar os LEDs e o buzzer conforme a tecla pressionada
void acionar_leds_e_buzzer(char tecla) {
    // Desliga todos os LEDs e o buzzer
    gpio_put(LED_VERMELHO_PINO, 0);
    gpio_put(LED_VERDE_PINO, 0);
    gpio_put(LED_AZUL_PINO, 0);
    gpio_put(BUZZER_PINO, 0);

    if (tecla == 'A') {  // LED Azul
        gpio_put(LED_AZUL_PINO, 1);
    } else if (tecla == 'B') {  // LED Verde
        gpio_put(LED_VERDE_PINO, 1);
    } else if (tecla == 'C') {  // LED Vermelho
        gpio_put(LED_VERMELHO_PINO, 1);
    } else if (tecla == '#') {  // Buzzer
        gpio_put(BUZZER_PINO, 1);
    }
}

int main() {
    // Inicialização dos pinos
    gpio_init(LED_VERMELHO_PINO);
    gpio_set_dir(LED_VERMELHO_PINO, GPIO_OUT);
    gpio_init(LED_VERDE_PINO);
    gpio_set_dir(LED_VERDE_PINO, GPIO_OUT);
    gpio_init(LED_AZUL_PINO);
    gpio_set_dir(LED_AZUL_PINO, GPIO_OUT);
    gpio_init(BUZZER_PINO);
    gpio_set_dir(BUZZER_PINO, GPIO_OUT);

    // Inicializar o teclado
    configurar_teclado();

    while (true) {
        char tecla = ler_tecla();  // Lê a tecla pressionada
        if (tecla != 0) {
            acionar_leds_e_buzzer(tecla);  // Aciona os LEDs e o buzzer conforme a tecla
        }
        sleep_ms(100);  // Delay para evitar leitura múltipla de uma única tecla
    }

    return 0;
}
