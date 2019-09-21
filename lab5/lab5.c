#include <lcom/lcf.h>
#include <lcom/lab5.h>
//#include <lcom/video_gr.h>
#include <machine/int86.h>
#include <kbc.h>
#include <kbd.h>
#include <liblm.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include "graphicalmacros.h"
#include "i8042.h"
#include "i8254.h"
#include "vbe1.h"
#include "sprite.h"
// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {

  if (delay < 0) {
    printf("ERRO: delay negativo\n");
    return -1;
  }

  lm_init(false);

  if (vg_init(mode) == NULL) {
    printf("ERRO: vg_init falhou\n");
    return -1;
  }

  sleep(delay);

  if (vg_exit() != 0) {
    printf("ERRO, no vg_exit\n");
    return -1;
  }

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

  if (width < 0 || height < 0) {
    printf("ERRO: width ou/e height negativos\n");
    return -1;
  }
  if (x < 0 || y < 0) {
    printf("ERRO: x ou/e y negativos\n");
    return -1;
  }

  int ipc_status, r, irq_set, multiplebytes = 0;
  uint8_t bit_no;
  message msg;
  char *video_mem;

  extern uint8_t scancode;

  lm_init(false);

  video_mem = vg_init(mode);

  if (video_mem == NULL) {
    printf("ERRO: vg_init falhou\n");
    return -1;
  }

  if (kb_subscribe_int(&bit_no) != 0) { // subscrever os interruptds do keyboard
    printf("ERRO: kb_subscribe falhou\n");
    return -1;
  }

  irq_set = BIT(bit_no); // metê se o irq set a 1  que é o que corresponde ao keyboard

  vg_draw_rectangle(x, y, width, height, color);

  while (scancode != ESC_BREAK) { //condiçao para sair do ciclo do interrupts, caso se detete o scancode do esc
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih(); //chamada do keyboard handler em c;
            //ok, aqui temos um scancode, agora temos de o testar.

            if (multiplebytes == 1) {
              multiplebytes = 0;
              scancode = 0x00;
            }

            else if (scancode == 0xE0) {
              multiplebytes = 1;
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
    printf("ERRO: keyboard unsubscribe falhou\n");
    return -1;
  }

  if (vg_exit() != 0) {
    printf("ERRO: no vg_exit\n");
    return -1;
  }

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {

  if (no_rectangles < 0) {
    printf("ERRO: numero de rectangles negativo\n");
    return -1;
  }

  int ipc_status, r, irq_set, multiplebytes = 0;
  uint8_t bit_no;
  message msg;
  uint32_t color = first;
  char *video_mem;
  uint16_t width = 0, height = 0;

  lm_init(false);

  video_mem = vg_init(mode);

  if (video_mem == NULL) {
    printf("ERRO: vg_init falhou\n");
    return -1;
  }

  uint16_t h_res = get_h_res(); /* Horizontal resolution in pixels */
  uint16_t v_res = get_v_res();
  extern uint8_t scancode;

  if (kb_subscribe_int(&bit_no) != 0) { // subscrever os interruptds do keyboard
    printf("ERRO: kb subscribe falhou\n");
    return -1;
  }

  irq_set = BIT(bit_no); // metê se o irq set a 1  que é o que corresponde ao keyboard
  if(no_rectangles != 0){
    width = ((h_res) / no_rectangles);
    height = ((v_res) / no_rectangles);
  }

  for (int row = 0; row < no_rectangles; row++) {
    for (int col = 0; col < no_rectangles; col++) {
      color = returncolor(row, col, first, step, no_rectangles);
      vg_draw_rectangle(col * width, row * height, width, height, color);
    }
  }

  while (scancode != ESC_BREAK) { //condiçao para sair do ciclo do interrupts, caso se detete o scancode do esc
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih(); //chamada do keyboard handler em c;
            //ok, aqui temos um scancode, agora temos de o testar.

            if (multiplebytes == 1) {
              multiplebytes = 0;
              scancode = 0x00;
            }

            else if (scancode == 0xE0) {
              multiplebytes = 1;
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
    printf("ERRO: keyboard unsubscribe falhou\n");
    return -1;
  }

  if (vg_exit() != 0) {
    printf("ERRO: no vg_exit falhou\n");
    return -1;
  }

  return 0;
}

int(video_test_xpm)(const char *xpm[], uint16_t x, uint16_t y) {

  if (xpm == NULL) {
    printf("ERRO: xpm mal\n");
    return -1;
  }
  if (x < 0 || y < 0) {
    printf("ERRO: coordenadas negativas\n");
    return -1;
  }

  int ipc_status, r, irq_set, multiplebytes = 0;
  uint8_t bit_no;
  message msg;
  char *video_mem;
  extern uint8_t scancode;

  lm_init(false);

  video_mem = vg_init(INDEXED_MODE);

  if (video_mem == NULL) {
    printf("ERRO: vg_init falhou\n");
    return -1;
  }

  if (kb_subscribe_int(&bit_no) != 0) { // subscrever os interruptds do keyboard
    printf("ERRO: kb subscribe falhou\n");
    return -1;
  }

  irq_set = BIT(bit_no); // metê se o irq set a 1  que é o que corresponde ao keyboard

  draw_xpm(x, y, xpm);

  while (scancode != ESC_BREAK) { //condiçao para sair do ciclo do interrupts, caso se detete o scancode do esc
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih(); //chamada do keyboard handler em c;
            //ok, aqui temos um scancode, agora temos de o testar.

            if (multiplebytes == 1) {
              multiplebytes = 0;
              scancode = 0x00;
            }

            else if (scancode == 0xE0) {
              multiplebytes = 1;
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
    printf("ERRO: keyboard unsubscribe falhou\n");
    return -1;
  }

  if (vg_exit() != 0) {
    printf("ERRO: no vg_exit falhou\n");
    return -1;
  }

  return 0;
}

int(video_test_move)(const char *xpm[], uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate) {

  if (fr_rate <= 0) {
    printf("ERRO: frame rate negativo ou igual a zero\n");
    return -1;
  }

  int ipc_status, r, kbd_irq_set, timer_irq_set, multiplebytes = 0;
  uint8_t kbd_bit_no, timer_bit_no;
  message msg;
  int conta_frames = 0, conta_frames1 = 0;
  uint16_t x = xi, y = yi;
  char *video_mem;
  extern uint8_t scancode;
  int time_per_frame = 0;

  lm_init(false);

  video_mem = vg_init(INDEXED_MODE);

  if (video_mem == NULL) {
    printf("ERRO: vg_init falhou\n");
    return -1;
  }

  time_per_frame = sys_hz() / fr_rate;
  
  if (kb_subscribe_int(&kbd_bit_no) != 0){
    printf("ERRO: kb subscribe falhou\n");
    return -1;
  }

  if (timer_subscribe_int(&timer_bit_no) != 0){
    printf("ERRO: timer subscribe falhou\n");
    return -1;
  }

  kbd_irq_set = BIT(kbd_bit_no); // metê se o irq set a 1  que é o que corresponde ao keyboard
  timer_irq_set = BIT(timer_bit_no);

  draw_xpm(x, y, xpm);

  while (scancode != ESC_BREAK) { /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0){
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)){
        case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & timer_irq_set){

            conta_frames++;


              if ((x < xf || y < yf) && (conta_frames % time_per_frame == 0)){

                conta_frames1++;

                if (speed < 0){

                  if (conta_frames1 == abs(speed)){
                    conta_frames1 = 0;

                    erase_xpm(x, y, xpm);

                    if (xi == xf){
                      y = y + 1;
                    }
                    else if (yi == yf) {
                      x = x + 1;
                    }
                    draw_xpm(x, y, xpm);
                  }
                }
                else if (speed >= 0) {

                  erase_xpm(x, y, xpm);

                  if(x+speed > xf && yf==yi){
                    speed = xf-x;
                  }
                  if(y+speed >yf && xf==x){
                    speed = yf-y;
                  }

                  if (xi == xf) {
                    y = y + speed;
                  }
                  else if (yi == yf) {
                    x = x + speed;
                  }
                  draw_xpm(x, y, xpm);
                }
              }
            }

          if (msg.m_notify.interrupts & kbd_irq_set) {

            kbc_ih();
            if (multiplebytes == 1) {
              multiplebytes = 0;
              scancode = 0x00;
            }

            else if (scancode == 0xE0) {
              multiplebytes = 1;
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
    printf("ERRO: keyboard unsubscribe falhou\n");
    return -1;
  }

  if ((timer_unsubscribe_int()) != 0) { //unsubscribe os interrupts do keyboard
    printf("ERRO: timer unsubscribe falhou\n");
    return -1;
  }

  if (vg_exit() != 0) {
    printf("ERRO: no vg_exit falhou\n");
    return -1;
  }

  return 0;
}

int(video_test_controller)() {
  
  char * posicao;
  char *auxiliar;
  uint16_t *auxiliar1;
  uint16_t base;
  uint16_t offset;

  posicao = lm_init(false);

  vbe_ctrl_info_t struct1;
  vg_vbe_contr_info_t display;
  memset(&display, 0, sizeof(display));

  strcpy(struct1.VbeSignature,"VBE2");

  vbe_get_ctrl_info(&struct1);

  
  strcpy(display.VBESignature,struct1.VbeSignature);
  display.VBEVersion[0]=struct1.VbeVersion;
  display.VBEVersion[1]=((struct1.VbeVersion)>>8);
  display.TotalMemory = struct1.TotalMemory*64;

  base = ((struct1.OemProductNamePtr) >> 16);
  offset = (struct1.OemProductNamePtr);
  auxiliar =(posicao + base * 16 + offset);

  display.OEMProductNamePtr  = auxiliar;

  base = ((struct1.OemStringPtr) >> 16);
  offset = (struct1.OemStringPtr);
  auxiliar =(posicao + base * 16 + offset);

  display.OEMString  = auxiliar;



  base = struct1.OemVendorNamePtr >> 16;
  offset = struct1.OemVendorNamePtr;

  auxiliar =(posicao + base * 16 + offset);

  display.OEMVendorNamePtr  = auxiliar;

  base = struct1.OemProductRevPtr >> 16;
  offset = struct1.OemProductRevPtr;

  auxiliar =(posicao + base * 16 + offset);

  display.OEMProductRevPtr  = auxiliar;
  
  base = struct1.VideoModePtr >> 16;
  offset = struct1.VideoModePtr;

  auxiliar1 =(uint16_t*)(posicao + base * 16 + offset);

  display.VideoModeList = auxiliar1;

  
  vg_display_vbe_contr_info(&display);

	return 0;
}
