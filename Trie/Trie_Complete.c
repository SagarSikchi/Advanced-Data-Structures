#include <stdio.h>
#include <stdlib.h>

/* define character size */
#define CHAR_SIZE 26

char input[20];
int choice;

/* A Trie Node */
struct Trie
{
	int isLeaf;	          /* 1 when node is a leaf node */
	struct Trie* character[CHAR_SIZE];
};

void read_input(){
  printf("Enter the word : ");
  scanf("%s", input);
}

/* Function that returns a new Trie node */
struct Trie* getNewTrieNode()
{
	struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
	node->isLeaf = 0;

	for (int i = 0; i < CHAR_SIZE; i++)
		node->character[i] = NULL;

	return node;
}

/* Iterative function to insert a string in Trie */
void insert(struct Trie *head, char* str)
{
	/* start from root node */
	struct Trie* curr = head;
	while (*str)
	{
		/* create a new node if path doesn't exists */
		if (curr->character[*str - 'a'] == NULL)
			curr->character[*str - 'a'] = getNewTrieNode();

		/* go to next node */
		curr = curr->character[*str - 'a'];

		/* move to next character */
		str++;
	}

	/* mark current node as leaf */
	curr->isLeaf = 1;
}

/* 
   Iterative function to search a string in Trie. It returns 1
   if the string is found in the Trie, else it returns 0
*/
int search(struct Trie* head, char* str)
{
	/* return 0 if Trie is empty */
	if (head == NULL)
		return 0;

	struct Trie* curr = head;
	while (*str)
	{
		/* go to next node */
		curr = curr->character[*str - 'a'];

		/* if string is invalid (reached end of path in Trie) */
		if (curr == NULL)
			return 0;

		/* move to next character */
		str++;
	}

	/* 
	    if current node is a leaf and we have reached the
	    end of the string, return 1
	*/
	return curr->isLeaf;
}

/* returns 1 if given node has any children */
int haveChildren(struct Trie* curr)
{
	for (int i = 0; i < CHAR_SIZE; i++)
		if (curr->character[i])
			return 1;	/* child found */

	return 0;
}

/* Recursive function to delete a string in Trie */
int deletion(struct Trie **curr, char* str)
{
	/* return if Trie is empty */
	if (*curr == NULL)
		return 0;

	/* if we have not reached the end of the string */
	if (*str)
	{
		/* 
		   recur for the node corresponding to next character in
		   the string and if it returns 1, delete current node
		   (if it is non-leaf)
		*/
		if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
			deletion(&((*curr)->character[*str - 'a']), str + 1) &&
			(*curr)->isLeaf == 0)
		{
			if (!haveChildren(*curr))
			{
				free(*curr);
				(*curr) = NULL;
				return 1;
			}
			else {
				return 0;
			}
		}
	}

	// if we have reached the end of the string
	if (*str == '\0' && (*curr)->isLeaf)
	{
		/* if current node is a leaf node and don't have any children */
		if (!haveChildren(*curr))
		{
			free(*curr);      /* delete current node */
			(*curr) = NULL;
			return 1;         /* delete non-leaf parent nodes */
		}

		/* if current node is a leaf node and have children */
		else
		{
			/* mark current node as non-leaf node (DON'T DELETE IT) */
			(*curr)->isLeaf = 0;
			return 0;	        /* don't delete its parent nodes */
		}
	}

	return 0;
}

int main()
{
    struct Trie* head = getNewTrieNode();  /* Function to make Root Node as NULL */
	int count = -1;
    while(count != 0)
    {
        if (head == NULL){
		    printf("Trie is empty!!\n\n");
		} 

        printf("Enter your choice :\n");
        printf("1. Insert Word in Trie\n");
        printf("2. Search Word in Trie\n");
        printf("3. Delete the Word from Trie\n");
        printf("4. Exit.\n\n");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1: read_input();
                insert(head, input);
                // free(input);
                printf("\n");
                break;
        case 2: read_input();
                printf("%d ", search(head, input));
                printf("\n");
                break;
        case 3: read_input();
                deletion(&head, input);
                printf("\n");
                break;
        case 4: count++;
                break;
        default : printf("Enter the valid choice.\n");
                    break;
        }
    }
    printf("Thank You !!!");
    return 0;

}