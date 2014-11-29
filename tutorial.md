#3DS homebrew development tutorial

##Summary
- [Is it legal?](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md/blob/gh-pages/tutorial.md#is-it-legal)
- [Setup](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md/blob/gh-pages/tutorial.md#setup)
  - [Hardware](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#hardware)
  - [Computer setup](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#computer-setup)
  - [3DS setup](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#3ds-setup)
  - [Homebrew installation](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#homebrew-installation)
- [Anatomy of a homebrew project](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#anatomy-of-a-homebrew-project)
  - [Basics](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#basics)
  - [Build procedure](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#build-procedure)
- [Homebrew development](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#homebrew-development)
  - [Hello template](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#hello-template)
  - ...
  - ...
  - ...

##Is it legal?

Yes, reverse-engineering a video game console and making homebrew software for it is 100% legal.<br>
The only thing that is illegal is piracy.<br>
This project doesn't encourage you to pirate 3DS games (which is impossible using NINJHAX).<br>
It is only here to help you develop homebrews, so don't worry and have fun!

##Setup

###Hardware

Here's what you need to buy to get started:

- A Nintendo 3DS / 2DS with a firmware version between 4.0.0-7 and 9.2.0-20 + a SD card.<br>
or <br>
- A New 3DS with a firmware between 9.0.0-20 and 9.2.0-20 + a micro SD card.
- An SD / microSD card reader.
- A copy of the 3DS game "Cubic Ninja" (new or used). It has in the same region as your 3DS (Europe, USA or Japan).

Note: the Gateway 3DS flashcard can also launch homebrews, but only in .3ds and .cia formats.<br>
This tutorial will focus on .3dsx homebrews, compatible with Ninjhax + hbmenu.

###Computer setup

Here's what you need to install on your computer:

- The latest version of [DevkitPro](http://devkitpro.org). You can do a full install, or install only DevkitARM + ctrulib.
- Download [Aemstro](https://github.com/smealum/aemstro) and place its content "msys", inside your devkitPro install folder. (ex: ````C:\devkitPro\msys````)
- A C++ compatible IDE like [Netbeans](https://netbeans.org/downloads), or a code editor, like [notepad++](http://notepad-plus-plus.org).
- An FTP client like [FileZilla](https://filezilla-project.org) or [WinSCP](http://winscp.net) to upload homebrews  on your 3DS using wi-fi. (optional)
- An image editor like [GIMP](http://www.gimp.org/) to create images for your homebrews. (optional)
- Latest version of [Python 3.x.x](https://www.python.org)

Windows users: check your environment variables:

- Right-click "This PC" and select "Properties".
- Click "Advanced system settings" (on the left).
- Click "Environment Variables..." (on the bottom).
- Highlight the "PATH" variable (on top), click "Edit...".
- Check that your DevkitARM and Python install folders are present (ex: "C:\DevkitPro\DevkitARM\bin", "C:\Python34").
- If one (or both) are not present, add them at the end, saparated by ";". Save and quit.

Linux users: you'll find more setup info on [3Dbrew](http://3dbrew.org/wiki/Setting_up_Development_Environment) 

###3DS setup

Follow these steps to install the homebrew launcher (hbmenu) on your 3DS (this needs to be done only once):

- Download [Ninjhax's homebrew starter kit](http://smealum.net/ninjhax/dl/starter.zip) and unzip it at the root of your SD / microSD card.
- Insert the SD / microSD card in your console.
- Go on Ninjhax's website and [generate the QR code corresponding to your console's firmware](http://smealum.net/ninjhax/#qrcode). (you can find your firmware version in the "Settings" app, on the upper screen.)
- Enable your 3DS' wi-fi connection.
- Start the game Cubic Ninja, choose "Create", then "QR code", and finally "Scan QR code". 
- Scan the QR Code, then follow on-screen instructions to enable the exploit and start hbmenu.

The next time you turn your console on, just launch Cubic Ninja, choose "Create", then "QR code" and hbmenu will start directly.

<img src="http://img.ctrlv.in/img/14/11/22/54709c512ae72.png" width=400>

To uninstall Ninjhax (or install it on another console), you need to delete your save file.<br>
(go to Cubic Ninja's main menu and press L+R+X+Y)

###Homebrew installation

Two files are needed for a 3DS homebrew to be run with Ninjhax: a .3dsx file and a .smdh file.

If you want to launch homebrews on your console, or test your own builds easily, you can use your computer to place them in the "3ds" folder of your SD / microSD card.

Note: you can create subfolders in your 3ds folder to organize your homebrews.

You can also upload them directly using wi-fi:
1. Start hbmenu.<br>
2. Start the ftPONY homebrew.<br>
3. Note the IP and port displayed on the upper screen (for example: "IP: 192.168.0.128 port 5000")<br>
4. Start a FTP client on your desktop, and use these credentials to get connected.<br>
5. If asked, choose "anonymous connection".<br>
6. You should now see your SD / microSD card's filesystem and be able to drag & drop files and folders in the "3ds" folder of your card.<br>
7. Press B to quit ftPONY and launch your new apps.
<img src="http://img.ctrlv.in/img/14/11/22/54709afe2f047.png" width=700>

If you are running linux (or have cat and netcat on windows/mac) you can also use NetLoader:<br>
1. Start hbmenu<br>
2. Press the Y button<br>
3. On your PC open a terminal (or command promt when using Windows)<br>
4. Browse to the directory your .3dsx file is located in. (using cd foldername to go into a folder and cd.. to go back from a subfolder)<br>
5. use the command: ````cat name.3dsx | nc ip 9000```` Where you replace "name.3dsx" with your .3dsx file and ip with the IP displayed on the 3DS' bottom screen.<br>
6. After a little bit of time (depending on the filesize of your .3dsx) it will automaticly boot your homebrew.<br>
Note: Both the PC and 3DS have to be connected in the same network for this to work! This is only useful for testing as the file won't stay on the 3DS after it is closed. (External files your homebrew might try to load has to already be on the SD card!)<br>

##Anatomy of a homebrew project

Please download (or clone) smea's [ctrulib project](https://github.com/smealum/ctrulib) on your computer. (For example in C:/3DS/ctrulib)

###Basics

Let's take a look at ctrulib's project template (in the template folder).
<br>It's a minimal project that does nothing else than printing a white pixel on the upper screen.

It contains:

- a source folder, containing a main.c file. (the source code of your homebrew)
- a makefile file (allowing to build your homebrew for hbmenu)

Let's see how bigger projects are made, for example [Yeti3DS](https://github.com/smealum/yeti3DS). You can notice a few other things:

- an icon.png file (a 48x48px image to display on hbmenu instead of the default one) 
- the source folder contains more .c files and .h files. (those files are used to organize big C/C++ project.<br>Note that the main function ````int main()```` remains in main.c, the other C files are used to store additional code and data called by ````main````).
- The makefile contains [three optional lines](https://github.com/smealum/yeti3DS/blob/master/Makefile#L40-L42) to specify the game's author, title and description.

In many projects, like [3dscraft](https://github.com/smealum/3dscraft) you can find a data folder containing .bin files.<br>These files are used to store images data. The tutorial will explain how to use them in your projects.

###Build procedure

Let's go back to our ctrulib/template folder.

- Open a CLI (command line interface). If you're on Windows, press Shift + right click on the template folder and choose "Open a CLI here".
- type ````make```` and press enter.
- After a few seconds, the process finishes and you can find a build folder (you can ignore it) and two new files .3dsx and .smdh. You can copy them to your SD card to test the homebrew on real hardware.
- You can rebuild those files at any time after editing your source code. You'll need to run ````make clean```` before rebuilding your project.

You can now try to build all ctrulib examples (or other open source homebrew projects) and run them on your 3DS.
<br>
Please note that some examples (like http) may not be buildable yet, and some others (like gpu) don't work on hbmenu yet.


##Homebrew development

Please download the following file: [project template](http://xem.github.io/3DShomebrew/tutorial/template.zip).
<br>
It's based on ctrulib's template project but cleaner and more complete. (logo, metadata)

Note: unless you want to edit the makefile by hand, you should put all of your source and header files in the source folder. The makefile does not account for subfolders, and will not compile code that reside in one.

Unzip the template on your computer (For example in C:/3DS/template) and ton't touch it. It will be the model for our upcoming projects.
<br>
In this tutorial, we will develop small programs based on this template.
<br>
We won't start with an "Hello World!", but just a few steps earlier than that.

### Hello template!

Let's open the source folder of our project template, and take a look at main.c's source code, as well as its comments (starting with ````//````)

````C
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
````

That's the minimal homebrew you could imagine. As you may have guessed, it does the following:
- include 3ds.h (a library made to easily access 3DS's hardware with code),
- initialize various things (screens, inputs, etc.). Homebrews could not do much without that,
- Start an infinite loop (each iteration represents a frame, so unless your program is very slow, this loop will restart every ~1/60 seconds.
- In each iteration:
  - We wait for the screen to be ready (i.e. the end of the last 1/60 of a second),
  - We "read" which buttons are currently pressed and exit the infinite loop if START is pressed.
  <br>(NB: breaking the infinite loop with START is not mandatory, but it's becoming the standard way to quit homebrews),
  - Swap and flush current framebuffers.
- After the loop, un-iitialize all that and return 0, to get back to hbmenu.

But what are frame buffers, and what does it mean to "flush" and "swap" hem at every frame? Answer soon!

### Hello pixel!

### Hello image!

### "Hello world!"

### Hello stereoscopy!

### Hello animation!

### Hello buttons!

### Hello touchscreen!

### Hello sound!

### Hello microphone!

### Hello filesystem!

### Hello Internet!

### Hello Gyroscope!

### Hello Infrared communication!

### Hello NFC!

### Hello Camera(s)!

### Hello Battery, 3D slider, luminosity, etc


Coming soon!
