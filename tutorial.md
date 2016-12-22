#3DS homebrew development tutorial

[Return to homepage](http://goo.gl/CLdz5Q)

##Introduction

This document will explain in detail how to develop homebrews (applications / games) for Nintendo 3DS, 2DS and New 3DS.
<br>We will code them in C/C++, with [ctrulib](https://github.com/smealum/ctrulib)'s help, and play them with [Ninjhax](http://smealum.net/ninjhax) and [hbmenu](https://github.com/xem/3ds_hb_menu).
<br>Basic notions of programming are required, even if they come from another language (Java, PHP, JS, ...).
<br>Note that the 3DS homebrew scene is very young, and many things are still impossible to do. (see the [limitations page](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md/blob/gh-pages/tutorial/limitations.md)).
<br>But we're here to make it as simple as possible!

##Summary

- [Is it legal?](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md/blob/gh-pages/tutorial.md#is-it-legal)
- [Setup](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md/blob/gh-pages/tutorial.md#setup)
  - [Hardware](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#hardware)
  - [Computer setup](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#computer-setup)
  - [3DS setup](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#3ds-setup)
  - [Homebrew installation](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#homebrew-installation)
- [Homebrew development](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#homebrew-development)
  - [Hello template!](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#hello-template)
  - [Hello build procedure!](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#hello-build-procedure)
  - [Hello source code!](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#hello-source_code)
  - [Hello Screens, VRAM and framebuffers!](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#hello-screens-vram-and-framebuffers)
  - [Hello pixel!](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#hello-pixel)
  - [Hello Buttons!](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#hello-buttons)
  - ...
  - ...
  - ...

##Is it legal?

Yes, reverse-engineering a video game console and making homebrew software for it is 100% legal.<br>
The only thing that is illegal is piracy, but pirating 3DS retail or eShop games is impossible with Ninjhax.<br>
This tutorial is only here to help you develop and play 3DS homebrews, so don't worry and have fun!

##Setup

###Hardware

Here's what you need to get started:

- A Nintendo 3DS / 3DS XL / 2DS with a firmware version between 4.0.0-7 and 9.2.0-20 + a SD card.<br>
or <br>
- A New 3DS with a firmware between 9.0.0-20 and 9.2.0-20 + a micro SD card.
- An SD / microSD card reader.
- A copy of the 3DS game "Cubic Ninja". It has to be in the same region as your 3DS (Europe, USA or Japan).

Note: the Gateway 3DS flashcard can also launch homebrews, but only in .3ds and .cia formats.<br>
This tutorial will focus on .3dsx homebrews, compatible with Ninjhax + hbmenu.

###Computer setup

Here's what you need to install on your computer:

- The latest version of [DevkitPro](http://devkitpro.org). You can do a full install, or install only DevkitARM + ctrulib.
- Download [Aemstro](https://github.com/smealum/aemstro) and place its content in "msys", inside your devkitPro install folder. (ex: ````C:\devkitPro\msys````)
- A C++ compatible IDE like [Netbeans](https://netbeans.org/downloads), or a code editor like [notepad++](http://notepad-plus-plus.org).
- An FTP client like [FileZilla](https://filezilla-project.org) or [WinSCP](http://winscp.net) to upload homebrews  on your 3DS using wi-fi.
- Latest version of [Python 3](https://www.python.org).
- Create a working directory. (for example ````C:\3DS````). All our projects will go in here.

Linux users: you'll find more setup info on [3Dbrew](http://3dbrew.org/wiki/Setting_up_Development_Environment).

###Homebrew Channel installation

Follow these steps to install the homebrew launcher (or "hbmenu") on your 3DS. This needs to be done only once:

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

###Deploying your code to the 3DS

Two files are needed for a 3DS homebrew to be run with Ninjhax: a .3dsx file and a .smdh file.

If you want to run homebrews on your console, you can use your computer to place them in the "3ds" folder of your SD / microSD card.<br>
Note: you can organize your homebrews into subfolders.

You can also upload them directly using wi-fi, if your PC and 3DS are connected to the same local network:

1. Start hbmenu.
2. Start the ftPONY homebrew.
3. Note the IP and port displayed on the upper screen (for example: "IP: 192.168.0.128 port 5000")
4. Start a FTP client on your desktop, and use these credentials to get connected.
5. If asked, choose "anonymous connection".
6. You should now see your SD / microSD card's filesystem and be able to drag & drop files and folders in the "3ds" folder of your card.
7. Press B to quit ftPONY and launch your new apps.

<img src="http://img.ctrlv.in/img/14/11/22/54709afe2f047.png" width=700>

For Linux users, or Windows / Mac users using cat or netcat:

1. Download the latest version of [hbmenu](https://github.com/smealum/3ds_hb_menu), build it and install it on your SD card.
2. Start hbmenu
3. Press the Y button
4. On your PC open a terminal (or command promt when using Windows)
5. Browse to the directory your .3dsx file is located in.
6. use the command: ````cat name.3dsx | nc ip 9000```` Where you replace "name.3dsx" with your .3dsx file and ip with the IP displayed on the bottom screen.
7. After a little bit of time (depending on the filesize of your .3dsx) it will automatically boot your homebrew.

Note: This is only useful for testing as the file won't stay on the 3DS after it is closed.

###Updates

Frameworks, libraries and popular homebrews are regularly updated by their authors, to fix bugs or to add new features.
<br>We advise you to frequently check if a new version of DevkitPro + ctrulib or Ninjhax + hbmenu is available, and install it!

##Homebrew development

First, download the following file and unzip it in your working directory: [project template](http://xem.github.io/3DShomebrew/tutorial/template.zip).
<br>You can also browse its content [here](https://github.com/xem/3DShomebrew/tree/gh-pages/tutorial/template).
<br>During this tutorial, we will develop small programs based on this template.

### Hello template!

The template folder, like most 3DS projects, contains:
- a source folder, containing a main.c file. (the source code of our homebrew).
- a data folder, that will be used to store our program's assets (images, music, ...).
- an icon.png file (a 48x48px image to display on hbmenu).
- a makefile file (used to build our homebrew).

### Hello build procedure!

We will now see how to build our project.
<br>("building" consists of generating the files that will be played on your console)

- Open a CLI (command line interface). If you're on Windows, press Shift + right click on the template folder and choose "Open a command line interface here".
- type ````make```` and press enter.
- After a few seconds, the process finishes.
- A "build" folder, and three files (.elf, .3dsx and .smdh) appear.
- Copy the .3dsx and the .smdh files on your SD card to test the homebrew on real hardware.

When you will work on your own projects, note that you can rebuild them at any time to test your changes:

- run the ````make clean```` command. (this will erase the build files)
- run the ````make```` command again.

Similarly, you can build any homebrew open-source project by opening a CLI in the folder containing its "Makefile" and executing the command ````make````.

Windows users: if you get compilation errors during the build, check your environment variables:

- Right-click "This PC" and select "Properties".
- Click "Advanced system settings" (on the left).
- Click "Environment Variables..." (on the bottom).
- Highlight the "PATH" variable (on top), click "Edit...".
- Check that your DevkitARM and Python install folders are present (ex: "C:\DevkitPro\DevkitARM\bin", "C:\Python34").
- If one (or both) are not present, add them at the end, saparated by ";". Save and quit.

### Hello source code!

Let's open source/main.c and analyse its contents:

````C
#include <3ds.h>

int main()
{
  // Initializations
  srvInit();        // services
  aptInit();        // applets
  hidInit(NULL);    // input
  gfxInit();        // graphics
  gfxSet3D(false);  // stereoscopy (true: enabled / false: disabled)
  u32 kDown;        // keys down
  u32 kHeld;        // keys pressed
  u32 kUp;          // keys up

  // Main loop
  while (aptMainLoop())
  {

    // Wait for next frame
    gspWaitForVBlank();

    // Read which buttons are currently pressed or not
    hidScanInput();
    kDown = hidKeysDown();
    kHeld = hidKeysHeld();
    kUp = hidKeysUp();

    // If START button is pressed, break loop and quit
    if (kDown & KEY_START){
      break;
    }


    /** Your code goes here **/


    // Flush and swap framebuffers
    gfxFlushBuffers();
    gfxSwapBuffers();
  }

  // Exit
  gfxExit();
  hidExit();
  aptExit();
  srvExit();

  // Return to hbmenu
  return 0;
}
````

That's the minimal homebrew you could imagine.
<br>It's not very useful yet (it just keeps the screens black until we press START to exit.) but it will be soon!
<br>As you may have guessed, it does the following things:
- include 3ds.h (a library made to easily access 3DS's hardware with code).
- initialize various things (services, applets, inputs, graphics...). Homebrews could not do much without those.
- Start an infinite loop (each iteration represents a frame, and up to 60 frames are displayed per second.
- In each iteration:
  - We wait for the screen to be ready.
  - We "read" which buttons are currently pressed. If START is pressed, we quit the infinite loop.
  <br>(NB: pressing START is becoming the standard way to quit homebrews, but of course you can change this behavior),
  - Swap and flush current framebuffers (we'll explain that later).
- After the loop, we unload everything and ````return 0````, to get back to hbmenu.


### Hello Screens, VRAM and framebuffers!

In a previous chapter, we talked about framebuffers. We will now see what this means.
<br>The 3DS VRAM (video memory) holds the image information of three screens:

- The top-left screen (the image sent to your left eye in stereoscopic (3D) mode; also used in 2D mode).
- The top-right screen (the image sent to your right eye in stereoscopic mode; unused in 2D mode).
- The bottom screen (2D only)

For each screen, there is room in the VRAM for two images, called "framebuffers", of "fb0 / fb1" for short.
<br>The two framebuffers replace each other at each frame (60 times per second):
- when fb 0 is displayed on a screen, fb1 is pre-rendered for the next frame.
- on the next frame, fb0 is reset, fb1 is displayed on screen and fb0 is pre-rendered for next frame.
- on the next frame, fb1 is reset, fb0 is displayed on screen and fb1 is pre-rendered for next frame.

etc, etc...
<br>
to vulgarize, let's just say that the 3DS does this under the hood, at each frame and for each screen, while your code puts the ink on the next paper :)

<img src="http://i1238.photobucket.com/albums/ff492/machineking0011/1235471162_duckrabbitseason.gif">

That's why we flush (reset) and swap the buffers at the end of the main loop. It allows the homebrew's code to always draw the next frame without risking to alter what is currently on screen.

In the VRAM, framebuffers store the color information of each pixel of the screen.
<br>Each pixel color is a mix of Red, Green and Blue (the primary colors for screens).
<br>Each primary color is stored on one byte (its value goes from 0 to 255).
<br>Top screens' framebuffers take 400 x 240 x 3 bytes, and the bottom screen's framebuffers take 320 x 240 x 3 bytes.

But it's not that simple:
- By default, the pixels colors are stored in reverse order (B,G,R instead of R,G,B).
- In the VRAM, all the screens are rotated by -90 degrees, as if you turned your 3DS to look at it from the right side.

To sum up, on each screen, both framebuffers use 3 bytes to store Blue, Green and Red components of each pixel, starting from the bottom-left pixel and going through each column from bottom to top until it reaches the top-right pixel.

### Hello pixel!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello image!

Displaying images or sprites is a vital part of most 2D games and applications. The functions to render images to the screen can be hard to comprehend but luckily enough they've been made for us and they are easy to use.

Images used in 3DS homebrews are usually in a .bin format, you can get an image in this format by either exporting the image as raw data (BGR or ABGR format) or using the <a href="http://xem.github.io/3DShomebrew/tools/image-to-bin.html">image to BIN</a> web tool. The web tool allows you to convert your image and rotate it 90 degrees clockwise, in order to show them the right way up on the 3DS itself.

You can try to develop image-rendering functions by yourself, or use directly the ones present in [our functions collection](https://github.com/xem/3DShomebrew/blob/gh-pages/functions.md). Copy those files in your project and include them with ````#include <functions.h>```` in your main.c file, after 3ds.h inclusion.

To include images in your project:
- Place your BIN files in the "data" folder.
- Include each image's definition in your source code. For example, with "my_image.bin", add ````#include "my_image.h"```` in main.c, after functions.h inclusion. (this .h file doesn't exist yet, but it will be created during build).

- ````gfxDrawSprite```` is the functions you'll be using for displaying images that <b>do not</b> have transperancy in them:
- ````gfxDrawSpriteAlpha```` is the function you'll be using for images with transparency (if you don't want to blend with the background):
- ````gfxDrawSpriteAlphaBlend```` is the function used for transperancy and blending with the background.

The parameters are:
- Screen: the screen to use (use the constant GFX_TOP or GFX_BOTTOM)
- Side: which "side" of the stereoscopic screen to use (GFX_LEFT or GFX_RIGHT for top screen, 0 for bottom screen)
- Spritedata: the content of your image in BGR format (for gfxDrawSprite) and ABGR (for the others): use "(u8*)name_of_your_bin_file". (the (u8*) part means that the BIN file is read as a bytes array).
- Width, height, x, y: the size and position of your image on the screen. 

Remember: the point {X=0;Y=0} is the left-bottom corner of the screen, because it's rotated -90 degrees.

Example: ````gfxDrawSprite(GFX_TOP, GFX_LEFT, (u8*)image_bin, 100, 100, 10, 10);````.
<br>This will render an image to the top left screen, with a width and height of 100 pixels and located at 10 pixels from the bottom and left side of the screen.

<!-- TODO: include example with each kind of image rendering -->

### Hello buttons!

Buttons are very important for most homebrew applications, and they are pretty simple to use.

The template code already does the following operations:

- Initialize the HID (Human Input Device) service, with ````hidInit(NULL);````.
- Create the variables ````kDown````, ````kHeld```` and ````kUp```` to hold the state of all the inputs.
- Scan the HID at every frame, with ````hidScanInput()```` and update these variables.
- Exit with ````hidExit();```` at the end of the program.

Three variables are used to store the state of the buttons:

- kDown represents the buttons that are pressed, but weren't pressed the frame before.
- kHeld represents the buttons that are pressed, and were also pressed the frame before.
- kUp represents the buttons that are not pressed, but were pressed the frame before.

Ctrulib provides a handy list of constants for us to access each button in kDown, kHeld and kUp:

````
KEY_SELECT    // Select Button
KEY_START     // Start Button
KEY_DRIGHT    // Right key on D-Pad (the directional stick on the left)
KEY_DLEFT     // Left key on D-Pad
KEY_DUP       // Up key on D-Pad
KEY_DDOWN     // Down key on D-Pad
KEY_R         // R Button
KEY_L         // L Button
KEY_A         // A Button
KEY_B         // B Button
KEY_X         // X Button
KEY_Y         // Y Button
KEY_ZL        // ZL Button (new 3DS only)
KEY_ZR        // ZR Button (new 3DS only)
KEY_TOUCH     // Touch screen
````

Note that the HOME button, the POWER button and the right circle pad of the New 3DS aren't present here. We will explain how to read them in a future chapter.

Here are a few examples of code that you can write to handle user input:

````
if (kDown & KEY_A){
  // code for when A is pressed
}

if (kHeld & KEY_B){
  // Code for when B is being held
}

if (kUp & KEY_START){
  // Code for when start is released
}
````

They compare the current key state vars with the constant of the button we want to check, using a bit mask.
<br>
If the corresponding button is down / held / up, the test succeeds, and the following code is executed.

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### "Hello world!"
While I've only technically tried compiling this with C++, it should be easily translatable to regular C.

Remember, you can always use Citra after compiling to test your program. (Excluding socket programming as of Sept 9th, 2016, Citra has a bug where it's unable to properly do socket programming. Be sure to check and see if this is still the case, though.)

 - Let's begin -

First, let's put in our regular includes and start our main function
````
#include <stdio.h>
#include <3ds.h>

int main() {
 // code goes here
}

````

Alright, perfect! Now lets actually get something done. Let's actually initialize our console so we can actually put text on the screen.

````

#include <stdio.h>
#include <3ds.h>

int main() {
  //Allows for graphics (Needed for console Init)
	gfxInitDefault();
	
	consoleInit(GFX_TOP, NULL); //Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.
}
````

And just like that, we now have our program ready for text to appear! In later portions of the tutorial, we'll be discussing how to use the bottom screen as a keyboard to input text. For now, however, feel free to experiment with making either the top and bottom of the screen a command console.

Alright, now we've initiated the ability to put text on the screen, let's go a step further. and actually print "Hello World" to the screen? Revolutionary, right? 

````
#include <stdio.h>
#include <3ds.h>

int main() {
  //Allows for graphics (Needed for console Init)
	gfxInitDefault();
	
	consoleInit(GFX_TOP, NULL); //Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.
	
	printf("Hello World!");
}
````

We did it! We've finally put "Hello World" on the screen. However, as you've probably noticed, if we ended the program here, it'd probably either crash, not compile, or something else due to the fact that:

1) We haven't made it a loop so the program runs continously

2) Haven't returned 0, as this is "int main()"

So let's solve these problems right now.

````

#include <stdio.h>
#include <3ds.h>

int main()
{
    // Allows to take inputs (Specifically the start button for our case)
    hidInit();
    hidScanInput();

    //Tells us when a key is pressed down
    u32 kDown = hidKeysDown();

    //Allows for graphics (Needed for console INit)
	gfxInitDefault();

	//gfxSet3D(true); //Uncomment if using stereoscopic 3D
	consoleInit(GFX_TOP, NULL); //Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.

	printf("Hello World");

	// Main loop
	while (aptMainLoop())
	{
		if (kDown & KEY_START)
			break; //Break in order to return to hbmenu

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}

````

And we're now done! As you might have noticed, there's some functions in there that I haven't gone over. What's with those "gfx\[name\]()" functions and why do we have them?

For some of the functions we init, including many of the ones coming up such as sockets, they require that any that you init() must be Exit().

For the FlushBuffers and SwapBuffers functions, you can read about them here: https://smealum.github.io/ctrulib/gfx_8h.html
While knowing what they do exactly isn't all that important, it is important that you have them in your program.

There's even more we could do! For example:
````
	printf("\x1b[0;0H[This Prints on the first line]");
	printf("\x1b[1;0H[This prints on the second line!]");
````

By using the string "\x1b[0;0H" we can manipulate what line our text comes on. This is useful for a variety of reasons. If we were to have our printf inside our endless loop, it would endlessly print lines of code. In the future, we'll need the ability to clear and printf on our screen repeatedly. By having the ability to pick which line gets printed, we can have consistency.

If we use C++ features and for-loops, we could have an entire string vector and print out text

````
std::vector<std::string> chatMessages; //Just pretend it's already populated

//30 total lines (from 0 to 29)
for(int i = 0; i < chatMessages.size(); i++) {
  //We want to reserve the first 5 lines for some reason, such as keeping instructions on. Hence the (i+5)
    printf("\x1b[%d;0H%s", (i+5), chatMessages[i].c_str()); // Notice we have %d where we originally put "0" and "1" in the printf above. Put %s from the string array, and converted it into a C string to prevent errors with printf
    if(i >= 23) {
    //As we do have a maximum amount of console lines to work with, we simply clear out the array and start again
        i = 0;
    }
  }

````

But we'll use this moreso when we get to socket programming, rather than here. So don't worry about the code above too much just yet.


For conviency, having the kDown and KEY_START breaking the loop back to the homebrew menu makes everything much easier.

-VSMS
<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello Typing!

Alright, now we're able to put text on the screen. But what if we want a user to put their own text?
You're in luck! As there's already a library for this, it doesn't require too much extra information on our end in order to add a keyboard.

HBKBLib: https://gbatemp.net/threads/hbkblib-a-3ds-keyboard-library.397568/

This is the library we'll be using. Best part of it is, the demo inside already has a compiled version of the library, so we really don't even have to worry about compiling it ourselves! It is definitely preferred that you compile it yourself, however. I had a lot of trouble getting it to compile, so I simply decided to use the precompiled version. Doing so gave me compile errors later on that we'll be able to fix, but if you compile it yourself initially, you could probably avoid the headache.

 - Let's begin -

Due to how the devkitpro compiler and makefile works, it's paramount that you have both HBKB's "include" and "lib" folders are inside of the "libs" folder on your project's main directory. Furthermore, we need to make adjustments to the actual makefile to make sure the hbkb library is included. The -lhbkb is what's important.

Example:
````
LIBS: -lctru -lm -lhbkb 
````

As stated earlier, YOU MAY HAVE PROBLEMS IF YOU USE THE PRECOMPILED VERSION OF THE HBKB LIBRARY. If so, please use
````
-D_GLIBCXX_USE_CXX11_ABI=0 
````
in either your cflags or your cxx flags. I have it in my CXX flags because I largely use C++ for most of my projects. Again, ONLY USE THAT IF YOU HAVE COMPILING ISSUES.

Alright, now that the files are in the correct folders, and those folders are in the correct libs folder, and we've made the proper changes to the makefile, it's finally time to begin writing our program.

HBKB comes with it's own demo file, and I'll largely be using that (with some modifications) for the basis of this example.

Again, I mainly write this code to work for C++, but unlike the previous section, this might either NOT be backwards compatible, or difficult to convert into backwards compatibility with regular C.

````
//Blablabla use in every program
#include <3ds.h>
#include <stdio.h>
#include <string>

//ONLY INCLUDE THIS IF YOU'RE HAVING COMPILING ISSUES
//#define _GLIBCXX_USE_CXX11_ABI 0/1

//The actual keyboard library
#include "hbkb.h"

int main() {

	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	// Keyboard Class
	HB_Keyboard sHBKB;

	printf("\x1b[0;0HHB_Keyboard Library Demo.");
	printf("\x1b[1;0HPress Start to exit.");

	while (aptMainLoop())
	{
		//Scan Inputs
		hidScanInput();
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) 
			break;

}
````
So far, we've only seen two unique lines of code. Let's disect them.


````
//The actual keyboard library
#include "hbkb.h"
````
Pretty self-explanatory. Includes the library we're going to be using.


````
	HB_Keyboard sHBKB;
````
Defines 'sHBKB' as a 'HB_Keyboard.' Nothing really unique or difficult to explain here.

So there's not much to talk about here. Let's keep digging in.


````
//Blablabla use in every program
#include <3ds.h>
#include <stdio.h>
#include <string>

//The actual keyboard library
#include "hbkb.h"

//ONLY INCLUDE THIS IF YOU'RE HAVING COMPILING ISSUES
//#define _GLIBCXX_USE_CXX11_ABI 0/1

int main() {

	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	// Keyboard Class
	HB_Keyboard sHBKB;

	printf("\x1b[0;0HHB_Keyboard Library Demo.");
	printf("\x1b[1;0HPress Start to exit.");

	while (aptMainLoop())
	{
		//Scan Inputs
		hidScanInput();
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) 
			break;
			
		// Touch Stuff
		touchPosition touch;

		//Read the touch screen coordinates
		hidTouchRead(&touch);

		// Call Keyboard with Touch Position
    u8 KBState = sHBKB.HBKB_CallKeyboard(touch);

}
````
Alright, now we have THREE new lines of code. Let's see if we can understand them!



````
		// Touch Stuff
		touchPosition touch;
````
So this actually is a part of the ctrulib library. This is how we use the 3ds to read x and y coordinates tapped on the bottom screen.


````
		//Read the touch screen coordinates
		hidTouchRead(&touch);
````
Here's the input library reading the coordinates.

````
		// Call Keyboard with Touch Position
    u8 KBState = sHBKB.HBKB_CallKeyboard(touch);
````
And finally, here's the hbkb library using the coordinates. We'll be using this a little later.

Ok, great! We've not only figured out how to get data from the bottom screen, but we've even figured out how to feed it into our keyboard. But we aren't done yet, as we haven't even created a string or saved a string. This is where it becomes largely C++.

````
//Blablabla use in every program
#include <3ds.h>
#include <stdio.h>
#include <string>

//The actual keyboard library
#include "hbkb.h"

//ONLY INCLUDE THIS IF YOU'RE HAVING COMPILING ISSUES
//#define _GLIBCXX_USE_CXX11_ABI 0/1

int main() {

	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	// Keyboard Class
	HB_Keyboard sHBKB;

	printf("\x1b[0;0HHB_Keyboard Library Demo.");
	printf("\x1b[1;0HPress Start to exit.");

	while (aptMainLoop())
	{
		//Scan Inputs
		hidScanInput();
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) 
			break;
			
		// Touch Stuff
		touchPosition touch;

		//Read the touch screen coordinates
		hidTouchRead(&touch);

		// Call Keyboard with Touch Position
    u8 KBState = sHBKB.HBKB_CallKeyboard(touch);
		
		// Print Input
    std::string InputHBKB = sHBKB.HBKB_CheckKeyboardInput(); // Check Input
    const char* InputCChar = InputHBKB.c_str();
    printf("\x1b[3;0HInput :");
    printf("\x1b[4;0H%s", InputCChar);
}
````


So now we have  `sHBKB.HBKB_CheckKeyboardInput();` which actually checks the input of all the buttons pressed on the keyboard! 
`const char* InputCChar = InputHBKB.c_str();` reads it as a C string, and the two `printf` functions display what the user is typing on the screen. 

Congradulations, you've officially begun typing! We'll experiment a little more with some of the features HBKB has to offer, such as cleaning the keyboard and using the KBState.

````
//Blablabla use in every program
#include <3ds.h>
#include <stdio.h>
#include <string>

//The actual keyboard library
#include "hbkb.h"

//ONLY INCLUDE THIS IF YOU'RE HAVING COMPILING ISSUES
//#define _GLIBCXX_USE_CXX11_ABI 0/1

int main() {

	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	// Keyboard Class
	HB_Keyboard sHBKB;

	printf("\x1b[0;0HHB_Keyboard Library Demo.");
	printf("\x1b[1;0HPress Start to exit.");

	while (aptMainLoop())
	{
		//Scan Inputs
		hidScanInput();
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) 
			break;
			
		// Touch Stuff
		touchPosition touch;

		//Read the touch screen coordinates
		hidTouchRead(&touch);

		// Call Keyboard with Touch Position
    u8 KBState = sHBKB.HBKB_CallKeyboard(touch);
		
		// Print Input
    std::string InputHBKB = sHBKB.HBKB_CheckKeyboardInput(); // Check Input
    const char* InputCChar = InputHBKB.c_str();
    printf("\x1b[3;0HInput :");
    printf("\x1b[4;0H%s", InputCChar);
    
    		if (KBState == 1) // User finished Input
		{
			sHBKB.HBKB_Clean(); // Clean Input
			printf("\x1b[2;0HKeyboard Return = Enter Key Pressed");
		}
		else if (KBState == 2)
			printf("\x1b[2;0HKeyboard Return = Generic Key Pressed");
		else if (KBState == 3)
		{
			sHBKB.HBKB_Clean(); // Clean Input
			printf("\x1b[2;0HKeyboard Return = Cancel Button Pressed");
		}
		else if (KBState == 4)
			printf("\x1b[2;0HKeyboard Return = No Key Pressed");
		else if (KBState == 0)
			printf("\x1b[2;0HKeyboard Return = UNKNOWN (HBKB Error).");
		else
			printf("\x1b[2;0HKeyboard Return = UNKNOWN (main.cpp Error).");
}
````

So, now we're acutally using the KBState. What are we doing with it? We're using it to understand what exactly the user is doing. For example:

If KBState == 1, the user likely wants to submit what they typed. If the KBState == 3, they probably want to cancel whatever they just did. The key states are pretty self explanatory, so I'll let you read them and see what they do.
Of course, the program isn't finished, as we need some final touches. I.E: Return 0, clear the buffers, etc.

````
#include <3ds.h>
#include <stdio.h>
#include <string>

#include "hbkb.h"

//ONLY INCLUDE THIS IF YOU'RE HAVING COMPILING ISSUES
//#define _GLIBCXX_USE_CXX11_ABI 0/1

int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	// Keyboard Class
	HB_Keyboard sHBKB;

	printf("\x1b[0;0HHB_Keyboard Library Demo.");
	printf("\x1b[1;0HPress Start to exit.");

	while (aptMainLoop())
	{
		//Scan Inputs
		hidScanInput();
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) 
			break;

		// Touch Stuff
		touchPosition touch;

		//Read the touch screen coordinates
		hidTouchRead(&touch);

		// Call Keyboard with Touch Position
        u8 KBState = sHBKB.HBKB_CallKeyboard(touch);
		
		// Print Input
        std::string InputHBKB = sHBKB.HBKB_CheckKeyboardInput(); // Check Input
        const char* InputCChar = InputHBKB.c_str();
        printf("\x1b[3;0HInput :");
        printf("\x1b[4;0H%s", InputCChar);
/*
		if (KBState == 1) // User finished Input
		{
			sHBKB.HBKB_Clean(); // Clean Input
			printf("\x1b[2;0HKeyboard Return = Enter Key Pressed");
			break;
		}
		else if (KBState == 2)
			printf("\x1b[2;0HKeyboard Return = Generic Key Pressed");
		else if (KBState == 3)
		{
			sHBKB.HBKB_Clean(); // Clean Input
			printf("\x1b[2;0HKeyboard Return = Cancel Button Pressed");
			break;
		}
		else if (KBState == 4)
			printf("\x1b[2;0HKeyboard Return = No Key Pressed");
		else if (KBState == 0)
			printf("\x1b[2;0HKeyboard Return = UNKNOWN (HBKB Error).");
		else
			printf("\x1b[2;0HKeyboard Return = UNKNOWN (main.cpp Error).");
*/
		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	// Exit services
	gfxExit();
	return 0;
}

````

REMEMBER: This is largely for C++, and may be difficult to use in C. Keep that in mind.
Also, if you have trouble compiling, be use to make the changes in the makefile and uncomment out 
````
//ONLY INCLUDE THIS IF YOU'RE HAVING COMPILING ISSUES
//#define _GLIBCXX_USE_CXX11_ABI 0/1
````
-VSMS

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello Sockets! (Part 1)

This portion of the tutorial requires EITHER knowledge of Javascript/Node.js OR you having the ability to make a TCP server in the language of choice. I won't be going too indepth of how to make a TCP server, but I will give you this link and a general overview of it: https://gist.github.com/creationix/707146

Furthermore, our 3ds-side (client-side) socket will mimic http://wiki.treck.com/Introduction_to_BSD_Sockets#TCP_Client but with some VERY IMPORTANT 3ds specific code that we'll need to go over. The link goes over the general knowledge needed for socket programming, but the 3ds has a few unique qwerks that are paramount to getting the socket programming to work. 

Here's an official example of 3ds socket code straight form the devkitPro github account and largely what we'll be basing our code around.
https://github.com/devkitPro/3ds-examples/blob/master/network/sockets/source/sockets.c

While the socket programming in-and-of itself is probably mostly just C code, many of the individual liberties I take are prodominately C++. If you only want to use sockets, it probably won't be an issue. If you're trying to use too much more of the code i write, turning it from C++ to C will likely be very difficult, so keep that in mind.
So this portion of the entire tutorial might be the most confusing for any number of reasons. Especially because of all the assumptions we'll be making.

1) We're assuming that you either have some basic knowledge of Node.js/Javascript to follow the guide OR you can make your own TCP server in any language of your choice.  (NOTE: As far as I'm aware, this will not work with socket.io).

2) You're programming for C++ and not C.

3) You have at least a basic understand of sockets.

4) We're constantly using command line to get our server up and running.

5) Although we're making a generic TCP server, we're assuming ONLY 3ds will be connect to it.

 - Let's Begin (TCP SERVER) - 
 
Let's actually start with the server, rather than the client. Otherwise, how will we know our 3ds is going to connect?
So, we're using Node.js as our server. I'm assuming you already know how to install and set node.js up. If not, https://www.youtube.com/playlist?list=PLoYCgNOIyGAACzU6GliHJDp4kmOw3NFsh will give you a basic understand. I generated the basic files with express-generator. As I stated earlier, socket.io (and websockets in general) doesn't use the same protocol that regular TCP sockets do, so we won't be using it. 

````
var socketClients = [];

net.createServer(function(socket) {
	socket.datacount = 0;
	socket.on("error", (err) => console.log("Abrupt client end."));
	socket.name = socket.remoteAddress + ":" + socket.remotePort;
	
	socketClients.push(socket);
	
	console.log("Connected made!");
	socket.write("Hi! Officially connected to the server\r\n"); 
	setInterval(function(){socket.datacount = 0}, 10000);
	
	socket.on("data", function(data) {
		socket.datacount++;
		if(socket.datacount > 15) {
			socket.write("Flood detection - Too many msgs\r\n");
			} else {
			try {
					socket.write("You said: " + data);
					console.log(socket.name + " said " + data)
					//socket.write("\r\n");
			} catch(e) {
				console.log(e);
			};
		}
	
	})
}).listen(8080);
````

Alright, I don't want to get /too/ in-depth since this is a 3ds tutorial and not a node.js/javascript or TCP Server tutorial. But I'll go over the general things that each piece of code does and let you know what's most important to keep for later. Furthermore, there's a lot that we're leaving out since we're assuming /only/ 3dses will be connecting to the TCP server (and not, say, a telnet command.)

`net.createServer(function(socket) {` - Creates the socket server. The socket variable inside of the function parenthesis is each individual socket connection.

`	socket.datacount = 0; ` - Used later for flood detection

`	socket.on("error", (err) => console.log("Abrupt client end."));` - Allows us to handle errors (such as unexpected connection closes, like when you press the power button to force a shutdown instead of the start button to handle graceful, intended exits.

`	socket.name = socket.remoteAddress + ":" + socket.remotePort;` - Used to help identify the socket. Gives us IP address and their port.

	`socketClients.push(socket);` - Pushes socket into an array of socket clients. This gives us the opportunity to later give every socket a message (We're not going to do that in this tutorial, as that's server side. But if you check the link above it wouldn't take too many extra lines of code. The only reason I didn't do this part is because I only own a 2ds and have no way of confirming it'd undoubtedly work on multiple systems as intended.)
	
	`console.log("Connected made!");` - Simple console log to let us know a user connected to our server
	`socket.write("Hi! Officially connected to the server\r\n"); ` - Tells the user they've connected to our server
	`setInterval(function(){socket.datacount = 0}, 10000);` - Used to reset the flood count every 10 seconds (prevent spammming to all users)

Alright, that was most of the simple code. Now let's get onto the major block:
````
	socket.on("data", function(data) { // We recieve the data from the 3ds client
		socket.datacount++; // Increases flood count detection
		if(socket.datacount > 15) { //If the user is indeed sending too many messages (He's sent more than 15 messages in 10 seconds)
			socket.write("Flood detection - Too many msgs\r\n"); // Let user know this is excessive
			} else {
			try { // try, catch for error prevention (In the event a telnet is connected for some reason)
					socket.write("You said: " + data); // Repeats data to user
					console.log(socket.name + " said " + data) //log data that was recieved from the client to sever console
					//socket.write("\r\n");
			} catch(e) {
				console.log(e); // If there is an error sending the message, log it to the console.
			};
		}
	
	})

````

That's basically it for the server. Again, as this isn't a server tutorial, but a 3ds tutorial, I may have been more vague than previously. Viewing the github gist on node.js TCP servers and watching the playlist on Node.js may help clear up any confusing information. Furthermore, you could just create any TCP server in any programming language of your choice.

Next is for the 3ds client.


-VSMS

### Hello Sockets! (Part 2)

 - Let's Begin (3DS CLIENT) -
 
Oh boy, even the includes are a block a code.

THIS WILL NOT WORK ON CITRA EMULATOR AS OF SEPT 9TH, 2016. ALL FILES MUST BE TESTED ON AN ACTUAL 3DS.
````
//Generic inputs
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>

#include "hbkb.h" // Keyboard (C++)
#include <vector> // Vectors (We're gonna create a vector of string for all messages) (C++)
#include <string.h> // std::string (C++)

#include <malloc.h> //Needed for memalign

// Needed for the socket connection
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>

//When we memalign for the sockbuffer
#define SOC_ALIGN       0x1000
#define SOC_BUFFERSIZE  0x100000

//Needed to remove compiler errors -- also change makefile if needed
//#define _GLIBCXX_USE_CXX11_ABI 0/1
````

Yes, that's only the includes. I feel as though the comments are self-explanatory, so I don't think I'm going to go too in-depth with them for the time being. I'll be more specific with the actual functions.

I'm also not gonna repost the entire thing until the end, but rather blocks at a time since this could get rather large.
Let's start with what we already know. 

````
int main()
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL); //Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.
  HB_Keyboard sHBKB;
  
  //Rest of code later
````

Alright, that's basically just what we've done previously. Nothing unusual here...
````
	int sock, bytes_recieved, ret, numberOfChatMessages;
  std::vector<std::string> chatMessages;

	char send_data[256], recv_data[256];
	send_data[0] = recv_data[0] = 0;
  numberOfChatMessages = 0;

	struct sockaddr_in server_addr;
	static u32 *SOC_buffer = NULL;
````
All of these variables are used later, but it's probably not such a bad idea to know what we're gonna do with them.

`sock` will be used as a return value to tell us wether or not we were able to initialize the socket function.
`bytes_recieved` will be for how many characters we can accept from the server
`ret` is for intilizing soc:u service (one of the 3ds quirks)
`numberOfChatMessages` specifically for our vector when receieve messages
`send_data` and `recv_data` are placeholders for sending and recieving data respectively.

We'll get into the server_addr in a bit, but SOC_buffer right now.

`SOC_buffer = (u32*)memalign(SOC_ALIGN, SOC_BUFFERSIZE);` needed for socInit();

````
if(SOC_buffer == NULL) {
        gfxExit();
        socExit();
        return 0;
	}
````
Just making sure our SOC_buffer actually exist.

````
	// Now intialise soc:u service
	if ((ret = socInit(SOC_buffer, SOC_BUFFERSIZE)) != 0) {
        gfxExit();
        socExit();
        return 0;
	}
````
Now we've used the 3ds specific socInit() function. We're now able to start using sockets.


`sock = socket(AF_INET, SOCK_STREAM, 0);` - We've officially created a socket! We haven't given it an IP address, so it's not actually doing much. But it at least exist!

````
	if(sock == -1) {
        gfxExit();
        socExit();
        return 0;
	}
````
Once again, making sure the sock actually exist.

Alright! Now we're ready to actually connect to a server. That's where server_addr comes in.

	`server_addr.sin_family = AF_INET;`
	`server_addr.sin_port = htons([INSERT SERVER PORT HERE]);` - IMPORTANT: Make sure whatever port you used in node.js, you use here.
`	server_addr.sin_addr.s_addr = inet_addr("[INSERT SERVER IP ADDRESS HERE]");` - Assuming you're using a local computer, use ipconfig in the command prompt. Type your ipv4 address (something like 192.168.x.x).

````
	if(connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        gfxExit();
        socExit();
        return 0;
	}
````
We're now officially connected to the server! We'll be able to connect to the server.


````
	if(fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK) == -1) {
        gfxExit();
        socExit();
        return 0;
	}
````
This makes the socket NONBLOCKING, allowing us to do multiple things while the socket connection happens in the background.
So we've actually done basically everything! We've initiation the soc:u, created a socket, and connected to the server!
All that's left now is the ability to send and recieve messages.
We'll take care of that in the third and final portion of sockets.

-VSMS

### Hello Sockets! (Part 3)

````
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();
		u32 kDown = hidKeysDown();
````

Again, all things we've seen before. Nothing unique or unusual here.

`ret = recv(sock, recv_data, sizeof(recv_data), 0);` - Here, we actually recieve messages and put the data in the recv_data. Great! 
Here's where some of my personal liberties are gonna start coming into play. Largely C++ features, this is where it may start being difficult to translate into C.

````
 if(strlen(recv_data) > 0){ // Checks to make sure the data we recieve isn't empty
            consoleClear(); // clears the console so text doesn't overlap
            numberOfChatMessages++; //Lets us know how many messages are in the vector

            if(numberOfChatMessages > 23) { // If there are more than 24 messages
                chatMessages.clear(); // Empties vector once we've surpassed 23 in the array
                numberOfChatMessages = 0; //Since we've reset the vector, we should reset this too
                chatMessages.push_back(recv_data); // (Remember vectors/arrays/etc start at 0)
                memset(&recv_data[0], 0, sizeof(recv_data)); // Clear the recv_data
            } else { //If we have less than 24 messages
                chatMessages.push_back(recv_data); //Add the data to the vector
                memset(&recv_data[0], 0, sizeof(recv_data)); //Clear the recv_data
                numberOfChatMessages++; //increase number of messages in the vector
            }
        }
````
Explained with comments, so it should be good.

Alright. So we can initiate the soc:u, create a socket, connect to a server, AND recieve data. Let's display data once we've obtained it. For now, we'll keep something basic.

````

    for(int i = 0; i < chatMessages.size(); i++) { //counts every message in vector
        printf("\x1b[%d;0H%s", (i+5), chatMessages[i].c_str()); // Prints every message on its own line, 5 lines down
        if(i >= 23) { //30 max total possible lines, mines 5 for instructions and etc, with 2 lines unused
            i = 0; // restart once we're 23 lines.
        }
    }

````

And we're officially able to print data we've recieved from the server onto the sceen! We still don't have the ability to /send/ data, but that's quite simple with HBKB library.

````


		// Touch Stuff
		touchPosition touch;

		//Read the touch screen coordinates
		hidTouchRead(&touch);

		// Call Keyboard with Touch Position
		u8 KBState = sHBKB.HBKB_CallKeyboard(touch);

		std::string InputHBKB = sHBKB.HBKB_CheckKeyboardInput(); // Check Input
		const char* InputCChar = InputHBKB.c_str();
````
All things we've seen before. Nothing unusual here.


````
		//Print input

		if (KBState == 1) {
			sHBKB.HBKB_Clean(); // Clean Input
			consoleClear();
			if (strlen(InputCChar) <= 100 && strlen(InputCChar) > 0) {
				strcpy(send_data, InputCChar);
				send(sock, send_data, (strlen(send_data) + 1), 0);
			}
		}
````

Now this is where we make a few changes from the original HBKB library.
`	if (strlen(InputCChar) <= 100 && strlen(InputCChar) > 0) {` We make sure we don't spam empty strings to the server. We also make sure we have a reasonable char length (100) to help prevent buffer overflows.
`strcpy(send_data, InputCChar);` Copies the InputCChar string into our send_data string.
`send(sock, send_data, (strlen(send_data) + 1), 0);` sends the string to the server through our socket.
We did it! We've officially accomplished everything we need to. Now we just return 0 and exit out of everything and do all the usual junk.

````
		if (kDown & KEY_START)
			break; //Break in order to return to hbmenu

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	socExit();
	close(sock);
	return 0;
````

And we're completely done! Too look at a more thorough view of the source code, visit here https://github.com/verysimplyms/3dsTCP-client

-VSMS

### Hello 3DS Portlibs!

This is where it gets very interesting. In this portion of the tutorial, we're going to be cross-compiling 3rd party libraries using https://github.com/devkitPro/3ds_portlibs
It's actually pretty simple and intuitive to follow. As of December 21st, 2016, I've only attempted two librarires. One being zlib (because it's required in order to get the other libraries to work) and the other being mbedtls (for encryption.)
I did this on Windows, so your experience may differ depending on your platform. If you're also doing this on windows, you may need to download wget. I downloaded the 64-bit version from https://eternallybored.org/misc/wget/ (you may need to rename it from wget64.exe to simply wget.exe if you plan on using the 64bit version.) Be sure to put this wget file in the ` C:/devkitpro/msys/bin ` folder.

- Let's begin - 

- Download https://github.com/devkitPro/3ds_portlibs
- Open MSYS from your devKitPro
- Follow the instructions on the devkitpro page

When it comes to installing zlib, it should be fairly simple and straightforward. Downloading and installing other libraries I'm not entirely sure about, as I've only done mbedtls and I had some small difficulties doing that due to cross-compiling platform issues. But those issues were relatively minor and simple to solve, as you'd expect from git repo whose sole existence is to port libraries for the 3ds.

-VSMS
### Hello Encryption! (AES) Part 1

With our last tutorial being an intro to portlibs, this is going to be an intro to encrypting data on our 3ds.
Encryption is paramount because of how necessary it to transmit secure information across the internet. Encryption reduces attacks such as MitM.

So this portion of the tutorial will be in 2 parts
1) Download, Installing, and Cross-compiling mbedtls
2) Creating our homebrew application (Should work in Citra)

- Let's begin - 

Simply follow the devkitpro instructions. This should lead you to "make mbedtls" and "install mbedtls."
Depending on the platform that you're compiling on, you may run into issues.

You should be sure CC, CXX, and AR are properly exported in MSYS. Additionally, I had issues regarding the [timing.c](https://tls.mbed.org/api/timing_8c_source.html) file regarding the `alarm()` function located [here](https://tls.mbed.org/kb/development/what-external-dependencies-does-mbedtls-rely-on). To add on to that, I also had difficulties with the [gen_key.c](https://tls.mbed.org/api/gen__key_8c_source.html) file with the `sleep(1)` function. In both instances, I made some minor work arounds (in the gen_key.c I commented out the line completely) and the library compiled and builded without issue.

After building the library, you should have: libmedcrypto.a, libmedtls.a, and libmedx509.a all in your library folder.
You're going to want to copy and paste these into your project's lib folder. Furthermore, you're going to want to take all of the header files in include/mbedtls (where you were cross-compiling your library) mbedtls folder, and copy and paste that folder into the include folder of your main project (where you want to actually make your .3dsx file for your 3ds) as well.

-VSMS

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello stereoscopy!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello animation!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello touchscreen!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello sound!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello microphone!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello filesystem!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello Internet!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello Gyroscope!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello Infrared communication!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello NFC!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello Camera(s)!

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

### Hello Battery, 3D slider, luminosity, etc.

<!-- TODO: describe the API, then provide a full example with source code and a zip to download. -->

Coming soon!

