#include<bits/stdc++.h>
using namespace std;

void addEdge(vector<int>* V, int u, int v)
{
    V[u].push_back(v);
}

void DFS(vector<int>* adj, int source, int n )
{
    vector<bool> visited(n+1, false);
    stack<int> st;
    st.push(source);

    vector<int>::iterator it;
    while(!st.empty()){
        source = st.top();
        st.pop();

        if(!visited[source]){
            cout<<source<<" ";
            visited[source] = true;
        }
        for(it = adj[source].begin(); it!=adj[source].end(); it++){
            if(!visited[*it]) st.push(*it);
        }
    }

}


int main()
{
    int node, edge, u, v;
    cout<<"Enter the value of node & edge :"<<endl;
    cin>>node>>edge;
    vector<int> graph[node+1];
    for(int i=0; i<edge; i++){
        cin>>u>>v;
       addEdge(graph,u,v);
    }
    DFS(graph,1, node);
    return 0;
}
