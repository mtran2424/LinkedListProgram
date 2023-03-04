/*
Author: 		My Tran

StudentID:		001550700

Course:			ICSI 333 System Fundamentals

Semester:		Spring 2022

TA:				Sourav Dutta

Filename:		LinkedListProgram.c

Description:	An interactive program that prompts the user for the following commands from 
				the keyboard to interact with a linked list. The program will prompt for and 
				execute said commands until the end command is proccessed from the user.
				
Assumptions:	-The command given by the user will be one of the following:
				 ina, inb, del, rep, prn, or end
				 
				-The command names are case sensitive
				
				-Each command will contain all and only the necessary arguments
				 so commands won't miss extraneous arguments
				 
				-Commands with one or more arguments will be separated by one or more
				 spaces
				 
				-String arguments won't include any whitespace
				
				-Erroneous commands are entered, they should be ignored


*/

//INCLUDED LIBRARIES
#include <stdio.h>	//standard input/output library
#include <string.h>	//string library for string related functions
#include <stdlib.h>	//included mainly for exit() function


//DEFINED CONSTANTS
#define MAX_STRING 255	//max length of text in node
#define CMD_LEN 4		//max length of command input including terminal




//Struct definition for each node in the linked list
struct node
{
	unsigned int index;		//4 Bytes
	struct node *next;		//8 Bytes
	char text[MAX_STRING];	//255 Bytes
};




//FUNCTION PROTOTYPES
void InsertAfter(struct node **, struct node **, unsigned int, char *);

void InsertBefore(struct node **, struct node **, unsigned int, char *);

struct node *Find(struct node *, unsigned int);

int GetCommand(struct node **, struct node **);

void Print(struct node *);

int IsEmpty(struct node *);

int TextExists(struct node *, char *);

void Replace(struct node *, unsigned int, char *);

void Delete(struct node **, struct node **, unsigned int);





int main()
{
	//declaring pointers for nodes that point to the first and last nodes in the list
	struct node *head, *tail;
	
	//head and tail initially point to NULL when the list is empty
	head = tail = NULL;
	
	//priming execution for command loop
	int flag = GetCommand(&head, &tail);
	
	//commands are gathered and executed until exit flag is returned from GetCommand
	while(flag == 0)
	{
		flag = GetCommand(&head, &tail);
	}
		
	return 0;
}//end main




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



/*
Function:		GetCommand()

Purpose:		Gets command from the user and performs command based on user input. 
				
Pre-condition:	Takes pointer to the head and tail of the list as arguments

Post-condition:	Command is executed and flag is returned to caller. Returns 1
				to indicate that exit command has been entered. 0 otherwise.
*/
int GetCommand(struct node **head, struct node **tail)
{
	//variables to store the commands
	char command[CMD_LEN];	//string to store a command
	unsigned int index;		//variable to store index for commands that require it
	char txt[MAX_STRING];	//string to store text to be inserted into a node
	
	
	//prompt for a command
	printf("\nCommand?  ");
	fflush(stdout);
	
	//get command
	scanf("%s", command);
	
	
	//ina indicates a call to InsertAfter
	//ina num str
	if(strcmp(command, "ina\0")==0)
	{
		//read in num and str from user
		scanf("%d", &index);
		
		scanf("%s", txt);
		
		InsertAfter(head, tail, index, txt);
		
		//returns 0 to caller to indicate no exit
		return 0;
	}
	//inb indicates a call to InsertBefore
	//inb num str
	else if(strcmp(command, "inb\0")==0)
	{
		//read in num and str from user
		scanf("%d", &index);
		
		scanf("%s", txt);
		
		InsertBefore(head, tail, index, txt);
		
		//returns 0 to caller to indicate no exit
		return 0;
	}
	//rep indicates a call to Replace
	//rep num str
	else if(strcmp(command, "rep\0")==0)
	{
		//read in num and str from user
		scanf("%d", &index);
		
		scanf("%s", txt);
		
		Replace(*head, index, txt);
		
		//returns 0 to caller to indicate no exit
		return 0;
	}
	//ina indicates a call to Delete
	//del num
	else if(strcmp(command, "del\0")==0)
	{
		//read in num from user
		scanf("%d", &index);
		
		Delete(head, tail, index);
		
		//returns 0 to caller to indicate no exit
		return 0;
		
	}
	//prn indicates a call to Print
	else if(strcmp(command, "prn\0")==0)
	{
		Print(*head);
		
		//returns 0 to caller to indicate no exit
		return 0;
	}
	//end indicates a call to end the program
	else if(strcmp(command, "end\0")==0)
	{
		return 1;
	}
	//if erroneous input is detected, 0 is returned to start a new command prompt
	else
	{
		//returns 0 to caller to indicate no exit
		return 0;
	}
}//end GetCommand





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





/*
Function:		InsertBefore()

Purpose:		Inserts a new node with text given by the input argument, before a node
				with the specified index if it exists, or at the beginning of the list otherwise. 
				No change occurs in the list if the text is already in the list.
				
Pre-condition:	Takes pointer to the head and tail of the list, a value representing an index, 
				and a pointer to an input string as arguments

Post-condition:	Node is inserted into the list if the text doesn't already exist in the list
*/
void InsertBefore(struct node **head, struct node **tail, unsigned int val, char *input)
{
	//node pointer to point to new node
	struct node *temp;
	
	//insert if the list was empty
	if(IsEmpty(*head))
	{
		//try to allocate space for the node to be created
		if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL) 
		{
			printf("Node allocation failed. \n");
			fflush(stdout);
			exit(1);
		}
	
	
		//insert the text into the node
		strcpy(temp->text, input);
	
	
		//set the next node to null
		temp -> next = NULL;
		
		
		//set head and tail to the new node
		*head = *tail = temp;
		//first node is given an index of 1
		temp -> index = 1;
		
		
		printf("\nText inserted at the beginning\n");
		fflush(stdout);
	}
	else
	{
		//if the text doesn't already exist, create a new node
		if(TextExists(*head, input) != 0)
		{
			//try to allocate space for the node to be created
			if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL) 
			{
				printf("Node allocation failed. \n");
				fflush(stdout);
				exit(1);
			}
	
	
			//insert the text into the node
			strcpy(temp->text, input);
	
	
			//set the next node to null
			temp -> next = NULL;
			
			
			//set tempNode to point to the node with the corresponding index
			struct node *tempNode = Find(*head, val);
			
			
			//if the index wasn't found
			if(tempNode == NULL || tempNode == *head)
			{
				
				//insert the node at the beginning
				//make temp the new head
				temp->index = (*head) ->index;
				temp->next = (*head);
				(*head) = temp;
				
				//increment the subsequent nodes' indexes
				temp = temp->next;
				while(temp != NULL)
				{
					temp->index++;
					temp = temp->next;
				}
				
				printf("\nText inserted at the beginning\n");
				fflush(stdout);
			}
			else
			{
				temp->index = tempNode->index;
				
				//swap the texts of the new node and the node at the correct position
				char swap[MAX_STRING];
				strcpy(swap, tempNode->text);
				strcpy(tempNode->text, temp->text);
				strcpy(temp->text, swap);
				
				//increment the subsequent nodes' indexes
				temp->next = tempNode->next;
				tempNode->next = temp;
				while(temp != NULL)
				{
					temp->index++;
					temp = temp->next;
				}
				
				printf("\nOK\n");
				fflush(stdout);
			}
			
			
		}
	}
}//end InsertBefore







//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





/*
Function:		InsertAfter()

Purpose:		Inserts a new node with text given by the input argument, after a node 
				with the specified index if it exists, or at the end of the list otherwise. 
				No change occurs in the list if the text is already in the list.
				
Pre-condition:	Takes pointer to the head and tail of the list, a value representing an index, 
				and a pointer to an input string as arguments

Post-condition:	Node is inserted into the list if the text doesn't already exist in the list
*/
void InsertAfter(struct node **head, struct node **tail, unsigned int val, char *input)
{
	//node pointer to point to new node
	struct node *temp;
	
	//insert if the list is empty
	if(IsEmpty(*head))
	{
		//try to allocate space for the node to be created
		if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL) 
		{
			printf("Node allocation failed. \n");
			fflush(stdout);
			exit(1);
		}
	
		//insert the text into the node
		strcpy(temp->text, input);
	
	
		//set the next node to null
		temp -> next = NULL;
		
		
		//set head and tail to the new node
		*head = *tail = temp;
		//first node is given an index of 1
		temp -> index = 1;
		
		
		printf("\nText inserted at the end\n");
		fflush(stdout);
	}
	else
	{
		//if the text doesn't already exist, create a new node
		if(TextExists(*head, input) != 0)
		{
			//try to allocate space for the node to be created
			if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL) 
			{
				printf("Node allocation failed. \n");
				fflush(stdout);
				exit(1);
			}
	
			//insert the text into the node
			strcpy(temp->text, input);
	
	
			//set the next node to null
			temp -> next = NULL;
			
			
			//set tempNode to point to the node with the corresponding index
			struct node *tempNode = Find(*head, val);
			
			
			//if the index wasn't found
			if(tempNode == NULL || tempNode == *tail)
			{
				//insert the node at the end
				temp->index = (*tail) ->index + 1;
				(*tail)->next = temp;
				*tail = temp;
				
				if(tempNode == NULL)
				{
					printf("\nText inserted at the end\n");
					fflush(stdout);
				}
				else
				{
					printf("\nOK\n");
					fflush(stdout);
				}
			}
			else
			{
				//insert temp into the list after the node in the correct position
				temp->index = tempNode->index;
				temp->next = tempNode->next;
				
				//increment the subsequent nodes' indexes
				tempNode->next = temp;
				
				while(temp != NULL)
				{
					temp->index++;
					temp = temp->next;
					
				}
				printf("\nOK\n");
				fflush(stdout);
				
			}
			
			
		}
	}
}//end InsertAfter






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~






/*
Function:		Find()

Purpose:		Finds the node with the given index and returns a pointer to it. If 
				index is not found, NULL is returned.
				
Pre-condition:	Takes pointer to the head of the list, and a value representing an 
				index as arguments

Post-condition:	Pointer to a node with a matching index is returned if found, otherwise 
				returns NULL
*/
struct node *Find(struct node *head, unsigned int val)
{
	//set a pointer to the head of the list
	struct node *temp = head;
	
	
	//if temp is NULL, then the list is empty or the end of the list is reached
	if(temp == NULL)
	{
		return NULL;
	}
	else
	{
		
		//if the node was found, return the pointer to it
		if(temp->index == val)
		{
			
			return temp;
		}
		//recursively traverse to the next node
		else if(temp->next != NULL)
		{
			temp = Find(temp->next, val);
			//return temp;
		}
	}
}//end Find







//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




/*
Function:		Replace()

Purpose:		Given a node index, replaces the text in the node if the index is found, 
				and leaves the list alone if the index is not found or the list is empty
				
Pre-condition:	Takes pointer to the head of the list, a value representing an index, and 
				a text string as arguments

Post-condition:	List is left alone if an index is not found or the text already exists in 
				the list. Otherwise, the text is replaced in the node with the 
				corresponding index.
*/
void Replace(struct node *head, unsigned int val, char *input)
{
	//checks for the text to already exist in the list
	if(TextExists(head, input) != 0)
	{
		//set temp to point to the index given by val
		struct node *temp = Find(head, val);
		
		//if temp points to NULL, the list contains no such index
		if(temp == NULL)
		{
			printf("\nNo such index\n");
			fflush(stdout);
		}
		//if temp points to something, the index is found
		else
		{
			strcpy(temp->text, input);
			
			
			//output message indicating the text has been replaced
			printf("\nReplaced\n");
			fflush(stdout);
		}
	}
}//end Replace





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





/*
Function:		TextExists()

Purpose:		If the list is not empty, traverses through the list searching for text
				matching that of the string given as an argument
				
Pre-condition:	Takes pointer to the head of the list as an argument and a text string

Post-condition:	Returns 0 if the list is empty or no match is found. 1 if a match is 
				found in the string
*/
int TextExists(struct node *head, char *str)
{
	//start temp pointing at head
	struct node *temp = head;
	
	//return 1 if list is empty
	if(IsEmpty(temp))
	{
		return 1;
	}
	else
	{
		//traverse through the list
		while(temp != NULL)
		{
			//return 0 if the text is found in the list
			if(strcmp(str, temp->text) == 0)
			{
				printf("\nSuch text exists already\n");
				fflush(stdout);
				
				return 0;
			}
			temp = temp->next;
		}
		
		//if value is not returned in loop, message is not found when the end is reached
		return 1;
		
	}
}//end TextExists




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




/*
Function:		Print()

Purpose:		Outputs message if the list is empty. Traverses through the list, node 
				by node, outputting the index and text of each node on separate lines
				
Pre-condition:	Takes pointer to the head of the list as an argument

Post-condition:	Message or list is output to stdout
*/
void Print(struct node *head)
{
	//start temp pointing at the head node
	struct node *temp = head;
	
	//if the list is empty, output message indicating such
	if(IsEmpty(head))
	{
		printf("\nThe list is empty.\n");
		fflush(stdout);
	}
	else
	{
		//otherwise, traverse through list outputting index and text of node line by line
		while(temp != NULL)
		{
			printf("\n%d\t%s\n", temp->index, temp->text);
			fflush(stdout);
			
			temp = temp->next;
		}
	}
}//end Print




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




/*
Function:		IsEmpty()

Purpose:		Determines if a linked list is empty or not
				
Pre-condition:	Takes pointer to the head of the list as an argument

Post-condition:	Returns 0 if list is empty, 1 otherwise
*/
int IsEmpty(struct node *head)
{
	return (head == NULL);
}//end IsEmpty





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~






/*
Function:		Delete()

Purpose:		Deletes a node at a given index if the index exists in the list
				
Pre-condition:	Takes pointer to the head and tail of the list, and an integer 
				representing the index as arguments

Post-condition:	Deletes the node at the given index if index exists. List is unchanged 
				otherwise
*/
void Delete(struct node **head, struct node **tail, unsigned int val)
{
	//set temp to point to the index given by val
	struct node *temp = Find(*head, val);
	
	//if temp points to NULL, the list contains no such index
	if(temp == NULL)
	{
		printf("\nNo such index\n");
		fflush(stdout);
	}
	//if temp points to something, the index is found
	else
	{
		//if there is only one item in the list, list is empty after delete
		if(temp == *head && temp == *tail)
		{
			free(temp);
			
			//reset head and tail to NULL
			*head = *tail = NULL;
		}
		//if target node is the head of the list,
		else if(temp == *head)
		{
			//move head to the next node
			*head = temp->next;
			
			//delete the former head node
			free(temp);
			
			//set temp equal to the head node, and decrement all the subsequent
			//node indexes
			temp = *head;
			while(temp != NULL)
			{
				temp->index--;
				temp = temp->next;
			}
			
		}
		//if the target is neither, than the target is in the middle of the list
		else //if(temp != *head && temp != *tail)
		{
			//if temp is not the tail
			if(temp->next != NULL)
			{
				//make the node at temp into the node next to it
				struct node *target = temp->next;
				strcpy(temp->text, target->text);
			
				//set the next node of temp to be the one after the next and delete 
				//the next
				temp->next = target->next;
			
				free(target);
			}
			
			else
			{
				//find the node behind the tail node
				temp = *head;
				while(temp->next->next != NULL)
				{
					temp = temp->next;
				}
			
			
				//make that node the new tail
				*tail = temp;
			
				//make temp the former tail and delete that node
				temp = temp->next;
			
				free(temp);
			
			
			
				//reset tail->next ptr to NULL
				(*tail)->next = NULL;
			}
			
			//decrement subsequent nodes after the new node
			if(temp != NULL)
			temp = temp->next;
			
			while(temp != NULL)
			{
				temp->index--;
				temp = temp->next;
			}
		}
		printf("\nDeleted\n");
		fflush(stdout);
		
	}
}//end Delete




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~