diff --git a/port1632.h b/port1632.h
new file mode 100644
index 0000000..7c0d15c
--- /dev/null
+++ b/port1632.h
@@ -0,0 +1,13 @@
+#pragma once
+
+#define MMain(hInst, hPrevInst, lpCmdLine, nCmdShow) \
+   INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, \
+   INT nCmdShow) {  \
+   INT _argc;       \
+   CHAR **_argv;
+
+#define MMoveTo(hdc, x, y)               MoveToEx(hdc, x, y, NULL)
+
+#define GET_WM_ACTIVATE_STATE(wp,lp) LOWORD(wp)
+
+#define GET_WM_COMMAND_ID(wp,lp) LOWORD(wp)
\ No newline at end of file
