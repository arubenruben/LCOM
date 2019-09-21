#pragma once
/*Funcao especifica de lab3, especificaçao especifica de sys_inb, que caso se trate de lab3, processa para alem desse comando, um contador para poder comparar o numero de chamadas ao sistema efetuada pelos diferentes meios de comunicacao com os I/O devices

  port_t port- recebe uma variavel do tipo port, com o endereco para que vamos fazer sys_inb
  byte-        Byte de data para injetar no endereco port

  retorna 0 em sucesso, !0 em caso de erro
*/
int (sys_inb_cnt)(port_t port, uint32_t *byte);


/*Funcao central da administracao da comunicacao de/para o kernel. Aceita todas os possiveis inputs para o sistema, recebendo um byte de data "comand" e um byte por referencia para retornar para a funcao primitiva o valor de uma eventual leitura do sistema.
  *leitura-Byte por referencia para retornar uma eventual leitura do sistema

  retorna 0 em sucesso, !0 em caso de erro
*/
int (keyboard_messaging)(uint8_t *leitura, uint8_t comand);

/* Funcao especializada em executar comandos para o sistema.
  registo-Local de escrita
  command-Tipo de Operacao a realizar
  e_argumento-Byte de controlo para distinguir escrita de argumentos de comandos para o IN_BUF_0x64

retorna 0 em caso de sucesso !0 em caso de erro
*/
uint8_t(keyboard_command_issue)(uint8_t registo,uint8_t command, uint8_t e_argumento);

/* Funcao especializada em receber os camandos do registo de output, OUT_BUF
  leitura-Byte por referencia para retornar o valor lido no OUT_BUF

  retorna 0 em caso de sucesso !0 em caso de erro
*/

int (keyboard_command_receive)(uint8_t *leitura);
/* interrupt handler for the KB */
void(kbc_ih)();
