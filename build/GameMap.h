
//{{BLOCK(GameMap)

//======================================================================
//
//	GameMap, 256x256@8, 
//	Transparent color : 00,00,00
//	+ palette 256 entries, not compressed
//	+ bitmap not compressed
//	Total size: 512 + 65536 = 66048
//
//	Time-stamp: 2024-01-08, 22:19:55
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GAMEMAP_H
#define GRIT_GAMEMAP_H

#define GameMapBitmapLen 65536
extern const unsigned int GameMapBitmap[16384];

#define GameMapPalLen 512
extern const unsigned short GameMapPal[256];

#endif // GRIT_GAMEMAP_H

//}}BLOCK(GameMap)
