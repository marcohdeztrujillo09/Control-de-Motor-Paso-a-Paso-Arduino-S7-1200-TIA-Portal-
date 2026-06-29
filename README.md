# ⚙️ Control de Motor Paso a Paso — Arduino & S7-1200 (TIA Portal)

> Arduino · TIA Portal · S7-1200 · Motor Paso a Paso · Ladder · C++

Práctica de automatización industrial que implementa el control completo de un motor paso a paso desde dos plataformas distintas: un microcontrolador **Arduino** y un PLC **Siemens S7-1200** programado en TIA Portal. Ambas soluciones ofrecen las mismas funcionalidades de control, cada una con su propio esquema eléctrico.

> ⚠️ **Nota:** Este proyecto fue desarrollado como práctica educativa. El código puede requerir ajustes o actualizaciones para adaptarse a versiones más recientes de TIA Portal o de las librerías de Arduino utilizadas.

---

## 📋 Tabla de contenidos

- [Estructura del repositorio](#-estructura-del-repositorio)
- [Descripción general](#-descripción-general)
- [Funcionalidades implementadas](#-funcionalidades-implementadas)
- [Plataformas y herramientas](#-plataformas-y-herramientas)
- [Esquemas eléctricos](#-esquemas-eléctricos)
- [Descripción del programa](#-descripción-del-programa)
- [Requisitos y compatibilidad](#-requisitos-y-compatibilidad)

---

## 📁 Estructura del repositorio

```text
├── 📁 esquema-s7-1200/               # Solución con PLC Siemens S7-1200
│   ├── 📄 esquema-electrico-s7.png   # Esquema de conexiones del PLC
│   └── 📄 proyecto-tia-portal/       # Proyecto exportado de TIA Portal
├── 📁 esquema-arduino/               # Solución con Arduino
│   ├── 📄 esquema-electrico-arduino.png  # Esquema de conexiones de Arduino
│   └── 📄 motor_paso_a_paso.ino      # Código fuente Arduino 
```

---

## 📝 Descripción general

El objetivo de la práctica es controlar un **motor paso a paso** mediante lógica programada, implementando las funciones típicas de un sistema de automatización industrial: arranque, paro, inversión de giro, control de velocidad y seguridad. El mismo conjunto de funcionalidades se desarrolla en paralelo en dos entornos:

- **Arduino** — programación en C++ con control directo de señales digitales al driver del motor.
- **S7-1200 en TIA Portal** — programación en lenguaje Ladder (KOP) con bloques.

Ambas versiones fueron diseñadas y probadas con sus respectivos esquemas eléctricos.

---

## ✅ Funcionalidades implementadas

| Función | Descripción |
|---|---|
| **Arranque suave** | El motor acelera progresivamente desde parado hasta la velocidad establecida |
| **Paro suave** | El motor decelera de forma gradual hasta detenerse completamente |
| **Cambio de giro** | Inversión de la dirección de giro con parada intermedia y arranque suave automático |
| **Memoria de velocidad** | Al realizar el cambio de giro, el motor recupera la misma velocidad que tenía antes de la inversión |
| **Aumento de velocidad** | Incremento de la velocidad en pasos del 10% sobre la velocidad actual |
| **Disminución de velocidad** | Reducción de la velocidad en pasos del 10% sobre la velocidad actual |
| **Paro de emergencia** | Detención inmediata del motor ante una situación de riesgo |

---

## 🛠️ Plataformas y herramientas

| Plataforma | Tecnología |
|---|---|
| **Microcontrolador** | Arduino (C++) |
| **PLC** | Siemens S7-1200 |
| **Entorno de programación PLC** | TIA Portal V16 |
| **Lenguaje PLC** | Ladder (KOP) con bloques FB y FC |
| **Accionamiento** | Motor paso a paso + driver |

---

## 🔌 Esquemas eléctricos

Cada plataforma dispone de su propio esquema de conexiones detallando el cableado entre el controlador, el driver del motor y los elementos de mando (pulsadores, señales de emergencia).

**Esquema S7-1200:**

![Esquema S7-1200](esquema-s7-1200/esquema-electrico-s7.png)

**Esquema Arduino:**

![Esquema Arduino](esquema-arduino/esquema-electrico-arduino.png)

---

## 💻 Descripción del programa

### Versión Arduino
El código gestiona las señales de paso y dirección del driver del motor paso a paso. La velocidad se controla modificando el delay entre pulsos, y las funciones de arranque/paro suave se implementan variando progresivamente ese intervalo. El paro de emergencia interrumpe inmediatamente el ciclo de pulsos.

### Versión S7-1200 (TIA Portal)
El programa está estructurado con bloques de función:
- **FB (Function Block):** bloques con memoria propia que gestionan el estado del motor (velocidad actual, dirección, estado de marcha).
- **FC (Function):** bloques sin memoria para operaciones de cálculo y lógica de control puntual.
- La lógica de arranque/paro suave se implementa mediante temporizadores y contadores en Ladder.
- El paro de emergencia actúa sobre la salida del driver con prioridad absoluta sobre el resto de la lógica.

---

## 📋 Requisitos y compatibilidad

**Arduino:**
- Arduino IDE (cualquier versión reciente)
- Librería de control de motor paso a paso compatible con el driver utilizado

> ⚠️ Revisar la librería empleada en el código original, ya que puede haber cambiado de nombre o API en versiones más nuevas del IDE.

**TIA Portal:**
- Siemens TIA Portal V16 o superior
- PLC Siemens S7-1200 (o simulador S7-PLCSIM)

> ⚠️ Si se abre el proyecto con una versión más reciente de TIA Portal, es posible que solicite migrar el proyecto. Se recomienda hacer una copia de seguridad antes de abrirlo.

---

> Práctica de automatización industrial · Técnico en Automatización y Robótica Industrial
