#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "pico/cyw43_arch.h"

// Define GPIO para os LEDs de saída
#define GPIO_RED_LED 13
#define GPIO_GREEN_LED 11
#define GPIO_BLUE_LED 12

// Define GPIO para os buzzers
#define BUZZER_A 21
#define BUZZER_B 10

// Define tempo para T01 e T02
#define T01_TIME 1000000
#define T02_TIME 150

// Define os pinos do teclado com as portas GPIO
uint columns[4] = {5, 4, 3, 2}; 
uint rows[4] = {9, 8, 7, 6};

// Mapa de teclas
char KEY_MAP[16] = {
    '1', '2' , '3', 'A',
    '4', '5' , '6', 'B',
    '7', '8' , '9', 'C',
    '*', '0' , '#', 'D'
};

// Mascaras para leitura simultaneas de multiplos gpio
uint all_columns_mask = 0x0;
uint column_mask[4];

// Imprimir valor binário
void imprimir_binario(int num) {
    int i;
    for (i = 31; i >= 0; i--) {
        (num & (1 << i)) ? printf("1") : printf("0");
    }
}

// Inicializa o keypad
void pico_keypad_init(void) {

    for (int i = 0; i < 4; i++) {

        gpio_init(columns[i]);
        gpio_init(rows[i]);

        gpio_set_dir(columns[i], GPIO_IN);
        gpio_set_dir(rows[i], GPIO_OUT);
        gpio_pull_down(columns[i]);

        gpio_put(rows[i], 0);

        all_columns_mask = all_columns_mask + (1 << columns[i]);
        column_mask[i] = 1 << columns[i];
    }
}

// Faz leitura da tecla pressionada
char pico_keypad_get_key(void) {
    int row;
    uint32_t cols;

    for (int j = 0; j < 4; j++) {
        gpio_put(rows[j], 1);
    }

    cols = gpio_get_all();
    cols = cols & all_columns_mask;
    //imprimir_binario(cols);
    
    if (cols == 0x0) {
        return 0;
    }

    for (int j = 0; j < 4; j++) {
        gpio_put(rows[j], 0);
    }

    for (row = 0; row < 4; row++) {

        gpio_put(rows[row], 1);

        cols = gpio_get_all();
        gpio_put(rows[row], 0);
        cols = cols & all_columns_mask;
        if (cols != 0x0) {
            break;
        }   
    }

    if (cols == column_mask[0]) {
        return (char) KEY_MAP[row * 4 + 0];
    }
    else if (cols == column_mask[1]) {
        return (char) KEY_MAP[row * 4 + 1];
    }
    if (cols == column_mask[2]) {
        return (char) KEY_MAP[row * 4 + 2];
    }
    else if (cols == column_mask[3]) {
        return (char) KEY_MAP[row * 4 + 3];
    }
    else {
        return 0;
    }
}

// Temporizador 01
static bool T01(bool IN, uint64_t time_us){
    static uint64_t prev_time;
    static uint64_t curr_time;
    static bool set_value;

    if(!IN){
        curr_time = time_us_64();
        prev_time = curr_time;
        set_value = false;
    }else{
        curr_time = time_us_64();
        if(curr_time - prev_time >= time_us)
            set_value = true;
    }
    return set_value;
}

// Temporizador 02
static bool T02(bool IN, uint64_t time_us){
    static uint64_t prev_time;
    static uint64_t curr_time;
    static bool set_value;

    if(!IN){
        curr_time = time_us_64();
        prev_time = curr_time;
        set_value = false;
    }else{
        curr_time = time_us_64();
        if(curr_time - prev_time >= time_us)
            set_value = true;
    }
    return set_value;
}

// Geracao do sinal para os buzzers
static bool song_gen(bool * IN_T, uint64_t T_Time, bool (*Timer)(bool,uint64_t)){
    static bool song_out = 0;

    if(!*IN_T && !Timer(*IN_T,T_Time))
        *IN_T = 1;

    if(Timer(*IN_T,T_Time) && !song_out)
        song_out = 1;
    else if(Timer(*IN_T,T_Time) && song_out)
        song_out = 0;

    if(Timer(*IN_T,T_Time))
        *IN_T = 0;
  
    return song_out;
}

// Funcao principal
int main() {
    bool IN1_T = 0, IN2_T = 0;
    char character_press;

    stdio_init_all();
    pico_keypad_init();

    // Inicializa os LEDs
    gpio_init(GPIO_RED_LED);
    gpio_set_dir(GPIO_RED_LED, GPIO_OUT);
    gpio_init(GPIO_GREEN_LED);
    gpio_set_dir(GPIO_GREEN_LED, GPIO_OUT);
    gpio_init(GPIO_BLUE_LED);
    gpio_set_dir(GPIO_BLUE_LED, GPIO_OUT);

    // Inicializa os buzzers
    gpio_init(BUZZER_A);
    gpio_set_dir(BUZZER_A, GPIO_OUT);
    gpio_init(BUZZER_B);
    gpio_set_dir(BUZZER_B, GPIO_OUT);

    while (true) {
        // Leitura do teclado
        if(!IN1_T && !T01(IN1_T,T01_TIME))
            IN1_T = 1;

        if(T01(IN1_T,T01_TIME)){
            character_press = pico_keypad_get_key();
            printf("\nTecla pressionada: %c\n", character_press);
        }

        if(T01(IN1_T,T01_TIME))
            IN1_T = 0;

        // Avaliacao de caractere para o RED_LED
        if (character_press=='A')
        {
            gpio_put_masked(0x3800,0x2000);
            gpio_put(BUZZER_A,0);
            gpio_put(BUZZER_B,0);
        }

        // Avaliacao de caractere para o GREEN_LED
        if (character_press=='B')
        {
            gpio_put_masked(0x3800,0x800);
            gpio_put(BUZZER_A,0);
            gpio_put(BUZZER_B,0);
        }

        // Avaliacao de caractere para o BLUE_LED
        if (character_press=='C')
        {
            gpio_put_masked(0x3800,0x1000);
            gpio_put(BUZZER_A,0);
            gpio_put(BUZZER_B,0);
        }

        // Avaliacao de caractere para o RGB_LED
        if (character_press=='D')
        {
            gpio_put_masked(0x3800,0x3800);
            gpio_put(BUZZER_A,0);
            gpio_put(BUZZER_B,0);
        }

        // Avaliacao de caractere para os buzzers
        if (character_press=='#')
        {
            gpio_put_masked(0x3800,0x0);
            gpio_put(BUZZER_A, song_gen(& IN2_T,T02_TIME,T02));
            gpio_put(BUZZER_B, song_gen(& IN2_T,T02_TIME,T02));
        }

        // Avaliacao de caractere para o desligar tudo
        if (character_press=='*')
        {
            gpio_put_masked(0x3800,0x0);
            gpio_put(BUZZER_A,0);
            gpio_put(BUZZER_B,0);
        }
    }
    return 0;
}
