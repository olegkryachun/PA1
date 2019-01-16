#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stuff.h"

// Init funtion
void init(Node *a){
  int i;
  (a[0]).data = 98662; //Sentinal node initialization
  (a[0]).valid = 1;
  (a[0]).next = 5;

  for(i = 1; i <= 99; i++){  //clears all nodes in node list
    (a[i]).data = 999;
    (a[i]).next = -99999;
    (a[i]).valid = 0;
  }

  (a[5]).data = 10;
  (a[5]).valid = 1;
  (a[5]).next = 30;

  (a[30]).data = 30;
  (a[30]).valid = 1;
  (a[30]).next = -1;


}

// Start Function
void start(Node *list){
  char temp[50];
  char input;
  int num,valid,del=0;

while(input != 'x'){
  
  printf("> ");

  //Gets input from user and stores in variables
  fgets(temp,50,stdin);
  valid = sscanf(temp,"%c %d",&input, &num);

  if(valid == 2){ // If user input a letter and a number then it send the information to the correct funtion
    if(input == 'i')
      insertNode(list); //Insert Nodes
    else if(input == 's')
      searchNode(list,num,&del);  //Check if a node is in the list
    else if(input == 'd')
      deleteNode(list,num);  //Delete node from the list
    else
      printInfo();
  }

  if(valid == 1){  //If user input one input or the second input is invalid then checks what the input was and if invalid it prints the Info page
    if(input == '?')
      printInfo();  //Print Directory Information
    else if(input == 'p')
      printList(list); //Print Node List
    else if(input == 'x')
      exit(0); //Exits the program
    else
    printInfo();  //If user enters something invalid then print the directory information
  }
 }

}

void printInfo(Node *list){

//Prints Directory information
  printf("Please enter one of the folowing commands:\n");
  printf("i number	insert number into the list\n");
  printf("p       	print the list in order\n");
  printf("s number 	search for a number in the list\n");
  printf("d number	delete the number from the list\n");
  printf("x       	exit the program\n");
} 

void insertNode(Node *list){


}

//Prints List Array and directs back to start function
void printList(Node *list){
int loc;
loc = list[0].next;

  if(loc != MYNULL){ //if there is a node other than sentinal

    while(list[loc].next != MYNULL){
      printf("%d ", (list[loc]).data); //Prints the current node data
      loc = (list[loc]).next; //move to check the next node
    }
    printf("%d ",(list[loc]).data);  //if the next node is MYNULL then print the current node as the last node
  } 

  printf("\n");
}

Return searchNode(Node *list, int num, int *del){ //This function returns a struct Return

  Return retrn;
  int loc = list[0].next;
  retrn.found = NOTFOUND, retrn.endList = 0, retrn.prev = 0; //Initializes elements of retrn

  if(loc != MYNULL){  //Make sure Sentinel node isn't pointing to MYNULL
    while(list[loc].next != MYNULL && retrn.found != 1){  //while node not found and the next node isn't NULL
      if(num == list[loc].data){
        retrn.found = FOUND;  //Value exists
        retrn.index = loc;    //Sets current to index
      }
      retrn.prev = loc;  //Set current to prev before current moves to next
      loc = list[loc].next;
    }
    if(list[loc].data == num){  //After next node is pointing to MYNULL check if the current node's data is equal to the value
      retrn.found = FOUND;  //Value exists
      retrn.index = loc;  //Sets current to index
      if(*del == 1)
        retrn.endList = 1;  //If this is executed then the node that is being searched for is the last node so endList is flagged
    }
  }



  if(*del == -1)  //If the delete function calls the search function, this is the indicator
    return retrn;

  if(retrn.found == FOUND)
    printf("FOUND\n");  //Notify the user that the number is found
  if(retrn.found == NOTFOUND)
    printf("NOT FOUND\n");//Notify the user that the numbe was not found and set the integer point

return retrn;
}

void deleteNode(Node *list, int num){

  Return retrn;
  int del = -1;  //Define del to send to searchNode so the function knows where it's being called to
  retrn = searchNode(list,num,&del);


  if(retrn.found == NOTFOUND){
    printf("NODE NOT FOUND\n");
  }
  if(retrn.found == FOUND){

  release_node(list,retrn.index);
  printf("SUCCESS\n");
}

}



int get_node(Node *list){
  int i;

  for(i=1; i<=99; i++)
    if(list[i].valid == 0)  //Searches for first available node
      return i;   //Return index of available node
}

void release_node(Node *list,int index){
  list[index].valid = 0;
}
