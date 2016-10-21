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

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0     (GUI_ID_USER + 0x0F)
#define ID_BUTTON_0     (GUI_ID_USER + 0x10)
#define ID_BUTTON_1     (GUI_ID_USER + 0x11)
#define ID_PROGBAR_0     (GUI_ID_USER + 0x13)
#define ID_SPINBOX_0     (GUI_ID_USER + 0x14)
#define ID_SPINBOX_1     (GUI_ID_USER + 0x16)
#define ID_PROGBAR_1     (GUI_ID_USER + 0x17)
#define ID_DROPDOWN_0    (GUI_ID_USER + 0x18)
#define ID_FRAMEWIN_1     (GUI_ID_USER + 0x19)
#define ID_BUTTON_2     (GUI_ID_USER + 0x1A)
#define ID_TEXT_0     (GUI_ID_USER + 0x1B)

#define ID_FRAMEWIN_3     (GUI_ID_USER + 0x1C)
#define ID_BUTTON_OK     (GUI_ID_USER + 0x1D)
#define ID_TEXT_1     (GUI_ID_USER + 0x1E)
#define ID_WINDOW_1     (GUI_ID_USER + 0x1F)



/*********************************************************************
*
*       Static data
*
**********************************************************************
*/


extern WM_HWIN hWin_menu;
extern WM_HWIN hIcon_PWM,hIcon_Time, hIcon_SD,hIcon_PREV ;
extern int _cbButtonSkin(const WIDGET_ITEM_DRAW_INFO *pDrawItemInfo);

WM_HWIN hWin_timer;
WM_HWIN hWin_message;

int PhaseBrez=0;
int PhasePower=0;
int BrezPower=0;
float BrezKoeff=0;
int TimerONOFF=0;
uint8_t Brez_Count=0;
float BrezErr=0;

/*********************************************************************
*
*       _OwnerDraw
*/
//int _OwnerDraw(const WIDGET_ITEM_DRAW_INFO *pDrawItemInfo){
//	GUI_RECT Rect;
//	switch(pDrawItemInfo->Cmd)
//

/*********************************************************************
*
*       _cbMESSAGE
*/

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
*
*       _aTIMER
*/
static const GUI_WIDGET_CREATE_INFO _aTIMER[] = {
  { FRAMEWIN_CreateIndirect, "TIMER", ID_FRAMEWIN_0, 80, 20, 300, 200, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 10, 20, 50, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 80, 20, 50, 30, 0, 0x0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 160, 10, 20, 80, 1, 0x0, 0 },
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_0, 100, 110, 80, 40, 0, 0x0, 0 },
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_1, 200, 110, 80, 40, 0, 0x0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_1, 260, 10, 20, 80, 1, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0, 10, 100, 70, 35, 0, 0x0, 0 }, 
	
};



/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbTIMER(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int 		temp;
	int     NCode;
  int     Id;

	
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
		case WM_DELETE:
			
			hWin_timer=0;
		break;
		case WM_INIT_DIALOG:
			hItem = pMsg->hWin;
			FRAMEWIN_SetTitleHeight(hItem, 20);
			FRAMEWIN_SetFont(hItem,GUI_FONT_16_1);
			FRAMEWIN_AddCloseButton(hItem, FRAMEWIN_BUTTON_RIGHT,0);	
			FRAMEWIN_SetMoveable(hItem, 1);
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetText(hItem, "START");  //ПУСК
			if(TimerONOFF==1)
			{
				BUTTON_SetSkin(hItem, _cbButtonSkin);
				WM_SetFocus(hItem);
			}
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetText(hItem, "STOP");// СТОП
			if(TimerONOFF==0)
			{
				BUTTON_SetSkin(hItem, _cbButtonSkin);
				WM_SetFocus(hItem);
			}
			hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
			PROGBAR_SetValue(hItem, PhasePower);
			if(PhaseBrez==1)
				WM_HideWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_1);
			PROGBAR_SetValue(hItem, BrezPower);
			if(PhaseBrez==0)
				WM_HideWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
			DROPDOWN_AddString(hItem, "Phase");
			DROPDOWN_AddString(hItem, "Brez");
			DROPDOWN_SetSel(hItem,PhaseBrez);
			// USER START (Optionally insert additional code for further widget initialization)
			hItem=WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
			SPINBOX_SetValue(hItem,PhasePower);
			SPINBOX_SetRange(hItem,0,95);
			SPINBOX_SetFont(hItem,GUI_FONT_16_1);
			if(PhaseBrez==1)
				WM_DisableWindow(hItem);
			hItem=WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_1);
			SPINBOX_SetValue(hItem,BrezPower);
			SPINBOX_SetFont(hItem,GUI_FONT_16_1);
			if(PhaseBrez==0)
				WM_DisableWindow(hItem);
			
		
			
			// USER END
    break;
		case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
				case WM_NOTIFICATION_RELEASED:
					TimerONOFF=1;
					TIM2->CCER |=TIM_CCER_CC2E;												// Output Enable  CC2
					TIM2->CCER|=TIM_CCER_CC1E;												// Enable capture CC1
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);		
					BUTTON_SetSkin(hItem, _cbButtonSkin);
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);	
					BUTTON_SetSkin(hItem, BUTTON_SKIN_FLEX);
				break;
          }
    break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
					TIM2->CCER &=~TIM_CCER_CC2E;												// Output Disable CC2
					TIM2->CCER&=~TIM_CCER_CC1E;												   //Disable capture CC1
					Brez_Count=0;
					BrezErr=0;
					TimerONOFF=0;
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
					BUTTON_SetSkin(hItem, BUTTON_SKIN_FLEX);
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
					BUTTON_SetSkin(hItem, _cbButtonSkin);
			break;
      }
    break;
    case ID_SPINBOX_0: // Notifications sent by 'Spinbox'
      switch(NCode) {
      case WM_NOTIFICATION_VALUE_CHANGED:
        hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
				PhasePower=SPINBOX_GetValue(hItem);
				TIM2->ARR=1000-PhasePower*10;
				TIM2->CCR2=970-PhasePower*10;
				hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
				PROGBAR_SetValue(hItem, PhasePower);	
				WM_Paint(hItem);
			 break;
       }
    break;
    case ID_SPINBOX_1: // Notifications sent by 'Spinbox'
      switch(NCode) {
				case WM_NOTIFICATION_VALUE_CHANGED:
        hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_1);
				BrezPower=SPINBOX_GetValue(hItem);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_1);
				PROGBAR_SetValue(hItem, BrezPower);
				temp=BrezPower/2;
				BrezKoeff=temp/50.0f;
				WM_Paint(hItem);
			  break;
        }
    break;
    case ID_DROPDOWN_0: // Notifications sent by 'Dropdown'
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
        if(TimerONOFF)
					{
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
						DROPDOWN_Collapse(hItem);
						WM_Paint(hItem);
						Message("Остановите таймер!",Msg_Err);
					}
									
      break;
       case WM_NOTIFICATION_SEL_CHANGED:
        hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
				PhaseBrez=DROPDOWN_GetSel(hItem);
					if(PhaseBrez==0)
						{
							TIM2->CCMR1 &=~TIM_CCMR1_IC1PSC_0;	// Канал захвата настроим на каждый спад импульса
							TIM2->DIER &=~TIM_DIER_CC1IE;				//Если меняем режим на Фазовый то для TIM2 по Capture/Compare 1 interrupt disable
							TIM2->ARR=1000-PhasePower*10;
							TIM2->CCR2=970-PhasePower*10;
							hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_1);
							WM_HideWindow(hItem);
							hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_1);
							WM_DisableWindow(hItem);
							hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
							WM_ShowWindow(hItem);
							hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
							WM_EnableWindow(hItem);
							WM_Exec();
						}
					else if(PhaseBrez==1)
						{
							TIM2->CCMR1 |=TIM_CCMR1_IC1PSC_0; // Канал захвата настроим - прерывание на каждый второй спад импульса
							TIM2->DIER |=TIM_DIER_CC1IE;		//Если меняем режим на Брезенхема то для TIM2 по Capture/Compare 1 interrupt enable
							TIM2->ARR=45;
							TIM2->CCR2=15;
							hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
							WM_HideWindow(hItem);
							hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
							WM_DisableWindow(hItem);
							hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_1);
							WM_ShowWindow(hItem);
							hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_1);
							WM_EnableWindow(hItem);	
							WM_Exec();
						}	
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
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateTIMER
*/

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



WM_HWIN CreateTIMER(void) {
  hWin_timer = GUI_CreateDialogBox(_aTIMER, GUI_COUNTOF(_aTIMER), _cbTIMER, hWin_menu, 0, 0);
  return hWin_timer;
}


// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/