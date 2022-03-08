//
// Created by Matthew Baysa on 2/6/22.
//
#include <iostream>
using namespace std;

#ifndef P1_HANGMAN_H
#define P1_HANGMAN_H


class hangman : public error_code {
public:
    hangman();
    bool initializeFile(string);
    void displayStatistics();
    bool newWord();
    void displayGame();
    bool guess(char letter, bool& done, bool& won);
    void revealWord();
    void resetGame();
private:
    string words[100];
    string theWord;
    string blankWord;
    int letterAmt = 0;
    int wins = 0;
    int losses = 0;
    int numWords;
    int miss = 0;
    int fin = 0;
    int randNum;
    struct BodyPart : public error_code {
        string firstLine;
        string secondLine;
        string thirdLine;
        bool displaySecond;
        bool displayThird;
    };
    static const int BODY_SIZE = 9;
    BodyPart body[BODY_SIZE];
    char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K','L','M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    bool letterAvailable[26] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
};


#endif //P1_HANGMAN_H
