# Project Cyan - A Tower Defense Game
![Preview of the project](https://raw.githubusercontent.com/mflottDesign/dat220/master/preview.png)
## About the project
Project Cyan was the final project for the course DAT220 at the University of Agder. The idea was to create a "new" type of Tower Defense genre game that would combine good aspects of other games into something more complete. The main things that inspired the things included in the project were Warcraft III's in-game UI and possibility for fanmade content, Trackmania's in-game editor (which resulted in an in-game map editor), Minecrafts intuitive settings menu and bloons easy-to-use upgrade and targeting system. By combining these features into a concept the project aimed to achieve a higher level of complexity to the gameplay as well as more possibilities for playermade content within the project period. While it did not end up being a complete product, a lot of the groundwork was done for planned features.

This project was done in collaboration with Christer Steffensen Mathisen.

## Installation
### Windows
#### Prerequisites
The compiler used for the project is MinGW 6.1.0, and can be downloaded at https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/6.1.0/threads-posix/seh/x86_64-6.1.0-release-posix-seh-rt_v5-rev0.7z/download

It also uses multiple libraries for the UI and logging:
* SFML 2.4.2 - GCC 6.1.0 MinGW (SEH) - 64-bit, https://www.sfml-dev.org/
* TGUI - You will have to compile your own MinGW 6.1.0 (SEH), we used v0.7, https://github.com/texus/TGUI
* PLOG - For logging, https://github.com/SergiusTheBest/plog
* nlohmann/json - https://github.com/nlohmann/json

Save each of these libraries somewhere, e.g. ``C:/dev/libs/``, and add each of theme to your systems PATH.

#### Setup
For the project we used the JetBrains CLion IDE, which can be found at https://www.jetbrains.com/clion/download/#section=windows.
After installing the IDE and launching it for the first time the program should be able to find the compiler by itself. If not, locate it when asked.

On the next prompt you will be asked to either create a new project or open a project folder. Choose to locate a project folder and locate the extracted folder of this project. It should recognize it as a project.

After opening the project, you have to link the required libraries. To do this, first go to ``View -> Tool Windows -> CMake``, then on the bottom left side click on the cogwheel and choose ``CMake settings``. Assuming that the compiler path is in ``C:/mingw64`` and the path to the libraries is in ``C:/dev/libs/`` copy and paste the following:
```
-D CMAKE_CXX_COMPILER=C:/mingw64/bin/gcc.exe -DCMAKE_CXX_FLAGS="-IC:/dev/libs/SFML/include -IC:/dev/libs/TGUI/include -IC:/dev/libs/PLOG/include" -DCMAKE_EXE_LINKER_FLAGS="-LC:/dev/libs/SFML/lib -LC:/dev/libs/TGUI/lib"
```

The last thing to do now si to set the ``Working directory`` of the project. This can be done by going to ``Run -> Edit configurations``.
