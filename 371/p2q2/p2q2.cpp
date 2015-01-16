#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>


using namespace std;

char exor(char bit0, char bit1){
	//cout<<bit0<<endl<<bit1<<endl;
	if(bit0 == bit1){
		return '0';
	}else{
		return '1';
	}
}


int main(int argc, char* argv[]){

	//get commandline arguments
	char* filename;
	filename = argv[1];

	//read from file
	ifstream infile;
	infile.open(filename);

	if(!infile.is_open()){
		cout<<"exit"<<endl;
		exit(EXIT_FAILURE);
	}

	//stores input from file
	string g,d,r,result;

	//assign values
	if(infile.good()){
		infile>>g;
		infile>>d;
		infile>>r;
		infile.close();
	}

	int g_len = g.length();
	int d_len = d.length();
	int r_len = r.length();
	int result_len = r_len + d_len;

	bool matches=true;
	
	result=d;
	//pad result with 0
	for(int i = 0; i < r_len; i++){
		result.append("0");
	}

	//perform xor
	for(int i = 0;i < d_len; i++){
		if (result[i]=='1'){
			for(int j = 0; j< g_len; j++){
				result[i+j]=exor(result[i+j],g[j]);
			}
		}
	}

	//check for match
	for(int i = r_len-1; i>=0; i--){
		if (r[i]!=result[i+result_len-r_len]){
			matches=false;
		}
	}

	if (matches){
		cout<<"Yes"<<endl;
	}else{
		cout<<"No"<<endl;
	}

	return 0;
}
