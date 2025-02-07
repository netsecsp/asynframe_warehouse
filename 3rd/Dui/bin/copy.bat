cd %~dp0

copy ..\..\..\..\..\project\window\asynframe\bin\asyncore.dll .

del *.log

cd ../DuiLib
rmdir /S /Q Build