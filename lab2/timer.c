#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <minix/syslib.h>
#include <stdint.h>
#include <minix/drivers.h>
#include "i8254.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static int hook_id; // hookid utilizado para a funçao irq_setpolicy()
unsigned int globalcounter = 0; // contador globar utilizado para contar as interrupçoes do timer 0

uint8_t(timerselector) (uint8_t timer){ 
//func que seleciona o timer. Ambiguidade valor numerico do timer-Ref do timer
    if(timer==0)
      timer = TIMER_0;  //selecionar timer 0
    else if(timer==1)
      timer = TIMER_1; //selecionar timer 1
    else if(timer==2)
      timer = TIMER_2; //selecionar timer 2
  return timer;
}

int (timer_set_frequency)(uint8_t (timer), uint32_t (freq)) { 
//func que altera a frequencia. Problema, o timer so altera 16

  if((timer<0 || timer >2)||(freq<=0)){//erro caso o timer seja errado ou freq seja igual a zero
    return 1;
  }

  uint8_t st,stout=INITIALIZE0,timerref= INITIALIZE0;
  uint8_t msb, lsb = INITIALIZE0;
  uint16_t outbbyte=INITIALIZE0;

  outbbyte = (uint32_t)(TIMER_FREQ/freq);// freq que vamos efetivamente mandar para o contador

  if(timer_get_conf(timer, &st)!=0){//tiro a config atual, para a preservar
    return 1;
  }
  timerref = timerselector(timer);

  stout=st;
  stout=stout&FOURLSB_STATUSBYTE; //preserva a integridade do st, o byte retorno,o e preserva os 4 bits menos significativos.

  stout=stout|TIMER_LSB_MSB;//o modo preferido, no guiao para dar set ao timer e LSB Followed by MSB

//preparar a control word para incidir sobre o timer pretendido
//caso timerref == TIMER_0 não precisamos de fazer nada pois os  bits correspondente ja estão a 00
  if(timerref == TIMER_1) 
    stout = stout|TIMER_SEL1;// bits 6 e 5 passam a 01 invés de 00

  else if(timerref == TIMER_2)
    stout = stout|TIMER_SEL2; //bits 6 e 5 passam a 10 inves de 00

//mandar a control word
  if(sys_outb(TIMER_CTRL, stout)!=0){ //caso aconteca algum erro ao mandar a control word
    return 1;
  }
  if(util_get_LSB(outbbyte, &lsb)!=0){//tirar os LSBs para dar upload para o register de 8 bits followed by MSB
    return 1;
  }

  if(sys_outb(timerref,lsb)!=0){ //mandar os Lsb da freq para o timer
    return 1;
  }

  if(util_get_MSB(outbbyte, &msb)!=0){//tira o MSB para mandar os restantes 8 bits para o timer com a frequecia certa
    return 1;
  }

  if(sys_outb(timerref,msb)!=0){ //mandar os Msb da freq para o timer
    return 1;
  }

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {

  if(bit_no == NULL) {//erro caso a apontador bit no não seja valido
    return 1;
  }
  hook_id = 0;
  *bit_no = hook_id; // bit no recebe o hook id que nos configuramos para mandarmos para o kernel
  if(sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id)!=OK){//da set a policy
      return 1;
  }

  return 0;
  // sys_irqsetpolicy ja da enable nos interrupts dai nao se utilizar a funcao enable para dar enable no interrupts
}

int (timer_unsubscribe_int)() {
    
  if(sys_irqdisable(&hook_id)!=OK){//disable primeiro, para depois tirar a policy set
    return 1;
  }
  if(sys_irqrmpolicy(&hook_id)!=OK){//disbable nos interrupts
    return 1;
  }
  return 0;
}

void (timer_int_handler)() {
  globalcounter ++; //incrementa o counter
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  if(timer<0 || timer>2 || st == NULL){ 
    return 1;
  }
    
  uint8_t readback=INITIALIZE0, timeradress= INITIALIZE0; // byte
  uint32_t aux;

  timeradress = timerselector(timer); //selecionar timer
  readback=readback|TIMER_RB_CMD;//programa a control word
  readback = readback|BIT(5);//no guiao e explicito que o count, ativo em baixo, nunca e para ler, por isso, pomo-lo a alto

//Seleciona o Timer na Control Word
  if(timeradress == TIMER_0){
    readback = readback|BIT(1);
  }
  else if(timeradress == TIMER_1){
    readback = readback|BIT(2);
  }
  else if(timeradress == TIMER_2){
    readback = readback|BIT(3);
  }
//manda a control word
  if(sys_outb(TIMER_CTRL	, readback)!=0){
    return 1;
  }
//recebemos a config do timer
  if(sys_inb(timeradress, &aux)!=0){
    return 1;
  }
  *st=(uint8_t)aux; //CAST PARA 8 BITS

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,enum timer_status_field field){ 
 

  if((timer<0 || timer>2)){ //verificar parametros de entrada
    return 1;
  }

  union timer_status_field_val conf;
  uint8_t staux, timeradress = INITIALIZE0;
  timeradress = timerselector(timer);
  
  staux=st; //para preservar a configuracao

  //De acordo com a implementacao, temos de passar para um enum o modo como vamos ler
  if(field == all){
    conf.byte = st;
  }

  else if(field == initial){
    staux = staux >> 4;//tirar os bits 5 e 4, isto e so preciso para o caso de termos de tirar o initialization mode

    //nos andamos com staux para a direita, para por os lsbs prontos a dar-nos info acerca do que queremos

    if((staux&TIMER_TYPEOFACESS) == MODE_LSB) 
      conf.in_mode = LSB_only;

    else if((staux&TIMER_TYPEOFACESS) == MODE_MSB)
      conf.in_mode = MSB_only;

    else if((staux&TIMER_TYPEOFACESS) == MODE_LSB_MSB)
      conf.in_mode = MSB_after_LSB;

    else
      conf.in_mode = INVAL_val;

    staux = st;//
  }


  else if(field == mode){

    staux = staux >> 1 ; //anda 1 para a direita para termos os lsbs como sendo o mode
    staux=staux & TIRAROMODE; //tira tudo o que e , isto é tudo o que nao e relacionado com o mode em que o timer se encontra
    
    if(staux==COUNTINGMODE6){ // caso seja um dos casos raros
      staux=COUNTINGMODE2;
    }
    else if(staux==COUNTINGMODE7){ // caso seja um dos casos raros
      staux=COUNTINGMODE3;
    }
    conf.count_mode = staux;

    staux=st;
  
  }

  else if(field == base){

    if((staux&TIMER_BCD)==TIMER_BCD){
      conf.bcd = true;  
    }

    else if((staux&TIMER_BCD)==TIMER_BIN){
      conf.bcd = false;
    }
  }  
  else{
    //caso haja algum prob com a estrutura retorna erro,
    return 1;
  }

  if(timer_print_config(timer, field, conf)==1){
    return 1;
  }
  return 0;
}
