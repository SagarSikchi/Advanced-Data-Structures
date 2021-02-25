#include <stdio.h>
#include <stdlib.h>

struct treeNode
{
   enum
   {
      black,
      red
   } color;
   int data;
   struct treeNode *left;
   struct treeNode *right;
   struct treeNode *parent;
} *root = NULL;         /* Root Node */
struct treeNode *tnode; /* Parent of Root Node and replace NULL */
int value;
int choice;

int read_input()
{
   printf("Enter the value :");
   scanf("%d", &value);
   return value;
}

int find(int item, struct treeNode **fnode)
{
   struct treeNode *node_;
   if (root == tnode) /* Tree is Empty */
   {
      *fnode = tnode;
      return 0;
   }
   if (item == root->data) /* Item is at Root */
   {
      *fnode = root;
      return 1;
   }
   /* Initialize node_ */
   if (item < root->data)
      node_ = root->left;
   else
      node_ = root->right;
   while (node_ != tnode)
   {
      if (item == node_->data)
      {
         *fnode = node_;
         return 1;
      }
      if (item < node_->data)
         node_ = node_->left;
      else
         node_ = node_->right;
   }
   *fnode = tnode; /* Item is not Found */
   return 0;
}

struct treeNode *succ(struct treeNode *fnode)
{
   struct treeNode *node_ = fnode->right;
   while (node_->left != tnode)
   {
      node_ - node_->left;
   }
   return node_;
}

void display(struct treeNode *node, int level)
{
   int i;
   if (node != tnode)
   {
      display(node->left, level + 1);
      /* printf("  ");
     for(i = 0; i < level; i++)
        printf(" "); */
      printf("%d ", node->data);
      if (node->color == red)
         printf("-> [RED]\n");
      else
         printf("-> [BLACK]\n");
      display(node->right, level + 1);
   }
}

void l_rotation(struct treeNode *node_)
{
   struct treeNode *node_r = node_->right; /* node_r is the right child of node_  */
   node_->right = node_r->left;
   if (node_r->left != tnode)
      node_r->left->parent = node_;
   node_r->parent = node_->parent;

   if (node_->parent == tnode)
      root = node_r;
   else if (node_ == node_->parent->left)
      node_->parent->left = node_r;
   else
      node_->parent->right = node_r;
   node_r->left = node_;
   node_->parent = node_r;
}

void r_rotation(struct treeNode *node_)
{
   struct treeNode *node_l; /* node_l is the left child of node_  */
   node_l = node_->left;
   node_->left = node_l->right;
   if (node_l->right != tnode)
      node_l->right->parent = node_;
   node_l->parent = node_->parent;

   if (node_->parent == tnode)
      root = node_l;

   else if (node_ == node_->parent->right)
      node_->parent->right = node_l;
   else
      node_->parent->left = node_l;
   node_l->right = node_;
   node_->parent = node_l;
}

void insert_balance(struct treeNode *newNode)
{
   struct treeNode *parent_node, *grand_parent, *uncle;
   while (newNode->parent->color == red)
   {
      parent_node = newNode->parent;
      grand_parent = parent_node->parent;

      if (parent_node == grand_parent->left)
      {
         uncle = grand_parent->right;

         if (uncle->color == red)
         { /*  Uncle is Red and case L_1 */
            grand_parent->color = red;
            parent_node->color = black;
            uncle->color = black;
            newNode = grand_parent;
         }
         else
         {                                     /* Uncle is Black */
            if (newNode == parent_node->right) /* case L_2a */
            {
               l_rotation(parent_node);
               newNode = parent_node;
               parent_node = newNode->parent;
            }
            /* case L_2b */
            parent_node->color = black;
            grand_parent->color = red;
            r_rotation(grand_parent);
         }
      }
      else if (parent_node == grand_parent->right)
      {
         uncle = grand_parent->left;

         if (uncle->color == red) /* Uncle is Red and case R_1 */
         {
            grand_parent->color = red;
            parent_node->color = black;
            uncle->color = black;
            newNode = grand_parent;
         }
         else
         {                                    /* Uncle is Black */
            if (newNode == parent_node->left) /* case R_2a */
            {
               r_rotation(parent_node);
               newNode = parent_node;
               parent_node = newNode->parent;
            }
            /* case R_2b */
            parent_node->color = black;
            grand_parent->color = red;
            l_rotation(grand_parent);
         }
      }
   }
   root->color = black;
}

void delete_balance(struct treeNode *d_node)
{
   struct treeNode *sibling;
   while (d_node != root)
   {
      if (d_node == d_node->parent->left)
      {
         sibling = d_node->parent->right;
         if (sibling->color == red) /* case L_1 */
         {
            sibling->color = black;
            d_node->parent->color = red;
            l_rotation(d_node->parent);
            sibling = d_node->parent->right; /* new Sibling */
         }
         if (sibling->left->color == black && sibling->right->color == black)
         {
            sibling->color = red;
            if (d_node->parent->color == red) /* case L_2a */
            {
               d_node->parent->color = black;
               return;
            }
            else
               d_node = d_node->parent; /* case L_2b */
         }
         else
         {
            if (sibling->right->color == black) /* case L_3a */
            {
               sibling->left->color = black;
               sibling->color = red;
               r_rotation(sibling);
               sibling = d_node->parent->right;
            }
            sibling->color = d_node->parent->color; /* case L_3b */
            d_node->parent->color = black;
            sibling->right->color = black;
            l_rotation(d_node->parent);
            return;
         }
      }
      else
      {
         sibling = d_node->parent->left;
         if (sibling->color == red) /* case R_1 */
         {
            sibling->color = black;
            d_node->parent->color = red;
            r_rotation(d_node->parent);
            sibling = d_node->parent->left;
         }
         if (sibling->right->color == black && sibling->left->color == black)
         {
            sibling->color = red;
            if (d_node->parent->color == red) /* case R_2a */
            {
               d_node->parent->color = black;
               return;
            }
            else
               d_node = d_node->parent; /* case R_2b */
         }
         else
         {
            if (sibling->left->color == black) /* case R_3a */
            {
               sibling->right->color = black;
               sibling->color = red;
               l_rotation(sibling);
               display(root, 1);
               sibling = d_node->parent->left;
            }
            sibling->color = d_node->parent->color; /* case R_3b */
            d_node->parent->color = black;
            sibling->left->color = black;
            r_rotation(d_node->parent);
            return;
         }
      }
   }
}

void recursion_inorder(struct treeNode *tmp)
{
   if (tmp != tnode)
   {
      recursion_inorder(tmp->left);
      printf("%d ", tmp->data);
      recursion_inorder(tmp->right);
   }
}

void insert(int key)
{
   struct treeNode *new, *temp, *current;
   current = tnode;
   new = root;

   while (new != tnode)
   {
      current = new;
      if (key < new->data)
         new = new->left;
      else if (key > new->data)
         new = new->right;
      else
      {
         printf("Duplicate Key !\n");
         return;
      }
   }
   temp = (struct treeNode *)malloc(sizeof(struct treeNode));
   temp->data = key;
   temp->left = tnode;
   temp->right = tnode;
   temp->color = red;
   temp->parent = current;
   if (current == tnode)
      root = temp;
   else if (temp->data < current->data)
      current->left = temp;
   else
      current->right = temp;
   insert_balance(temp);
}

void delete (int key)
{
   struct treeNode *child, *node, *successor;
   if (!find(key, &node))
   {
      printf("Item not present !\n");
      return;
   }
   if (node->left != tnode || node->right != tnode)
   {
      successor = succ(node);
      node->data = successor->data;
      node = successor;
   }
   if (node->left != tnode)
      child = node->left;
   else
      child = node->right;
   child->parent = node->parent;
   if (node->parent == tnode)
      root = child;
   else if (node == node->parent->left)
      node->parent->left = child;
   else
      node->parent->right = child;
   if (child == root)
      child->color = black;
   else if (node->color == black) /* Black Node */
   {
      if (child != tnode) /* One Child which is Red */
         child->color = black;
      else
         delete_balance(child);
   }
}

void preInsertion()
{
   insert(10);
   insert(20);
   insert(30);
   insert(80);
   insert(90);
   insert(50);
   insert(40);
   insert(60);
}

int main()
{
   tnode = (struct treeNode *)malloc(sizeof(struct treeNode));
   tnode->data = -1;
   tnode->color = black;
   root = tnode;
   preInsertion(); // Demo values in the tree
   int count = -1;
   while (count != 0)
   {
      printf("Enter your choice :\n");
      printf("1. Insert Element in RB Tree\n");
      printf("2. Delete the node from RB Tree\n");
      printf("3. Display The RB Tree in Inorder Traversal\n");
      printf("4. Display the RB Tree with Color of Nodes\n");
      printf("5. Exit().\n\n");
      scanf("%d", &choice);

      switch (choice)
      {
      case 1:
         read_input();
         insert(value);
         break;
      case 2:
         read_input();
         delete (value);
         break;
      case 3:
         recursion_inorder(root);
         printf("\n");
         break;
      case 4:
         display(root, 1);
         printf("\n");
         break;
      case 5:
         count++;
         break;
      default:
         printf("Enter the valid choice.\n");
         break;
      }
   }
   printf("Thank You !!!");
   return 0;
}
