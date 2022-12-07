set dir=%~p0
call :next %dir:~0,-1%
goto :eof

:next
setlocal
mkdir build
cd build
set Configuration=Debug
cmake .. -D CMAKE_INSTALL_PREFIX:PATH="D:/Program Files/%~n1" -D CMAKE_BUILD_TYPE=%Configuration%
cmake --build . --config %Configuration%
endlocal
goto :eof
