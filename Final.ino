#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "minhasMacros.h"
#include "minhaCom.h"
#include "minhaAdc.h"
#include "minhasIOs.h"


uint32_t temp = 0;
int objeto;

//Sensor Ultrassônico medindo altura do líquido
void medir(){
    temp = 0;
    setBit(PORTB, TRIG);
    _delay_us(10);
    clearBit(PORTB, TRIG);
    while (!testBit(PINB, ECHO)){ //Loop até o sinal Echo
      temp=0;
    }
    while((temp<23200) && testBit(PINB, ECHO)){ //Início da contagem
        temp++;
    }
}

void aprox(){
  objeto = digitalRead(7);
  if (objeto == 0)
  {
    Serial.println("Objeto : Detectado");
  }
  else
  {
    Serial.println("Objeto : Ausente !");
  }
}

void setup(){
    Serial.begin(9600); // Habilita Comunicação Serial a uma taxa de 9600 bauds.
    init_io();
    objeto=1;
    clearBit(PORTB, TRIG);

}

void loop(){
    medir();
    Serial.print(temp);
    Serial.println(" cm");
    _delay_ms(100);
    aprox();

}
