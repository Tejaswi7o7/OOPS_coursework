#include<bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;

class CurrencySorter{
    public:
        void operator()(vector<int>&arr){// functor to sort an array using quick sort.
            quickSort(arr,0,arr.size()-1);
        } 
    private:
        void quickSort(vector<int>&arr, int low, int high){ // recursive quick sort.
            if(low<high){
                int pi=partition(arr,low,high);
                quickSort(arr,low,pi-1);
                quickSort(arr,pi+1,high);
            }
        }
        int partition(vector<int>&arr,int low,int high){ // partition function for quick sort.
            int pivot=arr[high];
            int i=(low-1);
            for(int j=low;j<high;j++){
                if(arr[j]<=pivot){
                    i++;
                    swap(arr[i],arr[j]);
                }
            }
            swap(arr[i+1],arr[high]);
            return (i+1);
        }
};

class FibonacciGenerator{
    public:
        long long int operator()(long long int n){
            return fibonacci(n);
        }

    private:
        void multiply(long long int A[2][2],long long int B[2][2],long long int C[2][2]){
            for(int i=0;i<2;++i){
                for(int j=0;j<2;++j){
                    C[i][j]=0;
                    for(int k=0;k<2;++k){
                        C[i][j]=(C[i][j]+A[i][k]*B[k][j]%mod)%mod;
                    }
                }
            }
        }
        void matrixPower(long long int base[2][2],long long int expo,long long int result[2][2]){
            long long int temp[2][2];
            result[0][0]=1;result[0][1]=0;
            result[1][0]=0;result[1][1]=1;
            while(expo>0){
                if(expo%2==1){
                    multiply(result,base,temp);
                    for(int i=0;i<2;++i){
                        for(int j=0;j<2;++j){
                            result[i][j]=temp[i][j];
                        }
                    }
                }
                multiply(base,base,temp);
                for(int i=0;i<2;++i){
                    for(int j=0;j<2;++j){
                        base[i][j]=temp[i][j];
                    }
                }
                expo /=2;
            }
        }
        long long int fibonacci(long long int n){
            if(n==0){
                return 0;
            }
            long long int F[2][2]={{1,1},{1,0}};
            long long int result[2][2];
            matrixPower(F,n-1,result);
            return result[0][0];
        }
    };

    class PrimeCalculator {
        public:
            void printPrimes(long long int l, long long int r){
                vector<long long int>prime=sieve(l,r);
                for(long long p:prime){
                    cout<<p<<" ";
                }
                cout<<endl;
            }
        
            long long int printPrimeSum(long long int l, long long int r){
                vector<long long>prime=sieve(l, r);
                long long sum=0;
                for(long long p:prime){
                    sum+=p; 
                }
                return sum;
            }
        
        private:
            vector<long long>sieve(long long int l,long long int r){
                long long int limit=sqrt(r);
                vector<bool>isPrime(limit+1,true);
                isPrime[0]=isPrime[1]=false;
                for (long long int i = 2;i*i<=limit;i++){
                    if(isPrime[i]){
                        for(long long int j=i*i;j<=limit;j+=i){
                            isPrime[j]=false;
                        }
                    }
                }
                vector<long long int>prime;
                for(long long int i=2;i<=limit;i++){
                    if(isPrime[i]){
                        prime.push_back(i);
                    }
                }
                vector<bool>rangePrime(r-l+1,true);
                if(l==1){
                    rangePrime[0]=false;
                }
                for(long long int p:prime){
                    long long int start=max(p*p,(l+p-1)/p*p);
                    for (long long int i=start;i<=r;i+=p) {
                        rangePrime[i-l]=false;
                    }
                }
                vector<long long int>ans;
                for(long long int i=l;i<=r;i++){
                    if(rangePrime[i-l]) {
                        ans.push_back(i);
                    }
                }
                return ans;
            }
        };
    
    class NumberAnalyzer{
    public:
        bool isSquareFree(int x) {
            for(int i=2;i*i<=x;i++){
                if(x%(i*i)==0){
                    return false;
                }
            }
            return true;
        }
        long long int countDivisors(int x) {
            long long int count=1;
            for(int i=2;i*i<=x;i++){
                if(x%i==0){
                    int exp=0;
                    while(x%i==0){
                        x/= i;
                        exp++;
                    }
                    count*=(exp+1);
                }
            }
            if (x>1){
                count*=2;
            }
            return count;
        }
        long long int sumOfDivisors(int x){
            long long int sum=1;
            for(int i=2;i*i<=x;i++){
                if(x%i==0){
                    int exp=0;
                    while(x%i==0){
                        x/=i;
                        exp++;
                    }
                    sum*=(pow(i,exp+1)-1)/(i-1);
                }
            }
            if(x>1)sum*=(x+1);
            return sum;
        }
    };
int main(){
    int input;
    cin>>input;
    if(input==1){
        CurrencySorter sort;
        int t;
        cin>>t;
        while(t--){
            int n;
            cin>>n;
            vector<int>arr(n);
            for(int i=0;i<n;i++){
                cin>>arr[i];
            }
            sort(arr);
            for(int i=0;i<n;i++){
                cout<<arr[i]<<" ";
            }
            cout<<endl;
        }
    }
    else if(input==2){
        FibonacciGenerator fib;
        int t;
        cin>>t;
        while(t--){
            long long int i;
            cin>>i;
            cout<<fib(i)<<endl;
        }
    }
    else if(input==3){
        PrimeCalculator primecalc;
        int t;
        cin>>t;
        while(t--){
            string command;
            cin>>command;
            if(command=="printPrimes"){
                long long int l,r;
                cin>>l>>r;
                primecalc.printPrimes(l,r);
            }
            else if(command=="printPrimeSum"){
                long long int l,r;
                cin>>l>>r;
                cout<<primecalc.printPrimeSum(l,r)<<endl;
            }
        }
    }
    else if(input==4){
        NumberAnalyzer num;
        int t;
        cin>>t;
        while(t--){
            string command;
            cin>>command;
            if(command=="isSquareFree"){
                int x;
                cin>>x;
                cout<<(num.isSquareFree(x)? "yes" : "no") <<endl;
            }
            else if(command=="countDivisors"){
                int x;
                cin>>x;
                cout<<num.countDivisors(x)<<endl;
            }
            else if(command=="sumOfDivisors"){
                int x;
                cin>>x;
                cout<<num.sumOfDivisors(x)<<endl;
            }
        }
    }
}