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
#define ID_WINDOW_0     (GUI_ID_USER + 0x07)
#define ID_ICON_PWM     (GUI_ID_USER + 0x0E)
#define ID_ICON_TIME     (GUI_ID_USER + 0x15)
#define ID_ICON_PREV     (GUI_ID_USER + 0x16)
#define ID_ICON_SDCARD     (GUI_ID_USER + 0x17)
#define ID_ICON_ALARM     (GUI_ID_USER + 0x18)

extern WM_HWIN hWin_alarm;
extern WM_HWIN hWin_time;
extern WM_HWIN hWin_timer;
extern WM_HWIN hWin_SD;
extern WM_HWIN BUTTON_KEY(void);

WM_HWIN CreateMENU(void);

WM_HWIN hWin_menu;


ICONVIEW_Handle hIcon_PWM,hIcon_Time, hIcon_SD,hIcon_PREV,hIcon_ALARM ;
WM_HWIN hWin;
GUI_RECT  pRect;

/*********************************************************************
*
*       _cbMENU
*/
static void _cbMENU(WM_MESSAGE * pMsg) {
  
	int     NCode;
  int     Id;

  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_ICON_PWM: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
			if(hWin_timer==0)	
				CreateTIMER();
			break;
      }
    break;
    case ID_ICON_TIME: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
       if(hWin_time==0)	
				 CreateTIME_DATE();
			break;
      }
    break;
    case ID_ICON_SDCARD: 
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
			if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)==0)	
			{	
					if(countSD_files_window<2)
					{
						countSD_files_window++;  // Inrement count window SD_files
						SD_Files();
					}
			}		
			else
				Message("Вставьте SD карту!!! ", Msg_Err);
			break;
      }
    break;
    case ID_ICON_ALARM: 
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
				if(hWin_alarm==0)	
					CreateALARM();
			break;
      }
    break;
		case ID_ICON_PREV: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
        	WM_HideWindow(hWin_menu);
				//	WM_DeleteWindow(hWin_menu);//hWin_menu=0;
					CreateStart();
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
*       CreateMENU
*/

WM_HWIN CreateMENU(void) {
	
		hWin_menu=WINDOW_CreateEx(60,15,410, 260,WM_HBKWIN, WM_CF_SHOW,0,ID_WINDOW_0,_cbMENU);	
		WINDOW_SetBkColor(hWin_menu, 0x00DF6687);	
			
		hIcon_ALARM=ICONVIEW_CreateEx(100,70,75,75,hWin_menu,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_ALARM,65,65);
		ICONVIEW_AddBitmapItem(hIcon_ALARM,&bmalarm,"Будильник"); 
		ICONVIEW_SetFont(hIcon_ALARM,&GUI_FontArial16);
		
		hIcon_PWM=ICONVIEW_CreateEx(100,0,66,65,hWin_menu,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_PWM,56,62);
		ICONVIEW_AddBitmapItem(hIcon_PWM,&bmpwm,"Таймер");	
		ICONVIEW_SetFont(hIcon_PWM,&GUI_FontArial16);
		ICONVIEW_SetIconAlign(hIcon_PWM, ICONVIEW_IA_TOP);
		
		hIcon_Time=ICONVIEW_CreateEx(20,0,66,65,hWin_menu,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_TIME,56,61);
		ICONVIEW_AddBitmapItem(hIcon_Time,&bmdate,"Время");	
		ICONVIEW_SetFont(hIcon_Time,&GUI_FontArial16);
		ICONVIEW_SetIconAlign(hIcon_Time, ICONVIEW_IA_TOP);
		
		hIcon_SD=ICONVIEW_CreateEx(20,70,66,65,hWin_menu,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_SDCARD,56,62);
		ICONVIEW_AddBitmapItem(hIcon_SD,&bmsd,"SD карта");	
		ICONVIEW_SetFont(hIcon_SD,&GUI_FontArial16);
		ICONVIEW_SetIconAlign(hIcon_SD, ICONVIEW_IA_TOP);
		
		hIcon_PREV=ICONVIEW_CreateEx(20,200,58,58,hWin_menu,WM_CF_SHOW|WM_CF_HASTRANS,0,ID_ICON_PREV,48,48);
		ICONVIEW_AddBitmapItem(hIcon_PREV,&bmprev,"");	
		
		return hWin_menu;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
