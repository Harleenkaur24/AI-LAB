#include<iostream>
#include<vector>

using namespace std;
class graph{
    int v;
    vector<vector<int>> adjlist;
    public:
    graph(int v){
        this->v=v;
        adjlist=vector<vector<int>> (v);
    }

    void addedge(int u,int v){
        adjlist[u].push_back(v);

    }

    void display()
    {
        for(int i=0;i<v;i++)
        {
            cout<<"Vertex"<<i<<" :";
            for(int j :adjlist[i])
            {
                cout<<"->"<<j;
            }
            cout<<endl;
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
    graph g(4);
    g.addedge(0,1);
    g.addedge(0,2);
    g.addedge(1,2);
    g.addedge(2,0);
    g.addedge(2,3);
    g.addedge(3,3);
    cout<<"Display:\n";
    g.display();
    cout<<"DFS starting from vertex 2:\n";
    g.dfs(2);
    return 0;
}