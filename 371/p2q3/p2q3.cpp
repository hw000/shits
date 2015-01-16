#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <queue>
#include <cfloat>
#include <vector>
#define node pair<string,double> // final dist to source
using namespace std;

class Prior{
public: 
	double operator() (const pair<string, double> &p1, const pair<string,double> &p2){
		return p1.second<p2.second;
	}
};


	int n; 									// number of nodes in network
	int n_links;							// number of links
	

	map<string, double> dist; 				// stores the shortest path from source
	map<string, string> pred;		
 	map<string, vector<node> > neighbour;


 	map<string,map<string,map<string,double> > >d_vecs;
 	vector<string> nodes;

string get_path(string n,string source,string path){
	if(n==source){
		return path;
	}else{
		return get_path(pred[n],source,path=pred[n]+"-"+path);
	}
}

void print_path(string source){
	for(int i=1;i<n;i++){
		cout<<nodes[i]<<": "<<get_path(nodes[i],source,"")<<nodes[i]<<" "<<dist[nodes[i]]<<endl;

	}
}

void print_vec(){
	for (int i=0;i<n;i++){
		cout<<"node: "<<nodes[i]<<endl;
		cout<<"------------------------------------------------"<<endl;
		cout<<"  ";
		for(int j=0;j<n;j++){
			cout<<nodes[j]<<"                ";
		}
		cout<<endl;
		for(int j=0;j<n;j++){
			cout<<nodes[j]<<" ";
			for(int k=0;k<n;k++){
				cout<<d_vecs[nodes[i]][nodes[j]][nodes[k]]<< "                ";
			}
			cout<<endl;
		}

	}
}

void link_state(string source){
	priority_queue<node,vector<node>,Prior>Q;
	Q.push(node(source,dist[source]));
	string u,v;
	double w;
	while(!Q.empty()){
		u=Q.top().first;
		Q.pop();

		int size=neighbour[u].size();
		for (int i=0;i<size;i++){
			v=neighbour[u][i].first;
			w=neighbour[u][i].second;
			//cout<<v<<" "<<w<<endl;
			if(dist[v]>dist[u]+w){
				dist[v]=dist[u]+w;
				Q.push(node(v,dist[v]));
				pred[v]=u;
			}
		}

	}

	print_path(source);

}

void distance_vec(){
	//map<string,map<string,map<string,double> > >d_vecs;

	//init n n x n distance vectors

	//node table x from x to x from y to y etc to 0
	for(int i=0; i<n;i++){
		d_vecs[nodes[i]][nodes[i]][nodes[i]]=0;
	}

	//intialize to inf
	for(int i=0; i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<n;k++){
				if(j!=k)
				d_vecs[nodes[i]][nodes[j]][nodes[k]]=999;
			}
		}
	}


	//set init neighbour vals

	//update neighbours
	for(int i=0;i<n;i++){
		int size=neighbour[nodes[i]].size();
		for (int j=0;j<size;j++){
			string n_name=neighbour[nodes[i]][j].first;
			double weight=neighbour[nodes[i]][j].second;
			d_vecs[nodes[i]][nodes[i]][n_name]=weight;
		}
		//neighbour[node[i]][].first
	}

	//iteratively update assume no negative edge costs
	//longest


	for(int k=0;k<n_links-1;k++){
		//print_vec();

		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(i!=j){
					d_vecs[nodes[i]][nodes[j]]=d_vecs[nodes[j]][nodes[j]];
				}
				//d_vecs[node[i]][node[j]]
			}
		}

		for(int i=0;i<n;i++){
			for (int j=0;j<n;j++){
				int size=neighbour[nodes[i]].size();
				for(int h=0;h<size;h++){
					string n_name=neighbour[nodes[i]][h].first;
					double weight=neighbour[nodes[i]][h].second;
						//cost from neighbour to dest		source to neighbour
					if(d_vecs[n_name][n_name][nodes[j]] + d_vecs[nodes[i]][nodes[i]][n_name]< d_vecs[nodes[i]][nodes[i]][nodes[j]]){
						d_vecs[nodes[i]][nodes[i]][nodes[j]]=d_vecs[n_name][n_name][nodes[j]] + d_vecs[nodes[i]][nodes[i]][n_name];
					}
					
				}
			}

		}
	}

}
int main(int argc, char* argv[]){


	char* filename;
	filename = argv[1];

	//read from file
	ifstream infile;
	infile.open(filename);

	if(!infile.is_open()){
		cout<<"exit"<<endl;
		exit(EXIT_FAILURE);
	}
	if(infile.good()){
		infile>>n>>n_links;
	}
	//cout<<"n is "<<n<<" n_links is "<<n_links<<endl;


	string tmp;
	getline(infile, tmp);					//ignore first line

	string source;
	
	string n1,n2;
	double tmp_dist;
	if(infile.good()){

		//load nodes into distance vector
		//fill distance vector
		for(int i = 0; i < n; i++){
			infile>>tmp;
			nodes.push_back(tmp);
			if(dist.empty()){
				source=tmp;
				dist[tmp]=0;

			}else{

				dist[tmp]=DBL_MAX;

			}

		}

		//edges
		//length of links ex length[n1][n2]returns length of link
		while(infile>>n1>>n2>>tmp_dist){

			//store neighbour
			neighbour[n1].push_back(node(n2,tmp_dist));
			neighbour[n2].push_back(node(n1,tmp_dist));
		}


	}
	cout<<"link state"<<endl;
	cout<<"------------------------------------------------"<<endl;
	link_state(source);

	cout<<endl<<endl;

	cout<<"distance vector"<<endl;

	distance_vec();
	cout<<"------------------------------------------------"<<endl<<endl;
	print_vec();
	return 0;
}