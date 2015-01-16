#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]){

	//get commandline arguments
	int n; 						//N 
	double eRTT = 100;			//set initial eRTT 100 from question
	double a=0.125;				//alpha value
	char* filename;
	filename = argv[1];

	//read from file
	ifstream infile;
	infile.open(filename);

	if(!infile.is_open()){
		cout<<"exit"<<endl;
		exit(EXIT_FAILURE);
	}


	//assign values
	
	if(infile.good()){
		infile>>n;
	}
	char cNum[n];				//stores sample rtts as chars
	double arr[n];				//stores sample rtts
	int i=-1;					//to index arr
	//int tmp;
	while(infile.good()){
		//infile>>tmp;
		infile.getline(cNum,256,',');
		arr[i]=atof(cNum);
		i++;
	}
	infile.close();


	//calculate eRTTs iteratively
	for(int j=0;j<n;j++){
		//cout<<"eRTT "<<j<<" is "<<eRTT<<endl;
		eRTT=(1-a)*eRTT+a*arr[j];
		arr[j]=eRTT;
	}


	//print eRTTs
	for(int j=0;j<n;j++){
		if(j!=n-1){
			cout<<setprecision(2)<<fixed<<arr[j]<<", ";
		}else{
			cout<<setprecision(2)<<fixed<<arr[j];
		}
	}
	return 0;


}