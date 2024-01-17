
#include "Timer.h"
#include "Controls.h"

static int msec, sec;

void isrTimer0() {
    msec = (msec + 1) % 1000;
	if (msec == 0) {
		sec = (sec + 1) % 60;
	}
    if (sec == 5) {
        killCat();
    }
}

void setTimer0() {
	//Set the minutes, the seconds and the mseconds
	sec = msec = 0;

	//Configure the timer (i.e. TIMER0) correctly
	TIMER_DATA(0) = TIMER_FREQ_1024(1000);
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	
	//Associate the interrupt handler and enable the interrupt line
	irqSet(IRQ_TIMER0, &isrTimer0);
	irqEnable(IRQ_TIMER0);
}

void resetTimer() {
    irqDisable(IRQ_TIMER0);
    sec = msec = 0;
    irqEnable(IRQ_TIMER0);
}

void stopTimer0() {
    irqDisable(IRQ_TIMER0);
}
