#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  // Makes a BST of cards to represent each player's hands
  BST handA;
  BST handB;
  string suit;
  string value;
  int val;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    suit = line.substr(0,1);
    value = line.substr(2);
    // Converts string values to int values
    if (value == "a")
      val = 1;
    else if (value == "j")
      val = 11;
    else if (value == "q")
      val = 12;
    else if (value == "k")
      val = 13;
    else 
      val = stoi(value);

    Card car(suit, val);
    handA.insert(car);
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() > 0)){
    suit = line.substr(0,1);
    value = line.substr(2);
    // Converts string values to int values
    if (value == "a")
      val = 1;
    else if (value == "j")
      val = 11;
    else if (value == "q")
      val = 12;
    else if (value == "k")
      val = 13;
    else 
      val = stoi(value);

    Card car(suit, val);
    handB.insert(car);
  }
  cardFile2.close();
  
  // Actual game
  //int turn = 0;
  bool play = true;
  Card car1;
  Card car2;

  /*
  while (play) {
    if (turn % 2 == 0) {
      car = handA.gameTurnMin(handB);
      if (car.getValue() != 0) {
        cout << "Alice picked matching card ";
        car.print();
      }
      else {
        play = false;
      }
    }
    else {
      car = handB.gameTurnMax(handA);
      if (car.getValue() != 0) {
        cout << "Bob picked matching card ";
        car.print();
      }
      else {
        play = false;
      }
    }
    turn++;
  }
  */

  while (play) {
    car1 = handA.gameTurnMin(handB);
    if (car1.getValue() != 0) {
      cout << "Alice picked matching card ";
      car1.print();
    }
    car2 = handB.gameTurnMax(handA);
    if (car2.getValue() != 0) {
      cout << "Bob picked matching card ";
      car2.print();
    }  
    if (car1.getValue() == 0 && car2.getValue() == 0) {
      play = false;
    }
  }
  // Game ends, print hands
  cout << endl;
  cout << "Alice's cards:" << endl;
  handA.printInOrder();
  cout << endl;
  cout << "Bob's cards:" << endl;
  handB.printInOrder();
  
  return 0;
}
