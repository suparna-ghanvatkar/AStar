//implementing a star search algorithm for finding the optimal path for robot delivery system
#include<iostream>
#include<queue>//for priority queue
#include<vector>
using namespace std;
class Node //this class inherited by node for graph and this is used for prior q
{
   protected:
	int node_no;
	int wt;
   public:
	Node()
	{
		node_no=0;
		wt=0;
	}
	Node(int n,int w)
	{
		node_no=n;
		wt=w;
	}
	//inline definitions of accessor functions
	void setno(int i)	
	{
		node_no=i;
	}
	void setwt(int i)
	{
		wt=i;
	}
	int getno()
	{
		return node_no;
	}
	int getwt()
	{
		return wt;
	}
};
class Gnode:public Node
{
   public:
	Gnode *next;
	int visited;
	Gnode()
	{
		next=NULL;
	}
	Gnode(int i,int j):Node(i,j)		//pass i and j to node parametrised constructor :)
	{
		next=NULL;
	}
};
struct CompareNode	//structure for comparison of nodes defined for purpose of prior q stl
{
	bool operator()(Node &n1, Node &n2)
	{
		return n1.getwt()>n2.getwt();
	}
};
priority_queue<Node,vector<Node>,CompareNode> Q;//define the priority queue used in a str
class Graph
{
	Gnode g[16];	//adjacency list representation
   public:
	Graph()
	{
		for(int i=0;i<=16;i++)
		{
			g[i].setno(i);
			g[i].setwt(0);
			g[i].next=NULL;
		}
	}
	void insertadj(int i);	//insert adj list for one vertex :)
	void insert();
	int getwt(int,int);
	friend class AStar;
};
void Graph::insertadj(int i)
{
	int n,w;
	Gnode *temp,*t=&g[i];
	cout<<"Insert next nodes(and weights) after node number "<<i<<"(-1 for null):";
	cin>>n>>w;
	if(n==-1)
	{
		g[i].next=NULL;		
		return;
	}
	//go in while loop for entering the next node
	while(n!=-1)
	{
		temp=new Gnode(n,w);//code from here				     	
		t->next=temp;
		t=temp;
		cout<<"Insert next nodes(and weights) after node number "<<i<<"(-1 for null):";
		cin>>n>>w;
	}	
}	
void Graph::insert()
{
	for(int i=0;i<=16;i++)
		insertadj(i);
}
int Graph::getwt(int q,int w)
{
	int i=0;
	Gnode *temp;
	temp=&g[q];
	while(temp->next!=NULL)
	{
		temp=temp->next;
		if(temp->getno()==w)
		{
			return temp->getwt();
		}
	}
	return -1;
}
int H[]={26,23,21,24,17,18,27,13,15,10,12,6,6,4,1,0,12};
class AStar
{
	Node n;
	Graph G;
	int g,f,h;
	int cost;
	int curr; //for current node number
	int end;
    public:
	AStar(int start,int e)
	{
		cost=0;
		g=f=h=0;
		G.insert();
		curr=start;
		end=e;
	}
	int calcf(int,int);
	void neigh(int);	//used for pushing the neighbours into priority q
	void algo();
};
int AStar::calcf(int c,int i)
{
	h=H[i];
	g=(cost+G.getwt(c,i));
	return g+h;
}
void AStar::neigh(int i)
{
	Gnode *temp;
	temp=&G.g[i];
	while(temp->next!=NULL)
	{
		temp=temp->next;
		f=calcf(i,temp->getno());
		n.setno(temp->getno());
		n.setwt(f);
		Q.push(n);
	}
} 
void AStar::algo()
{
	do
	{
		neigh(curr);	//neighbours of start node get pushed in q
		n=Q.top();
		Q.pop();
		curr=n.getno();	
		if(curr==end)
		{
			cout<<"Reached!"<<endl;
			return;
		}
		else cout<<curr<<"->";
	}while(!Q.empty());
}	
int main()
{
	AStar a(2,15);
	a.algo();
	return 0;
}
