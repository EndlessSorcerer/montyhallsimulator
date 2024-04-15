#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
#include <unordered_map>

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
	if(k>(n-2)){
		cerr<<"invalid values";
		return;
	}
	if(k<0 || n<0 || num<=0){
		cerr<<"invalid values";
		return;
	}
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
	unordered_map<string, int> args;

    // Initialize default values
    args["--num_doors"] = 3;
    args["--num_doors_opened_by_host"] = 1;
    args["--num_simulations"] = 1000;

    for (int i = 1; i < argc; i++) {
        string arg(argv[i]);
        if (arg == "--num_doors") {
            if (i + 1 < argc) {
                args["--num_doors"] = stoi(argv[i + 1]);
                ++i;
            } else {
                cerr << "Missing value for --num_doors" << endl;
            }
        } else if (arg == "--num_doors_opened_by_host") {
            if (i + 1 < argc) {
                args["--num_doors_opened_by_host"] = stoi(argv[i + 1]);
                ++i;
            } else {
                cerr << "Missing value for --num_doors_opened_by_host" << endl;
            }
        } else if (arg == "--num_simulations") {
            if (i + 1 < argc) {
                args["--num_simulations"] = stoi(argv[i + 1]);
                ++i;
            } else {
                cerr << "Missing value for --num_simulations" << endl;
            }
        } else {
            cerr << "Unknown argument: " << arg << endl;
        }
    }

    cout << "num_doors: " << args["--num_doors"] << endl;
    cout << "num_doors_opened_by_host: " << args["--num_doors_opened_by_host"] << endl;
    cout << "num_simulations: " << args["--num_simulations"] << endl;
	int n,k,num;
	n=args["--num_doors"];
	k=args["--num_doors_opened_by_host"];
	num=args["--num_simulations"];
	simulate(n,k,num);
}
