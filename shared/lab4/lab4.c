// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/lab4.h>
#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <minix/drivers.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include <stdbool.h>
#include "mousedriver.h"
#include "i8042.h"
#include "kbc.h"
#include "i8254.h"
#include <math.h>
// Any header files included below this line should have been created by you
extern uint8_t mousebyte;
extern int mouse_hook_id;

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(mouse_test_packet)(uint32_t cnt)
{
  int ipc_status, r, irq_set, contadorbytes = 0;
  message msg;
  uint8_t bit_no;
  struct packet leitura;
  uint8_t arg_report = INITIALIZE0;
  uint8_t lixo;

  if (mouse_subscribe_int(&bit_no) != 0)
    return 1;

  irq_set = BIT(bit_no);

  if ((sys_irqdisable(&mouse_hook_id)) != OK)
  { //disable primeiro, para depois tirar a policy set
    printf("ERRO , sys_irqdisable falhou\n");
    return -1;
  }

  if ((mouse_messaging(&arg_report, ENABLE_DATA_REPORTING)) != 0)
  {
    printf("ERRO , messaging falhou\n");
    return -1;
  }

  if ((sys_irqenable(&mouse_hook_id)) != OK)
  {
    printf("erro , sys_irqenable falhou\n");
    return -1;
  }

  while (cnt > 0)
  { //condiçao para sair do ciclo do interrupts, caso se detete o scancode do esc
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status))
    {
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE:

        if (msg.m_notify.interrupts & irq_set)
        {
          mouse_ih();

          //testar a sincronizacao
          if (contadorbytes == 0)
          {
            if ((mousebyte & BIT(3)) != 0)
            {
              leitura.bytes[0] = mousebyte;
            }
            else
              continue;
          }

          else if (contadorbytes == 1)
          {

            leitura.bytes[1] = mousebyte;
          }

          else if (contadorbytes == 2)
          {
            leitura.bytes[2] = mousebyte;
            if (data_processing(&leitura) != 0)
            {
              printf("ERRO , data_processing falhou\n");
              return -1;
            }

            contadorbytes = -1;
            cnt--;
            mouse_print_packet(&leitura);
          }

          else if (contadorbytes > 2)
          {
            printf("O contador excedeu 2\n");
            return -1;
          }

          contadorbytes++;
          //fecha o while
        }
        break;
      default:
        break;
      }
    }
    else
    {
      //fica vazio
    }
  }
  if ((sys_irqdisable(&mouse_hook_id)) != OK)
  { //disable primeiro, para depois tirar a policy set
    printf("ERRO , sys_irqdisable falhou\n");
    return -1;
  }

  if ((mouse_messaging(&arg_report, DISABLE_DATA_REPORTING)) != 0)
  {
    printf("messaging falhou\n");
    return -1;
  }

  if ((sys_irqenable(&mouse_hook_id)) != OK)
  {
    printf("erro , sys_irqenable falhou\n");
    return -1;
  }

  if ((mouse_unsubscribe_int()) != 0)
  {
    printf("ERRO , mouse_unsubscribe falhou\n");
    return -1;
  }

  keyboard_command_receive(&lixo);

  return 0;
}

int(mouse_test_remote)(uint16_t period, uint8_t cnt)
{

  uint8_t bit_no;
  struct packet leitura;
  uint8_t arg_report = INITIALIZE0, readata[3];

  if (period < 0)
  {

    printf("ERRO\n");
    return -1;
  }

  if (mouse_subscribe_int(&bit_no) != 0)
  {
    printf("ERRO , mouse_subscribe falhou\n");
    return 1;
  }

  if ((sys_irqdisable(&mouse_hook_id)) != OK)
  { //disable primeiro, para depois tirar a policy set
    printf("ERRO , sys_irqdisable falhou\n");
    return -1;
  }

  while (cnt > 0)
  {

    if ((mouse_messaging(&arg_report, READ_DATA)) != 0)
    {
      printf("ERRO , messaging falhou\n");
      return -1;
    }

    if ((keyboard_command_receive(&readata[0])) != 0)
    {
      printf("ERRO , command_receive falhou\n");
      return -1;
    }

    if ((keyboard_command_receive(&readata[1])) != 0)
    {
      printf("ERRO , command_receive falhou\n");
      return -1;
    }

    if ((keyboard_command_receive(&readata[2])) != 0)
    {
      printf("ERRO , command_receive falhou\n");
      return -1;
    }

    //testar a sincronizacao

    if ((readata[0] & BIT(3)) != 0)
    {
      leitura.bytes[0] = readata[0];
    }
    else
      continue;

    leitura.bytes[1] = readata[1];

    leitura.bytes[2] = readata[2];

    if (data_processing(&leitura) != 0)
    {
      printf("ERRO , data_processing falhou\n");
      return -1;
    }
    cnt = cnt - 1;
    mouse_print_packet(&leitura);

    tickdelay(micros_to_ticks(period * 1000));
    //fecha o while
  }

  if ((mouse_messaging(&arg_report, SET_STREAM_MODE)) != 0)
  {
    printf("ERRO , mouse_messaging falhou\n");
    return -1;
  }

  if ((mouse_messaging(&arg_report, DISABLE_DATA_REPORTING)) != 0)
  {
    printf("ERRO , mouse_messaging falhou\n");
    return -1;
  }
  uint8_t leitura1 = minix_get_dflt_kbc_cmd_byte();

  if ((keyboard_command_issue(IN_BUF_0x64, WRITE_COMMAND_BYTE)) != 0)
  {
    printf("ERRO , command_issue falhou\n");
    return -1;
  }
  if ((keyboard_command_issue(IN_BUF_0x60, leitura1)) != 0)
  {
    printf("ERRO , command_issue falhou\n");
    return -1;
  }

  if ((sys_irqenable(&mouse_hook_id)) != OK)
  {
    printf("erro , sys_irqenable falhou\n");
    return -1;
  }

  if ((mouse_unsubscribe_int()) != 0)
  {
    printf("ERRO , mouse_subscribe falhou\n");
    return -1;
  }
  return 0;
}

int(mouse_test_async)(uint8_t idle_time)
{

  int ipc_status, r, irq_timer0 = INITIALIZE0, irq_mouse = INITIALIZE0;
  uint8_t bit_no1, bit_no2;
  message msg;
  uint8_t currenttimer = INITIALIZE0;
  extern int globalcounter;
  int contadorbytes = 0;
  struct packet leitura;
  uint8_t arg_report = INITIALIZE0;

  if (idle_time < 0)
  {
    printf("ERRO- Tempo invalido\n");
    return -1;
  }

  if (timer_subscribe_int(&bit_no1) != 0)
  {
    printf("ERRO , timer_subscribe falhou\n");
    return -1;
  }

  irq_timer0 = BIT(bit_no1);

  if (mouse_subscribe_int(&bit_no2) != 0)
  {
    printf("ERRO , mouse_subscribe falhou\n");
    return -1;
  }

  irq_mouse = BIT(bit_no2);

  if ((sys_irqdisable(&mouse_hook_id)) != OK)
  { //disable primeiro, para depois tirar a policy set
    printf("ERRO , sys_irqdisable falhou\n");
    return -1;
  }

  if ((mouse_messaging(&arg_report, ENABLE_DATA_REPORTING)) != 0)
    return -1;

  if ((sys_irqenable(&mouse_hook_id)) != OK)
  {
    printf("erro , sys_irqenable falhou\n");
    return -1;
  }

  if (idle_time <= 0)
  {
    printf("ERRO NO TEMPO\n");
    return -1;
  }
  while (currenttimer < idle_time)
  { /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status))
    { /* received notification */
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: /* hardware interrupt notification */
        if (msg.m_notify.interrupts & irq_timer0)
        { /* subscribed interrupt */
          timer_int_handler();
          if ((globalcounter % sys_hz()) == 0)
          {
            currenttimer++;
          }
        }
        if (msg.m_notify.interrupts & irq_mouse)
        { /* subscribed interrupt*/ /* process KBD interrupt request */

          mouse_ih();

          //testar a sincronizacao
          if (contadorbytes == 0)
          {
            if ((mousebyte & BIT(3)) != 0)
            {
              leitura.bytes[0] = mousebyte;
            }
            else
              contadorbytes = -1;
          }

          else if (contadorbytes == 1)
          {

            leitura.bytes[1] = mousebyte;
          }

          else if (contadorbytes == 2)
          {
            leitura.bytes[2] = mousebyte;

            if (data_processing(&leitura) != 0)
            {
              printf("ERRO , data_processing falhou\n");
              return -1;
            }

            contadorbytes = -1;
            mouse_print_packet(&leitura);
            currenttimer = 0;
            globalcounter = 0;
          }

          else if (contadorbytes > 2)
          {
            printf("O contador excedeu 2\n");
            return -1;
          }

          contadorbytes++;
          //fecha o while
        }

        break;
      default:
        break;
      }
    }
    else
    {
      //fica vazio
    }
  }

  if ((sys_irqdisable(&mouse_hook_id)) != OK)
  { //disable primeiro, para depois tirar a policy set
    printf("ERRO , sys_irqdisable falhou\n");
    return -1;
  }

  if ((mouse_messaging(&arg_report, DISABLE_DATA_REPORTING)) != 0)
  {
    printf("ERRO , messaging falhou\n");
    return -1;
  }

  if ((sys_irqenable(&mouse_hook_id)) != OK)
  {
    printf("erro , sys_irqenable falhou\n");
    return -1;
  }

  if ((sys_irqdisable(&mouse_hook_id)) != OK)
  { //disable primeiro, para depois tirar a policy set
    printf("ERRO , sys_irqdisable falhou\n");
    return -1;
  }

  if ((mouse_messaging(&arg_report, SET_DEFAULT)) != 0)
  {
    printf("ERRO , messaging falhou\n");
    return -1;
  }
  if ((sys_irqenable(&mouse_hook_id)) != OK)
  {
    printf("erro , sys_irqenable falhou\n");
    return -1;
  }
  if ((mouse_unsubscribe_int()) != 0)
  { //unsubscribe dos interrupts do keyboard
    printf("ERRO , mouse_unsubscribe falhou\n");
    return -1;
  }
  if ((timer_unsubscribe_int()) != 0)
  { //unsibscribe dos interrupts do timer
    printf("ERRO , timer_unsubscribe falhou\n");
    return -1;
  }
  return 0;
}

typedef enum
{
  INIT,
  DRAW_LINE_UP_RIGHT,
  VERTICE,
  DRAW_LINE_DOWN_RIGHT,
  CHECK_X_LEN,
  FIM
} state_t;

static state_t st = INIT; // initial state; keep state
static int somatoriox = 0;
static int somatorioy = 0;

/*enum mouse_ev_t { LB_PRESSED,
                  LB_RELEASED,
                  RB_PRESSED,
                  RB_RELEASED,
                  BUTTON_EV,
                  MOUSE_MOV };

struct mouse_ev {
  enum mouse_ev_t type;
  int16_t delta_x, delta_y;
};*/
enum mouse_ev_t_estados
{
  INIT1,
  LB_PRESSED1,
  LB_RELEASED1,
  RB_PRESSED1,
  RB_RELEASED1,
  MOUSE_MOVL1,
  MOUSE_MOV1,
  MOUSE_MOVR1
};

static enum mouse_ev_t_estados evento = INIT1;

struct mouse_ev mouse_detect_event_not_provided(struct packet *pp)
{

  struct mouse_ev return_value;
  uint8_t byte0, byte1, byte2;
  uint16_t mousebyte16bits;
  int sinalx, sinaly;

  byte0 = pp->bytes[0];
  byte1 = pp->bytes[1];
  byte2 = pp->bytes[2];

  switch (evento)
  {
  case INIT1:
    if (((byte0 & L_B) != 0) && ((byte0 & R_B) == 0))
    {
      evento = LB_PRESSED1;
    }
    else if (((byte0 & R_B) != 0) && ((byte0 & L_B) == 0))
    {
      evento = RB_PRESSED1;
    }

    break;

  case LB_PRESSED1:

    if (((byte0 & L_B) == 0))
      evento = LB_RELEASED1;
    else if ((byte0 & R_B) != 0)
    {
      evento = INIT1;
    }
    else if (byte1 != 0 || byte2 != 0)
    {
      evento = MOUSE_MOVL1;
    }

    break;

  case RB_PRESSED1:
    if (((byte0 & R_B) == 0))
      evento = RB_RELEASED1;
    else if ((byte0 & L_B) != 0)
    {
      evento = INIT1;
    }
    else if (byte1 != 0 || byte2 != 0)
    {
      evento = MOUSE_MOVR1;
    }

    break;

  case LB_RELEASED1:
    if (((byte0 & L_B) != 0))
      evento = LB_PRESSED1;
    else if (((byte0 & R_B) != 0))
      evento = RB_PRESSED1;

    break;

  case RB_RELEASED1:
    if (((byte0 & R_B) != 0))
      evento = RB_PRESSED1;
    else if (((byte0 & L_B) != 0))
      evento = LB_PRESSED1;

    break;

  case MOUSE_MOVL1:
    if (((byte0 & L_B) == 0))
      evento = LB_RELEASED1;
    else if (((byte0 & R_B) != 0))
      evento = INIT1;

    break;
  case MOUSE_MOVR1:
    if (((byte0 & R_B) == 0))
      evento = RB_RELEASED1;
    else if (((byte0 & L_B) != 0))
      evento = INIT1;

    break;
  case MOUSE_MOV1:

    break;
  }
  if (evento == MOUSE_MOVL1 || evento == MOUSE_MOVR1)
  {
    return_value.type = MOUSE_MOV;
  }
  else if (evento == LB_PRESSED1)
    return_value.type = LB_PRESSED;
  else if (evento == RB_PRESSED1)
    return_value.type = RB_PRESSED;
  else if (evento == LB_RELEASED1)
    return_value.type = LB_RELEASED;
  else if (evento == RB_RELEASED1)
    return_value.type = RB_RELEASED;
  else if (evento == INIT1)
    return_value.type = -1;

  if ((byte0 & X_SIGN) != 0)
  {
    sinalx = 1;
  }
  else
    sinalx = 0;

  if ((byte0 & Y_SIGN) != 0)
  {
    sinaly = 1;
  }
  else
    sinaly = 0;

  if (sinalx == 1)
  {
    mousebyte16bits = 0;
    mousebyte16bits = (mousebyte16bits | byte1);
    mousebyte16bits = mousebyte16bits | Complemento_2;
    return_value.delta_x = mousebyte16bits;
  }
  else
  {
    mousebyte16bits = 0;
    mousebyte16bits = (mousebyte16bits | byte1);

    return_value.delta_x = mousebyte16bits;
  }

  if (sinaly == 1)
  {
    mousebyte16bits = 0;
    mousebyte16bits = (mousebyte16bits | byte2);
    mousebyte16bits = mousebyte16bits | Complemento_2;
    return_value.delta_y = mousebyte16bits;
  }
  else
  {
    mousebyte16bits = 0;
    mousebyte16bits = (mousebyte16bits | byte2);
    return_value.delta_y = mousebyte16bits;
  }
  return return_value;
}

void check_inverted_v(struct mouse_ev *evt, uint8_t x_len, uint8_t tolerance)
{

  switch (st)
  {
  case INIT:

    if (evt->type == LB_RELEASED)
      st = INIT;
    else if (evt->type == LB_PRESSED)
    {
      st = DRAW_LINE_UP_RIGHT;
    }
    else
    {
      st = INIT;
    }
    break;

  case DRAW_LINE_UP_RIGHT:

    if (evt->type == LB_RELEASED)
    {
      st = VERTICE;
      break;
    }

    if (evt->type == MOUSE_MOV)
    {
      st = DRAW_LINE_UP_RIGHT;

      somatoriox = somatoriox + evt->delta_x;
      somatorioy = somatorioy + evt->delta_y;
    }

    if (evt->type == RB_PRESSED || (evt->delta_x < -tolerance) || (evt->delta_y < -tolerance))
    {
      st = INIT;
      somatoriox = 0;
      somatorioy = 0;
    }

    break;

  case VERTICE:

    if (evt->type == LB_PRESSED)
    {
      st = DRAW_LINE_UP_RIGHT;
      somatoriox = 0;
      somatorioy = 0;
      break;
    }

    if (somatoriox < x_len)
    {
      st = INIT;

      somatoriox = 0;
      somatorioy = 0;
      break;
    }

    if (somatorioy <= somatoriox)
    {
      st = INIT;
      somatoriox = 0;
      somatorioy = 0;
    }
    if ((abs(evt->delta_x) > tolerance) || (abs(evt->delta_y) > tolerance))
    {
      st = INIT;
      somatoriox = 0;
      somatorioy = 0;
    }
    if (evt->type == RB_PRESSED)
    {
      st = DRAW_LINE_DOWN_RIGHT;
      somatoriox = 0;
      somatorioy = 0;
      break;
    }

    break;

  case DRAW_LINE_DOWN_RIGHT:

    if (evt->type == RB_RELEASED)
    {
      st = CHECK_X_LEN;
      break;
    }

    if (evt->type == MOUSE_MOV)
    {
      st = DRAW_LINE_DOWN_RIGHT;

      somatoriox = somatoriox + evt->delta_x;
      somatorioy = somatorioy + evt->delta_y;
    }
    if (evt->type == LB_PRESSED || (evt->delta_x < -tolerance) || (evt->delta_y > tolerance))
    {
      st = INIT;
      somatoriox = 0;
      somatorioy = 0;
    }
    break;

  case CHECK_X_LEN:

    if (somatoriox < x_len || abs(somatorioy) <= somatoriox)
    {
      st = INIT;
      somatoriox = 0;
      somatorioy = 0;
      break;
    }
    st = FIM;
    break;

  case FIM:
    st = FIM;
    break;
  }

  return;
}

int(mouse_test_gesture)(uint8_t x_len, uint8_t tolerance)
{
  int ipc_status, r, irq_set, contadorbytes = 0;
  message msg;
  uint8_t bit_no;
  struct packet leitura;
  struct mouse_ev processamento;

  uint8_t arg_report = INITIALIZE0;
  uint8_t lixo;

  if (x_len <= 0)
  {
    printf("ERRO- X len invalido\n");
    return -1;
  }

  if (mouse_subscribe_int(&bit_no) != 0)
    return 1;

  irq_set = BIT(bit_no);

  if ((sys_irqdisable(&mouse_hook_id)) != OK)
  { //disable primeiro, para depois tirar a policy set
    printf("ERRO , sys_irqdisable falhou\n");
    return -1;
  }

  if ((mouse_messaging(&arg_report, ENABLE_DATA_REPORTING)) != 0)
    return -1;

  if ((sys_irqenable(&mouse_hook_id)) != OK)
  {
    printf("erro , sys_irqenable falhou\n");
    return -1;
  }

  while (st != FIM)
  { //condiçao para sair do ciclo do interrupts, caso se detete o scancode do esc
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status))
    {
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE:

        if (msg.m_notify.interrupts & irq_set)
        {
          mouse_ih();

          //testar a sincronizacao
          if (contadorbytes == 0)
          {
            if ((mousebyte & BIT(3)) != 0)
            {
              leitura.bytes[0] = mousebyte;
            }
            else
              continue;
          }

          else if (contadorbytes == 1)
          {

            leitura.bytes[1] = mousebyte;
          }

          else if (contadorbytes == 2)
          {
            leitura.bytes[2] = mousebyte;
            if (data_processing(&leitura) != 0)
            {
              return -1;
            }

            contadorbytes = -1;
            mouse_print_packet(&leitura);

            processamento = mouse_detect_event_not_provided(&leitura);
            check_inverted_v(&processamento, x_len, tolerance);
            //check_inverted_v(mouse_detect_event(&leitura), x_len, tolerance);
            if (st == CHECK_X_LEN)
            {
              processamento = mouse_detect_event_not_provided(&leitura);

              check_inverted_v(&processamento, x_len, tolerance);
            }
          }

          else if (contadorbytes > 2)
          {
            printf("O contador excedeu 2\n");
            return -1;
          }

          contadorbytes++;
          //fecha o while
        }
        break;
      default:
        break;
      }
    }
    else
    {
      //fica vazio
    }
  }

  processamento = mouse_detect_event_not_provided(&leitura);
  check_inverted_v(&processamento, x_len, tolerance);

  if ((sys_irqdisable(&mouse_hook_id)) != OK)
  { //disable primeiro, para depois tirar a policy set
    printf("ERRO , sys_irqdisable falhou\n");
    return -1;
  }

  if ((mouse_messaging(&arg_report, DISABLE_DATA_REPORTING)) != 0)
  {
    printf("messaging falhou\n");
    return -1;
  }

  if ((sys_irqenable(&mouse_hook_id)) != OK)
  {
    printf("erro , sys_irqenable falhou\n");
    return -1;
  }

  if ((mouse_unsubscribe_int()) != 0)
  {
    return -1;
  }

  keyboard_command_receive(&lixo);

  return 0;
}
