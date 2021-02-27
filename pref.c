diff --git a/pref.c b/pref.c
index 767d16b..584bd85 100644
--- a/pref.c
+++ b/pref.c
@@ -3,8 +3,9 @@
 /****************/
 
 #define _WINDOWS
+#define WIN32_LEAN_AND_MEAN
 #include <windows.h>
-#include <port1632.h>
+#include "port1632.h"
 
 #include "main.h"
 #include "res.h"
