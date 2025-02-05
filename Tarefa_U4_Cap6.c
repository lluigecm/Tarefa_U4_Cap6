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

ssd1306_t ssd;          // Inicialização da estrutura do display OLED

int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
