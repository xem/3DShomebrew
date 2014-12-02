/** ========================================================================================================**/
/**                                                 Graphics                                                **/
/** ========================================================================================================**/


void gfxDrawSprite(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y) {
  //This function includes documantation so you might be able to figure out what the function is doing, you don't need to understand this to use it!
  if(!spriteData)return; //check if the function has sprite data, if not stop!

  u16 fbWidth, fbHeight; //set variables for width and height
  u8* fbAdr = gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight); //get framebuffer for the screen and side used.

  if(x + width < 0 || x >= fbWidth)return; //check invalid x cords
  if(y + height < 0 ||y >= fbHeight)return; //check invalid y cords

  u16 xOffset = 0, yOffset = 0; //set offset for x and y
  u16 widthDrawn = width, heightDrawn = height; //set width/height vars that for drawing

  if(x < 0) xOffset = -x; //use offset
  if(y < 0) yOffset = -y; //use offset
  if(x + width >= fbWidth) widthDrawn = fbWidth - x;
  if(y + height >= fbHeight) heightDrawn = fbHeight - y;
  widthDrawn -=xOffset;
  heightDrawn -=yOffset;

  int j;
  for(j = yOffset; j < yOffset + heightDrawn; j++) { //for loop for drawing image
    memcpy(&fbAdr[ ((x + xOffset) + (y + j) * fbWidth) * 3 ], &spriteData[ ((xOffset + j) * width) * 3 ], widthDrawn * 3); //copy imagedata into memory
  }
}

void gfxDrawSpriteAlpha(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y) {
  if(!spriteData)return;

  u16 fbWidth, fbHeight;
  u8* fbAdr = gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);

  if(x + width < 0 || x >= fbWidth)return;
  if(y + height < 0 || y >= fbHeight)return;

  u16 xOffset = 0, yOffset = 0;
  u16 widthDrawn = width, heightDrawn = height;

  if(x < 0)xOffset = -x;
  if(y < 0)yOffset = -y;
  if(x + width >= fbWidth) widthDrawn = fbWidth - x;
  if(y + height >= fbHeight)heightDrawn = fbHeight - y;
  widthDrawn -=xOffset;
  heightDrawn -=yOffset;

  //TODO : optimize
  fbAdr += ( y + yOffset) * fbWidth * 3;
  spriteData += yOffset * width * 4;
  int j, i;
  for(j = yOffset; j < yOffset + heightDrawn; j++) {
    u8* fbd = &fbAdr[ (x + xOffset) * 3 ];
    u8* data = &spriteData[ xOffset * 4 ];
    for(i = xOffset; i < xOffset + widthDrawn; i++) {
      if(data[3]) {
        fbd[0] = data[0];
        fbd[1] = data[1];
        fbd[2] = data[2];
      }
      fbd +=3;
      data +=4;
    }
    fbAdr += fbWidth * 3;
    spriteData += width * 4;
  }
}

void gfxDrawSpriteAlphaBlend(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y) {
  if(!spriteData)return;

  u16 fbWidth, fbHeight;
  u8* fbAdr = gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);

  if(x + width < 0 || x >= fbWidth)return;
  if(y + height < 0 || y >= fbHeight)return;

  u16 xOffset = 0, yOffset = 0;
  u16 widthDrawn = width, heightDrawn = height;

  if(x < 0)xOffset = -x;
  if(y < 0)yOffset = -y;
  if(x + width >= fbWidth) widthDrawn = fbWidth - x;
  if(y + height >= fbHeight)heightDrawn = fbHeight - y;
  widthDrawn -=xOffset;
  heightDrawn -=yOffset;


  //TODO : optimize
  fbAdr += (y + yOffset) * fbWidth * 3;
  spriteData += yOffset * width *4;
  int j, i;
  for(j = yOffset; j < (yOffset + heightDrawn); j++) {
    u8* fbd = &fbAdr[ (x + xOffset) * 3 ];
    u8* data = &spriteData[ xOffset * 4 ];
    for(i = xOffset; i < xOffset + widthDrawn; i++) {
      if(data[3]) {
        u8 alphaSource = data[3];
        fbd[0] = ((data[0] * alphaSource)+(fbd[0] * (255 - alphaSource))) / 256;
        fbd[1] = ((data[1] * alphaSource)+(fbd[1] * (255 - alphaSource))) / 256;
        fbd[2] = ((data[2] * alphaSource)+(fbd[2] * (255 - alphaSource))) / 256;
      }
      fbd +=3;
      data +=4;
    }
    fbAdr += fbWidth * 3;
    spriteData += width * 4;
  }
}
