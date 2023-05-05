cls
@Echo OFF

title Folder BASEe

if EXIST "Control Panel.{21EC2020-3AEA-1069-A2DD-08002B30309D}" goto UNLOCK
if NOT EXIST BASEe goto MDBASEe



:CONFIRM
echo Encrypt the BASE /??

set/p "cho="

if %cho%==Y goto LOCK
if %cho%==y goto LOCK
if %cho%==n goto END
if %cho%==N goto END

echo --
echo --
color fc
echo UNrecognised.
echo --
echo --

goto CONFIRM



:LOCK
ren BASEe "Control Panel.{21EC2020-3AEA-1069-A2DD-08002B30309D}"
attrib +h +s "Control Panel.{21EC2020-3AEA-1069-A2DD-08002B30309D}"
echo Folder locked
goto End
pause



:UNLOCK
echo WELCOME SIGNORE ray
echo at your service
echo spell my name!
set/p "CODE="
if NOT %CODE%==hermit goto FAIL
attrib -h -s "Control Panel.{21EC2020-3AEA-1069-A2DD-08002B30309D}"
ren "Control Panel.{21EC2020-3AEA-1069-A2DD-08002B30309D}" BASEe
echo BASEe Unlocked successfully
goto End



:FAIL
echo --
echo --
echo FATAL FAILURE

pause
goto end


:MDBASEe
md BASEe
echo BASE established
pause
goto End



:End