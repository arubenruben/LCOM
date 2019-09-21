#include <lcom/lcf.h>
#include <minix/drivers.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include <stdbool.h>
#include <stdint.h>
#include <i8254.h>
#include "i8042.h"
#include "kbc.h"
#include "kbd.h"
//sdasdasds
int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}
extern uint8_t scancode;
extern int sys_inb_counter; //contador de vezes que chamamos a função sys_inb

int(kbd_test_scan)(bool(assembly)) { // a cada interrupt lê se um scancode , breakcode ou make code

  int ipc_status, r, irq_set;
  uint8_t bit_no, size = 0, bytes[2];
  bool make;
  message msg;
  int multiplebytes = 0;
  extern int return_kbc_ih;

  if (kb_subscribe_int(&bit_no) != 0) // subscrever os interruptds do keyboard
    return 1;

  irq_set = BIT(bit_no); // metê se o irq set a 1  que é o que corresponde ao keyboard

  while (scancode != ESC_BREAK) { //condiçao para sair do ciclo do interrupts, caso se detete o scancode do esc
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) {
            if (assembly == TRUE) {

              kbc_asm_ih();

              return_kbc_ih = 1;
            }
            else if (assembly == FALSE) { //caso seja para funcionar com o ih em c e não em assembly
              return_kbc_ih = 0;
              kbc_ih(); //chamada do keyboard handler em c;
              //ok, aqui temos um scancode, agora temos de o testar.
            }
            if (return_kbc_ih == -1) //verificaçao do valor de retorno global do kbc:ih , ja kbc_ih é void;
              continue;

            if (multiplebytes == 1) { //caso seja um scancode ou breakcode de dois bytes
              multiplebytes = 0;
              bytes[1] = scancode;
              size = 2;
            }

            else if (scancode == 0xE0) { //caso seja o scancode 0xE0 , quer dizer que temos que esperar por outro scancode para depois imprimimos
              multiplebytes = 1;
              bytes[0] = scancode;
            }
            else {
              bytes[0] = scancode;
              size = 1;
            }
            //testar se é breakcode ou makecode
            if ((scancode & MSB) == INITIALIZE0) {
              make = TRUE;
            }
            else {
              make = FALSE;
            }
            if (multiplebytes != 1 && return_kbc_ih == 1) {
              kbd_print_scancode(make, size, bytes); //dar print o scancode
            }
          }
          break;
        default:
          break;
      }
    }
    else {
      //fica vazio
    }
  }
  if ((keyboard_unsubscribe_int()) != 0) { //unsubscribe os interrupts do keyboard
    return -1;
  }
  if (assembly == false) { //so deve imprimir se nao for em assembly

    kbd_print_no_sysinb(sys_inb_counter); // dar print no numero de vezes que se chamou a funçao sys inb
  }

  return 0;
}
int(kbd_test_poll)() {
  //no polling o ciclo é exatamente igual ao do scan só que não há ciclo para os interrupts
  uint8_t size = 0, bytes[2], leitura;
  bool make;
  int multiplebytes = 0;
  extern int return_kbc_ih;

  while (scancode != ESC_BREAK) {
    return_kbc_ih = 0;
    kbc_ih();

    if (return_kbc_ih == -1)
      continue;

    if (multiplebytes == 1) {
      multiplebytes = 0;
      bytes[1] = scancode;
      size = 2;
    }

    else if (scancode == 0xE0) {

      multiplebytes = 1;
      bytes[0] = scancode;
    }
    else {
      bytes[0] = scancode;
      size = 1;
    }
    //testar se é breakcode:
    if ((scancode & MSB) == INITIALIZE0) {
      make = TRUE;
    }
    else {
      make = FALSE;
    }

    if (multiplebytes != 1 && return_kbc_ih == 1) {
      kbd_print_scancode(make, size, bytes);
    }
  }
  if (keyboard_messaging(&leitura, READ_COMMAND_BYTE) != 0)
    return -1;
  if (keyboard_messaging(&leitura, WRITE_COMMAND_BYTE) != 0)
    return -1;                          //reativar os interrupts do keyboard já que quando se inicia a função polling, o lcf desativa os interrupts, pelo que temos que escrever um command byte para podermos reativa los;
  kbd_print_no_sysinb(sys_inb_counter); // dar print no numero de vezes que se chamou a funçao sys inb
  return 0;
}

int(kbd_test_timed_scan)(uint8_t(n)) {

  int ipc_status, r, irq_timer0 = INITIALIZE0, irq_kbd = INITIALIZE0;
  uint8_t bit_no1, bit_no2, size = 0, bytes[2];
  bool make;
  message msg;
  int multiplebytes = 0;
  uint8_t currenttimer = INITIALIZE0;
  extern int globalcounter;
  extern int return_kbc_ih;

  if (timer_subscribe_int(&bit_no1) != 0)
    return 1;

  irq_timer0 = BIT(bit_no1);

  if (kb_subscribe_int(&bit_no2) != 0)
    return 1;

  irq_kbd = BIT(bit_no2);

  if (n <= 0) {
    printf("ERRO NO TEMPO\n");
    return -1;
  }
  while ((scancode != ESC_BREAK) && (currenttimer < n)) { /* You may want to use a different condition */
                                                      /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                                /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_timer0) { /* subscribed interrupt */
            timer_int_handler();
            if ((globalcounter % sys_hz()) == 0) {
              currenttimer++;
            }
          }
          if (msg.m_notify.interrupts & irq_kbd) { /* subscribed interrupt*/ /* process KBD interrupt request */
            return_kbc_ih = 0;
            currenttimer =INITIALIZE0;
            kbc_ih();
            if (return_kbc_ih == -1){
              return -1;
            }
            //ok, aqui temos um scancode, agora temos de o testar.

            if (multiplebytes == 1) {
              multiplebytes = 0;
              bytes[1] = scancode;
              size = 2;
            }

            else if (scancode == 0xE0) {
              multiplebytes = 1;
              bytes[0] = scancode;
            }
            else {
              bytes[0] = scancode;
              size = 1;
            }
            //testar se é breakcode:
            if ((scancode & MSB) == INITIALIZE0) {
              make = TRUE;
            }
            else {
              make = FALSE;
            }

            if (multiplebytes != 1 && return_kbc_ih == 1) {
              kbd_print_scancode(make, size, bytes);
            }
            currenttimer = INITIALIZE0;
          }
          break;
        default:
          break;
      }
    }
    else {
      //fica vazio
    }
  }

  if ((keyboard_unsubscribe_int()) != 0) { //unsubscribe dos interrupts do keyboard
    return -1;
  }
  if ((timer_unsubscribe_int()) != 0) { //unsibscribe dos interrupts do timer
    return -1;
  }
  kbd_print_no_sysinb(sys_inb_counter); // printf do numero de vezes que chamamos a funçao sys_inb
  return 0;
}
