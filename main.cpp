#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

//prints out the adjacency matrix with the names of each vertex along the edges
void print(char* vertices[20], int adjacency[20][20])
{
	for(int i = -1; i < 20; i++)
	{
		//for every line except the first, start the line with the name of the vertex
		if(i != -1)
		{
			if(vertices[i])
				cout << vertices[i] << "\t";
		}
		
		for(int j = 0; j < 20; j++)
		{
			//only put vertex names along the first line
			if(i == -1)
			{				
				if(vertices[j])
					cout << "\t" << vertices[j];
			}
			//put the edge weight in the main body of the table
			else
			{
				if(vertices[i] && vertices[j])
				{
					if(adjacency[i][j] != -1)
						cout << adjacency[i][j];
					else
						cout << "-";
					
					cout << "\t";
				}
			}
		}
		
		if(vertices[i])
			cout << endl;
	}
}

//add a vertex to the graph
void addVertex(char* vertices[20])
{
	//find the first spot in vertices that isn't empty
	int index = -1;
	while(vertices[++index]);
	
	//prompt the user for the name and add it
	cout << "Enter the name of the vertex you would like to add.\n";
	char* input = new char[15];
	cin >> input;
	vertices[index] = input;
}

//add an edge connecting vertices
void addEdge(char* vertices[20], int adjacency[20][20])
{
	char* first = new char[15];
	int firstInd = -1;
	char* second = new char[15];
	int secondInd = -1;
	int weight = -1;
	
	//prompt the user for the vertices
	cout << "Enter the name of the first vertex you want to connect.\n";
	cin >> first;
	cout << "Enter the name of the second vertex you want to connect.\n";
	cin >> second;
	
	//find the index of each vertex
	for(int i = 0; i < 20; i++)
	{
		if(vertices[i])
		{
			if(!strcmp(first, vertices[i]))
				firstInd = i;
			
			if(!strcmp(second, vertices[i]))
				secondInd = i;
		}
	}
	
	//prompt the user for the weight of the edge
	cout << "Enter the weight of the edge you want to make.\n";
	cin >> weight;
	
	//complain if something is wrong
	if(firstInd == -1 || secondInd == -1 || weight == -1)
	{
		cout << "Something went wrong.\n";
		return;
	}
	
	//add the edge to the matrix
	adjacency[firstInd][secondInd] = weight;
	adjacency[secondInd][firstInd] = weight;
}

//remove a vertex and delete everything it's connected to
void removeVertex(char* vertices[20], int adjacency[20][20])
{
	//prompt the user for the vertex to be removed
	cout << "Enter the name of the vertex you would like to remove.\n";
	char* input = new char[15];
	cin >> input;
	
	//go through the list of vertices to find it
	for(int i = 0; i < 20; i++)
	{
		if(vertices[i])
		{
			//if the vertex is found
			if(!strcmp(input, vertices[i]))
			{
				//delete it
				delete vertices[i];
				vertices[i] = NULL;
				
				//set all its edges to 0
				for(int j = 0; j < 20; j++)
				{
					adjacency[i][j] = -1;
					adjacency[j][i] = -1;
				}
				
				return;
			}
		}
	}
	
	//if it wasn't found, tell the user
	cout << "That vertex could not be found.\n";
}

//deletes an edge from the graph
void removeEdge(char* vertices[20], int adjacency[20][20])
{
	char* first = new char[15];
	int firstInd = -1;
	char* second = new char[15];
	int secondInd = -1;
	
	//prompt the user for the ends of the edge being deleted
	cout << "Enter the name of one end of the edge you want to delete.\n";
	cin >> first;
	cout << "Enter the name of the other end of the edge you want to delete.\n";
	cin >> second;
	
	//find the index of each vertex
	for(int i = 0; i < 20; i++)
	{
		if(vertices[i])
		{
			if(!strcmp(first, vertices[i]))
				firstInd = i;
			
			if(!strcmp(second, vertices[i]))
				secondInd = i;
		}
	}
	
	//complain if something is wrong
	if(firstInd == -1 || secondInd == -1 || adjacency[firstInd][secondInd] == -1)
	{
		cout << "Something doesn't exist here.\n";
		return;
	}
	
	//remove the edge from the matrix
	adjacency[firstInd][secondInd] = -1;
	adjacency[secondInd][firstInd] = -1;
}

void outputList(char* vertices[20], int prev[], int start, bool last = true)
{
	if(prev[start] != -1)
		outputList(vertices, prev, prev[start], false);
	
	if(vertices[start])
		cout << vertices[start];
	if(!last)
		cout << "->";
}

//find the shortest path between two nodes
void salesman(char* vertices[20], int adjacency[20][20])
{
	char* start = new char[15];
	int startInd = -1;
	char* end = new char[15];
	int endInd = -1;
	
	//prompt the user for the ends of the edge being deleted
	cout << "Enter the name of the vertex you want to start at.\n";
	cin >> start;
	cout << "Enter the name of the vertex you want to end at.\n";
	cin >> end;
	
	//I need the maximum existing index for other things so might as well use it in lots of places
	int maxIndex = 0;
	for(int i = 0; i < 20; i++)
	{
		if(vertices[i])
			maxIndex = i;
	}
	
	//find the index of each vertex
	for(int i = 0; i <= maxIndex; i++)
	{
		if(vertices[i])
		{
			if(!strcmp(start, vertices[i]))
				startInd = i;
			
			if(!strcmp(end, vertices[i]))
				endInd = i;
		}
	}
	
	//complain if something is wrong
	if(startInd == -1 || endInd == -1)
	{
		cout << "Either the start or the end doesn't exist.\n";
		return;
	}
	
	bool visited[maxIndex+1] = {false};
	int dist[maxIndex+1] = {INT_MAX};
	int prev[maxIndex+1] = {-1};
	bool remaining = false;
	
	for(int i = 0; i <= maxIndex; i++)
	{
		if(vertices[i])
		{
			dist[i] = INT_MAX;
			prev[i] = -1;
			visited[i] = false;
			remaining = true;
		}
		else
		{
			visited[i] = true;
		}
	}
	
	dist[startInd] = 0;
	
	while(remaining)
	{
		int minDist = INT_MAX;
		int minIndex = -1;
		for(int i = 0; i <= maxIndex; i++)
		{
			if(!visited[i] && minDist > dist[i])
			{
				minDist = dist[i];
				minIndex = i;
			}
		}
		visited[minIndex] = true;
		
		for(int i = 0; i <= maxIndex; i++)
		{
			if(adjacency[minIndex][i] != -1)
			{
				int maybe = dist[minIndex] + adjacency[minIndex][i];
				if(maybe < dist[i])
				{
					dist[i] = maybe;
					prev[i] = minIndex;
				}
			}
		}
		
		remaining = false;
		for(int i = 0; i <= maxIndex; i++)
		{
			if(!visited[i])
			{
				remaining = true;
			}
		}
	}
	
	if(dist[endInd] == INT_MAX)
	{
		cout << "There is no connection between the nodes.\n";
		return;
	}
	cout << "Minimum distance: " << dist[endInd] << "\nPath: ";
	outputList(vertices, prev, endInd);
	cout << endl;	
}

int main()
{	
	//build an array of char pointers to store the names of the vertices
	char* vertices[20] = {(char*)""};
	
	//build an array of integers to store edges
	int adjacency[20][20] = {{-1}};
	
	//initialize all edges to -1 
	for(int i=0; i < 20; i++)
	{
		vertices[i] = NULL;
		for(int j=0; j < 20; j++)
		{
			adjacency[i][j] = -1;
		}
	}
	
	bool running = true;
	
	while(running)
	{
		int input = 0;
		cout << "Enter a number.\n1: Add a vertex to the graph\n2: Add an edge to the graph\n3: Remove a vertex from the graph\n";
		cout << "4: Remove an edge from the graph\n5: Print the adjacency matrix\n6: Find the shortest distance between two vertices\n7: Quit\n\n";
		cin >> input;
		cout << endl;
		if(input == 1)
			addVertex(vertices);
		else if(input == 2)
			addEdge(vertices, adjacency);
		else if(input == 3)
			removeVertex(vertices, adjacency);
		else if(input == 4)
			removeEdge(vertices, adjacency);
		else if(input == 5)
			print(vertices, adjacency);
		else if(input == 6)
			salesman(vertices, adjacency);
		else if(input == 7)
			running = false;
		else
			cout << "Sorry, I couldn't understand that.\n";
		
		cout << endl;
	}
	
	return 0;
}