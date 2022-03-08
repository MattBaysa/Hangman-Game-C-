//
// Created by Matthew Baysa on 2/6/22.
//

#include "hangman.h"
#include "hangman.h"
#include<fstream>
#include<string>
#include<stdlib.h>

hangman::hangman(){
    body[0].firstLine = "    ----\n";
    body[1].firstLine = "    |  |\n";
    body[2].firstLine = "       |\n";
    body[2].secondLine = "    O  |\n";
    body[3].firstLine = "       |\n";
    body[3].secondLine = "    |  |\n";
    body[4].firstLine = "       |\n";
    body[4].secondLine = "   -|  |\n";
    body[4].thirdLine = "   -|- |\n";
    body[5].firstLine = "       |\n";
    body[5].secondLine = "    |  |\n";
    body[6].firstLine = "       |\n";
    body[6].secondLine = "   /   |\n";
    body[6].thirdLine = "   / \\ |\n";
    body[7].firstLine = "       |\n";
    body[8].firstLine = "_______|___\n";
    for (int i = 0; i < BODY_SIZE; i++){
        body[i].displaySecond = false;
        body[i].displayThird = false;
    }
}

bool hangman::initializeFile(string filename){
    const string FILEN = filename;
    int i = 0;

    ifstream inFile;
    string word;
    bool didItWork;
    inFile.open(FILEN);

    if(!inFile.fail()){
        while(inFile>>word){
            words[i] = word;
            i++;
        }
        didItWork = true;
    }
    else{
        didItWork = false;
    }
    inFile.close();

    numWords = i; //amount of words in the list

    return didItWork;
}


void hangman::displayStatistics() {
    cout << "Wins: " << wins << endl;
    cout << "Losses: " << losses << endl;
    cout << "Words from file: " << numWords << endl;
    cout << "Words still available to play: " << numWords - (wins+losses) << endl;
}

bool hangman::newWord(){
//    int randNum = 0;
    bool stillWords = true;

    if((numWords - (wins+losses)) == 0){
        stillWords = false;
    }
    else {
        randNum = rand() % numWords; // create random number between 0 and amount of words
        while (words[randNum] == "") { // checks if number/word has already been used and new number/word if it has
            randNum = rand() % numWords;
        }

        theWord = words[randNum]; //use randomized number to choose target word

        words[randNum] = ""; // change location of word to empty to avoid using words twice


        for (int i = 0; theWord[i] != '\0'; i++) {
            letterAmt++; //amount of letters in word
            blankWord[i] = '_'; //creates the word to be guessed
        }
    }

    return stillWords;
}

void hangman::displayGame(){
    if(miss == 0){
        for (int i = 0; i < BODY_SIZE; i++){
            body[i].displaySecond = false;
            body[i].displayThird = false;
        }
    }
    else if(miss == 1){
        body[2].displaySecond = true;
    }
    else if(miss == 2){
        body[2].displaySecond = true;
        body[3].displaySecond = true;
    }
    else if(miss == 3){
        body[2].displaySecond = true;
        body[3].displaySecond = true;
        body[4].displaySecond = true;
    }
    else if(miss == 4){
        body[2].displaySecond = true;
        body[3].displaySecond = true;
        body[4].displaySecond = false;
        body[4].displayThird = true;
    }
    else if(miss == 5){
        body[2].displaySecond = true;
        body[3].displaySecond = true;
        body[4].displaySecond = false;
        body[4].displayThird = true;
        body[5].displaySecond = true;
    }
    else if(miss == 6){
        body[2].displaySecond = true;
        body[3].displaySecond = true;
        body[4].displaySecond = false;
        body[4].displayThird = true;
        body[5].displaySecond = true;
        body[6].displaySecond = true;
    }
    else if(miss == 7){
        body[2].displaySecond = true;
        body[3].displaySecond = true;
        body[4].displaySecond = false;
        body[4].displayThird = true;
        body[5].displaySecond = true;
        body[6].displaySecond = false;
        body[6].displayThird = true;
    }


    for(int i = 0; i < BODY_SIZE; i++){
        if(body[i].displaySecond == true){
            cout << body[i].secondLine;
        }
        else if(body[i].displayThird == true){
            cout << body[i].thirdLine;
        }
        else{
            cout << body[i].firstLine;
        }

    }

    cout << "\nYour Word: ";
    for(int i = 0; i < letterAmt; i++){
        cout << blankWord[i] << ' ';
    }

    cout << "\nLetters Available: ";
    for(int i = 0; i<26; i++){
        if(letterAvailable[i] == 1){//if letter is available
            cout << alphabet[i] << ' ';
        }
    }
    cout << endl;
}

bool hangman::guess(char letter, bool& done, bool& won){
    bool letInWord = false;

    int letterLoc = 0;
    for(int i=0; i<26; i++){ //find indices of letter in alphabet
        if(alphabet[i] == letter){
            letterLoc = i;
        }
    }

    letterAvailable[letterLoc] = 0; // says that letter has been guessed

    for(int i = 0; i<letterAmt; i++){//look for guessed letter in word
        if(theWord[i] == letter){//letter is in word
            blankWord[i] = letter;
            letInWord = true;
            fin += 1;
        }
    }

    if(letInWord == false) {
        miss += 1;//used to see if the word is complete or not
    }

    if(fin == letterAmt){//if the amount letters in the word is correctly guess
        won = true;
        done = true;
        wins += 1;
    }
    else if(miss == 7){//if the amount of wrong guesses reaches max
        done = true;
        losses += 1;
    }

    return  letInWord;
}

void hangman::revealWord(){
    cout << "The word was .... " << theWord << endl;
}

void hangman::resetGame() {
    blankWord = ""; //reset blankWord
    letterAmt = 0; //reset letterAmt
    miss = 0; //reset miss counter
    fin = 0; //reset correct letters in word
    for(int i = 0; i<26; i++){ //reset available letters in alphabet
        letterAvailable[i] = 1;
    }
}