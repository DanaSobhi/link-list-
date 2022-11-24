#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Maxsize 2000
/** Dana Sobhi Section 1 **/
void properMenu();
struct node* clearList(struct node* d);
void erase(struct node * d);
struct node* readTextFolder(struct node* a);
struct node* readTextFolderP(struct node* a);
void addDataNodes(char x[],struct node* L,struct node* p);
void printStrings(struct node* n);
int IsEmpty(struct node* n);
int lastNode(struct node* a,struct node* s);
struct node* removee(char id[],struct node *s);
struct node * add(char id[],struct node *s);
struct node* bussesWith(struct node *bus , struct node *pass,struct node *x);
struct node* bussesWithout(struct node *bus , struct node *pass,struct node *x);
void SearchaBus(char id[],struct node*b);
struct node* removeeP(char id[],struct node *s);
//Linked List
struct node // Define a struct which contain a pointer leads to the second struct & a place to the string which will put
{
    char Data[Maxsize] ;
    struct node* Next ;
};

int main()
{

    struct node* busses = NULL; // defining a Struct we will work with.
    busses = clearList(busses) ;
    struct node* pass = NULL;// defining a Struct we will work with
    pass = clearList(pass);
    struct node* alle = NULL;// defining a Struct we will work with
    alle = clearList(alle);
    struct node* nonee = NULL;
    nonee = clearList(nonee);

    properMenu();

int x =0;
do{         // to scan the option

scanf("%d",&x);// scan the option number

    if(x <= 0 || 10 <= x){
        printf("Not an option");
        }

switch (x) // to know which option the user select
        {
    case 1 :
            busses = NULL;
            busses =readTextFolder(busses);
    printf("----Choose from the menu-----\n");
            break;
    case 2 :
           pass = NULL;
           pass =readTextFolderP(pass);
    printf("----Choose from the menu-----\n");
            break;
    case 3 :
        alle= NULL;
    alle= bussesWith(busses,pass,alle);
            printStrings(alle);
    printf("----Choose from the menu-----\n");
            break;
    case 4 :
        printf("Enter the data to search\n");
        char r[100];
        scanf("\n%s",r);
        SearchaBus(r,alle);
    printf("----Choose from the menu-----\n");
        break;

    case 5:
            nonee= NULL;
    nonee = bussesWithout(busses,pass,nonee);
            printStrings(nonee);
     //       printStrings(nonee);
    printf("----Choose from the menu-----\n");
            break;
    case 6:
        printf("Enter the data to add make sure it matches the file pattern , as adding '#' between them. \n");
        char adding[100];
        scanf("\n%s",adding);
        add(adding,pass);
        printf("----Choose from the menu-----\n");
            break;
    case 7 :
        printf("Enter the data to delete\n");
        char temp[100];
        scanf("\n%s",temp);
        removeeP(temp,pass);
        printStrings(pass);
        printf("----Choose from the menu-----\n");
    break;

    case 8:
        printf("Enter the data to delete\n");
        char temp2[100];
        scanf("\n%s",temp2);
        removeeP(temp2,busses);
        alle= bussesWith(busses,pass,alle);
        printStrings(alle);
    printf("----Choose from the menu-----\n");
            break;
      }

}while(x != 9);//as if it chooses 9 it will exit the app
    return 0;
}


void properMenu() // just print the menu
{
printf("***********************************************\n");
printf("*1-......Load the bus information file......-1*\n");
printf("*2-...Load the passenger information file...-2*\n");
printf("*3-. Assign & Print all passenger and buses.-3*\n");
printf("*4-...Search a specific bus information.....-4*\n");
printf("*5-.......Print unmatched passengers........-5*\n");
printf("*6-...........Add new passenger.............-6*\n");
printf("*7-............Delete passenger.............-7*\n");
printf("*8-...........Delete bus number.............-8*\n");
printf("*9..................Exit....................-9*\n");
printf("*************Choose from the menu**************\n");
}

struct node* clearList(struct node* d) // to ensure that the Linked List d is empty
{
    if(d != NULL)         // if not empty..
        erase( d ); // call function to delete the Linked List
    d = (struct node*)malloc(sizeof(struct node)); // give the Linked List a new memory
    if(d == NULL) //if there's no memory left for ll L.
        printf("Error\n");
    d->Next = NULL; // make the pointer in the struct node points on NULL
    return d;
}

void erase(struct node* d)
{
    struct node* P; // node to deletion.
    struct node* temp; // after getting rid of P node , temp will be used to get next data .
    P = d->Next; //let p get the node of d.
    d->Next = NULL; // let d node point to nothing.
    while(P != NULL) // while there is a node to delete:
    {
        temp = P->Next; // temp get the next node , let temp point to p->next to prevent data loss.
        free(P); // P get rid of the current node " p " ,
        P=temp; // as soon P is not null , loop after other nodes to delete. similar to p = p->next
    }
}

struct node* readTextFolder(struct node* a)
{
    char temp[350]; // String we will store what we will scan from the file in.
    a = clearList(a) ; //to prevent putting previous data into the link list
    struct node* p = a; // P points on the struct node that we will add the inputs for it after scanning the file
    FILE* b = fopen("busses.txt","r"); // select the file to open, and scan it later
    if(b == NULL) // if the file does't exist print or empty
        printf("File is empty!\n");
    else  //the file exist, then:
        do{fscanf(b,"%s\n",temp); //scan the file line by line
            addDataNodes(temp,a,p); //will insert what we read in the file into link list a
            p = p->Next; //point to the next node in link list if exist.
        }while(!feof(b)); //until the end of the file .
    printf("The Input file has been read\n"); // print when this function read without problems
    fclose(b); // close the file we opened before

    return a;//return the link list , will have the information about what we read in the file.
}

struct node* readTextFolderP(struct node* a)
{//similar from the above , instead the file is for passengers.
    char temp[350];
    a = clearList(a) ;
    struct node* p = a;
    FILE* in = fopen("passengers.txt","r");
    if(in == NULL)
        printf("The File is Empty \n");
    else
        do{fscanf(in,"%s\n",temp);

            addDataNodes(temp,a,p);
            p = p->Next;
        }while(!feof(in));
    printf("The Input file has been read\n");
    fclose(in);
    return a;
}
void addDataNodes(char x[],struct node* L,struct node* p) // X is the string we will use to insert the data into the p node in link list L.
{
    struct node* temp ; // define a struct node
    temp = (struct node*)malloc(sizeof (struct node)); // give it a place
    strcpy(temp->Data,x); // copy the required data in the node
    temp->Next=p->Next; // will let the new node temp point into the same as p node , to prevent the link list data to lost.
    p->Next=temp; //as node p pointer leads to the new node.
}

void printStrings(struct node* n)
{
    struct node* p = n ; // P points on link list  n
    if(IsEmpty(n)) //check in the link list is empty
        printf("Empty!\n");
    else // otherwise..
        while(!lastNode(p,n)) // while P is not the last node in the link list  n
        {
            p=p->Next; //P points in the next struct node and print its data
            printf("%s\n",p->Data);
        }

    printf("\n");
}


int IsEmpty(struct node* n) //boolean function to check link list l  is empty or no
{
    return n->Next == NULL ; //if the head node don't point to anything then its empty will return 1
}

int lastNode(struct node* a,struct node* s) //boolean function to check if node a is the last node in the link list s
{
    return a->Next == NULL; // 1 if there is no next node
}

struct node* removeeP(char id[],struct node *s) { //to remove a data from the link list s
 struct   node *current_node = s; //current_node point to s.
 struct   node *previous; //node to check the previous node.
char str[250]; //string to store the data at.

if(IsEmpty(s)) //check if L is empty or not.
        printf("Empty!\n");


else do{
current_node=current_node->Next;// current_node points in the next struct node
strcpy(str,current_node->Data); //take the data to separate it

char * temp = strtok(str, "#"); //first token is the id.
//printf("%s\n",temp);
    if (strcmp(temp,id) == 0) { //if the id matches.
            if (current_node == s) { //and this node is same as s
                 s = current_node->Next; //  let s be the next node as skipping a node.
            } else {
                previous->Next = current_node->Next; //else the previous node next , will point at the current one next , as this is the node we will delete.
            }
        }
    previous = current_node; //else the previous node is the current node


}while(!lastNode(current_node,s));

return(s); //return s after changes.
}
struct node * add(char id[],struct node *s) { // a function to add a data into the link list.
struct  node *newNode; //create a node in the link list
    newNode = (struct node *) malloc(sizeof(struct node)); //settle up a place for the node
    strcpy(newNode->Data,id); //copy the data into the link list
    newNode->Next = s->Next;//let the next pointer  point into the next pointer of the link list
    s->Next = newNode;  //let the next of the main link list point to the new node
return s; //return the link list after the data added.
}


struct node* bussesWith(struct node *bus , struct node *pass,struct node *x){

int i = 0;
struct node* p;
struct node* b = bus;
char st[150];
char str[120];
int n =0;
int number=0;
//char tempee[100][Maxsize]= {0};
char smallspace[2] =" ";
char linee[2] ="\n";

x = clearList(x) ; //clear the list to prepare it
struct node* e = x; // the list we will use to add the new nodes.

if(IsEmpty(bus)|| IsEmpty(pass)) //if one of the lists is empty.
        printf("Empty!\n");

else
do{//printf("================== bus =================\n");
    int seated = 0;
    char tempee[1000][Maxsize];
       b=b->Next;
        strcpy(str,b->Data); //divide the string into it components
        char * temp = strtok(str, "#"); //Bus id
    //  printf("%s\n",temp);
        char * tempDate = strtok(NULL, "#"); //bus date
     //   printf( "%s\n", tempDate );
        char * tempTime = strtok(NULL, "#"); //departure time,
 //       printf( "%s\n", tempTime );
        char * tempFrom = strtok(NULL, "#"); //from
  //      printf( "%s\n", tempFrom );
        char * tempTo = strtok(NULL, "#"); //to
  //      printf( "%s\n", tempTo );
        char * tempPrice = strtok(NULL, "#"); //price
//     printf("%s\n", tempPrice );
        char * tempCapacity = strtok(NULL, "#"); //capacity
//     printf("%s\n", tempCapacity );//test to see if it reads it
//printf("%s \n",b->Data);
p = pass; // point again to the link list to read it.
i=0; //reset the number.
//seated = 0; //reset the number for new bus.

int cap = atoi(tempCapacity);
do{
p=p->Next;
strcpy(st,p->Data);


       //     printf("%d %s %s \n",count,st,temp);
char * pass1 = strtok(st, "#"); //traveler id
             // printf("%s\n",pass1);
char * pass2 = strtok(NULL, "#"); //traveler date
            //  printf( "%s\n", pass2 );
char * pass3 = strtok(NULL, "#"); //departure time,
            //       printf( "%s\n", pass3 );
char * pass4 = strtok(NULL, "#"); //from
             //       printf( "%s\n", pass4 );
char * pass5 = strtok(NULL, "#"); //to
            //      printf( "%s\n", pass5 );

if((strcmp(tempDate,pass2)==0) && (strcmp(tempTime,pass3)==0) ){ //if the date and depart time matches.
        if(cap >=0){ //as soon the capacity more than 0
        char a[150]; //array to store data.
        strcpy(a,pass1); //copy the data to the string
      //  printf("%s\n",a);
        strcpy(tempee[seated],a); //copy the data to the array of strings
    //    printf("%s\n",tempee[seated]);
        seated++; //add number of seated people
        cap--; //seat taken
        }
        i++; //to count number of people who has the same department time.

}
}while(!lastNode(p,pass));

         char y[50];
//use a string to add the info. as some of the data might be lost.
strcpy(y,tempDate);
strcat(temp,smallspace);
strcat(temp,y);
strcpy(y,tempTime);
strcat(temp,smallspace);
strcat(temp,y);
strcpy(y,tempFrom);
strcat(temp,smallspace);
strcat(temp,y);
strcpy(y,tempTo);
strcat(temp,smallspace);
strcat(temp,y);
strcpy(y,tempPrice);
strcat(temp,smallspace);
strcat(temp,y);
strcpy(y,tempCapacity);
strcat(temp,smallspace);
strcat(temp,y);
strcat(temp,linee);
//printf("%s\n",temp);
//printf("================: in it :==============\n");
char g[500];
strcat(g,linee);
    for(int o = 0; o <= seated;o++){
    //  printf("%s\n",tempee[o]);

   // strcpy(g,tempee[o]);
    //copy the data of the array list
    strcat(g,tempee[o]);
    strcat(g,linee);
  //  printf("%s\n",g); //print them out.
    }
 //   printf("%s",g);
strcat(temp,g);
strcat(temp,smallspace); //add everything to the string
    addDataNodes(temp,x,e); //add the string into the list.
    e = e->Next;


//printf("\n*-Number of people :%d \n*-people who took a seat : %d \n",i,seated);

}while(!lastNode(b,bus));
return x;
}

struct node* bussesWithout(struct node *bus , struct node *pass,struct node *x){

int i = 0;
struct node* p;
struct node* b = bus;
char st[150];
char str[120];
int n =0;
int number=0;
int seated = 0;
char tempee[1000][Maxsize]= {0};
char smallspace[2] =" ";
char linee[2] ="\n";

x = clearList(x) ; //clear the list to prepare it

struct node* e = x; // the list we will use to add the new nodes.

if(IsEmpty(bus)|| IsEmpty(pass)) //if one of the lists is empty.
        printf("Empty!\n");

else
do{//printf("================== bus =================\n");
       b=b->Next;
        strcpy(str,b->Data); //divide the string into it components
        char * temp = strtok(str, "#"); //Bus id
    //  printf("%s\n",temp);
        char * tempDate = strtok(NULL, "#"); //bus date
     //   printf( "%s\n", tempDate );
        char * tempTime = strtok(NULL, "#"); //departure time,
 //       printf( "%s\n", tempTime );
        char * tempFrom = strtok(NULL, "#"); //from
  //      printf( "%s\n", tempFrom );
        char * tempTo = strtok(NULL, "#"); //to
  //      printf( "%s\n", tempTo );
        char * tempPrice = strtok(NULL, "#"); //price
//     printf("%s\n", tempPrice );
        char * tempCapacity = strtok(NULL, "#"); //capacity
//     printf("%s\n", tempCapacity );//test to see if it reads it
//printf("%s \n",b->Data);

p = pass; // point again to the link list to read it.
i=0; //reset the number.
seated = 0; //reset the number for new bus.

int cap = atoi(tempCapacity);
do{
p=p->Next;
strcpy(st,p->Data);


       //     printf("%d %s %s \n",count,st,temp);
char * pass1 = strtok(st, "#"); //traveler id
             // printf("%s\n",pass1);
char * pass2 = strtok(NULL, "#"); //traveler date
            //  printf( "%s\n", pass2 );
char * pass3 = strtok(NULL, "#"); //departure time,
            //       printf( "%s\n", pass3 );
char * pass4 = strtok(NULL, "#"); //from
             //       printf( "%s\n", pass4 );
char * pass5 = strtok(NULL, "#"); //to
            //      printf( "%s\n", pass5 );
if(strcmp(tempDate,pass2)==0 && strcmp(tempTime,pass3)==0 ){ //if the date and depart time matches.
char a[150]; //array to store data.
        strcpy(a,pass1); //copy the data to the string
        strcpy(tempee[seated],a);
        seated++; //add number of seated people
        pass = removeeP(tempee[seated],pass);

}

}while(!lastNode(p,pass));
//printf("\n*-Number of people :%d \n*-people who took a seat : %d \n",i,seated);


}while(!lastNode(b,bus));


return pass;
}


void SearchaBus(char id[],struct node*b){
struct   node *current_node = b; //current_node point to b.
char str[250]; //string to store the data at.

if(IsEmpty(b)) //check if L is empty or not.
        printf("Empty!\n");

else do{
current_node=current_node->Next;// current_node points in the next struct node

strcpy(str,current_node->Data); //take the data to separate it

char * temp = strtok(str, " "); //first token is the id.
//printf("%s\n",temp);
    if (strcmp(temp,id) == 0) { //if the id matches.
    printf("%s\n",current_node->Data);
}

}while(!lastNode(current_node,b));

}

