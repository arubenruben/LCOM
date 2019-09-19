#include <lcom/lcf.h>
#include <lcom/lab2.h>
#include <lcom/timer.h>
#include "i8254.h"
#include <stdbool.h>
#include <stdint.h>
#include <minix/syslib.h>

extern unsigned int globalcounter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  
  uint8_t st=INITIALIZE0;//func teste do valor ligo, crio apontador para receber byte, leio e dou display.
  if(timer_get_conf(timer, &st)!=0){
    return 1;
  }
  if(timer_display_conf(timer, st, field)!=0){
    return 1;
  }
  return 0;
}

int(timer_test_time_base)(uint8_t (timer), uint32_t (freq)) {
  if(timer_set_frequency(timer, freq)!=0){//func que testa a alteracao da frequencia do timer
    return 1;
  }
  return 0;
}

int(timer_test_int)(uint8_t time) {
  
  int ipc_status, r, irq_set;
  message msg;
  uint8_t bit_no,currenttimer=1;

  if(timer_subscribe_int(&bit_no)!=0)
    return 1;
  irq_set =  BIT(bit_no);

  
  while(currenttimer <= time) { /* You may want to use a different condition */
     /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */                                
                
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */

                    timer_int_handler();
                    if((globalcounter % sys_hz())==0){
                      currenttimer++;
                      timer_print_elapsed_time();
                    }
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */        
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }
  return 0;
}


int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  
  if(lsb == NULL)
    return 1;
  *lsb=0x00;
  //func que tira os bits menos significativos de um 16 bits para 1 so byte.
  *lsb = (uint8_t)(*lsb)|val ;//fazer ou, e tirar o lsb
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {

  if(msb == NULL)
    return 1;
  *msb=0x00;
  val = val >> 8;//anda para a direita, MSB passa a LSB
  *msb = (uint8_t) (*msb)|val;//faz ou, e tirar com um ou.
  return 0;
}
