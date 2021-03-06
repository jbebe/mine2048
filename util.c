diff --git a/util.c b/util.c
index f02ac46..d0f3f2b 100644
--- a/util.c
+++ b/util.c
@@ -2,10 +2,11 @@
 /* util.c */
 /**********/
 
-#define  _WINDOWS
+#define _WINDOWS
+#define WIN32_LEAN_AND_MEAN
 #include <windows.h>
 #include "shellapi.h"   // for ShellAbout
-#include <port1632.h>
+#include "port1632.h"
 
 #include "main.h"
 #include "res.h"
@@ -15,6 +16,7 @@
 #include "stdio.h"
 #include "stdlib.h"
 #include "dos.h"
+#include "_crt.h"
 
 extern INT dypBorder;
 extern INT dxpBorder;
@@ -33,19 +35,24 @@ extern BOOL fEGA;
 extern PREF Preferences;
 
 
-
-
 /****** R N D ******/
 
 /* Return a random number between 0 and rndMax */
 
+INT rand_wrapper(VOID) {
+#ifdef _DEBUG
+    return rand();
+#else
+    return _crt_rand();
+#endif
+}
+
 INT Rnd(INT rndMax)
 {
-        return (rand() % rndMax);
+    return (rand_wrapper() % rndMax);
 }
 
 
-
 /****** R E P O R T  E R R ******/
 
 /* Report and error and exit */
@@ -83,8 +90,10 @@ VOID LoadSz(WORD id, CHAR * sz)
 
 VOID InitConst(VOID)
 {
-        srand(LOWORD(GetCurrentTime()));
-
+#ifdef _DEBUG
+    srand(LOWORD(GetCurrentTime()));
+#endif
+        
         LoadSz(ID_GAMENAME, szClass);
         LoadSz(ID_MSG_SEC,  szTime);
         LoadSz(ID_NAME_DEFAULT, szDefaultName);
