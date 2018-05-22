#include <iostream>
#include <cstring>

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
				cout << "\t";
				
				if(vertices[j])
					cout << vertices[j];
			}
			//put the edge weight in the main body of the table
			else
			{
				if(adjacency[i][j] != -1)
					cout << adjacency[i][j];
				else
					cout << "\t";
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
	cout << "Enter the name of the vertex you would like to add\n";
	char* input = new char[15];
	cin >> input;
	vertices[index] = input;
}

void addEdge(char* vertices[20], int adjacency[20][20])
{
	char* first = new char[15];
	char* second = new char[15];
	int weight = -1;
	
	cout << "Enter the name of the first vertex you want to connect\n";
	cin >> first;
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
	print(vertices, adjacency);
	
	addVertex(vertices);
	addVertex(vertices);
	addVertex(vertices);
	addVertex(vertices);
	
	adjacency[1][2] = 25;
	
	print(vertices, adjacency);	
	
	return 0;
}