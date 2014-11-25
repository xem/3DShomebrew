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
  - [New project](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#new-project)
- [Homebrew development](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#homebrew-development)
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
- Start hbmenu.
- Start the ftPONY homebrew.
- Note the IP and port displayed on the upper screen (for example: "IP: 192.168.0.128 port 5000")
- Start a FTP client on your desktop, and use these credentials to get connected.
- If asked, choose "anonymous connection".
- You should now see your SD / microSD card's filesystem and be able to drag & drop files and folders in the "3ds" folder of your card.
- Press B to quit ftPONY and launch your new apps.

<img src="http://img.ctrlv.in/img/14/11/22/54709afe2f047.png" width=700>

##Anatomy of a homebrew project

###Basics

Let's take a look at our template default, in ctrulib/template. It's a minimal project that does nothing else than printing a white pixel on the upper screen.

It contains:
- a source folder, containing a main.c file. (the source code of your homebrew)
- a makefile file (allowing to build your homebrew for hbmenu)

Let's see how bigger projects are made, for example [Yeti3DS](https://github.com/smealum/yeti3DS). You can notice a few other things:
- an icon.png file (a 48x48px image to display on hbmenu instead of the default one) 
- the source folder contains more .c files and .h files. (those files are used to organize big C/C++ project.<br>Note that the main function ````int main()```` remains in main.c, the other C files are used to store additional code and data called by ````main````).
- The makefile contains [three optional lines](https://github.com/smealum/yeti3DS/blob/master/Makefile#L40-L42) to specify the game's author, title and description.

In many projects, like [3dscraft](https://github.com/smealum/3dscraft) you can find a data folder containing .bin files. These files are used to store images data. The tutorial will explain how to use them in your projects.

<!--Reminder: [the tools](https://github.com/xem/3DShomebrew/blob/gh-pages/tutorial.md#tools) present in this project allow to convert image files in BIN and BIN files in PNG.-->

###Build procedure

Let's go back to our ctrulib/template folder.
- Open a CLI (command line interface). If you're on Windows, press Shift + right click on the template folder and choose "Open a CLI here".
- type ````make```` and press enter.
- After a few seconds, the process finishes and you can find a build folder (you can ignore it) and two new files .3dsx and .smdh. You can copy them to your SD card to test the homebrew on real hardware.
- You can rebuild those files at any time after editing your source code. You'll need to run ````make clean```` before rebuilding your project.

You can now try to build all ctrulib examples (or other open source homebrew projects) and run them on your 3DS.

***(TODO: figure out how to build the http example without "implicit declaration of function" errors)***

###New project

To start developing your own homebrew:

- Make a copy of the template folder, place it where you want, and give it a name, for example "tuto". (for example).<br>Do not use spaces in your projects names (this can cause build issues).
- Edit the makefile file, and add those 3 lines under the line 33:

````
APP_TITLE := tuto
APP_DESCRIPTION := 3DS homebrew tutorial
APP_AUTHOR := me!
````

- Add a 48x48px icon.png file at the root of the tuto folder. Here's an example that you can download, use and edit freely:<br>

<a href="http://img.ctrlv.in/img/14/11/22/5470cab56bf39.png"><img src="http://img.ctrlv.in/img/14/11/22/5470cab56bf39.png"></a>

##Homebrew development

This part will detail how to develop a 3DS homebrew by covering all the features in ctrulib and all the technical details of the console. 

Chapters will include: display (stereoscopic or not, using bitmap or GPU, ...), sound, input, SD card access, HTTP internet access, microphone, battery, gyroscope, NFC and ... God knows what.

Coming soon!
