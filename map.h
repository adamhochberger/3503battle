//
//  map.h
//  battle_ship_1
//
//  Created by Evan Waxman on 3/22/17.
//  Copyright © 2017 Evan Waxman. All rights reserved.
//

#ifndef map_h
#define map_h

#include <stdio.h>
#include <iostream>

using namespace std;

class map {
private:
    const static int size = 10;     // Size won't ever change
    
public:
    map();
    char mapArray[size][size];
    void printMap();
    bool hitCheck(map *guessMap, int coordinate[]);
    bool guessCheck(int coordinate[]);
};

// Constructor for map object
map::map() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mapArray[i][j] = '~';       // Default map element value is ~
        }
    }
}

// Checks if coordinate was already guessed
bool map::guessCheck(int coordinate[]) {
    if(mapArray[coordinate[0]][coordinate[1]] == 'X' || mapArray[coordinate[0]][coordinate[1]] == 'O') {    // Only other values for guess map
        return 1;
    }else {
        return 0;
    }
}

// Checks if ship was hit
bool map::hitCheck(map *guessMap, int coordinate[2]){
    if(mapArray[coordinate[0]][coordinate[1]] == '~'){
        guessMap->mapArray[coordinate[0]][coordinate[1]] = 'O';     // Update guess map
        return 0;
    }else {
        guessMap->mapArray[coordinate[0]][coordinate[1]] = 'X';     // Update guess map
        return 1;
    }
}

// Print mapArray of map
void map::printMap(){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << mapArray[i][j] << " " ;
        }
        cout << endl; //formats into square- new line after reaching 'gameSize'
    }
    cout << endl;
}


#endif /* map_h */

