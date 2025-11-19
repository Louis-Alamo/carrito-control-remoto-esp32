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
STOP      → Detener
```

### Direccionales
```
DI        → Toggle direccional izquierda
DD        → Toggle direccional derecha
```

### Control diferencial (avanzado)
Permite acelerar y girar simultáneamente:
```
V255G0    → Adelante a máxima velocidad, sin giro
V255G-120 → Adelante con giro suave izquierda
V255G120  → Adelante con giro suave derecha
V-200G0   → Reversa sin giro
V128G-255 → Media velocidad con giro máximo izquierda
```

**Formato:** `V<velocidad>G<giro>`
- Velocidad: -255 (atrás) a 255 (adelante)
- Giro: -255 (izquierda) a 255 (derecha)

## 📊 Respuestas del ESP32

- `OK` → Comando ejecutado correctamente
- `ERROR: Comando desconocido` → Comando inválido

## 🌐 Control simultáneo

Puedes usar **WiFi y Bluetooth al mismo tiempo**:
- **Bluetooth** → Control en tiempo real (lag ~5-20ms)
- **WiFi** → Interfaz web en http://192.168.4.1

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
STOP      → Se detiene completamente
DI        → Enciende direccional izquierda
DI        → Apaga direccional izquierda
```

## ⚡ Ventajas del control Bluetooth

- ✅ **Lag mínimo**: ~5-20ms (vs ~50-200ms de WiFi)
- ✅ **Más estable**: No depende de HTTP/TCP
- ✅ **Funciona a distancia**: 10-30 metros
- ✅ **Consume menos batería** que WiFi
