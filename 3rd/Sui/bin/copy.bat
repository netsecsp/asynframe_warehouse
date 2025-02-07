cd %~dp0

copy ..\..\..\..\..\project\window\asynframe\bin\asyncore.dll .

del *.log

cd ..
rmdir /S /Q obj