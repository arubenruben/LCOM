PROG=proj

SRCS = proj.c graphics.c kbc.c kbd.c mousedriver.c vetor.c vbe1.c timer.c game.c bitmap.c statemachine.c rtc.c fila.c uart.c

CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
