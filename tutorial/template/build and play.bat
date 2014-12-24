REM === Build ===
make

REM === pause if there were errors ===
if %errorlevel% neq 0 pause

REM === Find the .3dsx file ===
FOR %%F IN (*.3dsx) DO (

  REM === Launch the emulator ===
  START emulator/3dmoo.exe %%F

  REM === Upload to 3DS with Netcat ===
  cd netcat
  cat ../%%F | nc 192.168.137.8 9000
)