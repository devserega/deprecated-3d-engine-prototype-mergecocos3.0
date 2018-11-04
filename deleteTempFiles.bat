@echo off

echo.this script clean up all temp files (version 2.5)

::--------- delete WIN32 build  temp files ---------------
:: DEBUG
call:deleteFolder "build\Debug.win32"
call:deleteFolder "cocos3d\proj.win32\Debug.win32"
call:deleteFolder "cocos2dx\cocos\2d\Debug.win32"
call:deleteFolder "cocos2dx\cocos\audio\proj.win32\Debug.win32"
call:deleteFolder "EngineDemo\proj.win32\Debug.win32"

:: RELEASE
call:deleteFolder "build\Release.win32"
call:deleteFolder "cocos3d\proj.win32\Release.win32"
call:deleteFolder "cocos2dx\cocos\2d\Release.win32"
call:deleteFolder "cocos2dx\cocos\audio\proj.win32\Release.win32"
call:deleteFolder "EngineDemo\proj.win32\Release.win32"

call:deleteFile "build\*.sdf"

::--------- delete ANDROID build  temp files ---------------
:: ...

echo.&pause&goto:eof

::--------------------------------------------------------
::-- Function section starts below here
::--------------------------------------------------------

:deleteFolder - delete folder with it content
echo.
echo. Delete folder %~1
rmdir %~1 /s /q
goto:eof

:deleteFile - delete file
echo.
echo. Delete file %~1
del /s /q %~1 
goto:eof

