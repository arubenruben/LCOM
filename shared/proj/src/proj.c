#include <lcom/lcf.h>
#include "i8042.h"
#include "i8254.h"
#include "kbc.h"
#include "kbd.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include "graphicalmacros.h"
#include "vbe1.h"
#include "bitmap.h"
#include "game.h"
#include "mousedriver.h"
#include "graphics.h"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(proj_main_loop)()
{

  lm_init(false);

  if (vg_init(MODE) == NULL)
  {
    printf("ERRO, no vg_init\n");
    return -1;
  }

  boot_resources *start = (boot_resources *)game_load();

  if (start == NULL)
  {
    printf("Erro no startup");
    return -1;
  }

  all_interrupts(start);

  game_end(start);

  vg_exit();

  return 0;
}
