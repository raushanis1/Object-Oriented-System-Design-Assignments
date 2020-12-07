/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/
    
/* In this program I had tried to implement the Seidel's Algorithm for Polygon Triangulation. 
   Seidel's Algorithm basically works in three steps :
   1. Decompose the Polygon into Trapezoids             ----> O(nlog*n) expected time [this is defined below]        
   2. Decompose the Trapezoids into Monotone Polygons   ----> O(n) time
   3. Triangulate the Monotone Polygons                 ----> O(n) time
   
   However, I faced difficulty while trying to implement the whole algorithm, but I have implemented some useful classes for that.
   But finally I have fully implemented the Step 3, i.e. triangulation of Monotone Polygons which runs in O(n) time.
   Definition:: A polygon is called monotone with respect to a straight line L, if every line orthogonal to L intersects the polygon at most twice 
   Here is the description of the whole Seidel algorithm, and also the part of triangulation of monotone polygons :
   
   ---------------------------------------------------------- ALGORITHM --------------------------------------------------------------------------------
   The expected time of the Seidel algorithm is O(nlog*n) where log*n is iterated logarithm of n, which is the number of times the logarithm function 
   must be iteratively applied before the result log(log(log(..))) is less than or equal to 1
   Randomized algorithm is used to create the trapezoidal decomposition of the X-Y plane arising due the segments (sides) of the polygon by taking a 
   random ordering of the segments of polygon and adding one segment at a time to incrementally construct the trapezoids
   
   Then the trapezoids are decomposed into y-monotone polygons. A y-monotone polygon is a polygon whose boundary consists of two y-monotone chains 
   in the left and in the right. A y-monotone chain means a sequence of vertices where the y-coordinates increase or decrease monotonically. When 
   moving in clockwise direction, the right y-monotone chain has y-coordinates monotonically decreasing and the left y-monotone chain has y-coordinates 
   monotonically increasing. These y-monotone polygons are computed from the trapezoidal decomposition by checking whether the two vertices of the 
   original polygon lie on the same side
   
   Now, a monotone polygon can be triangulated in O(n) time by using a greedy algorithm which repeatedly cuts off the convex corners of the polygon. 
   This algorithm works as follows :
   1. Obtain a sorted list of vertices of the polygon, sorted in descending order of their y-coordinates. This can be done in O(n) time rather than 
      sorting all in O(nlogn) time because the two monotone chains are already sorted, we just need to merge them like the merge() function in merge 
	  sort, and this can be done in O(n) time. Suppose the vertices after sorting are v1,v2,...,vn
   2. Push v1 and v2 into a stack 
   3. for i=3 to n, for vertex vi, do : 
         if vi and top() of stack are in the same monotonic chain (either both in left chain or both in right chain), then add diagonals from vi 
		 to the vertices in the stack before top() of the stack and pop() the top() of stack after making every such diagonal. When no more diagonals 
		 are possible, then push vi into the stack. 
		 
		 otherwise, if vi and top() of stack are not in the same monotonic chain, save the value of the top of the stack as old_top, and add diagonals 
		 from vi to all the vertices on the stack. Then push vi and old_top into the stack.
	
	  In this step, in each iteration, atleast one diagonal is formed. There are total n vertices and so n - 3 diagonals should be formed, after which 
	  we break from the loop. Hence this step takes O(n) time.
	  
   --------------------------------------------------------- xxxxxxxxxx --------------------------------------------------------------------------------  
*/   

#include <iostream>
#include <math.h>
using namespace std;

int n;                     // n is the number of vertices (or sides) of the polygon in the program

class Point
{
	public:
	    double x,y;        // We would access the coordinates and index of points throughout the program, hence these data members are made public in this class
		int idx;
		
		Point() : x(0),y(0)                  // No argument constructor         
		  { }
		
		Point(double a, double b):x(a),y(b)  // 2 argument constructor
          { }
         
        Point operator +(Point a)            // Overloading the + operator for calculating sum of two Point type objects
          {
          	return Point(x+a.x , y+a.y);
		  }
          
        Point operator -(Point a)            // Overloading the - operator for calculating difference between two Point type objects
          {
          	return Point(x-a.x , y-a.y);
		  }
    
        Point multiply_scalar(double c)      // function to scale (multiply) a point by a factor c
          {  return Point(c*x, c*y); }
    
        Point divide_scalar(double c)        // function to scale (divide) a point by a factor c
          {  return Point(x/c , y/c); }
		
		double cross_product(Point a)        // function to return the magnitude of cross product of the vectors OX and OA where O:origin
          {  return (x*a.y - y*a.x); }
    
        double dot_product(Point a)          // function to return the dot product of the vectors OX and OA where O:origin
          {  return (x*a.x + y*a.y); }
    
        double norm()                        // function to return the distance of the point from the origin O
          {  return sqrt(x*x + y*y); }
    
        Point normalize()                    // function to make norm of point (distance from origin) = 1, this is called normalization
          {
          	return Point(x/this->norm() , y/this->norm());
		  }
		
	    bool operator == (Point p)            // Overloading the comparison operator for comparing two Point type objects
		  {
		  	if(x==p.x && y==p.y)
		  	  return true;
		  	else
		  	  return false;
		  }

};

template <typename T> class vector    // Implementing class vector for storing vector of Points (in general, vector of data type T objects) further in the program
{
    T* arr;                           // pointer to store the address of the vector
    int capacity,current_size;        // capacity is the storage limit and current_size is the size of the vector currently
 
    public:
      vector()                        // No argument constructor
        {
          arr = new T[1];
          capacity = 1;
          current_size = 0;
        }
 
      void push_back(T data)                // Function to add an element at the end of the vector
        {
          if (current_size == capacity)     // If size capacity is reached, then double the capacity to store further elements
		    {
              T* temp = new T[2*capacity];
              for (int i=0; i<capacity; i++) 
			    {
                  temp[i]=arr[i];           // copying old array elements to new array
                }
              delete[] arr;                 // deleting previous array
              capacity *= 2;
              arr = temp;
            }
          arr[current_size] = data;         // Inserting data at the end of the vector
          current_size++;
        }
    
      T operator [](int index)              // Overloading the indexing operator to return the element at any index
        {
      	  if(index < current_size)
      	    return arr[index];
	    }

      void pop()                            // Function to delete last element
	    { current_size--; }
 
      int size()                            // Function to get the current size of the vector
	    { return current_size; }
 
};

double orient2d(Point pa, Point pb, Point pc)
{
	double acx,acy,bcx,bcy;
    acx = pa.x - pc.x;
    bcx = pb.x - pc.x;
    acy = pa.y - pc.y;
    bcy = pb.y - pc.y;
    return (acx*bcy - acy*bcx);
}

class Edge                            // Implementation of class Edge for the Seidel algorithm
{
    public:
        Point p, q, above, below;
        vector <Point> mpoints;
        double slope, c;              // slope is the slope of line, and c is the y-intercept
        
        Edge(Point a, Point b)
          {
            p=a; q=b;
            if(b.x-a.x == 0)
              slope = 0;
            else
              slope = (b.y - a.y)/(b.x - a.x);
            c = a.y - (a.x * slope);
            mpoints.push_back(a);
            mpoints.push_back(b);
          }

        bool is_above(Point a)
		  {
		  	if(orient2d(p,q,a) < 0)
		  	  return true;
		  	return false;
          }

        bool is_below(Point a)
		  {
		  	if(orient2d(p,q,a) > 0)
		  	  return true;
		  	return false;
          }

        void add_mpoints(Point a)
	      {
            for(int i=0;i<mpoints.size();i++)
              {
                if(mpoints[i]==a)
                  return;
              }
            mpoints.push_back(a);
          }
};

struct node 
{
    Point p;
	node* next;
};

class stack            // Implementating of class stack 
{
    public:
	    node *top;

	    stack() : top(NULL)         // No argument constructor to initialize top to NULL
		  {}

	    void push(Point p1)         // Function to perform push new element in stack
		  {
		    node* temp = new node;
		    temp->p = p1;
		    temp->next = top;
		    top = temp;
	      }

	    void pop()                  // Function to perform pop in stack
		  {
		    if(top==NULL) 
			  {
			    cout << "Underflow !!\n";
			    return;
		      }
		    top=top->next;
	      }
	    
	    bool is_empty()             // Function to check if stack is empty or not
	      {
	      	if(top==NULL)
	      	  return true;
	      	return false;
	      }
	    
	    Point top_point()           // Function to return the data (here, point) at the top of the stack
		  {
		    return top->p;
	      }
	    
};


bool is_convex(Point prev, Point p1, Point next, int chain)   // Function to check if a vertex p1 is a convex vertex or not (interior angle at p1 is less than 180 degrees)  
{
  	double pro;
    pro = prev.x*(next.y - p1.y) + p1.x*(prev.y - next.y) + next.x*(p1.y - prev.y);  // Using vector cross product, to check for convexity at a vertex p1
	if(chain==1)                    // chain=1 means the point is a part of the right monotone (from top vertex to bottom vertex in clockwise order) of the polygon
	  {
	  	if(pro>0)
	  	  return true;
	  	return false;
	  } 
	
    else                           // chain=2 means the point is a part of the left monotone (from bottom vertex to top vertex in clockwise order) of the polygon
	  {
	  	if(pro<0)
	  	  return true;
	  	return false;
	  } 
}
  
bool is_x_monotone(Point vertices[])   // Function to check whether a polygon is x-monotone or not
{
	int m=0, M=0,i,next_idx;
	bool flag = true;
	for(i=0;i<n;i++) 
	  {
		if(vertices[i].x < vertices[m].x)         // m stores the index of the left most vertex of the polygon, i.e. one with least x coordinate
		  m=i;
		else if (vertices[i].x > vertices[M].x)   // M stores the index of the right most vertex of the polygon, i.e. one with largest x coordinate
		  M=i;	  
	  }
	  
	i = m;
	while(i!=M)                  // Moving clockwise from the leftmost to the rightmost vertex once (moving in upper half vertices)
	  {
		next_idx=(i+1)%n;
		if(vertices[next_idx].x < vertices[i].x) 
		  {
			flag=false;
			break;
		  }
		i=(i+1)%n;          // Moving to the next vertex in next loop. Indices of the vertices are calculated modulo n, as nth vertex is again adjacent to 1st vertex
	  }
	  
	while(i!=m)                 // Now moving clockwise again from the rightmost vertex to the leftmost vertex once (moving in lower half vertices)
	  {
		next_idx=(i+1)%n;
		if(vertices[next_idx].x > vertices[i].x) 
		  {
			flag=false;
			break;
		  }
		i=(i+1)%n;          // Moving to the next vertex in next loop. Indices of the vertices are calculated modulo n, as nth vertex is again adjacent to 1st vertex
	  }
	  
	return flag;
}  
  
bool is_y_monotone(Point vertices[])    // Function to check whether a polygon is y-monotone or not
{
	int m=0, M=0,i,next_idx;
	bool flag = true;
	for(i=0;i<n;i++) 
	  {
		if(vertices[i].y < vertices[m].y)    // m stores the index of the bottom most vertex of the polygon, i.e. one with least y-coordinate
		  m=i;
		  
		if(vertices[i].y > vertices[M].y)    // M stores the index of the top most vertex of the polygon, i.e one with largest y-coordinate
		  M=i;	  
	  }

	i = m;
	while(i!=M)                              // Moving clockwise from the bottom most to the top most vertex once (moving in left half vertices)
	  {
		next_idx=(i+1)%n;
		if(vertices[next_idx].y < vertices[i].y) 
		  {
			flag=false;
			break;
		  }
		i=(i+1)%n;         // Moving to the next vertex in next loop. Indices of the vertices are calculated modulo n, as nth vertex is again adjacent to 1st vertex
	  }
	  
	while(i!=m)                             // Now moving clockwise again from the top most vertex to the bottom most vertex once (moving in right half vertices)
	  {
		next_idx=(i+1)%n;
		if(vertices[next_idx].y > vertices[i].y) 
		  {
			flag=false;
			break;
		  }
		i=(i+1)%n;         // Moving to the next vertex in next loop. Indices of the vertices are calculated modulo n, as nth vertex is again adjacent to 1st vertex
	  }
	  
	return flag;
} 

void check_monotone(Point vertices[])    // If polygon is not y-monotone, but is x-monotone, then by transformation, form a new y-monotone polygon and triangulate that
{
	int i,t;
	if(is_x_monotone(vertices) && !is_y_monotone(vertices)) 
	  {
		for(i=0;i<n;i++) 
		  {
			t=vertices[i].x;
			vertices[i].x = (-1)*vertices[i].y;   // If original x-monotone but non-y-monotone polygon has vertices (x,y) then the new polygon has vertices (-y,x) 
			vertices[i].y = t;
		  }
	  }
}

void Triangulate(Point vertices[])      // Function for performing Polygon Triangulation for the y-monotone polygon (or y-monotone after conversion)
{
	Point new_points[n];                // The new_points will store vertices sorted in decreasing order of the y-coordinates
	int chain[n];                       // chain[] array stores whether any vertex in polygon is in the right chain (i.e. chain=1) or the left chain (i.e. chain=2)
	int m=0,M=0,i;                      // chain is a sequence of points whose y-coordinates are monotonic (increasing if in left chain, and decreasing if in right chain)
	Point chain1[n], chain2[n];         // chain1[] contains the vertices in chain=1 (i.e. right chain) and chain2[] contains vertices in chain=2 (i.e. left chain) 
	stack s;       
	
	for(i=0;i<n;i++) 
	  {
	  	if(vertices[i].y < vertices[m].y) 
		  m=i;	                           // m stores the index of the bottom most vertex of the polygon, i.e. one with least y-coordinate
		  
		if(vertices[i].y > vertices[M].y) 
		  M=i;                             // M stores the index of the top most vertex of the polygon, i.e one with largest y-coordinate
	  }

	int size1=0,size2=0;                   // size1 stores the number of vertices in chain1 and size2 stores the number of vertices in chain2
	i=M;
	do{	
		chain1[size1++] = vertices[i];
		chain[vertices[i].idx] = 1;        // Mark the right chain vertices as 1 in chain[] array
		i=(i+1)%n;
	  }while(i!=(m+1)%n);
	
	i=(M+n-1)%n;
	while(i!=m)
	  {
	  	chain2[size2++]=vertices[i];
	  	chain[vertices[i].idx]=2;          // Mark the left chain vertices as 2 in chain[] array
	  	i=(i+n-1)%n;
	  }
	  
	int s1= 0,s2=0,index=0;
	while(s1!=size1 && s2!=size2)          // Merging chain1[] and chain2[] points to make sorted order of vertices in new_points[] array
	  {                                    // Since chain1[] and chain2[] already have points sorted in some order (increasing or decreasing) according to their y coordinates
		if (chain1[s1].y > chain2[s2].y) 
		  new_points[index++] = chain1[s1++];
		  
		else 
		  new_points[index++] = chain2[s2++];
		  
	  }
	  
	while(s1!=size1) 
	  new_points[index++] = chain1[s1++];
	  
	  
	while(s2!=size2) 
	  new_points[index++] = chain2[s2++];  // now, new_points[] contain vertices sorted accordinf to y-coordinate         
	  
	s.push(new_points[0]);                      // push the first and second vertices into the stack
	s.push(new_points[1]);
	int count=0;                                // counts the number of diagonals formed while triangulation. This should ultimately become n-3
	for(i=2;i<n;i++) 
	{
	  if(s.top!=NULL && ((abs(new_points[i].idx - s.top_point().idx))%n == 1 || (abs(new_points[i].idx - s.top_point().idx))%n == n - 1)) 
		{                                       // if current vertex vi and s.top() are in the same monotonic chain (either both in left chain or both in right chain), then add
		  while(s.top->next!=NULL)              // diagonals from vi to the vertices in the stack before top() of the stack till possible (not possible when they are adjacent)
		    { 
			  Point top = s.top_point();
			  Point prev_top = ((s.top)->next)->p;
			  if(is_convex(prev_top, top, new_points[i], chain[new_points[i].idx])) 
			    {
				  cout<<"{"<<prev_top.idx<<", "<<new_points[i].idx<<"}\n";   // Print the indices of the points between which diagonals are drawn to triangulate the polygon
				  count++;
				  if(count==n-3)                // If number of diagonals has reached (n-3), then no need to form any more diagonals. So break
				    break;
				  s.pop();
				}
				
			  else 
				break;	
			}
		  
		  s.push(new_points[i]);                // When no more diagonals are possible, then push vi into the stack
		}
		
	  else                                      // when vi is not in the same chain as the vertex on the top of the stack
	    {
		  Point old_top;
		  node *o_top = NULL;
		  if(s.top != NULL) 
		    {
		       old_top=s.top_point(); 
			   o_top = s.top;	
			}
			
		  while (s.top != NULL) 
		    {
			  int top_idx = s.top_point().idx;
			  s.pop();                          // form diagonals from the current vertex to every vertex on the stack, except to adjacent vertices
			  if ((abs(top_idx - new_points[i].idx))%n != 1 && (abs(top_idx - new_points[i].idx))%n != n - 1) 
			    {
				  cout<<"{"<<new_points[i].idx<<", "<<top_idx<<"}\n";    // Print the indices of the points between which diagonals are drawn to triangulate the polygon
				  count++;
				  if (count==n-3)               // If number of diagonals has reached (n-3), then no need to form any more diagonals. So break
				    break;  
				}
			}
			
		  if (o_top != NULL) s.push(old_top);
			s.push(new_points[i]);
		}
		
	  if (count==n-3)                           // If number of diagonals has reached (n-3), then no need to form any more diagonals. So break
		break;
		
	}
} 

  
int main() 
{
	int i,t;
	n=9;                                        // n is the number of sides of the polygon
	Point vertices[n];
	double points[n][2]={{4,4},{5,7},{6,4},{8,5},{9,4},{10,6},{9,2},{5,2},{3,3}};   // Initializing the vertices of the polygon in clockwise order
	cout<<"\nCoordinates of the vertices of the Simple Polygon in Clockwise order are :\n\n";
	for(i=0;i<n;i++) 
	  {
	  	cout<<"("<<points[i][0]<<","<<points[i][1]<<")"<<endl;
		vertices[i].x=points[i][0];
		vertices[i].y=points[i][1];
		vertices[i].idx=i;
	  }
	check_monotone(vertices);
	
	cout<<"\nTriangulating this Polygon by putting diagonal between vertices with following indices :\n\n";
	Triangulate(vertices);
	cout << endl;

	return 0;
}  
 
