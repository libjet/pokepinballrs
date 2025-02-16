#include "global.h"
#include "m4a.h"
#include "main.h"
#include "titlescreen.h"

struct OptionsData {
	s16 unk0;
	u16 unk2;
	u16 unk4;
	u16 unk6;
	s16 unk8;
	s16 unkA;
	u16 unkC;
	s16 unkE;
	s16 unk10;
	u8 unk12;
	u8 unk13;
	u8 unk14;
	u8 unk15;
	u8 unk16;
	u8 unk17;
	s16 unk18;
	u8 unk1A[6];
	s16 unk20;
	s16 unk22;
	s16 unk24[2];
	s16 unk28;
	u8 unk2A;
	s8 unk2B;
	s8 unk2C;
	u8 unk2D;
	s8 unk2E;
	u8 unk2F;
	u8 unk30;
};

extern struct OptionsData gOptionsData;
extern s16 gUnknown_0200B204[][2];
extern u8 gUnknown_02031B18[];

extern const u16 gOptionsBackground_Pals[];
extern const u8 gOptionsText_Gfx[];
extern const u8 gOptionsBackground_Gfx[];
extern const u8 gOptionsText_Tilemap[];
extern const u8 gOptionsBackground_Tilemap[];

void OptionsMain(void) {
	gUnknown_08527F08[gMain.subState]();
}

void sub_51240(void) {
	ResetSomeGraphicsRelatedStuff();

	REG_DISPCNT = 0x1080;
	REG_BG0CNT = 4;
	REG_DISPCNT |= 0x100;
	REG_BG1CNT = 0x109;
	REG_DISPCNT |= 0x200;

	gMain.unk16 = REG_DISPCNT;

	DmaCopy16(3, gOptionsBackground_Pals, (void *)PLTT, 0x200);
	DmaCopy16(3, gOptionsText_Gfx, (void *)(VRAM + 0x4000), 0x1800);
	DmaCopy16(3, gOptionsBackground_Gfx, (void *)(VRAM + 0x8000), 0xC00);
	DmaCopy16(3, gOptionsText_Tilemap, gUnknown_03005C00, 0x800);
	DmaCopy16(3, gUnknown_03005C00, (void *)VRAM, 0x800);

	if (gGameBoyPlayerEnabled != 1) {
		sub_1068C(0x12, 4, 2, 1, 2);
		sub_1068C(0x12, 5, 3, 2, 2);
	}

	DmaCopy16(3, gUnknown_03005C00, (void *)VRAM, 0x800);
	DmaCopy16(3, gOptionsBackground_Tilemap, (void *)(VRAM + 0x800), 0x800);
	DmaCopy16(3, gGBAButtonIcons_Pals, (void *)(PLTT + 0x200), 0x60);
	DmaCopy16(3, gOptionsSprites_Gfx, (void *)(VRAM + 0x10000), 0x2020);
	sub_513B8();
	sub_51C9C();
	m4aMPlayAllStop();
	sub_CBC();
	sub_24C();
	sub_10C0();

	gMain.subState++;
}

void sub_513B8(void) {
	int i;
	int j;

	gOptionsData.unk0 = 0;
	gOptionsData.unk2 = 0;
	gOptionsData.unk4 = 0;
	gOptionsData.unk6 = 1;
	gOptionsData.unk8 = 0;
	gOptionsData.unkA = 0;
	gOptionsData.unkC = gMain_saveData.unk143;
	gOptionsData.unkE = 0;
	gOptionsData.unk10 = 0;
	gOptionsData.unk12 = 0;
	gOptionsData.unk13 = 0;
	gOptionsData.unk14 = 1;
	gOptionsData.unk15 = 0;
	gOptionsData.unk16 = 0;
	gOptionsData.unk17 = 1;
	gOptionsData.unk18 = 0;
	for (i = 0; i < 6; i++)
		gOptionsData.unk1A[i] = 0;
	gOptionsData.unk20 = 0;
	gOptionsData.unk22 = 0;
	for (i = 0; i < 2; i++)
		gOptionsData.unk24[i] = 10;
	gOptionsData.unk28 = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 10; j++)
			gUnknown_02031AF0[i][j] = gUnknown_08527ED6[i][j];
	}
	sub_52528();
	if (gGameBoyPlayerEnabled == 1) {
		gOptionsData.unk2A = gMain_saveData.unk141;
		gMain_saveData.unk141 = 1;
	} else {
		gOptionsData.unk2A = 0;
		gMain_saveData.unk141 = 0;
	}
	gOptionsData.unk2E = 0;
	gOptionsData.unk2B = 0;
	gOptionsData.unk2C = 0;
	gOptionsData.unk2D = 0;
	gOptionsData.unk2F = 0;
	gOptionsData.unk30 = 0;
}

void sub_514B8(void) {
	s16 r4;

	sub_51C9C();
	switch (gOptionsData.unk0) {
		case 0:
			if (gMain.newKeys & DPAD_UP) {
				if (gOptionsData.unkA != 0xD) {
					if (gOptionsData.unkA == 0xE) {
						m4aSongNumStart(0x67);
						gOptionsData.unkA = 0xD;
					} else if (gOptionsData.unkA > 0) {
						m4aSongNumStart(0x67);
						gOptionsData.unkA--;
					}
				}
			} else if (gMain.newKeys & DPAD_DOWN) {
				if (gOptionsData.unkA < 6) {
					m4aSongNumStart(0x67);
					gOptionsData.unkA++;
				} else if (gOptionsData.unkA == 0xD) {
					m4aSongNumStart(0x67);
					gOptionsData.unkA = 0xE;
				} else if (gOptionsData.unkA == 0xE) {
					m4aSongNumStart(0x67);
					gOptionsData.unkA = 2;
				}
			}
			if ((gMain.newKeys & DPAD_RIGHT) && gGameBoyPlayerEnabled == 1 && (u16)gOptionsData.unkA < 2) {
				m4aSongNumStart(0x67);
				gOptionsData.unkA += 0xD;
			}
			if ((gMain.newKeys & DPAD_LEFT) && gGameBoyPlayerEnabled == 1 && (u16)(gOptionsData.unkA - 13) < 2) {
				m4aSongNumStart(0x67);
				gOptionsData.unkA -= 0xD;
			}
			if (gMain.newKeys & A_BUTTON) {
				switch (gOptionsData.unkA) {
					case 0:
						m4aSongNumStart(0x65);
						gOptionsData.unk0 = 1;
						gOptionsData.unk18 = 0;
						gOptionsData.unk30 = 1;
						if (gOptionsData.unk2E == 1) {
							gOptionsData.unk2B = 0;
							gOptionsData.unk2D = 0;
							gOptionsData.unk2C = 0;
							gOptionsData.unk2E = 0;
						}
						break;
					case 1:
						m4aSongNumStart(0x65);
						gOptionsData.unk0 = 2;
						gOptionsData.unk18 = 0;
						gOptionsData.unk30 = 1;
						if (gOptionsData.unk2E == 1) {
							gOptionsData.unk2B = 0;
							gOptionsData.unk2D = 0;
							gOptionsData.unk2C = 0;
							gOptionsData.unk2E = 0;
						}
						break;
					case 2:
					case 3:
					case 4:
					case 5:
						m4aSongNumStart(0x65);
						gOptionsData.unkC = gOptionsData.unkA - 2;
						gMain_saveData.unk143 = gOptionsData.unkC;
						break;
					case 6:
						m4aSongNumStart(0x65);
						gOptionsData.unkC = gOptionsData.unkA - 2;
						gMain_saveData.unk143 = gOptionsData.unkC;
						gOptionsData.unkA = 7;
						gOptionsData.unk0 = 3;
						break;
					case 14:
						if (gGameBoyPlayerEnabled == 1) {
							m4aSongNumStart(0x65);
							gOptionsData.unk2D = 0;
							if (gOptionsData.unk2E == 1)
								gOptionsData.unk2E = 0;
							gOptionsData.unk2B = 0;
							gOptionsData.unk2C = 0;
							gOptionsData.unk2A = 0;
						}
						break;
					case 13:
						if (gGameBoyPlayerEnabled == 1) {
							m4aSongNumStart(0x65);
							sub_11B0(11);
							if (gOptionsData.unk2E == 0)
								gOptionsData.unk2E = 1;

							gOptionsData.unk2B = 0;
							gOptionsData.unk2C = 0;
							gOptionsData.unk2A = 1;
						}
						break;
				}
			} else if (gMain.newKeys & B_BUTTON) {
				m4aSongNumStart(0x66);
				gMain.subState++;
				sub_525CC(gMain_saveData.unk143);
			}
			if (!(gMain.frameCount & 7))
				gOptionsData.unk2 = 1 - gOptionsData.unk2;
			break;
		case 1:
			if (gMain.heldKeys & DPAD_LEFT) {
				if (gOptionsData.unk18 == 0) {
					gOptionsData.unkE--;
					gOptionsData.unk18 = 10;
				}
			} else if (gMain.heldKeys & DPAD_RIGHT) {
				if (gOptionsData.unk18 == 0) {
					gOptionsData.unkE++;
					gOptionsData.unk18 = 10;
				}
			}

			if (gMain.newKeys & DPAD_UP)
				gOptionsData.unkE += 10;
			else if (gMain.newKeys & DPAD_DOWN)
				gOptionsData.unkE -= 10;

			if (gOptionsData.unkE < 0)
				gOptionsData.unkE = 33;
			if (gOptionsData.unkE > 33)
				gOptionsData.unkE = 0;

			r4 = gOptionsData.unkE + 1;
			gOptionsData.unk12 = r4 / 100;
			r4 %= 100;
			gOptionsData.unk13 = r4 / 10;
			gOptionsData.unk14 = r4 % 10;
			if (gMain.newKeys & A_BUTTON) {
				m4aMPlayAllStop();
				m4aSongNumStart(gUnknown_08527D22[gOptionsData.unkE]);
			} else if (gMain.newKeys & B_BUTTON) {
				m4aMPlayAllStop();
				m4aSongNumStart(0x66);
				gOptionsData.unk4 = 0;
				gOptionsData.unk30 = 0;
				gOptionsData.unk0 = 0;
			}
			if (!(gMain.frameCount & 7))
				gOptionsData.unk4 = 1 - gOptionsData.unk4;
			if (gOptionsData.unk18 > 0)
				gOptionsData.unk18--;
			break;
		case 2:
			if (gMain.heldKeys & DPAD_LEFT) {
				if (gOptionsData.unk18 == 0) {
					gOptionsData.unk10--;
					gOptionsData.unk18 = 10;
				}
			} else if (gMain.heldKeys & DPAD_RIGHT) {
				if (gOptionsData.unk18 == 0) {
					gOptionsData.unk10++;
					gOptionsData.unk18 = 10;
				}
			}

			if (gMain.newKeys & DPAD_UP)
				gOptionsData.unk10 += 10;
			else if (gMain.newKeys & DPAD_DOWN)
				gOptionsData.unk10 -= 10;

			if (gOptionsData.unk10 < 0)
				gOptionsData.unk10 = 0xB7;
			if (gOptionsData.unk10 > 0xB7)
				gOptionsData.unk10 = 0;

			r4 = gOptionsData.unk10 + 1;
			gOptionsData.unk15 = r4 / 100;
			r4 %= 100;
			gOptionsData.unk16 = r4 / 10;
			gOptionsData.unk17 = r4 % 10;
			if (gMain.newKeys & A_BUTTON) {
				m4aMPlayAllStop();
				m4aSongNumStart(gUnknown_08527D66[gOptionsData.unk10]);
			} else if (gMain.newKeys & B_BUTTON) {
				m4aMPlayAllStop();
				m4aSongNumStart(0x66);
				gOptionsData.unk4 = 0;
				gOptionsData.unk30 = 0;
				gOptionsData.unk0 = 0;
			}
			if (!(gMain.frameCount & 7))
				gOptionsData.unk4 = 1 - gOptionsData.unk4;
			if (gOptionsData.unk18 > 0)
				gOptionsData.unk18--;
			break;
		case 3:
			if (gMain.newKeys & DPAD_UP) {
				if (gOptionsData.unkA > 7) {
					m4aSongNumStart(0x67);
					gOptionsData.unkA--;
				}
			} else if (gMain.newKeys & DPAD_DOWN) {
				if (gOptionsData.unkA <= 10) {
					m4aSongNumStart(0x67);
					gOptionsData.unkA++;
				}
			}
			if (gMain.newKeys & A_BUTTON) {
				m4aSongNumStart(0x65);
				gOptionsData.unk0 = 4;
				gOptionsData.unk1A[gOptionsData.unkA - 7] = 1;
			} else if (gMain.newKeys & B_BUTTON) {
				m4aSongNumStart(0x66);
				gOptionsData.unkA = 6;
				gOptionsData.unk0 = 0;
			}
			if (!(gMain.frameCount & 7))
				gOptionsData.unk2 = 1 - gOptionsData.unk2;
			break;
		case 4:
			gOptionsData.unk8++;
			if (gOptionsData.unk8 > 24) {
				gOptionsData.unk8 = 0;
				gOptionsData.unk6 = 1 - gOptionsData.unk6;
			}
			if (gMain.newKeys & (KEYS_MASK ^ START_BUTTON)) {
				s16 i;

				m4aSongNumStart(0x65);
				gOptionsData.unk20 = 10;
				gOptionsData.unk22 = 0;
				for (i = 0; i < 2; i++)
					gOptionsData.unk24[i] = 10;
				gOptionsData.unk28 = 0;
			}
			if (gOptionsData.unk20 > 0) {
				sub_524BC();
				gOptionsData.unk20--;
				if (gOptionsData.unk20 == 0) {
					gUnknown_02031AF0[4][(gOptionsData.unkA - 7) * 2 + 0] = gOptionsData.unk24[0];
					gUnknown_02031AF0[4][(gOptionsData.unkA - 7) * 2 + 1] = gOptionsData.unk24[1];
					gMain_saveData.unk144[(gOptionsData.unkA - 7)][0] = gUnknown_086BB910[gOptionsData.unk24[0]][0];
					gMain_saveData.unk144[(gOptionsData.unkA - 7)][1] = gUnknown_086BB910[gOptionsData.unk24[1]][0];
					gOptionsData.unk0 = 3;
					gOptionsData.unk1A[gOptionsData.unkA - 7] = 0;
					gOptionsData.unk8 = 0;
					gOptionsData.unk6 = 1;
				}
			}
			break;
	}
	if (gOptionsData.unk2E == 1) {
		if (++gOptionsData.unk2B > gUnknown_086BB9B4[gOptionsData.unk2C].unk2) {
			gOptionsData.unk2B = 0;
			gOptionsData.unk2C++;
			if (gOptionsData.unk2C > 12) {
				gOptionsData.unk2C = 0;
				gOptionsData.unk2D = 0;
				gOptionsData.unk2E = 0;
			}
			gOptionsData.unk2D = gUnknown_086BB9B4[gOptionsData.unk2C].unk0;
		}
	} else {
		gOptionsData.unk2B++;
		if (gOptionsData.unk2B > 18) {
			gOptionsData.unk2B = 0;
			gOptionsData.unk2D = 1 - gOptionsData.unk2D;
		}
	}
	sub_11FC();
}

void sub_51C3C(void) {
	sub_111C();
	if (sub_1170() != 0) {
		sub_1198();
		gMain.subState++;
	}
}

void sub_51C60(void) {
	gMain_saveData.unk141 = gOptionsData.unk2A;
	SaveFile_WriteToSram();
	sub_2B4();
	m4aMPlayAllStop();
	sub_D10();
	gAutoDisplayTitlescreenMenu = 1;
	SetMainGameState(STATE_TITLE);
}

NAKED
void sub_51C9C(void) {
	asm_unified("\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, sl\n\
	mov r6, sb\n\
	mov r5, r8\n\
	push {r5, r6, r7}\n\
	sub sp, #0x8c\n\
	ldr r0, _08051D38 @ =gUnknown_0200B3B8\n\
	mov r8, r0\n\
	ldr r2, _08051D3C @ =gOptionsData\n\
	movs r3, #4\n\
	ldrsh r1, [r2, r3]\n\
	movs r0, #0xe6\n\
	lsls r0, r0, #4\n\
	muls r1, r0, r1\n\
	movs r0, #0xa1\n\
	lsls r0, r0, #3\n\
	add r0, r8\n\
	adds r1, r1, r0\n\
	str r1, [sp, #0x60]\n\
	add r4, sp, #0xc\n\
	mov sl, r4\n\
	mov r6, sp\n\
	adds r6, #0x18\n\
	str r6, [sp, #0x6c]\n\
	mov r7, sp\n\
	adds r7, #0x1c\n\
	str r7, [sp, #0x74]\n\
	mov r0, sp\n\
	adds r0, #0x20\n\
	str r0, [sp, #0x7c]\n\
	movs r0, #0xb8\n\
	lsls r0, r0, #2\n\
	add r0, r8\n\
	mov r3, sl\n\
	mov r1, r8\n\
	adds r1, #0xb8\n\
	mov r2, sp\n\
	movs r4, #2\n\
	mov ip, r4\n\
_08051CEA:\n\
	stm r2!, {r1}\n\
	stm r3!, {r0}\n\
	adds r0, #0xb8\n\
	adds r1, #0xb8\n\
	movs r6, #1\n\
	rsbs r6, r6, #0\n\
	add ip, r6\n\
	mov r7, ip\n\
	cmp r7, #0\n\
	bge _08051CEA\n\
	movs r0, #0\n\
	mov ip, r0\n\
	movs r1, #8\n\
	add r1, r8\n\
	mov sb, r1\n\
	ldr r2, _08051D40 @ =gUnknown_0200B978\n\
	adds r2, #8\n\
	str r2, [sp, #0x70]\n\
	ldr r0, _08051D44 @ =gUnknown_0200BAE8\n\
	adds r4, r0, #0\n\
	adds r4, #0xb8\n\
	adds r5, r0, #0\n\
	movs r3, #0\n\
	ldr r1, [sp, #0x6c]\n\
	adds r2, r5, #0\n\
	subs r2, #0xb8\n\
_08051D1E:\n\
	ldr r0, _08051D48 @ =gUnknown_0200293A\n\
	add r0, ip\n\
	ldrb r0, [r0]\n\
	cmp r0, #1\n\
	bne _08051D50\n\
	ldr r6, _08051D3C @ =gOptionsData\n\
	movs r7, #6\n\
	ldrsh r0, [r6, r7]\n\
	cmp r0, #1\n\
	bne _08051D50\n\
	ldr r0, _08051D4C @ =gUnknown_0200C7D8\n\
	str r0, [r1]\n\
	b _08051D52\n\
	.align 2, 0\n\
_08051D38: .4byte gUnknown_0200B3B8\n\
_08051D3C: .4byte gOptionsData\n\
_08051D40: .4byte gUnknown_0200B978\n\
_08051D44: .4byte gUnknown_0200BAE8\n\
_08051D48: .4byte gUnknown_0200293A\n\
_08051D4C: .4byte gUnknown_0200C7D8\n\
_08051D50:\n\
	str r2, [r1]\n\
_08051D52:\n\
	ldr r6, [sp, #0x74]\n\
	adds r0, r6, r3\n\
	str r5, [r0]\n\
	ldr r7, [sp, #0x7c]\n\
	adds r0, r7, r3\n\
	str r4, [r0]\n\
	movs r0, #0x8a\n\
	lsls r0, r0, #2\n\
	adds r4, r4, r0\n\
	adds r5, r5, r0\n\
	adds r2, r2, r0\n\
	adds r3, #0xc\n\
	adds r1, #0xc\n\
	movs r6, #1\n\
	add ip, r6\n\
	mov r7, ip\n\
	cmp r7, #5\n\
	ble _08051D1E\n\
	ldr r0, _08051F64 @ =gUnknown_0200C890\n\
	str r0, [sp, #0x64]\n\
	movs r0, #1\n\
	mov r1, r8\n\
	strh r0, [r1]\n\
	movs r2, #1\n\
	mov r1, sp\n\
	movs r3, #2\n\
	mov ip, r3\n\
_08051D88:\n\
	ldm r1!, {r0}\n\
	strh r2, [r0]\n\
	movs r4, #1\n\
	rsbs r4, r4, #0\n\
	add ip, r4\n\
	mov r6, ip\n\
	cmp r6, #0\n\
	bge _08051D88\n\
	ldr r7, [sp, #0x64]\n\
	adds r7, #8\n\
	str r7, [sp, #0x78]\n\
	movs r2, #1\n\
	mov r1, sl\n\
	movs r0, #2\n\
	mov ip, r0\n\
_08051DA6:\n\
	ldm r1!, {r0}\n\
	strh r2, [r0]\n\
	movs r3, #1\n\
	rsbs r3, r3, #0\n\
	add ip, r3\n\
	mov r4, ip\n\
	cmp r4, #0\n\
	bge _08051DA6\n\
	movs r0, #1\n\
	ldr r6, [sp, #0x60]\n\
	strh r0, [r6]\n\
	ldr r7, _08051F68 @ =gUnknown_0200B978\n\
	strh r0, [r7]\n\
	movs r0, #0\n\
	mov ip, r0\n\
	ldr r6, [sp, #0x6c]\n\
	movs r3, #1\n\
	movs r2, #0\n\
_08051DCA:\n\
	adds r1, r2, r6\n\
	movs r5, #2\n\
_08051DCE:\n\
	ldm r1!, {r0}\n\
	strh r3, [r0]\n\
	subs r5, #1\n\
	cmp r5, #0\n\
	bge _08051DCE\n\
	adds r2, #0xc\n\
	movs r1, #1\n\
	add ip, r1\n\
	mov r4, ip\n\
	cmp r4, #5\n\
	ble _08051DCA\n\
	movs r0, #1\n\
	ldr r6, [sp, #0x64]\n\
	strh r0, [r6]\n\
	ldr r7, _08051F6C @ =gUnknown_0200C948\n\
	strh r0, [r7]\n\
	ldr r5, _08051F70 @ =gOptionsData\n\
	adds r0, r5, #0\n\
	adds r0, #0x30\n\
	ldrb r0, [r0]\n\
	lsls r0, r0, #0x18\n\
	asrs r0, r0, #0x18\n\
	ldr r1, _08051F74 @ =gUnknown_0200CA00\n\
	strh r0, [r1]\n\
	ldr r0, _08051F78 @ =gUnknown_086BB9EC\n\
	movs r1, #0x20\n\
	ldr r2, _08051F7C @ =gUnknown_0200B3B8\n\
	bl LoadSpriteSets\n\
	ldr r2, _08051F80 @ =gUnknown_086BB968\n\
	movs r3, #0xa\n\
	ldrsh r1, [r5, r3]\n\
	lsls r1, r1, #2\n\
	adds r1, r1, r2\n\
	ldrh r0, [r5, #2]\n\
	ldrh r1, [r1]\n\
	adds r0, r0, r1\n\
	mov r4, r8\n\
	strh r0, [r4, #2]\n\
	movs r6, #0xa\n\
	ldrsh r0, [r5, r6]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r2\n\
	ldrh r0, [r0, #2]\n\
	strh r0, [r4, #4]\n\
	mov r7, sb\n\
	ldr r4, _08051F84 @ =gOamBuffer\n\
	mov r0, r8\n\
	ldrh r2, [r0, #8]\n\
	lsls r2, r2, #3\n\
	adds r2, r2, r4\n\
	movs r3, #2\n\
	ldrsh r1, [r7, r3]\n\
	movs r6, #2\n\
	ldrsh r0, [r0, r6]\n\
	adds r1, r1, r0\n\
	ldr r3, _08051F88 @ =0x000001FF\n\
	adds r0, r3, #0\n\
	ands r1, r0\n\
	ldrh r3, [r2, #2]\n\
	ldr r6, _08051F8C @ =0xFFFFFE00\n\
	adds r0, r6, #0\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strh r0, [r2, #2]\n\
	mov r0, r8\n\
	ldrh r1, [r0, #8]\n\
	lsls r1, r1, #3\n\
	adds r1, r1, r4\n\
	ldrb r0, [r0, #4]\n\
	ldrb r7, [r7, #4]\n\
	adds r0, r0, r7\n\
	strb r0, [r1]\n\
	movs r1, #0\n\
	mov ip, r1\n\
	mov r8, r4\n\
	mov r5, sp\n\
	movs r2, #0x48\n\
	mov sb, r2\n\
_08051E6C:\n\
	ldr r0, [r5]\n\
	mov r3, sb\n\
	strh r3, [r0, #2]\n\
	ldr r1, [r5]\n\
	movs r0, #0x20\n\
	strh r0, [r1, #4]\n\
	ldr r4, [r5]\n\
	adds r7, r4, #0\n\
	adds r7, #8\n\
	ldrh r2, [r4, #8]\n\
	lsls r2, r2, #3\n\
	add r2, r8\n\
	ldr r0, _08051F90 @ =gUnknown_02002932\n\
	add r0, ip\n\
	ldrb r1, [r0]\n\
	adds r1, #0x16\n\
	ldrh r3, [r2, #4]\n\
	ldr r0, _08051F94 @ =0xFFFFFC00\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strh r0, [r2, #4]\n\
	ldrh r3, [r4, #8]\n\
	lsls r3, r3, #3\n\
	add r3, r8\n\
	movs r0, #2\n\
	ldrsh r1, [r7, r0]\n\
	ldr r0, [r5]\n\
	movs r2, #2\n\
	ldrsh r0, [r0, r2]\n\
	adds r1, r1, r0\n\
	ldr r2, _08051F88 @ =0x000001FF\n\
	adds r0, r2, #0\n\
	ands r1, r0\n\
	ldrh r2, [r3, #2]\n\
	adds r0, r6, #0\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strh r0, [r3, #2]\n\
	ldrh r1, [r4, #8]\n\
	lsls r1, r1, #3\n\
	add r1, r8\n\
	ldm r5!, {r0}\n\
	ldrb r0, [r0, #4]\n\
	ldrb r7, [r7, #4]\n\
	adds r0, r0, r7\n\
	strb r0, [r1]\n\
	movs r3, #7\n\
	add sb, r3\n\
	movs r4, #1\n\
	add ip, r4\n\
	mov r7, ip\n\
	cmp r7, #2\n\
	ble _08051E6C\n\
	movs r0, #0\n\
	mov ip, r0\n\
	ldr r1, _08051F84 @ =gOamBuffer\n\
	mov r8, r1\n\
	movs r6, #0x48\n\
	mov r5, sl\n\
_08051EE2:\n\
	ldr r0, [r5]\n\
	strh r6, [r0, #2]\n\
	ldr r0, [r5]\n\
	movs r2, #0x2c\n\
	mov sb, r2\n\
	mov r3, sb\n\
	strh r3, [r0, #4]\n\
	ldr r4, [r5]\n\
	adds r7, r4, #0\n\
	adds r7, #8\n\
	ldrh r2, [r4, #8]\n\
	lsls r2, r2, #3\n\
	add r2, r8\n\
	ldr r0, _08051F98 @ =gUnknown_02002935\n\
	add r0, ip\n\
	ldrb r1, [r0]\n\
	adds r1, #0x16\n\
	ldrh r3, [r2, #4]\n\
	ldr r0, _08051F94 @ =0xFFFFFC00\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strh r0, [r2, #4]\n\
	ldrh r3, [r4, #8]\n\
	lsls r3, r3, #3\n\
	add r3, r8\n\
	movs r0, #2\n\
	ldrsh r1, [r7, r0]\n\
	ldr r0, [r5]\n\
	movs r2, #2\n\
	ldrsh r0, [r0, r2]\n\
	adds r1, r1, r0\n\
	ldr r2, _08051F88 @ =0x000001FF\n\
	adds r0, r2, #0\n\
	ands r1, r0\n\
	ldrh r2, [r3, #2]\n\
	ldr r0, _08051F8C @ =0xFFFFFE00\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strh r0, [r3, #2]\n\
	ldrh r1, [r4, #8]\n\
	lsls r1, r1, #3\n\
	add r1, r8\n\
	ldm r5!, {r0}\n\
	ldrb r0, [r0, #4]\n\
	ldrb r7, [r7, #4]\n\
	adds r0, r0, r7\n\
	strb r0, [r1]\n\
	adds r6, #7\n\
	movs r3, #1\n\
	add ip, r3\n\
	mov r4, ip\n\
	cmp r4, #2\n\
	ble _08051EE2\n\
	movs r0, #0x48\n\
	ldr r6, [sp, #0x60]\n\
	strh r0, [r6, #2]\n\
	ldr r7, _08051F70 @ =gOptionsData\n\
	movs r1, #0xa\n\
	ldrsh r0, [r7, r1]\n\
	cmp r0, #0\n\
	bne _08051F9C\n\
	movs r0, #0x20\n\
	strh r0, [r6, #4]\n\
	b _08051FA6\n\
	.align 2, 0\n\
_08051F64: .4byte gUnknown_0200C890\n\
_08051F68: .4byte gUnknown_0200B978\n\
_08051F6C: .4byte gUnknown_0200C948\n\
_08051F70: .4byte gOptionsData\n\
_08051F74: .4byte gUnknown_0200CA00\n\
_08051F78: .4byte gUnknown_086BB9EC\n\
_08051F7C: .4byte gUnknown_0200B3B8\n\
_08051F80: .4byte gUnknown_086BB968\n\
_08051F84: .4byte gOamBuffer\n\
_08051F88: .4byte 0x000001FF\n\
_08051F8C: .4byte 0xFFFFFE00\n\
_08051F90: .4byte gUnknown_02002932\n\
_08051F94: .4byte 0xFFFFFC00\n\
_08051F98: .4byte gUnknown_02002935\n\
_08051F9C:\n\
	cmp r0, #1\n\
	bne _08051FA6\n\
	mov r3, sb\n\
	ldr r2, [sp, #0x60]\n\
	strh r3, [r2, #4]\n\
_08051FA6:\n\
	ldr r5, _080520D0 @ =gOamBuffer\n\
	ldr r7, _080520D4 @ =0xFFFFFE00\n\
	ldr r4, [sp, #0x60]\n\
	adds r4, #8\n\
	movs r6, #1\n\
	mov ip, r6\n\
_08051FB2:\n\
	ldrh r3, [r4]\n\
	lsls r3, r3, #3\n\
	adds r3, r3, r5\n\
	movs r0, #2\n\
	ldrsh r1, [r4, r0]\n\
	ldr r2, [sp, #0x60]\n\
	movs r6, #2\n\
	ldrsh r0, [r2, r6]\n\
	adds r1, r1, r0\n\
	ldr r0, _080520D8 @ =0x000001FF\n\
	adds r6, r0, #0\n\
	ands r1, r6\n\
	ldrh r2, [r3, #2]\n\
	adds r0, r7, #0\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strh r0, [r3, #2]\n\
	ldrh r1, [r4]\n\
	lsls r1, r1, #3\n\
	adds r1, r1, r5\n\
	ldr r2, [sp, #0x60]\n\
	ldrb r0, [r2, #4]\n\
	ldrb r3, [r4, #4]\n\
	adds r0, r0, r3\n\
	strb r0, [r1]\n\
	adds r4, #8\n\
	movs r0, #1\n\
	rsbs r0, r0, #0\n\
	add ip, r0\n\
	mov r1, ip\n\
	cmp r1, #0\n\
	bge _08051FB2\n\
	movs r0, #0x48\n\
	ldr r2, _080520DC @ =gUnknown_0200B978\n\
	strh r0, [r2, #2]\n\
	ldr r3, _080520E0 @ =gOptionsData\n\
	movs r4, #0xc\n\
	ldrsh r0, [r3, r4]\n\
	lsls r0, r0, #1\n\
	ldr r7, _080520E4 @ =gUnknown_086BB9A8\n\
	adds r0, r0, r7\n\
	ldrh r0, [r0]\n\
	strh r0, [r2, #4]\n\
	ldr r7, [sp, #0x70]\n\
	ldrh r2, [r2, #8]\n\
	lsls r2, r2, #3\n\
	ldr r0, _080520D0 @ =gOamBuffer\n\
	adds r2, r2, r0\n\
	movs r3, #2\n\
	ldrsh r1, [r7, r3]\n\
	adds r1, #0x48\n\
	ands r1, r6\n\
	ldrh r3, [r2, #2]\n\
	ldr r0, _080520D4 @ =0xFFFFFE00\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strh r0, [r2, #2]\n\
	ldr r4, _080520DC @ =gUnknown_0200B978\n\
	ldrh r1, [r4, #8]\n\
	lsls r1, r1, #3\n\
	ldr r6, _080520D0 @ =gOamBuffer\n\
	adds r1, r1, r6\n\
	ldrb r0, [r4, #4]\n\
	ldrb r7, [r7, #4]\n\
	adds r0, r0, r7\n\
	strb r0, [r1]\n\
	movs r7, #0\n\
	mov ip, r7\n\
	ldr r0, _080520E0 @ =gOptionsData\n\
	str r0, [sp, #0x68]\n\
	movs r1, #0x54\n\
	str r1, [sp, #0x80]\n\
	movs r2, #0\n\
	str r2, [sp, #0x84]\n\
	movs r3, #0\n\
	str r3, [sp, #0x88]\n\
	ldr r4, [sp, #0x6c]\n\
	mov r8, r4\n\
_0805204E:\n\
	ldr r0, [sp, #0x68]\n\
	adds r0, #0x1a\n\
	add r0, ip\n\
	ldrb r0, [r0]\n\
	cmp r0, #1\n\
	bne _080520E8\n\
	mov r6, r8\n\
	ldr r1, [r6]\n\
	movs r0, #0x9c\n\
	strh r0, [r1, #2]\n\
	ldr r0, [r6]\n\
	add r7, sp, #0x80\n\
	ldrh r7, [r7]\n\
	strh r7, [r0, #4]\n\
	movs r5, #0\n\
	ldr r1, [sp, #0x68]\n\
	movs r2, #6\n\
	ldrsh r0, [r1, r2]\n\
	adds r0, #1\n\
	cmp r5, r0\n\
	blt _0805207A\n\
	b _080522E2\n\
_0805207A:\n\
	ldr r3, [sp, #0x6c]\n\
	ldr r6, [sp, #0x84]\n\
	adds r4, r3, r6\n\
	ldr r7, _080520D0 @ =gOamBuffer\n\
	mov sb, r7\n\
	movs r6, #8\n\
	ldr r0, _080520D4 @ =0xFFFFFE00\n\
	mov sl, r0\n\
_0805208A:\n\
	ldr r0, [r4]\n\
	adds r7, r0, r6\n\
	ldrh r2, [r7]\n\
	lsls r2, r2, #3\n\
	add r2, sb\n\
	movs r3, #2\n\
	ldrsh r1, [r7, r3]\n\
	movs r3, #2\n\
	ldrsh r0, [r0, r3]\n\
	adds r1, r1, r0\n\
	ldr r3, _080520D8 @ =0x000001FF\n\
	adds r0, r3, #0\n\
	ands r1, r0\n\
	ldrh r3, [r2, #2]\n\
	mov r0, sl\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strh r0, [r2, #2]\n\
	ldrh r1, [r7]\n\
	lsls r1, r1, #3\n\
	add r1, sb\n\
	ldr r0, [r4]\n\
	ldrb r0, [r0, #4]\n\
	ldrb r7, [r7, #4]\n\
	adds r0, r0, r7\n\
	strb r0, [r1]\n\
	adds r6, #8\n\
	adds r5, #1\n\
	ldr r7, [sp, #0x68]\n\
	movs r1, #6\n\
	ldrsh r0, [r7, r1]\n\
	adds r0, #1\n\
	cmp r5, r0\n\
	blt _0805208A\n\
	b _080522E2\n\
	.align 2, 0\n\
_080520D0: .4byte gOamBuffer\n\
_080520D4: .4byte 0xFFFFFE00\n\
_080520D8: .4byte 0x000001FF\n\
_080520DC: .4byte gUnknown_0200B978\n\
_080520E0: .4byte gOptionsData\n\
_080520E4: .4byte gUnknown_086BB9A8\n\
_080520E8:\n\
	mov r2, r8\n\
	ldr r1, [r2]\n\
	movs r0, #0x9c\n\
	strh r0, [r1, #2]\n\
	ldr r0, [r2]\n\
	add r3, sp, #0x80\n\
	ldrh r3, [r3]\n\
	strh r3, [r0, #4]\n\
	ldr r4, [r2]\n\
	adds r7, r4, #0\n\
	adds r7, #8\n\
	ldr r6, [sp, #0x68]\n\
	movs r0, #0xc\n\
	ldrsh r1, [r6, r0]\n\
	lsls r0, r1, #2\n\
	adds r0, r0, r1\n\
	lsls r0, r0, #1\n\
	ldr r1, [sp, #0x88]\n\
	adds r0, r1, r0\n\
	ldr r2, _08052490 @ =gUnknown_02031AF0\n\
	adds r0, r0, r2\n\
	ldrb r0, [r0]\n\
	ldrh r2, [r4, #8]\n\
	lsls r2, r2, #3\n\
	ldr r3, _08052494 @ =gOamBuffer\n\
	adds r2, r2, r3\n\
	lsls r0, r0, #3\n\
	ldr r1, _08052498 @ =gUnknown_086BB910\n\
	adds r6, r0, r1\n\
	ldrh r0, [r6, #2]\n\
	ldr r1, _0805249C @ =0x000003FF\n\
	ands r1, r0\n\
	ldrh r3, [r2, #4]\n\
	ldr r0, _080524A0 @ =0xFFFFFC00\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strh r0, [r2, #4]\n\
	ldrh r1, [r4, #8]\n\
	lsls r1, r1, #3\n\
	ldr r2, _08052494 @ =gOamBuffer\n\
	adds r1, r1, r2\n\
	ldrb r2, [r6, #4]\n\
	lsls r2, r2, #6\n\
	ldrb r3, [r1, #1]\n\
	movs r0, #0x3f\n\
	mov sl, r0\n\
	ands r0, r3\n\
	orrs r0, r2\n\
	strb r0, [r1, #1]\n\
	ldrh r2, [r4, #8]\n\
	lsls r2, r2, #3\n\
	ldr r1, _08052494 @ =gOamBuffer\n\
	adds r2, r2, r1\n\
	ldrb r1, [r6, #5]\n\
	lsls r1, r1, #6\n\
	ldrb r3, [r2, #3]\n\
	mov r0, sl\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strb r0, [r2, #3]\n\
	ldrh r2, [r4, #8]\n\
	lsls r2, r2, #3\n\
	ldr r3, _08052494 @ =gOamBuffer\n\
	adds r2, r2, r3\n\
	movs r0, #2\n\
	ldrsh r1, [r7, r0]\n\
	mov r3, r8\n\
	ldr r0, [r3]\n\
	movs r3, #2\n\
	ldrsh r0, [r0, r3]\n\
	adds r1, r1, r0\n\
	ldr r0, _080524A4 @ =0x000001FF\n\
	ands r1, r0\n\
	ldrh r3, [r2, #2]\n\
	ldr r0, _080524A8 @ =0xFFFFFE00\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strh r0, [r2, #2]\n\
	ldrh r1, [r4, #8]\n\
	lsls r1, r1, #3\n\
	ldr r2, _08052494 @ =gOamBuffer\n\
	adds r1, r1, r2\n\
	mov r3, r8\n\
	ldr r0, [r3]\n\
	ldrb r0, [r0, #4]\n\
	ldrb r7, [r7, #4]\n\
	adds r0, r0, r7\n\
	strb r0, [r1]\n\
	ldr r4, [sp, #0x68]\n\
	movs r7, #0xc\n\
	ldrsh r1, [r4, r7]\n\
	lsls r0, r1, #2\n\
	adds r0, r0, r1\n\
	lsls r0, r0, #1\n\
	adds r0, #1\n\
	ldr r1, [sp, #0x88]\n\
	adds r0, r1, r0\n\
	ldr r2, _08052490 @ =gUnknown_02031AF0\n\
	adds r0, r0, r2\n\
	ldrb r0, [r0]\n\
	mov sb, r0\n\
	cmp r0, #0xa\n\
	bne _080521B8\n\
	b _080522E2\n\
_080521B8:\n\
	ldr r3, [sp, #0x74]\n\
	ldr r4, [sp, #0x84]\n\
	adds r5, r3, r4\n\
	ldr r1, [r5]\n\
	mov r7, r8\n\
	ldr r0, [r7]\n\
	ldrh r0, [r0, #2]\n\
	ldrb r6, [r6, #6]\n\
	adds r0, r0, r6\n\
	strh r0, [r1, #2]\n\
	ldr r1, [r5]\n\
	ldr r0, [r7]\n\
	ldrh r0, [r0, #4]\n\
	strh r0, [r1, #4]\n\
	ldr r4, [r5]\n\
	adds r7, r4, #0\n\
	adds r7, #8\n\
	ldrh r2, [r4, #8]\n\
	lsls r2, r2, #3\n\
	ldr r0, _08052494 @ =gOamBuffer\n\
	adds r2, r2, r0\n\
	ldrh r1, [r2, #4]\n\
	ldr r0, _080524A0 @ =0xFFFFFC00\n\
	ands r0, r1\n\
	movs r1, #0x2a\n\
	orrs r0, r1\n\
	strh r0, [r2, #4]\n\
	ldrh r1, [r4, #8]\n\
	lsls r1, r1, #3\n\
	ldr r2, _08052494 @ =gOamBuffer\n\
	adds r1, r1, r2\n\
	ldrb r2, [r1, #1]\n\
	mov r0, sl\n\
	ands r0, r2\n\
	strb r0, [r1, #1]\n\
	ldrh r1, [r4, #8]\n\
	lsls r1, r1, #3\n\
	ldr r3, _08052494 @ =gOamBuffer\n\
	adds r1, r1, r3\n\
	ldrb r2, [r1, #3]\n\
	mov r0, sl\n\
	ands r0, r2\n\
	strb r0, [r1, #3]\n\
	ldrh r3, [r4, #8]\n\
	lsls r3, r3, #3\n\
	ldr r6, _08052494 @ =gOamBuffer\n\
	adds r3, r3, r6\n\
	movs r0, #2\n\
	ldrsh r1, [r7, r0]\n\
	ldr r0, [r5]\n\
	movs r2, #2\n\
	ldrsh r0, [r0, r2]\n\
	adds r1, r1, r0\n\
	ldr r6, _080524A4 @ =0x000001FF\n\
	ands r1, r6\n\
	ldrh r2, [r3, #2]\n\
	ldr r0, _080524A8 @ =0xFFFFFE00\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strh r0, [r3, #2]\n\
	ldrh r1, [r4, #8]\n\
	lsls r1, r1, #3\n\
	ldr r0, _08052494 @ =gOamBuffer\n\
	adds r1, r1, r0\n\
	ldr r0, [r5]\n\
	ldrb r0, [r0, #4]\n\
	ldrb r7, [r7, #4]\n\
	adds r0, r0, r7\n\
	strb r0, [r1]\n\
	ldr r1, [sp, #0x7c]\n\
	ldr r2, [sp, #0x84]\n\
	adds r6, r1, r2\n\
	ldr r1, [r6]\n\
	ldr r0, [r5]\n\
	ldrh r0, [r0, #2]\n\
	adds r0, #8\n\
	strh r0, [r1, #2]\n\
	ldr r1, [r6]\n\
	mov r3, r8\n\
	ldr r0, [r3]\n\
	ldrh r0, [r0, #4]\n\
	strh r0, [r1, #4]\n\
	ldr r5, [r6]\n\
	adds r7, r5, #0\n\
	adds r7, #8\n\
	ldrh r3, [r5, #8]\n\
	lsls r3, r3, #3\n\
	ldr r4, _08052494 @ =gOamBuffer\n\
	adds r3, r3, r4\n\
	mov r0, sb\n\
	lsls r4, r0, #3\n\
	ldr r1, _08052498 @ =gUnknown_086BB910\n\
	adds r4, r4, r1\n\
	ldrh r0, [r4, #2]\n\
	ldr r1, _0805249C @ =0x000003FF\n\
	ands r1, r0\n\
	ldrh r2, [r3, #4]\n\
	ldr r0, _080524A0 @ =0xFFFFFC00\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strh r0, [r3, #4]\n\
	ldrh r2, [r5, #8]\n\
	lsls r2, r2, #3\n\
	ldr r3, _08052494 @ =gOamBuffer\n\
	adds r2, r2, r3\n\
	ldrb r1, [r4, #4]\n\
	lsls r1, r1, #6\n\
	ldrb r3, [r2, #1]\n\
	mov r0, sl\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strb r0, [r2, #1]\n\
	ldrh r2, [r5, #8]\n\
	lsls r2, r2, #3\n\
	ldr r0, _08052494 @ =gOamBuffer\n\
	adds r2, r2, r0\n\
	ldrb r1, [r4, #5]\n\
	lsls r1, r1, #6\n\
	ldrb r3, [r2, #3]\n\
	mov r0, sl\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strb r0, [r2, #3]\n\
	ldrh r3, [r5, #8]\n\
	lsls r3, r3, #3\n\
	ldr r1, _08052494 @ =gOamBuffer\n\
	adds r3, r3, r1\n\
	movs r2, #2\n\
	ldrsh r1, [r7, r2]\n\
	ldr r0, [r6]\n\
	movs r4, #2\n\
	ldrsh r0, [r0, r4]\n\
	adds r1, r1, r0\n\
	ldr r0, _080524A4 @ =0x000001FF\n\
	ands r1, r0\n\
	ldrh r2, [r3, #2]\n\
	ldr r0, _080524A8 @ =0xFFFFFE00\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strh r0, [r3, #2]\n\
	ldrh r1, [r5, #8]\n\
	lsls r1, r1, #3\n\
	ldr r2, _08052494 @ =gOamBuffer\n\
	adds r1, r1, r2\n\
	ldr r0, [r6]\n\
	ldrb r0, [r0, #4]\n\
	ldrb r7, [r7, #4]\n\
	adds r0, r0, r7\n\
	strb r0, [r1]\n\
_080522E2:\n\
	ldr r3, [sp, #0x80]\n\
	adds r3, #0xc\n\
	str r3, [sp, #0x80]\n\
	ldr r4, [sp, #0x84]\n\
	adds r4, #0xc\n\
	str r4, [sp, #0x84]\n\
	ldr r6, [sp, #0x88]\n\
	adds r6, #2\n\
	str r6, [sp, #0x88]\n\
	movs r7, #0xc\n\
	add r8, r7\n\
	movs r0, #1\n\
	add ip, r0\n\
	mov r1, ip\n\
	cmp r1, #4\n\
	bgt _08052304\n\
	b _0805204E\n\
_08052304:\n\
	movs r5, #8\n\
	movs r0, #0xaa\n\
	ldr r2, [sp, #0x64]\n\
	strh r0, [r2, #2]\n\
	ldr r0, _080524AC @ =gOptionsData\n\
	adds r0, #0x2a\n\
	ldrb r0, [r0]\n\
	lsls r1, r0, #1\n\
	adds r1, r1, r0\n\
	lsls r1, r1, #2\n\
	movs r0, #0x2c\n\
	subs r0, r0, r1\n\
	strh r0, [r2, #4]\n\
	ldr r7, [sp, #0x78]\n\
	ldrh r2, [r2, #8]\n\
	lsls r2, r2, #3\n\
	ldr r3, _08052494 @ =gOamBuffer\n\
	adds r2, r2, r3\n\
	movs r4, #2\n\
	ldrsh r1, [r7, r4]\n\
	adds r1, #0xaa\n\
	ldr r6, _080524A4 @ =0x000001FF\n\
	adds r0, r6, #0\n\
	ands r1, r0\n\
	ldrh r3, [r2, #2]\n\
	ldr r4, _080524A8 @ =0xFFFFFE00\n\
	adds r0, r4, #0\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strh r0, [r2, #2]\n\
	ldr r0, [sp, #0x64]\n\
	ldrh r1, [r0, #8]\n\
	lsls r1, r1, #3\n\
	ldr r2, _08052494 @ =gOamBuffer\n\
	adds r1, r1, r2\n\
	ldrb r0, [r0, #4]\n\
	ldrb r7, [r7, #4]\n\
	adds r0, r0, r7\n\
	strb r0, [r1]\n\
	movs r0, #0xc0\n\
	ldr r3, _080524B0 @ =gUnknown_0200C948\n\
	strh r0, [r3, #2]\n\
	strh r5, [r3, #4]\n\
	ldr r6, _080524AC @ =gOptionsData\n\
	adds r6, #0x2d\n\
	mov sl, r6\n\
	adds r5, r3, #0\n\
	adds r5, #8\n\
	movs r6, #0x40\n\
	mov sb, r4\n\
	movs r7, #1\n\
	mov ip, r7\n\
_0805236C:\n\
	ldrh r3, [r5]\n\
	lsls r3, r3, #3\n\
	ldr r0, _08052494 @ =gOamBuffer\n\
	adds r3, r3, r0\n\
	mov r2, sl\n\
	movs r1, #0\n\
	ldrsb r1, [r2, r1]\n\
	lsls r1, r1, #2\n\
	adds r1, r6, r1\n\
	ldr r7, _0805249C @ =0x000003FF\n\
	adds r4, r7, #0\n\
	ands r1, r4\n\
	ldrh r2, [r3, #4]\n\
	ldr r0, _080524A0 @ =0xFFFFFC00\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strh r0, [r3, #4]\n\
	ldrh r3, [r5]\n\
	lsls r3, r3, #3\n\
	ldr r0, _08052494 @ =gOamBuffer\n\
	adds r3, r3, r0\n\
	movs r2, #2\n\
	ldrsh r1, [r5, r2]\n\
	ldr r7, _080524B0 @ =gUnknown_0200C948\n\
	movs r2, #2\n\
	ldrsh r0, [r7, r2]\n\
	adds r1, r1, r0\n\
	ldr r7, _080524A4 @ =0x000001FF\n\
	mov r8, r7\n\
	mov r0, r8\n\
	ands r1, r0\n\
	ldrh r2, [r3, #2]\n\
	mov r0, sb\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strh r0, [r3, #2]\n\
	ldrh r1, [r5]\n\
	lsls r1, r1, #3\n\
	ldr r2, _08052494 @ =gOamBuffer\n\
	adds r1, r1, r2\n\
	ldr r3, _080524B0 @ =gUnknown_0200C948\n\
	ldrb r0, [r3, #4]\n\
	ldrb r7, [r5, #4]\n\
	adds r0, r0, r7\n\
	strb r0, [r1]\n\
	adds r5, #8\n\
	adds r6, #0x80\n\
	movs r0, #1\n\
	rsbs r0, r0, #0\n\
	add ip, r0\n\
	mov r1, ip\n\
	cmp r1, #0\n\
	bge _0805236C\n\
	ldr r2, _080524B4 @ =gUnknown_0200CA00\n\
	ldrh r0, [r2]\n\
	cmp r0, #1\n\
	bne _08052454\n\
	movs r0, #0xb0\n\
	strh r0, [r2, #2]\n\
	movs r0, #8\n\
	strh r0, [r2, #4]\n\
	adds r7, r2, #0\n\
	adds r7, #8\n\
	ldrh r2, [r2, #8]\n\
	lsls r2, r2, #3\n\
	ldr r3, _08052494 @ =gOamBuffer\n\
	adds r2, r2, r3\n\
	ldr r5, _080524AC @ =gOptionsData\n\
	adds r5, #0x2f\n\
	movs r1, #0\n\
	ldrsb r1, [r5, r1]\n\
	lsls r1, r1, #6\n\
	adds r1, #0x54\n\
	ands r1, r4\n\
	ldrh r3, [r2, #4]\n\
	ldr r0, _080524A0 @ =0xFFFFFC00\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strh r0, [r2, #4]\n\
	ldr r4, _080524B4 @ =gUnknown_0200CA00\n\
	ldrh r2, [r4, #8]\n\
	lsls r2, r2, #3\n\
	ldr r6, _08052494 @ =gOamBuffer\n\
	adds r2, r2, r6\n\
	movs r0, #2\n\
	ldrsh r1, [r7, r0]\n\
	movs r3, #2\n\
	ldrsh r0, [r4, r3]\n\
	adds r1, r1, r0\n\
	mov r4, r8\n\
	ands r1, r4\n\
	ldrh r3, [r2, #2]\n\
	ldr r0, _080524A8 @ =0xFFFFFE00\n\
	ands r0, r3\n\
	orrs r0, r1\n\
	strh r0, [r2, #2]\n\
	ldr r6, _080524B4 @ =gUnknown_0200CA00\n\
	ldrh r1, [r6, #8]\n\
	lsls r1, r1, #3\n\
	ldr r0, _08052494 @ =gOamBuffer\n\
	adds r1, r1, r0\n\
	ldrb r0, [r6, #4]\n\
	ldrb r7, [r7, #4]\n\
	adds r0, r0, r7\n\
	strb r0, [r1]\n\
	ldr r0, _080524B8 @ =gMain\n\
	ldr r0, [r0, #0x4c]\n\
	movs r1, #0x12\n\
	bl __umodsi3\n\
	cmp r0, #0\n\
	bne _08052454\n\
	ldrb r1, [r5]\n\
	movs r0, #1\n\
	subs r0, r0, r1\n\
	strb r0, [r5]\n\
_08052454:\n\
	movs r0, #0\n\
	ldr r1, [sp, #0x60]\n\
	strh r0, [r1]\n\
	mov ip, r0\n\
	ldr r4, [sp, #0x6c]\n\
	movs r3, #0\n\
_08052460:\n\
	mov r2, ip\n\
	adds r2, #1\n\
	mov r6, ip\n\
	lsls r0, r6, #1\n\
	add r0, ip\n\
	lsls r0, r0, #2\n\
	adds r1, r0, r4\n\
	movs r5, #2\n\
_08052470:\n\
	ldm r1!, {r0}\n\
	strh r3, [r0]\n\
	subs r5, #1\n\
	cmp r5, #0\n\
	bge _08052470\n\
	mov ip, r2\n\
	cmp r2, #5\n\
	ble _08052460\n\
	add sp, #0x8c\n\
	pop {r3, r4, r5}\n\
	mov r8, r3\n\
	mov sb, r4\n\
	mov sl, r5\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_08052490: .4byte gUnknown_02031AF0\n\
_08052494: .4byte gOamBuffer\n\
_08052498: .4byte gUnknown_086BB910\n\
_0805249C: .4byte 0x000003FF\n\
_080524A0: .4byte 0xFFFFFC00\n\
_080524A4: .4byte 0x000001FF\n\
_080524A8: .4byte 0xFFFFFE00\n\
_080524AC: .4byte gOptionsData\n\
_080524B0: .4byte gUnknown_0200C948\n\
_080524B4: .4byte gUnknown_0200CA00\n\
_080524B8: .4byte gMain");
}

void sub_524BC(void) {
	int i, pressedKeys;
	if (gOptionsData.unk28 >= 2)
		return;

	pressedKeys = gMain.heldKeys & (KEYS_MASK ^ START_BUTTON);
	if (!pressedKeys)
		return;

	for (i = 0; i < 10; i++) {
		int key = pressedKeys & (1 << i);
		if (key && !(gOptionsData.unk22 & key)) {
			gOptionsData.unk22 |= key;
			gOptionsData.unk24[gOptionsData.unk28] = i;
			if (++gOptionsData.unk28 == 2)
				return;
		}
	}
}

void sub_52528(void) {
	int i, j;
	u8 var0;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 2; j++) {
			switch (gUnknown_0200B204[i][j]) {
				case 0x1:
					var0 = 0;
					break;
				case 0x2:
					var0 = 1;
					break;
				case 0x4:
					var0 = 2;
					break;
				case 0x10:
					var0 = 4;
					break;
				case 0x20:
					var0 = 5;
					break;
				case 0x40:
					var0 = 6;
					break;
				case 0x80:
					var0 = 7;
					break;
				case 0x100:
					var0 = 8;
					break;
				case 0x200:
					var0 = 9;
					break;
				case 0x8:
				default:
					var0 = 10;
					break;
			}
			gUnknown_02031B18[i * 2 + j] = var0;
		}
	}
}

extern const u8 gUnknown_08527EFE[];

void sub_525CC(s8 arg0) {
	int i;
	s8 var0 = arg0 + 1;
	switch (var0) {
		case 0:
			gMain.unk60 = gUnknown_086BB910[5][0];
			gMain.unk62 = gUnknown_086BB910[10][0];
			gMain.unk64 = gUnknown_086BB910[0][0];
			gMain.unk66 = gUnknown_086BB910[10][0];
			gMain.unk68 = gUnknown_086BB910[9][0];
			gMain.unk6A = gUnknown_086BB910[10][0];
			gMain.unk6C = gUnknown_086BB910[8][0];
			gMain.unk6E = gUnknown_086BB910[10][0];
			gMain.unk70 = gUnknown_086BB910[9][0];
			gMain.unk72 = gUnknown_086BB910[8][0];
			gMain_saveData.unk144[0][0] = gUnknown_086BB910[1][0];
			gMain_saveData.unk144[0][1] = gUnknown_086BB910[10][0];
			gMain_saveData.unk144[1][0] = gUnknown_086BB910[0][0];
			gMain_saveData.unk144[1][1] = gUnknown_086BB910[10][0];
			gMain_saveData.unk144[2][0] = gUnknown_086BB910[5][0];
			gMain_saveData.unk144[2][1] = gUnknown_086BB910[10][0];
			gMain_saveData.unk144[3][0] = gUnknown_086BB910[4][0];
			gMain_saveData.unk144[3][1] = gUnknown_086BB910[10][0];
			gMain_saveData.unk144[4][0] = gUnknown_086BB910[6][0];
			gMain_saveData.unk144[4][1] = gUnknown_086BB910[10][0];
			for (i = 0; i < 10; i++)
				gUnknown_02031B18[i] = gUnknown_08527EFE[i];
			break;
		case 1:
			gMain.unk60 = gUnknown_086BB910[5][0];
			gMain.unk62 = gUnknown_086BB910[10][0];
			gMain.unk64 = gUnknown_086BB910[0][0];
			gMain.unk66 = gUnknown_086BB910[10][0];
			gMain.unk68 = gUnknown_086BB910[9][0];
			gMain.unk6A = gUnknown_086BB910[10][0];
			gMain.unk6C = gUnknown_086BB910[8][0];
			gMain.unk6E = gUnknown_086BB910[10][0];
			gMain.unk70 = gUnknown_086BB910[9][0];
			gMain.unk72 = gUnknown_086BB910[8][0];
			break;
		case 2:
			gMain.unk60 = gUnknown_086BB910[5][0];
			gMain.unk62 = gUnknown_086BB910[10][0];
			gMain.unk64 = gUnknown_086BB910[0][0];
			gMain.unk66 = gUnknown_086BB910[10][0];
			gMain.unk68 = gUnknown_086BB910[9][0];
			gMain.unk6A = gUnknown_086BB910[10][0];
			gMain.unk6C = gUnknown_086BB910[8][0];
			gMain.unk6E = gUnknown_086BB910[10][0];
			gMain.unk70 = gUnknown_086BB910[1][0];
			gMain.unk72 = gUnknown_086BB910[10][0];
			break;
		case 3:
			gMain.unk60 = gUnknown_086BB910[9][0];
			gMain.unk62 = gUnknown_086BB910[10][0];
			gMain.unk64 = gUnknown_086BB910[8][0];
			gMain.unk66 = gUnknown_086BB910[10][0];
			gMain.unk68 = gUnknown_086BB910[5][0];
			gMain.unk6A = gUnknown_086BB910[10][0];
			gMain.unk6C = gUnknown_086BB910[0][0];
			gMain.unk6E = gUnknown_086BB910[10][0];
			gMain.unk70 = gUnknown_086BB910[5][0];
			gMain.unk72 = gUnknown_086BB910[0][0];
			break;
		case 4:
			gMain.unk60 = gUnknown_086BB910[9][0];
			gMain.unk62 = gUnknown_086BB910[10][0];
			gMain.unk64 = gUnknown_086BB910[8][0];
			gMain.unk66 = gUnknown_086BB910[10][0];
			gMain.unk68 = gUnknown_086BB910[5][0];
			gMain.unk6A = gUnknown_086BB910[10][0];
			gMain.unk6C = gUnknown_086BB910[4][0];
			gMain.unk6E = gUnknown_086BB910[10][0];
			gMain.unk70 = gUnknown_086BB910[6][0];
			gMain.unk72 = gUnknown_086BB910[10][0];
			break;
		case 5:
			gMain.unk60 = gMain_saveData.unk144[0][0];
			gMain.unk62 = gMain_saveData.unk144[0][1];
			gMain.unk64 = gMain_saveData.unk144[1][0];
			gMain.unk66 = gMain_saveData.unk144[1][1];
			gMain.unk68 = gMain_saveData.unk144[2][0];
			gMain.unk6A = gMain_saveData.unk144[2][1];
			gMain.unk6C = gMain_saveData.unk144[3][0];
			gMain.unk6E = gMain_saveData.unk144[3][1];
			gMain.unk70 = gMain_saveData.unk144[4][0];
			gMain.unk72 = gMain_saveData.unk144[4][1];
			break;
	}
}
