#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

struct node {
  // Your code here
  char* name;
  char* tea;
  struct node* left;
  struct node* right;
  
};

typedef struct node Node;

int depth(struct node *root);
int dfs(struct node *root, char *tok);
bool leafnode(struct node *root);
bool equal(char* str1, char* str2);
int max(int x, int y);

/******************The binary tree***********************
 * The following is an illustration of the binary tree
 * I *highly* recommend you test your algorithm on.
 ********************************************************
 *                        Nicholas
 *                        /      \
 *                     Mark      Parker
 *                    /          /     \
 *                Swaleh     Soroush   Other Mark
 *                                 \
 *                                 Ana
 *                                 /
 *                             Bassel
 *
 *
 * (where "/" indicates a left branch, 
 *    and "\" indicates a right branch)
 *
 */


int max(int x, int y) {
  if (x >= y) {
    return x;

  } else {
    return y;
  }
}

bool equal(char* str1, char* str2) {
  if (strcmp(str1, str2) == 0) {
    return true;

  } else {
    return false;
  }
}


bool leafnode(struct node* root) {
  if (root->left == NULL && root->right == NULL){
    return true;

  } else {
    return false;
  }
}



int depth(struct node *root) {
  if (leafnode(root)){
    return 1;

  }

  Node* left_child = root->left;
  Node* right_child = root->right;

  int left_depth = 1;
  int right_depth = 1;

  if (left_child != NULL) {
    left_depth += depth(left_child);
  }

  if (right_child != NULL) {
    right_depth += depth(right_child);
  }

  return max(left_depth, right_depth);
  
}



int recursive_search(struct node *root, char *tok){
  if (equal(root->name, tok)){
    return 1;
  }

  if (leafnode(root)){
    return -1;

  } else {
    
    Node* left_child = root->left;
    Node* right_child = root->right;
    
    int total_searches = -1;
    int left_searches = 0;
    int right_searches = 0;
  
    if (left_child != NULL) {
       // we've found it in a left branch if we get a positive value;
      // don't need to consider right as searched
      left_searches += recursive_search(left_child, tok);
       if (left_searches > 0) {
	 total_searches = 1 + left_searches;
	 return total_searches;
       }
    }

    if (right_child != NULL) {
      // we've found it in a right branch if we get a positive value;
      // we need to added left and right searches
      right_searches += recursive_search(right_child, tok);
      if (right_searches > 0) {
	total_searches = 1 + right_searches + abs(left_searches);
	return total_searches;	
      }
      
    }

    // not found
    // need to compare -- 
    total_searches += left_searches + right_searches;
    return total_searches;

    
    
  }
  
}




int dfs(struct node *root, char *tok){
  int search_result = recursive_search(root, tok);

  if (search_result > 0) {
    return search_result;
  } else {
    
    return -1;
  }
}
  



int main() {
    
    Node *root = malloc(sizeof(Node));
    root->name = "Nicholas";
    root->tea = "Orange Pekoe with Lemon";
    root->left = malloc(sizeof(Node));
    root->left->left = malloc(sizeof(Node));
    root->left->right = NULL;
    root->left->left->left = NULL;
    root->left->left->right = NULL;
    root->right = malloc(sizeof(Node));
    root->right->left = malloc(sizeof(Node));
    root->right->right = malloc(sizeof(Node));
    root->right->right->left = NULL;
    root->right->right->right = NULL;
    root->right->left->left = NULL;
    root->right->left->right = malloc(sizeof(Node));
    root->right->left->right->left = malloc(sizeof(Node));
    root->right->left->right->right = NULL;
    root->right->left->right->left->left = NULL;
    root->right->left->right->left->right = NULL;
    
    root->left->name = "Mark";
    root->left->tea = "Green";
    root->right->left->name = "Soroush";
    root->right->left->tea = "Oolong";
    
    root->right->name = "Parker";
    root->right->tea = "Rooibos";
    
    root->right->right->name = "Other Mark";
    root->right->right->tea = "Sencha";
    
    root->left->left->name = "Swaleh";
    root->left->left->tea = "White";
    
    root->right->left->right->name = "Ana";
    root->right->left->right->tea = "Hibiscus";
    
    root->right->left->right->left->name = "Bassel";
    root->right->left->right->left->tea = "Matcha";
    
    printf("The depth of the tree is: %d\n", depth(root));
    // expected result is 5.

    
    printf("Depth First Search for : Nicholas\n");
    printf("result: %d\n", dfs(root, "Nicholas"));
    // expected result is 1
    
    printf("Depth First Search for : Other Mark\n");
    printf("result: %d\n", dfs(root, "Other Mark"));
    // expected result is 8
    
    printf("Depth First Search for : Parker\n");
    printf("result: %d\n", dfs(root, "Parker"));
    
    printf("Depth First Search for : Soroush\n");
    printf("result: %d\n", dfs(root, "Soroush"));
    
    printf("Depth First Search for : Swaleh\n");
    printf("result: %d\n", dfs(root, "Swaleh"));
    
    printf("Depth First Search for : Ana\n");
    printf("result: %d\n", dfs(root, "Ana"));
    // expected result is 6
    
    printf("Depth First Search for : Julius Ceasar\n");
    printf("result: %d\n", dfs(root, "Julius Ceasar"));
    // expected result is -1
    
    free(root->right->left->right->left);
    free(root->right->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->right);
    free(root->left->left);
    free(root->left);
    free(root);

    
}
