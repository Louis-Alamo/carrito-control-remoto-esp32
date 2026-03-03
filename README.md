# 🏎️ Carrito Control Remoto ESP32

Este proyecto implementa un sistema de control remoto para un carrito robótico utilizando un **ESP32** y comunicación **Bluetooth Serial**. El sistema permite controlar el movimiento (velocidad y dirección) del vehículo desde un smartphone.

## ✨ Características

- **Control Bluetooth de Baja Latencia**: Respuesta rápida (~5-20ms) para un manejo preciso.
- **Manejo Diferencial**: Control independiente de motores para movimientos suaves y giros sobre el propio eje.
- **Seguridad Activa**: Detención automática del vehículo si se pierde la conexión Bluetooth.
- **Protocolo de Comandos Eficiente**: Comandos simples para control total (ej. `V255G0`).

## 🛠️ Requisitos de Hardware

- **Microcontrolador**: 1 x ESP32.
- **Motores**: 4 x Motoreductores de 5V.
- **Driver de Motores**: 1 x L298N.
- **Fuente de Alimentación**: 6 x Baterías de 1.5V (o similar, dependiendo de la potencia deseada).

## 💻 Requisitos de Software

- **PlatformIO**: Para gestión del proyecto, compilación y carga.
- **Framework Arduino**: Base del desarrollo.
- **App para control de Bluetooth**: Cualquier aplicación que permita enviar datos seriales (Terminal, Joystick, Controlador personalizado, etc).

## 🚀 Instalación y Carga

1.  **Clonar el repositorio**:
    ```bash
    git clone https://github.com/Louis-Alamo/carrito-control-remoto-esp32.git
    cd carrito-control-remoto-esp32
    ```

2.  **Abrir en PlatformIO**:
    Abre la carpeta del proyecto en VS Code con la extensión de PlatformIO instalada.

3.  **Compilar y Subir**:
    Conecta tu ESP32 por USB y ejecuta:
    ```bash
    pio run -t upload
    ```

4.  **Monitor Serial** (Opcional):
    Para ver logs de depuración:
    ```bash
    pio device monitor
    ```

## 🎮 Instrucciones de Uso

**Nota Importante:** Este proyecto consiste únicamente en el código para el ESP32. **No incluye una aplicación móvil dedicada.**

Para controlar el carrito, puedes utilizar **cualquier aplicación** que sirva para enviar comandos por Bluetooth (Terminal, Joystick, etc).

1.  Enciende el carrito.
2.  Abre tu aplicación de terminal Bluetooth preferida.
3.  Busca y conéctate al dispositivo llamado **`Carrito_ESP32`**.
4.  Una vez conectado, envía los siguientes caracteres para controlar el vehículo:

### Lista de Comandos

| Tecla           | Acción                         |
| :-------------- | :----------------------------- |
| **W**           | Acelerar adelante              |
| **S**           | Retroceder                     |
| **A**           | Girar izquierda                |
| **D**           | Girar derecha                  |
| **X** o Espacio | Detenerse                      |
| **I**           | Toggle direccional izquierda   |
| **J**           | Toggle direccional derecha     |

### Comandos Avanzados (Velocidad + Giro)

Para un control más preciso, puedes enviar comandos con el formato `V<velocidad>G<giro>` seguidos de un salto de línea (`\n`):

-   **Velocidad (V)**: `-255` (atrás) a `255` (adelante).
-   **Giro (G)**: `-255` (izquierda) a `255` (derecha).

**Ejemplos:**
-   `V255G0\n` (Adelante rápido)
-   `V255G-120\n` (Adelante girando izquierda)

> ℹ️ Para más detalles sobre los comandos, consulta el archivo [BLUETOOTH_COMMANDS.md](BLUETOOTH_COMMANDS.md).

## 📂 Estructura del Proyecto

-   `src/`: Código fuente C++.
    -   `main.cpp`: Punto de entrada y configuración principal.
    -   `BluetoothManager`: Gestión de la conexión Bluetooth.
    -   `CarritoService`: Lógica de control del vehículo.
-   `include/`: Archivos de cabecera (.h).
-   `platformio.ini`: Configuración del entorno de compilación.
-   

## Colaboradores

*   [Carlos Emmanuel](https://github.com/Carlos-Emmanuel-ISC6)
*   [Louis Alamo](https://github.com/Louis-Alamo)
