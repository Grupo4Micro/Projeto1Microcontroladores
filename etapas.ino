//Programa: Conectando Sensor Ultrassonico HC-SR04 ao Arduino

//Define os pinos para o trigger e echo

//Inicializa o sensor nos pinos definidos acima
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "minhasMacros.h"
#include "minhaCom.h"
#include "minhaAdc.h"

const uint8_t trig_pin = 10;
const uint8_t echo_pin = 9;

uint32_t print_timer;

//  #define ECHO        PINB2   //PINO 10
//  #define TRIGGER     PD5     //PINO 5

/*float medir(){
    init_io();
    int temp = 0;
    setBit(PORTD, PD5);
    //delay de pelo menos 10 micro
    _delay_us(11);
    clearBit(PORTD, PD5);
    while((temp<23600) && (isBitSet(PIND,PIND5))){
        _delay_us(1);
        temp++;
    }
    return temp*0.017;
}*/

void setup()
{
    initUSART();
    initAdc();
    clearBit(DDRB, DDB1); //ECHO
    setBit(DDRB, DDB2); //TRIGGER
    clearBit(PORTB, PB2);
    char msg0[20];
    sprintf(msg0,"Distancia =\n");
    printString(msg0);
}

void loop()
{
  // Espera 0,5s (500ms) entre medições.
if (millis() - print_timer > 500) {
print_timer = millis();
 
// Pulso de 5V por pelo menos 10us para iniciar medição.
setBit(PORTB, PB2);
_delay_us(11);
clearBit(PORTB, PB2);
 
/* Mede quanto tempo o pino de echo ficou no estado alto, ou seja,
o tempo de propagação da onda. */
uint32_t pulse_time = pulseIn(echo_pin, HIGH);
 
/* A distância entre o sensor ultrassom e o objeto será proporcional a velocidade
do som no meio e a metade do tempo de propagação. Para o ar na
temperatura ambiente Vsom = 0,0343 cm/us. */
float distance = 0.01715 * pulse_time;
char msg[20] ;

sprintf(msg,"%i.%i cm\n", floor (distance), int((distance-floor(distance))*100));
    printString(msg);
 
/* Imprimimos o valor na porta serial;
Serial.print(distance);
Serial.println(" cm");*/
}





  
    /*//Recebe um caracter da serial
    medir();
    uint8_t x = receiveByte();
    float valor = medir();
    char msg1[20];
    sprintf(msg1,"%i cm\n", floor(valor));
    printString(msg1);
    int i;
    sprintf(i,"%i cm\n",i);
    printString(i);
    _delay_ms(1000);
    i++;*/
}
