#include <lcom/lcf.h>
#include "uart_macros.h"
#include "fila.h"
#include "i8042.h"
#include "i8254.h"
#include "uart.h"
#include "kbc.h"
#include "game.h"
#include "kbd.h"
#include "mousedriver.h"

static int uart_hook_id = 4;

void self_clearing_receiver()
{
  uint32_t leitura;
  sys_inb(FIFO_CONTROL_REG, &leitura);
  leitura = leitura | BIT(1);
  sys_outb(FIFO_CONTROL_REG, leitura);
  return;
}

void self_clearing_transmitter()
{
  uint32_t leitura;
  sys_inb(FIFO_CONTROL_REG, &leitura);
  leitura = leitura | BIT(2);
  sys_outb(FIFO_CONTROL_REG, leitura);
  return;
}
fila *get_transmitter(boot_resources *start)
{
  return start->fila_transmitter;
}

fila *get_receiver(boot_resources *start)
{
  return start->fila_receiver;
}

int configurate_uart()
{
  uint32_t leitura;
  uint32_t bit_rate = 1;
  uint32_t bits = 8;

  if (sys_inb(LINE_CONTROL_REG, &leitura))
  {
    return -1;
  }

  leitura = leitura & BIT(LCR_BREAK_CONTROL_BIT);
  leitura = leitura | BIT(LCR_DLAB_BIT);
  leitura = leitura | (bits << LCR_BITS_PER_CHAR_BIT);
  leitura = leitura | BIT(LCR_NUM_STOP_BITS_BIT);
  leitura = leitura | (3 << LCR_PARITY_CONTROL_BIT);

  if (sys_outb(LINE_CONTROL_REG, leitura))
  {
    return -1;
  }

  if (sys_outb(RECEIVER_BUFFER_REG, (bit_rate & 0x00ff))!=0)
  {
    return -1;
  }
  if (sys_outb(INTERRUPT_ENABLE_REGISTER, ((bit_rate >> 16) & 0x00ff))!=0)
  {
    return -1;
  }
  if (sys_outb(LINE_CONTROL_REG, leitura & ~BIT(LCR_DLAB_BIT))!=0)
  {
    return -1;
  }

  return 0;
}

int process_char(unsigned char aux, boot_resources *start)
{
  uint32_t scancode2;
  uint32_t mouse_byte2;
  uint32_t mouse_byte;
  uint32_t mouse_byte1;
  uint32_t LSR_read;
  int i = 0;
  if (aux == 'm')
  {
    while (i < 3)
    {
      if (sys_inb(LINE_STATUS_REG, &LSR_read))
      {
        return -1;
      }
      if (LSR_read & BIT(LSR_RECEIVER_DATA_BIT))
      {
        if (i == 0)
        {
          if (sys_inb(RECEIVER_BUFFER_REG, &mouse_byte))
          {
            return -1;
          }
          i++;
        }
        else if (i == 1)
        {
          if (sys_inb(RECEIVER_BUFFER_REG, &mouse_byte1))
          {
            return -1;
          }
          i++;
        }
        else if (i == 2)
        {
          if (sys_inb(RECEIVER_BUFFER_REG, &mouse_byte2))
          {
            return -1;
          }
          i++;
        }
      }
    }
    i = 0;
    start->mouse_packet2.bytes[0] = (uint8_t)mouse_byte;
    start->mouse_packet2.bytes[1] = (uint8_t)mouse_byte1;
    start->mouse_packet2.bytes[2] = (uint8_t)mouse_byte2;
    data_processing(&(start->mouse_packet2));
    mouse_processing_p2(start);
  }
  else if (aux == 'k')
  {
    if (sys_inb(RECEIVER_BUFFER_REG, &scancode2))
    {
      return -1;
    }
    start->scancode2 = (uint8_t)scancode2;
    kbd_processing_p2(start);
  }
  else if (aux == 'r')
  {
    start->maquina2_pronta_para_multiplayer = 1;
  }
  else if (aux == 'u')
  {
    start->maquina2_pronta_para_multiplayer = 0;
  }
  return 0;
}

int transmit_queue(struct boot_resources *start)
{
  uint32_t aux_sender = INITIALIZE0;
  uint32_t leitura;
  unsigned char *carater = (unsigned char *)malloc(sizeof(unsigned char));
  if (carater == NULL)
  {
    return -1;
  }

  while ((fila_tamanho(start->fila_transmitter) > 0))
  {
    if (sys_inb(LINE_STATUS_REG, &leitura))
    {
      return -1;
    }

    if ((leitura & BIT(5)) != 0)
    {
      carater = fila_front(start->fila_transmitter);

      if (carater == NULL)
      {
        printf("Char Invalido\n");
        return -1;
      }
      aux_sender = *carater;
      if (sys_outb(TRANSMITTER_HOLDING_REG, aux_sender))
      {
        return -1;
      }
      fila_pop(start->fila_transmitter);
    }
  }
  return 0;
}

unsigned char receive_char(boot_resources *start)
{
  uint32_t aux_32;
  uint32_t LSR_read;
  unsigned char aux = 0;
  sys_inb(LINE_STATUS_REG, &LSR_read);

  while (LSR_read & BIT(LSR_RECEIVER_DATA_BIT))
  {
    if (LSR_read & (BIT(LSR_OVERRUN_ERROR_BIT) | BIT(LSR_PARITY_ERROR_BIT) | BIT(LSR_FRAMING_ERROR_BIT)))
    {
      printf("Houve erros de alguma especie na comunicacao\n");
      self_clearing_receiver();
      self_clearing_transmitter();
      return -1;
    }
    sys_inb(RECEIVER_BUFFER_REG, &aux_32);
    aux = (unsigned char)aux_32;
    process_char(aux, start);
    sys_inb(LINE_STATUS_REG, &LSR_read);
  }
  return -1;
}

int uart_subscribe_int(uint8_t *bit_no)
{
  uint32_t leitura;
  if (bit_no == NULL)
  {
    return -1;
  }
  *bit_no = (uint8_t)uart_hook_id; // bit no recebe o hook id que nos configuramos para mandarmos para o kernel
  if (sys_irqsetpolicy(IRQ_UART_LINE, IRQ_REENABLE | IRQ_EXCLUSIVE, &uart_hook_id) != OK)
  { //da set a policy
    printf("ERRO , sys_irqsetpolicy falhou\n");
    return -1;
  }
  sys_outb(FIFO_CONTROL_REG, BIT(FCR_ENABLE_FIFO) |
                                 BIT(FCR_CLEAR_RECEIVE_FIFO) |
                                 BIT(FCR_CLEAR_TRANSMIT_FIFO));

  sys_inb(INTERRUPT_ENABLE_REGISTER, &leitura);

  leitura = leitura & 0xF0; //da disable aos interrupts na tabela

  sys_outb(INTERRUPT_ENABLE_REGISTER, leitura);

  sys_inb(INTERRUPT_ID_REG, &leitura);
  if ((leitura & 0xC0) == 0)
  {
    printf("Erro a inicializar o FIFO\n");
    return -1;
  }
  else
  {
    printf("Tudo ok, FIFO Working\n\n");
  }
  sys_irqdisable(&uart_hook_id);

  if (configurate_uart()!=0)
    {
      return -1;
    }

  self_clearing_receiver();
  self_clearing_transmitter();
  return 0;
}

int uart_unsubscribe_int()
{
  uint32_t leitura;
  sys_inb(INTERRUPT_ENABLE_REGISTER, &leitura);
  leitura = leitura & (BIT(7) | BIT(6) | BIT(5) | BIT(4) | BIT(3));
  sys_outb(INTERRUPT_ENABLE_REGISTER, leitura);

  sys_inb(FIFO_CONTROL_REG, &leitura);
  leitura = leitura & (BIT(7) | BIT(6) | BIT(5) | BIT(4) | BIT(3));
  sys_outb(FIFO_CONTROL_REG, leitura);

  self_clearing_receiver();
  self_clearing_transmitter();

  if (sys_irqrmpolicy(&uart_hook_id) != OK)
  { //disbable nos interrupts
    printf("ERRO , sys_irqrmpolicy falhou\n");
    return -1;
  }
  return 0;
}
