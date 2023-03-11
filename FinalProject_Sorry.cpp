/* Program Name: FinalProject_Sorry.cpp
*  Author: Alonzo West
*  Date Last Updated: 3/10/2023
*  Purpose: Create a game of Sorry with 2 dice.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

/*KNOWN ISSUES
  First slot on the game board only shows one player
  Entering a char to and int variable causes infinite loop*/

using namespace std;

// Struct for player's info to easily add more features like times rolled, doubles rolled, previous roll, etc.
struct playerType {
    string name = "";
    int position = 0; // board position
    bool lastRollDouble = false;
};

// Function Prototypes
void pageHeader(string, string, int);
void displayRules(int);
int rollDie();
bool isValidMove(int, int);
int leader(int, playerType[4]);
int lastPlace(int, playerType[4]);
int simpleMove(int);
void swapPositions(playerType, playerType);
void movePieces(int, int, int, playerType[4]);
void printPlayerPositions(int, playerType[4]);
void printBoard(int[51]);
void clearBoard(int[51]);


int main() {
    while (true) {
        // Variables
        int pageWidth = 108; // set page width for cleanliness
        int gameBoard[51]; // 50 spaces + 1 for waiting to get on the board
        playerType playerInfo[4]; // Array of structs for four max players
        int numPlayers;
        int dieOne;
        int dieTwo;
        int prevPosition;
        bool playGame = true; // Game's on/off switch
        int round = 1; // Counter for number of rounds
        bool increment; // Determine whether to move to next player in loop
        string winner;

        // Head section of program
        pageHeader("SORRY GAME", // Title
            "Lets play a game of Sorry with 2 dice and 2-4 players!",
            pageWidth); // Page Width

        // Display rules before play and press enter to continue.
        displayRules(pageWidth);


        // Get number of players
        cout << "How many people are playing? ";
        do {
            cin >> numPlayers;
            cin.ignore(); // remove the new line char from the input stream
            if (numPlayers < 2 || numPlayers > 4) {
                cout << "Invalid number of players. Please try again.\n";
            }
        } while (numPlayers < 2 || numPlayers > 4); // Input validation - Only 2-4 players can play this game.;

        // Register player names to an array of structs
        for (int i = 0; i < numPlayers; i++) {
            cout << "Player " << i + 1 << " Name: ";
            getline(cin, playerInfo[i].name); // getline incase players want first and last names
        }

        // Seed the random number generator
        srand(time(0) * time(0)); // time(0) squared to give better randomness

        // Game Loop
        while (playGame) {
            cout << setw((pageWidth + 13) / 2) << "( ROUND " << round << " )\n";

            // Round Loop
            for (int i = 0; i < numPlayers;) { // Incrementing the loop within the code. 
                cout << "\n____________________________________\n";
                cout << "Its " + playerInfo[i].name + "'s turn.\n"
                    << "Press ENTER to Roll Dice.";

                // Wait for player to press enter to roll the dice.
                cin.get();
                prevPosition = playerInfo[i].position;
                dieOne = rollDie();
                dieTwo = rollDie();

                cout << '\n' << playerInfo[i].name << " rolled [" << dieOne << "] and [" << dieTwo << "]\n";

                // Check if player is on the board and if the roll is a valid movement
                if (isValidMove(playerInfo[i].position, (dieOne + dieTwo))) {
                    // Will not increment when player recieves another turn. (Rolls double)
                    if (dieOne == dieTwo) {
                        if (playerInfo[i].lastRollDouble == true) {
                            playerInfo[i].position = 1;
                            cout << playerInfo[i].name + " rolled two doubles in a row! Go back to square one!\n";

                            // Reset lastRollDouble status incase they roll another double next round
                            playerInfo[i].lastRollDouble = false;
                        }
                        else {
                            cout << '\n' + playerInfo[i].name + " rolled a double! They get another turn!\n";

                            // Update Player positions
                            movePieces((dieOne + dieTwo), i, numPlayers, playerInfo);

                            playerInfo[i].lastRollDouble = true;
                        }
                        // Rules say rolling double is always another turn (besides first roll)
                        increment = false;

                    }
                    else {
                        // Update Player positions
                        movePieces((dieOne + dieTwo), i, numPlayers, playerInfo);

                        playerInfo[i].lastRollDouble = false;
                        increment = true;
                    }
                }
                else if (dieOne == dieTwo && playerInfo[i].position == 0) {
                    cout << '\n' + playerInfo[i].name + " is on the board!\n";

                    // Update Player position (first time)
                    playerInfo[i].position = 1;
                    increment = true;
                }
                else if (playerInfo[i].position == 0) {
                    cout << "\nSorry! Must roll double to begin.\n";
                    increment = true;
                }
                else {
                    cout << "\nSorry! No move available.\n";

                    if (dieOne == dieTwo) {
                        cout << '\n' + playerInfo[i].name + " rolled a double! They get another turn!\n";

                        playerInfo[i].lastRollDouble = true;
                        increment = false;
                    }
                    else {
                        playerInfo[i].lastRollDouble = false;
                        increment = true;
                    }
                }

                // Show movement
                cout << "Movement: " << prevPosition << " -> " << playerInfo[i].position << '\n';

                // Check for a winning move
                if (playerInfo[i].position == 50) {
                    winner = playerInfo[i].name;
                    playGame = false;
                    break;
                }

                // Increment the loop as long as character doesnt get another turn
                if (increment == true) {
                    i++;
                }
            }

            // Assign players positions to the game board array
            for (int i = 0; i < numPlayers; i++) {
                gameBoard[playerInfo[i].position] = i + 1;
            }

            // Display players' positions above the board
            printPlayerPositions(numPlayers, playerInfo);

            // Show updated board positions at the end of each round
            printBoard(gameBoard);
            clearBoard(gameBoard);

            if (playGame == false) {
                cout << setw((pageWidth + 9) / 2) << "WINNER!\n"
                    << setw((pageWidth + winner.length() + 17) / 2) << "Congratulations " + winner + '!' << "\n\n";
            }

            round++;
        }

        // Ask to play again
        cout << setw((pageWidth + 37) / 2) << "Would you like to play again? (y/n) ";
        if (cin.get() == 'y') {
            cout << "\n\n\n\n\n\n\n";
            continue;
        }
        else {
            cout << '\n' << setw((pageWidth + 31) / 2) << "Until next time! Goodbye!\n\n\n";
            break;
        }
    }
    return 0;
}

// Function to center the title over the description
void pageHeader(string title, string description, int pageWidth) {
    cout << setw((pageWidth + title.length()) / 2) << title << '\n' << setfill('=') << setw(pageWidth) << ""
        << setfill(' ')
        << '\n' << setw((pageWidth + description.length()) / 2) << description << "\n\n";
}

// Displays the list of rules
void displayRules(int pageWidth) {
    cout << setw((pageWidth + 7) / 2) << "RULES\n"
        << setfill('-') << setw(pageWidth) << "" << '\n'
        << "1. Players must roll a double to begin!\n"
        << "2. A player must roll an EXACT number to enter the winning space.\n"
        << "3. Landing on a space occupied by another player sends them back to square one.\n"
        << "4. Rolling a double after a double sends you back to square one.\n"
        << "5. Dice rolls have the following actions:\n"
        << "\t2 = Move two spaces\n"
        << "\t3 = Move three spaces\n"
        << "\t4 = Move back one space\n"
        << "\t5 = Move five spaces\n"
        << "\t6 = Move six spaces\n"
        << "\t7 = Swap spots with the leading layer (if already in lead, nothing)\n"
        << "\t8 = Move Eight spaces\n"
        << "\t9 = Move nine spaces\n"
        << "\t10 = Move ten spaces\n"
        << "\t11 = Swap spots with the last player (if already in last ,nothing)\n"
        << "\t12 = Start Over\n"
        << setw(pageWidth) << "" << "\n\n"
        << setfill(' ');
}

// Roll Dice
int rollDie() {
    return rand() % 6 + 1;
}

// Check for valid movement once a player is on the board
bool isValidMove(int position, int diceRoll) {
    if (position == 0) {
        return false;
    }
    else if (position + simpleMove(diceRoll) > 0 && position + simpleMove(diceRoll) < 51) {
        return true;
    }
    else {
        return false;
    }
}

// Player piece movement logic
int simpleMove(int diceRoll) { // NEED TO FIX POSITION UPDATE
    if (diceRoll == 4) {
        return -1;
    }
    else if (diceRoll == 7 || diceRoll == 11 || diceRoll == 12) {
        return 0;
    }
    else {
        return diceRoll;
    }
}

// Function to swap any two players' positions
void swapPositions(int indexOne, int indexTwo, playerType playerInfo[4]) {
    int temp = playerInfo[indexOne].position;
    playerInfo[indexOne].position = playerInfo[indexTwo].position;
    playerInfo[indexTwo].position = temp;
}

// Function to do all the piece movements
void movePieces(int diceRoll, int currentIndex, int numPlayers, playerType playerInfo[4]) {
    cout << '\n';
    if (diceRoll == 7) {
        cout << playerInfo[currentIndex].name + " rolled a 7! Swap positions with the leader!\n";
        swapPositions(currentIndex, leader(numPlayers, playerInfo), playerInfo);
    }
    else if (diceRoll == 11) {
        cout << playerInfo[currentIndex].name + " rolled an 11! Swap positions with last place!\n";
        //Dont swap with someone who isnt on the board yet
        if (playerInfo[lastPlace(numPlayers, playerInfo)].position != 0) {
            swapPositions(currentIndex, lastPlace(numPlayers, playerInfo), playerInfo);
        }
    }
    else if (diceRoll == 12) {
        cout << playerInfo[currentIndex].name + " rolled a 12! Go back to square one!\n";
        playerInfo[currentIndex].position = 1;
    }
    else {
        // After moving if another player is also in same spot bump them back to spot 1
        playerInfo[currentIndex].position += simpleMove(diceRoll);
        for (int i = 0; i < numPlayers; i++) {
            // If not cuurent player AND the current players new position is the same as another players AND the position is greter than 1
            if (i != currentIndex && playerInfo[currentIndex].position == playerInfo[i].position && playerInfo[currentIndex].position > 1) {
                playerInfo[i].position = 1;
                cout << playerInfo[currentIndex].name + " landed on top of " + playerInfo[i].name + " and sent them back to square 1!\n";
            }
        }
    }
}

// Find the Leaders index
int leader(int numPlayers, playerType playerInfo[4]) {
    int leadIndex = 0;
    for (int i = 1; i < numPlayers; i++) {
        if (playerInfo[i].position > playerInfo[i - 1].position) {
            leadIndex = i;
        }
    }
    return leadIndex;
}

// Find whos in last place
int lastPlace(int numPlayers, playerType playerInfo[4]) {
    int lastIndex = 0;
    for (int i = 1; i < numPlayers; i++) {
        if (playerInfo[i].position < playerInfo[i - 1].position) {
            lastIndex = i;
        }
    }
    return lastIndex;
}

void printPlayerPositions(int numPlayers, playerType playerInfo[4]) {
    cout << "\n____________________________________\n";

    for (int i = 0; i < numPlayers; i++) {
        cout << 'P' << i + 1 << ": " + playerInfo[i].name + ' ' << left << setw(8) << playerInfo[i].position << right;
    }
    cout << endl;

    // Restore formatting to default settings
    cout.unsetf(ios::left); cout.unsetf(ios::right);
}

void printBoard(int gameBoard[51]) {
    for (int i = 1; i <= 50; i++) {
        if (gameBoard[i] > 0) {
            cout << "[P" << gameBoard[i] << ']';
        }
        else {
            cout << "[]";
        }
    };
    cout << "\n\n" << endl;
}

void clearBoard(int gameBoard[51]) {
    for (int i = 0; i < 51; i++) {
        gameBoard[i] = 0;
    }
}

