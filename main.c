/*
Creator: Oleg Kryachun
Date: 01/10/2019
CSE 222; Program Assignment 1

This program creates a linked list array of 100 struct variables and is manipulated by the user. The user can delete, add, search, or print the list.
This list automatically sorts the array in incrementing order when any operation is done, the pointer are manipulated to keep the list in order from least to greatest.

*/


#include <stdio.h>
#include <string.h>
#include "stuff.h"

int main(){

  Node list[100];  //Create the node array
  init(list);  //Initialize all the nodes within the array
  start(list);  //Begin the program
return 0;
}
