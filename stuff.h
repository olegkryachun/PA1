#define MYNULL -1
#define FOUND 1
#define NOTFOUND 0


typedef struct{
  int data;
  int next;
  int valid;
}Node;

typedef struct{
  int prev;
  int index;
  int endList;
  int found;
}Return;

void init(Node *list);
void start(Node *list);
void printInfo();
Return searchNode(Node *list, int);
int deleteNode(Node *list, int);
void printList(Node *list);
int insertNode(Node *list,int);
int get_node(Node *list);
void release_node(Node *list,int);


