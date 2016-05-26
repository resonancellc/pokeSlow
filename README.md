# pokeSlow
pokeSlow now allows a user to select a PHBankGB Box 1 Pokemon and edit its species, attacks, level, EVs, and IVs.  There is also a feature to import a first generation .pkm file located on the SD card at "/pk/bank/pokemon.pkm".

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
7. Import pokemon.pkm from SD 
8. Exit

## Glitch Pokemon - I don't recommend this

There have been problems with editing Mew into the game.  My theory is this has to do with Mew's coding in the game, as it wasn't coded like a regular Pokemon.  Due to this, any attempts to change a species to Mew will result in a Rhydon.

The alternative to get a Mew is using the pokemon.pkm injector with a Mew obtained from a save.  Getting a Mew from the Mew Glitch won't result in a bad Pokemon, because of the way the Mew is called into battle (unlike Missingno).
This can be done on the VC games, but finding a clone of the 1999 TRU Mew online is a bit more memorable.

With this feature, those experienced enough can get a GlitchDex.  Though, please don't try this if you don't have knoweldge on the various glitches in the game, as some are extremely dangerous.

## A Note on Generation 1 IVs and EVs

In the first generation, IVs only go up to 15, and EVs go up to 65535 each (about 255 squared).  Unlike future generations, EVs can each be maxed, instead of the 510 point limit per Pokemon.

## Credits

Thanks to gocario for PHBankGB, xem for the fun 3DS Homebrew Tutorial, and the Citra development team for their emulator, Citra.
