diff --git a/sound.c b/sound.c
index f2fedad..7a6427b 100644
--- a/sound.c
+++ b/sound.c
@@ -2,9 +2,10 @@
 /* sound.c */
 /***********/
 
-#define  _WINDOWS
+#define _WINDOWS
+#define WIN32_LEAN_AND_MEAN
 #include <windows.h>
-#include <port1632.h>
+#include "port1632.h"
 
 #include "main.h"
 #include "sound.h"
