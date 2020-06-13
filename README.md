# Projeto cancela automática
Demonstraçlão de protótipo que visa imitar o comporttamento de uma cancela automatizada.

## History
1. When a gate is low (horizontally) a red LED is lit;

2. When a car is approached or the red LED is blinking and an audible signal is displayed while the engine moves a cancellation without opening direction (put it vertically);

3. When a cancellation is completely open (vertically), the red LED must be turned off, the audible signal stops rising and a green LED must be activated;

4. After the car passes the gate, the green LED must be turned off, an audible signal must be emitted and the red LED must remain flashing while the engine moves a cancellation without the direction of closing (horizontally);

5. After closing a cancellation completely closed (horizontally), the audible signal must stop rising and the red LED must remain lit.

## Diagrans
### Circuit

## Resolution

### Setup devices and  ports
Define constants for pins like this:
```c
// constantes
// -------- servo ------------------
Servo sv;
const int servoPin = 3; // gate
// -------- leds -------------------
const int redledPin = 9;   
const int greenLedPin = 10;
// -------- pieso ------------------
const int piesoPin = 8;    // song emiter
// -------- sensor proximidade -----
const int sensorPinEntrada = 2;    // sensor for open gate when proximity veichele has detected
const int sensorPinsSaida = 4; // sensor for close gate when veichele has safety distance

```