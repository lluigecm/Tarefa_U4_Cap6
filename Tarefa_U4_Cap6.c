#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include "inc/matriz_leds.h"


#define RED_LED 13
#define GREEN_LED 11
#define BLUE_LED 12     // Definições pinos LEDs e botões
#define BUTTON_A 5
#define BUTTON_B 6

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15      // Definições I2C (DISPLAY OLED - SSD1306)
#define endereco 0x3C


int main()
{
    stdio_init_all();
    
    i2c_init(I2C_PORT, 400*1000); // Inicializa o barramento I2C
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Define os pinos SDA e SCL
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA); // Habilita os pull-ups
    gpio_pull_up(I2C_SCL);
    ssd1306_t ssd;          // Inicialização da estrutura do display OLED
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display OLED
    ssd1306_config(&ssd);   // Configura o display OLED
    ssd1306_send_data(&ssd); // Envia os dados para o display

    ssd1306_fill(&ssd, false); // Limpa o display
    ssd1306_send_data(&ssd);   // Envia os dados para o display

    bool cor = true;
    while (true) {

        cor = !cor;

        ssd1306_fill(&ssd, cor); // Limpa o display
        ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
        ssd1306_draw_string(&ssd, "Testando Oled", 8, 10);
        ssd1306_draw_string(&ssd, "Embarca Tech", 20, 30);
        ssd1306_draw_string(&ssd, "Lucas Luige", 15, 48);
        ssd1306_send_data(&ssd); // Envia os dados para o display

        sleep_ms(2000);

    }
}
