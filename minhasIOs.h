#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "minhasMacros.h"

                      //Pinos do arduino    Portas do Micro
#define LED_PIR     2 //____pino 2______________PORTA D
#define LED_M       3 //____pino 3______________PORTA D
#define LED1        4 //____pino 4______________PORTA D
#define LED2        5 //____pino 5______________PORTA D
#define BOMB1       6 //____pino 6______________PORTA D
#define BOMB2       7 //____pino 7______________PORTA D
#define BTN1        0 //____pino 8______________PORTA B
#define BTN2        1 //____pino 9______________PORTA B
#define ECHO        2 //____pino 10_____________PORTA B
#define TRIG        3 //____pino 11_____________PORTA B
#define PIR         4 //____pino 12_____________PORTA B
#define BTN_M       5 //____pino 13_____________PORTA B


void init_io(){
    //ENTRADAS
    clearBit(DDRB, BTN_M);
    clearBit(DDRB, BTN1);
    clearBit(DDRB, BTN2);
    clearBit(DDRB, ECHO);
    clearBit(DDRB, PIR);
    //SAIDAS
    setBit(DDRD, LED_PIR);
    setBit(DDRD, LED_M);
    setBit(DDRD, LED1);
    setBit(DDRD, LED2);
    setBit(DDRB, TRIG);
    setBit(DDRD, BOMB1);
    setBit(DDRD, BOMB2);
    //PULL-UP
    setBit(PORTB, BTN_M);
    setBit(PORTB, BTN1);
    setBit(PORTB, BTN2);
}
