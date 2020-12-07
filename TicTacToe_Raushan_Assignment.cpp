/** NAME: Raushan Sharma
    ROLL: 18MA20058       
	ASSIGNMENT:	A tic-tac-toe player that never loses, and wins whenever possible  **/

#include<iostream>
using namespace std;

char grid[3][3];       // The Tic-Tac-Toe grid (It stores * i.e. stars for blank places )

int safe_move(int p)   // This function checks if there is any row or column or diagonal where user has occupied 2 blocks and the third block is empty
{                      // If this occurs, then computer will put its move in that blank, so as to ensure user doesn't win in next move
	char ch1,ch2;
	if(p==1)
	  { ch1='X'; ch2='O'; }
	else
	  { ch1='O'; ch2='X'; }
	int count1_row[3]={0},count2_row[3]={0},count1_col[3]={0},count2_col[3]={0},count1_dia[2]={0},count2_dia[2]={0};
	int i,j;          // count1's store the count of ch1 (X or O) in a row or column or diagonal, whereas count2's store the count of blank places
	
	for(i=0;i<3;i++)
	  {
	  	for(j=0;j<3;j++)
	  	 {
	  	   if(j==i)
	  	     {
	  	     	if(grid[i][j]=='*')
	  	     	  count2_dia[0]++;
	  	     	else if(grid[i][j]==ch1)
	  	     	  count1_dia[0]++;
			 }
		   if(j+i==2)
		     {
		     	if(grid[i][j]=='*')
	  	     	  count2_dia[1]++;
	  	     	else if(grid[i][j]==ch1)
	  	     	  count1_dia[1]++;	
			 }
	  	   if(grid[i][j]=='*')
			 {
			 	count2_row[i]++;
			 	count2_col[j]++;
			 }	
		   else if(grid[i][j]==ch1)
		     {
		     	count1_row[i]++;
				count1_col[j]++;	
			 } 
		 }
	  }
	  
	if(count1_dia[0]==2 && count2_dia[0]==1)
	  {
	  	for(j=0;j<3;j++)
	  	  {
	  	  	if(grid[j][j]=='*')
		      {
		      	grid[j][j]=ch2;
		      	return (4*j+1);
			  }	
		  }
	  }
	
	if(count1_dia[1]==2 && count2_dia[1]==1)
	  {
	  	for(j=0;j<3;j++)
	  	  {
	  	  	if(grid[j][2-j]=='*')
		      {
		      	grid[j][2-j]=ch2;
		      	return (2*j+3);
			  }	
		  }
	  }   
	
	for(i=0;i<3;i++)
	  {
	  	if(count1_row[i]==2 && count2_row[i]==1)  // If in any row/column/diagonal, there are 2 user occupied blocks and 1 blank, then putting computer's move in the blank 
	  	  {
	  	  	for(j=0;j<3;j++)
	  	  	  {
	  	  	  	if(grid[i][j]=='*')
	  	  	  	  {
	  	  	  	  	grid[i][j]=ch2;
	  	  	  	  	return (3*i+j+1);
				  }
			  }
		  }
	  	if(count1_col[i]==2 && count2_col[i]==1)
	  	  {
	  	  	for(j=0;j<3;j++)
	  	  	  {
	  	  	  	if(grid[j][i]=='*')
	  	  	  	  {
	  	  	  	  	grid[j][i]=ch2;
	  	  	  	  	return (3*j+i+1);
				  }
			  }
		  }
	  }
	
	return 0;	
}

int win_possible(int p)    // This function checks if there is any row or column or diagonal where computer has occupied 2 blocks and the third block is empty
{                          // If this occurs, then computer will put its move in that blank, so as to ensure its win in next move
	char ch;
	if(p==1)
	  ch='O';
	else
	  ch='X';
	int count1_row[3]={0},count2_row[3]={0},count1_col[3]={0},count2_col[3]={0},count1_dia[2]={0},count2_dia[2]={0};
	int i,j;               // count1's store the count of ch1 (X or O) in a row or column or diagonal, whereas count2's store the count of blank places
	for(i=0;i<3;i++)
	  {
	  	for(j=0;j<3;j++)
	  	 {
	  	   if(j==i)
	  	     {
	  	     	if(grid[i][j]=='*')
	  	     	  count2_dia[0]++;
	  	     	else if(grid[i][j]==ch)
	  	     	  count1_dia[0]++;
			 }
		   if(j+i==2)
		     {
		     	if(grid[i][j]=='*')
	  	     	  count2_dia[1]++;
	  	     	else if(grid[i][j]==ch)
	  	     	  count1_dia[1]++;	
			 }
	  	   if(grid[i][j]=='*')
			 {
			 	count2_row[i]++;
			 	count2_col[j]++;
			 }	
		   else if(grid[i][j]==ch)
		     {
		     	count1_row[i]++;
				count1_col[j]++;	
			 } 
		 }
	  }

	if(count1_dia[0]==2 && count2_dia[0]==1)
	  {
	  	for(j=0;j<3;j++)
	  	  {
	  	  	if(grid[j][j]=='*')
		      {
		      	grid[j][j]=ch;
		      	return (4*j+1);
			  }	
		  }
	  }
	
	if(count1_dia[1]==2 && count2_dia[1]==1)
	  {
	  	for(j=0;j<3;j++)
	  	  {
	  	  	if(grid[j][2-j]=='*')
		      {
		      	grid[j][2-j]=ch;
		      	return (2*j+3);
			  }	
		  }
	  }   
	
	for(i=0;i<3;i++)
	  {
	  	if(count1_row[i]==2 && count2_row[i]==1)  // If in any row/column/diagonal, there are 2 comp occupied blocks and 1 blank, then comp moves in the blank and wins
	  	  {
	  	  	for(j=0;j<3;j++)
	  	  	  {
	  	  	  	if(grid[i][j]=='*')
	  	  	  	  {
	  	  	  	  	grid[i][j]=ch;
	  	  	  	  	return (3*i+j+1);
				  }
			  }
		  }
	  	if(count1_col[i]==2 && count2_col[i]==1)
	  	  {
	  	  	for(j=0;j<3;j++)
	  	  	  {
	  	  	  	if(grid[j][i]=='*')
	  	  	  	  {
	  	  	  	  	grid[j][i]=ch;
	  	  	  	  	return (3*j+i+1);
				  }
			  }
		  }
	  }
	
	return 0;
}

void printgrid()   // Function to display the Tic-Tac-Toe grid
{
	int i,j;
	cout<<endl<<endl;
	for(i=0;i<6;i++)
	  {
	  	if(i%2==0)
	  	  {
	  	  	cout<<"\t";
	  	    for(j=0;j<3;j++)
	  	     {
	  	  	   if(grid[i/2][j]!='*')
	  	  	      {
	  	  	      	if(j<2)
	  	  	      	  cout<<" "<<grid[i/2][j]<<" |";
	  	  	      	else
	  	  	      	  cout<<" "<<grid[i/2][j]<<" ";
				  }
	  	  	   else
	  	  	      {
	  	  	      	if(j<2)
	  	  	      	  cout<<" "<<" "<<" |";
	  	  	      	else
	  	  	      	  cout<<" "<<" "<<" ";
				  }
		     }
		  }
	  	else if(i%2==1 && i<5)
		   cout<<"\n\t-----------\n";
	  }
	cout<<endl<<endl;
}

void Current_state()              // Function to display the current state of the grid after every move in the game
{
	cout<<"\nCurrent state of the grid :\n";
    printgrid();	
}

void Computer_move(int p,int t)   // Function to display where Computer puts its move
{
	if(p==1)
	  { cout<<"Computer puts a O at position "<<t<<"\n";
	    Current_state();
	  }
	else
	  { cout<<"Computer puts a X at position "<<t<<"\n";
	    Current_state();
	  }	
}


void input(int player)            // Function to take input from the user for its next move
{
	int pos,x,y;
	
	if(player==1)
	  {
	  	cout<<"Enter the position where you want to put your next X : ";
      	cin>>pos;
      	x=(pos-1)/3; y=(pos-1)%3;   // Converting to coordinates in the grid from the position entered as a number between 1 to 9
      	if(grid[x][y]=='*')
      	  grid[x][y]='X';
      	else if(grid[x][y]!='*')   // Checking for validity of the user's input
      	  {
      	  	cout<<"\nInvalid input!! Please put a X on a blank position!!  Try again...\n\n";
      	  	input(1);
		  }
	  }
	
	else if(player==2)
	  {
	  	cout<<"Enter the position where you want to put your next O : ";
      	cin>>pos;
      	x=(pos-1)/3; y=(pos-1)%3;
      	if(grid[x][y]=='*')
      	  grid[x][y]='O';
      	else if(grid[x][y]!='*')   // Checking for validity of user's input
      	  {
      	  	cout<<"\nInvalid input!! Please put a O on a blank position!!Try again...\n\n";
      	  	input(2);
		  }
	  }
}

int any_move(int p)   // When computer is not going to lose wherever it puts its next move, this function selects the first blank block and comp moves there
{
	int x,y,i,j,t;
	char ch;
	if(p==1) ch='O';
	else ch='X';
	
	for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	    if(grid[i][j]=='*')
	      { grid[i][j]=ch;
	        return (3*i+j+1);
		  }
}

void p1Move8()                         // Function for the 8th move by computer when user is Player 1
{
	int t;                             // The 8th move is the last move for the computer when user plays first
	t=win_possible(1);                 // Either computer wins in this move
	if(t!=0)
	  { cout<<"Computer puts a O at position "<<t<<"\n";   // Move 8 by computer 
		Current_state();
		cout<<"\nComputer Wins!!!\n\n";
	  }
	else if(t==0)                       // Or if computer can't win in this move
	  {
	  	t=safe_move(1);                // Then check if computer can stop user from winning by giving a safe move()
	  	if(t!=0)
	  	  {
	  	  	cout<<"Computer puts a O at position "<<t<<"\n";   // Move 8 by computer 
		    Current_state();
		    input(1);                 // Move 9 by user
		    Current_state();
		    cout<<"\nMatch Drawn!!!\n\n";
		  }
		else                          // If none of the above cases hold, then giving anywhere in blank block would result in a draw
	     { t=any_move(1);
		   cout<<"Computer puts a O at position "<<t<<"\n";   // Move 8 by computer 
		   Current_state();
		   input(1);                  // Move 9 by user
		   Current_state();
		   cout<<"\nMatch Drawn!!!\n\n";
	     }	
	  }
}

void p2Move9()               // Function for the 9th move by computer when user is Player 2
{
	int t;                  // The 9th move is the last move for the computer when user plays second
	t=win_possible(2);      // Either computer wins in this move
	if(t!=0)
	  { cout<<"Computer puts a X at position "<<t<<"\n";  // Move 9 by computer
		Current_state();
		cout<<"\nComputer Wins!!!\n\n";
	  }
	else                    // Or, if computer can't win in this move, then giving in blank block would result in a draw
	  { t=any_move(2);
		cout<<"Computer puts a X at position "<<t<<"\n";
		Current_state();
		cout<<"\nMatch Drawn!!!\n\n";
	  }	
}

void p1case1_strategy()    // Strategy when user is player 1 and doesn't give its first move in centre, then computer starts with O in centre
{
	int x,y,t;
	grid[1][1]='O';       // Move 2 by computer
    Computer_move(1,5);
		     
	input(1);             // Move 3 by user
    Current_state();
      	     
    t=safe_move(1);
    if(t!=0)
      {
      	cout<<"Computer puts a O at position "<<t<<"\n";   // Move 4 by computer 
		Current_state();
	  }
	else if(t==0)
	  {
		if(grid[1][0]==grid[0][1] && grid[1][0]=='X')
		  { grid[0][0]='O'; x=0; y=0;
		  }
		else if(grid[1][0]==grid[2][1] && grid[1][0]=='X')
		  { grid[2][0]='O'; x=2; y=0;
		  }
		else if(grid[2][1]==grid[1][2] && grid[2][1]=='X')
		  { grid[2][2]='O'; x=2; y=2;
		  }
		else if(grid[1][2]==grid[0][1] && grid[1][2]=='X')
		  { grid[0][2]='O'; x=0; y=2;
		  } 
		else if(grid[0][0]==grid[2][2] && grid[0][0]=='X')
		  { grid[1][0]='O'; x=1; y=0;
		  }
		else if(grid[0][2]==grid[2][0] && grid[0][2]=='X')
		  { grid[1][0]='O'; x=1; y=0;
		  }
		else if(grid[0][1]=='*' && grid[0][0]==grid[0][2])
		  { grid[0][1]='O'; x=0; y=1;
		  }
		else if(grid[1][0]=='*' && grid[0][0]==grid[2][0])
		  { grid[1][0]='O'; x=1; y=0;
		  }
		else if(grid[2][1]=='*' && grid[2][0]==grid[2][2])
		  { grid[2][1]='O'; x=2; y=1;
		  }
		else if(grid[1][2]=='*' && grid[2][2]==grid[0][2])
		  { grid[1][2]='O'; x=1; y=2;
		  }
				 
		Computer_move(1,3*x+y+1);    // Move 4 by computer			 
	  }
	  
	input(1);                        // Move 5 by user
	Current_state();
			 
	t=win_possible(1);               // If user plays 1st, then from 6th move of computer, just check if a win is possible 
	if(t!=0)
	  { Computer_move(1,t);          // Move 6 by computer
		cout<<"\nComputer Wins!!!\n\n";
	  }
	else if(t==0)
	  { t=safe_move(1);              // Or, check for a safe move (i.e. defend user's chance to win)
		if(t!=0)
		  Computer_move(1,t);        // Move 6 by computer
		else if(t==0)
		  { t=any_move(1);          // Or else, move anywhere, computer won't lose
			Computer_move(1,t);     // Move 6 by computer
		  }
		input(1);                   // Move 7 by user
		Current_state();
			 
		p1Move8();
	  }
}

void p1case2_strategy()             // Strategy when user is player 1 and gives its first move in centre, then computer starts with O in a corner
{
	int x,y,t;
	grid[0][0]='O';                 // Move 2 by computer
	cout<<"Computer puts a O at position "<<1<<"\n";
	Current_state();
		     
	input(1);                       // Move 3 by user
    Current_state();
      	     
    t=safe_move(1);
    if(t!=0)     
      {
      	cout<<"Computer puts a O at position "<<t<<"\n";   // Move 4 by computer 
		Current_state();
			     
		input(1);                     // Move 5 by user
		Current_state();
			     
		t=win_possible(1);            // If user plays 1st, then from 6th move of computer, just check if a win is possible
	    if(t!=0)
		  { Computer_move(1,t);       // Move 6 by computer
			cout<<"\nComputer Wins!!!\n\n";
		  }
		else if(t==0)
		  { t=safe_move(1);           // Or, check for a safe move (i.e. defend user's chance to win)
			if(t!=0)
			  Computer_move(1,t);     // Move 6 by computer
			else if(t==0)
			  { t=any_move(1);        // Or else, move anywhere, computer won't lose
			    Computer_move(1,t);   // Move 6 by computer
			  }
			input(1);                 // Move 7 by user
			Current_state();
			 
			p1Move8();
		  }	     
	  }
	  
	else if(t==0)    
	  {
		grid[0][2]='O';
		cout<<"Computer puts a O at position "<<3<<"\n";   // Move 4 by computer 
		Current_state();
			     
		input(1);                     // Move 5 by user
		Current_state();
		
		t=win_possible(1);
	    if(t!=0)
		  { Computer_move(1,t);       // Move 6 by computer
			cout<<"\nComputer Wins!!!\n\n";
		  }
		else if(t==0)
		  { t=safe_move(1);
			if(t!=0)
			  Computer_move(1,t);     // Move 6 by computer
			else if(t==0)
			  { t=any_move(1);
			    Computer_move(1,t);   // Move 6 by computer
			  }
			input(1);                // Move 7 by user
			Current_state();
			 
			p1Move8();
		  }	     
	  }	
}

void p2case1_strategy()          // Strategy when user is player 2 and gives its first move in centre
{
	int x,y,t;
	
	x=0;y=0;
	grid[x][y]='X';
	Computer_move(2,3*x+y+1);    // Move 3 by computer on opposite corner
	input(2);                    // Move 4 by user
	Current_state();
		     
	if(grid[0][2]=='O' || grid[2][0]=='O')  // In this case computer would win
	  {
		if(grid[0][2]=='*')
		  {
		    grid[0][2]='X';                // Move 5 by computer
		    Computer_move(2,3);
		    input(2);                      // Move 6 by user
		    Current_state();
					 
			t=win_possible(2);
			Computer_move(2,t);            // Move 7 by computer
			cout<<"\nComputer Wins!!!\n\n";
		  }
				   
		else if(grid[2][0]=='*')
		  {
			grid[2][0]='X';                // Move 5 by computer
			Computer_move(2,7);
		    input(2);                      // Move 6 by user
		    Current_state();
					 
			t=win_possible(2);
			Computer_move(2,t);            // Move 7 by computer
			cout<<"\nComputer Wins!!!\n\n";
		  }
	  }
			 
	else if(grid[0][2]=='*' && grid[2][0]=='*')  
	  {
		t=safe_move(2);
		if(t!=0)
		  { Computer_move(2,t);            // Move 5 by computer in this case
		  }
		input(2);                          // Move 6 by user
		Current_state();
		         
		t=win_possible(2);
		if(t!=0)
		  { Computer_move(2,t);            // Move 7 by computer 
			cout<<"\nComputer Wins!!!\n\n";
		  }
		else if(t==0)
		  {
			t=safe_move(2);
			Computer_move(2,t);           // Move 7 by computer
			input(2);                     // Move 8 by user
		    Current_state();
		    p2Move9();
		  }	
	  }
}

void p2case2_strategy()          // Strategy if user doesn't give O in the middle and computer plays first
{
	int x,y,t;
	
	if(grid[0][0]=='*')
	  { x=0;y=0; }
	else if(grid[0][2]=='*')
	  { x=0;y=2; }
	  
	grid[x][y]='X';
	Computer_move(2,3*x+y+1);    // Move 3 by computer on another corner
	input(2);                    // Move 4 by user
	Current_state();
			 
	t=win_possible(2);
	if(t!=0)
	  { Computer_move(2,t);      // Move 5 by computer
		cout<<"\nComputer Wins!!!\n\n";
	  }
			   
	else if(grid[0][0]=='X' && grid[1][1]=='O')  // In this case just put X where O can't complete its win
	  { t=safe_move(2);
		if(t!=0)
		  { Computer_move(2,t);                 // Move 5 by computer in this case
		  }
				 
		input(2);                               // Move 6 by user
		Current_state();
		
		t=win_possible(2);                      // If user plays 2nd, then from 7th move of computer, just check if a win is possible
	    if(t!=0)
		  { Computer_move(2,t);                 // Move 7 by computer
			cout<<"\nComputer Wins!!!\n\n";
		  }
		else if(t==0)
		  { t=safe_move(2);                     // Or, check for a safe move (i.e. defend user's chance to win)
			if(t!=0)
			  Computer_move(2,t);               // Move 7 by computer
			else if(t==0)
			  { t=any_move(2);                  // Or else, move anywhere, computer won't lose
			    Computer_move(2,t);             // Move 7 by computer
			  }
			input(2);                           // Move 8 by user
			Current_state();
			 
			p2Move9();
		  }		   
	  }
			   
	else if(grid[0][2]=='X' && grid[1][2]=='O')
	  {
		grid[2][0]='X';    // Move 5 by computer in this case
		Computer_move(2,7);
		input(2);   // Move 6 by user
		Current_state();
				 
		t=win_possible(2);
		if(t!=0)
		  {
		    cout<<"Computer puts a X at position "<<t<<"\n";    // Move 7 by computer 
			Current_state();
			cout<<"\nComputer Wins!!!\n\n";
		  }
	  }	
}

int main()
{
	int i,j,p,pos,x,y,t;    // p stores the player number of the user, pos stores the input position of the user, and x,y stores its corresponding coordinates
	char ch;                // character for asking whether or not to continue the game
	
	for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	    grid[i][j]='*';    // Initializing the grid to all *'s ( stars can be thought of as blanks ) 
    
    cout<<"Welcome to the game of Tic-Tac-Toe !!!\n";
    
    do{
    	
    cout<<"\nWhich player do you want to be? \nFor Player 1, enter 1 and for Player 2, enter 2 : ";
    cin>>p;
    cout<<endl;
    
    for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	    grid[i][j]='*';
    
    if(p==1)              // User plays first ( User plays with X and computer with O )
      {
      	 cout<<"\nInitial state of the grid :\n";
      	 printgrid();
      	 
      	 cout<<"Enter the position where you want to put your first X : ";
      	 cin>>pos;
      	 x=(pos-1)/3; y=(pos-1)%3;
      	 grid[x][y]='X';                // Move 1 by user
      	 Current_state();
      	 
      	 if(grid[1][1]=='*')            // User starts with a X not in the centre block
      	   {
      	   	 p1case1_strategy();
		   }
		   
		 else if(grid[1][1]=='X')       // User starts with a X in the centre block
		   {
		   	 p1case2_strategy();
		   }
      	 
	  }
	  
    else if(p==2)                      // Computer plays first (User plays with O and computer with X )
      {
      	 grid[2][2]='X';
      	 Computer_move(2,9);           // Move 1 by Computer at a corner
      	 input(2);                     // Move 2 by user
      	 Current_state();
      	 
      	 if(grid[1][1]=='O')           // If user gives O in the centre
      	   {
      	   	 p2case1_strategy();
		   }
		 else                          // If user doesn't give O in the centre
		   {
		   	 p2case2_strategy();
		   }
	  }
	  
	cout<<"\n\nDo you want to play again?? (Press Y for yes/ N for no) :\n";
	cin>>ch;
	
    }while(ch=='Y' || ch=='y');
    
	return 0;
}
