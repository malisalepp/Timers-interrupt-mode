#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

static void gpioConfig(){

  GPIO_InitTypeDef GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;               
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;      
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIOInitStructure);

}

static void timerConfig(){

   TIM_TimeBaseInitTypeDef TIMERInitStructure;
	 NVIC_InitTypeDef NVICInitStructure;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	 TIMERInitStructure.TIM_ClockDivision = 1;                   
	 TIMERInitStructure.TIM_CounterMode = TIM_CounterMode_Up;    
	 TIMERInitStructure.TIM_Period = 11999;                       
	 TIMERInitStructure.TIM_Prescaler = 3999;                    
	 TIMERInitStructure.TIM_RepetitionCounter = 0;               

   TIM_TimeBaseInit(TIM3,&TIMERInitStructure);
	 TIM_Cmd(TIM3,ENABLE);
	
	 NVICInitStructure.NVIC_IRQChannel = TIM3_IRQn;
	 NVICInitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVICInitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	 NVICInitStructure.NVIC_IRQChannelSubPriority = 0;
	
	 TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	 NVIC_Init(&NVICInitStructure);
	
}

static void toggle_led(){

   uint16_t readLead = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);

	 if(readLead ==(uint16_t)Bit_SET){
	 
	 GPIO_ResetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
	 
	 }
	 
	 else{
		
	 GPIO_SetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);	
		
	 }
	
}

static void TIM3_IRQHandler(){

     toggle_led();
   	 TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

}


int main(){

	 gpioConfig();
	 timerConfig();
	 TIM3_IRQHandler();
	
   while(1){
	 
	 
	 
		}
	 
}



