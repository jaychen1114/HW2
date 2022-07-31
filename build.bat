@echo off
set PATH=%cd%\mingw64\bin;%PATH%
del .\bin /Q
md .\bin
md .\bin\object
g++ .\src\object\potion.cpp -c -o .\bin\object\potion.o -Wall -Wextra -std=c++17 -Isrc -Iinclude 
g++ .\src\object\asteroid.cpp -c -o .\bin\object\asteroid.o -Wall -Wextra -std=c++17 -Isrc -Iinclude 
g++ .\src\object\bullet.cpp -c -o .\bin\object\bullet.o -Wall -Wextra -std=c++17 -Isrc -Iinclude 
g++ .\src\object\player.cpp -c -o .\bin\object\player.o -Wall -Wextra -std=c++17 -Isrc -Iinclude 
md .\bin\engine
g++ .\src\engine\end.cpp -c -o .\bin\engine\end.o -Wall -Wextra -std=c++17 -Isrc -Iinclude 
g++ .\src\engine\menu.cpp -c -o .\bin\engine\menu.o -Wall -Wextra -std=c++17 -Isrc -Iinclude -lallegro 
g++ .\src\engine\mainGame.cpp -c -o .\bin\engine\mainGame.o -Wall -Wextra -std=c++17 -Isrc -Iinclude 
g++ .\src\engine\scene.cpp -c -o .\bin\engine\scene.o -Wall -Wextra -std=c++17 -Isrc -Iinclude 
md .\bin\AI
g++ .\src\AI\model.cpp -c -o .\bin\AI\model.o -Wall -Wextra -std=c++17 -Isrc -Iinclude
md .\bin\utils
g++ .\src\utils\imageProcess.cpp -c -o .\bin\utils\imageProcess.o -Wall -Wextra -std=c++17 -Isrc -Iinclude 
g++ .\src\utils\log.cpp -c -o .\bin\utils\log.o -Wall -Wextra -std=c++17 -Isrc -Iinclude 
g++ .\src\main.cpp -o .\bin\main.exe .\bin\object\potion.o .\bin\AI\model.o .\bin\object\asteroid.o .\bin\object\bullet.o .\bin\object\player.o .\bin\engine\end.o .\bin\engine\menu.o .\bin\engine\mainGame.o .\bin\engine\scene.o .\bin\utils\imageProcess.o .\bin\utils\log.o -Wall -Wextra -std=c++17 -Isrc -Iinclude -lallegro -lallegro_font  -lallegro_image -lallegro_ttf -lallegro_primitives -Llib
pause