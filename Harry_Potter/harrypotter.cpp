#include<bits/stdc++.h>
using namespace std;

template<typename t>
// Minpriorityqueue class 
class Minpriorityqueue{

    private:

    // contains min heap 
    vector<t>heap;
    // heapifying up 
    void heapup(size_t index){
        // move the element up until heap property is satisfied
        while(index>0){
            size_t p=(index-1)/2;
            if(heap[p]>heap[index]){
                swap(heap[p],heap[index]);
                index=p;
            }
            else{
                break;
            }
        }
    }
    // heapifying down
    void heapdown(size_t index){
        // move the element down until heap property is satisfied
        size_t size=heap.size();
        while(2*index+1<size){
            size_t left=2*index+1,right=2*index+2;
            size_t smallest=index;
            // find the smallest child
            if(right<size && heap[right]<heap[smallest]){
                smallest=right;
            }
            if(left<size && heap[left]<heap[smallest]){
                smallest=left;
            }
            if(smallest==index){
                break;
            }
            swap(heap[index],heap[smallest]);
            index=smallest;
        }
    }

    public:

    void push(const t& value){
        // inserts a new element into the priority queue while preserving its heap property in O(log n) time.
        heap.push_back(value);
        heapup(heap.size()-1);
    }

    void pop(){
        // removes the top (minimum) element from the priority queue in O(log n) time.
        if (empty()){ 
            return;
        }
        heap[0] = heap.back();
        heap.pop_back();
        if (!empty()){
             heapdown(0);
        }
    }

    const t& top()const{
        // retrieves the top (minimum) element from the priority queue without removing it.
        return heap[0];

    }

    const size_t size()const{
        // returns the number of elements currently stored in the priority queue.
        return heap.size();
    }
    const bool empty() const{
        // checks whether the priority queue is empty, returning true if it contains no elements.
        return heap.empty();
    }
};

// node class 
class node{

    private:

    string name;
    long long int distance;
    int edges;

    public:

    node(string n,long long int d=LLONG_MAX,int e=0):name(n),distance(d),edges(e){}
    string getname()const{
        return name;
    }
    long long int getdistance()const{
        return distance;
    }
    int getedges()const{
        return edges;
    }
    void setdistance(int d){
        distance=d;
    }
    // overloading operator > for priority queue
    bool operator>(const node& other)const{
        return distance>other.distance;
    }
     // overloading operator < for priority queue
    bool operator<(const node& other)const{
        return distance<other.distance;
    }
};

// // fuction to implement dijkstra s shortest even path
// int DSEP(unordered_map<string,node>& graph,string s,string dis){
//     unordered_map<string,int>&dist;
//     Minpriorityqueue pq;
//     pq.push(node(s,0));

//     while(!pq.empty()){
//         node current=pq.top();
//         pq.pop();
//         string u=current.getname();
//         int d=current.distance();
//         for(auto &  [v,weight]:graph[u]){
//             fot(int i=0;i<2;i++){
//                 int new_dist=d+weight;
//                 int a=(d/weight)/2;
//                 if(new_dist<dist[v][a]){
//                     dist[v][a]=new_dist;
//                     pq.push(node(v, new_dist));
//                 }
//             }
//         }
//     }

// }

// class implementing dijkstra's shortest even path algorithm
class DSEP{
    private:

    // adjacency list to store graph
    unordered_map<string,vector<pair<string,int>>>adjlist;
    
    public:

    // function to add undirected edge to graph
    void addedge(string u,string v,int weight){
         adjlist[u].push_back({v,weight});
         adjlist[v].push_back({u,weight});
    }
    // main dijkstra implementation for even path
    long long Dijkstra(string s,string dest){
        Minpriorityqueue<node>pq;
        // maps to store distances for even and odd edge counts
        unordered_map<string,pair<long long int,int>>evendist;
        unordered_map<string,pair<long long int,int>>odddist;

        // initialize source node
        pq.push(node(s,0,0));
        evendist[s]={0,0};

        while(!pq.empty()){
            node current=pq.top();
            pq.pop();

            string room=current.getname();
            long long int currdist=current.getdistance();
            int curredges=current.getedges();

            // check if destination reached with even edges
            if(room==dest && curredges%2==0){
                return currdist;
            }
            // explore all neighboutrs
            for(size_t i=0;i<adjlist[room].size();i++){
                string nextroom=adjlist[room][i].first;
                int weight=adjlist[room][i].second;
                long long int newdist=currdist+weight;
                int newedges=curredges+1;

                // choose appropriate distance map based on edge count 
                auto& D=(newedges%2==0)?evendist:odddist;

                if(D.find(nextroom)==D.end() || newdist<D[nextroom].first){
                    D[nextroom]={newdist,newedges};
                    pq.push(node(nextroom,newdist,newedges));
                }
            }


        }
        // return -1 if no even path exists
        if(evendist.find(dest)==evendist.end()){
            return -1;
        }
        return evendist[dest].first;
    }
};

int main(){
    int n,m;
    cin>>n>>m;
    DSEP graph;
    vector<string>roomnum(n);
    // read rooms 
    // clears new line after n m 
    getline(cin,roomnum[0]);
    for(int i=0;i<n;i++){
        getline(cin,roomnum[i]);
    }
    // read edges 
    for(int j=0;j<m;j++){
        string u,v;
        int w;
        cin>>u>>v>>w;
        graph.addedge(u,v,w);
    }
    // read source and destination
    string s,des;
    cin>>s>>des;
    // print result 
    cout<<graph.Dijkstra(s,des)<<endl;
}