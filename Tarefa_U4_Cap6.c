#include <stdio.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "inc/ssd1306.h"
#include "matriz_leds.h"

#define RED_LED 13
#define GREEN_LED 11
#define BLUE_LED 12     // Definições pinos LEDs e botões
#define BUTTON_A 5
#define BUTTON_B 6

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15      // Definições I2C (DISPLAY OLED - SSD1306)
#define endereco 0x3C

ssd1306_t ssd;          // Inicialização da estrutura do display OLED
bool cor = true;

uint last_time= 0;      // Variavel auxiliar para debounce

const Matriz_leds_config zero = {
    {{0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
};

const Matriz_leds_config one = {
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
};

const Matriz_leds_config two =  {
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.0}}  // Linha 4
};

const Matriz_leds_config three = {
    {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.0}, {0.05, 0.05, 0.0}, {0.05, 0.05, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.0}, {0.05, 0.05, 0.0}, {0.05, 0.05, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.0}, {0.05, 0.05, 0.0}, {0.05, 0.05, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
};

const Matriz_leds_config four = {
    {{0.0, 0.0, 0.0}, {0.05, 0.0, 0.05}, {0.0, 0.0, 0.0}, {0.05, 0.0, 0.05}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.05, 0.0, 0.05}, {0.0, 0.0, 0.0}, {0.05, 0.0, 0.05}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.05, 0.0, 0.05}, {0.05, 0.0, 0.05}, {0.05, 0.0, 0.05}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.0, 0.05}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.0, 0.05}, {0.0, 0.0, 0.0}}  // Linha 4
};

const Matriz_leds_config five = {
    {{0.0, 0.0, 0.0}, {0.0, 0.05, 0.05}, {0.0, 0.05, 0.05}, {0.0, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.0, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.0, 0.05, 0.05}, {0.0, 0.05, 0.05}, {0.0, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.05, 0.05}, {0.0, 0.05, 0.05}, {0.0, 0.05, 0.05}, {0.0, 0.0, 0.0}}  // Linha 4
};

const Matriz_leds_config six = {
    {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}  // Linha 4
};

const Matriz_leds_config seven ={
    {{0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
};

const Matriz_leds_config eight ={
    {{0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.05, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
};

const Matriz_leds_config nine ={
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.05}, {0.0, 0.0, 0.0}}  // Linha 4
};

const Matriz_leds_config nothing = {

    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
};

Matriz_leds_config *nums[] = {&zero, &one, &two, &three, &four, &five, &six, &seven, &eight, &nine, &nothing};

void setup(){
    gpio_init(RED_LED);//--------------------------------|
    gpio_set_dir(RED_LED, GPIO_OUT);//                   |
//                                                       |
    gpio_init(GREEN_LED);//                              |
    gpio_set_dir(GREEN_LED, GPIO_OUT);//                 |
//                                                       |
    gpio_init(BLUE_LED);//                               |
    gpio_set_dir(BLUE_LED, GPIO_OUT);//                  |  Configuração dos LEDs e botões
//                                                       |
    gpio_init(BUTTON_A);//                               |
    gpio_set_dir(BUTTON_A, GPIO_IN);//                   |
    gpio_pull_up(BUTTON_A);//                            |
//                                                       |
    gpio_init(BUTTON_B);//                               |
    gpio_set_dir(BUTTON_B, GPIO_IN);//                   |
    gpio_pull_up(BUTTON_B);//----------------------------|

    i2c_init(I2C_PORT, 400*1000); // Inicializa o barramento I2C
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Define os pinos SDA e SCL
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA); // Habilita os pull-ups
    gpio_pull_up(I2C_SCL);
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display OLED
    ssd1306_config(&ssd);   // Configura o display OLED
    ssd1306_send_data(&ssd); // Envia os dados para o display
    
    ssd1306_fill(&ssd, false); // Limpa o display
    ssd1306_send_data(&ssd);   // Envia os dados para o display
}

void handle_uart(char c, PIO pio, uint sm){
    if(!isalpha(c) && !isdigit(c)){   // Verifica se o caracter é uma letra ou número
        printf("Caracter não reconhecido\n");
        return;
    }

    printf("Caracter enviado: %c\n", c);

    ssd1306_fill(&ssd, cor); // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 58, !cor, cor); // Desenha um retângulo
    ssd1306_draw_string(&ssd, "Caracter", 10, 10);
    ssd1306_draw_string(&ssd, "Recebido:", 10, 25);
    ssd1306_draw_char(&ssd, c, 64, 45);
    ssd1306_send_data(&ssd); // Envia os dados para o display

    if(isdigit(c)){
        imprimir_desenho(nums[c - '0'], pio, sm);   // Conversão de char para int implicita
    }

    sleep_ms(200); // Aguarda 200ms
}

bool debounce(){
    if(to_ms_since_boot(get_absolute_time()) - last_time > 200){      // Debounce de 200ms
        last_time = to_ms_since_boot(get_absolute_time());
        return true;
    }
    return false;
}

void button_callback(int gpio, uint32_t events){
    if(debounce()){
        ssd1306_fill(&ssd, cor); // Limpa o display
        ssd1306_rect(&ssd, 3, 3, 122, 58, !cor, cor); // Desenha um retângulo
        
        if(gpio == BUTTON_A){
        
            gpio_put(GREEN_LED, !gpio_get(GREEN_LED));;     // Alterna o estado do LED
            printf("Botão A pressionado e LED verde alternado\n");
        
            ssd1306_draw_string(&ssd, "LED Verde", 30, 10);
        
            if(gpio_get(GREEN_LED)){
                ssd1306_draw_string(&ssd, "Ligado", 30, 25);
            }else{
                ssd1306_draw_string(&ssd, "Desligado", 30, 25);
            }
        
        }
        
        if(gpio == BUTTON_B){

            gpio_put(BLUE_LED, !gpio_get(BLUE_LED));    // Alterna o estado do LED
            printf("Botão B pressionado e LED azul alternado\n");
            
            ssd1306_draw_string(&ssd, "LED Azul", 30, 10);
            
            if(gpio_get(BLUE_LED)){
                ssd1306_draw_string(&ssd, "Ligado", 30, 25);
            }else{
                ssd1306_draw_string(&ssd, "Desligado", 30, 25);
            }

        }
        ssd1306_send_data(&ssd); // Envia os dados para o display
    }
}

void display_init_config(){
    ssd1306_fill(&ssd, cor); // Limpa o display----------------------------------------|
    ssd1306_rect(&ssd, 3, 3, 122, 58, !cor, cor); // Desenha um retângulo              |
    ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 10);//                                |
    ssd1306_draw_string(&ssd, "03/02", 20, 25);//                                      |    Configuração inicial do display
    ssd1306_draw_string(&ssd, "Tarefa 1", 20, 40);//                                   |
    ssd1306_send_data(&ssd); // Envia os dados para o display--------------------------|
}

int main(){

    stdio_init_all();
    setup();

    PIO pio = pio0;
    uint sm = configurar_matriz(pio);

    display_init_config();  // Configuração inicial do display
    
    imprimir_desenho(nums[10], pio, sm);

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_callback);   // Configuração das interrupções

    while (true) {
        
        if(stdio_usb_connected()){  // Verifica se o USB está conectado
            char c;
            if(scanf("%c", &c) == 1){   // Verifica se há um caracter foi enviado
                handle_uart(c, pio, sm);
            }
        }

        sleep_ms(50);  // Aguarda 50ms entre cada iteração
    }
}