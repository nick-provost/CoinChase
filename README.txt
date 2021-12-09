Assignment 5 - The Final Game - Coin Chase
Nick Provost
CPSC 4160

This project exhibits a controllable character (resembling Spiderman)
in a pixel-esque world cointaining Coins of an amount that the player
can decide upon starting the game.

Coin Chase is a speed-based game, and the goal is to navigate the map
collecting all coins as quickly as possible. Once all coins are collected,
the game ends, showing the player their time and allowing them to either
exit the game or play again.

Coin Chase compiles on the SoC machines. To run Coin Chase, first make
the executable by running "make." Then, to run the executable, use the
command "./coin_chase"

The controls for the character allow for input from up to two keys
simultaneously and are as follows:

SINGLE-KEY INPUT:
W - Performs the "walk away" animation and moves the character 3 pixels
	up
A - Performs the "walk left" animation and moves the character 3 pixels
	to the left
S - Performs the "walk toward" animation and moves the character 3 pixels
	down
D - Performs the "walk right" animation and moves the character 3 pixels
	to the right
SPACE - Performs the "lunge" animation and moves the character 9 pixels
	in whichever x-direction they were last facing (Note: The
	character does not move in the y-direction unless using with
	W or S, as it is designed for faster movement)

MULTI-KEY INPUT:
W + A - Performs either the "walk left" or "walk away" animation (whichever
	was pressed last) and moves the character 3 pixels up and 3 pixels
	to the left
W + D - Performs either the "walk right" or "walk away" animation (whichever
	was pressed last) and moves the character 3 pixels up and 3 pixels
	to the right
S + A - Performs either the "walk left" or "walk toward" animation (whichever
	was pressed last) and moves the character 3 pixels down and 3 pixels
	to the left
S + D - Performs either the "walk right" or "walk toward" animation (whichever
	was pressed last) and moves the character 3 pixels down and 3 pixels
	to the right
SPACE + W - Performs the "lunge" animation and moves the character 3 pixels
	up and 9 pixels in whichever x-direction they were last facing
SPACE + S - Performs the "lunge" animation and moves the character 3 pixels
	down and 9 pixels in whichever x-direction they were last facing



IMAGE SOURCES:
(Note: some images were edited slightly to better fit my needs for this project)

Character Spritesheet: https://www.pngkit.com/bigpic/u2t4u2q8w7w7u2u2/

World Map Tilesheet: https://craftpix.net/product/summer-farm-top-down-2d-game-tileset/

Coin Image: https://www.pngegg.com/en/png-ertzr