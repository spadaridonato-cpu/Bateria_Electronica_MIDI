# Bateria_Electronica_MIDI

## Descripción
Una batería electrónica, construido con Arduino, funciona como un controlador MIDI, permitiendo una interpretación de batería real con sonidos digitales dentro de una DAW.

Este proyecto transforma los golpes de batería en señales MIDI mediante sensores piezoeléctricos y un sistema de detección del estado del hi-hat.

## Tecnologías y componentes utilizados
- Arduino UNO
- Sensores piezoeléctricos (para golpes de batería)
- Sensor de efecto Hall A3144 (detección de apertura/cierre del hi-hat)
- Resistencias
- Software DAW (FL Studio o similar)
- Software de USB MIDI
- C++ (Arduino)

## Cómo funciona
Cada pad de batería contiene un sensor piezoeléctrico que genera un pico de voltaje al ser golpeado.
Arduino lee estas señales, filtra el ruido y las convierte en mensajes de notas MIDI.

El sistema en los pedales, utiliza un sensor de efecto Hall para detectar la posición del hithat:
- Pedal cerrado → una nota MIDI
- Pedal abierto → otra nota MIDI

Arduino envía datos MIDI a la computadora, donde una estación de trabajo de audio digital (DAW) reproduce sonidos de batería en tiempo real.

## 👨‍💻 Autor
Proyecto personal de Arduino + Tecnología musical
