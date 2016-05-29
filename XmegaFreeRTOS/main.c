/*
 * XmegaFreeRTOS.c
 *
 * Created: 29-May-16 5:04:18 PM
 * Author : emon1
 */ 

#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"

volatile int t1var = 0;
volatile int t2var = 0;
volatile int t3var = 0;


void thread_1( void *pvParameters ){
	//serial_startup();
	int i = 0;
	while(1){
		//printf("hello world %d\n\r",i);
		//i++;
		asm("nop");
		t1var++;
		PORTR.OUTTGL = (1<<0);
		vTaskDelay(1000); //wait 1 sec
	}
}
void thread_2( void *pvParameters ){
	//DDRB |= (1<<DDB0); //set PORTB, PIN0 as output
	while(1){
		//PORTB ^= (1<<PORTB0); //toggle PORTB, PIN0
		asm("nop");
		t2var++;
		PORTR.OUTTGL = (1<<1);
		vTaskDelay(2000); //wait 2 seconds
	}
}
void thread_3( void *pvParameters ){
	//DDRB |= (1<<DDB1); //set PORTB, PIN1 as output
	while(1){
		//PORTB ^= (1<<PORTB1); //togle PORTB, PIN0
		asm("nop");
		t3var++;
		PORTD.OUTTGL = (1<<4);
		vTaskDelay(200); //wait 200 ms
	}
}




int main(void)
{
	
	PORTR.DIRSET = (1<<0);
	PORTR.DIRSET = (1<<1);
	PORTD.DIRSET = (1<<4);
	
	
	//creating the threads
	xTaskCreate(thread_1, (const char*) "t1", 300, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate(thread_2,(const char *) "t2", 100, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate(thread_3,(const char *) "t3", 100, NULL, tskIDLE_PRIORITY, NULL );
	
	
	//starting the scheduler
	vTaskStartScheduler();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

