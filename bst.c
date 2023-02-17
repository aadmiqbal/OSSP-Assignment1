#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

typedef struct _Node Node;

Node * addNode(Node * root, int value);

Node * removeNode(Node * root, int value);

void displaySubtree(Node * N);

int numberLeaves(Node * N);

Node * removeSubtree(Node * root, int value);

int nodeDepth (Node * R, Node * N);

Node * smallestinLeftSubtree(Node * N);

Node * deleteSubtree(Node* root);

struct _Node{
    int data;
    struct _Node* left;
    struct _Node* right;
};

Node * smallestinLeftSubtree(Node * N){
	Node * temp = N;
	//finds rightmost(smallest) node in subtree and returns it
	while(temp->right != NULL){
		temp = temp->right;
	}
	return temp;	
}

Node * addNode(Node *root,int value){
	Node* current = root;
	//creates root node when root argument is NULL
	if(current==NULL){
		Node *root1 =(Node*)malloc(sizeof(Node));
		root1->data = value;
		root1->right = NULL;
		root1->left = NULL;
		current = root1;
		return current;
	}else{
		while(1){ //loop
		//if adding to an already existing tree
		if(current->data == value){
			return NULL; //return null if value already exists
		}
		if(current->data > value && current->right!=NULL){
		//if current nodes data is greater than the value to be added,
		//but there is already a right child of this node,
		//current points at the right child to check where to go from there
			current = current->right;
		}else if(current->data > value && current->right==NULL){
		//the value to be inserted is greater than the current nodes value
		// and there is no right child so can allocate memory for a new node where right pointer points
			Node *root1 =(Node*)malloc(sizeof(Node));
			(root1->data) = value;
			(root1->right) = NULL;
			(root1->left) = NULL;
			(current->right) = root1;
			return (current->right);} //returns the leaf}
			//other two cases are the same but if the value to be added is greater, it goes in the left direction
		else if(current->data < value && current->left!=NULL){
			current = current->left;}
		else if(current->data < value && current->left==NULL){
			Node *root1 =(Node*)malloc(sizeof(Node));
			root1->data = value;
			root1->right = NULL;
			root1->left = NULL;
			(current->left) = root1;
			return (current->left);
	}
}
}
}

void displaySubtree(Node * N){
            Node *current = N;
            if(current==NULL){
                return;
            }
	//in order traversal
            displaySubtree(current->right); //recursively travels down to every node and prints their value
            printf("%d\n",current->data); 
            displaySubtree(current->left);
}

Node * removeNode(Node * root, int value){
	Node *current = root;
	if(current==NULL){//nothing can be removed from empty tree/node
	return NULL;}
	//recursively goes into node to be deleted
	if(current->data < value){
		current->left = removeNode(current->left,value);
	}else if(current->data > value){
		current->right = removeNode(current->right,value);
	}else{
	//node to be deleted has been found
	//leaf
	if(current->data == value &&current->left==NULL && current->right == NULL){
		free(current);
		return NULL;
	}else if(current->data == value &&current->left!=NULL && current->right == NULL){
	//only has left child
		//return left child so parent points at it
		Node * leftchild = current->left;
		free(current);
		return leftchild;
	}else if(current->data == value && current->left==NULL && current->right != NULL){
	//only has right child
		//return right child so parent points at it
		Node * rightchild = current->right;
		free(current);
		return rightchild;
	}
	else{
		//has 2 children
		//obtain a copy of the smallest node in the bigger subtree,use copy to overwrite current node and delete the original node and returns a sbtree with root value updated and one less node
		Node *smallestnode = smallestinLeftSubtree(current->left);
		current->data = smallestnode->data;
            	current->left = removeNode(current->left,smallestnode->data);
		return current;
	}
}
	return current;
}

int numberLeaves(Node * N){
	 if(N==NULL){
        return 0;
        //empty tree has no leaves
    }
    if(N->left==NULL && N->right==NULL){
        //if N is a leaf
        return 1;
    }else{
    //recursively adds all leaves from subtrees
        return numberLeaves(N->left) + numberLeaves(N->right);
    }	
	}
	
int nodeDepth (Node * R, Node * N){
//if either tree is empty return -1
    if(N==NULL){
    return -1;
    }
    if(N==NULL){
    return -1;
    }
    int n = N->data; //value of node to be searched for
    int i = 0; //holds depth
    int found = 0; //value is 0 until it is found
    Node *temp = R;
    while (temp!=NULL)
    {
    //searches for n and increments i each time temp points at a new child
        if(temp->data > n){
        temp = temp->right;
        i = i + 1;}
        else if(temp->data < n){
        temp = temp->left;
        i = i + 1;
        }else{
        //value is found so break out of while loop and change value of found variable
        found = 1;
        break;
    }
    }
    
    if(found == 0){
    return -1;} //if value was not apart of the tree
    
    return i;    
}

Node * removeSubtree(Node * root, int value){
	Node* current = root;
    if(current==NULL){ //cant remove subtree from empty tree & will run if value cant be found
        return current;
    }
     if(value< current->data){ //searching for node containing value to delete
        current->right = removeSubtree(current->right,value);
     }else if (value > current->data)
     {
        current->left = removeSubtree(current->left,value);
     }else{  //value found so deletes all nodes under this node and this node itself
        current = deleteSubtree(current);
        return NULL; //returns NULL to the child pointer of subtree's parent
     }
     return current;
}

Node * deleteSubtree(Node* root){
	Node* temp = root;
    if(temp==NULL){
        return NULL;
    }
    //recursively frees all nodes under and including root passed in
    temp->right = deleteSubtree(temp->right);
    temp->left = deleteSubtree(temp->left);
    free(temp);
    return NULL;
} 


