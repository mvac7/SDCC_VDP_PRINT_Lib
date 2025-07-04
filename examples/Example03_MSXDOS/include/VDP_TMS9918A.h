/* =============================================================================
  VDP TMS9918A MSX Library (fR3eL Project)
============================================================================= */
#ifndef  __VDP_TMS9918A_H__
#define  __VDP_TMS9918A_H__


// ---------------------------------------------------------
//VDP Ports  
#define VDPVRAM   0x98  //VRAM Data (Read/Write)
#define VDPSTATUS 0x99  //VDP Status Registers


// ---------------------------------------------------------
// screen modes
// https://konamiman.github.io/MSX2-Technical-Handbook/md/Chapter4a.html#3--screen-modes-of-the-msx2
#define TEXT1		0	// text mode       (screen 0)
#define GRAPHIC1	1	// graphics 1 mode (screen 1)
#define GRAPHIC2	2	// graphics 2 mode (screen 2)
#define MULTICOLOR	3	// multicolor mode (screen 3)



// ---------------------------------------------------------
// TMS9918 palette color codes
#ifndef _COLORS
#define _COLORS
#define TRANSPARENT   0
#define BLACK         1
#define GREEN         2
#define LIGHT_GREEN   3
#define DARK_BLUE     4
#define LIGHT_BLUE    5
#define DARK_RED      6
#define CYAN          7
#define RED           8
#define LIGHT_RED     9
#define DARK_YELLOW  10
#define LIGHT_YELLOW 11
#define DARK_GREEN   12
#define MAGENTA      13
#define GREY         14
#define GRAY         14
#define WHITE        15
#endif



/* ----------------------------------------------------------------------------
Definition of the different zones of the video memory.
---------------------------------------------------------------------------- */
#define T1_MAP	0x0000 // Name Table
#define T1_PAT	0x0800 // Pattern Table

#define G1_MAP	0x1800 // Name Table
#define G1_PAT	0x0000 // Pattern Table
#define G1_COL	0x2000 // Color Table

#define G2_MAP	0x1800 // Name Table
#define G2_PAT	0x0000 // Pattern Table
#define G2_PAT_A	0x0000 // Pattern Table Bank A
#define G2_PAT_B	0x0800 // Pattern Table Bank B
#define G2_PAT_C	0x1000 // Pattern Table Bank C
#define G2_COL	0x2000 // Color Table
#define G2_COL_A	0x2000 // Color Table Bank A
#define G2_COL_B	0x2800 // Color Table Bank B
#define G2_COL_C	0x3000 // Color Table Bank C

#define MC_MAP	0x0800 // Name Table
#define MC_PAT	0x0000 // Pattern Table (A tile contains the color data of 2x2 blocks)

#define SPR_OAM 0x1B00 // Sprite Attribute Table (Object Attribute Memory)
#define SPR_PAT 0x3800 // Sprite Pattern Table




/* ----------------------------------------------------------------------------
Definition of the different zones of the video memory, based on the 
BASE instruction of MSX BASIC.
OAM = Object Attribute Memory
---------------------------------------------------------------------------- */
// VRAM address tables T1 Screen 0 TXT40
#define BASE0 0x0000 // Name Table
#define BASE2 0x0800 // Pattern Table

// VRAM address tables G1 Screen 1 TXT32
#define BASE5 0x1800 // Name Table
#define BASE6 0x2000 // Color Table
#define BASE7 0x0000 // Pattern Table
#define BASE8 0x1B00 // Sprite Attribute Table (OAM)
#define BASE9 0x3800 // Sprite Pattern Table

// VRAM address tables G2 Screen 2 GRAPH1
#define BASE10 0x1800 // Name Table
#define BASE11 0x2000 // Color Table
#define BASE12 0x0000 // Pattern Table
#define BASE13 0x1B00 // Sprite Attribute Table (OAM)
#define BASE14 0x3800 // Sprite Pattern Table

// VRAM address tables MC Screen 3 GRAPH2
#define BASE15 0x0800 // Name Table
#define BASE17 0x0000 // Pattern Table
#define BASE18 0x1B00 // Sprite Attribute Table (OAM)
#define BASE19 0x3800 // Sprite Pattern Table



/* ----------------------------------------------------------------------------
G2 BANKs addends
Labels to facilitate the positioning of the tileset banks in G2 mode.
---------------------------------------------------------------------------- */
#define BANK0  0x0000
#define BANK1  0x0800
#define BANK2  0x1000



/* ----------------------------------------------------------------------------
Sprite Sizes
---------------------------------------------------------------------------- */
#define SPRITES8x8		0
#define SPRITES16x16	1




/* =============================================================================
SCREEN
Description:
		Sets the display mode of the screen.
		T1 and G1 modes are initialized the map (Pattern Name Table) with 
		value 0. 
		In G2 and MC mode are initialized in an orderly manner (as in 
		MSX BASIC) to be able to display an image directly.
Input:	[char] number of screen mode
			0 = Text mode 1
			1 = Graphic 1
			2 = Graphic 2
			3 = MultiColor (MC)
Output:	-
============================================================================= */
void SCREEN(char mode);



/* =============================================================================
SetSpritesSize
Description: 
		Set size type for the sprites.
Input:	[char] size: 0=8x8; 1=16x16
Output:	-
============================================================================= */ 
void SetSpritesSize(char size);



/* =============================================================================
SetSpritesZoom
Description: 
		Set zoom type for the sprites.
Input:	[char] or [boolean]/[switcher] zoom: 0/false/OFF = x1; 1/true/ON = x2
Output:	-
============================================================================= */
void SetSpritesZoom(char zoom);



/* =============================================================================
CLS 
Description: 
		 Clear Screen
		 Fill the Name Table with the value 0
		 Note: Does not clear the sprite attribute table (OAM)
Input:	-
Output:	-
============================================================================= */
void CLS(void);



/* =============================================================================
SortG2map 
Description: 
		Initializes the pattern name table, with sorted values. 
		Designed to be able to display a G2 (256x192px) image.
Input:	-
Output:	-
============================================================================= */
void SortG2map(void);



/* =============================================================================
SortMCmap 
Description: 
		Initializes the pattern name table, with sorted values. 
		Designed to be able to display a MC (64x48 blocks) image.
Input:	-
Output:	-
============================================================================= */
void SortMCmap(void);



/* =============================================================================
ClearSprites
Description: 
		Initialises the sprite attribute table (OAM). 
		The vertical location of the sprite is set to 209.
Input:	-
Output:	-
============================================================================= */
void ClearSprites(void);



/* =============================================================================
COLOR
Description:
		Specifies the ink, foreground and background colors.
		This function has different behaviors depending on the screen mode.
		In T1 (text) mode, the color change is instantaneous except the 
		border color which has no effect.
		In G1, G2 and MC modes, only the border color has an instant effect. 
		Ink and background colors are only used when starting the screen with 
		the SCREEN() function.

Input:	[char] ink color
		[char] background color
		[char] border color
Output:	-     
============================================================================= */
void COLOR(char ink, char background, char border);



/* =============================================================================
VPOKE
Description:
		Writes a value to the video RAM. 
		Warning!! The order of the values has been reversed to 
		optimize the function taking advantage of the new 
		Z80 calling conventions.
Input:	[char] value
		[unsigned int] VRAM address
Output:	- 
============================================================================= */
void VPOKE(char value, unsigned int vaddr);



/* =============================================================================
FastVPOKE
Description:
		Writes a value to the next video RAM position. 
		Requires the VDP to be in write mode, either by previously 
		using VPOKE or SetVRAMtoWRITE functions.
Input:	[char] value
Output:	- 
============================================================================= */
extern void FastVPOKE(char value);



/* =============================================================================
VPEEK
Description:
		Reads a value from video RAM. 
Input:	[unsigned int] VRAM address
Output:	[char] value
============================================================================= */ 
char VPEEK(unsigned int vaddr);



/* =============================================================================
FastVPEEK
Description:
		Reads the next video RAM value.
		Requires the VDP to be in read mode, either by previously 
		using VPEEK or SetVRAMtoREAD functions.
Input:	-
Output:	[char] value
============================================================================= */
extern char FastVPEEK(void);



/* =============================================================================
FillVRAM                               
Description:
		Fill a large area of the VRAM of the same byte.
Input:	[unsigned int] VRAM address
		[unsigned int] blocklength
		[char] Value to fill.
Output:	- 
============================================================================= */
void FillVRAM(unsigned int vaddr, unsigned int length, char value);



/* =============================================================================
CopyToVRAM
Description:
		Block transfer from memory to VRAM 
Input:	[unsigned int] Memory address
		[unsigned int] VRAM address
		[unsigned int] blocklength
Output:	- 
============================================================================= */
void CopyToVRAM(unsigned int addr, unsigned int vaddr, unsigned int length);



/* =============================================================================
CopyFromVRAM
Description:
		Block transfer from VRAM to memory
Input:	[unsigned int] VRAM address                     
		[unsigned int] RAM address
		[unsigned int] blocklength
Output:	-
============================================================================= */
void CopyFromVRAM(unsigned int vaddr, unsigned int addr, unsigned int length);



/* =============================================================================
GetVDP
Description:
		Provides the mirror value of a VDP register stored in system 
		variables.
Input:	[char] VDP register              
Output:	[char] Value
============================================================================= */
char GetVDP(char reg);



/* =============================================================================
SetVDP
Description:
		Writes a value to a VDP register
Input:	[char] VDP register (0-7)                    
		[char] value
Output:	-
============================================================================= */
void SetVDP(char reg, char value);



/* =============================================================================
SetVRAMtoREAD
Description:
		Enable VDP to read (Similar to BIOS SETRD)
Input:	[char] VRAM address
Output:	-
============================================================================= */
void SetVRAMtoREAD(unsigned int vaddr);



/* =============================================================================
SetVRAMtoWRITE
Description: 
		Enable VDP to write (Similar to BIOS SETWRT)
Input:	[char] VRAM address
Output:	-             
============================================================================= */
void SetVRAMtoWRITE(unsigned int vaddr);



#endif