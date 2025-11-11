// Variables para el volante
    let currentAngle = 0;
    let isDragging = false;
    const maxAngle = 180;
    const steeringWheel = document.getElementById('steeringWheel');
    const angleValue = document.getElementById('angleValue');
    
    // Variables para pedales
    let acceleratorValue = 0;
    let brakeValue = 0;
    
    // Control del Volante
    function getAngleFromEvent(e) {
      const rect = steeringWheel.getBoundingClientRect();
      const centerX = rect.left + rect.width / 2;
      const centerY = rect.top + rect.height / 2;
      
      const clientX = e.touches ? e.touches[0].clientX : e.clientX;
      const clientY = e.touches ? e.touches[0].clientY : e.clientY;
      
      const deltaX = clientX - centerX;
      const deltaY = clientY - centerY;
      
      let angle = Math.atan2(deltaY, deltaX) * (180 / Math.PI) + 90;
      
      // Limitar el ángulo
      angle = Math.max(-maxAngle, Math.min(maxAngle, angle));
      
      return angle;
    }
    
    function updateSteering(angle) {
      currentAngle = angle;
      steeringWheel.style.transform = `rotate(${angle}deg)`;
      angleValue.textContent = `${Math.round(angle)}°`;
      
      // Aquí enviarías el comando al ESP32
      sendCommand('steering', angle);
    }
    
    steeringWheel.addEventListener('mousedown', (e) => {
      isDragging = true;
      updateSteering(getAngleFromEvent(e));
    });
    
    steeringWheel.addEventListener('touchstart', (e) => {
      e.preventDefault();
      isDragging = true;
      updateSteering(getAngleFromEvent(e));
    });
    
    document.addEventListener('mousemove', (e) => {
      if (isDragging) {
        updateSteering(getAngleFromEvent(e));
      }
    });
    
    document.addEventListener('touchmove', (e) => {
      if (isDragging) {
        e.preventDefault();
        updateSteering(getAngleFromEvent(e));
      }
    });
    
    document.addEventListener('mouseup', () => {
      isDragging = false;
    });
    
    document.addEventListener('touchend', () => {
      isDragging = false;
    });
    
    // Control de Pedales
    function setupPedal(pedalId, fillId, valueId, type) {
      const pedal = document.getElementById(pedalId);
      const fill = document.getElementById(fillId);
      const valueDisplay = document.getElementById(valueId);
      let isPressed = false;
      
      function updatePedal(e) {
        const rect = pedal.getBoundingClientRect();
        const clientY = e.touches ? e.touches[0].clientY : e.clientY;
        const relativeY = clientY - rect.top;
        const percentage = Math.max(0, Math.min(100, 100 - (relativeY / rect.height) * 100));
        
        fill.style.height = `${percentage}%`;
        valueDisplay.textContent = `${Math.round(percentage)}%`;
        
        if (type === 'accelerator') {
          acceleratorValue = percentage;
        } else {
          brakeValue = percentage;
        }
        
        // Enviar comando al ESP32
        sendCommand(type, percentage);
      }
      
      pedal.addEventListener('mousedown', (e) => {
        isPressed = true;
        updatePedal(e);
      });
      
      pedal.addEventListener('touchstart', (e) => {
        e.preventDefault();
        isPressed = true;
        updatePedal(e);
      });
      
      document.addEventListener('mousemove', (e) => {
        if (isPressed && e.target === pedal) {
          updatePedal(e);
        }
      });
      
      document.addEventListener('touchmove', (e) => {
        if (isPressed) {
          e.preventDefault();
          updatePedal(e);
        }
      });
      
      document.addEventListener('mouseup', () => {
        if (isPressed) {
          isPressed = false;
          fill.style.height = '0%';
          valueDisplay.textContent = '0%';
          if (type === 'accelerator') {
            acceleratorValue = 0;
          } else {
            brakeValue = 0;
          }
          sendCommand(type, 0);
        }
      });
      
      document.addEventListener('touchend', () => {
        if (isPressed) {
          isPressed = false;
          fill.style.height = '0%';
          valueDisplay.textContent = '0%';
          if (type === 'accelerator') {
            acceleratorValue = 0;
          } else {
            brakeValue = 0;
          }
          sendCommand(type, 0);
        }
      });
    }
    
    setupPedal('accelerator', 'acceleratorFill', 'acceleratorValue', 'accelerator');
    setupPedal('brake', 'brakeFill', 'brakeValue', 'brake');
    
    // Función para enviar comandos al ESP32
    function sendCommand(type, value) {
      // Aquí implementarías la comunicación con el ESP32
      // Por ejemplo, usando fetch para enviar solicitudes HTTP:
      /*
      fetch(`/control?${type}=${value}`)
        .then(response => response.json())
        .then(data => console.log('Comando enviado:', data))
        .catch(error => console.error('Error:', error));
      */
      console.log(`${type}: ${value}`);
    }