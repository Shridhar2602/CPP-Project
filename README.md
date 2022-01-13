# C++ Project

Recreating a platforming level of [Cuphead](https://store.steampowered.com/app/268910/Cuphead/) using SDL.

## Screenshots

![Screenshot (6)](https://user-images.githubusercontent.com/63835433/149332188-da744131-44d7-4363-b1d9-5404df990d81.png)
![Screenshot (7)](https://user-images.githubusercontent.com/63835433/149332205-9d116831-daf6-4cf5-9fb8-5c8d59edadad.png)
![Screenshot (11)](https://user-images.githubusercontent.com/63835433/149332224-ae92734c-93fd-4a01-8ae4-7bbcd09e682d.png)
![Screenshot (14)](https://user-images.githubusercontent.com/63835433/149332253-649c048d-e78f-40bc-a322-1984e8f48608.png)
![Screenshot (15)](https://user-images.githubusercontent.com/63835433/149332404-e8520ac5-1788-4d4e-a998-dbb872f8862b.png)
![Screenshot (18)](https://user-images.githubusercontent.com/63835433/149332262-fecbdea5-3cc9-46a2-b118-277f5dac5822.png)
![Screenshot (19)](https://user-images.githubusercontent.com/63835433/149332271-6fccaf56-b0de-4d10-967a-94b9a366bd53.png)

### Run 
```
make all
./cuphead
```
### Controls

- Left : Move left
- Right : Move right
- Z : Jump
- X : Shoot

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
