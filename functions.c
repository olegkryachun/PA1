#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stuff.h"



// Init funtion
void init(Node *a){
  int i;
  (a[0]).data = 98662; //Sentinal node initialization
  (a[0]).valid = 1;
  (a[0]).next = MYNULL;

  for(i = 1; i <= 99; i++){  //clears all nodes in node list
    (a[i]).data = 999;
    (a[i]).next = -99999;
    (a[i]).valid = 0;
  }
}



// Start Function
void start(Node *list){

  init(list);  //Initialize all the nodes within the array

  char temp[50], input;
  int num,valid;
  Return retrn;

  while(input != 'x'){
    printf("> ");

 //Gets input from user and stores in variables
    fgets(temp,50,stdin);
    valid = sscanf(temp,"%c %d",&input, &num);

    if(valid == 2){ // If user input a letter and a number then it send the information to the correct funtion
      if(input == 'i'){
        retrn.found = insertNode(list,num); //Insert Nodes
        if(get_node(list) == -1)  printf("OUT OF SPACE\n");
        if(retrn.found == -2)  printf("NODE ALREADY EXISTS\n");
      }
      else if(input == 's'){
        retrn = searchNode(list,num);  //Check if a node is in the list
        if(retrn.found == 1)  printf("FOUND\n");
        else printf("NODE NOT FOUND\n");
      }
      else if(input == 'd'){
        retrn.found = deleteNode(list,num);  //Delete node from the list
        if(retrn.found == 1) printf("SUCCESS\n");
        else printf("NODE NOT FOUND\n");
      }
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



int insertNode(Node *list, int num){

  int prev = 0, curr = list[0].next, greater = 0, equal = 0;
  int index = get_node(list);

  if(list[0].next == MYNULL){  //If linked list is empty then insert node to first place in memory
    list[0].next = index;
    list[index].data = num;
    list[index].next = MYNULL;
    return 0;
  }else{

    while(greater != 1 && equal != 1 && list[curr].next != MYNULL){
      if(list[curr].data > num)  //Once the current data is larger then insert num, flag is set
        greater = 1;
      else if(list[curr].data == num)  //If number exists in set, flag is set
        equal = 1;
      else{
        prev = curr;
        curr = list[curr].next;
      }
    }
    if(list[curr].data > num)  //Checks last node of the list if greater than the insert num
      greater =1;
    if(list[curr].data == num)  //Checks last node if equal to
      equal = 1;

    if(equal != 1 && greater != 1){  //If none of the nodes are greater or equal to then the node must be bigger then the rest so add it to the end of the list
    list[curr].next = index;
    list[index].next = MYNULL;
    list[index].data = num;
    return 0;
    }


  }

  if(equal == 1)  //If node exists
      return -2;

  if(greater == 1){  //Inserts node before the node greater than itself
    list[prev].next = index;
    list[index].next = curr;
    list[index].data = num;
    return 0;
    }
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




Return searchNode(Node *list, int num){ //This function returns a struct Return

  Return retrn;
  int loc = list[0].next;
  retrn.found = NOTFOUND, retrn.endList = 0; //Initializes elements of retrn

  if(loc != MYNULL){  //Make sure Sentinel node isn't pointing to MYNULL

    if(list[loc].data == num){  //If the node that is being deleted is the first node then set the variables and skip the rest of the checking
      retrn.prev = 0;
      retrn.index = list[0].next;
      retrn.found = FOUND;
    }else{

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
      retrn.endList = 1;  //If this is executed then the node that is being searched for is the last node so endList is flagged
    }
    }
  }
  return retrn;
}




int deleteNode(Node *list, int num){

  Return retrn = searchNode(list,num);
  if(retrn.found == FOUND){

    if(retrn.endList == 1)  //If the node being deleted is at the end of the list then point the previous node to MYNULL 
      list[retrn.prev].next = MYNULL;
    else
    list[retrn.prev].next = list[retrn.index].next; //else the prev node points to the node that the deleted node pointed to

    release_node(list,retrn.index);  //clear the valid sign for the node being deleted
  }
  return retrn.found;
}




int get_node(Node *list){
  int i;

  for(i=0; i<=99; i++){
    if(list[i].valid == 0){  //Searches for first available node after finding one, sets valid value to 1
      list[i].valid = 1;
      return i;   //Return index of available node
    }
  }
  return -1;
}



void release_node(Node *list,int index){
  list[index].valid = 0;  //Clears valid sign for released node
}
