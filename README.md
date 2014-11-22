3DS Homebrew tutorial
=====================

Introduction
------------

This document explains how to make your own homebrew softwares on  Nintendo 3DS / 2DS / new 3DS.
It's in the public domain and all contributions / translations are welcome!
Thanks to Smealum (http://smealum.net) for making this possible!

Setup
-----

**Hardware**

Here's what you need to buy to get started:
- A Nintendo 3DS/2DS/new3DS device with a firmware version between 4.0.0-7 and 9.2.0-20. (you can find your firmware version in the "Console parameters" app, on the upper screen.)
- A SD card + a SD card reader.
- A copy of the 3DS game **Cubic Ninja** (new or used)

**Software**

Here's what you need to download and install:
- The latest version of DevKitPro (http://devkitpro.org). During setup, you can choose to install devkitARM only.
- ctrulib (https://github.com/smealum/ctrulib/archive/master.zip). Unzip it inside DevKitPro's install folder.
- Ninjhack's homebrew starter kit. Unzip it at the root of your SD card and place the SD card in your console.
- A C++ compatible IDE like Netbeans (https://netbeans.org/downloads), or any code editor, like notepad++ (http://notepad-plus-plus.org).
- A FTP client like FileZilla (https://filezilla-project.org), to upload homebrews directly on your 3DS using wi-fi connection. (optional)
- P.ython 3.x.x (https://www.python.org), to use advanced development features in your homebrews. (optional)

** Initial setup **

Follow these steps to install the homebrew launcher on your 3DS (this has to be done only once):
- Go on Ninjhax's website and generate the QR code corresponding to your console's firmware (http://smealum.net/ninjhax/#qrcode).
- Enable your 3DS's wi-fi connexion.
- Start the game Cubic Ninja, choose "Create", then "QR code", and finally "Scan QR code". 
- Scan the QR Code, then follow on-screen instructions.

** Future setup **

The next times you turn your console on, just launch Cubic Ninja, choose "Create", then "QR code" and the HB launcher will start directly.

** Send homebrews on your console**

If you want to play homebrews on your console (or test your own builds) easily, you can place them in the "3ds" folder of your SD card, but you can also upload them directly using wi-fi:
- Start HB launcher.
- Start ftPONY.
- Note the IP and port displayed on the upper screen (for example: "IP: 192.168.0.128 port 5000")
- Start a FTP client on your desktop, and use these credentials to connect to your console. You should see your SD card's filesystem and be able to drag&drop files and folders in the 3ds folder.
- Press B to quit ftPONY and launch your new apps.

![FileZilla connected to ftPONY](http://img.ctrlv.in/img/14/11/22/54709afe2f047.png)



