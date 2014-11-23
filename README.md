#3DS Homebrew tutorial and tools


##Introduction

Hello everyone,<br>
This project has two purposes:

- Explain how to make your own homebrews for Nintendo 3DS / 2DS / New 3DS from scratch.
- Provide some handy tools to ease your homebrew development.

It's in the public domain and all contributions / translations are welcome!<br>
Thanks to [smealum](http://smealum.net) for his [Ninjhax](http://smealum.net/ninjhax), [ctrulib](https://github.com/smealum/ctrulib) and [hbmenu](https://github.com/xem/3ds_hb_menu) projects.<br>
Authors: xem, octopuserectus.


##Summary

- [Setup](https://github.com/xem/3DShomebrew#setup)
  - [Hardware](https://github.com/xem/3DShomebrew#hardware)
  - [Software](https://github.com/xem/3DShomebrew#software)
  - [Homebrew launcher (hbmenu) setup](https://github.com/xem/3DShomebrew#homebrew-launcher-hbmenu-setup)
  - [Homebrew installation](https://github.com/xem/3DShomebrew#homebrew-installation)
  - [Where can we find 3DS homebrews?](https://github.com/xem/3DShomebrew#where-can-we-find-3ds-homebrews)
- [Anatomy of a homebrew project](https://github.com/xem/3DShomebrew#anatomy-of-a-homebrew-project)
  - [Basics](https://github.com/xem/3DShomebrew#basics)
  - [Build procedure](https://github.com/xem/3DShomebrew#build-procedure)
  - [New project](New project)
- [Homebrew development](https://github.com/xem/3DShomebrew#homebrew-development)
  - ...
  - ...
  - ...
  - ...
  - ...
  - ...
  - ...
  



##Setup


###Hardware

Here's what you need to buy to get started:

- A Nintendo 3DS / 2DS console with a firmware version between 4.0.0-7 and 9.2.0-20 + a SD card.
or 
- A New 3DS with a firmware between 9.0.0-20 and 9.2.0-20 + a micro SD card.
- An SD / microSD card reader.
- A copy of the 3DS game "Cubic Ninja" (new or used). 

Note: Gateway 3DS can also play homebrews, but only in .3ds and .cia formats. This tutorial will focus on .3dsx homebrews, playable with Ninjhack + hbmenu.


###Software

Here's what you need to download and install:

- The latest version of [DevkitPro](http://devkitpro.org). During setup, you can choose to install devkitARM only.
- [Ninjhack's homebrew starter kit](http://smealum.net/ninjhax/dl/starter.zip). Unzip this at the root of your SD card and place the SD card in your console.
- A C++ compatible IDE like [Netbeans](https://netbeans.org/downloads), or a code editor, like [notepad++](http://notepad-plus-plus.org).
- A FTP client like [FileZilla](https://filezilla-project.org) or [WinSCP](http://winscp.net) to upload homebrews directly on your 3DS using wi-fi connection. (optional)
- Latest version of [Python 3.x.x](https://www.python.org), to use advanced features in your homebrews. (optional)
- Note that [ctrulib](https://github.com/smealum/ctrulib) is automatically installed by DevkitPro, in the libctru folder. You can get the latest version [here](https://github.com/smealum/ctrulib/archive/master.zip). (optional)

###Homebrew launcher (hbmenu) setup

Follow these steps to install the hbmenu on your 3DS (this needs to be done only once):

- Go on Ninjhax's website and [generate the QR code corresponding to your console's firmware](http://smealum.net/ninjhax/#qrcode). (you can find your firmware version in the "Settings" app, on the upper screen.)
- Enable your 3DS' wi-fi connexion.
- Start the game Cubic Ninja, choose "Create", then "QR code", and finally "Scan QR code". 
- Scan the QR Code, then follow on-screen instructions to start hbmenu.

The next time you turn your console on, just launch Cubic Ninja, choose "Create", then "QR code" and hbmenu will start directly.

<img src="http://img.ctrlv.in/img/14/11/22/54709c512ae72.png" width=400>

###Homebrew installation

Two files are needed for a 3DS homebrew to be playable with Ninjhack: a *.3dsx file and a *.smdh file.

If you want to play homebrews on your console, or test your own builds easily, you can use your computer to place them in the "3ds" folder of your SD card.

Note: you can create subfolders in your 3ds folder to organize your homebrews.

You can also upload them directly using wi-fi:
- Start hbmenu.
- Start the ftPONY homebrew.
- Note the IP and port displayed on the upper screen (for example: "IP: 192.168.0.128 port 5000")
- Start a FTP client on your desktop, and use these credentials to get connected.
- If asked, choose "anonymous connection".
- You should now see your SD card's filesystem and be able to drag & drop files and folders in the "3ds" folder of your SD card.
- Press B to quit ftPONY and launch your new apps.

<img src="http://img.ctrlv.in/img/14/11/22/54709afe2f047.png" width=700>

###Where can we find 3DS homebrews?

Here are some sites listing 3DS homebrews. Most of them will need to be built with ctrulib to be playable with hbmenu.

- [3Dbrew](http://www.3dbrew.org/wiki/Homebrew_Applications)
- [Nintendomax](http://www.nintendomax.com/portal.php?&page_id=3)
- [GBAtemp](https://gbatemp.net/threads/homebrew-development.360646/)

##Anatomy of a homebrew project

###Basics

Let's take a look at our template default, in ctrulib/template. It's a minimal project that does nothing else than printing a white pixel on the upper screen.

It contains:
- a source folder, containing a main.c file. (this contains the source code of your homebrew)
- a makefile file (this contains the instructions to build our homebrew for hbmenu)

Let's see how bigger projects are made, for example [Yeti3DS](https://github.com/smealum/yeti3DS). You can notice a few other things:
- an icon.png file (This is a 48x48px image displayed on hbmenu alongside your homebrew. Optional but preferable.) 
- the source folder contains more .c files and .h files. (this is a common way to structure and organize a C/C++ project. Note that the main function ````int main()```` remains in main.c, the other C files are used to store additional code and data).

In many projects, like [3dscraft](https://github.com/smealum/3dscraft) you can find a data folder containing .bin files. Those are images, and we'll explain later how to make and how to use them.

###Build procedure

Let's go back to our ctrulib/template folder.
- Open a CLI (command line invite). If you're on Windows, press Shift + right click on the template folder and choose "Open a CLI here".
- type ````make```` and press enter.
- After a few seconds, the process finishes and you can find a build folder (you can ignore it) and two new files .3dsx and .smdh. You can send them on your SD card to test the homebrew on real hardware.
- You can rebuild those files anytyme after editing your source code.

You can try to build all ctrulib examples and run them on your 3DS.

***Sadly, I can't manage to build the "gpu" example (it says "python: command not found") nor the "httpd" example ("implicit declaration of function"). If someone knows how to fix that... :)***

###New project

To start developing your own homebrew:

- Make a copy of the template folder, place it where you want, and name it "tuto" (for example).
- Add a 48x48px icon.png file. Here's an example that you can download, use and edit freely:

<a href="http://img.ctrlv.in/img/14/11/22/5470cab56bf39.png"><img src="http://img.ctrlv.in/img/14/11/22/5470cab56bf39.png"></a>

##Homebrew development

This part will detail how to develop a 3DS homebrew by covering all the features in ctrulib and all the technical details of the console. 

Chapters will include: display (stereoscopic or not, using bitmap or GPU, ...), sound, input, SD card access, HTTP internet access, microphone, battery, gyroscop, NFC and ... God knows what.

Coming soon!
