# Sorrylike-Console-Game
Final Project for Computer Science 101 written in c++.
 
CSCI 101 Final Project
C++ Game Program

INTRODUCTION: Play sorry with two die, and one peg. Move your piece down the board first. But rolling certain numbers will change the pace of the game. 
INCLUDE IN YOUR ASSIGNMENT: Annotation is a major part of any program. At the top of each of your C++ programs, you should have at least four lines of documentation:
// Program name: tictactoe.cpp
// Author: Twilight Sparkle
// Date last updated: 5/26/2016
// Purpose: Play the game of Tic-Tac-Toe

ASSIGNMENT: Sorry Game
	
1. To play “Sorry”, you’ll need to create up to Four players.
    Prompt the user for the number of players (2-4).
3. Create two die for the players to roll.
4. Create an Array to be used to track the player’s positions on the playing board.
5. The playing board has 50 spaces (with 50 being the winning space).
6. The dice have special conditions:
		2 = Move two spaces
		3 = Move three spaces
		4 = Move back one space.
		5 = Move five spaces.
		6 = Move six spaces.
		7 = Swap spots with the leading layer / or nothing if player is in lead.
		8 = Move Eight spaces.
		9 = Move nine spaces.
		10 = Move ten spaces.
		11 = Swap spots with the last player / or do nothing if player is last.
		12 = Start Over
6.  A player must roll a double to start.
7.  If a player lands on the same space as another, the other player must return to the beginning.
		  Example: If P1 lands on a space where P3 is, P3 would go back to the start.
8. A player must roll an EXACT number to enter the winning space.
9. Use a random Generator to “roll” the dice, the user must press enter to roll.
10. Depict the players’ positions on the screen after each round.
11. Once a player finishes, create a winning message announcing the winner.
12. Then ask the user if they would like to play again.
13. You must use at least three functions. Some function examples could be:
		  Roll dice, check for other player (when moving), display board.
14. Display the status/location of the players between sets of rolls.
15. Depict a Playing Board on the screen and display the Players’ position on the board. (Extra Credit)
		(maybe try using a method to create the board and screen each time a player moves)
16. If a player rolls a double, they’ll get another roll (Extra Credit).
	17. If a player rolls two doubles in a row, they Start Over (Extra Credit).
