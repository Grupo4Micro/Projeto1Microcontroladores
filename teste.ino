//Programa: Conectando Sensor Ultrassonico HC-SR04 ao Arduino

//Define os pinos para o trigger e echo

//Inicializa o sensor nos pinos definidos acima
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "minhasMacros.h"
#include "minhaCom.h"
#include "minhaAdc.h"

#define BOT_1       PINB0   //PINO 8
#define BOT_2       PINB1   //PINO 9
#define ECHO        PINB2   //PINO 10
#define PIR         PINC0   //PINO A0
#define RED_LED     PB4     //PINO 12
#define GREEN_LED   PB5     //PINO 13
#define YELLOW_LED  PD4     //PINO 4
#define TRIGGER     PD5     //PINO 5
#define RELAY_1     PD2     //PINO 2
#define RELAY_2     PD3     //PINO 3

void init_io(){
    //ENTRADAS
    clearBit(DDRB, DDB0); //BOT_1
    clearBit(DDRB, DDB1); //BOT_2
    clearBit(DDRB, DDB2); //ECHO
    clearBit(DDRC, DDC0); //PIR
    //SAIDAS
    setBit(DDRB, DDB4); //RED_LED
    setBit(DDRB, DDB5); //GREEN_LED
    setBit(DDRD, DDD4); //YELLOW_LED
    setBit(DDRD, DDD5); //TRIGGER
    setBit(DDRD, DDD2); //RELAY_1
    setBit(DDRD, DDD3); //RELAY_2
}

float medir(){
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
}

void setup()
{
    initUSART();
    initAdc();
    init_io();
    medir();
    char msg0[20];
    sprintf(msg0,"Distancia =\n");
    printString(msg0);
}

void loop()
{
    //Recebe um caracter da serial
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
    i++;
}
