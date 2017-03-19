// Anything after // is a comment not actual C++ code
// // Comments are important and I use them to explain things
// // Why not read the comments in this code
//  
//  // These "include" code from the C++ library and SFML too
// #include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <math.h>
/*
#include "battleShip.h"
#include "bullet.h"
#include "holdShips.h"
#include "Factory.h"
*/
#define bulletSize 1
#define bulletSpeed 10
#define overshoot  20
#define marginOfError 4
#define scale1 .75
#define scale2 1.75
#define maxRange 10 // number of steps
class bullet: public sf::CircleShape{
        public:
                int explodeStage;
                int speed;
                int size;
                int xCoordTarget;
                int yCoordTarget;
                int directionX;
                int directionY;
                int numberOfSteps;
                int step;
        bullet(int XstartCoord, int YstartCoord, int TarCoorX, int TarCoorY ):sf::CircleShape(bulletSize){
            directionX = bulletSpeed*(TarCoorX-XstartCoord)/(sqrt( (TarCoorX-XstartCoord)*(TarCoorX-XstartCoord)+(TarCoorY-YstartCoord)*(TarCoorY-YstartCoord)));
            directionY = bulletSpeed*(TarCoorY-YstartCoord)/(sqrt( (TarCoorX-XstartCoord)*(TarCoorX-XstartCoord)+(TarCoorY-YstartCoord)*(TarCoorY-YstartCoord)));
                 step=0;    
                numberOfSteps= (sqrt( (TarCoorX-XstartCoord)*(TarCoorX-XstartCoord)+(TarCoorY-YstartCoord)*(TarCoorY-YstartCoord))) / bulletSpeed;
            this -> explodeStage = 0;
            this ->  xCoordTarget = TarCoorX;
            this ->  yCoordTarget    = TarCoorY;
            this ->  setOutlineColor(sf::Color::White);
            this ->  setOutlineThickness(1);
            this ->  setPosition(XstartCoord,YstartCoord);
               this-> go(); 
   sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(300,300);
   
        }
        bool go(){//bullet keeps going if not near the boat, explodes at end of range or if sufficently close to target.
               if(step==numberOfSteps&&true){
                    explode();
                    return true;
               }
               else if (step>maxRange){explode(); return false;}
        else{this->move(directionX,directionY); step++;}               
        }

        void explode(){
                if(explodeStage%2==0){
                     this->setOutlineThickness(0);
                     this->setOutlineColor(sf::Color::Red);   
                     this-> setFillColor(sf::Color::Blue);
                     this->scale(scale1, scale2);
                }
                else{
                    this->setOutlineColor(sf::Color::Blue);   
                    this-> setFillColor(sf::Color::Red);
                    this->setOutlineThickness(explodeStage);
                    this->scale(scale2,scale1); 
                }
                this->explodeStage++;
        }
};

class battleShip : public sf::RectangleShape{
        public:
                int currentRotation;
                int length;
                int width;
                int speed;
                int Direction;
    battleShip(): sf::RectangleShape(){
               this-> Direction=0;
                this-> width =4;
                this-> length = width*4;
                this-> speed =1;
                currentRotation =0;
    
         this-> setSize(sf::Vector2f(length,width));
       this->setOutlineColor(sf::Color::Red);
       this->setOutlineThickness(5);
      this->setPosition(100, 20);
         }
    void    setDirection(int i){
            this->Direction=i; 
            this-> setRotation(i*45+45);
    }
#define northWest 0
#define north 1
#define northEast 2
#define east 3
#define southEast 4
#define south 5
#define southWest 6
#define west 7

#define speed 5
#define WestEdge 0
#define EastEdge 1000
#define NorthEdge 0
#define SouthEdge 1000
#define changeDirectionThreshHold .95
             void wander(){
//                     this->move(100,100);
                   //Wander allows each boat to patrol on its own. If the boat goes off the edge of its boundary, it travels back. If the boat is not off the edge, it generally 
                   // * continues on the same path, but there is a small chance it turns. Direction is expressed as an int from 0-7 inclusive, with 0 being northwest, 1 being north
                   // * 2 being north east, 3 being east, 4 being south-east, 5 being south, 6 being south west and seven being west */                        
               int y = this->getPosition().y;
//                std::cout<<y<<std::endl;
                int x = this->getPosition().x; 
                                if( x<WestEdge){    //going East

                                     
//                                        this->move(speed,0);
                                                if( y<NorthEdge){// y is north of envelope and must head south
                                                    setDirection(southEast);
                                                    this->move(speed,-speed);
                                                } //move up
                                                else if (y>SouthEdge){//ship is south of south edge and must head north
                                                        setDirection(northEast);
                                                        this->move(speed,-speed);
                                                } //move down
                                                else{// just go east
                                                       this->move(speed,0);
                                                        setDirection(east);
                                                }
                                    }
                                else if ( x>EastEdge){//off of east edge must go west
                                      this->move(-speed,0);     
                                        if( y<0){
                                                setDirection(southWest);
                                                    this->move(0,speed);// move right
                                                } //move up
                                                else if (y>1000){
                                                    setDirection(northWest);
                                                    this->move(0,-speed);// move right
                                                } //move down
                                                else{ 
                                                    setDirection(west);
                                                }//not super important depends on the ship
                                }
                                else{// there is no interaction with the right-left boundary
                                      
                                             if( y<0){
                                                setDirection(south);
                                                    this->move(0,speed);// move down
                                                } //move up
                                                else if (y>1000){
                                                    setDirection(north);
                                                    this->move(0,-speed);// move up
                                                } 
                                             else{// there is no interaction with the boundaries
                                                if(  ((double) rand() / (RAND_MAX))<changeDirectionThreshHold){ // direction stays the same unless the random number is over a high value
                                                     switch(Direction){
                                                            case northWest:this->move(-speed,-speed); break;
                                                            case north:this->move(0,-speed);          break;
                                                            case northEast:this->move(speed,-speed);  break;
                                                            case east :this->move(speed,0);           break;  
                                                            case southEast:this->move(speed,speed);   break;
                                                            case south:this->move(0,speed);           break;  
                                                            case southWest:this->move(-speed,speed);  break;
                                                            case west:this->move(-speed,0);           break;  
                                                        }
                                                    }
                                                 else{
                                                    switch(   int (((double) rand() / (RAND_MAX))*8)) {//get a random int 0-7, pick a new direction 
                                                             case northWest: setDirection(northWest); break;
                                                             case north:  setDirection(north);          break;
                                                             case northEast:setDirection(northEast);  break;
                                                             case east : setDirection(east);           break;
                                                             case southEast: setDirection(southEast);   break;
                                                             case south: setDirection(south);           break;
                                                             case southWest: setDirection(southWest);  break;
                                                            }
                                                         }
                                                    }
                                        }
              }// wander function
};



class holdShips{// probably needs window to e passed in so it can draw the objects
        public:
                bool side;
                int numberHeld;
                std::vector<battleShip*> vec;

                holdShips(bool Side){
                numberHeld=0;
                this->side = side;
                std::vector<battleShip*> vec;
                }

               void  eachShip(){// each ship in the vector
               }

               void addShip(battleShip *thisShip ){
                       this->vec.push_back(thisShip);
                       numberHeld++;
               }
                
               bool getSide(){
                  return this->side;
                }
        void drawAll(){
          for(int i =0; i != this->numberHeld; i++){
                vec.at(i)->wander();
             //   vec.at(i)->
            }
        
        }

};
 /*
class Factory: public sf::RectangleShape{
        
        public:
                int productionCapacity;
                int type;
                bool side;
                holdShips *pointerToHolder;
                Factory(holdShips  *thisHolder):sf::RectangleShape(){
                     // this -> mySideHolder = thisHolder; 
                      this -> side = thisHolder->getSide();
                     this-> pointerToHolder = thisHolder;
                      this -> productionCapacity =100;
                      this -> type=0;
                      this -> setSize(sf::Vector2f(200,200));
                      this -> setPosition(80,80);
                
    this->setOutlineColor(sf::Color::Red);
    this->setOutlineThickness(5);
                }
               void  makeShip(){
                    battleShip thisShip= battleShip();
//create a new battleship object, then add it
               pointerToHolder->addShip(&thisShip);
              
               }};
*/
int main(){  
        
   // std::vector<*battleShip > vec;
   // static int frame =0;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Battle For The Atlantic!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(300,300);
    

// std::vector<*battleShip> left; // these hold all the ships, they are then passed into hold all. then hold all objects are used by factory. Hold all objects draw all required objects. 
  // std::vector<*battleShip> right;
 
//     holdShips  holdLefts(true);
  //   holdShips  holdRight(false); 
  
    battleShip myShip;
  //  Factory myFactory(&holdLefts);
    bullet myBullet(0,0,500,500);
    while (window.isOpen()){//event loop
//        if(frame==100){frame=0; } // this is intended to allow coordinated actions over several frames 
//        else{frame++; }
       
        sf::Event event;
        myShip.wander();
        while (window.pollEvent(event)){

                switch(event.type) {
                case sf::Event::Closed : window.close(); break; // prints "1",
                case sf::Event::KeyPressed:
                                         switch(event.key.code){
                                               case sf::Keyboard::Up: myShip.rotate(1); break; 
                                                 case sf::Keyboard::Down:myBullet.go(); break;
                                                 case sf::Keyboard::Left: shape.move(5,0); break;
                                                case sf::Keyboard::Right:myShip.wander(); break;
                                         }
            }
      }
        window.clear();
        window.draw(myBullet);
    //    window.draw(myFactory);
       window.draw(myShip);//draw all    
        window.draw(shape);
        window.display();
                          }
                            return 0;
}
