[![Build Status](https://travis-ci.org/jean553/Memoris.svg?branch=master)](https://travis-ci.org/jean553/Memoris)

License : GNU GPL v3

# Memoris

![Image 1](github/readme.png)

Memoris is a C++ 14 video game developed using the SFML. The main goal is to move a pin on a grid of cells, from the departure to the arrival.
The player has to find all the stars on the map before going to the arrival cell. The whole map is only visible a few seconds before the game
starts. Then, all the cells are hidden. The player has to "memorize" the cells disposition before playing.

The map is full of special cells, including `one life more`, `additional time`... but also `one life less`, `less time`... !
The player has to find all the stars and the arrival before the available time is over.

**NOTE: this work is in progress. Some features are not implemented yet, some of them are partially implemented.**

### License and credits

The program is open-source, distributed under the GNU General Public License.

The game contains many assets (musics, sounds, pictures, fonts... etc...), all of them are distributed under various licenses ( CreativeCommons, GNU GPL/LGPL... etc... ).
(check the `Credits` section for details).

## Compatibility

Successfully compiled and executed on :
 * Ubuntu 14.04 LTS
 * Archlinux (2017-03-01)

## Installation

### Ubuntu 14.04 LTS

Compile and run:
```
curl -s https://raw.githubusercontent.com/jean553/Memoris/master/install.sh | sudo bash
```

### ArchLinux

Clone the project:
```
git clone https://github.com/jean553/Memoris
```

Install required tools:
```
pacman -S gcc cmake sfml
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
cmake -D CMAKE_CXX_COMPILER=g++ ..
make
```

## Documentation

```
sudo apt-get install doxygen
doxygen
```

## Credits

### Fonts

"Crystal" - http://openfontlibrary.org/en/font/crystal#CRYSTAL-Regular - Felipe Munoz - CreativeCommons BY 3.0 ( https://creativecommons.org/licenses/by/3.0/ )
This font is distributed under the CreativeCommons BY 3.0 terms (check licenses/cc_by_3.txt for details)

"Hi" - http://openfontlibrary.org/en/font/hi - Mew Too, Robert Jablonski - SIL Open Font License ( http://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL )
This font is distributed under the SIL Open Font License terms (check licenses/hi_font_sil_ofl.txt for details)

### Musics

Zeropage - Ambient Pills Update - Ambient Dance - CreativeCommons 3.0 BY (https://www.jamendo.com/track/23557/ambient-dance) (https://creativecommons.org/licenses/by/3.0/)

Zeropage - Ambient Pills - Void Sensor - CreativeCommons 3.0 BY (https://www.jamendo.com/track/20233/void-sensor) (https://creativecommons.org/licenses/by/3.0/)

Zeropage - Ambient Pills - Ambiose - CreativeCommons BY (https://www.jamendo.com/track/20235/ambiose) (https://creativecommons.org/licenses/by/3.0/)

Jamendo licenses information note: https://www.jamendo.com/legal/licenses

Music files have been converted from MP3 to OGG format. This is the only modification.

### Icons

https://www.iconfinder.com/recepkutuk - Free for commercial use
(departure cell image, arrival cell image)

https://www.iconfinder.com/iconsets/aiga-symbol-signs - Public domain
(stairs up cell image, stairs down cell image)

https://www.iconfinder.com/icons/2792947/christmas_star_xmas_icon - by Smashicons - CreativeCommons 3.0 BY (http://creativecommons.org/licenses/by/3.0/) - Resized
(star cell, star image)

https://www.iconfinder.com/icons/3547/favourite_heart_love_icon#size=128 - by Everaldo Coelho - LGPL
(life cell, life image)

https://www.iconfinder.com/icons/1493282/cancel_cross_exit_remove_icon#size=128 - by GlyphLab - Free for commercial use
(dead cell)

https://www.iconfinder.com/icons/2123964/app_essential_time_ui_icon#size=128 - by Just Icon - Free for commercial use
(more time cell, less time cell)

https://www.iconfinder.com/icons/173117/timer_icon#size=128 - by Snip Master - CreativeCommons 3.0 BY-NC (https://creativecommons.org/licenses/by-nc/3.0/) - Resized
(timer image)

https://www.iconfinder.com/icons/10576/wall_icon#size=128 - by Webdesigner Depot - Free for commercial use (author website: https://www.webdesignerdepot.com/)
(wall cell)

https://www.iconfinder.com/icons/352908/horizontal_mirror_icon#size=128 - by Appercuts Apps - Free for commercial use (author website: https://www.iconfinder.com/appercuts)
(horizontal mirror cell and vertical mirror cell)

https://www.iconfinder.com/icons/2561283/cw_rotate_icon#size=128 - by Cole Bemis - MIT License
(left rotation cell and right rotation cell)

https://www.iconfinder.com/icons/1055119/arrow_up_icon#size=128 - by Nick Roach - GPL
(editor up button and editor down button)

https://www.iconfinder.com/icons/1094176/code_elevator_emergency_sign_sos_icon#size=128 - by beguima - CreativeCommons 3.0 BY (https://creativecommons.org/licenses/by/3.0/) - Resized
(game elevator image)

https://www.iconfinder.com/icons/308945/arrow_up_icon#size=128 - by Ivan Boyko - CreativeCommons 3.0 BY (https://creativecommons.org/licenses/by/3.0/) - Resized
(elevator up cell and elevator down cell)

https://www.iconfinder.com/icons/216359/test_icon#size=128 - by Greepit - Free for commercial use
(test button)

https://www.iconfinder.com/icons/1054960/bullseye_target_icon#size=128 - by Nick Roach - GPL
(target image)

https://www.iconfinder.com/paomedia - CreativeCommons - BY 3.0 - https://creativecommons.org/licenses/by/3.0/
(new button image, quit button image)

https://www.iconfinder.com/icons/186411/arrow_down_icon#size=64 - Free for commercial use
(items list up image, items list down image)
