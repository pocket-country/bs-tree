/*
for the btxx.c programs see cslibrary.stanford.edu/110/BinaryTrees.html
Nick Parlante nick.parlante@cs.stanford.edu c2000-2001
... this page also saved in evernote
*/
#import <stdio.h>
#import <stdlib.h>

// our basic node structure
struct node {
  int data;
  struct node* left;
  struct node* right;
};

/* given a binary tree, return true if node with target data found in tree */
static int lookup(struct node* node, int target) {
  // base case empty tree, return false
  if ( node == NULL ) {
    return(false);
  }
  else {
    // see if we find data value in this node
    if (target == node->data) return(true);
    else {
      // recurse down sub-tree.  Note selecting branch depends on def of btree
      if (target < node->data) return(lookup(node->left, target));
      else return(lookup(node->right, target));
    }
  }
}

/*
given a binary tree and a new value, return a _new_ tree with a node
containing that value.  Note page discuss this as a method for avoiding
pass by ref parameteres, means call has to be used as a function

Uses a 'helper' function - which is actually just a function i don't get
all the fuss over the 'helper' Bit
*/
struct node* newNode(int data) {
  struct node* node = new(struct node); //allocate memory for data structure
  node->data = data;
  node->left = NULL;
  node->right= NULL;

  return(node);
}

struct node* insert(struct node* node, int data) {
  // empty tree, simply return new node as root
  if (node == NULL) {
    return (newNode(data));
  }
  else {
    //recurse down tree
    if (data <= node->data) node->left = insert(node->left, data);
    else node->right = insert(node->right,data);

    return(node);
  }
}

/*
Print a BST in order -- we will save the the "top down" view for later,
I have to think about thiis and my use vis tools ... this copies answer from
worksheet
*/
void printTree(struct node* node) {
  if (node == NULL) return;

  printTree(node->left);
  printf(" %d ", node->data);
  printTree(node->right);
}

// does this work to print by 'level'?
void printTreeL(struct node* node, const char* side) {
  if (node == NULL) {
    printf(" %s ", side);
    return;
  }
  printf(" %d ", node->data);
  printTreeL(node->left, "L");
  printTreeL(node->right, "R");
}


/*
Now buiild a tree and try this out ... next step will be to put together an
intreface
*/
int main (int argc, char *argv[]) {

  printf("Hello World \n");

  printf("Our list will have %d nodes \n", argc-1);

  //generate root node
  struct node* root = NULL;
  // loop over input args and add 'em in
  for (int i = 1; i < argc; ++i ) {
    //might want some guard here, atoi doc says
    //returns 0 when invalid.
    int value = atoi(argv[i]);
    printf("node %d value is %d\n", i, value);
    root = insert(root, value);
  }

  //if (true) printf("true\n");
  //if (false) printf("false\n");

  // a simple tree - we are going to make this from
  // command line arguments
  //struct node* root = newNode(2);
  //root->left = newNode(1);
  //root->right = newNode(3);

  printTreeL(root,"R");
  //how to get this into the actual function
  printf("\n\n");

  printf("That's all folks\n");
}
