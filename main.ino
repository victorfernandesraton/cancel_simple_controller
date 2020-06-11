#include <Arduino.h>
#include <Servo.h>

// constantes
// -------- servo ------------------
Servo sv;
const int servoPin = 3;
// -------- leds -------------------
const int greenLedPin = 8; // led verde
const int redledPin = 4;   // led vermelha
// -------- sensor proximidade -----
const int sensorPinEntrada = 10;
const int sensorPinsSaida = 12;
// -------- pieso ------------------
const int piesoPin = 11;

// piscar led
void changeLed(int ledPin)
{
    digitalWrite(ledPin, !digitalRead(ledPin));
}
// controle cancela
int controlCancel(int start, int end, int blinker)
{
    int out;
    if (start > end)
    {
        Serial.print("Fechando");
        for (int i = start; i >= end - 1; i--)
        {
            if (blinker > 0 && i % 20 == 0)
            {
                changeLed(blinker);
            }
            sv.write(i);
            Serial.print(".");
            delay(25);
            out = i;
        }
    }
    else
    {
        Serial.print("Abrindo");
        for (int i = start; i <= end; i++)
        {
            if (blinker > 0 && i % 20 == 0)
            {
                changeLed(blinker);
            }
            sv.write(i);
            Serial.print(".");
            delay(25);
            out = i;
        }
    }
    Serial.println("");
    return out;
}

// fechar cancela
int closeCancel() { return controlCancel(90, 0, redledPin); }

// abrir cancela
int openCancel() { return controlCancel(0, 90, redledPin); }

// posição de proximidade
float getSensorProximity(int sensorPinEntrada)
{
    pinMode(sensorPinEntrada, OUTPUT);
    digitalWrite(sensorPinEntrada, LOW);
    delayMicroseconds(2);
    digitalWrite(sensorPinEntrada, HIGH);

    delayMicroseconds(5);
    digitalWrite(sensorPinEntrada, LOW);
    pinMode(sensorPinEntrada, INPUT);
    return 0.01523 * pulseIn(sensorPinEntrada, HIGH);
}

// emite som com o pieso
void emitBeep(int piesoPin)
{
    tone(piesoPin, 440);
    delay(100);
    tone(piesoPin, 220);
    delay(100);
    tone(piesoPin, 880);
}

void setup()
{
    Serial.begin(9600);

    sv.attach(3);                 // porta do sianl servo motor
    sv.write(0);                  // posição inicial servo motor
    pinMode(greenLedPin, OUTPUT); // setup led verde
    pinMode(redledPin, OUTPUT);   // setup led vermelho
    pinMode(piesoPin, OUTPUT);    // porta do pieso
}

void loop()
{

    long sensorEntradaDistance = getSensorProximity(sensorPinEntrada);  // valor Distância sensor de entrada
    long sensorSaidaDistance = getSensorProximity(sensorPinsSaida); // valor Distância sebsir de saida
    long cancelPosition = sv.read(); // valor posião do moto

    Serial.print("posição do portão (graus) :\t");
    Serial.println(cancelPosition);
    Serial.print("Distância sensor de entrada (cm):\t");
    Serial.println(sensorEntradaDistance);
    Serial.print("Diatãncia sensor de saida (cm):\t");
    Serial.println(sensorSaidaDistance);

    // Carro próximoo da cancela na entrada
    if (sensorEntradaDistance < 100 && cancelPosition == 0)
    {
        // desliga led
        digitalWrite(greenLedPin, LOW);
        // emite som
        emitBeep(piesoPin);
        // abertura de cancela
        openCancel();
    }
    // canxela erguida mas o carro está longe dae perpassar as cancelas
    else if (sensorSaidaDistance >= 50 && cancelPosition >= 90)
    {
        noTone(piesoPin);
        digitalWrite(redledPin, LOW);
        digitalWrite(greenLedPin, HIGH);
    }
    // cancela aberta
    else if (sensorEntradaDistance >= 100 && sensorSaidaDistance < 50 && cancelPosition >= 90)
    {
        // desliga led
        digitalWrite(greenLedPin, LOW);
        // emite som
        emitBeep(piesoPin);
        // fecha cancela
        closeCancel();
    }
    // cancela fechada sem veiculo proximo
    else if (cancelPosition == 0)
    {
        noTone(piesoPin);
        digitalWrite(redledPin, HIGH);
        digitalWrite(greenLedPin, LOW);
    }
    delay(200);
}
