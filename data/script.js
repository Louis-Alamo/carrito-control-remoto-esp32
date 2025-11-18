// URL base del ESP32
const BASE_URL = 'http://192.168.4.1';

const buttons = {
    left: document.getElementById('btnLeft'),
    right: document.getElementById('btnRight'),
    accelerate: document.getElementById('btnAccelerate'),
    brake: document.getElementById('btnBrake')
};

const status1 = document.getElementById('status1');
const status2 = document.getElementById('status2');

// Estado actual de las acciones
const activeActions = new Set();

// Mapeo de teclas a botones
const keyMap = {
    'a': 'left',
    'd': 'right',
    'ArrowLeft': 'left',
    'ArrowRight': 'right',
    'w': 'accelerate',
    's': 'brake',
    'ArrowUp': 'accelerate',
    'ArrowDown': 'brake'
};

const actionMessages = {
    'left': 'Girando Izquierda',
    'right': 'Girando Derecha',
    'accelerate': 'Acelerando',
    'brake': 'Frenando'
};

// Función para calcular y enviar control diferencial
function sendDifferentialControl() {
    let velocidad = 0;
    let giro = 0;

    // Calcular velocidad adelante/atrás
    if (activeActions.has('accelerate')) {
        velocidad = 255;
    } else if (activeActions.has('brake')) {
        velocidad = -255;
    }

    // Calcular ajuste de giro
    if (activeActions.has('left')) {
        giro = -255;
    } else if (activeActions.has('right')) {
        giro = 255;
    }

    // Enviar comando combinado
    const endpoint = `/control?v=${velocidad}&g=${giro}`;
    fetch(BASE_URL + endpoint)
        .then(response => {
            if (!response.ok) {
                console.error('Error en la petición:', response.status);
            }
        })
        .catch(error => {
            console.error('Error de conexión:', error);
        });
}

// Función para enviar comando de detener
function sendStopCommand() {
    fetch(BASE_URL + '/detener')
        .catch(error => {
            console.error('Error al detener:', error);
        });
}

// Función para actualizar el panel de estado
function updateStatusPanel() {
    const actions = Array.from(activeActions);
    
    if (actions.length === 0) {
        status1.textContent = 'Modo Carrera';
        status1.classList.remove('active');
        status2.textContent = '---';
        status2.classList.remove('active');
    } else if (actions.length === 1) {
        status1.textContent = actionMessages[actions[0]];
        status1.classList.add('active');
        status2.textContent = '---';
        status2.classList.remove('active');
    } else {
        // Máximo 2 acciones
        status1.textContent = actionMessages[actions[0]];
        status1.classList.add('active');
        status2.textContent = actionMessages[actions[1]];
        status2.classList.add('active');
    }
}

// Función para activar un botón
function activateButton(buttonKey) {
    const button = buttons[buttonKey];
    if (button && activeActions.size < 2) {
        button.classList.add('active');
        activeActions.add(buttonKey);
        updateStatusPanel();
        
        // Enviar control diferencial actualizado
        sendDifferentialControl();
    }
}

// Función para desactivar un botón
function deactivateButton(buttonKey) {
    const button = buttons[buttonKey];
    if (button) {
        button.classList.remove('active');
        activeActions.delete(buttonKey);
        updateStatusPanel();
        
        // Si no hay acciones activas, detener
        if (activeActions.size === 0) {
            sendStopCommand();
        } else {
            // Si aún hay acciones, actualizar control diferencial
            sendDifferentialControl();
        }
    }
}

// Eventos de teclado
document.addEventListener('keydown', (e) => {
    const key = e.key.toLowerCase();
    const buttonKey = keyMap[key] || keyMap[e.key];
    
    if (buttonKey && !activeActions.has(buttonKey)) {
        e.preventDefault();
        activateButton(buttonKey);
    }

    // Teclas numéricas para funciones del vehículo (no implementadas en API)
    switch(e.key) {
        case '1':
            e.preventDefault();
            btnHazard.click();
            break;
        case '2':
            e.preventDefault();
            btnTurnLeft.click();
            break;
        case '3':
            e.preventDefault();
            btnTurnRight.click();
            break;
        case '4':
            e.preventDefault();
            btnLights.click();
            break;
        case '5':
            e.preventDefault();
            btnSiren.click();
            break;
        case '6':
            e.preventDefault();
            btnHorn.click();
            break;
    }
});

document.addEventListener('keyup', (e) => {
    const key = e.key.toLowerCase();
    const buttonKey = keyMap[key] || keyMap[e.key];
    
    if (buttonKey) {
        e.preventDefault();
        deactivateButton(buttonKey);
    }
});

// Eventos táctiles/clic para cada botón
Object.keys(buttons).forEach(key => {
    const button = buttons[key];
    
    // Mouse/touch start
    button.addEventListener('mousedown', () => activateButton(key));
    button.addEventListener('touchstart', (e) => {
        e.preventDefault();
        activateButton(key);
    });
    
    // Mouse/touch end
    button.addEventListener('mouseup', () => deactivateButton(key));
    button.addEventListener('mouseleave', () => deactivateButton(key));
    button.addEventListener('touchend', (e) => {
        e.preventDefault();
        deactivateButton(key);
    });
});

// Prevenir comportamiento por defecto de las flechas
window.addEventListener('keydown', (e) => {
    if(['ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight'].includes(e.key)) {
        e.preventDefault();
    }
});

// ========== FUNCIONES DEL VEHÍCULO (NO CONECTADAS A API) ==========

const btnHazard = document.getElementById('btnHazard');
const btnTurnLeft = document.getElementById('btnTurnLeft');
const btnTurnRight = document.getElementById('btnTurnRight');
const btnLights = document.getElementById('btnLights');
const btnSiren = document.getElementById('btnSiren');
const btnHorn = document.getElementById('btnHorn');
const lightIcon = document.getElementById('lightIcon');

let hazardActive = false;
let turnLeftActive = false;
let turnRightActive = false;
let lightsMode = 0;
let sirenActive = false;
let hornActive = false;

// Preventivas
btnHazard.addEventListener('click', () => {
    hazardActive = !hazardActive;
    
    if (hazardActive) {
        btnHazard.classList.add('blink-active');
        turnLeftActive = false;
        turnRightActive = false;
        btnTurnLeft.classList.remove('blink-active');
        btnTurnRight.classList.remove('blink-active');
    } else {
        btnHazard.classList.remove('blink-active');
    }
});

// Direccional izquierda
btnTurnLeft.addEventListener('click', () => {
    turnLeftActive = !turnLeftActive;
    
    if (turnLeftActive) {
        btnTurnLeft.classList.add('blink-active');
        hazardActive = false;
        turnRightActive = false;
        btnHazard.classList.remove('blink-active');
        btnTurnRight.classList.remove('blink-active');
    } else {
        btnTurnLeft.classList.remove('blink-active');
    }
});

// Direccional derecha
btnTurnRight.addEventListener('click', () => {
    turnRightActive = !turnRightActive;
    
    if (turnRightActive) {
        btnTurnRight.classList.add('blink-active');
        hazardActive = false;
        turnLeftActive = false;
        btnHazard.classList.remove('blink-active');
        btnTurnLeft.classList.remove('blink-active');
    } else {
        btnTurnRight.classList.remove('blink-active');
    }
});

// Luces (3 modos)
btnLights.addEventListener('click', () => {
    lightsMode = (lightsMode + 1) % 3;
    
    btnLights.classList.remove('lights-off', 'lights-low', 'lights-high');
    
    if (lightsMode === 0) {
        btnLights.classList.add('lights-off');
        lightIcon.textContent = '💡';
    } else if (lightsMode === 1) {
        btnLights.classList.add('lights-low');
        lightIcon.textContent = '🔅';
    } else {
        btnLights.classList.add('lights-high');
        lightIcon.textContent = '🔆';
    }
});

// Sirena
btnSiren.addEventListener('click', () => {
    sirenActive = !sirenActive;
    
    if (sirenActive) {
        btnSiren.classList.add('siren-active');
    } else {
        btnSiren.classList.remove('siren-active');
    }
});

// Claxon
btnHorn.addEventListener('click', () => {
    hornActive = !hornActive;
    
    if (hornActive) {
        btnHorn.classList.add('horn-active');
    } else {
        btnHorn.classList.remove('horn-active');
    }
});
