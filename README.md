[![Build Status](https://travis-ci.org/jean553/Memoris.svg?branch=master)](https://travis-ci.org/jean553/Memoris)

License : GNU GPL v3

# Memoris

![Image 1](github/readme.png)

Memoris is a C++ 14 video game developed using the SFML. The main goal is to move a pin on a grid of cells, from the departure to the arrival.
The player has to find all the stars on the map before going to the arrival cell. The whole map is only visible a few seconds before the game
starts and all the cells are suddently hidden. The player has to "memorize" the cells disposition before playing.

The map is full of bonus, lifes, additional time... but also malus ! The player has to find all the stars and the arrival before the countdown
finishes.

There are also many events cell on the map that move the disposition of the cells : symmetry effects, teleportation, walls, floors switch... etc...

**NOTE: this work is in progress. Some features are not implemented yet, some of them are partially implemented.**

### License and credits

The program is open-source, distributed under the GNU General Public License. The game contains many assets ( musics, sounds, pictures, fonts... etc... ), all of them are distributed under various licenses ( CreativeCommons, GNU GPL/LGPL... etc... ). 

After individual verification of each asset license, all of them can be included into the project. Each asset source is specified in the "Credits" section of the README.md file. 

**If you are the author of some of them and you don't want these resources to be used in Memoris, just let me know. The asset will be deleted immediately.**

## Compatibility

Successfully compiled on :
 * Ubuntu 14.04 LTS.

Successfully executed on :
 * Ubuntu 14.04 LTS
 * Debian 8

## Compile and run
```
curl -s https://raw.githubusercontent.com/jean553/Memoris/master/install.sh | sudo bash
```

## Installation on Ubuntu 14.04 LTS

Requirements to compile C++14 code:

```
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
```

Install compilation tools:

```
sudo apt-get install g++-4.9 libsfml-dev cmake clang-3.5
```

## Execution

Execute the game from the root directory :

```
./bin/Memoris
```

## Development

Memoris is developed into a dedicated Docker container including all the required tools and development facilities.
Available here : [memoris-dev](https://github.com/jean553/memoris-dev)

To compile the sources manually, just execute :

```
mkdir build && cd build/
cmake ..
make
```

## Documentation

```
sudo apt-get install doxygen
doxygen
```

## Apply Allman coding style

```
./style.sh
```

## Credits

### Fonts

"Crystal" - http://openfontlibrary.org/en/font/crystal#CRYSTAL-Regular - Felipe Munoz - CreativeCommons BY 3.0 ( https://creativecommons.org/licenses/by/3.0/ )

"Hi" - http://openfontlibrary.org/en/font/hi - Mew Too, Robert Jablonski - SIL Open Font License ( http://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL )

"Limousine" - https://fontlibrary.org/en/font/limousine - OSP - GNU General Public License ( http://www.gnu.org/copyleft/gpl.html )

### Musics

Zeropage - Ambient Pills Update - Ambient Dance - CreativeCommons 3.0 BY (https://www.jamendo.com/track/23557/ambient-dance) (https://creativecommons.org/licenses/by/3.0/)

Zeropage - Ambient Pills - Void Sensor - CreativeCommons 3.0 BY (https://www.jamendo.com/track/20233/void-sensor) (https://creativecommons.org/licenses/by/3.0/)

Music files have been converted from MP3 to OGG format. This is the only modification.

### Icons

https://www.iconfinder.com/recepkutuk - Free for commercial use

https://www.iconfinder.com/iconsets/aiga-symbol-signs - Public domain

https://www.iconfinder.com/andromina - CreativeCommons 3.0 BY http://creativecommons.org/licenses/by/3.0/ - No changes have been made

http://www.webdesignerdepot.com/2009/03/200-free-exclusive-icons-siena/ - Free for commercial use with link to author website

http://www.danilodemarco.com/100-pictograms-icons/ - Free for commercial use with link to author website

http://www.icons-gallery.com - GNU GPL / GNU LGPL

https://www.iconfinder.com/snipicons - CreativeCommons - BY-NC 3.0 - http://creativecommons.org/licenses/by-nc/3.0/ ( images have been resized and integrated in others )

http://appercuts.blogspot.fr/ - Free for commercial use with link to author website

https://www.iconfinder.com/Squid.ink / http://thesquid.ink/flat-icons/ - CreativeCommons - BY 3.0 - http://creativecommons.org/licenses/by/3.0/

https://www.iconfinder.com/icons/1055053/controller_game_controller_video_game_icon#size=128 / http://www.elegantthemes.com/ - GNU GPL

http://code.google.com/u/newmooon/ - GNU GPL

https://www.iconfinder.com/paomedia - CreativeCommons - BY 3.0 - https://creativecommons.org/licenses/by/3.0/ 

https://www.elegantthemes.com/ - https://www.iconfinder.com/iconsets/circle-icons-1 - GNU GPL

### Sounds

All sounds files have been downloaded from www.universal-soundbank.com. They have
been converted from .mp3 to .wav. This is the only modification.
