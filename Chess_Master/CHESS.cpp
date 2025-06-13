#include<bits/stdc++.h>
#include<algorithm>
using namespace std;

#define int long long int

int min(int a,int b){
    return(a<b)?a:b;
}

void swap(int &a,int &b){
    int temp=a;a=b;b=temp;
}

int partition(vector<int>&arr,int low,int high,bool aso){
    int pivot=arr[high],i=low-1;
    for(int j=low;j<high;j++){
        if((aso&&arr[j]<pivot)||(!aso&&arr[j]>pivot)){++i;swap(arr[i],arr[j]);}
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}

void sort(vector<int>&arr,int low,int high,bool aso){
    if(low<high){
        int pivot=partition(arr,low,high,aso);
        sort(arr,low,pivot-1,aso);
        sort(arr,pivot+1,high,aso);
    }
}

void merge(vector<int>&arr,int left,int mid,int right,bool aso){
    int n1=mid-left+1,n2=right-mid;
    vector<int>L(n1),R(n2);
    for(int i=0;i<n1;i++)L[i]=arr[left+i];
    for(int i=0;i<n2;i++)R[i]=arr[mid+1+i];
    int i=0,j=0,k=left;
    while(i<n1&&j<n2){
        if((aso&&L[i]<=R[j])||(!aso&&L[i]>=R[j]))arr[k]=L[i++];
        else arr[k]=R[j++];
        k++;
    }
    while(i<n1)arr[k++]=L[i++];
    while(j<n2)arr[k++]=R[j++];
}

void mergeSort(vector<int>&arr,int left,int right,bool aso){
    if(left<right){
        int mid=left+(right-left)/2;
        mergeSort(arr,left,mid,aso);
        mergeSort(arr,mid+1,right,aso);
        merge(arr,left,mid,right,aso);
    }
}

void sortRow(vector<int>&row,bool aso){
    mergeSort(row,0,row.size()-1,aso);
}

bool comp_X(pair<int,int>a,pair<int,int>b){
    return (a.first<b.first)||(a.first==b.first && a.second<b.second);
}
bool comp_Y(pair<int,int>a,pair<int,int>b){
    return (a.second<b.second)||(a.second==b.second && a.first<b.first);
}

class Chess{
    private:
    vector<vector<int>>board;
    int size;
    public:
    Chess(int n):size(n){
        board.resize(n,vector<int>(n));
    }
    void setstates(vector<vector<int>>&states){
        board=states;
    }
    void sortRows(bool aso){
        for(auto &row:board)sortRow(row,aso);
    }
    int countInversions(){
        vector<int>newmat;
        for(auto &row:board)newmat.insert(newmat.end(),row.begin(),row.end());
        return sortandcount(newmat,0,newmat.size()-1);
    }
    void display(){
        for(int i=0;i<board.size();++i){
            for(int j=0;j<board[i].size();++j)cout<<board[i][j]<<" ";
            cout<<endl;
        }
    }
    
    pair<pair<int,int>,pair<int,int>>closestpair(vector<pair<int,int>>&points,map<pair<int,int>,int> &m){
        vector<pair<int,int>> PX=points,PY=points;
        sort(PX.begin(),PX.end(),comp_X);
        sort(PY.begin(),PY.end(),comp_Y);
        return findcp(PX,PY,m);
    }
    int mergeandcount(vector<int>&arr,int left,int mid,int right){
        vector<int>temp(right-left+1);
        int inversioncount=0,i=left,j=mid+1,k=0;
        while(i<=mid&&j<=right){
            if(arr[i]<=arr[j])temp[k++]=arr[i++];
            else{temp[k++]=arr[j++];inversioncount+=mid-i+1;}
        }
        while(i<=mid)temp[k++]=arr[i++];
        while(j<=right)temp[k++]=arr[j++];
        for(int i=left;i<=right;++i)arr[i]=temp[i-left];
        return inversioncount;
    }
    int sortandcount(vector<int>&arr,int left,int right){
        int inversioncount=0;
        if(left<right){
            int mid=left+(right-left)/2;
            inversioncount+=sortandcount(arr,left,mid);
            inversioncount+=sortandcount(arr,mid+1,right);
            inversioncount+=mergeandcount(arr,left,mid,right);
        }
        return inversioncount;
    }
    int dsquared(pair<int,int>&p1,pair<int,int>&p2){
        long long dx=p1.first-p2.first,dy=p1.second-p2.second;
        return dx*dx+dy*dy;
    }
    bool distanceEqual(pair<pair<int,int>,pair<int,int>>&pair1,pair<pair<int,int>,pair<int,int>>&pair2){
        pair<int,int>p1=pair1.first;
        pair<int,int>q1=pair1.second;
        if(!comp_X(p1,q1)){
            swap(p1,q1);
        }
        pair<int,int>p2=pair2.first;
        pair<int,int>q2=pair2.second;
        if(!comp_X(p2,q2)){
            swap(p2,q2);
        }
        if(p1.first!=p2.first){
            return p1.first<p2.first;
        }
        if(p1.second!=p2.second){
            return p1.second<p2.second;
        }
        if(q1.first!=q2.first){
            return q1.first<q2.first;
        }
        return q1.second<q2.second;
    }
    pair<pair<int,int>,pair<int,int>>findcp(vector<pair<int,int>>&PX,vector<pair<int,int>>&PY,map<pair<int,int>,int>&m){
        if(PX.size()<=3){
            int mindist=LLONG_MAX;
            pair<pair<int,int>,pair<int,int>>closestpair;
            for(int i=0;i<PX.size();++i){
                for(int j=i+1;j<PX.size();++j){
                    int dist=dsquared(PX[i],PX[j]);
                    if(dist<mindist){
                        mindist=dist;
                        closestpair={PX[i],PX[j]};
                    }
                    else if(dist==mindist){
                        pair<pair<int,int>,pair<int,int>>newPair={PX[i],PX[j]};
                        if(distanceEqual(newPair,closestpair)){
                            closestpair=newPair;
                        }
                    }
                }
            }
            return closestpair;
        }
        int mid=PX.size()/2;
        pair<int,int>midpoint=PX[mid];
        vector<pair<int,int>>leftX(PX.begin(),PX.begin()+mid),rightX(PX.begin()+mid,PX.end());
        vector<pair<int,int>>leftY,rightY;
        for(int i=0;i<PY.size();i++){
            if(PY[i].first<=midpoint.first){
                leftY.push_back(PY[i]);
            }else{
                rightY.push_back(PY[i]);
            }
        }
        auto leftPair=findcp(leftX,leftY,m),rightPair=findcp(rightX,rightY,m);
        int leftDist=dsquared(leftPair.first,leftPair.second),rightDist=dsquared(rightPair.first,rightPair.second);
        int minDist=min(leftDist,rightDist);
        pair<pair<int,int>,pair<int,int>>minPair=(leftDist<rightDist)?leftPair:rightPair;
        if(leftDist==rightDist){
            
            if(distanceEqual(leftPair,rightPair)){
                minPair=leftPair;
            }else{
                minPair = rightPair;
            }
        }
        vector<pair<int,int>>strip;
        for(auto &point:PY)if((point.first-midpoint.first)*(point.first-midpoint.first)<minDist)strip.push_back(point);
        for(int i=0;i<strip.size();++i){
            for(int j=i+1;j<strip.size()&&(strip[j].second-strip[i].second)*(strip[j].second-strip[i].second)<minDist;++j){
                int dist=dsquared(strip[i],strip[j]);
                if(dist<minDist){
                    minDist=dist;
                    minPair={strip[i],strip[j]};
                }
                else if(dist==minDist){
                    pair<pair<int,int>,pair<int,int>>newPair={strip[i],strip[j]};
                    if(distanceEqual(newPair,minPair)){
                        minPair=newPair;
                    }
                }
            }
        }
        return minPair;
    }
};

int32_t main(){
    Chess*board=nullptr;
    string command;
    while(cin>>command){
        if(command=="CREATE_2D"){
            int size;cin>>size;
            board=new Chess(size);
            vector<vector<int>>states(size,vector<int>(size)); // Fix: Use vector<vector<int>> instead of vector<vector<long long>>
            for(int i=0;i<size;++i)for(int j=0;j<size;++j)cin>>states[i][j];
            board->setstates(states);
        }else if(command=="SORT_2D"){
            string order;cin>>order;
            board->sortRows(order=="ascending");
        }else if(command=="INVERSION_2D")cout<<board->countInversions()<<endl;
        else if(command=="DISPLAY_2D")board->display();
        else if(command=="CLOSEST_2D"){
            int numPoints;cin>>numPoints;
            vector<pair<int,int>>points(numPoints);
            map<pair<int,int>,int> m;
            for(int i=0;i<numPoints;++i){cin>>points[i].first>>points[i].second;m[points[i]]=i;}
            auto closest=board->closestpair(points,m);
            if(m[closest.first]>m[closest.second]){swap(closest.first,closest.second);}
            cout<<closest.first.first<<" "<<closest.first.second<<" "<<closest.second.first<<" "<<closest.second.second<<endl;
        }else if(command=="END")break;
    }
    delete board;
    return 0;
}