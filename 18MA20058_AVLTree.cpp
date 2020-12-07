/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/
    
#include<iostream>
#include<math.h>
using namespace std;

struct node                     // A structure which is used to represent each node of the tree
{
    int data,height;            // Each node stores data and the height of that node, and pointers to its parent, left child and right child
    node* left = NULL;
    node* right = NULL;
    node* parent = NULL;
};

int max(int a, int b)           // A utility function to calculate the maximum of two values a and b
{
	if(a>=b)
	  return a;
	else
	  return b;
}

bool is_power_of_2(int x)       // Function to return whether an input number is a power of 2 or not (This is used in printTree function)
{
	while(x%2==0)
	  x=x/2;
	if(x==1)
	  return true;
	else
	  return false;
}

class AVL_Tree                           
{
	private:
		node* root;                      // pointer to the root of the tree
	
	public:
		int tree_arr[10000];             // tree_arr stores the corresponding array for the tree in heap representation
		AVL_Tree()                       // No argument constructor
		  {
		  	root=NULL;
		  	for(int i=0;i<10000;i++)
		  	  tree_arr[i]=INT_MAX;
		  }
		
		node* get_root()                // Function to return the root of the tree
		  {
		  	return root;
		  }
		
		void insert_node(int val);      // Function to perform insertion of a node in the tree
		
		int get_height(node* item)      // Function to get the height of a node in the tree
		  {
		  	if(item==NULL)
		  	  return 0;
		  	else
		  	  return item->height;
		  }
		
		int balance_factor(node* item)   // balance factor of a node is : bf = hl-hr ; where hl = height of its left child and hr = height of its right child
		  {
		  	int bf=(get_height(item->left)-get_height(item->right));
		  	return bf;
		  }
		
		void height_balance(node* item); // Function to recalculate height of a node, after insertion or deletion is done 
		void fix(node* item);            // Function which checks whether left or right rotation is needed for rebalancing the tree, and calls those functions
		void ReBalance(node* temp);      // Function to perform rebalancing after insertion or deletion of a node
		void LeftRotate(node *x);        // Function to perform left rotation about a node, for rebalancing heights
		void RightRotate(node* x);       // Function to perform right rotation about a node, for rebalancing heights
	
		void InOrderTraversal(node* temp);    // Function to perform In-order traversal of the tree -> This will print the elements in sorted order
		void Remove_node(node* p, node* cur, int val);
		void Delete(int val);                 // Function to delete a value (if found) from the tree
		void Build_array(node* root, int i);  // Function to build the tree_arr array corresponding to the tree
		void printTree();                     // Function to print the tree
};

void AVL_Tree::insert_node(int val)
{
	if(root==NULL)                       // If the tree is empty, the element to be inserted will be the root
	  {
		root=new node;
		root->data=val;
		root->height=0;
		root->parent=NULL;
		root->left=NULL; root->right=NULL;
	  }
	else if(root!=NULL)
	  {
		node* x=get_root();          // node x is used to traverse down the tree to find the place where BST (Binary Search Tree) insert of node item will take place
		node* item=new node;         // item is the new node to be inserted, which shall contain the data: val
		item->data=val;
			  	
		while(x!=NULL)                  // The new node must be inserted as some leaf node, hence the check : while x doesn't become NULL
		  {
			if(val < (x->data))         // If val is lesser than data at current node, move to the left subtree of the current node
			  {
			  	if(x->left==NULL)
			  	  {
			  	  	x->left=item;
			  	  	item->height=0;
			  	  	item->parent=x;
			  	  	break;
				  }
				else
				  x=x->left;
			  }
			
			else if(val > (x->data))    // If val is greater than data at current node, move to the right subtree of the current node
			  {
			  	if(x->right==NULL)
			  	  {
			  	  	x->right=item;
			  	  	item->height=0;
			  	  	item->parent=x;
			  	  	break;
				  }
				else
				  x=x->right;
			  }
			
			else if(val==x->data)
			  return;  	  	
		  }
		
		ReBalance(item);                // Check if any balancing of height is required after this insertion
	  }
}

void AVL_Tree::height_balance(node* item)
{
	int l=0,r=0;
	if((item->left)!=NULL)
	  l=item->left->height;
	if((item->right)!=NULL)
	  r=item->right->height;
	item->height=max(l,r)+1;           // Height of a node = 1 + max of heights of its left and right child 
}

void AVL_Tree::fix(node* item)         // Function which checks whether left or right rotation is needed for rebalancing the tree, and calls those functions
{
	if(balance_factor(item) > 1)       // If balance factor of the current node is > 1, then Right rotate is needed as tree is heavier/lengthier on the left subtree of this node 
	  {
	  	if(balance_factor(item->left) < 0)
	  	  {
	  	  	LeftRotate(item->left);    // LR rotate : double rotation case
		  }
		RightRotate(item);
		height_balance(item);          // Recalculating the height of this node after performing rotation
	  }
	
	else if(balance_factor(item) < -1)  // If balance factor of this node is < -1, then Left rotate is needed as tree is heavier/lengthier on the right subtree of this node
	  {
	  	if(balance_factor(item->right) > 0)
	  	  {
	  	  	RightRotate(item->right);   // RL rotate : double rotation case 
		  }
		LeftRotate(item);               
		height_balance(item);           // Recalculating the height of this node after performing rotation
	  }
}

void AVL_Tree::ReBalance(node* temp)
{
	if(temp==root)
	  fix(root);
	else
	  {
	  	while(temp != NULL)
	  	  {
	  	  	height_balance(temp);      // Recalculating the height of the nodes 
	  	  	temp=temp->parent;
	  	  	if(temp != NULL)
	  	  	  fix(temp);
		  }
	  }
}

void AVL_Tree::LeftRotate(node* x)     // Function to perform Left rotate about node x 
{
	node* temp=new node;
	if(x->right->left)
	  { temp->right = x->right->left;
      }
	temp->left = x->left;
	temp->data = x->data;
	x->data = x->right->data;
	
	x->left = temp;
	if(temp->left)
	  { temp->left->parent=temp;
      }
	if(temp->right)
	  { temp->right->parent=temp;
      }
	temp->parent=x;
	
	if(x->right->right)
	  { x->right=x->right->right;
      }
	else
	  { x->right=NULL;
      }
	
	if(x->right)
	  { x->right->parent=x;
      }
	
	height_balance(x->left);            // Recalculating the heights of the required nodes after left rotation about x
	if(x->right)
	  height_balance(x->right);
	height_balance(x);
}

void AVL_Tree::RightRotate(node* x)     // Function to perform Right rotate about node x
{
	node* temp=new node;
	if(x->left->right)
	  temp->left=x->left->right;
	temp->right=x->right;
	temp->data=x->data;
	x->data=x->left->data;
	
	x->right=temp;
	if(temp->left)
	  temp->left->parent=temp;
	if(temp->right)
	  temp->right->parent=temp;
	temp->parent=x;
	
	if(x->left->left)
	  x->left=x->left->left;
	else
	  x->left=NULL;
	
	if(x->left)
	  x->left->parent=x;
	
	height_balance(x->right);           // Recalculating the heights of the required nodes after right rotation about x 
	if(x->left)
	  height_balance(x->left);
	height_balance(x);	
}


void AVL_Tree::InOrderTraversal(node* temp)   // Function for In-order traversal of the tree : Left subtree -> Root -> Right subtree
{
	if(temp==NULL)
	  return;
	InOrderTraversal(temp->left);
	cout << " " << temp->data;
	InOrderTraversal(temp->right);
}

void AVL_Tree::Remove_node(node* p, node* cur, int val)  // Function to remove a node from the tree and call ReBalance() function for rebalancing the AVL tree
{
	if(cur==NULL)
	  return;
	if(cur->data==val)
	  {
	  	if(cur->left==NULL && cur->right==NULL)        // Case 1 : When cur node is a leaf node
	  	  {
	  	  	if(p->data==cur->data)
	  	  	  root=NULL;
	  	  	else if(p->right==cur)
	  	  	  p->right=NULL;
	  	  	else
	  	  	  p->left=NULL;
	  	  	ReBalance(p);
		  }
		
		else if(cur->left!=NULL && cur->right==NULL)   // Case 2
		  {
		  	int x=cur->data;
		  	cur->data=cur->left->data;
		  	cur->left->data=x;
		  	Remove_node(cur,cur->left,val);
		  }
		
		else if(cur->left==NULL && cur->right!=NULL)   // Case 3
		  {
		  	int x=cur->data;
		  	cur->data=cur->right->data;
		  	cur->right->data=x;
		  	Remove_node(cur,cur->right,val);
		  }
		
		else                                           // Case 4
		  {
		  	node* temp=cur->right;
		  	int flag=0;
		  	while(temp->left!=NULL)
		  	  {
		  	  	flag=1;
		  	  	p=temp;
		  	  	temp=temp->left;
			  }
		    if(flag==0)
              p=cur;
            int x=cur->data;
            cur->data=temp->data;
            temp->data=x;
            Remove_node(p,temp,temp->data);
		  }
	  }
}

void AVL_Tree::Delete(int val)   // Function to search for a node with its data = val, and deletes it using Remove_node() function, if found 
{
	node* temp=root;
	node* p=temp;
	int flag=0;
	if(temp==NULL)
	  Remove_node(NULL,NULL,val);
	
	while(temp!=NULL)
	  {
	  	if(val==temp->data)
	  	  {
	  	  	flag=1;
	  	  	Remove_node(p,temp,val);
	  	  	break;
		  }
		else if(val < temp->data)
		  {
		  	p=temp;
		  	temp=temp->left;
		  }
		else
		  {
		  	p=temp;
		  	temp=temp->right;
		  }
	  }
	
	if(flag==0)
	  {
	  	cout<<"\nElement doesn't exist!!\n";
	  }
}

void AVL_Tree::Build_array(node* root, int i)    // Function to build the tree_arr array corresponding to the tree, which is like a heap tree
{
	if(root==NULL)                               // If a node is empty, we store INT_MAX for that node in the tree_arr array
	  { tree_arr[i]=INT_MAX;
	    return;
	  }
	else
	  tree_arr[i]=root->data;
	
	if(root->left==NULL && root->right==NULL)    // If the current node is a leaf node, then return
	  return;
	Build_array(root->left,2*i+1);               // Otherwise, assign position for the left and right child of the current node 
	Build_array(root->right,2*i+2);
}

void AVL_Tree::printTree()               // Function to print the AVL tree using the tree_arr array representation of tree
{
	for(int i=0;i<10000;i++)
	  tree_arr[i]=INT_MAX;               // Initializing the elements of tree_arr array to INT_MAX which represents that the node is blank presently 
	Build_array(get_root(),0);           // Fill up the tree_arr array corresponding to the tree using Build_array function
	int i,j,h,g;                         
	h=get_height(get_root());            // h stores the height of the root of the tree
	cout<<endl;
	cout<<"Height of the tree = "<<h<<endl;   
	
	cout<<"\nThe AVL tree now is : \n\n";
	for(j=1;j<pow(2,h-1);j++)
	  	cout<<"  ";
	cout<<" ";
	i=0;g=h;                             // g stores the current height at each level of the tree 
	while(i<pow(2,h+1)-1)
	  {	
	  	if(tree_arr[i]==INT_MAX)         // if an element is INT_MAX then that is a blank node, so print a white space there
	  	  cout<<"  ";
	  	else
	  	  { 
	  	    if(tree_arr[i]%10 == 0)      // If it is a single digit number, print two extra spaces with it, for tree to look good
			  cout<<tree_arr[i]<<"   ";
			else if(tree_arr[i]%100==0)  // If a two digit number, then print one extra space
			  cout<<tree_arr[i]<<"  ";
			else
			  cout<<tree_arr[i]<<" ";
	      }
	  	if(is_power_of_2(i+2))           // if (i+2) is a power of 2, we break from current level and move to the next level of the tree
	  	  { cout<<endl;
	  	    g--;                         // height reduces by 1 for the next level
	  	    for(j=1;j<pow(2,g-1);j++)
	  	      cout<<"  ";
	      }
	    else
	      {
	      	for(j=1;j<pow(2,g);j++)
	  	      cout<<"  ";
		  }
	  	i++;
	  }
	cout<<endl<<endl;
    
}

int main()
{
	AVL_Tree T,S;
	
	S.insert_node(30);
	S.insert_node(10);
	S.insert_node(50);
	
	S.printTree();                      // Printing the AVL tree S with values 30,10,50 inserted
	
	S.insert_node(90);
	S.insert_node(12);
	S.insert_node(85);
	S.insert_node(5);
	
	S.printTree();                      // Printing the AVL tree S with again 90 and 5 inserted

	S.Delete(50);
	S.insert_node(88);
	S.insert_node(54);
	S.printTree();                      // Printing the AVL tree S again with value 50 deleted and 88,54 inserted
	
	S.Delete(10);
	cout<<"In-order traversal of this tree :\n";
	S.InOrderTraversal(S.get_root());   // In-order traversal of the tree S gives the elements of S in sorted order
	cout<<endl<<endl;
	S.printTree();                      // Printing the final AVL tree S

	int i,j,h,g;                        // h stores the height of the root of the tree
	int arr[]={1,17,2,6,12,19};
	int n=6;                            // n is the size of the array
	cout<<"Input array :\n";
	for(i=0;i<n;i++)
	  { T.insert_node(arr[i]);          // Inserting the elements of the array in the tree T
	    cout<<" "<<arr[i];
	  }
	cout<<endl;
	
	node* r=T.get_root();
	
	cout<<"\nSorting using In-order traversal of AVL tree : \n";
	T.InOrderTraversal(r);              // In order traversal of the AVL tree prints the array elements in sorted order
	cout<<endl<<endl;
	T.printTree();                      // Printing the AVL tree T
	cout<<endl;
	
	return 0;
}
