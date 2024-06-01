# Magic Set Editor 2

Magic Set Editor, or MSE for short, is a program with which you can design your own cards for popular trading card games. MSE can then generate images of those cards that you can print or upload to the internet. Magic Set Editor also has a statistics window that will give useful information about your set, like the average mana cost, number of rares, etc. When you have finished your set, you can export it to an HTML file to use on the Internet, or to Apprentice or CCG Lackey so you can play with your cards online.

More information on https://magicseteditor.boards.net/

=======
## Main Features in the Unofficial Branch
 * Fixes the "All Image" art selector list to include .jpeg images.
 * Allows for the option to remove aliasing on selected art by increasing the size of the stored images in the set file.
 * Adds a text filter on the style tab for Stylesheet.
 * Decouples the zoom and export scales.

=======

## Dependencies

The code depends on
 * wxWidgets >= 3.0
 * boost
 * hunspell

## Building on Windows with Visual Studio

On windows, the program can be compiled with Visual Studio (recommended) or with mingw-gcc.
 * VS instructions up-to-date as of April 2024
 * Download and install [Visual Studio Community Edition](https://visualstudio.microsoft.com/vs/community/)
 * Download and install [vcpkg](https://github.com/microsoft/vcpkg)
 * Use vcpkg to install pkgconf, wxwidgets, boost, hunspell

=======
````
.\vcpkg install pkgconf wxwidgets boost-smart-ptr boost-regex boost-logic boost-pool boost-iterator hunspell --triplet=x64-windows-static
````
and/or
````
.\vcpkg install pkgconf wxwidgets boost-smart-ptr boost-regex boost-logic boost-pool boost-iterator hunspell --triplet=x86-windows-static
````
````
.\vcpkg integrate install
````

 * Then just use "Open Folder" from inside visual studio to open the Magic Set Editor source code root folder.
 * Select the configuration that you want to build (release x64-windows-static), and hit F7.

Notes:
 * You will most likely get a message about being unable to open hunspell-1.7.lib because pkgconf forgets to add the actual path to HUNSPELL_LIBRARIES. If so, uncomment the noted line in CMakeLists.txt (line 31) and point it to the root vcpkg installation to find the correct hunspell-1.7.lib file.

 * You may need to work around [this bug](https://github.com/microsoft/vcpkg/issues/4756) by replacing `$VCPATH\IDE\CommonExtensions\Microsoft\CMake\CMake\share\cmake-3.16\Modules\FindwxWidgets.cmake` with the file from  https://github.com/CaeruleusAqua/vcpkg-wx-find (`$VCPATH` is usually `C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7`)
 * vcpkg by default installs 32 bit versions of libraries, use `vcpkg install PACKAGENAME --triplet=x64-windows` if you want to enable a 64 bit build.
 * Similarly, to use a static build, use `vcpkg install PACKAGENAME --triplet=x32-windows` or `vcpkg install PACKAGENAME -triplet=x64-windows-static`.
 
For running tests you will also need to
 * Download and install perl (For example [Strawberry perl](http://strawberryperl.com/) or using [MSYS2](https://www.msys2.org/))
The tests can be run from inside visual studio

## Building on Windows with GCC (MSYS2)

 * Download and install [msys2](https://www.msys2.org/)
 * Install a recent version of the gcc compiler, cmake, and wxWidgets libraries:

```
pacman -S mingw32/mingw-w64-i686-gcc
pacman -S mingw32/mingw-w64-i686-wxWidgets
pacman -S mingw32/mingw-w64-i686-boost
pacman -S mingw32/mingw-w64-i686-hunspell
pacman -S cmake
```

   Use `mingw64/mingw-w64-x86_64-...` instead of for the 64bit build.
 * Build

```
cmake -G "MSYS Makefiles" -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

 Use `CMAKE_BUILD_TYPE=Debug` for a debug build.

## Building on Linux

 * Install the dependencies; for example, on a Debian-based system:

```
sudo apt install g++
sudo apt install libboost-dev libwxgtk3.0-gtk3-dev libhunspell-dev
```

Then use cmake to build:

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

 Use `CMAKE_BUILD_TYPE=Debug` for a debug build.

## Building on FreeBSD

 * Install the dependencies:

```
sudo pkg install hunspell cmake wx30-gtk3 boost-all
```

Then use cmake to build:

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

 Use `CMAKE_BUILD_TYPE=Debug` for a debug build.

## Building on Mac OS

 * Install the dependencies; for example, using Homebrew: (Note: Tested with boost 1.84.0, wxmac (wxwidgets) 3.2.4, hunspell 1.7.2, cmake 3.28.3, dylibbundler 1.0.5.)

```
brew install boost wxwidgets hunspell cmake dylibbundler
```

 * Then use cmake to build:

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_APPLE_BUNDLE=1 ..
cmake --build .
```

 Use `CMAKE_BUILD_TYPE=Debug` for a debug build.
 * Finally, copy the resources to a SharedSupport directory and run the executable:

```
mkdir magicseteditor.app/Contents/SharedSupport
cp -r ../resource magicseteditor.app/Contents/SharedSupport
open ./magicseteditor.app
```
