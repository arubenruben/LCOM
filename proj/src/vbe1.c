#include <lcom/lcf.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include "i8042.h"
#include "i8254.h"
#include "kbc.h"
#include "kbd.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include "graphicalmacros.h"
#include "vbe1.h"
#include <stdlib.h>

static char *video_mem;
char *double_buffer;
static uint16_t h_res;
static uint16_t v_res;
static uint8_t bits_per_pixel;

void *(vg_init)(uint16_t mode)
{
  int r1;
  struct minix_mem_range mr;
  static unsigned int vram_base; /* VRAM's physical addresss */
  struct reg86u r;               //registro com os commandos para a BIOS
  static unsigned int vram_size; /* VRAM's size, but you can use*/
  vbe_mode_info_t vmi_p;         /* Number of VRAM bits per pixel */

  if (vbe_get_mode_info_ours(mode, &vmi_p) != 0)
  {
    printf("ERRO: vbe_get_info falhou\n");
    return NULL;
  };

  h_res = vmi_p.XResolution;
  v_res = vmi_p.YResolution;
  bits_per_pixel = vmi_p.BitsPerPixel;

  vram_base = vmi_p.PhysBasePtr;
  vram_size = vmi_p.XResolution * vmi_p.YResolution * ((vmi_p.BitsPerPixel + 7) / 8);
  /* Allow memory mapping */

  mr.mr_base = vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if (OK != (r1 = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r1);

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED)
    panic("couldn't map video memory");

  memset(&r, 0, sizeof(r)); //dar set 0 aos registos com os comandos

  r.u.w.ax = VBE_SET_MODE;             // VBE call, function 02 -- set VBE mode
  r.u.w.bx = (SET_LINEAR_MODE | mode); // set bit 14: linear framebuffer
  r.u.b.intno = BIOS_CALL;

  if (sys_int86(&r) != OK)
  {
    printf("set_vbe_mode: sys_int86() failed \n");
    return NULL;
  }

  double_buffer = (char *)malloc(vram_size);

  return video_mem;
}

int(vbe_get_mode_info_ours)(uint16_t mode, vbe_mode_info_t *vmi_p)
{
  mmap_t map;
  struct reg86u reg;
  phys_bytes buf;

  if (lm_alloc(sizeof(vbe_mode_info_t), &map) == NULL) //alloc memory needed
  {
    printf("ERRO: lm_alloc falhou\n"); //reboot minix if there is problem or do retrys but may not solve
    return -1;
  }

  memset(&reg, 0, sizeof(reg));
  buf = map.phys;

  reg.u.w.ax = VBE_GET_MODE_INFO; // VBE get mode info (0x4F01)//funcçao
  reg.u.w.es = PB2BASE(buf);      // PB2BASE Is a macro for computing the base of a segment, a 16-bit value, given a 32-bit linear address;
  reg.u.w.di = PB2OFF(buf);       // PB2OFF Is a macro for computing the offset with respect to the base of a segment, a 16-bit value, given a 32-bit linear address;
  reg.u.w.cx = mode;
  reg.u.b.intno = BIOS_CALL; // (0x10)//mete serviços bios

  if (sys_int86(&reg) != OK)
  { // call BIOS
    printf("ERRO: sys_int86() falhou\n");
    lm_free(&map); //free memory
    return -1;
  }

  if (reg.u.b.ah == FUNCTION_CALL_FAILED || reg.u.b.ah == FUNCTION_INVALID_IN_MODE || reg.u.b.ah == FUNCTION_NOT_SUPPORTED)
  {
    lm_free(&map);
    return -1;
  }

  memcpy(vmi_p, map.virt, map.size);
  lm_free(&map); //free memory
  return 0;
}

uint16_t get_h_res()
{
  return h_res;
}
uint16_t get_v_res()
{
  return v_res;
}
uint32_t get_bits_per_pixel()
{
  return bits_per_pixel;
}
int get_vram_size()
{
  int conta = (h_res * v_res * (bits_per_pixel / 8));
  return conta;
}
char *get_double_buffer()
{
  return double_buffer;
}
char *get_video_mem()
{
  return video_mem;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
  for (uint16_t i = y; i < height + y; i++)
  {
    if (vg_draw_hline(x, i, width, color) == -1)
    {
      return -1;
    }
  }
  return 0;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color)
{
  for (uint16_t i = x; i < x + len; i++)
  {
    if (vg_set_pixel(i, y, color) == -1)
    {
      return -1;
    }
  }
  return 0;
}

int(vg_set_pixel)(uint16_t x, uint16_t y, uint32_t color)
{

  if ((x < 0 || x >= h_res) || (y < 0 || y >= v_res)) // input check
    return -1;
  char *posicao_mem;

  if (bits_per_pixel == BITS_PER_PIXEL_0X110)
  {
    color = color & MODE_0X110_15BIT_PROBLEM;
  }

  posicao_mem = video_mem + ((x + y * h_res) * ((bits_per_pixel + 7) / 8));

  for (unsigned i = 0; i < (bits_per_pixel + 7) / 8; i++)
  {
    *posicao_mem = color;
    posicao_mem++;
    color = color >> 8;
  }

  return 0;
}
