//
//  map.cpp
//  battle_ship_1
//
//  Created by Evan Waxman on 3/23/17.
//  Copyright © 2017 Evan Waxman. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include "map.h"

using namespace std;

int main(){
    // Declare each map object
    map player1ships;
    map player2ships;
    map player1guesses;
    map player2guesses;
    
    // Show initialized player1ships map
    player1ships.printMap();
    
    int coordinate[2];      // Used to store coordinate value for map indexing.
    
    // For testing. Test assigning map value to desired coordinate.
/*
    coordinate[0] = 2;
    coordinate[1] = 5;
    
    //player1ships.mapArray[coordinate[0]][coordinate[1]] = 'X';
    //player1guesses.mapArray[1][1] = 'X';
*/
    
    string input;   // Used to store input argument from user
    while(1) {
        cout << "Enter coordinate: ";
        cin >> input;
        coordinate[0] = input[0] - 0x41;    // First argument must be a char A-J. Subtract
                                            // 0x41 to get int value for array indexing.
                                            // Refer to ASCII table.
        coordinate[1] = input[1] - 0x31;    // Second argument must be a char 1-10. Subtract
                                            // 0x31 to get int value for array indexing.
                                            // Refer to ASCII table.

        if(player1guesses.guessCheck(coordinate)) {     // If coordinate was already guessed
            cout << "Already guessed that coordinate. Try again." << endl;
        }else {
            if(player1ships.hitCheck(&player1guesses, coordinate)) {    // If ship was hit
                cout << "Target hit!" << endl;
            }else {
                cout << "Target missed!" << endl;
            }
        }
        player1guesses.printMap();          // Print guess map to see changes
    }
}
