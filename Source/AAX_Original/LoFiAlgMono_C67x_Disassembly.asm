0000: 00909a79            CMPEQ          .L1X A4, B4, A1
0004: 028005e1 ||         ZERO           .S1 A5
0008: 031090fa ||         SUB            .L2X B4, A4, B6
000c: 02184da3            SHR            .S2 B6, 2, B4
0010: 0fbc1059 ||         ADD            .L1X 0, B15, A31
0014: 921381a0 || [!A1]   ADD            .S1 -4, A4, A4
0018: 02a14069            MVKH           .S1 0x42800000, A5
001c: 07ff8452 ||         ADDK           .S2 -248, B15
0020: 020025ff            STW        .D2T2 B4, *+B15[37]
0024: 067d4074 ||         STW        .D1T1 A12, *-A31[10]
0028: 028024fd            STW        .D2T1 A5, *+B15[36]
002c: 8001d990 || [ A1]   B              .S1 0x0eec
0030: 06fd2075            STW        .D1T1 A13, *-A31[9]
0034: 050038fe ||         STW        .D2T2 B10, *+B15[56]
0038: 077d0075            STW        .D1T1 A14, *-A31[8]
003c: 058039fe ||         STW        .D2T2 B11, *+B15[57]
0040: 07fce075            STW        .D1T1 A15, *-A31[7]
0044: 06003afe ||         STW        .D2T2 B12, *+B15[58]
0048: 057c2075            STW        .D1T1 A10, *-A31[1]
004c: 06803bfe ||         STW        .D2T2 B13, *+B15[59]
0050: 05fc0275            STW        .D1T1 A11, *+A31[0]
0054: 01803cfe ||         STW        .D2T2 B3, *+B15[60]
0058: 02903264            LDW        .D1T1 *++A4[1], A5
005c: 090000f8            SUB            .L1 A0, A0, A18
0060: 0d8000f8            SUB            .L1 A0, A0, A27
0064: 0c8000f8            SUB            .L1 A0, A0, A25
0068: 09efff88            SET            .S1 A27, 31, 31, A19
006c: 0214a266            LDW        .D1T2 *+A5[5], B4
0070: 0f954264            LDW        .D1T1 *+A5[10], A31
0074: 04946266            LDW        .D1T2 *+A5[3], B9
0078: 01940264            LDW        .D1T1 *+A5[0], A3
007c: 03942266            LDW        .D1T2 *+A5[1], B7
0080: 0910005b            ADD            .L2 0, B4, B18
0084: 020026ff ||         STW        .D2T2 B4, *+B15[38]
0088: 06158264 ||         LDW        .D1T1 *+A5[12], A12
008c: 021002e7            LDW        .D2T2 *+B4[0], B4
0090: 0e950264 ||         LDW        .D1T1 *+A5[8], A29
0094: 01fc6266            LDW        .D1T2 *+A31[3], B3
0098: 0ffca266            LDW        .D1T2 *+A31[5], B31
009c: 070c0264            LDW        .D1T1 *+A3[0], A14
00a0: 04148267            LDW        .D1T2 *+A5[4], B8
00a4: 069c02e4 ||         LDW        .D2T1 *+B7[0], A13
00a8: 020027ff            STW        .D2T2 B4, *+B15[39]
00ac: 0795a264 ||         LDW        .D1T1 *+A5[13], A15
00b0: 0e8027ef            LDW        .D2T2 *+B15[39], B29
00b4: 080c48db ||         CMPLT          .L2 2, B3, B16
00b8: 05956264 ||         LDW        .D1T1 *+A5[11], A11
00bc: 022402e6            LDW        .D2T2 *+B9[0], B4
00c0: 01b80058            ADD            .L1 0, A14, A3
00c4: 0f8028fe            STW        .D2T2 B31, *+B15[40]
00c8: 050c0264            LDW        .D1T1 *+A3[0], A10
00cc: 037448da            CMPLT          .L2 2, B29, B6
00d0: 011a0f7b            AND            .L2 B16, B6, B2
00d4: 02002afe ||         STW        .D2T2 B4, *+B15[42]
00d8: 720028ee    [!B2]   LDW        .D2T2 *+B15[40], B4
00dc: 0f2002e4            LDW        .D2T1 *+B8[0], A30
00e0: 0f152266            LDW        .D1T2 *+A5[9], B30
00e4: 04f468fa            CMPLT          .L2 B3, B29, B9
00e8: 600000aa    [ B2]   MVK            .S2 1 (0x0001), B0
00ec: 70102a5b    [!B2]   CMPEQ          .L2 1, B4, B0
00f0: 0214e266 ||         LDW        .D1T2 *+A5[7], B4
00f4: 02f46afa            CMPLTU         .L2 B3, B29, B5
00f8: 02a4a0fa            SUB            .L2 B5, B9, B5
00fc: 0080005a            ADD            .L2 0, B0, B1
0100: 608000fa    [ B2]   SUB            .L2 B0, B0, B1
0104: 02002bff            STW        .D2T2 B4, *+B15[43]
0108: 7214607a || [!B2]   ADD            .L2 B3, B5, B4
010c: 0294c267            LDW        .D1T2 *+A5[6], B5
0110: 02fd8058 ||         ADD            .L1 12, A31, A5
0114: 72140276    [!B2]   STW        .D1T2 B4, *+A5[0]
0118: 457d2275    [ B1]   STW        .D1T1 A10, *+A31[9]
011c: 72002cfe || [!B2]   STW        .D2T2 B4, *+B15[44]
0120: 320028ee    [!B0]   LDW        .D2T2 *+B15[40], B4
0124: 71940266    [!B2]   LDW        .D1T2 *+A5[0], B3
0128: 42802cec    [ B1]   LDW        .D2T1 *+B15[44], A5
012c: 0f0029fe            STW        .D2T2 B30, *+B15[41]
0130: 0f182dda            XOR            .L2 1, B6, B30
0134: 3213e05a    [!B0]   ADD            .L2 -1, B4, B4
0138: 320028ff    [!B0]   STW        .D2T2 B4, *+B15[40]
013c: 720c48da || [!B2]   CMPLT          .L2 2, B3, B4
0140: 72102ddb    [!B2]   XOR            .L2 1, B4, B4
0144: 428028fd || [ B1]   STW        .D2T1 A5, *+B15[40]
0148: 008822a2 ||         RSQRSP         .S2 B2, B1
014c: 7093cffb    [!B2]   OR             .L2 B30, B4, B1
0150: 00901058 ||         ADD            .L1X 0, B4, A1
0154: 420028ee    [ B1]   LDW        .D2T2 *+B15[40], B4
0158: 094bff88            SET            .S1 A18, 31, 31, A18
015c: 0dc8005a            ADD            .L2 0, B18, B27
0160: 02802dfe            STW        .D2T2 B5, *+B15[45]
0164: 0e48005a            ADD            .L2 0, B18, B28
0168: 42902a5b    [ B1]   CMPEQ          .L2 1, B4, B5
016c: 420027ee || [ B1]   LDW        .D2T2 *+B15[39], B4
0170: 010c2264            LDW        .D1T1 *+A3[1], A2
0174: 747d2264    [!B2]   LDW        .D1T1 *+A31[9], A8
0178: 40941058    [ B1]   ADD            .L1X 0, B5, A1
017c: 520000aa    [!B1]   MVK            .S2 1 (0x0001), B4
0180: 42906afb    [ B1]   CMPLTU         .L2 B3, B4, B5
0184: 420027ee || [ B1]   LDW        .D2T2 *+B15[39], B4
0188: 50901058    [!B1]   ADD            .L1X 0, B4, A1
018c: 0004105a            ADD            .L2X 0, A1, B0
0190: 500000fa    [!B1]   SUB            .L2 B0, B0, B0
0194: 0548a3e6            LDDW       .D2T2 *+B18[5], B11:B10
0198: 421068fa    [ B1]   CMPLT          .L2 B3, B4, B4
019c: 4210a0fb    [ B1]   SUB            .L2 B5, B4, B4
01a0: 42fd91a2 || [ B1]   ADD            .S2X 12, A31, B5
01a4: 4210607a    [ B1]   ADD            .L2 B3, B4, B4
01a8: 421402f6    [ B1]   STW        .D2T2 B4, *+B5[0]
01ac: 217d2274    [ B0]   STW        .D1T1 A2, *+A31[9]
01b0: 419402e7    [ B1]   LDW        .D2T2 *+B5[0], B3
01b4: 42fd2264 || [ B1]   LDW        .D1T1 *+A31[9], A5
01b8: 0f8000fa            SUB            .L2 B0, B0, B31
01bc: 010021fc            STW        .D2T1 A2, *+B15[33]
01c0: 42002efe    [ B1]   STW        .D2T2 B4, *+B15[46]
01c4: 0b8026ee            LDW        .D2T2 *+B15[38], B23
01c8: 420c48db    [ B1]   CMPLT          .L2 2, B3, B4
01cc: 428021fc || [ B1]   STW        .D2T1 A5, *+B15[33]
01d0: 42102dda    [ B1]   XOR            .L2 1, B4, B4
01d4: 4093cffa    [ B1]   OR             .L2 B30, B4, B1
01d8: 420027ee    [ B1]   LDW        .D2T2 *+B15[39], B4
01dc: 000c4264            LDW        .D1T1 *+A3[2], A0
01e0: 0448005a            ADD            .L2 0, B18, B8
01e4: 050020fc            STW        .D2T1 A10, *+B15[32]
01e8: 042043e6            LDDW       .D2T2 *+B8[2], B9:B8
01ec: 429068fb    [ B1]   CMPLT          .L2 B3, B4, B5
01f0: 420027ee || [ B1]   LDW        .D2T2 *+B15[39], B4
01f4: 000022fc            STW        .D2T1 A0, *+B15[34]
01f8: 0d0021ee            LDW        .D2T2 *+B15[33], B26
01fc: 42fd8058    [ B1]   ADD            .L1 12, A31, A5
0200: 740020fc    [!B2]   STW        .D2T1 A8, *+B15[32]
0204: 42106afa    [ B1]   CMPLTU         .L2 B3, B4, B4
0208: 429480fb    [ B1]   SUB            .L2 B4, B5, B5
020c: 024801a2 ||         ADD            .S2 0, B18, B4
0210: 031063e7            LDDW       .D2T2 *+B4[3], B7:B6
0214: 4214607a || [ B1]   ADD            .L2 B3, B5, B4
0218: 42140276    [ B1]   STW        .D1T2 B4, *+A5[0]
021c: 037d0365            LDDW       .D1T1 *+A31[8], A7:A6
0220: 42002ffe || [ B1]   STW        .D2T2 B4, *+B15[47]
0224: 027023e6            LDDW       .D2T2 *+B28[1], B5:B4
0228: 0e0020ec            LDW        .D2T1 *+B15[32], A28
022c: 510000aa    [!B1]   MVK            .S2 1 (0x0001), B2
0230: 0d0030fe            STW        .D2T2 B26, *+B15[48]
0234: 990028ee    [!A1]   LDW        .D2T2 *+B15[40], B18
0238: 0610005b            ADD            .L2 0, B4, B12
023c: 069401a3 ||         ADD            .S2 0, B5, B13
0240: 0218d702 ||         MPYDP          .M2X B7:B6, A7:A6, B5:B4
0244: 037cc364            LDDW       .D1T1 *+A31[6], A7:A6
0248: 083395b0            MPYSPDP        .M1X A28, B13:B12, A17:A16
024c: 0b68005a            ADD            .L2 0, B26, B22
0250: 0d7fff8a            SET            .S2 B31, 31, 31, B26
0254: 047d8364            LDDW       .D1T1 *+A31[12], A9:A8
0258: 08191702            MPYDP          .M2X B9:B8, A7:A6, B17:B16
025c: 994be05a    [!A1]   ADD            .L2 -1, B18, B18
0260: 0b7d4364            LDDW       .D1T1 *+A31[10], A23:A22
0264: 990028fe    [!A1]   STW        .D2T2 B18, *+B15[40]
0268: 08121318            ADDDP          .L1X A17:A16, B5:B4, A17:A16
026c: 04c922e0            AND            .S1 A9, A18, A9
0270: 04291700            MPYDP          .M1X A9:A8, B11:B10, A9:A8
0274: 00e7ff88            SET            .S1 A25, 31, 31, A1
0278: 0d7dc364            LDDW       .D1T1 *+A31[14], A27:A26
027c: 026c83e6            LDDW       .D2T2 *+B27[4], B5:B4
0280: 095801a0            ADD            .S1 0, A22, A18
0284: 08421e58            ADDDP          .L1X A17:A16, B17:B16, A17:A16
0288: 09ceedf8            XOR            .L1 A23, A19, A19
028c: 0beafdf8            XOR            .L1X A23, B26, A23
0290: 08489702            MPYDP          .M2X B5:B4, A19:A18, B17:B16
0294: 0d0000fa            SUB            .L2 B0, B0, B26
0298: 097e0364            LDDW       .D1T1 *+A31[16], A19:A18
029c: 0febff8a            SET            .S2 B26, 31, 31, B31
02a0: 04410319            ADDDP          .L1 A9:A8, A17:A16, A9:A8
02a4: 28002eec || [ B0]   LDW        .D2T1 *+B15[46], A16
02a8: 0d8026ee            LDW        .D2T2 *+B15[38], B27
02ac: 0318d700            MPYDP          .M1X A7:A6, B7:B6, A7:A6
02b0: 0c866df8            XOR            .L1 A19, A1, A25
02b4: 053d62f4            STW        .D2T1 A10, *+B15[11]
02b8: 280028fc    [ B0]   STW        .D2T1 A16, *+B15[40]
02bc: 498028ee    [ B1]   LDW        .D2T2 *+B15[40], B19
02c0: 0a22131a            ADDDP          .L2X B17:B16, A9:A8, B21:B20
02c4: 083001a3            ADD            .S2 0, B12, B16
02c8: 08b40943 ||         ADD            .D2 B13, 0, B17
02cc: 047000a0 ||         SPDP           .S1 A28, A9:A8
02d0: 0842c5b2            MPYSPDP        .M2 B22, B17:B16, B17:B16
02d4: 0b0026ee            LDW        .D2T2 *+B15[38], B22
02d8: 414c2a5b    [ B1]   CMPEQ          .L2 1, B19, B2
02dc: 095ce3e6 ||         LDDW       .D2T2 *+B23[7], B19:B18
02e0: 000801a3            ADD            .S2 0, B2, B0
02e4: 7d0028ee || [!B2]   LDW        .D2T2 *+B15[40], B26
02e8: 0c211703            MPYDP          .M2X B9:B8, A9:A8, B25:B24
02ec: 500005e2 || [!B1]   ZERO           .S2 B0
02f0: 0e52831b            ADDDP          .L2 B21:B20, B21:B20, B29:B28
02f4: 2c000058 || [ B0]   ADD            .L1 0, A0, A24
02f8: 2c7d2275    [ B0]   STW        .D1T1 A24, *+A31[9]
02fc: 0c480058 ||         ADD            .L1 0, A18, A24
0300: 0840d319            ADDDP          .L1X A7:A6, B17:B16, A17:A16
0304: 0858c3e6 ||         LDDW       .D2T2 *+B22[6], B17:B16
0308: 0a595703            MPYDP          .M2X B11:B10, A23:A22, B21:B20
030c: 4b7d2265 || [ B1]   LDW        .D1T1 *+A31[9], A22
0310: 7d6be05a || [!B2]   ADD            .L2 -1, B26, B26
0314: 0a4b5701            MPYDP          .M1X A27:A26, B19:B18, A21:A20
0318: 036d03e5 ||         LDDW       .D2T1 *+B27[8], A7:A6
031c: 41940266 || [ B1]   LDW        .D1T2 *+A5[0], B3
0320: 0d8030ee            LDW        .D2T2 *+B15[48], B27
0324: 22802fed    [ B0]   LDW        .D2T1 *+B15[47], A5
0328: 0b8000f8 ||         SUB            .L1 A0, A0, A23
032c: 00dfff89            SET            .S1 A23, 31, 31, A1
0330: 0b70005b ||         ADD            .L2 0, B28, B22
0334: 0bf401a2 ||         ADD            .S2 0, B29, B23
0338: 0bf011a0            ADD            .S1X 0, B28, A23
033c: 0960c701            MPYDP          .M1 A7:A6, A25:A24, A19:A18
0340: 0c42c703 ||         MPYDP          .M2 B23:B22, B17:B16, B25:B24
0344: 08621318 ||         ADDDP          .L1X A17:A16, B25:B24, A17:A16
0348: 7d0028fe    [!B2]   STW        .D2T2 B26, *+B15[40]
034c: 4b0022fc    [ B1]   STW        .D2T1 A22, *+B15[34]
0350: 0bffadfa            XOR            .L2 B29, B31, B23
0354: 0b588703            MPYDP          .M2 B5:B4, B23:B22, B23:B22
0358: 04191700 ||         MPYDP          .M1X A9:A8, B7:B6, A9:A8
035c: 0b0022ec            LDW        .D2T1 *+B15[34], A22
0360: 228028fc    [ B0]   STW        .D2T1 A5, *+B15[40]
0364: 0a42931a            ADDDP          .L2X B21:B20, A17:A16, B21:B20
0368: 08b41058            ADD            .L1X 0, B13, A17
036c: 08301058            ADD            .L1X 0, B12, A16
0370: 0a629318            ADDDP          .L1X A21:A20, B25:B24, A21:A20
0374: 0c6c00a3            SPDP           .S2 B27, B25:B24
0378: 0842c5b0 ||         MPYSPDP        .M1 A22, A17:A16, A17:A16
037c: 028c6264            LDW        .D1T1 *+A3[3], A5
0380: 0d230702            MPYDP          .M2 B25:B24, B9:B8, B27:B26
0384: 0a52ce5a            ADDDP          .L2 B23:B22, B21:B20, B21:B20
0388: 4b0c48da    [ B1]   CMPLT          .L2 2, B3, B22
038c: 4b582dda    [ B1]   XOR            .L2 1, B22, B22
0390: 40dbcffa    [ B1]   OR             .L2 B30, B22, B1
0394: 08220319            ADDDP          .L1 A17:A16, A9:A8, A17:A16
0398: 04524e59 ||         ADDDP          .L1 A19:A18, A21:A20, A9:A8
039c: 4b0028ef || [ B1]   LDW        .D2T2 *+B15[40], B22
03a0: 500000aa || [!B1]   MVK            .S2 1 (0x0001), B0
03a4: 0c1b0702            MPYDP          .M2 B25:B24, B7:B6, B25:B24
03a8: 0a8000f8            SUB            .L1 A0, A0, A21
03ac: 0a0000f8            SUB            .L1 A0, A0, A20
03b0: 01d7ff88            SET            .S1 A21, 31, 31, A3
03b4: 40582a5a    [ B1]   CMPEQ          .L2 1, B22, B0
03b8: 0b528e5a            ADDDP          .L2 B21:B20, B21:B20, B23:B22
03bc: 09210318            ADDDP          .L1 A9:A8, A9:A8, A19:A18
03c0: 047011a0            ADD            .S1X 0, B28, A8
03c4: 04f43df8            XOR            .L1X A1, B29, A9
03c8: 04291700            MPYDP          .M1X A9:A8, B11:B10, A9:A8
03cc: 0af4005a            ADD            .L2 0, B29, B21
03d0: 0a70005a            ADD            .L2 0, B28, B20
03d4: 0100005a            ADD            .L2 0, B0, B2
03d8: 0d4a8703            MPYDP          .M2 B21:B20, B19:B18, B27:B26
03dc: 086a1e58 ||         ADDDP          .L1X A17:A16, B27:B26, A17:A16
03e0: 510000fa    [!B1]   SUB            .L2 B0, B0, B2
03e4: 62fd2274    [ B2]   STW        .D1T1 A5, *+A31[9]
03e8: 0a9c105b            ADD            .L2X 0, A7, B21
03ec: 03dc7df9 ||         XOR            .L1X A3, B23, A7
03f0: 01d3ff88 ||         SET            .S1 A20, 31, 31, A3
03f4: 0f42c703            MPYDP          .M2 B23:B22, B17:B16, B31:B30
03f8: 0a18105b ||         ADD            .L2X 0, A6, B20
03fc: 03581058 ||         ADD            .L1X 0, B22, A6
0400: 0310d700            MPYDP          .M1X A7:A6, B5:B4, A7:A6
0404: 098e6df8            XOR            .L1 A19, A3, A19
0408: 41fd2264    [ B1]   LDW        .D1T1 *+A31[9], A3
040c: 04410318            ADDDP          .L1 A9:A8, A17:A16, A9:A8
0410: 028023fc            STW        .D2T1 A5, *+B15[35]
0414: 00f41058            ADD            .L1X 0, B29, A1
0418: 0e4a9702            MPYDP          .M2X B21:B20, A19:A18, B29:B28
041c: 418023fc    [ B1]   STW        .D2T1 A3, *+B15[35]
0420: 018023ec            LDW        .D2T1 *+B15[35], A3
0424: 0d7b431a            ADDDP          .L2 B27:B26, B31:B30, B27:B26
0428: 0320c319            ADDDP          .L1 A7:A6, A9:A8, A7:A6
042c: 0f8005e2 ||         ZERO           .S2 B31
0430: 04b411a1            ADD            .S1X 0, B13, A9
0434: 06ffff8b ||         SET            .S2 B31, 31, 31, B13
0438: 0f4ac702 ||         MPYDP          .M2 B23:B22, B19:B18, B31:B30
043c: 04301058            ADD            .L1X 0, B12, A8
0440: 042065b0            MPYSPDP        .M1 A3, A9:A8, A9:A8
0444: 035810a2            SPDP           .S2X A22, B7:B6
0448: 0a8005e0            ZERO           .S1 A21
044c: 0e6b831b            ADDDP          .L2 B29:B28, B27:B26, B29:B28
0450: 0d20c702 ||         MPYDP          .M2 B7:B6, B9:B8, B27:B26
0454: 0318c318            ADDDP          .L1 A7:A6, A7:A6, A7:A6
0458: 0857ff88            SET            .S1 A21, 31, 31, A16
045c: 013d82f4            STW        .D2T1 A2, *+B15[12]
0460: 0423131a            ADDDP          .L2X B25:B24, A9:A8, B9:B8
0464: 0cdc01a2            ADD            .S2 0, B23, B25
0468: 0bb722e2            AND            .S2 B25, B13, B23
046c: 0e73831b            ADDDP          .L2 B29:B28, B29:B28, B29:B28
0470: 0b594702 ||         MPYDP          .M2 B11:B10, B23:B22, B23:B22
0474: 0440d700            MPYDP          .M1X A7:A6, B17:B16, A9:A8
0478: 003da2f4            STW        .D2T1 A0, *+B15[13]
047c: 02bdc2f4            STW        .D2T1 A5, *+B15[14]
0480: 0423431a            ADDDP          .L2 B27:B26, B9:B8, B9:B8
0484: 0d1811a2            ADD            .S2X 0, A6, B26
0488: 0d8005e2            ZERO           .S2 B27
048c: 0cc3bdfa            XOR            .L2X B29, A16, B25
0490: 0c70005a            ADD            .L2 0, B28, B24
0494: 0c628702            MPYDP          .M2 B21:B20, B25:B24, B25:B24
0498: 056fff8a            SET            .S2 B27, 31, 31, B10
049c: 04791319            ADDDP          .L1X A9:A8, B31:B30, A9:A8
04a0: 0b22c31a ||         ADDDP          .L2 B23:B22, B9:B8, B23:B22
04a4: 048411a2            ADD            .S2X 0, A1, B9
04a8: 045c105a            ADD            .L2X 0, A23, B8
04ac: 04410702            MPYDP          .M2 B9:B8, B17:B16, B9:B8
04b0: 0d9d5dfa            XOR            .L2X B10, A7, B27
04b4: 0948d700            MPYDP          .M1X A7:A6, B19:B18, A19:A18
04b8: 0f8005e2            ZERO           .S2 B31
04bc: 02688702            MPYDP          .M2 B5:B4, B27:B26, B5:B4
04c0: 037e0276            STW        .D1T2 B6, *+A31[16]
04c4: 04611318            ADDDP          .L1X A9:A8, B25:B24, A9:A8
04c8: 0f0030ee            LDW        .D2T2 *+B15[48], B30
04cc: 0d6a5702            MPYDP          .M2X B19:B18, A27:A26, B27:B26
04d0: 0c002dee            LDW        .D2T2 *+B15[45], B24
04d4: 00004000            NOP 3
04d8: 08210318            ADDDP          .L1 A9:A8, A9:A8, A17:A16
04dc: 0258831a            ADDDP          .L2 B5:B4, B23:B22, B5:B4
04e0: 04531700            MPYDP          .M1X A25:A24, B21:B20, A9:A8
04e4: 097fff8a            SET            .S2 B31, 31, 31, B18
04e8: 098000fa            SUB            .L2 B0, B0, B19
04ec: 0423431a            ADDDP          .L2 B27:B26, B9:B8, B9:B8
04f0: 099ff06a            MVKH           .S2 0x3fe00000, B19
04f4: 0aca3df8            XOR            .L1X A17, B18, A21
04f8: 0210831a            ADDDP          .L2 B5:B4, B5:B4, B5:B4
04fc: 0a400058            ADD            .L1 0, A16, A20
0500: 090005e2            ZERO           .S2 B18
0504: 0de002e6            LDW        .D2T2 *+B24[0], B27
0508: 0421131b            ADDDP          .L2X B9:B8, A9:A8, B9:B8
050c: 04529700 ||         MPYDP          .M1X A21:A20, B21:B20, A9:A8
0510: 00002000            NOP 2
0514: 08408702            MPYDP          .M2 B5:B4, B17:B16, B17:B16
0518: 0a0000f8            SUB            .L1 A0, A0, A20
051c: 0a8000f8            SUB            .L1 A0, A0, A21
0520: 0a9ff068            MVKH           .S1 0x3fe00000, A21
0524: 0421031b            ADDDP          .L2 B9:B8, B9:B8, B9:B8
0528: 0a5385b0 ||         MPYSPDP        .M1 A28, A21:A20, A21:A20
052c: 027f8276            STW        .D1T2 B4, *+A31[28]
0530: 0a3d7d42            ADDAW          .D2 B15, 11, B20
0534: 0d901058            ADD            .L1X 0, B4, A27
0538: 0c4ad5b0            MPYSPDP        .M1X A22, B19:B18, A25:A24
053c: 00002000            NOP 2
0540: 040026ef            LDW        .D2T2 *+B15[38], B8
0544: 0a229318 ||         ADDDP          .L1X A21:A20, B9:B8, A21:A20
0548: 00000000            NOP 1
054c: 09425318            ADDDP          .L1X A19:A18, B17:B16, A19:A18
0550: 08bf8942            ADD            .D2 B15, 28, B17
0554: 00000000            NOP 1
0558: 00a022e4            LDW        .D2T1 *+B8[1], A1
055c: 440027ee    [ B1]   LDW        .D2T2 *+B15[39], B8
0560: 0a528318            ADDDP          .L1 A21:A20, A21:A20, A21:A20
0564: 00000000            NOP 1
0568: 09490319            ADDDP          .L1 A9:A8, A19:A18, A19:A18
056c: 04430e58 ||         ADDDP          .L1 A25:A24, A17:A16, A9:A8
0570: 920030ef    [!A1]   LDW        .D2T2 *+B15[48], B4
0574: 088008c0 ||         SUB            .D1 A0, A0, A17
0578: 44a06afb    [ B1]   CMPLTU         .L2 B3, B8, B9
057c: 440027ef || [ B1]   LDW        .D2T2 *+B15[39], B8
0580: 089ff068 ||         MVKH           .S1 0x3fe00000, A17
0584: 9b5800a0    [!A1]   SPDP           .S1 A22, A23:A22
0588: 080008c0            SUB            .D1 A0, A0, A16
058c: 084065b0            MPYSPDP        .M1 A3, A17:A16, A17:A16
0590: 0a3e02f4            STW        .D2T1 A20, *+B15[16]
0594: 442068fb    [ B1]   CMPLT          .L2 B3, B8, B8
0598: 094a4319 ||         ADDDP          .L1 A19:A18, A19:A18, A19:A18
059c: 0c210e58 ||         ADDDP          .L1 A9:A8, A9:A8, A25:A24
05a0: 44a120fb    [ B1]   SUB            .L2 B9, B8, B9
05a4: 340028ee || [!B0]   LDW        .D2T2 *+B15[40], B8
05a8: 4924607a    [ B1]   ADD            .L2 B3, B9, B18
05ac: 44a4607a    [ B1]   ADD            .L2 B3, B9, B9
05b0: 448031fe    [ B1]   STW        .D2T2 B9, *+B15[49]
05b4: 048000fa            SUB            .L2 B0, B0, B9
05b8: 3423e05a    [!B0]   ADD            .L2 -1, B8, B8
05bc: 340028fe    [!B0]   STW        .D2T2 B8, *+B15[40]
05c0: 640031ee    [ B2]   LDW        .D2T2 *+B15[49], B8
05c4: 049ff06a            MVKH           .S2 0x3fe00000, B9
05c8: 04480058            ADD            .L1 0, A18, A8
05cc: 04cc0058            ADD            .L1 0, A19, A9
05d0: 08220318            ADDDP          .L1 A17:A16, A9:A8, A17:A16
05d4: 640028ff    [ B2]   STW        .D2T2 B8, *+B15[40]
05d8: 040000fa ||         SUB            .L2 B0, B0, B8
05dc: 0423c5b2            MPYSPDP        .M2 B30, B9:B8, B9:B8
05e0: 0abe22f4            STW        .D2T1 A21, *+B15[17]
05e4: 0c3e82f4            STW        .D2T1 A24, *+B15[20]
05e8: 9b3e82f4    [!A1]   STW        .D2T1 A22, *+B15[20]
05ec: 0cbea2f4            STW        .D2T1 A25, *+B15[21]
05f0: 9bbea2f4    [!A1]   STW        .D2T1 A23, *+B15[21]
05f4: 08420318            ADDDP          .L1 A17:A16, A17:A16, A17:A16
05f8: 0471031a            ADDDP          .L2 B9:B8, B29:B28, B9:B8
05fc: 497c6276    [ B1]   STW        .D1T2 B18, *+A31[3]
0600: 0c802bee            LDW        .D2T2 *+B15[43], B25
0604: 0dfe8274            STW        .D1T1 A27, *+A31[20]
0608: 0b8028ee            LDW        .D2T2 *+B15[40], B23
060c: 037f0274            STW        .D1T1 A6, *+A31[24]
0610: 02ffa277            STW        .D1T2 B5, *+A31[29]
0614: 997000a1 || [!A1]   SPDP           .S1 A28, A19:A18
0618: 0b1401a2 ||         ADD            .S2 0, B5, B22
061c: 0421031b            ADDDP          .L2 B9:B8, B9:B8, B9:B8
0620: 090c10a3 ||         SPDP           .S2X A3, B19:B18
0624: 03fe2277 ||         STW        .D1T2 B7, *+A31[17]
0628: 083ec2f4 ||         STW        .D2T1 A16, *+B15[22]
062c: 0b7ea277            STW        .D1T2 B22, *+A31[21]
0630: 993e02f4 || [!A1]   STW        .D2T1 A18, *+B15[16]
0634: 097d8277            STW        .D1T2 B18, *+A31[12]
0638: 0d000829 ||         MVK            .S1 16 (0x0010), A26
063c: 08bee2f4 ||         STW        .D2T1 A17, *+B15[23]
0640: 03ff2275            STW        .D1T1 A7, *+A31[25]
0644: 006402e7 ||         LDW        .D2T2 *+B25[0], B0
0648: 930c00a0 || [!A1]   SPDP           .S1 A3, A7:A6
064c: 0cff5e41            ADDAD          .D1 A31, A26, A25
0650: 0d0026ee ||         LDW        .D2T2 *+B15[38], B26
0654: 0bfca277            STW        .D1T2 B23, *+A31[5]
0658: 933ec2f4 || [!A1]   STW        .D2T1 A6, *+B15[22]
065c: 09fda277            STW        .D1T2 B19, *+A31[13]
0660: 921000a3 || [!A1]   SPDP           .S2 B4, B5:B4
0664: 99be22f4 || [!A1]   STW        .D2T1 A19, *+B15[17]
0668: 04640275            STW        .D1T1 A8, *+A25[0]
066c: 043e42f6 ||         STW        .D2T2 B8, *+B15[18]
0670: 04e42275            STW        .D1T1 A9, *+A25[1]
0674: 923e42f6 || [!A1]   STW        .D2T2 B4, *+B15[18]
0678: 01fc0265            LDW        .D1T1 *+A31[0], A3
067c: 04be62f6 ||         STW        .D2T2 B9, *+B15[19]
0680: 93bee2f4    [!A1]   STW        .D2T1 A7, *+B15[23]
0684: 92be62f7    [!A1]   STW        .D2T2 B5, *+B15[19]
0688: 220000fa || [ B0]   SUB            .L2 B0, B0, B4
068c: 228000fb    [ B0]   SUB            .L2 B0, B0, B5
0690: 220032ff || [ B0]   STW        .D2T2 B4, *+B15[50]
0694: 013c1058 ||         ADD            .L1X 0, B15, A2
0698: 228033ff    [ B0]   STW        .D2T2 B5, *+B15[51]
069c: 0a8bfd40 ||         ADDAW          .D1 A2, 31, A21
06a0: 02b06a65            LDW        .D1T1 *+A12[A3], A5
06a4: 0dbc1058 ||         ADD            .L1X 0, B15, A27
06a8: 0a6d1ec0            ADDAD          .D1 A27, 8, A20
06ac: 037e8365            LDDW       .D1T1 *+A31[20], A7:A6
06b0: 013c1059 ||         ADD            .L1X 0, B15, A2
06b4: 0e000929 ||         MVK            .S1 18 (0x0012), A28
06b8: 036023e7 ||         LDDW       .D2T2 *+B24[1], B7:B6
06bc: 0100022b ||         MVK            .S2 4 (0x0004), B2
06c0: 0834105a ||         ADD            .L2X 0, A13, B16
06c4: 0aea42e7            LDW        .D2T2 *+B26[18], B21
06c8: 09097ec1 ||         ADDAD          .D1 A2, 11, A18
06cc: 0d800a29 ||         MVK            .S1 20 (0x0014), A27
06d0: 0e0000fb ||         SUB            .L2 B0, B0, B28
06d4: 0ebc81a2 ||         ADD            .S2 4, B15, B29
06d8: 0d7ce267            LDW        .D1T2 *+A31[7], B26
06dc: 086043e5 ||         LDDW       .D2T1 *+B24[2], A17:A16
06e0: 0c8000ab ||         MVK            .S2 1 (0x0001), B25
06e4: 098005e1 ||         ZERO           .S1 A19
06e8: 090000fb ||         SUB            .L2 B0, B0, B18
06ec: 01780a58 ||         CMPEQ          .L1 0, A30, A2
06f0: 041400a0            SPDP           .S1 A5, A9:A8
06f4: 025036e6            LDW        .D2T2 *B20++[1], B4
06f8: 0320c338            SUBDP          .L1 A7:A6, A9:A8, A7:A6
06fc: 04503764            LDDW       .D1T1 *A20++[1], A9:A8
0700: 098000fa            SUB            .L2 B0, B0, B19
0704: 09a0b06a            MVKH           .S2 0x41600000, B19
0708: 0c100f22            ABSSP          .S2 B4, B24
070c: 026000a2            SPDP           .S2 B24, B5:B4
0710: 04225702            MPYDP          .M2X B19:B18, A9:A8, B9:B8
0714: 0310d318            ADDDP          .L1X A7:A6, B5:B4, A7:A6
0718: 220000fa    [ B0]   SUB            .L2 B0, B0, B4
071c: 221fb86a    [ B0]   MVKH           .S2 0x3f700000, B4
0720: 2290005b    [ B0]   ADD            .L2 0, B4, B5
0724: 220032ee || [ B0]   LDW        .D2T2 *+B15[50], B4
0728: 29802bee    [ B0]   LDW        .D2T2 *+B15[43], B19
072c: 000005e0            ZERO           .S1 A0
0730: 0f4fff88            SET            .S1 A19, 31, 31, A30
0734: 0c1cc038            DPTRUNC        .L1 A7:A6, A24
0738: 22189702    [ B0]   MPYDP          .M2X B5:B4, A7:A6, B5:B4
073c: 0425003a            DPTRUNC        .L2 B9:B8, B8
0740: 2b4c23e6    [ B0]   LDDW       .D2T2 *+B19[1], B23:B22
0744: 0480802a            MVK            .S2 256 (0x0100), B9
0748: 00884028            MVK            .S1 4224 (0x1080), A1
074c: 00a12f7a            AND            .L2 B9, B8, B1
0750: 0469090a            EXTU           .S2 B26, 8, 9, B8
0754: 528000f8    [!B1]   SUB            .L1 A0, A0, A5
0758: 42ffffa8    [ B1]   MVK            .S1 -1 (0xffff), A5
075c: 0296eca0            SHL            .S1 A5, 23, A5
0760: 2212c702    [ B0]   MPYDP          .M2 B23:B22, B5:B4, B5:B4
0764: 02a0bff8            OR             .L1X A5, B8, A5
0768: 2b140738    [ B0]   INTDP          .L1 A5, A23:A22
076c: a98000fa    [ A2]   SUB            .L2 B0, B0, B19
0770: 00800068            MVKH           .S1 0x00000000, A1
0774: 001ff068            MVKH           .S1 0x3fe00000, A0
0778: 010be05a            ADD            .L2 -1, B2, B2
077c: 0d14105a            ADD            .L2X 0, A5, B26
0780: 00002000            NOP 2
0784: 2b12d700    [ B0]   MPYDP          .M1X A23:A22, B5:B4, A23:A22
0788: 00002000            NOP 2
078c: 220000fa    [ B0]   SUB            .L2 B0, B0, B4
0790: 221f406a    [ B0]   MVKH           .S2 0x3e800000, B4
0794: 2290005b    [ B0]   ADD            .L2 0, B4, B5
0798: 220033ee || [ B0]   LDW        .D2T2 *+B15[51], B4
079c: 04485274            STW        .D1T1 A8, *++A18[2]
07a0: 04c82274            STW        .D1T1 A9, *+A18[1]
07a4: 0c306a76            STW        .D1T2 B24, *+A12[A3]
07a8: 018c2058            ADD            .L1 1, A3, A3
07ac: 22589702    [ B0]   MPYDP          .M2X B5:B4, A23:A22, B5:B4
07b0: 00002000            NOP 2
07b4: 0b6069a0            SHRU           .S1 A24, 3, A22
07b8: bc582da1    [!A2]   SHR            .S1 A22, 1, A24
07bc: bbd80a59 || [!A2]   CMPEQ          .L1 0, A22, A23
07c0: b4585da2 || [!A2]   SHR            .S2X A22, 2, B8
07c4: bc600a59    [!A2]   CMPEQ          .L1 0, A24, A24
07c8: b4a00a5b || [!A2]   CMPEQ          .L2 0, B8, B9
07cc: b4589da2 || [!A2]   SHR            .S2X A22, 4, B8
07d0: bb5f0079    [!A2]   ADD            .L1 A24, A23, A22
07d4: bbd86da0 || [!A2]   SHR            .S1 A22, 3, A23
07d8: b4d9307b    [!A2]   ADD            .L2X B9, A22, B9
07dc: bb5c0a58 || [!A2]   CMPEQ          .L1 0, A23, A22
07e0: b45931e3    [!A2]   ADD            .S2X B9, A22, B8
07e4: b4a00a5a || [!A2]   CMPEQ          .L2 0, B8, B9
07e8: b9a1207a    [!A2]   ADD            .L2 B9, B8, B19
07ec: 2b111319    [ B0]   ADDDP          .L1X A9:A8, B5:B4, A23:A22
07f0: 0fe66ce2 ||         SHL            .S2 B25, B19, B31
07f4: 027c073a            INTDP          .L2 B31, B5:B4
07f8: 040004fa            SUB            .L2 B0, B0, B9:B8
07fc: 0f3e7c42            ADDAW          .D2 B15, B19, B30
0800: 00002000            NOP 2
0804: 0210c702            MPYDP          .M2 B7:B6, B5:B4, B5:B4
0808: 2b480274    [ B0]   STW        .D1T1 A22, *+A18[0]
080c: 2bc82274    [ B0]   STW        .D1T1 A23, *+A18[1]
0810: 04480364            LDDW       .D1T1 *+A18[0], A9:A8
0814: 0b800058            ADD            .L1 0, A0, A23
0818: 00004000            NOP 3
081c: 00a11a62            CLR            .S2X B8, B8, B1
0820: 0b792df8            XOR            .L1 A9, A30, A22
0824: 44d80059    [ B1]   ADD            .L1 0, A22, A9
0828: 44480275 || [ B1]   STW        .D1T1 A8, *+A18[0]
082c: 00c436f6 ||         STW        .D2T2 B1, *B17++[1]
0830: 02209703            MPYDP          .M2X B5:B4, A9:A8, B5:B4
0834: 4b482275 || [ B1]   STW        .D1T1 A22, *+A18[1]
0838: 0b701058 ||         ADD            .L1X 0, B28, A22
083c: 04840266            LDW        .D1T2 *+A1[0], B9
0840: 0b042266            LDW        .D1T2 *+A1[1], B22
0844: 0f044264            LDW        .D1T1 *+A1[2], A30
0848: 0d046264            LDW        .D1T1 *+A1[3], A26
084c: 0c848264            LDW        .D1T1 *+A1[4], A25
0850: 04f402f6            STW        .D2T2 B9, *+B29[0]
0854: 0c04a264            LDW        .D1T1 *+A1[5], A24
0858: 0b7422f6            STW        .D2T2 B22, *+B29[1]
085c: 0f7442f4            STW        .D2T1 A30, *+B29[2]
0860: 0b12d318            ADDDP          .L1X A23:A22, B5:B4, A23:A22
0864: 0d7462f4            STW        .D2T1 A26, *+B29[3]
0868: 0cf482f4            STW        .D2T1 A25, *+B29[4]
086c: 0c74a2f4            STW        .D2T1 A24, *+B29[5]
0870: 0c7822e4            LDW        .D2T1 *+B30[1], A24
0874: 04250138            DPSP           .L1 A9:A8, A8
0878: 008eb8fa            CMPLT          .L2X B21, A3, B1
087c: 0b5ec038            DPTRUNC        .L1 A23:A22, A22
0880: 518005e0    [!B1]   ZERO           .S1 A3
0884: 0c4305b0            MPYSPDP        .M1 A24, A17:A16, A25:A24
0888: 00ec11a0            ADD            .S1X 0, B27, A1
088c: 0b580738            INTDP          .L1 A22, A23:A22
0890: 62b06a64    [ B2]   LDW        .D1T1 *+A12[A3], A5
0894: 04543274            STW        .D1T1 A8, *++A21[1]
0898: 00002000            NOP 2
089c: 0b5b0700            MPYDP          .M1 A25:A24, A23:A22, A23:A22
08a0: 0000e000            NOP 8
08a4: 6fffca10    [ B2]   B              .S1 0x06f0
08a8: 84dec138    [ A1]   DPSP           .L1 A23:A22, A9
08ac: 00004000            NOP 3
08b0: 84d40274    [ A1]   STW        .D1T1 A9, *+A21[0]
08b4: 08f40267            LDW        .D1T2 *+A29[0], B17
08b8: 040020ec ||         LDW        .D2T1 *+B15[32], A8
08bc: 038000fa            SUB            .L2 B0, B0, B7
08c0: 03a0286a            MVKH           .S2 0x40500000, B7
08c4: 030000fa            SUB            .L2 B0, B0, B6
08c8: 088000f8            SUB            .L1 A0, A0, A17
08cc: 02c51e00            MPYSP          .M1X A8, B17, A5
08d0: 089ff868            MVKH           .S1 0x3ff00000, A17
08d4: 0e0000fa            SUB            .L2 B0, B0, B28
08d8: 0d742264            LDW        .D1T1 *+A29[1], A26
08dc: 021410a2            SPDP           .S2X A5, B5:B4
08e0: 098021ee            LDW        .D2T2 *+B15[33], B19
08e4: 00188a62            CLR            .S2 B6, B4, B0
08e8: 038000fa            SUB            .L2 B0, B0, B7
08ec: 228024ec    [ B0]   LDW        .D2T1 *+B15[36], A5
08f0: 039ff86a            MVKH           .S2 0x3ff00000, B7
08f4: 0ccbff8a            SET            .S2 B18, 31, 31, B25
08f8: 0d8029ee            LDW        .D2T2 *+B15[41], B27
08fc: 00744264            LDW        .D1T1 *+A29[2], A0
0900: 04940178            SPTRUNC        .L1 A5, A9
0904: 0c0029ee            LDW        .D2T2 *+B15[41], B24
0908: 01746264            LDW        .D1T1 *+A29[3], A2
090c: 0aff7e40            ADDAD          .D1 A31, A27, A21
0910: 0324195a            CMPGT          .L2X 0, A9, B6
0914: 0ece2e02            MPYSP          .M2 B17, B19, B29
0918: 04200e00            MPYSP          .M1 A0, A8, A8
091c: 0e8000f8            SUB            .L1 A0, A0, A29
0920: 0418b2bb            SUBSP          .L2X A6, B5, B8
0924: 02981178 ||         SPTRUNC        .L1X B6, A5
0928: 030000fa            SUB            .L2 B0, B0, B6
092c: 00002000            NOP 2
0930: 022000a3            SPDP           .S2 B8, B5:B4
0934: 0f2cbc40 ||         ADDAW          .D1 A11, A5, A30
0938: 0facaa66            LDW        .D1T2 *+A11[A5], B31
093c: 0210c33a            SUBDP          .L2 B7:B6, B5:B4, B5:B4
0940: 02f82264            LDW        .D1T1 *+A30[1], A5
0944: 0f0000f8            SUB            .L1 A0, A0, A30
0948: 00004000            NOP 3
094c: 0f151e02            MPYSP          .M2X B8, A5, B30
0950: 0213e5b2            MPYSPDP        .M2 B31, B5:B4, B5:B4
0954: 046c03e6            LDDW       .D2T2 *+B27[0], B9:B8
0958: 02cc1e00            MPYSP          .M1X A0, B19, A5
095c: 037800a2            SPDP           .S2 B30, B7:B6
0960: 0f8022ee            LDW        .D2T2 *+B15[34], B31
0964: 0f0029ee            LDW        .D2T2 *+B15[41], B30
0968: 0a20005a            ADD            .L2 0, B8, B20
096c: 0210c31a            ADDDP          .L2 B7:B6, B5:B4, B5:B4
0970: 038005e2            ZERO           .S2 B7
0974: 03a0286a            MVKH           .S2 0x40500000, B7
0978: 030000fa            SUB            .L2 B0, B0, B6
097c: 0bfe2e02            MPYSP          .M2 B17, B31, B23
0980: 0d8005e2            ZERO           .S2 B27
0984: 0da0286a            MVKH           .S2 0x40500000, B27
0988: 0214813a            DPSP           .L2 B5:B4, B4
098c: 00004000            NOP 3
0990: 04935e01            MPYSP          .M1X A26, B4, A9
0994: 027400a2 ||         SPDP           .S2 B29, B5:B4
0998: 00000000            NOP 1
099c: 00188a62            CLR            .S2 B6, B4, B0
09a0: 00000000            NOP 1
09a4: 220024ef    [ B0]   LDW        .D2T2 *+B15[36], B4
09a8: 04212218 ||         ADDSP          .L1 A9, A8, A8
09ac: 3274005a    [!B0]   ADD            .L2 0, B29, B4
09b0: 0060c2e6            LDW        .D2T2 *+B24[6], B0
09b4: 0c0000fa            SUB            .L2 B0, B0, B24
09b8: a40020fc    [ A2]   STW        .D2T1 A8, *+B15[32]
09bc: 0290017b            SPTRUNC        .L2 B4, B5
09c0: 040020ec ||         LDW        .D2T1 *+B15[32], A8
09c4: 013ce2e7            LDW        .D2T2 *+B15[7], B2
09c8: 01fc0274 ||         STW        .D1T1 A3, *+A31[0]
09cc: 0d7ce276            STW        .D1T2 B26, *+A31[7]
09d0: 03540274            STW        .D1T1 A6, *+A21[0]
09d4: 08141959            CMPGT          .L1X 0, B5, A16
09d8: 02f3ff8b ||         SET            .S2 B28, 31, 31, B5
09dc: 03d42274 ||         STW        .D1T1 A7, *+A21[1]
09e0: 0aa41058            ADD            .L1X 0, B9, A21
09e4: 642000a0    [ B2]   SPDP           .S1 A8, A9:A8
09e8: 0b7e4364            LDDW       .D1T1 *+A31[18], A23:A22
09ec: 09400179            SPTRUNC        .L1 A16, A18
09f0: 649532e0 || [ B2]   AND            .S1X A9, B5, A9
09f4: 09c092b8            SUBSP          .L1X B16, A4, A19
09f8: 64250138    [ B2]   DPSP           .L1 A9:A8, A8
09fc: 080005e0            ZERO           .S1 A16
0a00: 04ae5c40            ADDAW          .D1 A11, A18, A9
0a04: 0a242264            LDW        .D1T1 *+A9[1], A20
0a08: 640020fd    [ B2]   STW        .D2T1 A8, *+B15[32]
0a0c: 044c00a0 ||         SPDP           .S1 A19, A9:A8
0a10: 0b0020ef            LDW        .D2T2 *+B15[32], B22
0a14: 01ae4a65 ||         LDW        .D1T1 *+A11[A18], A3
0a18: 09201058 ||         ADD            .L1X 0, B8, A18
0a1c: 03220338            SUBDP          .L1 A17:A16, A9:A8, A7:A6
0a20: 082011a0            ADD            .S1X 0, B8, A16
0a24: 04526e01            MPYSP          .M1 A19, A20, A8
0a28: 09a41058 ||         ADD            .L1X 0, B9, A19
0a2c: 0a201058            ADD            .L1X 0, B8, A20
0a30: 035800a2            SPDP           .S2 B22, B7:B6
0a34: 08a411a0            ADD            .S1X 0, B9, A17
0a38: 022010a3            SPDP           .S2X A8, B5:B4
0a3c: 0458d3b8 ||         SUBDP          .L1X B23:B22, A7:A6, A9:A8
0a40: 0c1865b0            MPYSPDP        .M1 A3, A7:A6, A25:A24
0a44: 03a41058            ADD            .L1X 0, B9, A7
0a48: 0a9f3dfa            XOR            .L2X B25, A7, B21
0a4c: 0c8000fa            SUB            .L2 B0, B0, B25
0a50: 032011a0            ADD            .S1X 0, B8, A6
0a54: 0ca0286a            MVKH           .S2 0x40500000, B25
0a58: 01990aa1            EXTU           .S1 A6, A8, A3
0a5c: 03a29aa2 ||         EXTU           .S2X B8, B20, B7
0a60: 0c131318            ADDDP          .L1X A25:A24, B5:B4, A25:A24
0a64: 020004fa            SUB            .L2 B0, B0, B5:B4
0a68: 009c7f79            AND            .L1X A3, B7, A1
0a6c: 00a09aa3 ||         EXTU           .S2X B8, B4, B1
0a70: 01fbff89 ||         SET            .S1 A30, 31, 31, A3
0a74: 037823e6 ||         LDDW       .D2T2 *+B30[1], B7:B6
0a78: 840004fa    [ A1]   SUB            .L2 B0, B0, B9:B8
0a7c: 548d3dfb    [!B1]   XOR            .L2X B9, A3, B9
0a80: 025c00a2 ||         SPDP           .S2 B23, B5:B4
0a84: 24211e78    [ B0]   SUBDP          .L1X A9:A8, B9:B8, A9:A8
0a88: 00e08a62            CLR            .S2 B24, B4, B1
0a8c: 0c670139            DPSP           .L1 A25:A24, A24
0a90: 039c11a0 ||         ADD            .S1X 0, B7, A7
0a94: 838000f9    [ A1]   SUB            .L1 A0, A0, A7
0a98: 031811a1 ||         ADD            .S1X 0, B6, A6
0a9c: 525c005a || [!B1]   ADD            .L2 0, B23, B4
0aa0: 420024ee    [ B1]   LDW        .D2T2 *+B15[36], B4
0aa4: 830008c0    [ A1]   SUB            .D1 A0, A0, A6
0aa8: 0c634e00            MPYSP          .M1 A26, A24, A24
0aac: 839ff868    [ A1]   MVKH           .S1 0x3ff00000, A7
0ab0: 2320c700    [ B0]   MPYDP          .M1 A7:A6, A9:A8, A7:A6
0ab4: 0290017a            SPTRUNC        .L2 B4, B5
0ab8: 01970218            ADDSP          .L1 A24, A5, A3
0abc: 013d02e6            LDW        .D2T2 *+B15[8], B2
0ac0: 0c8000f8            SUB            .L1 A0, A0, A25
0ac4: 0c9ff868            MVKH           .S1 0x3ff00000, A25
0ac8: a18021fd    [ A2]   STW        .D2T1 A3, *+B15[33]
0acc: 01941958 ||         CMPGT          .L1X 0, B5, A3
0ad0: 0b8021ee            LDW        .D2T2 *+B15[33], B23
0ad4: 0c77ff88            SET            .S1 A29, 31, 31, A24
0ad8: 0e8023ee            LDW        .D2T2 *+B15[35], B29
0adc: 098c923b            SUBSP          .L2X B4, A3, B19
0ae0: 018c0178 ||         SPTRUNC        .L1 A3, A3
0ae4: 2219131a    [ B0]   ADDDP          .L2X B9:B8, A7:A6, B5:B4
0ae8: 645c10a0    [ B2]   SPDP           .S1X B23, A9:A8
0aec: 0d0005e2            ZERO           .S2 B26
0af0: 64e12df9    [ B2]   XOR            .L1 A9, A24, A9
0af4: 034c10a1 ||         SPDP           .S1X B19, A7:A6
0af8: 0c0008c0 ||         SUB            .D1 A0, A0, A24
0afc: 64250139    [ B2]   DPSP           .L1 A9:A8, A8
0b00: 0dac6a64 ||         LDW        .D1T1 *+A11[A3], A27
0b04: 031b0338            SUBDP          .L1 A25:A24, A7:A6, A7:A6
0b08: 0f2c7c40            ADDAW          .D1 A11, A3, A30
0b0c: 2258931a    [ B0]   ADDDP          .L2X B5:B4, A23:A22, B5:B4
0b10: 01f82264            LDW        .D1T1 *+A30[1], A3
0b14: 640021fc    [ B2]   STW        .D2T1 A8, *+B15[33]
0b18: 0b8021ee            LDW        .D2T2 *+B15[33], B23
0b1c: 08f62e02            MPYSP          .M2 B17, B29, B17
0b20: 031b65b0            MPYSPDP        .M1 A27, A7:A6, A7:A6
0b24: 098e7e02            MPYSP          .M2X B19, A3, B19
0b28: 2c14813a    [ B0]   DPSP           .L2 B5:B4, B24
0b2c: 025c00a2            SPDP           .S2 B23, B5:B4
0b30: 0efc1e00            MPYSP          .M1X A0, B31, A29
0b34: 044c10a0            SPDP           .S1X B19, A9:A8
0b38: 2b60005a    [ B0]   ADD            .L2 0, B24, B22
0b3c: 045800a3            SPDP           .S2 B22, B9:B8
0b40: 04190e58 ||         ADDDP          .L1 A9:A8, A7:A6, A9:A8
0b44: 030004f8            SUB            .L1 A0, A0, A7:A6
0b48: 0220833a            SUBDP          .L2 B5:B4, B9:B8, B5:B4
0b4c: 028000f8            SUB            .L1 A0, A0, A5
0b50: 0b8000f8            SUB            .L1 A0, A0, A23
0b54: 0e0000fa            SUB            .L2 B0, B0, B28
0b58: 0cf41e00            MPYSP          .M1X A0, B29, A25
0b5c: 04250138            DPSP           .L1 A9:A8, A8
0b60: 0f0005e2            ZERO           .S2 B30
0b64: 01929a61            CLR            .S1X A4, A20, A3
0b68: 09d08a62 ||         CLR            .S2 B20, B4, B19
0b6c: 0f8000fa            SUB            .L2 B0, B0, B31
0b70: 00cc7f79            AND            .L1X A3, B19, A1
0b74: 00989a63 ||         CLR            .S2X B6, B4, B1
0b78: 0197ff89 ||         SET            .S1 A5, 31, 31, A3
0b7c: 04234e00 ||         MPYSP          .M1 A26, A8, A8
0b80: 8a0004f9    [ A1]   SUB            .L1 A0, A0, A21:A20
0b84: 039c11a0 ||         ADD            .S1X 0, B7, A7
0b88: 5a8eadf9    [!B1]   XOR            .L1 A21, A3, A21
0b8c: 838008c1 || [ A1]   SUB            .D1 A0, A0, A7
0b90: 031811a1 ||         ADD            .S1X 0, B6, A6
0b94: 094400a2 ||         SPDP           .S2 B17, B19:B18
0b98: 2250933a    [ B0]   SUBDP          .L2X B5:B4, A21:A20, B5:B4
0b9c: 016a4a62            CLR            .S2 B26, B18, B2
0ba0: 01f50218            ADDSP          .L1 A8, A29, A3
0ba4: 688024ee    [ B2]   LDW        .D2T2 *+B15[36], B17
0ba8: 830000f8    [ A1]   SUB            .L1 A0, A0, A6
0bac: 839ff868    [ A1]   MVKH           .S1 0x3ff00000, A7
0bb0: a18022fc    [ A2]   STW        .D2T1 A3, *+B15[34]
0bb4: 22189702    [ B0]   MPYDP          .M2X B5:B4, A7:A6, B5:B4
0bb8: 01c41178            SPTRUNC        .L1X B17, A3
0bbc: 013d22e6            LDW        .D2T2 *+B15[9], B2
0bc0: 030022ec            LDW        .D2T1 *+B15[34], A6
0bc4: 0ebd82e6            LDW        .D2T2 *+B15[12], B29
0bc8: 018c0958            CMPGT          .L1 0, A3, A3
0bcc: 0c7f9e40            ADDAD          .D1 A31, A28, A24
0bd0: 2c0020fe    [ B0]   STW        .D2T2 B24, *+B15[32]
0bd4: 631800a0    [ B2]   SPDP           .S1 A6, A7:A6
0bd8: 090e323b            SUBSP          .L2X B17, A3, B18
0bdc: 0b0c0178 ||         SPTRUNC        .L1 A3, A22
0be0: 24129318    [ B0]   ADDDP          .L1X A21:A20, B5:B4, A9:A8
0be4: 0a5fff88            SET            .S1 A23, 31, 31, A20
0be8: 63d0e2e0    [ B2]   AND            .S1 A7, A20, A7
0bec: 024800a2            SPDP           .S2 B18, B5:B4
0bf0: 631cc138    [ B2]   DPSP           .L1 A7:A6, A6
0bf4: 038005e0            ZERO           .S1 A7
0bf8: 039ff868            MVKH           .S1 0x3ff00000, A7
0bfc: 2421131a    [ B0]   ADDDP          .L2X B9:B8, A9:A8, B9:B8
0c00: 630022fd    [ B2]   STW        .D2T1 A6, *+B15[34]
0c04: 030000f9 ||         SUB            .L1 A0, A0, A6
0c08: 042edc40 ||         ADDAW          .D1 A11, A22, A8
0c0c: 0310d338            SUBDP          .L1X A7:A6, B5:B4, A7:A6
0c10: 018022ec            LDW        .D2T1 *+B15[34], A3
0c14: 04202264            LDW        .D1T1 *+A8[1], A8
0c18: 04aeca64            LDW        .D1T1 *+A11[A22], A9
0c1c: 013d42e6            LDW        .D2T2 *+B15[10], B2
0c20: 28a5013a    [ B0]   DPSP           .L2 B9:B8, B17
0c24: 020c10a2            SPDP           .S2X A3, B5:B4
0c28: 04491e00            MPYSP          .M1X A8, B18, A8
0c2c: 031925b0            MPYSPDP        .M1 A9, A7:A6, A7:A6
0c30: 2bc4005a    [ B0]   ADD            .L2 0, B17, B23
0c34: 045c00a2            SPDP           .S2 B23, B9:B8
0c38: 042000a0            SPDP           .S1 A8, A9:A8
0c3c: 0220833a            SUBDP          .L2 B5:B4, B9:B8, B5:B4
0c40: 0c8c11a2            ADD            .S2X 0, A3, B25
0c44: 288021fe    [ B0]   STW        .D2T2 B17, *+B15[33]
0c48: 03190318            ADDDP          .L1 A9:A8, A7:A6, A7:A6
0c4c: 288021ee    [ B0]   LDW        .D2T2 *+B15[33], B17
0c50: 040004f8            SUB            .L1 A0, A0, A9:A8
0c54: 0d802aee            LDW        .D2T2 *+B15[42], B27
0c58: 09508a62            CLR            .S2 B20, B4, B18
0c5c: 00911aa0            EXTU           .S1X A4, A8, A1
0c60: 09c89aa2            EXTU           .S2X B18, B4, B19
0c64: 0a1cc139            DPSP           .L1 A7:A6, A20
0c68: 039c11a0 ||         ADD            .S1X 0, B7, A7
0c6c: 00ca6f7b            AND            .L2 B19, B18, B1
0c70: 0973ff8a ||         SET            .S2 B28, 31, 31, B18
0c74: 490004f8    [ B1]   SUB            .L1 A0, A0, A19:A18
0c78: 99ca72e0    [!A1]   AND            .S1X A19, B18, A19
0c7c: 244893b8    [ B0]   SUBDP          .L1X B19:B18, A5:A4, A9:A8
0c80: 438005e0    [ B1]   ZERO           .S1 A7
0c84: 03181058            ADD            .L1X 0, B6, A6
0c88: 430000f8    [ B1]   SUB            .L1 A0, A0, A6
0c8c: 0a534e00            MPYSP          .M1 A26, A20, A20
0c90: 439ff868    [ B1]   MVKH           .S1 0x3ff00000, A7
0c94: 097bff8a            SET            .S2 B30, 31, 31, B18
0c98: 2320c700    [ B0]   MPYDP          .M1 A7:A6, A9:A8, A7:A6
0c9c: 02e68218            ADDSP          .L1 A20, A25, A5
0ca0: 0e002aee            LDW        .D2T2 *+B15[42], B28
0ca4: 0f3da2e6            LDW        .D2T2 *+B15[13], B30
0ca8: 0c8005e0            ZERO           .S1 A25
0cac: a28023fc    [ A2]   STW        .D2T1 A5, *+B15[35]
0cb0: 020023ee            LDW        .D2T2 *+B15[35], B4
0cb4: 00004000            NOP 3
0cb8: 231a4318    [ B0]   ADDDP          .L1 A19:A18, A7:A6, A7:A6
0cbc: 621000a2    [ B2]   SPDP           .S2 B4, B5:B4
0cc0: 00006000            NOP 4
0cc4: 62c8adfa    [ B2]   XOR            .L2 B5, B18, B5
0cc8: 22191e5b    [ B0]   ADDDP          .L2X B9:B8, A7:A6, B5:B4
0ccc: 6414813a || [ B2]   DPSP           .L2 B5:B4, B8
0cd0: 03181058            ADD            .L1X 0, B6, A6
0cd4: 230029ee    [ B0]   LDW        .D2T2 *+B15[41], B6
0cd8: 039c1058            ADD            .L1X 0, B7, A7
0cdc: 640023fe    [ B2]   STW        .D2T2 B8, *+B15[35]
0ce0: 028023ec            LDW        .D2T1 *+B15[35], A5
0ce4: 090004fa            SUB            .L2 B0, B0, B19:B18
0ce8: 2d14813a    [ B0]   DPSP           .L2 B5:B4, B26
0cec: 231843e6    [ B0]   LDDW       .D2T2 *+B6[2], B7:B6
0cf0: 00000000            NOP 1
0cf4: 021410a2            SPDP           .S2X A5, B5:B4
0cf8: 2ce8005a    [ B0]   ADD            .L2 0, B26, B25
0cfc: 046400a2            SPDP           .S2 B25, B9:B8
0d00: 231a25b2    [ B0]   MPYSPDP        .M2 B17, B7:B6, B7:B6
0d04: 0220833a            SUBDP          .L2 B5:B4, B9:B8, B5:B4
0d08: 2d0022fe    [ B0]   STW        .D2T2 B26, *+B15[34]
0d0c: 288029ee    [ B0]   LDW        .D2T2 *+B15[41], B17
0d10: 00006000            NOP 4
0d14: 01921a61            CLR            .S1X A4, A16, A3
0d18: 0a508a62 ||         CLR            .S2 B20, B4, B20
0d1c: 239cc13a    [ B0]   DPSP           .L2 B7:B6, B7
0d20: 008e9f7b            AND            .L2X B20, A3, B1
0d24: 01488a62 ||         CLR            .S2 B18, B4, B2
0d28: 480004f8    [ B1]   SUB            .L1 A0, A0, A17:A16
0d2c: 097fff8a            SET            .S2 B31, 31, 31, B18
0d30: 78ca3df8    [!B2]   XOR            .L1X A17, B18, A17
0d34: 22409e7a    [ B0]   SUBDP          .L2X B5:B4, A17:A16, B5:B4
0d38: 430000f8    [ B1]   SUB            .L1 A0, A0, A6
0d3c: 438000f8    [ B1]   SUB            .L1 A0, A0, A7
0d40: 439ff868    [ B1]   MVKH           .S1 0x3ff00000, A7
0d44: 290020ee    [ B0]   LDW        .D2T2 *+B15[32], B18
0d48: 03700a5a            CMPEQ          .L2 0, B28, B6
0d4c: 0e3d62e6            LDW        .D2T2 *+B15[11], B28
0d50: 22189702    [ B0]   MPYDP          .M2X B5:B4, A7:A6, B5:B4
0d54: 0abdc2e6            LDW        .D2T2 *+B15[14], B21
0d58: 2b9c005a    [ B0]   ADD            .L2 0, B7, B23
0d5c: 0998095a            CMPGT          .L2 0, B6, B19
0d60: 238021fe    [ B0]   STW        .D2T2 B7, *+B15[33]
0d64: 00008000            NOP 5
0d68: 23121319    [ B0]   ADDDP          .L1X A17:A16, B5:B4, A7:A6
0d6c: 220029ee || [ B0]   LDW        .D2T2 *+B15[41], B4
0d70: 014eee02            MPYSP          .M2 B23, B19, B2
0d74: 00004000            NOP 3
0d78: 221043e6    [ B0]   LDDW       .D2T2 *+B4[2], B5:B4
0d7c: 00000000            NOP 1
0d80: 2320d318    [ B0]   ADDDP          .L1X A7:A6, B9:B8, A7:A6
0d84: 00002000            NOP 2
0d88: 241245b3    [ B0]   MPYSPDP        .M2 B18, B5:B4, B9:B8
0d8c: 220029ee || [ B0]   LDW        .D2T2 *+B15[41], B4
0d90: 290022ee    [ B0]   LDW        .D2T2 *+B15[34], B18
0d94: 00002000            NOP 2
0d98: 241cc139    [ B0]   DPSP           .L1 A7:A6, A8
0d9c: 234443e5 || [ B0]   LDDW       .D2T1 *+B17[2], A7:A6
0da0: 08ec095a ||         CMPGT          .L2 0, B27, B17
0da4: 221043e6    [ B0]   LDDW       .D2T2 *+B4[2], B5:B4
0da8: 00000000            NOP 1
0dac: 2425013a    [ B0]   DPSP           .L2 B9:B8, B8
0db0: 04fa2e03            MPYSP          .M2 B17, B30, B9
0db4: 240023fc || [ B0]   STW        .D2T1 A8, *+B15[35]
0db8: 218023ed    [ B0]   LDW        .D2T1 *+B15[35], A3
0dbc: 0a562e02 ||         MPYSP          .M2 B17, B21, B20
0dc0: 221245b2    [ B0]   MPYSPDP        .M2 B18, B5:B4, B5:B4
0dc4: 22a00058    [ B0]   ADD            .L1 0, A8, A5
0dc8: 2b20005a    [ B0]   ADD            .L2 0, B8, B22
0dcc: 240020fe    [ B0]   STW        .D2T2 B8, *+B15[32]
0dd0: 231865b1    [ B0]   MPYSPDP        .M1 A3, A7:A6, A7:A6
0dd4: 0ff62e02 ||         MPYSP          .M2 B17, B29, B31
0dd8: 0af22e02            MPYSP          .M2 B17, B28, B21
0ddc: 034ece02            MPYSP          .M2 B22, B19, B6
0de0: 2914813a    [ B0]   DPSP           .L2 B5:B4, B18
0de4: 02fc4e1a            ADDSP          .L2 B2, B31, B5
0de8: 00000000            NOP 1
0dec: 0354c21a            ADDSP          .L2 B6, B21, B6
0df0: 219cc139    [ B0]   DPSP           .L1 A7:A6, A3
0df4: 031400a1 ||         SPDP           .S1 A5, A7:A6
0df8: 2cc8005b || [ B0]   ADD            .L2 0, B18, B25
0dfc: 290022fe || [ B0]   STW        .D2T2 B18, *+B15[34]
0e00: 08cf2e03            MPYSP          .M2 B25, B19, B17
0e04: 02c022f6 ||         STW        .D2T2 B5, *+B16[1]
0e08: 03600274            STW        .D1T1 A6, *+A24[0]
0e0c: 034002f6            STW        .D2T2 B6, *+B16[0]
0e10: 228c0058    [ B0]   ADD            .L1 0, A3, A5
0e14: 09967e02            MPYSP          .M2X B19, A5, B19
0e18: 03e02274            STW        .D1T1 A7, *+A24[1]
0e1c: 08bc2264            LDW        .D1T1 *+A15[1], A17
0e20: 04a6221a            ADDSP          .L2 B17, B9, B9
0e24: 0252621a            ADDSP          .L2 B19, B20, B4
0e28: 093c0264            LDW        .D1T1 *+A15[0], A18
0e2c: 218023fc    [ B0]   STW        .D2T1 A3, *+B15[35]
0e30: 04c042f6            STW        .D2T2 B9, *+B16[2]
0e34: 024062f6            STW        .D2T2 B4, *+B16[3]
0e38: 03340265            LDW        .D1T1 *+A13[0], A6
0e3c: 020025ee ||         LDW        .D2T2 *+B15[37], B4
0e40: 02c40264            LDW        .D1T1 *+A17[0], A5
0e44: 03b42264            LDW        .D1T1 *+A13[1], A7
0e48: 09b44264            LDW        .D1T1 *+A13[2], A19
0e4c: 08380264            LDW        .D1T1 *+A14[0], A16
0e50: 03180f21            ABSSP          .S1 A6, A6
0e54: 04c80265 ||         LDW        .D1T1 *+A18[0], A9
0e58: 0093e05a ||         ADD            .L2 -1, B4, B1
0e5c: 0094ce61            CMPGTSP        .S1 A6, A5, A1
0e60: 04382265 ||         LDW        .D1T1 *+A14[1], A8
0e64: 008025fe ||         STW        .D2T2 B1, *+B15[37]
0e68: 0db46265            LDW        .D1T1 *+A13[3], A27
0e6c: 82980059 || [ A1]   ADD            .L1 0, A6, A5
0e70: 039c0f20 ||         ABSSP          .S1 A7, A7
0e74: 0094ee61            CMPGTSP        .S1 A7, A5, A1
0e78: 0a384264 ||         LDW        .D1T1 *+A14[2], A20
0e7c: 829c0059    [ A1]   ADD            .L1 0, A7, A5
0e80: 0f4c0f21 ||         ABSSP          .S1 A19, A30
0e84: 0ab86264 ||         LDW        .D1T1 *+A14[3], A21
0e88: 08400f20            ABSSP          .S1 A16, A16
0e8c: 0097ce60            CMPGTSP        .S1 A30, A5, A1
0e90: 01260e61            CMPGTSP        .S1 A16, A9, A2
0e94: 82f80058 || [ A1]   ADD            .L1 0, A30, A5
0e98: a4c00059    [ A2]   ADD            .L1 0, A16, A9
0e9c: 086c0f21 ||         ABSSP          .S1 A27, A16
0ea0: 0d8008c0 ||         SUB            .D1 A0, A0, A27
0ea4: 04200f20            ABSSP          .S1 A8, A8
0ea8: 00960e60            CMPGTSP        .S1 A16, A5, A1
0eac: 82c00941    [ A1]   ADD            .D1 A16, 0, A5
0eb0: 0093f059 ||         ADD            .L1X -1, B4, A1
0eb4: 01250e60 ||         CMPGTSP        .S1 A8, A9, A2
0eb8: 8ffe3993    [ A1]   B              .S2 0x006c
0ebc: b4240059 || [!A2]   ADD            .L1 0, A9, A8
0ec0: 0ed00f21 ||         ABSSP          .S1 A20, A29
0ec4: 02c40274 ||         STW        .D1T1 A5, *+A17[0]
0ec8: 82903265    [ A1]   LDW        .D1T1 *++A4[1], A5
0ecc: 0123ae60 ||         CMPGTSP        .S1 A29, A8, A2
0ed0: a4740059    [ A2]   ADD            .L1 0, A29, A8
0ed4: 04d40f20 ||         ABSSP          .S1 A21, A9
0ed8: 01212e60            CMPGTSP        .S1 A9, A8, A2
0edc: a4240059    [ A2]   ADD            .L1 0, A9, A8
0ee0: 09efff88 ||         SET            .S1 A27, 31, 31, A19
0ee4: 04480275            STW        .D1T1 A8, *+A18[0]
0ee8: 090000f8 ||         SUB            .L1 A0, A0, A18
0eec: 01803cee            LDW        .D2T2 *+B15[60], B3
0ef0: 073f63e4            LDDW       .D2T1 *+B15[27], A15:A14
0ef4: 053f83e6            LDDW       .D2T2 *+B15[28], B11:B10
0ef8: 063fa3e6            LDDW       .D2T2 *+B15[29], B13:B12
0efc: 05003dec            LDW        .D2T1 *+B15[61], A10
0f00: 000c0363            B              .S2 B3
0f04: 063f43e4 ||         LDDW       .D2T1 *+B15[26], A13:A12
0f08: 05803eec            LDW        .D2T1 *+B15[62], A11
0f0c: 07807c52            ADDK           .S2 248, B15
0f10: 00004000            NOP 3
0f14: 00000000            NOP 1
0f18: 00000000            NOP 1
0f1c: 00000000            NOP 1
0f20: 03000029            MVK            .S1 0 (0x0000), A6
0f24: 0280002b ||         MVK            .S2 0 (0x0000), B5
0f28: 0fbc1059 ||         ADD            .L1X 0, B15, A31
0f2c: 05bcd4f4 ||         STW        .D2T1 A11, *B15--[6]
0f30: 03000069            MVKH           .S1 0x00000000, A6
0f34: 0280006b ||         MVKH           .S2 0x00000000, B5
0f38: 057ca075 ||         STW        .D1T1 A10, *-A31[5]
0f3c: 05bca2f6 ||         STW        .D2T2 B11, *+B15[5]
0f40: 0200002b            MVK            .S2 0 (0x0000), B4
0f44: 0094d9f9 ||         L_OP_0x4f      .L1X A6, B5, A1
0f48: 01800029 ||         MVK            .S1 0 (0x0000), A3
0f4c: 067c8075 ||         STW        .D1T1 A12, *-A31[4]
0f50: 053c82f6 ||         STW        .D2T2 B10, *+B15[4]
0f54: 0200006b            MVKH           .S2 0x00000000, B4
0f58: 02941059 ||         ADD            .L1X 0, B5, A5
0f5c: 010401a1 ||         ADD            .S1 0, A1, A2
0f60: 06fc6074 ||         STW        .D1T1 A13, *-A31[3]
0f64: 02101059            ADD            .L1X 0, B4, A4
0f68: 01800069 ||         MVKH           .S1 0x00000000, A3
0f6c: 0500002b ||         MVK            .S2 0 (0x0000), B10
0f70: 85940940 || [ A1]   ADD            .D1 A5, 0, A11
0f74: 860f0059    [ A1]   ADD            .L1 -8, A3, A12
0f78: 821068c1 || [ A1]   SUB            .D1 A4, A3, A4
0f7c: 000c99fb ||         L_OP_0x4f      .L2X B4, A3, B0
0f80: 01800029 ||         MVK            .S1 0 (0x0000), A3
0f84: 0500006a ||         MVKH           .S2 0x00000000, B10
0f88: 8210e941    [ A1]   ADD            .D1 A4, 7, A4
0f8c: 01800069 ||         MVKH           .S1 0x00000000, A3
0f90: 900000ab || [!A1]   MVK            .S2 1 (0x0001), B0
0f94: 068c1058 ||         ADD            .L1X 0, B3, A13
0f98: 90001413    [!A1]   B              .S2 0x1020
0f9c: 85106da0 || [ A1]   SHR            .S1 A4, 3, A10
0fa0: b58c105a    [!A2]   ADD            .L2X 0, A3, B11
0fa4: 00a87a78            CMPEQ          .L1X A3, B10, A1
0fa8: a08000f8    [ A2]   SUB            .L1 A0, A0, A1
0fac: 30000c90    [!B0]   B              .S1 0x1004
0fb0: 80001690    [ A1]   B              .S1 0x1054
0fb4: 23305264    [ B0]   LDW        .D1T1 *++A12[2], A6
0fb8: 2187f22a    [ B0]   MVK            .S2 4068 (0x0fe4), B3
0fbc: 00002000            NOP 2
0fc0: 0180006b            MVKH           .S2 0x00000000, B3
0fc4: 02302266 ||         LDW        .D1T2 *+A12[1], B4
0fc8: 02180214            LDBU       .D1T1 *+A6[0], A4
0fcc: 00006000            NOP 4
0fd0: 02ac8a64            LDW        .D1T1 *+A11[A4], A5
0fd4: 02182058            ADD            .L1 1, A6, A4
0fd8: 00004000            NOP 3
0fdc: 00141362            B              .S2X A5
0fe0: 00008000            NOP 5
0fe4: 00abe058            ADD            .L1 -1, A10, A1
0fe8: 8ffffd91    [ A1]   B              .S1 0x0fcc
0fec: 83305264 || [ A1]   LDW        .D1T1 *++A12[2], A6
0ff0: 8187f22a    [ A1]   MVK            .S2 4068 (0x0fe4), B3
0ff4: 82302266    [ A1]   LDW        .D1T2 *+A12[1], B4
0ff8: 8180006a    [ A1]   MVKH           .S2 0x00000000, B3
0ffc: 052be058            ADD            .L1 -1, A10, A10
1000: 82180214    [ A1]   LDBU       .D1T1 *+A6[0], A4
1004: 0500002b            MVK            .S2 0 (0x0000), B10
1008: 01800028 ||         MVK            .S1 0 (0x0000), A3
100c: 0500006b            MVKH           .S2 0x00000000, B10
1010: 01800068 ||         MVKH           .S1 0x00000000, A3
1014: 00a87a78            CMPEQ          .L1X A3, B10, A1
1018: 80000a91    [ A1]   B              .S1 0x1054
101c: 058c105a ||         ADD            .L2X 0, A3, B11
1020: 922836e6    [!A1]   LDW        .D2T2 *B10++[1], B4
1024: 91881c2a    [!A1]   MVK            .S2 4152 (0x1038), B3
1028: 00004000            NOP 3
102c: 0180006a            MVKH           .S2 0x00000000, B3
1030: 00100362            B              .S2 B4
1034: 00008000            NOP 5
1038: 002d4a7a            CMPEQ          .L2 B10, B11, B0
103c: 30000291    [!B0]   B              .S1 0x1034
1040: 322836e6 || [!B0]   LDW        .D2T2 *B10++[1], B4
1044: 31881c2a    [!B0]   MVK            .S2 4152 (0x1038), B3
1048: 3180006a    [!B0]   MVKH           .S2 0x00000000, B3
104c: 00002000            NOP 2
1050: 30100362    [!B0]   B              .S2 B4
1054: 0fbc1058            ADD            .L1X 0, B15, A31
1058: 01b4105b            ADD            .L2X 0, A13, B3
105c: 057c2264 ||         LDW        .D1T1 *+A31[1], A10
1060: 000c0363            B              .S2 B3
1064: 067c2365 ||         LDDW       .D1T1 *+A31[1], A13:A12
1068: 053c43e6 ||         LDDW       .D2T2 *+B15[2], B11:B10
106c: 05bcd2e4            LDW        .D2T1 *++B15[6], A11
1070: 00006000            NOP 4
1074: 00000000            NOP 1
1078: 00000000            NOP 1
107c: 00000000            NOP 1
