#include<bits/stdc++.h>
using namespace std;
class Graph{
    public:
    int N;
    vector<vector<int>>matrix;
    Graph(int n=0):N(n),matrix(n,vector<int>(n,0)){}
    bool isReachable(int u,int v){
        if(u==v)return true;
        vector<bool> a(N,false);
        vector<int> b={u};
        a[u]=true;                                                              
        while(!b.empty()){
            int nd=b.back();b.pop_back();
            for(int i=0;i<N;i++){
                if(matrix[nd][i]&&!a[i]){
                    if(i==v)return true;
                    a[i]=true;
                    b.push_back(i);
                }
            }
        }
        return false;
    }
    void addEdge(int u,int v){
        matrix[u][v]=1;
        matrix[v][u]=1;
    }
    void removeEdge(int u,int v){
        matrix[u][v]=0;
        matrix[v][u]=0;
    }
    
    Graph operator+(const Graph& g){
        Graph result(max(N,g.N));
        for(int i=0;i<result.N;i++){
            for(int j=0;j<result.N;j++){
                if((i<N && j<N && matrix[i][j]==1)||(i<g.N && j<g.N && g.matrix[i][j]==1)){
                    result.matrix[i][j]=1;
                }
            }
        }
        return result;
    }
    Graph operator-(const Graph& g){
        Graph result(max(N,g.N));
        for(int i=0;i<result.N;i++){
            for(int j=0;j<result.N;j++){
                if((i<N && j<N && matrix[i][j]==1)&&(i<g.N && j<g.N && g.matrix[i][j]==1)){
                    result.matrix[i][j]=1;
                }
            }
        }
        return result;
    }
    Graph operator!(){
        Graph complement(N);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(i!=j&&matrix[i][j]==0)
                    complement.matrix[i][j]=1;
            }
        }
        return complement;
    }
    friend istream& operator>>(istream& in,Graph& g){
        int M,u,v;
        in>>g.N>>M;
        g.matrix.assign(g.N,vector<int>(g.N,0));
        for(int i=0;i<M;i++){
            in>>u>>v;
            g.addEdge(u,v);
        }
        return in;
    }
    friend ostream& operator<<(ostream& out,const Graph& g){
        for(int i=0;i<g.N;i++){
            out<<"Vertex "<<i<<": ";
            for(int j=0;j<g.N;j++){
                if(g.matrix[i][j])out<<j<<" ";
            }
             out<<"\n";
        }
        return out;
    }
};
int main(){
    Graph p;
    string input;
    cin>>input>>p;
    while(cin>>input){
        if(input=="union"){
            Graph q;
            cin>>input>>q;
            p=p+q;
        }
        else if(input=="intersection"){
            Graph q;
            cin>>input>>q;
            p=p-q;
        }
        else if(input=="complement"){
            p=!p;
        }
        else if(input=="isReachable"){
            int u,v;
            cin>>u>>v;
            cout<<(p.isReachable(u,v)?"Yes":"No")<<"\n";
        }
        else if(input=="add_edge"){
            int u,v;
            cin>>u>>v;
            p.addEdge(u,v);
        }
        else if(input=="remove_edge"){
            int u,v;
            cin>>u>>v;
            p.removeEdge(u,v);
        }
        else if(input=="printGraph"){
            cout<<p;
        }
        else if(input=="end"){
            break;
        }




    }




}
