diff --git a/_crt.c b/_crt.c
new file mode 100644
index 0000000..ce4bf42
--- /dev/null
+++ b/_crt.c
@@ -0,0 +1,42 @@
+#define _WINDOWS
+#define WIN32_LEAN_AND_MEAN
+#include <windows.h>
+#include <wincrypt.h>
+
+HCRYPTPROV hCryptProv = NULL;
+LPCSTR CryptoContextContainer = "crypto_ctx_3";
+
+#ifndef _DEBUG
+
+// https://hero.handmade.network/forums/code-discussion/t/94-guide_-_how_to_avoid_c_c++_runtime_on_windows
+
+#include "winmine.h"
+
+void __stdcall WinMainCRTStartup()
+{
+    int Result = WinMain(GetModuleHandle(0), 0, 0, 0);
+    CryptReleaseContext(hCryptProv, 0);
+    ExitProcess(Result);
+}
+
+#endif
+
+void _crt_srand(unsigned int _Seed) {
+    // Ignore
+}
+
+int _crt_rand(void) {
+    static BOOL isInitialized = FALSE;
+    if (isInitialized == FALSE) {
+        if (!CryptAcquireContext(&hCryptProv, CryptoContextContainer, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
+            ExitProcess(1);
+        }
+        isInitialized = TRUE;
+    }
+
+    int result = 0;
+
+    CryptGenRandom(hCryptProv, sizeof(result), (BYTE*)&result);
+
+    return result;
+}
\ No newline at end of file
