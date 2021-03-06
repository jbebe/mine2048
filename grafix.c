diff --git a/grafix.c b/grafix.c
index fdbee60..7d9cbf5 100644
--- a/grafix.c
+++ b/grafix.c
@@ -3,8 +3,9 @@
 /*************/
 
 #define _WINDOWS
+#define WIN32_LEAN_AND_MEAN
 #include <windows.h>
-#include <port1632.h>
+#include "port1632.h"
 
 #include "main.h"
 #include "res.h"
@@ -67,7 +68,7 @@ extern INT iButtonCur;
 
 extern BOOL fEGA;
 
-
+extern INT _2048_score;
 
 
 /****** F I N I T  L O C A L ******/
@@ -288,6 +289,22 @@ VOID DisplayBlk(INT x, INT y)
         ReleaseDC(hwndMain, hDC);
 }
 
+VOID Display2048(INT x, INT y)
+{
+    HDC hDC = GetDC(hwndMain);
+    BitBlt(hDC,
+        ((x + 1) << 4) + (dxGridOff+dxBlk),
+        ((y + 1) << 4) + (dyGridOff+dyBlk),
+        dxBlk,
+        dyBlk,
+        MemBlkDc[iBLK(x, y)],
+        0,
+        0,
+        SRCCOPY);
+
+    ReleaseDC(hwndMain, hDC);
+}
+
 
 /****** D R A W  G R I D ******/
 
@@ -360,11 +377,38 @@ VOID DrawBombCount(HDC hDC)
 
 VOID DisplayBombCount(VOID)
 {
-        HDC hDC = GetDC(hwndMain);
-        DrawBombCount(hDC);
-        ReleaseDC(hwndMain, hDC);
+    HDC hDC = GetDC(hwndMain);
+    DrawBombCount(hDC);
+    ReleaseDC(hwndMain, hDC);
+}
+
+VOID Draw2048Score(HDC hDC)
+{
+    INT iLed;
+    INT cBombs;
+
+    if (_2048_score < 0)
+    {
+        iLed = iLedNegative;
+        cBombs = (-_2048_score) % 100;
+    }
+    else
+    {
+        iLed = _2048_score / 100;
+        cBombs = _2048_score % 100;
+    }
+
+    DrawLed(hDC, dxLeftBomb, iLed);
+    DrawLed(hDC, dxLeftBomb + dxLed, cBombs / 10);
+    DrawLed(hDC, dxLeftBomb + dxLed + dxLed, cBombs % 10);
 }
 
+VOID Display2048Score(VOID)
+{
+    HDC hDC = GetDC(hwndMain);
+    Draw2048Score(hDC);
+    ReleaseDC(hwndMain, hDC);
+}
 
 /****** D R A W  T I M E ******/
 
@@ -461,6 +505,20 @@ VOID DrawBackground(HDC hDC)
         DrawBorder(hDC, x = ((dxWindow-dxButton)>>1)-1, dyTopLed-1, x+dxButton+1, dyTopLed+dyButton, 1, 2);
 }
 
+VOID DrawBackground2048(HDC hDC)
+{
+    INT x, y;
+
+    DrawBorder(hDC, 0, 0, x = dxWindow - 1, y = dyWindow - 1, 3, 1);
+    DrawBorder(hDC, dxGridOff + 2 * dxBlk - 2, dyGridOff + 2 * dyBlk - 2, x - (dxGridOff + 2 * dxBlk - 3), y - (dyBottomSpace - 3 + 2 * dyBlk), 3, 0);
+    x -= (dxRightSpace - 3);
+    DrawBorder(hDC, dxGridOff - 3, dyTopSpace - 3, x, dyTopLed + dyLed + (dyBottomSpace - 6), 2, 0);
+
+    DrawBorder(hDC, dxLeftBomb - 1, dyTopLed - 1, dxLeftBomb + dxLed * 3, y = dyTopLed + dyLed, 1, 0);
+    DrawBorder(hDC, x = dxWindow - (dxRightTime + 3 * dxLed + dxpBorder + 1), dyTopLed - 1, x + (dxLed * 3 + 1), y, 1, 0);
+    DrawBorder(hDC, x = ((dxWindow - dxButton) >> 1) - 1, dyTopLed - 1, x + dxButton + 1, dyTopLed + dyButton, 1, 2);
+}
+
 
 /****** D R A W  S C R E E N ******/
 
@@ -473,6 +531,14 @@ VOID DrawScreen(HDC hDC)
         DrawGrid(hDC);
 }
 
+VOID DrawScreen2048(HDC hDC)
+{
+    DrawBackground2048(hDC);
+    Draw2048Score(hDC);
+    DrawButton(hDC, iButtonCur);
+    DrawTime(hDC);
+}
+
 VOID DisplayScreen(VOID)
 {
         HDC hDC = GetDC(hwndMain);
