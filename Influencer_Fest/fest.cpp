#include<bits/stdc++.h>
using namespace std;

// comparator struct for priority queue (min heap)
struct comparator{
    bool operator()(int a,int b){
        return a>b;
    }
};

// base class for graph algorithms
class GraphAlgorithm{
protected:
    int n; // number of nodes
    vector<vector<int>>graph; // adjacency list representation of the graph
    vector<int>hypescores; // stores hype scores for each node
public:
    GraphAlgorithm(int n,vector<int>hypescores):n(n),hypescores(hypescores){
        graph.resize(n+1); // resize graph to accommodate n nodes (1-based index)
    }
    void addedge(int u,int v){
        graph[u].push_back(v); // add directed edge from u to v
    }
    virtual void Query()=0; // pure virtual function to be overridden
};

// class to detect cycle in a directed graph
class isCycle:public GraphAlgorithm{
private:
    vector<bool>visited; // keeps track of visited nodes
    vector<bool>stack; // keeps track of recursion stack

    bool dfs(int u){
        if(!visited[u]){
            visited[u]=true;
            stack[u]=true;
            for(int i=0;i<graph[u].size();++i){
                int v=graph[u][i]; // get the adjacent node
                if(!visited[v]&&dfs(v)){
                    return true; // cycle detected
                }
                else if(stack[v]){
                    return true; // cycle detected
                }
            }
        }
        stack[u]=false; // remove node from recursion stack
        return false;
    }
public:
    isCycle(int n,vector<int>&hypescores):GraphAlgorithm(n,hypescores){
        visited.resize(n+1,false);
        stack.resize(n+1,false);
    }

    void Query(){
        for(int i=1;i<=n;++i){
            visited[i]=false;
            stack[i]=false;
        }
        for(int i=1;i<=n;++i){
            if(!visited[i]&&dfs(i)){
                cout<<"YES"<<endl; // cycle found
                return;
            }
        }
        cout<<"NO"<<endl; // no cycle found
    }
};

// class to determine valid topological order (if exists)
class validOrder:public GraphAlgorithm{
private:
    vector<int>indegree; // stores in-degree of each node
public:
    validOrder(int n,vector<int>&hypescores):GraphAlgorithm(n,hypescores){
        indegree.resize(n+1,0);
    }
    void Query()override{
        for(int u=1;u<=n;++u){
            for(int i=0;i<graph[u].size();++i){
                int v=graph[u][i]; // get the adjacent node
                indegree[v]++; // increase in-degree
            }
        }
        priority_queue<int,vector<int>,comparator>pq;
        for(int u=1;u<=n;++u){
            if(indegree[u]==0){ // push nodes with 0 in-degree
                pq.push(u);
            }
        }
        vector<int>ord;
        while(!pq.empty()){
            int u=pq.top();
            pq.pop();
            ord.push_back(u);
            for(int i=0;i<graph[u].size();++i){
                int v=graph[u][i]; // get the adjacent node
                if(--indegree[v]==0){ // if in-degree becomes 0, push to pq
                    pq.push(v);
                }
            }
        }
        if(ord.size()!=n){
            cout<<"NO"<<endl; // cycle exists, no valid topological order
        }
        else{
            for(int i=0;i<ord.size();++i){
                int u=ord[i];
                cout<<u<<" ";
            }
            cout<<endl;
        }
    }
};

// class to find strongly connected components (SCCs)
class indepComponent:public GraphAlgorithm{
private:
    vector<bool>vis; // visited array
    stack<int>ord; // stores nodes in order of finishing times
    vector<vector<int>>reversedgraph; // stores reversed edges

    void dfs1(int u){
        vis[u]=true;
        for(int i=0;i<graph[u].size();++i){
            int v=graph[u][i]; // get the adjacent node
            if(!vis[v]){
                dfs1(v);
            }
        }
        ord.push(u); // store nodes in order of finishing times
    }
    void dfs2(int u,vector<int>&component){
        vis[u]=true;
        component.push_back(u);
        for(int i=0;i<reversedgraph[u].size();++i){
            int v=reversedgraph[u][i];
            if(!vis[v]){
                dfs2(v,component);
            }
        }
    }
public:
    indepComponent(int n,vector<int>&hypescores):GraphAlgorithm(n,hypescores){
        reversedgraph.resize(n+1);
    }
    void Query()override{
        vis.assign(n+1,false);
        ord=stack<int>();
        for(int u=1;u<=n;++u){
            if(!vis[u]){
                dfs1(u);
            }
        }
        reversedgraph.assign(n+1,vector<int>());
        for(int u=1;u<=n;++u){
            for(int i=0;i<graph[u].size();++i){
                int v=graph[u][i]; // get the adjacent node
                reversedgraph[v].push_back(u); // reverse the edges
            }
        }
        vis.assign(n+1,false);
        vector<vector<int>>sccs;
        while(!ord.empty()){
            int u=ord.top();
            ord.pop();
            if(!vis[u]){
                vector<int>component;
                dfs2(u,component);
                sccs.push_back(component);
            }
        }
        int maxsize=0;
        for(int i=0;i<sccs.size();++i){
            const auto&scc=sccs[i];
            maxsize=max(maxsize,(int)scc.size());
        }
        cout<<sccs.size()<<" "<<maxsize<<endl; // print number of SCCs and max SCC size
    }
};

class maxHype:public GraphAlgorithm{
private:
    vector<vector<int>>reversedgraph; // stores the reversed graph for SCC computation
    vector<bool>vis; // visited array for DFS traversal
    stack<int>ord; // stack to store nodes in finishing order for SCC computation
    vector<int>scc; // stores the SCC id of each node
    vector<int>scc_hype; // stores the cumulative hype score of each SCC

    void dfs1(int u){
        vis[u]=true;
        for(int i=0;i<graph[u].size();++i){
            int v=graph[u][i]; // get the adjacent node
            if(!vis[v]){
                dfs1(v); // perform DFS traversal
            }
        }
        ord.push(u); // push the node to stack after processing
    }

    void dfs2(int u,int scc_num){
        vis[u]=true;
        scc[u]=scc_num; // assign SCC number to the node
        for(int i=0;i<reversedgraph[u].size();++i){
            int v=reversedgraph[u][i]; // get the adjacent node
            if(!vis[v]){
                dfs2(v,scc_num); // perform DFS on reversed graph
            }
        }
    }

    int maxPathSum(vector<vector<int>>& condensed_graph, vector<int>& dp, int u){
        if(dp[u]!=-1){
            return dp[u]; // return memoized result if already computed
        }
        dp[u]=scc_hype[u]; // base case: hype score of the current SCC
        for(int i=0;i<condensed_graph[u].size();++i){
            int v=condensed_graph[u][i]; // get adjacent SCC
            dp[u]=max(dp[u],scc_hype[u]+maxPathSum(condensed_graph,dp,v)); // compute maximum path sum
        }
        return dp[u];
    }
public:
    maxHype(int n,vector<int>&hypescores):GraphAlgorithm(n,hypescores){
        reversedgraph.resize(n+1);
        vis.resize(n+1,false);
        scc.resize(n+1,-1);
    }

    void Query()override{
        // Build reverse graph by reversing edges
        reversedgraph.assign(n+1,vector<int>());
        for(int u=1;u<=n;++u){
            for(int i=0;i<graph[u].size();++i){
                int v=graph[u][i];
                reversedgraph[v].push_back(u); // reverse the edge
            }
        }

        // First DFS to get finishing order
        vis.assign(n+1,false);
        for(int u=1;u<=n;++u){
            if(!vis[u]){
                dfs1(u); // run DFS on unvisited nodes
            }
        }

        // Second DFS to find SCCs
        vis.assign(n+1,false);
        int scc_num=0;
        while(!ord.empty()){
            int u=ord.top();
            ord.pop();
            if(!vis[u]){
                dfs2(u,scc_num++); // assign SCCs
            }
        }

        // Calculate hype scores for each SCC
        scc_hype.assign(scc_num,0);
        for(int u=1;u<=n;++u){
            scc_hype[scc[u]]+=hypescores[u]; // sum hype scores for each SCC
        }

        // Build condensed graph where each SCC is a node
        vector<vector<int>>condensed_graph(scc_num);
        for(int u=1;u<=n;++u){
            for(int i=0;i<graph[u].size();++i){
                int v=graph[u][i];
                if(scc[u]!=scc[v]){ // If they belong to different SCCs
                    condensed_graph[scc[u]].push_back(scc[v]); // add edge in condensed graph
                }
            }
        }

        // Compute maximum hype score using DP
        vector<int>dp(scc_num,-1); // -1 indicates uncomputed
        int max_hype=0;
        for(int i=0;i<scc_num;++i){
            max_hype=max(max_hype,maxPathSum(condensed_graph,dp,i)); // find max path sum
        }
        cout<<max_hype<<endl; // output the maximum hype score
    }
};
    

int main(){
    int n,m;
    cin>>n>>m;
    vector<int>h(n+1);
    for(int i=1;i<=n;++i){
        cin>>h[i]; 
    }
    isCycle cycleDetector(n,h);
    validOrder topoOrder(n,h);
    maxHype hypeCalculator(n,h);
    indepComponent sccFinder(n,h);

    for(int j=0;j<m;++j){
        int u,v;
        cin>>u>>v;
        cycleDetector.addedge(u,v);
        topoOrder.addedge(u,v);
        hypeCalculator.addedge(u,v);
        sccFinder.addedge(u,v);
    }
    int p;
    cin>>p;

    while(p--){
        int input;
        cin>>input;
        if(input==1){
            cycleDetector.Query();
        }
        else if(input==3){
            topoOrder.Query();
        }
        else if(input==4){
            hypeCalculator.Query();
        }
        else if(input==2){
            sccFinder.Query();
        }


    }

    
}
