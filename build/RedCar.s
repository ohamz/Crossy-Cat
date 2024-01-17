
@{{BLOCK(RedCar)

@=======================================================================
@
@	RedCar, 32x32@4, 
@	Transparent color : 00,FF,00
@	+ palette 256 entries, not compressed
@	+ 16 tiles not compressed
@	Total size: 512 + 512 = 1024
@
@	Time-stamp: 2024-01-08, 22:19:55
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global RedCarTiles		@ 512 unsigned chars
RedCarTiles:
	.word 0x00000000,0x00000000,0x00000000,0x10000000,0x10000000,0x21000000,0x21000000,0x21000000
	.word 0x42222222,0x42222222,0x42222222,0x21121122,0x21121122,0x11121122,0x11121122,0x11121122
	.word 0x00444444,0x00444444,0x00444444,0x04555512,0x04555512,0x45555121,0x45555121,0x45555121
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x22222220,0x22222220,0x22222220,0x22222222,0x22222222,0x11111221,0x11111221,0x11111221
	.word 0x22222222,0x22222222,0x22222222,0x42222222,0x42222222,0x22222222,0x22222222,0x22222222
	.word 0x42222222,0x42222222,0x42222222,0x22222244,0x22222244,0x21111122,0x21111122,0x21111122
	.word 0x00000444,0x00000444,0x00000444,0x00444442,0x00444442,0x04444422,0x04444422,0x04444422

	.word 0x13661122,0x13661122,0x13661122,0x36666112,0x36666112,0x36116111,0x36116111,0x36116111
	.word 0x22222221,0x22222221,0x22222221,0x12222221,0x12222221,0x11111111,0x11111111,0x11111111
	.word 0x11366112,0x11366112,0x11366112,0x13666611,0x13666611,0x13611611,0x13611611,0x13611611
	.word 0x54444512,0x54444512,0x54444512,0x45555422,0x45555422,0x55555511,0x55555511,0x55555511
	.word 0x36116110,0x36116110,0x36116110,0x36666000,0x36666000,0x33660000,0x33660000,0x33660000
	.word 0x11111111,0x11111111,0x11111111,0x03333303,0x03333303,0x00333000,0x00333000,0x00333000
	.word 0x13611611,0x13611611,0x13611611,0x33666600,0x33666600,0x03366000,0x03366000,0x03366000
	.word 0x55555511,0x55555511,0x55555511,0x00333330,0x00333330,0x00033300,0x00033300,0x00033300

	.section .rodata
	.align	2
	.global RedCarPal		@ 512 unsigned chars
RedCarPal:
	.hword 0x0000,0x7F99,0x20F8,0x1CC5,0x2D7E,0x7FFF,0x2907,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(RedCar)
