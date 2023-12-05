#include<bits/stdc++.h>
using namespace std;

vector<int> bfs(vector<vector<int>>&graph, int start)
{
    vector<bool> visited(graph.size(), false);
    vector<int> traversal;
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while(!q.empty()){
        int current = q.front();
        q.pop();
        traversal.push_back(current);

        for(int neighbour : graph[current]){
                if(!visited[neighbour]){
                    visited[neighbour] = true;
                    q.push(neighbour);
                }

        }
        }
        return traversal;
    }



int main()
{
    vector<vector<int>> graph = {{1, 2}, {0, 3, 4}, {0, 5}, {1}, {1}, {2}};
    vector<int>traversal = bfs(graph,1);

    for( int node : traversal){
        cout<<node<<" ";
    }
    return 0;

}

 /* for user input
 int x,y, start; // size of the vector
 cin>>x>>y;
 vector<vector<int>> graph(x, vector<int>(y))

                            for(int i = 0; i < x; i++){
                                for(int i = 0; i < y; i++){
                                    cin>>graph[i][j];
                                }
                            }
                            */
