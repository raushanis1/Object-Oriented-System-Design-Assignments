/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/
    
/* Implementation of Ear Clipping Algorithm in O(n^2) :
   
   An ear of a polygon is a vertex v[i], at which the interior angle of polygon is less than 180 degrees
   and the line segment joining v[i-1] and v[i+1] (adjacent vertices) lies completely inside the polygon,  
   and no other vertex of the polygon lies inside the triangle formed by the vertices v[i-1], v[i], v[i+1] 
   
   The Two Ears Theorem in geometry states that every simple polygon with more than three vertices has at least two non-overlapping ears, 
   and ears are vertices that can be removed from the polygon without introducing any crossings or overlapping diagonals
   
   ---------------------------------------------------------- ALGORITHM --------------------------------------------------------------------------
   We construct an array of ear vertices of the polygon using the is_ear() function which checks if a vertex is an ear vertex or not in O(n) time
   since it calls the no_point_inside() function to check if no other vertex of the polygon is inside the triangle formed at the ear vertex, and
   this no_point_inside() function itself runs in O(n) time. 
   
   Now, for making the ears[] array of ear vertices of the polygon, we check for each of the n vertices if it is an ear or not, hence this takes 
   O(n*n) = O(n^2) time.
   
   Then, we keep on clipping an ear vertex, drawing diagonals between the previous and next of the ear vertices, and making the size of polygon
   shorter by 1 in each iteration. This takes O(1) time. Also, after each iteration we maintain the ears[] array, for which we just need to check 
   if we need to add/delete the previous and next of the ear removed from the array or not, as rest of the polygon remains unchanged.
   
   We repeat this process until the size of the polygon becomes 3, i.e. the last ear vartex is reached
   --------------------------------------------------------- xxxxxxxxxx ---------------------------------------------------------------------------
*/
    
#include<iostream>
#include<math.h>
using namespace std;

double ERR = 0.000000001;  // Amount of permissible error while comparing two floating point numbers in this program [ This is used in is_inside() function ]

class Point
{
	public:
		double x,y;        // We would access the coordinates and index of points throughout the program, hence these data members are made public in this class
		int idx;
		
		bool operator == (Point p)    // Overloading the comparison operator for comparing two Point type objects
		  {
		  	if(x==p.x && y==p.y)
		  	  return true;
		  	else
		  	  return false;
		  }	
};

class Polygon
{
	private:
	    Point* vertices;               // Pointer to vertices of any object of Polygon class
		int size;                      // size is the No. of sides of the polygon 
		
	protected:
	    double Triangle_Area(Point a, Point b, Point c)      // Function to find area of a triangle (This is a helper function for other functions)
		  {
		  	return fabs((a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y))/2.0);    // Area of triangle with vertices a,b,c
		  }	
        
        bool is_inside(Point p, Point a, Point b, Point c)   // Function to check if a point p is inside the triangle formed by points a,b and c or not
          {
          	double area, area1, area2, area3;
            area  = Triangle_Area(a,b,c);                    // area = Area of ABC, area1 = Area of PAB, area2 = Area of PBC, area3 = Area of PCA
            area1 = Triangle_Area(p,a,b);                    
            area2 = Triangle_Area(p,b,c);                    // If P lies inside the triangle ABC, then we should have: area = area1 + area2 + area3
            area3 = Triangle_Area(p,c,a);                    // Otherwise, if P is outside triangle ABC, area1 + area2 + area3 > area
            
            if(fabs(area - (area1+area2+area3)) < ERR)   // Since area,area1,area2,area3 are floating point variables, we can't check area == area1 + area2 + area3 directly
              return true;                               // So we take a permissible error of ERR while comparing area and (area1 + area2 + area3) 
            return false;
          }
        
        bool no_point_inside(Point a, Point b, Point c)  // Function to check if there are no vertices (other than a,b,c) of the polygon inside triangle ABC or not
          {
          	int i;
          	Point p;
            for(i=0;i<size;i++)
              {
                p = vertices[i];                         // Iterating through the vertices of the polygon
                if(p == a || p == b|| p == c)
                  continue;
                else if(is_inside(p,a,b,c))              // If the current point p is inside the triangle ABC, then return false
                  return false;
              }
            return true;                                 // Return true if no vertex is inside the triangle ABC
          }
        
        bool is_convex(Point prev, Point p, Point next)  // Function to check if a vertex p is a convex vertex (interior angle at p is less than 180 degrees) or not
          {
          	double pro;
          	pro = prev.x*(next.y - p.y) + p.x*(prev.y - next.y) + next.x*(p.y - prev.y);  // Using vector cross product, 
          	if(pro<0)                                                                     // checking if vertex point P is a convex point or not
          	  return true;
          	else
          	  return false;
          }
        
        bool is_ear(Point a, Point b, Point c)           // Function to check if the vertex b is an ear vertex or not. An ear has been defined in the beginning
          {
            if(is_convex(a,b,c) && no_point_inside(a,b,c) && Triangle_Area(a,b,c)>0)  // If b is a convex point, and no other vertex lies inside ABC, and A,B,C are non-collinear
              return true;                                                            // then return true, i.e. b is an ear vertex
            return false;                                                             // Otherwise, return false
          }
        
        
    public:
    	Polygon(int n, int sides[][2])                                   // Two-argument constructor, here n = no. of sides of the polygon
    	  {                                                              // This function takes the entered value of no. of sides and vertices of the polygon as input
    	  	int i;                                                       // and assigns them to the data members size and vertices of the polygon object
    	  	size=n;
    	  	vertices = new Point[size];
    	  	cout<<"\nCoordinates of the vertices of the Simple Polygon in Clockwise order are :\n\n";
    	  	for(i=0;i<n;i++)
    	  	  {
    	  	  	cout<<"("<<sides[i][0]<<","<<sides[i][1]<<")"<<endl;
    	  	  	vertices[n-1-i].x=sides[i][0];
    	  	  	vertices[n-1-i].y=sides[i][1];
    	  	  	vertices[n-1-i].idx=i;
		      }
		  }
		
		void Triangulate(int edges[][2]);
};

void Polygon::Triangulate(int edges[][2])           // Function for performing Polygon Triangulation using Ear clipping method
{
	Point ears[size];
    int i,j=0,k=0,x=0;
    for(i=0;i<size;i++)
      {
        Point prev = vertices[(i-1+size) % size];   // indices are modulo size, since the index previous to 0th index is (size-1)
        Point p = vertices[i];
        Point next = vertices[(i+1) % size];        // indices are modulo size, since the index next to (size-1)th index is 0 , which is size % size      

        if(is_ear(prev, p, next))                   // Storing the vertices that are ears in the array : ears[]
            ears[j++] = p;                          
      }
    
    while(k<j && size>3)                            // Ear clipping, till the last ear is reached (when size becomes 3 , i.e. only 3 vertices remain)
      {
        Point e = ears[k++];            
        int index=0;
        for(i=0;i<size;i++)
          {
            if(vertices[i]==e)
              {
                index = i;
                break;
              }
          }

        int prev_idx = (index-1+size) % size;        // indices are modulo size, since the index previous to 0th index is (size-1)
        Point prev_point = vertices[prev_idx];       // The vertex just before the ear vertex
           
        int next_idx = (index+1) % size;             // indices are modulo size, since the index next to (size-1)th index is 0 , which is size % size
        Point next_point = vertices[next_idx];       // The vertex just after the ear vertex

        for(i=index+1;i<size;i++)
          vertices[i-1]=vertices[i];                 // Removing the ear vertex and shifting other vertices
    
        size--;                                      // After removal of the ear, the size of the polygon reduces by 1 vertex

        edges[x][0]=prev_point.idx;                  // Drawing a diagonal between the previous and next vertices of the ear vertex
		edges[x][1]=next_point.idx;
        x++;

        int prev_prev_index = (prev_idx-1+size) % size;      // Index of the 2nd previous point to the ear vertex removed
        Point prev_prev_point = vertices[prev_prev_index];
        int next_next_index = (index+1) % size;              // Since the points after the ear got shifted by one index to the left, the index of the 2nd next 
        Point next_next_point = vertices[next_next_index];   // point after the ear vertex removed is (index+1)%size

        if(is_ear(prev_prev_point, prev_point, next_point))  // If the resulting polygon after the ear removal has prev_point as an ear vertex  
          {                                                  // i.e. prev_prev_point, prev_point and next_point forms an ear, then mark this as an ear vertex
            int flag=0;                                      
            for(i=k;i<j;i++)
              {
                if(ears[i]==prev_point)                      // if prev_point was already there in the ears[] array, being an ear vertex of the original polygon                      
                  {                                          // then mark flag = 1 and break
                    flag=1;                             
					break;
                  }
              }
                  
            if(flag==0)                                      // If flag is 0, that means prev_point was not an ear vertex of the original polygon, but is an ear
              {                                              // of this new polygon. So, add prev_point to the ears[] array
                ears[j++]=prev_point;
              }
          }
              
        else                                                 // If prev_point is not an ear vertex of the new polygon, then check if it was an ear of the parent polygon
          {                                                  // If it was an ear of the parent polygon, then remove it from the ears[] array 
            int flag=0;
            for(i=k;i<j;i++)
              {
                if(ears[i]==prev_point)
                  {
                    flag=i;
					break;
                  }
              }
                    
			if(flag!=0)
              {
                for(int i=flag+1;i<j;i++)
                  {
                    ears[i-1]=ears[i];                       // Shifting the ear vertices by one index to the left after removing prev_point from the ears[] array
                  }
                j--;                                         // Reducing the size of the ears[] array by 1
              }
          }

        if(is_ear(prev_point, next_point, next_next_point))  // If the resulting polygon after the ear removal has next_point as an ear vertex
          {                                                  // i.e. prev_point, next_point and next_next_point forms an ear, then mark this as an ear vertex
            int flag=0;
            for(int i=k;i<j;i++)
              {
                if(ears[i]==next_point)                      // if next_point was already there in the ears[] array, being an ear vertex of the original polygon
                  {                                          // then mark flag = 1 and break
                    flag=1;
					break;
                  }
              }
                    
			if(flag==0)                                      // If flag is 0, that means next_point was not an ear vertex of the original polygon, but is an ear
              {                                              // of this new polygon. So, add next_point to the ears[] array
                ears[j++]=next_point;
              }
          }
                
		else                                                 // If next_point is not an ear vertex of the new polygon, then check if it was an ear of the parent polygon
          {                                                  // If it was an ear of the parent polygon, then remove it from the ears[] array 
            int flag=0;
            for(i=k;i<j;i++)
              {
                if(next_point==ears[i])
                  {
                    flag=i;
					break;
                  }
              }
                    
			if(flag!=0)
              {
                for(i=flag+1;i<j;i++)
                  {
                    ears[i-1]=ears[i];                       // Shifting the ear vertices by one index to the left after removing next_point from the ears[] array
                  }
                j--;                                         // Reducing the size of the ears[] array by 1
              }
          }

      }
}

int main()
{
	int n,i,a,b;

	n=10;                                                             // n is the number of sides of the polygon
	int edges[n-3][2];
	int sides[n][2]={{5,8},{6,10},{7,8},{9,9},{12,8},{10,7},{10,5},{8,4},{6,5},{8,7}};  // Initializing the vertices of the polygon in clockwise order
	
	Polygon S(n,sides);
	cout<<"\nTriangulating this Polygon by putting diagonal between vertices with following indices :\n\n";
	S.Triangulate(edges);
	for(i=0;i<n-3;i++)
	  {
	  	a = (edges[i][0]<edges[i][1])? edges[i][0] : edges[i][1];
	  	b = (edges[i][0]<edges[i][1])? edges[i][1] : edges[i][0];
	  	cout<<"{ "<<a<<" , "<<b<<" }"<<endl;                          // Print the indices of the points between which diagonals are drawn to triangulate the polygon
	  }
	cout<<endl;
	return 0;
}
