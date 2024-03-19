//Where is the led connected?
//Port: A
//Pin: 5
//BUTTON
//PORT: C
//PIN: 13

#define PERIPH_BASE 			(0X40000000UL) // PERIPHERAL ADDRESS BASE VALUE
#define AHB1PERIPH_OFFSET		(0X00020000UL) // GPIO START ADDRESS VALUE
#define AHB1PERIPH_BASE 		PERIPH_BASE + AHB1PERIPH_OFFSET

#define GPIOA_OFFSET 			(0X0000UL) //GPIO_A REGEISTER
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET				(0X3800UL) //CLOCK CONTROL REGISTER
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET 		(0X30UL) //GPIO PERIPHERAL CLOCK ENABLE REGISTER
#define RCC_AHB1EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET			(0X00UL) //GPIO MODE REGISTER
#define GPIO_MODE_R				(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET				(0x14UL) // OUTPUT DATA REGISTER
#define GPIO_OD_R				(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define GPIOEN 					(1U<<0) // 0b 0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5					(1U<<5) // LED PIN SET IN GPIO_A
#define LED_PIN					PIN5


/*
 * (1U<<10) 	//SET BIT 10 TO 1
 * &=~(1U<<11)	//SET BIT 11 TO 0*/

/* RCC AHB1ENR REG =	0b 0000 0000 0000 0000 1000 1111 0000 0000
 * RCC AHB1ENR REG =	0b 0000 0000 0000 0000 0000 0000 0000 0001
*/

int main(void)
{
	/* 1. Enable clock access to GPIO*/
	RCC_AHB1EN_R |= GPIOEN;
	/* 2. Set PA5 as output pin*/
	GPIO_MODE_R  |= (1U<<10); //SET BIT 10 TO 1
	GPIO_MODE_R  &=~(1U<<11); //SET BIT 11 TO 0

	while(1)
	{
	/* 3. Set PA5 as high*/
		GPIO_OD_R ^=LED_PIN;
		for(int i=0;i<1000000;i++){}
	}
}
