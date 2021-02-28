/* C program to implement Binomial Heap tree */

#include<stdio.h>
#include<malloc.h>

struct BHnode {
    int n;
    int degree;
    struct BHnode* parent;
    struct BHnode* child;
    struct BHnode* sibling;
};

struct BHnode* MAKE_BH_HEAP();
int BH_LINK(struct BHnode*, struct BHnode*);
struct BHnode* BH_CREATE_NODE(int);
struct BHnode* BH_UNION(struct BHnode*, struct BHnode*);
struct BHnode* BH_INSERT(struct BHnode*, struct BHnode*);
struct BHnode* BH_MERGE(struct BHnode*, struct BHnode*);
struct BHnode* BH_EXTRACT_MINIMUM(struct BHnode*);
int REVERT_LIST(struct BHnode*);
int DISPLAY(struct BHnode*);
struct BHnode* FIND_BHnode(struct BHnode*, int);
int BH_DECREASE_KEY(struct BHnode*, int, int);
int BH_DELETE(struct BHnode*, int);

int count = 1;

struct BHnode* MAKE_BH_HEAP() {
    struct BHnode* np;
    np = NULL;
    return np;
}

struct BHnode * H = NULL;
struct BHnode *Hr = NULL;

int BH_LINK(struct BHnode* y, struct BHnode* z) {
    y -> parent = z;
    y -> sibling = z -> child;
    z -> child = y;
    z -> degree = z -> degree + 1;
}

struct BHnode* BH_CREATE_NODE(int k) {
    struct BHnode* p;//new BHnode;
    p = (struct BHnode*) malloc(sizeof(struct BHnode));
    p -> n = k;
    return p;
}

struct BHnode* BH_UNION(struct BHnode* H1, struct BHnode* H2) {
    struct BHnode* prev_x;
    struct BHnode* next_x;
    struct BHnode* x;
    struct BHnode* H = MAKE_BH_HEAP();
    H = BH_MERGE(H1, H2);
    if (H == NULL)
        return H;
    prev_x = NULL;
    x = H;
    next_x = x -> sibling;
    while (next_x != NULL) {
        if ((x -> degree != next_x -> degree) || ((next_x -> sibling != NULL)
                && (next_x -> sibling) -> degree == x -> degree)) {
            prev_x = x;
            x = next_x;
        } else {
            if (x -> n <= next_x -> n) {
                x -> sibling = next_x -> sibling;
                BH_LINK(next_x, x);
            } else {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x -> sibling = next_x;
                BH_LINK(x, next_x);
                x = next_x;
            }
        }
        next_x = x -> sibling;
    }
    return H;
}

struct BHnode* BH_INSERT(struct BHnode* H, struct BHnode* x) {
    struct BHnode* H1 = MAKE_BH_HEAP();
    x -> parent = NULL;
    x -> child = NULL;
    x -> sibling = NULL;
    x -> degree = 0;
    H1 = x;
    H = BH_UNION(H, H1);
    return H;
}

struct BHnode* BH_MERGE(struct BHnode* H1, struct BHnode* H2) {
    struct BHnode* H = MAKE_BH_HEAP();
    struct BHnode* y;
    struct BHnode* z;
    struct BHnode* a;
    struct BHnode* b;
    y = H1;
    z = H2;
    if (y != NULL) {
        if (z != NULL && y -> degree <= z -> degree)
            H = y;
        else if (z != NULL && y -> degree > z -> degree)
            /* need some modifications here;the first and the else conditions can be merged together !!!! */
            H = z;
        else
            H = y;
    } else
        H = z;
    while (y != NULL && z != NULL) {
        if (y -> degree < z -> degree) {
            y = y -> sibling;
        } else if (y -> degree == z -> degree) {
            a = y -> sibling;
            y -> sibling = z;
            y = a;
        } else {
            b = z -> sibling;
            z -> sibling = y;
            z = b;
        }
    }
    return H;
}

int DISPLAY(struct BHnode* H) {
    struct BHnode* p;
    if (H == NULL) {
        printf("\nHEAP EMPTY");
        return 0;
    }
    printf("\nTHE ROOT BHnodeS ARE:-\n");
    p = H;
    while (p != NULL) {
        printf("%d", p -> n);
        if (p -> sibling != NULL)
            printf("- -> ");
        p = p -> sibling;
    }
    printf("\n");
}

struct BHnode* BH_EXTRACT_MINIMUM(struct BHnode* H1) {
    int min;
    struct BHnode* t = NULL;
    struct BHnode* x = H1;
    struct BHnode *Hr;
    struct BHnode* p;
    Hr = NULL;
    if (x == NULL) {
        printf("\nNOTHING TO EXTRACT");
        return x;
    }
    //    int min=x -> n;
    p = x;
    while (p -> sibling != NULL) {
        if ((p -> sibling) -> n < min) {
            min = (p -> sibling) -> n;
            t = p;
            x = p -> sibling;
        }
        p = p -> sibling;
    }
    if (t == NULL && x -> sibling == NULL)
        H1 = NULL;
    else if (t == NULL)
        H1 = x -> sibling;
    else if (t -> sibling == NULL)
        t = NULL;
    else
        t -> sibling = x -> sibling;
    if (x -> child != NULL) {
        REVERT_LIST(x -> child);
        (x -> child) -> sibling = NULL;
    }
    H = BH_UNION(H1, Hr);
    return x;
}

int REVERT_LIST(struct BHnode* y) {
    if (y -> sibling != NULL) {
        REVERT_LIST(y -> sibling);
        (y -> sibling) -> sibling = y;
    } else {
        Hr = y;
    }
}

struct BHnode* FIND_BHnode(struct BHnode* H, int k) {
    struct BHnode* x = H;
    struct BHnode* p = NULL;
    if (x -> n == k) {
        p = x;
        return p;
    }
    if (x -> child != NULL && p == NULL) {
        p = FIND_BHnode(x -> child, k);
    }

    if (x -> sibling != NULL && p == NULL) {
        p = FIND_BHnode(x -> sibling, k);
    }
    return p;
}

int BH_DECREASE_KEY(struct BHnode* H, int i, int k) {
    int temp;
    struct BHnode* p;
    struct BHnode* y;
    struct BHnode* z;
    p = FIND_BHnode(H, i);
    if (p == NULL) {
        printf("\nINVALID CHOICE OF KEY TO BE REDUCED");
        return 0;
    }
    if (k > p -> n) {
        printf("\nSORY!THE NEW KEY IS GREATER THAN CURRENT ONE");
        return 0;
    }
    p -> n = k;
    y = p;
    z = p -> parent;
    while (z != NULL && y -> n < z -> n) {
        temp = y -> n;
        y -> n = z -> n;
        z -> n = temp;
        y = z;
        z = z -> parent;
    }
    printf("\nKEY REDUCED SUCCESSFULLY!");
}

int BH_DELETE(struct BHnode* H, int k) {
    struct BHnode* np;
    if (H == NULL) {
        printf("\nHEAP EMPTY");
        return 0;
    }

    BH_DECREASE_KEY(H, k, -1000);
    np = BH_EXTRACT_MINIMUM(H);
    if (np != NULL)
        printf("\nBHnode DELETED SUCCESSFULLY");
}

int main() {
    int i, n, m, l;
    struct BHnode* p;
    struct BHnode* np;
    char ch;
    printf("ENTER THE NUMBER OF ELEMENTS : ");
    scanf("%d", &n);
    printf("\nENTER THE ELEMENTS:\n");
    for (i = 1; i <= n; i++) {
        scanf("%d", &m);
        np = BH_CREATE_NODE(m);
        H = BH_INSERT(H, np);
    }
    DISPLAY(H);
    do {
        printf("\nMENU :-\n");
        printf(
                "\n1)INSERT AN ELEMENT\n2)EXTRACT THE MINIMUM KEY BHnode\n3)DECREASE A BHnode KEY\n4)DELETE A BHnode\n5)QUIT\nENTER YOUR CHOICE : ");
        scanf("%d", &l);
        switch (l) {
        case 1:
            do {
                printf("\nENTER THE ELEMENT TO BE INSERTED : ");
                scanf("%d", &m);
                p = BH_CREATE_NODE(m);
                H = BH_INSERT(H, p);
                printf("\nNOW THE HEAP IS :\n");
                DISPLAY(H);
                printf("\nINSERT MORE(Y/y) = \n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'Y' || ch == 'y');
            break;
        case 2:
            do {
                printf("\nEXTRACTING THE MINIMUM KEY BHnode");
                p = BH_EXTRACT_MINIMUM(H);
                if (p != NULL)
                    printf("\nTHE EXTRACTED BHnode IS %d", p -> n);
                printf("\nNOW THE HEAP IS:\n");
                DISPLAY(H);
                printf("\nEXTRACT MORE(Y/y) = \n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'Y' || ch == 'y');
            break;
        case 3:
            do {
                printf("\nENTER THE KEY OF THE BHnode TO BE DECREASED : ");
                scanf("%d", &m);
                printf("\nENTER THE NEW KEY : ");
                scanf("%d", &l);
                BH_DECREASE_KEY(H, m, l);
                printf("\nNOW THE HEAP IS :\n");
                DISPLAY(H);
                printf("\nDECREASE MORE(Y/y) = \n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'Y' || ch == 'y');
            break;
        case 4:
            do {
                printf("\nENTER THE KEY TO BE DELETED : ");
                scanf("%d", &m);
                BH_DELETE(H, m);
                printf("\nDELETE MORE(Y/y) = \n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'y' || ch == 'Y');
            break;
        case 5:
            printf("\nTHANK YOU !\n");
            break;
        default:
            printf("\nINVALID ENTRY...TRY AGAIN....!\n");
        }
    } while (l != 5);
}
