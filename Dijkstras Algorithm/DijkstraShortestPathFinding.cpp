/*
	Assignment 3: Implement Dijkstra's Shortest Path Algorithm.
*/

#include <iostream>
#include <queue>

class AdjList
{
        class Node
        {
                int vertex;
                int weight;
                Node* next;

        public:
//--------------CONSTRUCTOR---------------------
                Node(int v)
                {
                        this->vertex = v;
                        this->weight = 0;
                        Node* next = NULL;
                }

//--------------GETTERS---------------------------
                int getVertex()
                {
                        return vertex;
                }

                int getWeight()
                {
                        return weight;
                }

                Node* getNext()
                {
                        return next;
                }

//--------------SETTERS---------------------------
                void setVertex(int v)
                {
                        this->vertex = v;
                }

                void setWeight(int w)
                {
                        this->weight = w;
                }

                void setNext(Node* next)
                {
                        this->next = next;
                }
        };
	
	struct DistNVert
	{
		int wt;
		int preVertex;
	};


        unsigned int verticesCount;

        Node **adjList;

        public:
                AdjList(unsigned int v) : verticesCount(v)
                {
                        verticesCount = v;
                        adjList = new Node *[v];

                        for(unsigned int i=0; i<v; i++)
                        {
                                //Node* newNode = new Node(i+1);
                                adjList[i] = new Node(i+1);
                        }
                }

                ~AdjList()
                {
                        for(unsigned int i=0; i<verticesCount; i++)
                        {
                                delete [] adjList[i];
                        }

                        delete adjList;
                }


                bool checkRange(int chk)
                {
                        if(chk>0 && chk<=verticesCount)
                        {
                                return true;
                        }

                        return false;
                }

		void addEdges()
                {
                        unsigned int fromV = 0;                 //Source Vertex
                        unsigned int toV = 0;                   //Destination Vertex
                        int weight = 0;                         //Edge Weight In Between Above 2 Vertices
                        int count = 0;
                        int choice;

			do
			{
				std::cout<<"\nRange: [1-"<<verticesCount<<"]";
				std::cout<<"\nEnter Source Node :";
				std::cin>> fromV;
			}while(!checkRange(fromV));

			do
			{
				std::cout<<"\nRange: [1-"<<verticesCount<<"]";
				std::cout<<"\nEnter Destination Node :";
				std::cin>> toV;
			}while(!checkRange(toV));

			if(fromV == toV)
			{
				std::cout<<"\nSource and Destination are same ie., Its a Loop\n Weight = 1";
				weight = 1;
			}
			else
			{
				std::cout<<"\nEnter Edge Weight : ";
				std::cin>> weight;
			}


			if(checkDuplicate(adjList[fromV-1], toV))
			{
				return;
			}



		//-------Directed Forward Link----------

			Node* newNode1 = new Node(toV);
			Node* curr1 = adjList[fromV-1];
			Node* prev1 = NULL;
			newNode1->setWeight(weight);

			newNode1->setNext(curr1->getNext());
			curr1->setNext(newNode1);

			/*int flag1 = 0;

			while(curr1 != NULL)
			{
				if(newNode1->getWeight() < curr1->getWeight())
				{
					if(curr1 == adjList[fromV-1])
					{
						newNode1->setNext(curr1->getNext());
						curr1->setNext(newNode1);
						flag1++;
						break;
					}
					else
					{
						newNode1->setNext(curr1);
						prev1->setNext(newNode1);
						flag1++;
						break;
					}

				}

				prev1 = curr1;
				curr1 = curr1->getNext();
			}

			if(flag1 == 1)
			{
				prev1->setNext(newNode1);
			}

*/
		//--------Make Undirected Reverse Link--------- 
		
		//--------------COMMENT THIS PART TILL-------
/*
			Node* newNode2 = new Node(toV);
			Node* curr2 = adjList[fromV-1];
			Node* prev2 = NULL;
			newNode2->setWeight(weight);
			int flag2 = 0;

			while(curr2 != NULL)
			{
				if(newNode2->getWeight() < curr2->getWeight())
				{
					if(curr2 == adjList[fromV-1])
					{
						newNode2->setNext(curr2->getNext());
						curr2->setNext(newNode2);
						flag++;
						break;
					}
					else
					{
						newNode2->setNext(curr2);
						prev->setnext(newNode2);
						flag++;
						break;
					}

				}

				prev2 = curr2;
				curr2 = curr2->getNext();
			}

			if(flag == 1)
			{
				prev2->setNext(newNode1);
			}


*/
		//-----------------------------------------HERE TO MAKE GRAPH DIRECTED-----
			count++;

			if(!checkCount(count))                  //check with Max Edges One Can Make.
			{
				std::cout<<"\nMax Edges You Can Enter In Undirected Graph Reached";
			}

      		}

	      	bool checkDuplicate(Node *trav, int dest)
		{
			trav = trav->getNext();
			while(trav != NULL)
			{
				if(trav->getVertex() == dest)
				{
					std::cout<<"\nEdge Already Exists, Enter Other Vertex";
					return true;
				}
				trav = trav->getNext();
			}

			return false;
		}

		bool checkCount(int count)
		{
			//For Directed Graph
			//int result = (verticesCount-1) * (verticesCount-2);

			//For UnDirected Graph
			int result = ((verticesCount) * (verticesCount-1))/2;

			if(count>=result)
			{
				return false;
			}

			return true;
		}

/*		void countConnectedVertices()
		{

		}
*/
		void printList()
		{
			std::cout<<"\nAdjacency List is: \n";
			Node* trav;

			for(int i=0; i<verticesCount; i++)
			{
				trav = adjList[i];

				std::cout <<"Vertex: "<< trav->getVertex() << "---> ";

				trav = trav->getNext();
				std::cout<<"[";

				while(trav != NULL)
				{
					std::cout<<"\tW: " << trav->getWeight() << " V: "<< trav->getVertex()<<" ";
					trav = trav->getNext();
				}

				std::cout<<"]";
				std::cout<<std::endl;
			}
		}

		void DFS_Traversal(int vertex)
		{
			bool *visited = new bool[verticesCount];

			for(int i=0; i<verticesCount; ++i)
			{
				visited[i] = false;
			}

			std::cout<<"\nDFS Traversal\n";
			printDFS(vertex-1, visited);
		}

		void printDFS(int v, bool *visited)
		{
			Node* temp = adjList[v];

			if(visited[v])
			{
				return;
			}

			std::cout<< temp->getVertex() << " ";
			visited[v] = true;

			while(temp->getNext() != NULL)
			{
				temp = temp->getNext();
				printDFS(temp->getVertex()-1, visited);
			}
		}


		void BFS_Traversal(unsigned int vertex)
		{
			bool *visited = new bool[verticesCount];
			for(int i=0; i<verticesCount; ++i)
			{
				visited[i] = false;
			}

			std::queue<unsigned int> q;
			q.push(vertex);

			std::cout<<"\nBFS Traversal\n";

			while(!q.empty())
			{
				unsigned int v = q.front();
				q.pop();

				std::cout<< v << " ";
				visited[v-1] = true;

				Node* temp = adjList[v-1];
				temp = temp->getNext();

				while(temp != NULL)
				{
					if(!visited[temp->getVertex()-1])
					{
						unsigned int tmp = temp->getVertex()-1;
						q.push(tmp+1);
						visited[tmp] = true;
					}
						temp = temp->getNext();
				}
			}
		}

		void DijkstraShortestPath(int startV)
		{
			int MAX_VALUE = 99999;

			bool *visited = new bool[verticesCount];
			
			for(int i=0; i<verticesCount; ++i)
			{
				visited[i] = false;
			}
			

			DistNVert *currDist = new DistNVert[verticesCount]();

			for(int i=0; i<verticesCount; ++i)
			{
				currDist[i].wt = MAX_VALUE;
			}

			currDist[startV-1].wt = 0;
			currDist[startV-1].preVertex = -1;
			
			printDijkstra(visited, currDist, startV);

		}

		bool allVisited(bool* visited)
		{
			
			for(int i=1; i<verticesCount; ++i)
			{
				if(visited[i] == false)
					return false;
			}

			return true;
		}

		void printDijkstra(bool *visited, DistNVert *currDist, int startV)
		{
			
			int v = 0;
			int u = 0;
			//queue<int> visited;

		/*	for(int i=1; i<verticesCount; ++i)
			{
				visited.push(i);
			}
*/
			while(!allVisited(visited))
			{
				v = getSmallWt(currDist, visited);
				
				Node* trav = adjList[v];
				trav = trav->getNext();
				
				/*if(trav == NULL)
				{
					visited[v] = true;
					continue;
				}*/
				

				while(trav != NULL)
				{
					u = trav->getVertex() - 1;
			
					if(currDist[u].wt > currDist[v].wt + trav->getWeight())
					{
						currDist[u].wt = currDist[v].wt + trav->getWeight();
						currDist[u].preVertex = v;
			
					}
			
					trav = trav->getNext();
					//std::cout<<"-----------------------while In-In---------------------";
				}
					//std::cout<<"-----------------------while Out-Out---------------------";
				
					visited[v] = true;
			}	

			std::cout<<"\n Dijkstra Shortest Path: ";
			
			for(int i=0; i<verticesCount; ++i)
			{
				std::cout<<i+1<<"-- V:"<<currDist[i].preVertex + 1 << " W:" <<currDist[i].wt<<"--------> ";
			}
			
		}

		int getSmallWt(DistNVert *cd, bool *visited)
		{
			int temp;
			int smallV = 99999;
			int index = -1;

			for(int i=0; i<verticesCount; ++i)
			{
				if(visited[i] == true)
					continue;
			
				temp = cd[i].wt;

				if(temp<smallV)
				{
					smallV = temp;
					index = i; 
				}
			}

			return index;
		}



};


unsigned int getVertex()
{
	unsigned int vertex;
	std::cout<<"\nEnter from which Vertex to Traverse: ";
	std::cin>> vertex;

	return vertex;
}


int main()
{
        unsigned int vertices = 0;
	unsigned int vertex = 0;
        int select;
       	std::cout<<"\nEnter Total Number Of Vertices: ";
	std::cin>> vertices;

	AdjList *lst = new AdjList(vertices);

	do
	{
		std::cout<<"\nEnter \n1. Add Edges \n2. DFS Traversal \n3. BFS Traversal\n";
		std::cout<<"4. Dijkstra's Shortest Path Finding. \n5. Print Adjacency List \n0.EXIT";
		std::cout<<"\nEnter Choice: ";
		std::cin>>select;

		switch(select)
		{
			case 1: lst->addEdges();
				break;

			case 2: vertex = getVertex();
				lst->DFS_Traversal(vertex);

				break;

			case 3: vertex = getVertex();
				lst->BFS_Traversal(vertex);

				break;

			case 4: vertex = getVertex();
				lst->DijkstraShortestPath(vertex);
				break;

			case 5: lst->printList();
				break;

			case 0: std::cout<<"\n----------EXIT-----------\n";
				break;

			default: std::cout<<"\nInvalid Choice. Select from [0-2] ONLY";
		}
	}while(select != 0);

 	return 0;
}

