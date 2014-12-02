#3DS functions

A collection of handy functions created by our contributors or inspired by other 3DS projects

##Browse



##Download & install

- Download [functions.zip](https://github.com/xem/3DShomebrew/blob/gh-pages/functions/functions.zip)
- Unzip it in your project's source folder
- Write ````#include "functions.h"````  at the beginning of your source code, just after 3ds.h.
- Use the  functions in your code.

Alternatively, you can [browse the source code](https://github.com/xem/3DShomebrew/blob/gh-pages/functions/functions) and copy what you need in your project.

##API

###Graphics

````
void gfxDrawSprite(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y);

void gfxDrawSpriteAlpha(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y);

void gfxDrawSpriteAlphaBlend(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y);
````
