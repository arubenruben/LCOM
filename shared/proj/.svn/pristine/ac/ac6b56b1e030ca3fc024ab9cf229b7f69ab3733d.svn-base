#include <lcom/lcf.h>
#include <minix/drivers.h>
#include <rtc_macros.h>

static int hook_id = 8; // hookid utilizado para a funçao irq_setpolicy()

char *(rtc_read_time)(uint8_t *seconds, uint8_t *minutes, uint8_t *hour, uint8_t *day_month, uint8_t *month, uint8_t *year)
{

    int i;
    u32_t leitura;
    char *return_str = (char *)malloc(sizeof(char) * 10);
    uint8_t day_week = 0;

    for (i = 0; i < 3; i++)
    {
        sys_outb(RTC_ADDR_REG, REGISTER_A);
        sys_inb(RTC_DATA_REG, &leitura);
        
        if ((leitura & UIP_MASK) == 0)
        {
            sys_outb(RTC_ADDR_REG, SECONDS_REG);
            sys_inb(RTC_DATA_REG, &leitura);
            *seconds = leitura;
            sys_outb(RTC_ADDR_REG, MIN_REG);
            sys_inb(RTC_DATA_REG, &leitura);
            *minutes = leitura;
            sys_outb(RTC_ADDR_REG, HOUR_REG);
            sys_inb(RTC_DATA_REG, &leitura);
            *hour = leitura;
            sys_outb(RTC_ADDR_REG, DAY_WEEK);
            sys_inb(RTC_DATA_REG, &leitura);
            day_week = leitura;
            sys_outb(RTC_ADDR_REG, DAY_MONTH);
            sys_inb(RTC_DATA_REG, &leitura);
            *day_month = leitura;
            sys_outb(RTC_ADDR_REG, MONTH);
            sys_inb(RTC_DATA_REG, &leitura);
            *month = leitura;
            sys_outb(RTC_ADDR_REG, YEAR);
            sys_inb(RTC_DATA_REG, &leitura);
            *year = leitura;
            break;
        }
        else
        {
        }
    }

    if (day_week == 1)
    {
        strcpy(return_str, "Sunday");
    }
    else if (day_week == 2)
    {
        strcpy(return_str, "Monday");
    }
    else if (day_week == 3)
    {
        strcpy(return_str, "Tuesday");
    }
    else if (day_week == 4)
    {
        strcpy(return_str, "Wednesday");
    }
    else if (day_week == 5)
    {
        strcpy(return_str, "Thursday");
    }
    else if (day_week == 6)
    {
        strcpy(return_str, "Friday");
    }
    else if (day_week == 7)
    {
        strcpy(return_str, "Saturday");
    }
    return return_str;
}

int(rtc_subscribe_int)(uint8_t *bit_no)
{

    if (bit_no == NULL)
    { //erro caso a apontador bit no não seja valido
        return -1;
    }

    *bit_no = hook_id; // bit no recebe o hook id que nos configuramos para mandarmos para o kernel

    if (sys_irqsetpolicy(IRQ_RTC_LINE, IRQ_REENABLE, &hook_id) != OK)
    { //da set a policy
        return -1;
    }
    return 0;
    //check
}

int(rtc_unsubscribe_int)()
{

    if (sys_irqdisable(&hook_id) != OK)
    { //disable primeiro, para depois tirar a policy set
        return -1;
    }
    if (sys_irqrmpolicy(&hook_id) != OK)
    { //disbable nos interrupts
        return -1;
    }
    return 0;
    //check
}
