diff --git a/_crt.h b/_crt.h
new file mode 100644
index 0000000..8072245
--- /dev/null
+++ b/_crt.h
@@ -0,0 +1,13 @@
+#pragma once
+
+#define _WINDOWS
+#define WIN32_LEAN_AND_MEAN
+#include <windows.h>
+#include <wincrypt.h>
+
+void _crt_srand(unsigned int _Seed);
+int _crt_rand(void);
+__stdcall WinMainCRTStartup();
+
+extern HCRYPTPROV hCryptProv;
+extern LPCSTR CryptoContextContainer;
\ No newline at end of file
