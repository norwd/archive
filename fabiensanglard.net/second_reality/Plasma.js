var SCREEN_WIDTH = 320;
var SCREEN_HEIGHT = 400;
var FRAME_BUFFER_WIDTH = 384;
var FRAME_BUFFER_HEIGHT = 400;
var PLANE_COUNT = 4;
var COLOURS_PER_ENTRY = 3;
var DPII = (3.1415926535*2.0);
var MAXY = 280;

var g_au8FrameBuffer = new Uint8Array(FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT);
var s_abSelectedPlanes = [ false, false, false, false ];
var s_nLineCompareY = 0;
var s_nHorizontalScrollOffset = 0;
var s_au8Palette = new Uint8Array(256 * COLOURS_PER_ENTRY);
var frame_count = 0;
var cop_drop = 0;
var do_pal = 0;
var cop_start = 0;
var cop_scrl = 0;
var cop_plz = 1;
var pompi = 0;
var dtau = new Array();
var fadepal = new Uint8Array(768 * 2);
var cop_fadepal_SelectedPaletteIndex = 0;
var anSelfModifyOffsets = new Uint16Array(5 * 84);

// [NK 8/1/2014] The assembly code assumes the tables are sequential in memory,
// [NK 8/1/2014] so merge them into one array to be safe.
var psini = new Uint8Array(16384 + (8192 * 2) + (8192 * 2));
var psini_DataView = new DataView(psini.buffer);
var ptau = new Uint8Array(256);
var pals = new Uint16Array(6 * 768);
var pals_DataView = new DataView(pals.buffer);

var curpal=0;
var timetable=[64*6*2-45,64*6*4-45,64*6*5-45,64*6*6-45,64*6*7+90,0];
var ttptr=0;

var	l1=1000, l2=2000, l3=3000, l4=4000;
var	k1=3500, k2=2300, k3=3900, k4=3670;

var	il1=1000, il2=2000, il3=3000, il4=4000;
var	ik1=3500, ik2=2300, ik3=3900, ik4=3670;

var inittable = new Array();
var IsComplete = false;

//--------------------------------------------------------------------------------------
// Variable wrappers

function Palette_WriteByte(nOffset, u8Byte)
{
	s_au8Palette[nOffset] = u8Byte;
}

function Palette_ReadByte(nOffset)
{
	return s_au8Palette[nOffset];
}

function FrameBuffer_WriteByte(nOffset, u8Byte)
{
	g_au8FrameBuffer[nOffset] = u8Byte;
}

function FrameBuffer_ReadByte(nOffset)
{
	return g_au8FrameBuffer[nOffset];
}

function lsini16_GetOffset()
{
	return 16384 + (8192 * 2);
}

function lsini4_GetOffset()
{
	return 16384;
}

function cop_fadepal_SetSelectedPaletteIndex(nIndex)
{
	cop_fadepal_SelectedPaletteIndex = nIndex;
}

function cop_fadepal_ReadWord(nByteOffset)
{
	// Advance to the currently selected palette.
	nByteOffset += (cop_fadepal_SelectedPaletteIndex * 768 * 2);

	return pals_DataView.getUint16(nByteOffset);
}

function fadepal_ReadByte(nByteOffset)
{
	return fadepal[nByteOffset];
}

function fadepal_WriteByte(nByteOffset, nValue)
{
	fadepal[nByteOffset] = nValue;
}

function lsini4_WriteWord(nIndex, nValue)
{
	var nByteOffset = lsini4_GetOffset() + (nIndex * 2);
	psini_WriteWord(nByteOffset, nValue);
}

function lsini16_WriteWord(nIndex, nValue)
{
	var nByteOffset = lsini16_GetOffset() + (nIndex * 2);
	psini_WriteWord(nByteOffset, nValue);
}

function psini_WriteByte(nIndex, nValue)
{
	psini[nIndex] = nValue;
}

function psini_ReadByte(nIndex, nValue)
{
	return psini[nIndex];
}

function psini_WriteWord(nByteOffset, nValue) {
	psini_DataView.setUint16(nByteOffset, nValue);
}

function psini_ReadWord(nByteOffset, nValue) {
	return psini_DataView.getUint16(nByteOffset);
}

function ptau_WriteByte(nIndex, nValue)
{
	ptau[nIndex] = nValue;
}

function ptau_ReadByte(nIndex)
{
	return ptau[nIndex];
}

function pal_WriteWord(nByteOffset, nWord)
{
	pals_DataView.setUint16(nByteOffset, nWord);
}

function pal_ReadWord(nByteOffset)
{
	return pals_DataView.getUint16(nByteOffset);
}

function fadepal_Clear()
{
	for (var i = 0; i < 768; i++)
	{
		fadepal[i] = 0;
	}
}

function fadepal_ClearToWhite() {
	for (var i = 0; i < 768; i++) {
		fadepal[i] = 63;
	}
}

function anSelfModifyOffsets_ReadWord(nOffset)
{
	return anSelfModifyOffsets[nOffset];
}

function anSelfModifyOffsets_WriteWord(nOffset, nValue)
{
	anSelfModifyOffsets[nOffset] = nValue;
}

//--------------------------------------------------------------------------------------
// SDL

function SDL_SetPixel(x, y, color)
{
	var pixels = image.data;
	var nOffset = (((y * 320) + x) * 4);
	pixels[nOffset] = (color >> 0) & 0xFF;
	nOffset++;
	pixels[nOffset] = (color >> 8) & 0xFF;
	nOffset++;
	pixels[nOffset] = (color >> 16) & 0xFF;
	nOffset++;
	pixels[nOffset] = 0xFF;
	nOffset++;
}

function SDL_SetPixelColours(x, y, nRed, nGreen, nBlue)
{
	var pixels = image.data;
	var nOffset = (((y * 320) + x) * 4);
	pixels[nOffset] = (nRed) & 0xFF;
	nOffset++;
	pixels[nOffset] = (nGreen) & 0xFF;
	nOffset++;
	pixels[nOffset] = (nBlue) & 0xFF;
	nOffset++;
	pixels[nOffset] = 0xFF;
	nOffset++;
}

//--------------------------------------------------------------------------------------
// VGA

function VGA_SelectBitPlanes02()
{
	s_abSelectedPlanes[0] = true;
	s_abSelectedPlanes[1] = false;
	s_abSelectedPlanes[2] = true;
	s_abSelectedPlanes[3] = false;
}

function VGA_SelectBitPlanes13()
{
	s_abSelectedPlanes[0] = false;
	s_abSelectedPlanes[1] = true;
	s_abSelectedPlanes[2] = false;
	s_abSelectedPlanes[3] = true;
}

function VGA_SelectBitPlanes0123()
{
	s_abSelectedPlanes[0] = true;
	s_abSelectedPlanes[1] = true;
	s_abSelectedPlanes[2] = true;
	s_abSelectedPlanes[3] = true;
}

function VGA_WriteDword(nOffset, uValue)
{
	// For each selected plane, calculate 4 pixel offsets and write 4 bytes.
	// nOffset = 0, 4, 8, etc

	for (var nPlaneIndex = 0; nPlaneIndex < PLANE_COUNT; nPlaneIndex++)
	{
		if (s_abSelectedPlanes[nPlaneIndex])
		{
			for (var nPixelIndex = 0; nPixelIndex < 4; nPixelIndex++)
			{
				// Get byte to write.
				var u8Byte = (uValue >> (nPixelIndex * 8)) & 0xFF;

				// Calculate offset.
				var nFrameBufferOffset = nPlaneIndex + (nOffset * 4) + (nPixelIndex * 4);

				// Write pixel.
				FrameBuffer_WriteByte(nFrameBufferOffset, u8Byte);
			}
		}
	}
}

function VGA_SetLineCompare(nY)
{
	s_nLineCompareY = nY;
}

function VGA_SetPaletteEntry(nIndex, u8Red, u8Green, u8Blue)
{
	var nOffset = 0;

	nOffset = (nIndex * 3) + 0;
	Palette_WriteByte(nOffset, u8Red);

	nOffset = (nIndex * 3) + 1;
	Palette_WriteByte(nOffset, u8Green);

	nOffset = (nIndex * 3) + 2;
	Palette_WriteByte(nOffset, u8Blue);
}

function VGA_ShowFrameBuffer()
{
	copper1();
	copper2();

	var nFirstLineIndex = (s_nLineCompareY + 1);

	// Plot the palettised frame buffer.
	var nFrameBufferOffset = 0;

	for (var nY = nFirstLineIndex; nY < SCREEN_HEIGHT; nY++)
	{
		for (var nX = 0; nX < SCREEN_WIDTH; nX++)
		{
			//ASSERT(nX + s_nHorizontalScrollOffset < FRAME_BUFFER_WIDTH);
			var nPaletteIndex = FrameBuffer_ReadByte(nFrameBufferOffset + nX + s_nHorizontalScrollOffset);

			var nPaletteOffset = 0;
			nPaletteOffset = (nPaletteIndex * 3) + 0;
			var nRed = Palette_ReadByte(nPaletteOffset);
			nPaletteOffset = (nPaletteIndex * 3) + 1;
			var nGreen = Palette_ReadByte(nPaletteOffset);
			nPaletteOffset = (nPaletteIndex * 3) + 2;
			var nBlue = Palette_ReadByte(nPaletteOffset);

			// [NK 12/1/2014] VGA colours range from 0 - 63 inclusive, but
			// [NK 12/1/2014] SDL colours range from 0 - 255 inclusive, so
			// [NK 12/1/2014] account for this here.
			nRed &= 63;
			nGreen &= 63;
			nBlue &= 63;

			nRed *= 255;
			nRed /= 63;
			nGreen *= 255;
			nGreen /= 63;
			nBlue *= 255;
			nBlue /= 63;

			SDL_SetPixelColours(nX, nY, nRed, nGreen, nBlue);
		}

		nFrameBufferOffset += FRAME_BUFFER_WIDTH;
	}
}

function VGA_SetHorizontalScrollOffset(nOffset)
{
	s_nHorizontalScrollOffset = nOffset;
}

function VGA_UploadPalette(Palette)
{
	var Source = new Uint8Array(Palette.buffer, 0, 768);
	var Destination = s_au8Palette;
	Destination.set(Source);
}

//--------------------------------------------------------------------------------------
// Tweak

function tw_setrgbpalette(pal, r, g, b)
{
	VGA_SetPaletteEntry(pal, r, g, b);
}

//--------------------------------------------------------------------------------------
// Asmyt

function plzline(y, vseg)
{
	// vseg represented a segment, so multiply by sixteen (shift left by 4)
	// to convert into an offset.
	var nVgaYOffset = vseg * 16;

	var cccTable =
	[
		3,2,1,0,7,6,5,4,11,10,9,8,15,14,13,12,19,18,17,16,23,22,21,20,27,26,25,24,31,30,29,28,35,34,33,32,39,38,37,36,43,42,41,40,47,46,45,44,51,50,49,48,55,54,53,52,59,58,57,56,63,62,61,60,67,66,65,64,71,70,69,68,75,74,73,72,79,78,77,76,83,82,81,80
	];
	var nCount = 84;

	var ah = 0;
	var al = 0;
	var eax = 0;

	for (var nIndex = 0; nIndex < nCount; nIndex++)
	{
		var ccc = cccTable[nIndex];

		if ((ccc & 1) == 1)
		{
			var nByteOffset = 0;
			var bx = 0;

			nByteOffset = (y * 2) + anSelfModifyOffsets_ReadWord((2 * 84) + ccc);
			nByteOffset &= 0xFFFF;
			bx = psini_ReadWord(nByteOffset);

			nByteOffset = bx + anSelfModifyOffsets_ReadWord((1 * 84) + ccc);
			nByteOffset &= 0xFFFF;
			ah = psini_ReadByte(nByteOffset);

			nByteOffset = (y * 2) + anSelfModifyOffsets_ReadWord((4 * 84) + ccc);
			nByteOffset &= 0xFFFF;
			bx = psini_ReadWord(nByteOffset);

			nByteOffset = bx + (y * 2) + anSelfModifyOffsets_ReadWord((3 * 84) + ccc);
			nByteOffset &= 0xFFFF;
			ah += psini_ReadByte(nByteOffset);
			ah &= 0xFF;
		}
		else
		{
			var nByteOffset = 0;
			var bx = 0;

			nByteOffset = (y * 2) + anSelfModifyOffsets_ReadWord((2 * 84) + ccc);
			nByteOffset &= 0xFFFF;
			bx = psini_ReadWord(nByteOffset);

			nByteOffset = bx + anSelfModifyOffsets_ReadWord((1 * 84) + ccc);
			nByteOffset &= 0xFFFF;
			al = psini_ReadByte(nByteOffset);

			nByteOffset = (y * 2) + anSelfModifyOffsets_ReadWord((4 * 84) + ccc);
			nByteOffset &= 0xFFFF;
			bx = psini_ReadWord(nByteOffset);

			nByteOffset = bx + (y * 2) + anSelfModifyOffsets_ReadWord((3 * 84) + ccc);
			nByteOffset &= 0xFFFF;
			al += psini_ReadByte(nByteOffset);
			al &= 0xFF;
		}

		if ((ccc & 3) == 2)
		{
			eax = (ah << 8) | (al << 0);
			eax <<= 16;
		}

		if ((ccc & 3) == 0)
		{
			eax |= (ah << 8) | (al << 0);

			VGA_WriteDword(nVgaYOffset + ccc, eax);
		}
	}

	return 0;
}

function setplzparas(c1, c2, c3, c4)
{
	var psiniOffset = 0;
	var lsini16Offset = lsini16_GetOffset();
	var lsini4Offset = lsini4_GetOffset();

	for (var ccc = 0; ccc < 84; ccc++)
	{
		var lc1 = c1 + psiniOffset + (ccc * 8);
		lc1 &= 0xFFFF;
		anSelfModifyOffsets_WriteWord((1 * 84) + ccc, lc1);

		var lc2 = (c2 * 2) + lsini16Offset - (ccc * 8) + (80 * 8); 
		lc2 &= 0xFFFF;
		anSelfModifyOffsets_WriteWord((2 * 84) + ccc, lc2);

		var lc3 = c3 + psiniOffset - (ccc * 4) + (80 * 4);
		lc3 &= 0xFFFF;
		anSelfModifyOffsets_WriteWord((3 * 84) + ccc, lc3);

		var lc4 = (c4 * 2) + lsini4Offset + (ccc * 32);
		lc4 &= 0xFFFF;
		anSelfModifyOffsets_WriteWord((4 * 84) + ccc, lc4);
	}	

	return 0;
}

function set_plzstart(start)
{
	VGA_SetLineCompare(start);

	return 0;
}


//--------------------------------------------------------------------------------------
// Copper

function init_copper()
{
	for (var ccc = 0; ccc < 65; ccc++)
	{
		dtau[ccc] = Math.floor(ccc * ccc / 4 * 43 / 128 + 60);
	}

	return 0;
}

function close_copper()
{
	return 0;
}

function pompota() {

	// [NK 18/1/2014] Disable this for now, as it looks a bit jittery.
	return;

	// [nk] This function toggles the horizontal split point every frame
	// [nk] between line 60 and 61, along with the horizontal offset.
	// [nk] (since set_plzstart == 60, it's splitting at the top of the plasma)
	VGA_SetLineCompare(60);
	cop_scrl = 4;

	pompi++;

	if ((pompi & 1) != 0)
	{
		// [NK 12/1/2014] Moving the starting line up and down each alternate frame
		// [NK 12/1/2014] doesn't look good in windowed mode.
		// [NK 13/1/2014] Seems to work okay in fullscreen mode though.
		//VGA_SetLineCompare(61);
		cop_scrl = 0;
	}
}

function moveplz()
{
	k1 += -3;
	k1 &= 4095;
	k2 += -2;
	k2 &= 4095;
	k3 += 1;
	k3 &= 4095;
	k4 += 2;
	k4 &= 4095;
	l1 += -1;
	l1 &= 4095;
	l2 += -2;
	l2 &= 4095;
	l3 += 2;
	l3 &= 4095;
	l4 += 3;
	l4 &= 4095;
}

function initpparas()
{
	l1 = il1;
	l2 = il2;
	l3 = il3;
	l4 = il4;

	k1 = ik1;
	k2 = ik2;
	k3 = ik3;
	k4 = ik4;
}

function do_drop()
{
	cop_drop++;

	if (cop_drop <= 64)
	{
		VGA_SetLineCompare(dtau[cop_drop]);
	}
	else
	{
		var bShouldFade = false;

		// [NK 18/1/2014] Hack for looping back to the first plasma.
		if ((cop_drop == 65) && (ttptr == 0)) {
			cop_drop = 128;
		}

		if (cop_drop >= 256)
		{
		}
		else if (cop_drop >= 128)
		{
			bShouldFade = true;
		}
		else if (cop_drop > 96)
		{
		}
		else //if (cop_drop > 64)
		{
			bShouldFade = true;
		}

		if (bShouldFade)
		{
			// [NK 15/1/2014] cop_pal always points to fadepal, so just upload fadepal.
			//cop_pal = fadepal;
			do_pal = 1;

			if (cop_drop == 65)
			{
				VGA_SetLineCompare(400);
				initpparas();
			}
			else
			{
				VGA_SetLineCompare(60);

				// [NK 9/1/2014] I think it's using 8.8 fixed point numbers to fade the palette.
				var cop_fadepalIndex = 0;
				var pfadepalIndex = 0;

				for (var nIndex = 0; nIndex < (768 / 16); nIndex++)
				{
					for (var ccc = 0; ccc < 16; ccc++)
					{
						// var al = cop_fadepal_ReadByte(cop_fadepalIndex + (ccc * 2));
						// al &= 0xFF;
						// var ah = cop_fadepal_ReadByte(cop_fadepalIndex + (ccc * 2) + 1);
						// ah &= 0xFF;
						// [NK 17/1/2014] Read cop_fadepal as words, rather than bytes,
						// [NK 17/1/2014] to avoid endian issues.
						var ax = cop_fadepal_ReadWord(cop_fadepalIndex + (ccc * 2));
						var al = ax & 0xFF;
						var ah = (ax >> 8) & 0xFF;

						var nOldValue = fadepal_ReadByte(pfadepalIndex + ccc + 768);
						nOldValue &= 0xFF;

						var t = fadepal_ReadByte(pfadepalIndex + ccc + 768);
						t &= 0xFF;
						t += al;
						t &= 0xFF;
						fadepal_WriteByte(pfadepalIndex + ccc + 768, t);

						var nNewValue = fadepal_ReadByte(pfadepalIndex + ccc + 768);
						nNewValue &= 0xFF;

						var nCarry = 0;

						if (nNewValue < nOldValue)
						{
							nCarry = 1;
						}

						t = fadepal_ReadByte(pfadepalIndex + ccc);
						t &= 0xFF;
						t += ah + nCarry;
						t &= 0xFF;
						fadepal_WriteByte(pfadepalIndex + ccc, t);
					}

					cop_fadepalIndex += 32;
					pfadepalIndex += 16;
				}
			}
		}
		else
		{
			cop_drop = 0;
		}
	}
}

// [nk] just before retrace
function copper1()
{
	// There is also assembly code to set the first pixel of
	// display memory here, but it may not be necessary.

	VGA_SetHorizontalScrollOffset(cop_scrl);
}

// [nk] in retrace
function copper2()
{
	// [nk] Don't think this is used.
	frame_count++;

	if (do_pal != 0)
	{
		do_pal = 0;
		// [NK 15/1/2014] cop_pal always points to fadepal, so just upload fadepal.
		//VGA_UploadPalette(cop_pal);
		VGA_UploadPalette(fadepal);
	}

	pompota();
	moveplz();

	if (cop_drop != 0)
	{
		do_drop();
	}
}


//--------------------------------------------------------------------------------------
// Plz

function dis_exit()
{
	return false;
}

var s_nFrameCount = 0;
function dis_getmframe()
{
	s_nFrameCount++;
	return s_nFrameCount;
}

function init_plz()
{
	var a;

	// [NK 8/1/2014] Instead of writing the tables as assembly files,
	// [NK 8/1/2014] just use them directly in C++.
	{
		for(var a=0;a<1024*16;a++)
		{
			if(a<1024*8)
			{
				lsini4_WriteWord(a, (Math.sin(a * DPII / 4096) * 55 + Math.sin(a * DPII / 4096 * 5) * 8 + Math.sin(a * DPII / 4096 * 15) * 2 + 64) * 8);
				lsini16_WriteWord(a, (Math.sin(a * DPII / 4096) * 55 + Math.sin(a * DPII / 4096 * 4) * 5 + Math.sin(a * DPII / 4096 * 17) * 3 + 64) * 16);
			}
			psini_WriteByte(a, Math.sin(a * DPII / 4096) * 55 + Math.sin(a * DPII / 4096 * 6) * 5 + Math.sin(a * DPII / 4096 * 21) * 4 + 64);
		}

		for(var a=1;a<=128;a++)
		{
			ptau_WriteByte(a, Math.cos(a * DPII / 128 + 3.1415926535) * 31 + 32);
		}
	}

	cop_start=96*(682-400);
	set_plzstart(60);
	init_copper();
	for(var a=0;a<256;a++) tw_setrgbpalette(a,63,63,63);

//	RGB
	var nPalOffset = ((0 * 768) + 3) * 2;
	for(a=1;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(63 - a)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(63 - a)); nPalOffset += 2;
	}

//	RB-black
	nPalOffset = ((1 * 768) + 3) * 2;
	for(a=1;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(63 - a)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(63 - a)); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(63)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)); nPalOffset += 2;
	}

//	RB-white
	nPalOffset = ((3 * 768) + 3) * 2;
	for(a=1;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(63)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(63-a)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(63-a)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(63)); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(63)); nPalOffset += 2;
	}

//	white
	nPalOffset = ((2 * 768) + 3) * 2;
	for(a=1;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)/2); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)/2); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)/2); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)/2); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)/2); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(a)/2); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(63-a)/2); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(63-a)/2); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(63-a)/2); nPalOffset += 2;
	}
	for(a=0;a<64;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)/2); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)/2); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(0)/2); nPalOffset += 2;
	}


//	white II
	nPalOffset = ((4 * 768) + 3) * 2;
	for(a=1;a<75;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(63-a*64/75)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(63-a*64/75)); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(63-a*64/75)); nPalOffset += 2;
	}
	for(a=0;a<106;a++)
	{
		pal_WriteWord(nPalOffset, 0); nPalOffset += 2;
		pal_WriteWord(nPalOffset, 0); nPalOffset += 2;
		pal_WriteWord(nPalOffset, 0); nPalOffset += 2;
	}
	for(a=0;a<75;a++)
	{
		pal_WriteWord(nPalOffset, ptau_ReadByte(a*64/75)*8/10); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(a*64/75)*9/10); nPalOffset += 2;
		pal_WriteWord(nPalOffset, ptau_ReadByte(a*64/75)); nPalOffset += 2;
	}

	nPalOffset = 0;
	for(var a=0;a<768;a++)
	{
		var n = pal_ReadWord(nPalOffset);
		n -= 63;
		n *= 2;
		n &= 0xFFFF;
		pal_WriteWord(nPalOffset, n);
		nPalOffset += 2;
	}

	for(var a=768;a<768*5;a++)
	{
		var n = pal_ReadWord(nPalOffset);
		n *= 8;
		n &= 0xFFFF;
		pal_WriteWord(nPalOffset, n);
		nPalOffset += 2;
	}
}

function plz()
{
	var y;

	if(dis_getmframe()>timetable[ttptr])
	{
		fadepal_Clear();
		cop_drop=1;
		ttptr++;

		if (ttptr == 4) {
			// [NK 18/1/2014] Loop back to the first plasma again.
			ttptr = 0;
			curpal = 0;
			s_nFrameCount = 0;
			fadepal_ClearToWhite();
			cop_drop = 1;
		}

		cop_fadepal_SetSelectedPaletteIndex(curpal++);

		il1=inittable[ttptr][0];
		il2=inittable[ttptr][1];
		il3=inittable[ttptr][2];
		il4=inittable[ttptr][3];
		ik1=inittable[ttptr][4];
		ik2=inittable[ttptr][5];
		ik3=inittable[ttptr][6];
		ik4=inittable[ttptr][7];
	}
//	if (curpal == 5 && cop_drop > 64) {
//		return true;
//	}

	VGA_SelectBitPlanes02();

	setplzparas(k1,k2,k3,k4);
	for(y=0;y<MAXY;y+=2)
		plzline(y,y*6);
	setplzparas(l1,l2,l3,l4);
	for(y=1;y<MAXY;y+=2)
		plzline(y,y*6);

	VGA_SelectBitPlanes13();

	setplzparas(k1,k2,k3,k4);
	for(y=1;y<MAXY;y+=2)
		plzline(y,y*6);
	setplzparas(l1,l2,l3,l4);
	for(y=0;y<MAXY;y+=2)
		plzline(y,y*6);

	VGA_ShowFrameBuffer();

	return false;
//	cop_drop=0;
//	set_plzstart(500);
//	cop_plz=0;
}


//--------------------------------------------------------------------------------------
// Main

function tmain()
{
	// Create arrays.
	inittable[0] = [1000,2000,3000,4000,3500,2300,3900,3670];
	inittable[1] = [1000,2000,4000,4000,1500,2300,3900,1670];
	inittable[2] = [3500,1000,3000,1000,3500,3300,2900,2670];
	inittable[3] = [1000,2000,3000,4000,3500,2300,3900,3670];
	inittable[4] = [1000,2000,3000,4000,3500,2300,3900,3670];
	inittable[5] = [1000,2000,3000,4000,3500,2300,3900,3670];

	init_copper();
	init_plz();
	cop_drop = 128;
	cop_fadepal_SetSelectedPaletteIndex(curpal++);
}


//--------------------------------------------------------------------------------------
// HTML5 specific code

window.onload = function () {
	document.getElementsByTagName("body")[0].className = "js";

	start();
};

var canvas = null;
var context = null;
var fps = null;
var tscale = 0.02;
var lastTick = 0;
var targetFps = 1;
var image;
var canvasId = "canvas";
var fpsId = "fps";

function init() {
	canvas = canvasId ? document.getElementById(canvasId) : null;
	fps = fpsId ? document.getElementById(fpsId) : null;

	if (canvas && canvas.getContext) {
		//		canvas.width = width = window.innerWidth;
		//		canvas.height = height = window.innerHeight;
		canvas.width = 320;
		canvas.height = 400;

		context = canvas.getContext("2d");

		if (context.createImageData) {
			image = context.createImageData(canvas.width, canvas.height);
		} else if (context.getImageData) {
			image = context.getImageData(0, 0, canvas.width, canvas.height);
		} else {
			// it's Opera
			image = { 'width': canvas.width, 'height': canvas.height,
				'data': new Array(canvas.width * canvas.height * 4)
			}
		}

		for (i = 0; i < image.data.length; i++) {
			image.data[i] = 255;
		}
		return true;
	} else {
		return false;
	}
}

function draw() {

	// Clear to black.
	length = 320 * 400;
	var p = 0;
	for (var i = 0; i < length; i++) {
		image.data[p] = 0;
		p++;
		image.data[p] = 0;
		p++;
		image.data[p] = 0;
		p++;
		image.data[p] = 0xFF;
		p++;
	}

	IsComplete = plz();

	if (!image) {
		return;
	}

	var x = 0;
	var y = 0;
//	var x = (window.innerWidth - 320) / 2;
//	var y = (window.innerHeight - 400) / 2;

	context.putImageData(image, x, y);
}

function tick() {
	var start, elapsed, sleep, target;
	start = new Date().getTime();

	// check if the canvas has been resized
//	if ((canvas.clientWidth / 8) != width ||
//        (canvas.clientHeight / 8) != height) {
//		init();
//	}

	if (!IsComplete) {
		draw();
	}

	// calculate stable FPS 
	elapsed = new Date().getTime() - start;

	target = 1000 / 60;

	// calculate sleep and schedule next tick
	sleep = target - elapsed;
	if (sleep < 1) {
		sleep = 1;
	} else if (sleep > 1000) {
		sleep = 1000;
	}

	lastTick = start;
	setTimeout(tick, sleep);
}

function start() {
	lastTick = new Date().getTime();

	tmain();

	if (init()) tick();
}
