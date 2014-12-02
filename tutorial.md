#3DS homebrew development tutorial

[Return to homepage](http://goo.gl/CLdz5Q)

##Introduction

This document will explain in detail how to develop homebrews (applications / games) for Nintendo 3DS, 2DS and New 3DS.
<br>We will code them in C/C++, with [ctrulib](https://github.com/smealum/ctrulib)'s help, and play them with [Ninjhax](http://smealum.net/ninjhax) and [hbmenu](https://github.com/xem/3ds_hb_menu).
<br>Basic notions of programming are required, even if they come from another language (Java, PHP, JS, ...).
<br>Note that the 3DS homebrew scene is very young, and many things are still impossible to do. (see the [limitations page](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md/blob/gh-pages/tutorial/limitations.md)).
<br>But we're here to make it as simple as possible!

##Summary

[TOC]

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
    kUp = hidKeysUp()

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
