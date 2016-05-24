# pokeSlow
pokeSlow now allows a user to select a PHBankGB Box 1 Pokemon and edit its species, attacks, level, EVs, and IVs.

This was a fun little project I decided doing as a way to take a break from life every so often.  It is used in conjunction with the Pokemon Homebrew Bank for the First Generation Virtual Console Games on the 3DS (also known as PHBankGB).  pokeSlow also has an option to convert all pokemon you have saved in the first box of the bank into Slowpokes for no reason besides pure amusement.

My goal for this was to make a Gen 1 VC Pokemon editor on the 3DS in a small amount of time.  Optimizations can be made, as well as access to more boxes, but for my purposes, the goal was completed.

This app doesn't have any images besides the icon, but instead uses text menus to allow editing.

## Installation

Place the pokeSlow.3dsx and pokeSlow.smdh in the "3ds" directory of your SD Card, open up your favorite homebrew loader, and run the program.

## Menus and Usage

Be sure to have at least one Pokemon stored in the first box of the PHBankGB, as well as the relavent files for PHBankGB to run in the appropriate places.
Upon loading, the app makes a backup of the "bankgb" file called "bankgb.bak" in the same directory.  In case of error, revert to that.

The main menu contains the following:

1. Change a Pokemon's Species
2. Change a Pokemon's Attacks
3. Edit the Level of a Pokemon
4. Max a Pokemon's IVs
5. Max a Pokemon's EVs
6. Convert All Pokemon to Slowpokes
7. Exit

## A Note on Generation 1 IVs and EVs

In the first generation, IVs only go up to 15, and EVs go up to 65535 each (about 255 squared).  Unlike future generations, EVs can each be maxed, instead of the 510 point limit per Pokemon.

## Credits

Thanks to gocario for PHBankGB, xem for the fun 3DS Homebrew Tutorial, and the Citra development team for their emulator, Citra.
