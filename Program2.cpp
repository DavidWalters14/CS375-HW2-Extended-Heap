#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;
struct node{
	int id;
	int score;
};

int left(int index){
	return 2*index;
};

int right(int index){
	return (2*index)+1;
};

int parent(int index){
	return index/2;
};
bool isLeaf(int index, vector<node> h){
	if(left(index)>=h.size()){
		return true;
	}
	return false;
}
heapify(vector<node> &h, vector<int> *ha){
	int i = 0;
	if(h.size()%2==0){
		i = (h.size/2)-1;
	}
	else{
		i = h.size/2
	}
	for(i >= 1; i--){
		while(!isLeaf(i,h)){
			int n = left(i);
			if(n+1 < h.size() && h[n].score > h[n+1].score){
				n = right(i);
			}
			if(h[i].score <= h[n].score){}
			else{
				node temp = h[i];
				h[i] = h[n];
				h[n] = temp;
				int temp2 = ha[i];
				ha[i] = ha[n];
				ha[n] = temp;
			}
			i = n;
		}
	}
};

int main(int argc, char** argv){
	ifstream input;
	input.open(argv[1]);
	ofstream output;
	output.open(argv[2]);
	if(!input.is_open()){
		cout << "could not open input file" << endl;
	}
	if(!output.is_open()){
		cout << "could not open output file";
	}
	int size;
	input >> size;
	vector<int> heap;
	vector<int> handle;
	heap.push_back(NULL);
	handle.resize(size+1);
	handle[0]=-1;
	for(int i = 1 ; i < handle.size() ; i++){
		handle[i]=-1;
	}
	string method;
	while(input >> method){
		if(method.compare("insertContestant")==0){
			string id;
			string score;
			input >> id;
			input >> score;
			int index1 = id.find('<');
			int index2 = id.find('>');
			int idnum = (int)id.substr(index1+1,index2);
			int index3 = score.find('<');
			int index4 = score.find('>');
			int scorenum = (int)score.substr(index3+1,index4);
			if(heap.size()+1==size){
				output << "Contestant <" << idnum << "> can not be inserted because the heap is full." << endl;
			}
			else if(handle[idnum]!=-1){
				output << "Contestant <" << idnum << "> is already in the extended heap: cannot insert." << endl;
			}
			else{
				heap.push_back(scorenum);
				heapify(heap, handle);
				output << "Contestant <" << idnum << "> inserted with initial score <" << scorenum << ">." << endl;
			}

		}
		else if(method.compare("showContestants")==0){
			for(int i = 1 ; i < heap.size() ; i++){
				if(handle[i]!=-1){
					output << "Contestant <" << i << "> in extended heap location <" << handle[i] << "> with score of <" << heap[handle[i]].score << ">." << endl;
				}
			}
		}
		else if(method.compare("findContestant")==0){
			string id;
			input >> id;
			int index1 = id.find('<');
			int index2 = id.find('>');
			int idnum = (int)id.substr(index1+1,index2);
			if(handle[idnum]==-1){
				output << "Contestant <" << idnum << "> is not in the extended heap." << endl;
			}
			else{
				output << "Contestant <" << idnum << "> is in the extended heap with score <" << heap[handle[idnum]].score ">." << endl;
			}
		}
		else if(method.compare("eliminateWeakest")==0){
			if(heap.size()==1){
				output << "No contestant can be eliminated since the extended heap is empty." << endl;
			}
			else{
				int id = heap[1].id;
				int score = heap[1].score;
				heap.erase(heap.begin()+1,heap.begin()+2);
				handle[id] = -1;
				heapify(heap,handle);
				output << "Contestant <" << id << "> with current lowest score <" << score << ">. eliminated."
			}
		}
		else if(method.compare("losePoints")==0){
			string id;
			input >> id;
			int index1 = id.find('<');
			int index2 = id.find('>');
			int idnum = (int)id.substr(index1+1,index2);
			string points;
			input >> points;
			int index3 = points.find('<');
			int index4 = points.find('>');
			int scorenum = (int)points.substr(index3+1,index4);
			if(handle[idnum]==-1){
				output << "Contestant <" << idnum << "> is not in the extended heap." << endl;
			}
			else{
				heap[handle[idnum]].score-=scorenum;
				output << "Contestant <" << idnum << ">'s score decreased by <" << scorenum << "> points to <" << heap[handle[idnum]].score << ">." << endl;
				heapify(heap, handle);
			}
		}
		else if(method.compare("earnPoints")==0){
			string id;
			input >> id;
			int index1 = id.find('<');
			int index2 = id.find('>');
			int idnum = (int)id.substr(index1+1,index2);
			string points;
			input >> points;
			int index3 = points.find('<');
			int index4 = points.find('>');
			int scorenum = (int)points.substr(index3+1,index4);
			if(handle[idnum]==-1){
				output << "Contestant <" << idnum << "> is not in the extended heap." << endl;
			}
			else{
				heap[handle[idnum]].score+=scorenum;
				output << "Contestant <" << idnum << ">'s score increased by <" << scorenum << "> points to <" << heap[handle[idnum]].score << ">." << endl;
				heapify(heap, handle);
			}
		}
		else if(method.compare("showHandles")==0){
			
		}
		else if(method.compare("crownWinner")==0){

		}
		else if(method.compare("showLocation")==0){

		}


	}
