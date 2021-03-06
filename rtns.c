diff --git a/rtns.c b/rtns.c
index 5f55ffd..4e150db 100644
--- a/rtns.c
+++ b/rtns.c
@@ -2,10 +2,12 @@
 /* mine.c */
 /**********/
 
-#define  _WINDOWS
+#define _WINDOWS
+#define WIN32_LEAN_AND_MEAN
 #include <windows.h>
-#include <port1632.h>
+#include "port1632.h"
 
+#include "winmine.h"
 #include "res.h"
 #include "main.h"
 #include "rtns.h"
@@ -52,7 +54,9 @@ INT rgStepY[iStepMax];
 
 INT iStepMac;
 
+/*** 2048 global variables  ***/
 
+INT _2048_score;
 
 /*** Global/External Variables ***/
 
@@ -198,11 +202,11 @@ VOID GameOver(BOOL fWinLose)
 VOID DoTimer(VOID)
 {
         if (fTimer && (cSec < 999))
-                {
-                cSec++;
-                DisplayTime();
-                PlayTune(TUNE_TICK);
-                }
+        {
+            cSec++;
+            DisplayTime();
+            PlayTune(TUNE_TICK);
+        }
 }
 
 
@@ -397,16 +401,16 @@ VOID StartGame(VOID)
         cBombStart = Preferences.Mines;
 
         do
-                {
-                do
-                        {
-                        x = Rnd(xBoxMac) + 1;
-                        y = Rnd(yBoxMac) + 1;
-                        }
-                while ( fISBOMB(x,y) );
-
-                SetBomb(x,y);
-                }
+        {
+            do
+            {
+                x = Rnd(xBoxMac) + 1;
+                y = Rnd(yBoxMac) + 1;
+            }
+            while ( fISBOMB(x,y) );
+
+            SetBomb(x,y);
+        }
         while(--cBombStart);
 
         cSec   = 0;
@@ -420,11 +424,9 @@ VOID StartGame(VOID)
         AdjustWindow(fAdjust);
 }
 
-
 #define fValidStep(x,y)  (! (fVISIT(x,y) || fGUESSBOMB(x,y)) )
 
 
-
 /****** P U S H  B O X ******/
 
 VOID PushBoxDown(INT x, INT y)
@@ -625,3 +627,190 @@ VOID UpdateBombCount(INT BombAdjust)
         DisplayBombCount();
 }
 
+/****** 2 0 4 8  G A M E *****/
+
+UCHAR _2048_FindTarget(UCHAR array[c2048Size], UCHAR x, UCHAR stop) {
+    UCHAR t;
+    // if the position is already on the first, don't evaluate
+    if (x == 0) {
+        return x;
+    }
+    for (t = x - 1;; t--) {
+        if ((array[t] & MaskData) != 0) {
+            if ((array[t] & MaskData) != (array[x] & MaskData)) {
+                // merge is not possible, take next position
+                return t + 1;
+            }
+            return t;
+        }
+        else {
+            // we should not slide further, return this one
+            if (t == stop) {
+                return t;
+            }
+        }
+    }
+    // we did not find a
+    return x;
+}
+
+BOOL _2048_SlideArray(BYTE array[c2048Size]) {
+    BOOL success = FALSE;
+    UCHAR x, t, stop = 0;
+
+    for (x = 0; x < c2048Size; x++) {
+        if ((array[x] & MaskData) != 0) {
+            t = _2048_FindTarget(array, x, stop);
+            // if target is not original position, then move or merge
+            if (t != x) {
+                // if target is zero, this is a move
+                if ((array[t] & MaskData) == 0) {
+                    array[t] = array[x];
+                }
+                else if ((array[t] & MaskData) == (array[x] & MaskData)) {
+                    // merge (increase power of two)
+                    array[t] = (array[t] & MaskFlags) + ((array[t] & MaskData) + 1);
+                    // increase score
+                    // score += (UINT)1 << array[t];
+                    _2048_score += (UINT)(array[t] & MaskData);
+                    // set stop to avoid double merge
+                    stop = t + 1;
+                }
+                array[x] &= MaskFlags;
+                success = TRUE;
+            }
+        }
+    }
+    return success;
+}
+
+VOID _2048_RotateBoard() {
+    UCHAR i, j, n = c2048Size;
+    UCHAR tmp;
+    for (i = 0; i < n / 2; i++) {
+        for (j = i; j < n - i - 1; j++) {
+            tmp = IBLK(i, j);
+            SetBlk(i, j, IBLK(j, n - i - 1));
+            SetBlk(j, n - i - 1, IBLK(n - i - 1, n - j - 1));
+            SetBlk(n - i - 1, n - j - 1, IBLK(n - j - 1, i));
+            SetBlk(n - j - 1, i, tmp);
+        }
+    }
+}
+
+BOOL _2048_DoLeft(VOID) {
+    BOOL success;
+    _2048_RotateBoard();
+    success = _2048_DoUp();
+    _2048_RotateBoard();
+    _2048_RotateBoard();
+    _2048_RotateBoard();
+    return success;
+}
+
+BOOL _2048_DoRight(VOID){
+    BOOL success;
+    _2048_RotateBoard();
+    _2048_RotateBoard();
+    _2048_RotateBoard();
+    success = _2048_DoUp();
+    _2048_RotateBoard();
+    return success;
+}
+
+BOOL _2048_DoUp(VOID){
+    BOOL success = FALSE;
+    for (char h = 0; h < c2048Size; h++) {
+        CHAR* line = (rgBlk + h * cBlkMaxWidth);
+        success |= _2048_SlideArray(line);
+    }
+    return success;
+}
+
+BOOL _2048_DoDown(VOID){
+    BOOL success;
+    _2048_RotateBoard();
+    _2048_RotateBoard();
+    success = _2048_DoUp();
+    _2048_RotateBoard();
+    _2048_RotateBoard();
+    return success;
+}
+
+VOID _2048_ClearField(VOID)
+{
+    for (int i = 0; i < c2048Size; ++i) {
+        for (int j = 0; j < c2048Size; ++j) {
+            SetBlk(i, j, (CHAR)(MaskVisit | 0));
+        }
+    }
+}
+
+VOID _2048_ShowField(VOID)
+{
+    for (int i = 0; i < c2048Size; ++i) {
+        for (int j = 0; j < c2048Size; ++j) {
+            Display2048(i, j);
+        }
+    }
+}
+
+VOID _2048_AddRandom() {
+    UCHAR x, y;
+    UCHAR r, len = 0;
+    UCHAR n, list[c2048BlkMax][2];
+
+    for (x = 0; x < c2048Size; x++) {
+        for (y = 0; y < c2048Size; y++) {
+            if (iBLK(x, y) == 0) {
+                list[len][0] = x;
+                list[len][1] = y;
+                len++;
+            }
+        }
+    }
+
+    if (len > 0) {
+        r = rand_wrapper() % len;
+        x = list[r][0];
+        y = list[r][1];
+        n = (rand_wrapper() % 10) / 9 + 1;
+        SetBlk(x, y, n);
+    }
+}
+
+VOID _2048_UpdateTimer(VOID) {
+    if (cSec == 0) {
+        PlayTune(TUNE_TICK);
+        cSec++;
+        DisplayTime();
+        fTimer = fTrue;
+    }
+}
+
+VOID _2048_UpdateScore(VOID) {
+    Display2048Score();
+}
+
+VOID _2048_Start(VOID) {
+
+    fTimer = FALSE;
+    cSec = 0;
+    _2048_score = 0;
+
+    BOOL fAdjust = (Preferences.Width != c2048Size || Preferences.Height != c2048Size)
+        ? (fResize | fDisplay) : fDisplay;
+
+    yBoxMac = rgLevelData[wGameBegin][1];
+    xBoxMac = rgLevelData[wGameBegin][2];
+
+    _2048_ClearField();
+    _2048_AddRandom();
+    _2048_AddRandom();
+
+    iButtonCur = iButtonHappy;
+    
+    SetStatusPlay;
+
+    AdjustWindow(fAdjust);
+}
\ No newline at end of file
