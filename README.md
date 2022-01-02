# C++ Project

## Contribution
1. Shridhar Sharma (IMT2020065)
   - Player 
   - Background
   - Leaderboard

2. Darshak Jivrajanai (IMT2020119)
   - Enemy
   - Scoring
  
3. Anurag Singh Naruka (IMT202093)
   - Platforms
   - Level Design
  
4. Arya Kondawar (IMT20200  
   - Main Menu
   - Changing Windows
  
5. Saugandh Krishna (IMT2020 
   - Music effects
 
## Prerequisites

### Install SDL
#### Linux ([Official Guide](https://wiki.libsdl.org/Installation)):
Install with :
```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-mixer-dev
```
Include the following files :
```
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
```

NOTE : On WSL, you need to be on Windows 11 Build 22000 or higher to run SDL. Follow [this](https://docs.microsoft.com/en-us/windows/wsl/tutorials/gui-apps) to enable native GUI support on WSL.

#### Windows : 
Refer to [this tutorial](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/index.php) to set up SDL on Windows.

### Run 
```
make all
./cuphead
```
