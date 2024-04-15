#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>

using namespace std;

mt19937 mt(time(nullptr));

int randomnum(int a,int b){
	return a+mt()%(b-a);
}

vector<int> randsampling(int n,int k){
	int i=0;
	vector<int> samples(k);
	for(;i<k;i++){
		samples[i]=i;
	}
	for(;i<n;i++){
		int j=randomnum(0,i+1);
		if(j<k){
			samples[j]=i;
		}
	}
	return samples;
}

void montyhall(int n,int k,int&switchwins,int&nonswitchwins){
	vector<bool> doors(n,0);
	int x=randomnum(0,n);
	doors[x]=1;
	int ini=randomnum(0,n);
	int i=0;
	// using reservoir sampling
	int m1=min(x,ini);
	int m2=max(x,ini);
	vector<int> opened(k);
	if(m1==m2){
		opened=randsampling(n-1,k);
		for(int j=0;j<k;j++){
			if(opened[j]>=m1){
				opened[j]++;
			}
		}
	}
	else{
		opened=randsampling(n-2,k);
		for(int j=0;j<k;j++){
			if(opened[j]>=m1){
				opened[j]++;
			}
		}
		for(int j=0;j<k;j++){
			if(opened[j]>=m2){
				opened[j]++;
			}
		}
	}
	vector<bool> switchable(n,1);
	switchable[ini]=0;
	for(int j=0;j<k;j++){
		switchable[opened[j]]=0;
	}
	int sw=randomnum(0,n-k-1);
	int j=0;
	for(;j<n;j++){
		if(switchable[j]==1){
			if(sw==0) break; 
			sw--;
		}
	}
	if(ini==x){
		nonswitchwins++;
		return;
	}
	else if(j==x){
		switchwins++;
		return;
	}
	return;
}

void simulate(int n,int k,int num){
	int switchwins=0;
	int nonswitchwins=0;
	for(int i=0;i<num;i++){
		montyhall(n,k,switchwins,nonswitchwins);
	}
	cout<<"simulated win% of sticking with the initial choice: "<<nonswitchwins/(double)num<<endl;
	cout<<"simulated win% of switching doors: "<<switchwins/(double)num<<endl;
	cout<<"expected win% of sticking with the initial choice: "<<1/(double)n<<endl;
	cout<<"expected win% of switching doors: "<<(1/(double)n)*((n-1)/((double)(n-k-1)))<<endl;
}

int main(int argc, char* argv[]){
	int n,k,num;
	n=atoi(argv[1]);
	k=atoi(argv[2]);
	num=atoi(argv[3]);
//	cin>>n>>k>>num;
	simulate(n,k,num);
}
