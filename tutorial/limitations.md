##3DS homebrews limitations

Current limitations of homebrews powered by Ninjhax:

- Ninjhax currently allows users to access only 64MB of RAM, even on the New 3DS.
- As there is currently no good way to use the DSP (sound processing chip) from homebrew, sound output is not yet possible on the New 3DS.
- There is also no known way to run code on the New 3DS's extra CPU cores under Ninjhax, but it's possible to use 80% of the system core's time using ````APT_SetAppCpuTimeLimit()```` rather than 30% (as it's the case on the old 3DS).
- We're currently unable to detect "Home button" being pressed (nor the POWER button) with code. As soon as a solution is found, we'll update the corresponding chapter, and it will certainly become the sdandard way to return to hbmenu, instead of pressing START.
