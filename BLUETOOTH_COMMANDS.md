# 📱 Guía de Control Bluetooth

## 🔌 Conexión

1. Abre una app de **Serial Bluetooth Terminal** en tu teléfono (Android/iOS)
2. Busca el dispositivo: **`Carrito_ESP32`**
3. Conéctate (no requiere contraseña)

## 🎮 Comandos disponibles

### Movimiento básico
```
W         → Acelerar adelante
S         → Retroceder
A         → Girar izquierda
D         → Girar derecha
X / SPACE → Detener
```

### Direccionales
```
I         → Toggle direccional izquierda
J         → Toggle direccional derecha
```

### Control diferencial (avanzado)
Permite acelerar y girar simultáneamente. Enviar con salto de línea (`\n`):
```
V255G0\n    → Adelante a máxima velocidad, sin giro
V255G-120\n → Adelante con giro suave izquierda
V255G120\n  → Adelante con giro suave derecha
V-200G0\n   → Reversa sin giro
V128G-255\n → Media velocidad con giro máximo izquierda
```

**Formato:** `V<velocidad>G<giro>\n`
- Velocidad: -255 (atrás) a 255 (adelante)
- Giro: -255 (izquierda) a 255 (derecha)

## 📊 Respuestas del ESP32

- `OK` → Comando ejecutado correctamente
- `ERROR: Comando desconocido` → Comando inválido

## 🛠️ Apps recomendadas

### Android
- [Serial Bluetooth Terminal](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal)
- Bluetooth Electronics

### iOS
- BLE Terminal
- Bluetooth Terminal

## 💡 Ejemplo de uso

```
W         → El carrito acelera
(esperar 2 segundos hasta que entre en modo crucero)
A         → Empieza a girar izquierda mientras acelera
X         → Se detiene completamente
I         → Enciende direccional izquierda
I         → Apaga direccional izquierda
V200G-80\n → Control diferencial: avanza con giro suave a la izquierda
```

## ⚡ Ventajas del control Bluetooth

- ✅ **Lag mínimo**: ~5-20ms (vs ~50-200ms de WiFi)
- ✅ **Más estable**: No depende de HTTP/TCP
- ✅ **Funciona a distancia**: 10-30 metros
- ✅ **Consume menos batería** que WiFi
