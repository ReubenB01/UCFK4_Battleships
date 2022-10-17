ENCE260 Assignment 2020
Group: 136
Developers: Reuben Brown(RBR99) Treasa Glubb(TGL24)

----------BATTLE SHIPS----------

A Two-player game using two UCFK4 (UC Funkit) microcontrollers. 
Battleships is a stategy guessing game, fire at your opponent's ships and sink their fleet before they sink yours.

---------HOW TO DOWNLOAD---------

-Open terminal window and enter the desired directory.
-Run Command "git clone https://eng-git.canterbury.ac.nz/ence260-2022/group_136" to download the game files.
-Run Command "make" to compile the code.
-Plug both UCFK4 microcontrollers into the same computer.
-Run command "make program" twice to load the game onto both microcontrollers.

-----------HOW TO PLAY-----------

Before the game starts, both players will be in the start menu.
Aim the infrared sensors on the microcontrollers towards each other so they can communicate. 
To start the game the player who wishes to be player1 should press down the navswitch.

---Placing your ships---

Both players will now be able to place their ships.
Each player will have 4 ships to place of varying length, 1 x length 3, 1 x length 2, 2 x length 1
Use the button to choose to place your ship horizontally or vertically on the board.
Push the navswitch north, east, south, west to move your ship to your desired location.
Push the navswitch down to place your ship.
Ships have to be placed to they lie entirely on the led matrix and can not be placed on top of each other.

---FIRING CANNONS---
Once both players have placed all 4 ships player1 will be able to fire their cannon.
Push north, east, south, west on the navwitch to choose the tile you wish to fire your cannons at.
Push down on the navswitch to fire the cannon.
The LED display will tell you whether you hit or missed your opponent's ship.
If you have hit a ship the tile you chose will blink.
If you miss your opponent's ship the tile you chose will stay on.

---WINNING AND LOSING---
You and your opponent will take turns firing at each others ships.
First person to hit all 7 of their opponent's ship tiles wins.
"WIN" will be displayed on the winning player's LED display.
"LOSE" will be dispayed on the losing player's LED display

---RESETTING THE GAME---

To reset the game and play again hold down the button, press the reset button then let go of the button.
You will be taken back to the start screen if you reset the game.





