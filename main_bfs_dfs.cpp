#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class graph{
	int v;
	vector<vector<int>> adjlist;

	public:
	graph(int v){
		this->v=v;
		adjlist=vector<vector<int>> (v);
	}
    void addedge(int u, int v){
     adjlist[u].push_back(v);
	}

	void display()
	{
		for (int i=0;i<v;i++){
			cout<<"Vertex"<<i<<":";
			for(int j:adjlist[i]){
				cout<<"->"<<j;
			}
			cout<<endl;
		}
	}

	void bfs(int start){
		int n=adjlist.size();
		queue<int> q;
		vector<bool> visited(n,false);
		visited[start]=true;
		q.push(start);

		while(!q.empty()){
			int node=q.front();
			q.pop();
			cout<<node<<" ";
			for(int neighbor:adjlist[node])
			{
				if(!visited[neighbor])
				{
                   visited[neighbor]=true;
				   q.push(neighbor);
				}
			}
		}
	}

	void dfsrec(int v, vector<bool> &visited)
    {
        visited[v]=true;
        cout<<v<<" ";

        for(int i:adjlist[v])
        {
            if(!visited[i])
            {
                dfsrec(i,visited);
            }
        }

    }

    void dfs(int v)
    {
        vector<bool> visited(v,false);
        dfsrec(v,visited);
    }

};

int main()
{
	int nodes,edges;
	cout<<"Enter no. of nodes:\n";
	cin>>nodes;
	graph g(nodes);
	cout<<"Enter no. of edges\n";
	cin>>edges;
	cout<<"Enter the edges (u v):\n";
	int u,v;
	for(int i=0; i<edges;i++)
	{
		cin>>u>>v;
		g.addedge(u,v);
	}
	g.display();

	int start_node;
	cout<<"Enter the starting node:\n";
	cin>>start_node;

	int option;
	cout<<"Enter 1 for BFS and 2 for DFS: \n ";
	cin>>option;

	if(option==1){
		g.bfs(start_node);
	}
	else if(option==2){
		g.dfs(start_node);
	}
	else{
		cout<<"Invalid option";
		return 0;
	}

	return 0;

	
}


