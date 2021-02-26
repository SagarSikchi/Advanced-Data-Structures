#include<stdio.h>
#include<stdlib.h>

int value, flag = 1;
int choice;

/* A Splay Tree Node */
struct splayNode
{
	int key;
	struct splayNode *left;
	struct splayNode *right;
};

struct splayNode *root = NULL;

void read_input(){
  printf("Enter the value : ");
  scanf("%d", &value);
}

/* NewNode creation function */
struct splayNode *newNode(int key)
{
	struct splayNode *node = (struct splayNode*)malloc(sizeof(struct splayNode));
	node -> key = key;
	node -> left = NULL;
	node -> right = NULL;
	return node;
}

/* Right Rotation function */
struct splayNode *rightRotate(struct splayNode *node_)
{
	struct splayNode *temp = node_ -> left;
	node_ -> left = temp -> right;
	temp -> right = node_;
	return temp;
}

/* Left Rotation function */
struct splayNode *leftRotate(struct splayNode *node_)
{
	struct splayNode *temp = node_ -> right;
	node_ -> right = temp -> left;
	temp -> left = node_;
	return temp;
}

struct splayNode *splay(struct splayNode *root, int key){

   /* root is NULL or key is present at root */
	if (root == NULL){
		return root;
    }

    if(root -> key == key){
        return root;
    }

	/* Key lies in left subtree */
	if (root -> key > key)
	{
		/* Key is not in tree, return */
		if (root -> left == NULL){
            return root;
        }

		/* Zig-Zig (Left-Left) */
		if (root -> left -> key > key)
		{
			/* First recursively bring the key as root of left-left */
			root -> left -> left = splay(root -> left -> left, key);

			/* Do first rotation for root, second rotation is done after else statement : right-right rotation */
			root = rightRotate(root);
		}
		else if (root -> left -> key < key) /* Zig-Zag (Left Right) */
		{
			/* First recursively bring the key as root of left-right */
			root -> left -> right = splay(root -> left -> right, key);

			/* Do first rotation for root -> left, then second rotation after else statement : left-right rotation */
			if (root -> left -> right != NULL)
				root -> left = leftRotate(root -> left);
		}

		/* Do second rotation for root */
		if(root -> left == NULL)
            return root;
        else
            rightRotate(root);
	}
	else /* Key lies in right subtree */
	{
		/* Key is not in tree, return */
        if (root -> right == NULL){
            return root;
        }

		/* Zag-Zig (Right-Left) */
		if (root -> right -> key > key)
		{
			/* Bring the key as root of right-left */
			root -> right -> left = splay(root -> right -> left, key);

			/* Do first rotation for root -> right, then second rotation after else statement : right-left rotation */
			if (root -> right -> left != NULL)
				root -> right = rightRotate(root -> right);
		}
		else if (root -> right -> key < key) /* Zag-Zag (Right Right) */
		{
			/* Bring the key as root of right-right and do first rotation, then second rotation after else statement : left-left rotation */
			root -> right -> right = splay(root -> right -> right, key);
			root = leftRotate(root);
		}

		/* Do second rotation for root */
		if(root -> right == NULL)
            return root;
        else
            leftRotate(root);
	}
}

/* Search function */
struct splayNode *search(struct splayNode *root, int skey)
{
   splay(root, skey);
}

/* Insert function */
struct splayNode *insert(int ikey)
{
    /* If tree is empty */
    if (root == NULL){
        printf("Key Inserted !\n");
        return newNode(ikey);
    }

    /* Bring the closest leaf node to root */
    root = splay(root, ikey);

    /* If key is already present, then return */
    if (root -> key == ikey){
        printf("Duplicate Key Inserted !\n");
        return root;
    }

    /* Otherwise insert new node */
    struct splayNode *newnode  = newNode(ikey);


    if (root -> key > ikey)
    {
        newnode -> right = root;
        newnode -> left = root -> left;
        root -> left = NULL;
    }

    else
    {
        newnode -> left = root;
        newnode -> right = root -> right;
        root -> right = NULL;
    }
    // printf("Key Inserted !\n");
    return newnode; /* newnode is now new root */
}

/* Delete function */
struct splayNode* delete(int dkey)
{
    struct splayNode *temp;
    if (!root){
        printf("No Tree Present !\n");
        return NULL;
    }

    root = splay(root, dkey);

    if (dkey != root -> key){
        printf("No Delete Key was Found !\n");
        return root;
    }
    if (!root -> left)
    {
        temp = root;
        root = root -> right;
    }
    else
    {
        temp = root;

        /* New root */
        root = splay(root -> left, dkey);
        root -> right = temp -> right;
    }

    free(temp);

    /* return root of the new Splay Tree */
    printf("Key to delete was Found !\n");
    printf("Key Deleted !\n");
    return root;

}


/* Traverse function */
void preOrder(struct splayNode *root)
{
	if (root != NULL)
	{
		printf("%d ", root -> key);
		preOrder(root -> left);
		preOrder(root -> right);
	}
}

int main()
{
    // Demo values
    root = insert(10);
    root = insert(20);
    root = insert(90);
    root = insert(70);
    root = insert(50);
    root = insert(30);
    root = insert(40);
    root = insert(80);
    root = insert(60);

    int count = -1;
    while(count != 0)
    {
        printf("Enter your choice :\n");
        printf("1. Insert Element in Splay Tree\n");
        printf("2. Search Element in Splay Tree\n");
        printf("3. Delete the node from Splay Tree\n");
        printf("4. Display The Splay Tree in PreOrder\n");
        printf("5. Display The Root of Splay Tree\n");
        printf("6. Exit.\n\n");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1: read_input();
                root = insert(value);
                printf("\n\n");
                break;
        case 2: read_input();
                root = search(root, value);
                if(root -> key == value)
                    printf("Searched item found !");
                else
                    printf("Searched item not found !");
                printf("\n\n");
                break;
        case 3: read_input();
                root = delete(value);
                printf("\n\n");
                break;
        case 4: if(root == NULL)
                    printf("No Tree to Traverse !");
                else{
                    printf("The PreOrder Traversal of Splay Tree ::\n");
                    preOrder(root);
                }
                printf("\n\n");
                break;
        case 5: printf("The Root of Splay Tree : %d\n\n", root -> key);
                break;
        case 6: count++;
                break;
        default : printf("Enter the valid choice.\n");
                    break;
        }
    }
    printf("Thank You !!!");
    return 0;
}
