diff --git a/winmine.c b/winmine.c
index 5bc911a..40f7736 100644
--- a/winmine.c
+++ b/winmine.c
@@ -5,9 +5,10 @@
 ****************************************************************************/
 
 #define _WINDOWS
+#define WIN32_LEAN_AND_MEAN
 #include <windows.h>
-#include <port1632.h>
 
+#include "port1632.h"
 #include "main.h"
 #include "rtns.h"
 #include "grafix.h"
@@ -286,15 +287,20 @@ BOOL FLocalButton(LONG lParam)
 
 		switch (msg.message)
 			{
-	   case WM_LBUTTONUP:
-			if (fDown)
-				{
-				if (PtInRect(&rcCapt, msg.pt))
-					{
-					DisplayButton(iButtonCur = iButtonHappy);
-					StartGame();
-					}
-				}
+		case WM_LBUTTONUP:
+		    if (fDown)
+		    {
+			   if (PtInRect(&rcCapt, msg.pt))
+			   {
+				   DisplayButton(iButtonCur = iButtonHappy);
+				   if (Preferences.wGameType == wGame2048) {
+					   _2048_Start();
+				   }
+				   else {
+					   StartGame();
+				   }
+			   }
+		    }
 			ReleaseCapture();
 			return fTrue;
 
@@ -333,6 +339,7 @@ VOID FixMenus(VOID)
 	CheckEm(IDM_INTER,  Preferences.wGameType == wGameInter);
 	CheckEm(IDM_EXPERT, Preferences.wGameType == wGameExpert);
 	CheckEm(IDM_CUSTOM, Preferences.wGameType == wGameOther);
+	CheckEm(IDM_2048,   Preferences.wGameType == wGame2048);
 
 	CheckEm(IDM_COLOR,  Preferences.fColor);
 	CheckEm(IDM_MARK,   Preferences.fMark);
@@ -452,6 +459,14 @@ LONG  APIENTRY MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LONG lParam)
 		    DoPref();
 		    break;
 
+		case IDM_2048:
+			Preferences.wGameType = wGame2048;
+			Preferences.Mines = 0;
+			Preferences.Height = 4;
+			Preferences.Width = 4;
+			_2048_Start();
+			goto LUpdateMenu;
+
 #ifdef NOISEY
 	    /** IDM_OPTIONS **/
 	    case IDM_SOUND:
@@ -529,8 +544,10 @@ LONG  APIENTRY MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LONG lParam)
 
 
 	case WM_KEYDOWN:
+	{
+		BOOL _2048_success = FALSE;
 		switch (wParam)
-			{
+		{
 		case VK_ESCAPE:
 			SetStatusPanic;
 			PostMessage(hwndMain, WM_SYSCOMMAND, SC_MINIMIZE, 0L);
@@ -552,10 +569,10 @@ LONG  APIENTRY MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LONG lParam)
 		case VK_F4:
 			if (FSoundSwitchable())
 				if (FSoundOn())
-					{
+				{
 					EndTunes();
 					Preferences.fSound = fsoundOff;
-					}
+				}
 				else
 					Preferences.fSound = FInitTunes();
 			break;
@@ -570,6 +587,32 @@ LONG  APIENTRY MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LONG lParam)
 				SetMenuBar(fmenuOn);
 			break;
 
+		case VK_LEFT:
+		case VK_RIGHT:
+		case VK_UP:
+		case VK_DOWN:
+			switch (wParam) {
+			case VK_DOWN:
+				_2048_success = _2048_DoLeft();
+				break;
+			case VK_UP:
+				_2048_success = _2048_DoRight();
+				break;
+			case VK_LEFT:
+				_2048_success = _2048_DoUp();
+				break;
+			case VK_RIGHT:
+				_2048_success = _2048_DoDown();
+				break;
+			}
+			if (_2048_success) {
+				_2048_AddRandom();
+			}
+			_2048_UpdateTimer();
+			_2048_UpdateScore();
+			_2048_ShowField();
+			break;
+
 #ifdef XYZZY
 		case VK_SHIFT:
 			if (iXYZZY >= cchXYZZY)
@@ -578,15 +621,16 @@ LONG  APIENTRY MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LONG lParam)
 
 		default:
 			if (iXYZZY < cchXYZZY)
-				iXYZZY = (szXYZZY[iXYZZY] == (CHAR) wParam) ? iXYZZY+1 : 0;
+				iXYZZY = (szXYZZY[iXYZZY] == (CHAR)wParam) ? iXYZZY + 1 : 0;
 			break;
 
 #else
 		default:
 			break;
 #endif
-			}	
+		}
 		break;
+	}
 
 /*  	case WM_QUERYENDSESSION:    SHOULDNT BE USED (JAP)*/
 
@@ -611,7 +655,6 @@ LONG  APIENTRY MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LONG lParam)
 		goto LBigStep;
 
 	case WM_LBUTTONDOWN:
-
 		if (fIgnoreClick)
 			{
 			fIgnoreClick = fFalse;
@@ -620,6 +663,8 @@ LONG  APIENTRY MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LONG lParam)
 
 		if (FLocalButton(lParam))
 			return 0;
+		
+		if (Preferences.wGameType == wGame2048) break;
 
 		if (!fStatusPlay)
 			break;
@@ -661,6 +706,7 @@ LBigStep:
 	case WM_RBUTTONUP:
 	case WM_MBUTTONUP:
 	case WM_LBUTTONUP:
+		if (Preferences.wGameType == wGame2048) break;
 		if (fButton1Down)
 			{
 LFixTimeOut:
@@ -674,6 +720,7 @@ LFixTimeOut:
 		break;
 
 	case WM_RBUTTONDOWN:
+		if (Preferences.wGameType == wGame2048) break;
 		if (fIgnoreClick)
 			{
 			fIgnoreClick = fFalse;
@@ -721,7 +768,13 @@ LFixTimeOut:
 		PAINTSTRUCT ps;
 		HDC hDC = BeginPaint(hWnd,&ps);
 
-		DrawScreen(hDC);
+		if (Preferences.wGameType == wGame2048) {
+			DrawScreen2048(hDC);
+			_2048_ShowField();
+		}
+		else {
+			DrawScreen(hDC);
+		}
 
 		EndPaint(hWnd, &ps);
 		}
@@ -953,7 +1006,7 @@ VOID AdjustWindow(INT fAdjust)
 #else
     		MoveWindow(hwndMain, Preferences.xWindow - dxpBorder,
     			Preferences.yWindow - dypAdjust,
-    			dxWindow+dxpBorder, dyWindow + dypAdjust, fTrue);
+    			dxWindow+dxpBorder + 14, dyWindow + dypAdjust + 14, fTrue);
 #endif
     		}
 
