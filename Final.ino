#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "minhasMacros.h"
#include "minhaCom.h"
#include "minhaAdc.h"
#include "minhasIOs.h"


uint16_t temp;
unsigned char podeGravar = 0;
uint16_t nvlMax = 0;
int i;

//Sensor Ultrassônico medindo altura do líquido
void medir() {
  temp = 0;
  setBit(PORTB, TRIG);
  _delay_us(10);
  clearBit(PORTB, TRIG);
  while (!testBit(PINB, ECHO)) { //Loop até o sinal Echo
  }
  while (testBit(PINB, ECHO)) { //Início da contagem
    temp++;
    _delay_us(1);
  }
  /*Serial.print(nvlMax);
  Serial.println(" nvlMax");
  Serial.print(temp);
  Serial.println(" temp");*/
  //_delay_ms(100);
}

void setup() {
  //Serial.begin(9600); // Habilita Comunicação Serial a uma taxa de 9600 bauds.
  init_io();
  temp = 0;
  podeGravar = 0;
  nvlMax = 0;
  clearBit(PORTD, LED_PIR);
  clearBit(PORTD, LED_M);
  clearBit(PORTD, LED1);
  clearBit(PORTD, LED2);
  clearBit(PORTD, BOMB1);
  clearBit(PORTD, BOMB2);
}

void loop() {
  if (!testBit(PINB, BTN_M)) {
    setBit(PORTD, LED_M);
  }
  if (!testBit(PINB, PIR)) { //Tem Copo
    setBit(PORTD, LED_PIR);

    //Modo manual acionado
    while (!testBit(PINB, BTN_M) && !testBit(PINB, PIR)) {
      podeGravar = 1;
      if (!testBit(PINB, BTN1)) {
        setBit(PORTD, BOMB1);
        setBit(PORTD, LED1);
      } else {
        clearBit(PORTD, BOMB1);
        clearBit(PORTD, LED1);
      }
      if (!testBit(PINB, BTN2)) {
        setBit(PORTD, BOMB2);
        setBit(PORTD, LED2);
      } else {
        clearBit(PORTD, BOMB2);
        clearBit(PORTD, LED2);
      }
    }

    //Modo automático
    clearBit(PORTD, LED_M);
    medir();

    //Modo manual foi usado e desligado
    if (podeGravar && (temp < 700 && temp > 0)) {
      medir();
      nvlMax = temp;
      podeGravar = 0;
    }
    if (podeGravar == 0 && nvlMax > 0) {
      medir();
      if (!testBit(PINB, BTN1)) {
        while (nvlMax < temp && temp < 2000) {
          setBit(PORTD, BOMB1);
          setBit(PORTD, LED1);
          medir();
        }
        clearBit(PORTD, BOMB1);
        clearBit(PORTD, LED1);
      }

      if (!testBit(PINB, BTN2)) {
        while (nvlMax < temp && temp < 2000) {
          //ligabomba          setBit(PORTD, BOMB2);
          setBit(PORTD, LED2);
          medir();
        }
        clearBit(PORTD, BOMB2);
        clearBit(PORTD, LED2);
      }
    }

    //Modo manual ainda não foi usado
    else if (podeGravar == 0 && nvlMax == 0) {
      setBit(PORTD, LED_PIR);
      _delay_ms(100);
      clearBit(PORTD, LED_PIR);
      _delay_ms(100);
    }
  }

  else {
    clearBit(PORTD, BOMB1);
    clearBit(PORTD, BOMB2);

    //Limpando as variaveis caso ja tenha usado Modo manual
    if (nvlMax != 0) {
      //Botões precionados por 3 segundos
      while ((!testBit(PINB, BTN2) && !testBit(PINB, BTN1)) ) {
        for (i = 0, i < 60, i++) {
          _delay_ms(50);
        }
      }
      //Se tiverem sido precionados por mais de 2 segundos
      if (i >= 60) {
        i=0;
        temp = 0;
        podeGravar = 0;
        nvlMax = 0;
        setBit(PORTD, LED_PIR);
        setBit(PORTD, LED_M);
        setBit(PORTD, LED1);
        setBit(PORTD, LED2);
        _delay_ms(250);
        clearBit(PORTD, LED_PIR);
        clearBit(PORTD, LED_M);
        clearBit(PORTD, LED1);
        clearBit(PORTD, LED2);
      }
    }
  }
}
