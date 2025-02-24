# Comunicação Serial, UART e I2C com Raspberry Pi Pico W 🚀

## Descrição 📝
Este projeto utiliza a placa **BitDogLab** para explorar conceitos de comunicação **UART** e **I2C**, aplicando comunicação serial no **RP2040** e demonstrando as funcionalidades da placa de desenvolvimento. 🛠️

---

## Funcionalidades 🎮
Os botões da placa permitem controlar a matriz de LEDs através de interrupções (IRQ), com as seguintes funcionalidades:

- **Botão A**: Alterna o estado do **LED verde** 💚.
- **Botão B**: Alterna o estado do **LED azul** 💙.
- **Display**: Exibe caracteres recebidos via **UART** e o estado atual dos LEDs 📟.
- **Matriz de LEDs**: Exibe uma configuração de LEDs correspondente a cada algarismo recebido via **UART** 🔢.

[**Vídeo de Demonstração** 🎥](https://youtube.com/shorts/AaEvV6LRgiA?si=8f5KfNi4N4Vcw2iU)

---

## Como Compilar 🛠️
Para compilar o programa, siga os passos abaixo:

1. Configure o ambiente de desenvolvimento para o **Raspberry Pi Pico**.
2. Utilize um compilador C compatível para gerar os arquivos `.uf2` e `.elf`.

Exemplo de botão de compilação:

![Botão Compilador](fotos_readme/compilador.png)

---

## Como Executar ⚡

1. Conecte a placa **BitDogLab** via cabo **micro-USB** 🔌.
2. Ative o modo **bootset** da placa.
3. Clique no botão **Run** ▶️.
4. Pressione os botões **A** e **B** para controlar os LEDs e exibir o estado atual no display 🎛️.
5. Envie caracteres via **UART** para a placa. *(O código suporta apenas letras e algarismos, sem caracteres especiais.)* 📨

Monitor serial no VScode:

![Interface Serial](fotos_readme/serial.png)

---

## Requisitos 📋

- Compilador C (ex: **gcc** ou equivalente) 🖥️.
- Sistema operacional compatível com programas em C.
- Extensão **Raspberry Pi Pico**.
- Placa **BitDogLab**.

---

## Observação ℹ️
Caso deseje executar o código na extensão **Wokwi**, será necessário criar e configurar os arquivos `.toml` e `.json` adequados. 🛠️

--- 