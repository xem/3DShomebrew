#include <3ds.h>

int main()
{
	// Initialize services
	srvInit();      // mandatory
	aptInit();      // mandatory
	hidInit(NULL);  // input (buttons, screen)
	gfxInit();      // graphics
  
  // Uncomment next line to enable stereoscopic 3D
  // gfxSet3D(true);
  
  // Initialize pressed keys data
  u32 kDown;
  
	// Main loop
	while (aptMainLoop())
	{
		// Wait next screen refresh
    gspWaitForVBlank();

    // Read which buttons are currently pressed 
		hidScanInput();
    kDown = hidKeysDown();
    
		// If START is pressed, break loop and quit
		if (kDown & KEY_START){
			break;
    }

		
    
    /** Your code goes here **/
    
    


		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	// Exit services
  gfxExit();
	hidExit();
	aptExit();
	srvExit();
  
  // Return to hbmenu
	return 0;
}
