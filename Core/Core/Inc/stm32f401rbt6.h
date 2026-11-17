/***************************************************
Name : R.VYSHNAVI
KMID : KM62BEAI09
File : stm32f401rbt6.h
***************************************************/

/*************************************
*            BASE ADDRESSES 
*************************************/

#define RCC_BASEADDR 		0x40023800
#define STK_BASEADDR    0xE000E000
#define SPI_BASEADDR    0x40013000
#define EXTI_BASEADDR 	0x40013C00 
#define NVIC_BASEADDR 	0xE000E100
#define ADC_BASEADDR   0x40012000
#define GPIOA_BASEADDR 	0x40020000
#define GPIOB_BASEADDR 	0x40020400
#define GPIOC_BASEADDR 	0x40020800
#define SYSCFG_BASEADDR 0x40013800 
#define USART2_BASEADDR 0x40004400 
#define USART6_BASEADDR 0x40011400 

/*************************************** 
*         PHYSICAL ADDRESSES 
***************************************/

/************************ PHYSICAL ADDRESSES OF RCC ****************************************/

#define RCC_AHB1ENR *((int *)(RCC_BASEADDR+0x30))
#define RCC_APB1ENR *((int *)(RCC_BASEADDR+0x40))
#define RCC_APB2ENR *((int *)(RCC_BASEADDR+0x44))

/************************ PHYSICAL ADDRESSES OF GPIOA ****************************************/

#define GPIOA_ODR     *((int *)(GPIOA_BASEADDR+0x14))
#define GPIOA_IDR     *((int *)(GPIOA_BASEADDR+0x10))
#define GPIOA_PUPDR   *((int *)(GPIOA_BASEADDR+0x0C))
#define GPIOA_MODER   *((int *)(GPIOA_BASEADDR+0x00))
#define GPIOA_AFRL    *((int *)(GPIOA_BASEADDR+0x20))

/************************ PHYSICAL ADDRESSES OF GPIOB ****************************************/

#define GPIOB_ODR     *((int *)(GPIOB_BASEADDR+0x14))
#define GPIOB_IDR     *((int *)(GPIOB_BASEADDR+0x10))
#define GPIOB_PUPDR   *((int *)(GPIOB_BASEADDR+0x0C))
#define GPIOB_MODER   *((int *)(GPIOB_BASEADDR+0x00))

/************************ PHYSICAL ADDRESSES OF GPIOC ****************************************/

#define GPIOC_ODR     *((int *)(GPIOC_BASEADDR+0x14))
#define GPIOC_IDR     *((int *)(GPIOC_BASEADDR+0x10))
#define GPIOC_PUPDR   *((int *)(GPIOC_BASEADDR+0x0C))
#define GPIOC_MODER   *((int *)(GPIOC_BASEADDR+0x00))
#define GPIOC_AFRL    *((int *)(GPIOC_BASEADDR+0x20))

/************************ PHYSICAL ADDRESSES OF NVIC ****************************************/

#define NVIC_ISER0 	*((int *)(NVIC_BASEADDR+0x00))
#define NVIC_ISER1 	*((int *)(NVIC_BASEADDR+0x04))

/************************ PHYSICAL ADDRESSES OF EXTI ****************************************/

#define EXTI_IMR 		*((int *)(EXTI_BASEADDR+0x00))
#define EXTI_FTSR 	*((int *)(EXTI_BASEADDR+0x0C))
#define EXTI_RTSR 	*((int *)(EXTI_BASEADDR+0x08))
#define EXTI_PR 		*((int *)(EXTI_BASEADDR+0x14))
	
/************************ PHYSICAL ADDRESSES OF SYSCFG **************************************/

#define SYSCFG_EXTICR1 *((int *)(SYSCFG_BASEADDR+0x08))
#define SYSCFG_EXTICR2 *((int *)(SYSCFG_BASEADDR+0x0C))
#define SYSCFG_EXTICR3 *((int *)(SYSCFG_BASEADDR+0x10))
#define SYSCFG_EXTICR4 *((int *)(SYSCFG_BASEADDR+0x14))
	
/************************ PHYSICAL ADDRESSES OF STK *****************************************/

#define STK_CTRL  *((int *)(STK_BASEADDR+0x10))
#define STK_LOAD  *((int *)(STK_BASEADDR+0x14))
#define STK_VAL   *((int *)(STK_BASEADDR+0x18))


/************************ PHYSICAL ADDRESSES OF ADC *****************************************/

#define ADC_CR1    *((int *)(ADC_BASEADDR+0x04))
#define ADC_CR2    *((int *)(ADC_BASEADDR+0x08))
#define ADC_SR     *((int *)(ADC_BASEADDR+0x00))
#define ADC_DR     *((int *)(ADC_BASEADDR+0x4C))
#define ADC_SQR1   *((int *)(ADC_BASEADDR+0x2C))
#define ADC_SQR2   *((int *)(ADC_BASEADDR+0x30))
#define ADC_SQR3   *((int *)(ADC_BASEADDR+0x34))
#define ADC_HTR    *((int *)(ADC_BASEADDR+0x24))
#define ADC_LTR    *((int *)(ADC_BASEADDR+0x28))
	
/************************ PHYSICAL ADDRESSES OF USART2 *****************************************/

#define USART2_CR1    *((int *)(USART2_BASEADDR+0x0C))
#define USART2_CR2    *((int *)(USART2_BASEADDR+0x10))
#define USART2_BRR    *((int *)(USART2_BASEADDR+0x08))
#define USART2_SR     *((int *)(USART2_BASEADDR+0x00))
#define USART2_DR     *((int *)(USART2_BASEADDR+0x04))
	
/************************ PHYSICAL ADDRESSES OF USART6 *****************************************/

#define USART6_CR1    *((int *)(USART6_BASEADDR+0x0C))
#define USART6_CR2    *((int *)(USART6_BASEADDR+0x10))
#define USART6_BRR    *((int *)(USART6_BASEADDR+0x08))
#define USART6_SR     *((int *)(USART6_BASEADDR+0x00))
#define USART6_DR     *((int *)(USART6_BASEADDR+0x04))
	

/************************ PHYSICAL ADDRESSES OF SPI *****************************************/

#define SPI_CR1   *((int *)(SPI_BASEADDR+0x00))
#define SPI_CR2   *((int *)(SPI_BASEADDR+0x04))
#define SPI_SR    *((int *)(SPI_BASEADDR+0x08))
#define SPI_DR    *((int *)(SPI_BASEADDR+0x0C))
	