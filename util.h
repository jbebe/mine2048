diff --git a/util.h b/util.h
index bd49996..2199625 100644
--- a/util.h
+++ b/util.h
@@ -2,9 +2,12 @@
 /* util.h */
 /**********/
 
+#pragma once
+
 VOID InitConst(VOID);
 VOID LoadSz(WORD, CHAR *);
 VOID ReportErr(WORD);
+INT rand_wrapper(VOID);
 INT  Rnd(INT);
 
 INT  GetDlgInt(HWND, INT, INT, INT);
