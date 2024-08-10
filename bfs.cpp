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
	

};
int main()
{
	graph g(5);
	g.addedge(0,1);
	g.addedge(0,2);
	g.addedge(1,3);
	g.addedge(1,4);
	g.addedge(2,4);
	cout<<"Display"<<"\n";
	g.display();
	cout<<"BFS starting from Vertex 0\n";
	g.bfs(0);
	return 0;
}