#include <iostream>
#include <queue>
using std::queue;

class DungeonMaster
{
	class ValueAtIndex
	{
		public:
		int pr, pc;						//Parent Position in Dungeon
		int r, c; 					//Current Position in Dungeon
		char path;
		bool isVisited;

		ValueAtIndex()
		{
			path = 'o';
			isVisited = false;
		}
	};


	int rows;
	int cols;
	ValueAtIndex** dungeon;

public:
	DungeonMaster(int r, int c) : rows(r), cols(c)
	{
		rows = r;
		cols = c;
		dungeon = new ValueAtIndex *[r];
		for(int i=0; i<r; i++)
		{
			dungeon[i] = new ValueAtIndex[c]();
		}
	}

	~DungeonMaster()
	{
		for(int i = 0; i< rows; i++)
		{
			delete [] dungeon[i];
		}

		delete [] dungeon;
	}

	bool dungeonMatrix(int sr, int sc, int er, int ec)
	{
		bool choice = true;

		while(choice)
		{
			std::cout<<"\n------------------------1---------------------";
			addBlocksInDungeon(sr,sc,er,ec);		//Add Lane Blocks in Dungeon
			std::cout<<"\nAdd More Blocks? [y/n] :";
			char ch;
			std::cin>>ch;
			choice = true*(ch=='y' || ch=='Y') + false*(ch=='n' || ch=='N');
		}
		
		dungeon[sr][sc].r = sr;
		dungeon[sr][sc].c = sc;
		dungeon[sr][sc].pr = -1;
		dungeon[sr][sc].pc = -1;
		
		queue<ValueAtIndex> q;
		q.push(dungeon[sr][sc]);
		ValueAtIndex temp;
		int dr[] = {-1,1,0,0};
		int dc[] = {0,0,1,-1};
		int r1, c1;									//Current Position in Dungeon
		int rr, cc;
		
		do
		{				
				temp = q.front();
				r1 = temp.r; c1 = temp.c;

				dungeon[r1][c1].isVisited = true;
				q.pop();

				for(int i=0; i<4; ++i) 					//4 for 4 direction one can Travel- N,S,E,W
				{																//Diagnolly Not Allowed
					rr = r1 + dr[i];
					cc = c1 + dc[i];

					if((rr<0 || rr>=rows) || (cc<0 || cc>=cols))
							continue;
					
					if(dungeon[rr][cc].path == 'o' && dungeon[rr][cc].isVisited == false)
					{
						dungeon[rr][cc].r = rr;
						dungeon[rr][cc].c = cc;
						dungeon[rr][cc].pr = r1;
						dungeon[rr][cc].pc = c1;
						dungeon[rr][cc].isVisited = true;
						q.push(dungeon[rr][cc]);
					}
					
					
					if(rr == er && cc == ec)
						return true;
				}
			
		}while(!(q.empty()));

		return false;
	}

	void addBlocksInDungeon(int sr, int sc, int er, int ec)
	{
		int br, bc;
		std::cout<<"\nEnter RoadBlock Row: ";
		std::cin>> br;
		
		std::cout<<"\nEnter RoadBlock Column: ";
		std::cin>> bc;

		if((br==sr && bc == sc) || (br==er && bc==ec))
				std::cout<<"Start and Destination Point Cant be Blocked";
		else
				dungeon[br][bc].path = 'x';
	}

	void printDungeonPath(int sr, int sc, int er, int ec)
	{
		int r = er, c = ec, r1, c1;
		std::cout<<"\nEXIT<--- ";

		while(!(dungeon[r][c].r == sr && dungeon[r][c].c == sc))
		{
			std::cout<<" ("<<r<<","<<c<<") <-----";
			r1 = dungeon[r][c].pr;
			c1 = dungeon[r][c].pc;
			r = r1; c = c1;
		}
			
		std::cout<<" ("<<sr<<","<<sc<<") ";
		std::cout<<"<--- START, You are Here ";
	}

};

int main()
{
		bool choice = true;
		int r,c;

		std::cout<<"\nEnter matrix size[nxm]\nn:";
		std::cin>> r;
		std::cout<<"m:";
		std::cin>> c;
		
		int sr,sc,er,ec;
		
		std::cout<<"\nEnter Start Coordinates (r,c): \nr: ";
		std::cin>> sr;
		std::cout<<"c: ";
		std::cin>> sc;
	
		std::cout<<"\nEnter End Coordinates (r,c): \nr: ";
		std::cin>> er;
		std::cout<<"c: ";
		std::cin>> ec;

		DungeonMaster *dm = new DungeonMaster(r,c);
		
		bool result = dm->dungeonMatrix(sr,sc,er,ec);

		if(result)
			dm->printDungeonPath(sr,sc,er,ec);
		else
			std::cout<<"\nYou are Trapped For Life. No Exit path Available!!!\n";
			
	return 0;
}
