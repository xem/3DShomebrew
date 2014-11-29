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
It's based on ctrulib's template project but cleaner and more complete. (it contains a logo, hbmenu metadata and comments)
<br>
Unzip it on your computer (For example in C:/3DS/template).
<br>
In this tutorial, we will develop small programs based on this template.
<br>
We won't do an "Hello World!" text printer yet; we'll start with a few more basic things.

### Hello template!

Let's open the source folder of our project template, and take a look at main.c's source code.

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
  u32 kDown;        // pressed keys data

  // Main loop
  while (aptMainLoop())
  {

    // Wait for next frame
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
  - Swap and flush current framebuffers.
- After the loop, we unload everything and ````return 0````, to get back to hbmenu.

#### Screens, VRAM and framebuffers

Let's take a look to the 3DS memory, and how it is mapped to the screens.
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

To sum up, on each screen, both framebuffers use 3 bytes to store Blue, Green and Red components of each pixel, starting from the bottom-left pixel and storing each column of pixels until it reaches the top-right pixel.

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
