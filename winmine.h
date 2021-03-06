diff --git a/winmine.h b/winmine.h
new file mode 100644
index 0000000..6822f16
--- /dev/null
+++ b/winmine.h
@@ -0,0 +1,12 @@
+#pragma once
+
+#define _WINDOWS
+#define WIN32_LEAN_AND_MEAN
+#include <windows.h>
+
+#define iPrefMax 3
+#define idRadMax 3
+
+extern INT rgLevelData[idRadMax][iPrefMax];
+
+INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow);
\ No newline at end of file
