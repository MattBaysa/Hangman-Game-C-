#include <iostream>
using namespace std;
#include <string>
#include <cctype>

#include "hangman.h"

using namespace std;

int main()
{


    hangman game;
    char letter;
    char choice;
    string filename;
    bool gameOver = false;
    bool gameWon = false;

    cout << "Welcome to hangman, the test of your word guessing abilities\n"
            "The game will give you the amount of letters in a randomized word\n"
            "Then you will try to guess the letters that make up that word\n"
            "Simple really, BUT if the letter  you guessed is not in the word...\n"
            "A body part will be added to the man. Completely guess the word and win\n"
            "or finish the drawing of the hanged man and lose\n"
            "Would you like to play?? (y/n): ";
    cin >> choice;

    cout << endl;

    if(choice == 'y' || choice == 'Y'){ //player want to play so begin initialization of game
        cout << "Wonderful choice! Before we start, I need a file from you that follows the below stipulations\n"
                "1) It must have no more than 100 words\n"
                "2) All words must be in all UPPERCASE letter\n"
                "3) The words should only be seperated by a space or a new line\n"
                "Please provide the file path here: ";
        cin >> filename;


        if(!game.initializeFile(filename)){ //check if file is loaded okay
            cout << "file problem...exiting" << endl;
            return 0;
        }else
            cout << "file loaded OK!" << endl << endl;
    }
    else{
        cout << "Well I guess you can never lose if you never play....\n"
                "BUT you also can never win. Maybe next time you'll take the risk\n"
                "Goodbye......for now";
        return 0;
    }
    game.displayStatistics();


    while(choice == 'Y'|| choice == 'y'){
        bool stillWords;

        game.resetGame();
        stillWords = game.newWord();

        if(stillWords == false){ // check if all the words in the file have been used
            cout << "Looks like you've used up all the words in the file.\n"
                    "If you'd like to play again, restart me and enter in a new file.\n"
                    "I'll see you soon!";
            return 0;
        }

        game.displayGame();
        gameOver = false;
        gameWon = false;

        while(gameOver == false){
            cout << "Guess a letter: ";
            cin >> letter;
            game.guess(toupper(letter), gameOver, gameWon);
            game.displayGame();
        }
        game.revealWord();
        if(gameWon){
            cout << "Congrats you guessed correctly!!" << endl;
        }

        game.displayStatistics();

        cout << endl << "Would you like to play again? (y/n)";
        cin >> choice;
    }


    return 0;
}
