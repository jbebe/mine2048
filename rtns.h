diff --git a/rtns.h b/rtns.h
index 87a2bcf..e453e4a 100644
--- a/rtns.h
+++ b/rtns.h
@@ -4,9 +4,14 @@
 
 /*** Bitmaps ***/
 
+/* 2048 constants */
+#define c2048BlkMax (4*4)
+#define c2048Size 4
 
 /* Blocks */
 
+#pragma once
+
 #define iBlkBlank    0
 #define iBlk1        1
 #define iBlk2        2
@@ -29,6 +34,8 @@
 #define NOTMaskBomb 0x7F
 
 #define cBlkMax (27*32)
+#define cBlkMaxHeight 27
+#define cBlkMaxWidth 32
 
 
 /* Leds */
@@ -58,6 +65,7 @@
 #define wGameInter  1
 #define wGameExpert 2
 #define wGameOther  3
+#define wGame2048   4
 
 
 
@@ -115,7 +123,9 @@
 
 typedef INT BLK;
 
-
+extern INT xBoxMac;
+extern INT yBoxMac;
+extern CHAR rgBlk[cBlkMax];
 
 /*** Routines ***/
 
