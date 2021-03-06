/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.22                          *
*        Compiled Jul  4 2013, 15:16:01                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "header.h"
#include <string.h>

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//#define Bank1_LCD_Data    ((uint32_t)0x60020000) // display controller Data ADDR

#define ID_WINDOW_0     (GUI_ID_USER + 0x00)
#define ID_ICON_CALIB    (GUI_ID_USER + 0x04)
#define ID_ICON_NEXT     (GUI_ID_USER + 0x05)


#define ID_BUTTON_BACK     (GUI_ID_USER + 0x1C)
#define ID_ICON_PAINT     (GUI_ID_USER + 0x15)
#define ID_ICON_EXIT 			(GUI_ID_USER + 0x16)
#define ID_ICON_PHOTO     (GUI_ID_USER + 0x17)

#define ID_ICON_ALARM_A     (GUI_ID_USER + 0x18)


#define ID_ICON_BLUE     (GUI_ID_USER + 0x1D)
#define ID_ICON_GREEN     (GUI_ID_USER + 0x1E)
#define ID_ICON_RED     (GUI_ID_USER + 0x1F)
#define ID_ICON_CYAN     (GUI_ID_USER + 0x20)
#define ID_ICON_MAGENTA     (GUI_ID_USER + 0x21)
#define ID_ICON_YELLOW     (GUI_ID_USER + 0x22)
#define ID_ICON_BLACK     (GUI_ID_USER + 0x23)
#define ID_ICON_BROWN     (GUI_ID_USER + 0x24)
#define ID_ICON_ORANGE     (GUI_ID_USER + 0x25)
#define ID_ICON_WHITE     (GUI_ID_USER + 0x26)

#define ID_BUTTON_OK     (GUI_ID_USER + 0x1B)
#define ID_WINDOW_1     (GUI_ID_USER + 0x01)
#define ID_FRAMEWIN_3     (GUI_ID_USER + 0x1A)
#define ID_TEXT_1     (GUI_ID_USER + 0x19)

#define ID_EDIT_1  				   (GUI_ID_USER + 0x27)
	
// USER START (Optionally insert additional defines)
extern volatile uint8_t canerr_clr;
extern volatile uint8_t canerr_disp;
extern volatile uint8_t time_disp;
extern volatile uint8_t canconnect;

extern void PictureView(void);
extern void Draw_JPG_File(const char *FileName);
extern void SD_LowLevel_Init(void);

extern GPIO_InitTypeDef 							GPIO_InitStruct;

extern WM_HWIN hWin_menu;
extern WM_HWIN hWin_message;

extern uint8_t cycle_start_pwm;

extern FIL pFile;

#define FLAG_STATUS_PAGE	0x08002000
extern volatile uint8_t write_flashflag;

extern void Flash_page_erase(uint32_t address,uint8_t countpage);
extern void Flash_prog(uint16_t * src,uint16_t * dst,uint32_t nbyte);

void CreateStart(void);

WM_HWIN hWin_start;
EDIT_Handle hEdit_time;
ICONVIEW_Handle hIcon_CALIB,hIcon_PAINT,hIcon_NEXT,hButton_BACK,hALARMA,hIcon_EXIT,hIcon_PHOTO;
ICONVIEW_Handle hIcon[9];

int xD[]={ID_ICON_BLUE,ID_ICON_GREEN,ID_ICON_RED,ID_ICON_CYAN,ID_ICON_MAGENTA,ID_ICON_YELLOW,ID_ICON_WHITE,ID_ICON_BLACK,ID_ICON_ORANGE};
int color[]={GUI_BLUE,GUI_GREEN,GUI_RED,GUI_CYAN,GUI_MAGENTA,GUI_YELLOW,GUI_WHITE,GUI_BLACK,GUI_ORANGE};

uint8_t sd_insert;
uint8_t sd_ins_rem;

/*********************************************************************
*       			_cbMESSAGE
*********************************************************************/
static void _cbMESSAGE(WM_MESSAGE * pMsg) {
  GUI_RECT pRECT;
	int     NCode,x,y;
  int     Id;
	switch (pMsg->MsgId) {
		case WM_DELETE:
			hWin_message=0;
		break;	
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
				switch(Id) {
					case ID_BUTTON_OK: 
						switch(NCode) {
							case WM_NOTIFICATION_RELEASED:
								WM_GetWindowRectEx(hWin_message, &pRECT);
								x=WM_GetWindowSizeX(hWin_message);
								y=WM_GetWindowSizeY(hWin_message);
								WM_DeleteWindow(hWin_message);
								GUI_ClearRect(pRECT.x0,pRECT.y0,pRECT.x0+x,pRECT.y0+y);
								
							break;	
							}
					break;
					}
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}
/*********************************************************************
*      				Message
**********************************************************************/
WM_HWIN Message(const char *p,int flag ){
	WM_HWIN hWin;
	BUTTON_Handle hButton;
	TEXT_Handle hText;
	int temp;
	if(hWin_message!=0)
			return hWin_message;
	GUI_SetFont(&GUI_FontArial16);
	temp=GUI_GetStringDistX(p);
	hWin_message=FRAMEWIN_CreateEx((240-temp/2),100,temp+16, 80,0, WM_CF_SHOW,0,ID_FRAMEWIN_3,0,0);
	FRAMEWIN_SetFont(hWin_message,&GUI_FontArial16);
	FRAMEWIN_SetActive(hWin_message, 1);
	if(flag==Msg_Err)
	{
		FRAMEWIN_SetBarColor(hWin_message,1,GUI_RED);
		FRAMEWIN_SetText(hWin_message, "Ошибка");
	}
	else 
		FRAMEWIN_SetText(hWin_message, "Сообщение");
	FRAMEWIN_SetTextAlign(hWin_message,GUI_TA_HCENTER);
	
	hWin=WINDOW_CreateEx(3,22,temp+9,55,hWin_message,WM_CF_SHOW,0,ID_WINDOW_1,_cbMESSAGE);
	WINDOW_SetBkColor(hWin, GUI_WHITE);
	
	hButton=BUTTON_CreateEx(((temp+16)/2-15),32,30,20,hWin, WM_CF_SHOW,0,ID_BUTTON_OK);
	BUTTON_SetText(hButton, "OK");
	
	hText=TEXT_CreateEx(5,10,temp,20,hWin,WM_CF_SHOW,TEXT_CF_HCENTER,ID_TEXT_1,p);
	TEXT_SetFont(hText,&GUI_FontArial16);
	
	
	WM_MakeModal(hWin_message);
	GUI_SetFont(&GUI_Font8x16);
	return hWin_message;
}
/*********************************************************************
*       			wcstrcat
**********************************************************************/
void wcstrcat(TCHAR *string_1,const TCHAR *string_2)
{
	for(;;)
	{
		if(*string_1=='\0')
			break;
		else
			string_1++;
	}
	for(;;)
	{
		*string_1++=*string_2++;
		if(*string_2=='\0')
			{*string_1=*string_2;
				break;
			}
	}
}

/*********************************************************************
*       			_cbSTART
**********************************************************************/
static void _cbSTART(WM_MESSAGE* pMsg) {
	int     NCode;
  int     Id;
	char i;
  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
			case ID_ICON_PHOTO: // Notifications sent by 'Button'
					switch(NCode) {
						case WM_NOTIFICATION_RELEASED:
							if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)==0)
								{
									Path[0]='0';
									Path[1]=':';
									Path[2]='\0';
									wcstrcat(Path,_T("Photo"));
									/* First entry directory Picture	*/
									fresult=f_opendir(&dir, Path);	
									if(fresult==FR_NO_PATH)
										Message("Папка Photo не найдена",Msg_Err);
									else
									{			
									time_show=0;
									WM_HideWindow(hWin_start);
									WM_HideWindow(hIcon_EXIT);
									WM_HideWindow(hALARMA);
									WM_HideWindow(PROGBAR_MEM);	
									PictureView();
									}	
									
								}
							else
								Message("Вставьте SD карту!",Msg_Err);
								
						break;
						}
			break;
			case ID_ICON_CALIB: // Notifications sent by 'Button'
					switch(NCode) {
						case WM_NOTIFICATION_RELEASED:
							time_show=0;
							WM_HideWindow(hWin_start);
							WM_HideWindow(hIcon_EXIT);
							WM_HideWindow(hALARMA);
							WM_HideWindow(PROGBAR_MEM);
							Touch_calibration();
						break;
					}
			break;
			case ID_ICON_NEXT: // Notifications sent by 'Button'
					switch(NCode) {
						case WM_NOTIFICATION_RELEASED:
							time_show=1;
							WM_HideWindow(hWin_start);
							if(hWin_menu==0)
								//{__disable_irq();
									CreateMENU();
								 //__enable_irq(); }
							else
								//{__disable_irq();
								 WM_ShowWindow(hWin_menu);
								 //__enable_irq(); }
						break;
           }
			break;
			case ID_ICON_PAINT: // Notifications sent by 'Button'
					switch(NCode) {
							case WM_NOTIFICATION_RELEASED:
							NVIC_DisableIRQ(TIM7_IRQn);
							NVIC_DisableIRQ(RTC_IRQn);
							
							time_show=0;
							WM_HideWindow(hWin_start);
							WM_HideWindow(hIcon_EXIT);
							WM_HideWindow(hALARMA);
							WM_HideWindow(PROGBAR_MEM);
							GUI_SetPenSize(7);
							GUI_SetBkColor(GUI_WHITE);
							GUI_SetColor(GUI_WHITE);
							GUI_Clear();
							TIM6->ARR = 40;
						  TIM6->EGR = TIM_EGR_UG;	
						  hButton_BACK=BUTTON_CreateEx(400,220,50,30,WM_HBKWIN,WM_CF_SHOW,0,ID_BUTTON_BACK);
							BUTTON_SetText(hButton_BACK, "EXIT");	
							
							for(i=0;i<9;i++)
						 {
							hIcon[i]=ICONVIEW_CreateEx(0,i*30,30,30,WM_HBKWIN,WM_CF_SHOW,0,xD[i],30,30);
							ICONVIEW_SetBkColor(hIcon[i], ICONVIEW_CI_BK, color[i]);
						 }
						 
							drawmode=1;	
						break;
						}
					break;		
		}
  break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}






/*********************************************************************
*       			_cbBkWin
***********************************************************************/
void _cbBkWin(WM_MESSAGE* pMsg) {
  
	int			i;
	int     NCode;
  int     Id;
	switch(pMsg->MsgId) {
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id){
				case ID_ICON_EXIT:
					switch(NCode) {
						case WM_NOTIFICATION_RELEASED:
							NVIC_SystemReset();
						break;
					}
				break;
				case ID_BUTTON_BACK:
					switch(NCode){
						case WM_NOTIFICATION_RELEASED:
							drawmode=0;
							WM_DeleteWindow(hButton_BACK);
							hButton_BACK=0;
							for(i=0;i<9;i++)
							{WM_DeleteWindow(hIcon[i]);
							hIcon[i]=0;
							}
							TIM6->ARR=250;
							TIM6->EGR = TIM_EGR_UG;
							TIM7->CNT=0;
													
							NVIC_EnableIRQ(TIM7_IRQn);
							NVIC_EnableIRQ(RTC_IRQn);
							
							GUI_SetBkColor(GUI_LIGHTBLUE);
							GUI_ClearRect(1,17,58,270);
							GUI_SetColor(GUI_YELLOW);
							GUI_DrawRect(0,16,59,271);
							GUI_SetBkColor(GUI_DARKBLUE);
							GUI_ClearRect(0,0,470,15);
							
							CreateStart();
						  WM_ShowWindow(hALARMA);
							WM_ShowWindow(hIcon_EXIT);
							WM_ShowWindow(PROGBAR_MEM);
							break;	
						}
					break;
					
					case ID_ICON_BLUE:
					switch(NCode){
						case WM_NOTIFICATION_CLICKED:			
						GUI_SetColor(GUI_BLUE);
						break;
						}
					break;
					case ID_ICON_GREEN:
					switch(NCode){
						case WM_NOTIFICATION_CLICKED:			
						GUI_SetColor(GUI_GREEN);
						break;
						}
					break;
					case ID_ICON_RED:
					switch(NCode){
						case WM_NOTIFICATION_CLICKED:			
						GUI_SetColor(GUI_RED);
						break;
						}
					break;
					case ID_ICON_CYAN:
					switch(NCode){
						case WM_NOTIFICATION_CLICKED:			
						GUI_SetColor(GUI_CYAN);
						break;
						}
					break;			
					case ID_ICON_MAGENTA:
					switch(NCode){
						case WM_NOTIFICATION_CLICKED:			
						GUI_SetColor(GUI_MAGENTA);
						break;
						}
					break;
					case ID_ICON_YELLOW:
					switch(NCode){
						case WM_NOTIFICATION_CLICKED:			
						GUI_SetColor(GUI_YELLOW);
						break;
						}
					break;
					case ID_ICON_WHITE:
					switch(NCode){
						case WM_NOTIFICATION_CLICKED:			
						GUI_SetPenSize(20);
						GUI_SetColor(GUI_WHITE);
						break;
						}
					break;
					case ID_ICON_BLACK:
					switch(NCode){
						case WM_NOTIFICATION_CLICKED:			
						GUI_SetColor(GUI_BLACK);
						break;
						}
					break;
					case ID_ICON_ORANGE:
					switch(NCode){
						case WM_NOTIFICATION_CLICKED:			
						GUI_SetColor(GUI_ORANGE);
						break;
						}
					break;		
				}	
			break;	
	 default:
    WM_DefaultProc(pMsg);
  }
}

void CreateStart(void)
{
	uint32_t cnt,alrm;
	__disable_irq();
	GUI_SetAlpha(0);
	
	if(hWin_start==0)
	{
		hWin_start=WINDOW_CreateEx(60,15,410, 260,WM_HBKWIN, WM_CF_SHOW,0,ID_WINDOW_0,_cbSTART);	
		WINDOW_SetBkColor(hWin_start, GUI_LIGHTBLUE);	
		
		hIcon_PHOTO=ICONVIEW_CreateEx(240,0,66,65,hWin_start,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_PHOTO,56,62);
		ICONVIEW_SetFont(hIcon_PHOTO,&GUI_FontArial16);
		ICONVIEW_AddBitmapItem(hIcon_PHOTO,&bmphoto,"Фото"); //&bmphoto
		ICONVIEW_SetIconAlign(hIcon_PHOTO, ICONVIEW_IA_TOP);
		
		
		hIcon_CALIB=ICONVIEW_CreateEx(340,0,66,65,hWin_start,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_CALIB,56,62);
		ICONVIEW_SetFont(hIcon_CALIB,&GUI_FontArial16);
		ICONVIEW_AddBitmapItem(hIcon_CALIB,&bmscreen,"Touch"); //&bmscreen
		ICONVIEW_SetIconAlign(hIcon_CALIB, ICONVIEW_IA_TOP);
		
		hIcon_PAINT=ICONVIEW_CreateEx(340,90,66,65,hWin_start,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_PAINT,56,62);
		ICONVIEW_SetFont(hIcon_PAINT,&GUI_FontArial16);
		ICONVIEW_AddBitmapItem(hIcon_PAINT,&bmpaint,"Краски"); //&bmpaint
		ICONVIEW_SetIconAlign(hIcon_PAINT, ICONVIEW_IA_TOP);
		
		hIcon_NEXT=ICONVIEW_CreateEx(340,200,58,58,hWin_start,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_NEXT,48,48);
		ICONVIEW_AddBitmapItem(hIcon_NEXT,&bmnext,"");   //&bmnext
		
		
		
		hIcon_EXIT=ICONVIEW_CreateEx(0,214,58,58,WM_HBKWIN,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_EXIT,48,48);
		ICONVIEW_AddBitmapItem(hIcon_EXIT,&bmexit,""); //&bmexit
		
		hALARMA=ICONVIEW_CreateEx(10,15,34,34,WM_HBKWIN,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_ALARM_A,24,24);
		alrm=(BKP->DR1<<16 |BKP->DR2);
		cnt=RTC->CNTH<<16|RTC->CNTL;
		if(alrm>cnt)
			ICONVIEW_AddBitmapItem(hALARMA,&bmAlarmA,""); //&bmAlarmA
		else
			ICONVIEW_AddBitmapItem(hALARMA,&bmAlarm_D,""); //&bmAlarm_D
	}
	else
		WM_ShowWindow(hWin_start);
		
	DateCalc();
	time_show=1;
	__enable_irq();
}


void MainTask(void)
{
	uint16_t count;
	uint16_t flag=0x00A7;
	
	uint32_t i;
	NVIC_SetPriority(SysTick_IRQn,1);
	WM_SetCallback(WM_HBKWIN, _cbBkWin);
		
	
	GUI_SetBkColor(GUI_LIGHTBLUE);
	GUI_ClearRect(1,17,58,270);
	GUI_SetColor(GUI_YELLOW);
	GUI_DrawRect(0,16,59,271);
	GUI_SetBkColor(GUI_DARKBLUE);
	GUI_ClearRect(0,0,470,15);
	
	EXTI_ClearITPendingBit(EXTI_Line0);
	NVIC_ClearPendingIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI0_IRQn);									//Разрешение EXTI0_IRQn прерывания
	
	WM_SetDesktopColor(GUI_DARKCYAN);
	
	pWIDGET_DRAW_ITEM_FUNC=BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);	
	SCROLLBAR_SetDefaultWidth(20);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	PROGBAR_MEM=PROGBAR_CreateEx(470,0,10,272,WM_HBKWIN,WM_CF_SHOW,PROGBAR_CF_VERTICAL,PROGBAR_MEM);
	PROGBAR_SetMinMax(PROGBAR_MEM,0,40*1024);
	AlarmCalc();
	
	
	GUI_EnableAlpha(1);
	CreateStart();
	
	while(1)
	{
		GUI_Delay(5);	
		
		if(canerr_clr)
		{
			GUI_SetBkColor(GUI_DARKBLUE);
			GUI_ClearRect(120,5,290,15);
			canerr_clr=0;
		}
		if(canerr_disp)	
		{
				GUI_SetFont(&GUI_Font6x8);
				GUI_DispStringAt("REC ",120,5);
				GUI_DispDec((uint8_t)((CAN1->ESR)>>24),3);
				GUI_DispStringAt("TEC ",190,5);
				GUI_DispDec((uint8_t)((CAN1->ESR)>>16),3);
				GUI_DispStringAt("ERF ",260,5);
				GUI_DispDec((uint8_t)(CAN1->ESR),1);
			
				GUI_SetFont(&GUI_FontArial16);	
				canerr_disp=0;
		}
		if(time_disp)
		{
			GUI_SetFont(&GUI_Font8x16);
			GUI_DispDecAt(Time.hour,350,0,2);
			GUI_DispString(":");
			GUI_DispDec(Time.min,2);
			time_disp=0;	
		}
		if(sd_ins_rem)
		{	
			if(hWin_message==0)
				sd_ins_rem=0;
			if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)==0)	
			{
				if(sd_error==SD_OK)
					{
						Message("SD карта вставлена",Msg_Msg);
					}	
				else
					{
						Message("Ошибка SD карты",Msg_Err);
					}
			}			
			else
			{
			  Message("SD карта удалена",Msg_Msg);
			}
		}
		if(ALARM_INT)
		{
			WM_DeleteWindow(hALARMA);
			hALARMA=ICONVIEW_CreateEx(10,15,34,34,WM_HBKWIN,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_ALARM_A,24,24);
			ICONVIEW_AddBitmapItem(hALARMA,&bmAlarm_D,"");
			ALARM_INT=0;
		}
/*
*
****************************************************************************************************************************/		
		if(write_flashflag)
		{
					// проверим флаг  в секторе FLAG_STATUS во флэш.
			count=0;
			while(*(uint16_t*)(FLAG_STATUS_PAGE+count)!=0xFFFF)		// Перебираем байты пока не дойдем до неписанного поля 0xFF 
			{
			count+=2;
			if(count>=2048)
				{
					count=0;
					
#ifdef MEDIUM_DENSITY			
				Flash_page_erase(FLAG_STATUS_PAGE,2);
#else	
				Flash_page_erase(FLAG_STATUS_PAGE,1);
#endif				
				break;
				}
			}
				
			Flash_prog((uint16_t*)&flag,(uint16_t*)(FLAG_STATUS_PAGE+count),2);
			SysTick->LOAD=(2500000*4);
			SysTick->VAL=0;
			while(!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk)){}	
			NVIC_SystemReset();
		}
		if(sleep_mode)
		{
			SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
			SysTick->CTRL&=~SysTick_CTRL_TICKINT_Msk;
			NVIC_DisableIRQ(EXTI0_IRQn);	
			NVIC_DisableIRQ(TIM6_IRQn); 							
			NVIC_DisableIRQ(TIM7_IRQn); 									
			NVIC_DisableIRQ(RTC_IRQn);						
			
			GPIOB->BSRR=GPIO_BSRR_BS5;		//закрываем нижний MOSFET  выкл. питание на LCD					
				
			/*GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;
			GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;	
			GPIO_InitStruct.GPIO_Pin=	GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|
																GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|
																GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	
			GPIO_Init(GPIOA, &GPIO_InitStruct);	
			
			
			GPIO_InitStruct.GPIO_Pin=GPIO_Pin_All;
			GPIO_Init(GPIOB, &GPIO_InitStruct);	
			
			GPIO_InitStruct.GPIO_Pin=	GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|
																GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
			GPIO_Init(GPIOC, &GPIO_InitStruct);	
			
			GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|
																GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|
																GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
			GPIO_Init(GPIOD, &GPIO_InitStruct);
			
			
			GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5|
																GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|
																GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
			GPIO_Init(GPIOE, &GPIO_InitStruct);
			if((GPIOE->IDR&GPIO_IDR_IDR0)==0)
			{
				GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
				GPIO_Init(GPIOE, &GPIO_InitStruct);
			}*/
			__WFI();
/**********************************************************		  
*						WakeUp from stop mode													*	
**********************************************************/				
			RCC->CR|= RCC_CR_HSEON;
			while((RCC->CR&RCC_CR_HSERDY)!=RCC_CR_HSERDY) {}
			//RCC->CFGR    PLLXTPRE=0x00   (HSE clock not divided)
			//RCC->CFGR    PLLMUL=0x07      (PLL input clock x 9)
			//RCC->CFGR   PLLSRC=0x01        (HSE oscillator clock selected as PLL input clock)	
			
			RCC->CR|= RCC_CR_PLLON;
			while((RCC->CR& RCC_CR_PLLRDY)!=RCC_CR_PLLRDY) {}
			RCC->CFGR|=RCC_CFGR_SW_PLL  ;
			while((RCC->CFGR&RCC_CFGR_SWS_PLL)!=RCC_CFGR_SWS_PLL) {}
/**************************************************************
*																															*
**************************************************************/				
			/*GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
			GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
			GPIO_Init(GPIOA, &GPIO_InitStruct);	
				
			GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
			GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
			GPIO_Init(GPIOA, &GPIO_InitStruct);	*/
				
			//Init_FSMC_GPIO();
			//TSC2046_LowLevel_Init();
			//SD_LowLevel_Init();
				
			EXTI_ClearITPendingBit(EXTI_Line0);
			NVIC_ClearPendingIRQ(EXTI0_IRQn);
												
				
			/*GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
			GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
			GPIO_Init(GPIOB,&GPIO_InitStruct);		*/
			GPIOB->BSRR=GPIO_BSRR_BR5;									//открываем нижний MOSFET  подаем питание на LCD
			SysTick->VAL=0;
			SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
			SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;
				
			Init_ssd1963();
						
		
			if(WM_IsVisible(hWin_start))
			{
				WM_HideWindow(hWin_start);
				WM_ShowWindow(hWin_start);
			}
			if(WM_IsVisible(hWin_menu))
			{
				WM_HideWindow(hWin_menu);
				WM_ShowWindow(hWin_menu);
			}
			if (drawmode)
				{	
					GUI_Clear();
					for(i=0;i<9;i++)
						{
							WM_HideWindow(hIcon[i]);
							WM_ShowWindow(hIcon[i]);
						}
					WM_Paint(hButton_BACK);
					WM_Exec();	
								
				}
			else
				{
				
				TIM7->CNT=0;
				TIM7->SR &= ~TIM_SR_UIF; 			//Сбрасываем флаг UIF
				GUI_SetBkColor(GUI_LIGHTBLUE);
				GUI_ClearRect(1,17,58,270);
				GUI_SetColor(GUI_YELLOW);
				GUI_DrawRect(0,16,59,271);
				GUI_SetBkColor(GUI_DARKBLUE);
				GUI_ClearRect(0,0,470,15);
					
				GUI_SetFont(&GUI_Font8x16);
				GUI_DispDecAt(Time.day,5,0,2);
				GUI_DispString(":");
				GUI_DispDec(Time.month,2);
				GUI_DispString(":20");
				GUI_DispDec(Time.year,2);	
				
				WM_Paint(hALARMA);
				WM_Paint(hIcon_EXIT);		
				WM_Exec();
				NVIC_EnableIRQ(EXTI0_IRQn); 									//Разрешение TIM2_IRQn прерывания
				NVIC_EnableIRQ(TIM7_IRQn); 									//Разрешение TIM7_IRQn прерывания
				NVIC_EnableIRQ(RTC_IRQn);										//Разрешение RTC_IRQn прерывания
				}
			
			NVIC_EnableIRQ(TIM6_IRQn); 							//Разрешение TIM6_DAC_IRQn прерывания
			backlight=BACKLIGHT_OFF;
			backlight_delay=0;
			sleep_mode=0;
		}
	}
}


/*************************** End of file ****************************/
