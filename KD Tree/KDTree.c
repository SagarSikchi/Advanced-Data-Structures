#include<stdio.h>
#include<stdlib.h>

const int k = 2;
int input_point[2], i, choice, flag = 0;

/* A structure to represent KDnode of KD Tree */
struct KDnode
{
	int point[2];
	struct KDnode *left;
    struct KDnode *right;
};

int arePointsSame(int point1[], int point2[]) {
	for (i = 0; i < k; ++i)
		if (point1[i] != point2[i])
			return 0;
	return 1;
}

void read_input(){
    printf("Enter Your Point :\n");
    for (i = 0; i < k; i++){
        scanf("%d", &input_point[i]);
    }
    printf("\n");
}


int searchRec(struct KDnode *root, int point[], unsigned depth) {
	if (root == NULL) {
		return 0;
    }
	if (arePointsSame(root -> point, point)) {
		return 1;
    }
	unsigned cd = depth % k;

	if (point[cd] < root -> point[cd]) {
		return searchRec(root -> left, point, depth + 1);
    }
	return searchRec(root -> right, point, depth + 1);
}

/*
int search(struct KDnode *root, int point[]) {
	return searchRec(root, point, 0);
}
*/

struct KDnode *newKDnode(int arr[])
{
	struct KDnode *temp;
    temp = (struct KDnode*)malloc(sizeof(struct KDnode));

	for (i = 0; i < k; i++) {
	   temp -> point[i] = arr[i];
    }

	temp -> left = NULL;
    temp -> right = NULL;
	return temp;
}

struct KDnode *insertRec(struct KDnode *root, int point[], unsigned depth) {
	if (root == NULL) {
	    return newKDnode(point);
    }

	unsigned cd = depth % k;

	if (point[cd] < (root -> point[cd])) {
		root -> left = insertRec(root -> left, point, depth + 1);
    }
	else{
		root -> right = insertRec(root -> right, point, depth + 1);
    }
	return root;
}
/*
struct KDnode *insert(struct KDnode *root, int point[]) {
	return insertRec(root, point, 0);
}
*/

struct KDnode *minNode(struct KDnode *x, struct KDnode *y, struct KDnode *z, int d){
    struct KDnode *res = x;
    if (y != NULL && y->point[d] < res->point[d])
        res = y;
    if (z != NULL && z->point[d] < res->point[d])
        res = z;
    return res;
}

struct KDnode *findMinRec(struct KDnode *root, int d, unsigned depth){
    if (root == NULL)
        return NULL;

    unsigned cd = depth % k;

    if (cd == d){
        if (root->left == NULL)
            return root;
        return findMinRec(root->left, d, depth+1);
    }

    return minNode(root, findMinRec(root->left, d, depth+1), findMinRec(root->right, d, depth+1), d);
}

struct KDnode *findMin(struct KDnode *root, int d)
{
    return findMinRec(root, d, 0);
}

void copyPoint(int p1[], int p2[]){
    for (i = 0; i < k; i++)
        p1[i] = p2[i];
}

struct KDnode *deleteNodeRec(struct KDnode *root, int point[], int depth){
    if (root == NULL)
        return NULL;

    int cd = depth % k;

    if (arePointsSame(root->point, point)){
        if (root->right != NULL){
            struct KDnode *min = findMin(root->right, cd);

            copyPoint(root->point, min->point);

            root->right = deleteNodeRec(root->right, min->point, depth+1);
        }
        else if (root->left != NULL) {
            struct KDnode *min = findMin(root->left, cd);
            copyPoint(root->point, min->point);
            root->left = deleteNodeRec(root->left, min->point, depth+1);
        }
        else {
            free(root);
            return NULL;
        }
        return root;
    }

    if (point[cd] < root->point[cd])
        root->left = deleteNodeRec(root->left, point, depth+1);
    else
        root->right = deleteNodeRec(root->right, point, depth+1);
    return root;
}

struct KDnode* deleteNode(struct KDnode *root, int point[]){
    return deleteNodeRec(root, point, 0);
}

void displayTree(struct KDnode *rootN){
    if (rootN == NULL)
        return;
    else{
        displayTree(rootN -> left);
        printf("{%d %d}    ", rootN -> point[0], rootN -> point[1]);
        displayTree(rootN -> right);
    }
}

void setInput(int x, int y) {
    input_point[0] = x;
    input_point[1] = y;
}

int main() {
    struct KDnode *root;
    root = (struct KDnode*)malloc(sizeof(struct KDnode));
    root = NULL;

    // Demo Values
    setInput(1, 2);
    root = insertRec(root, input_point, 0);
    setInput(3, 2);
    root = insertRec(root, input_point, 0);
    setInput(2, 1);
    root = insertRec(root, input_point, 0);
    setInput(1, 3);
    root = insertRec(root, input_point, 0);
    setInput(2, 2);
    root = insertRec(root, input_point, 0);
    setInput(3, 1);
    root = insertRec(root, input_point, 0);
    
    int count = -1;
    while(count != 0){
        printf("Enter your choice :\n");
        printf("1: Insert point in KD Tree\n");
        printf("2: Search point in KD Tree\n");
        printf("3: Delete the node from KD Tree\n");
        printf("4: Display The KD Tree Inorder\n");
        printf("5: Display The Root of KD Tree\n");
        printf("6: Exit\n\n");
        scanf("%d", &choice);

        switch(choice){
            case 1: read_input();
	            root = insertRec(root, input_point, 0);
                break;
            case 2: read_input();
                flag = searchRec(root, input_point, 0);
                if(flag == 1)
                    printf("Found\n");
                else
                     printf("Not Found\n");
                printf("\n");
                break;
            case 3: read_input();
                root = deleteNode(root, input_point);
                printf("\n");
                break;
            case 4: displayTree(root);
                printf("\n\n");
                break;
            case 5: printf("Root Node: {%d %d}\n\n", root -> point[0], root -> point[1]);
                break;
            case 6: count++;
                break;
            default : printf("Enter the valid choice\n");
                break;
        }
    }
    printf("Thank You !!!");
    return 0;
}
