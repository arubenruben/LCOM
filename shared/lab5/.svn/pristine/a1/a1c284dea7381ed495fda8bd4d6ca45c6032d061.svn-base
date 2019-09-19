#include <lcom/lab5.h>
#include <lcom/lcf.h>
//#include <lcom/video_gr.h>
#include "graphicalmacros.h"
#include "i8042.h"
#include "i8254.h"
#include <kbc.h>
#include <kbd.h>
#include <liblm.h>
#include <machine/int86.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include "sprite.h"

Sprite *create_sprite(const char *pic[], int x, int y,
                      int xspeed, int yspeed) {
  //allocate space for the "object"
  Sprite *sp = (Sprite *) malloc(sizeof(Sprite));
  if (sp == NULL)
    return NULL;
  // read the sprite pixmap
  sp->map = read_xpm(pic, &(sp->width), &(sp->height));
  if (sp->map == NULL) {
    free(sp);
    return NULL;
  }
  sp->xspeed= xspeed;
  sp->yspeed= yspeed;
  sp->x = x;
  sp->y = y;

  return sp;
}

/*static int draw_sprite(Sprite *sp, char *base){

  uint16_t x, y;
  x = sp->x;
  y = sp->y;

  draw_xpm(x,y,sp->*map);

  return 0;
}
*/


void destroy_sprite(Sprite *sp) {
  if (sp == NULL)
    return;
  if (sp->map)
    free(sp->map);
  free(sp);
  sp = NULL; // XXX: pointer is passed by value
  // should do this @ the caller
}
