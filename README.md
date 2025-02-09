# Comunicação Serial, UART e I2C com Raspberry Pi Pico W

## Descrição
O projeto consiste em utilizar a placa BitDogLab para aplicar conceitos de UART e I2C, utilizando comunicação serial no RP2040 e explorar as funcionalidades da placa de deesenvolvimento.

## Funcionalidades
O Botões permitem controlar a matriz de LEDs com as seguintes funcionalidades, a partir de IRQ:

- **Botão A**: Alterna o estado do LED verde.
- **Botão B**: Alterna o estado do LED azul
- **Display**: Exibe caracteres recebidos via UART, e o estado dos LEDs.
- **Matriz de LEDs**: Exibe uma configuração de LEDs, para cada algarismo recebido via UART.

[Vídeo de Demonstração](https://youtube.com/shorts/AaEvV6LRgiA?si=8f5KfNi4N4Vcw2iU)

## Como compilar
Para compilar o programa, utilize um compilador C, gerando os arquivos `.uf2` e `.elf`. Siga os passos abaixo:

1. Configure o ambiente de desenvolvimento para o Raspberry Pi Pico.
2. Compile o código utilizando um compilador compatível.

Segue um exemplo do botão de compilação:

![botao compilador](fotos_readme/compilador.png)

## Como executar

1. Plugue sua placa BitDogLab via cabo micro-usb.
2. Ative o modo bootset da placa.
3. Clique no botão Run.
4. Pressione os botões A e B para controlar os LEDs e exibir o estado atual no display.
5. Envie caracteres via UART para a placa. (O código não lida com caracteres especiais, apenas letras e algarismos)

![botao compilador](fotos_readme/serial.png)

## Requisitos
- Compilador C (gcc ou equivalente).
- Sistema operacional compatível com programas C.
- Extensão Raspberry Pi Pico.
- Placa BitDogLab

### Observação
- Caso queira rodar o código na extensão wokwi, será necessário criar e configurar os arquivos .toml e .json necessários.