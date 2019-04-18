#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "MinhasCom.h"
#include "MinhaAdc.h"
#include "MinhasMacros.h"
#define BOT_1       PB0
#define BOT_2       PB1
#define ECHO        PB2    
#define PIR         PB3
#define RED_LED     PB4
#define GREEN_LED   PB5
#define YELLOW_LED  PB6
#define TRIGGER     PB7
#define RELAY_1     PD2
#define RELAY_2     PD3

void init_io(){
    //ENTRADAS
    setBit(PORTB, BOT_1);
    setBit(PORTB, BOT_2);
    setBit(PORTB, ECHO);
    setBit(PORTB, PIR);
    //SAIDAS
    setBit(DDRB, RED_LED);
    setBit(DDRB, GREEN_LED);
    setBit(DDRB, BLUE_LED);
    setBit(DDRB, TRIGGER);
    setBit(DDRD, RELAY_1);
    setBit(DDRD, RELAY_2);
}

void setup(){
    init_io();                                      //FUNÇÂO PARA ENTRADAS E SAIDAS
    init_Adc();
}

void loop(){
    if(isBitSet(PINB, PIR)){                         //TEM COPO!!!
        setBit(PORTB, RED_LED);
        if(valor<=x){                               //DISTANCIA DO LIQUIDO AO SENSOR (AJUDA MURILO)   
            setBit(PORTB, GREEN_LED);
            clearBit(PORTB, YELLOW_LED);
            clearBit(PORTB, RELAY_1);
            clearBit(PORTB, RELAY_2);
        }
        else{
            clearBit(PORTB, GREEN_LED);
            if(isBitSet(PINB, BOT_1)){                            //BOTÃO 1 ACIONADO?
                setBit(PORTB, YELLOW_LED);
                setBit(PORTD, RELAY_1);
            }
            else    clearBit(PORTD, RELAY_1);
            
            if(isBitSet(PINB, BOT_2)){
                setBit(PORTB, YELLOW_LED);
                setBit(PORTD, RELAY_2);
            }                        
            else    clearBit(PORTD, RELAY_2);
                 
        }
    
    }
    else{                                       //NÃO TEM COPO!!!
        clearBit(PORTB, RED_LED); 
        clearBit(PORTB, GREEN_LED);
        clearBit(PORTB, YELLOW_LED);
        clearBit(PORTB, RELAY_1);
        clearBit(PORTB, RELAY_2);
    }
}
