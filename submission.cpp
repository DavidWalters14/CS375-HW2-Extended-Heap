#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <string.h>


using namespace std;
struct node{
	int id;
	int score;
	bool eliminated = false;
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
	//else if()
	return false;
};
void heapify(vector<node> &h, vector<int> &ha){
	int i = 0;
	if(h.size()%2==0){
		i = (h.size()/2)-1;
	}
	else{
		i = h.size()/2;
	}
	for(;i >= 1; i--){
		while(!isLeaf(i,h)){
			int n = left(i);
			if(n+1 < h.size() && h[n].score > h[n+1].score){
				n = right(i);
			}
			/*if(ha[i]==-1){
				ha[i]=ha[n];
			}*/

			if(h[i].score <= h[n].score){
				//cout << "no op flag" << endl;
				break;
			}
			else{
				node temp = h[i];
				h[i].id = h[n].id;
				h[i].score = h[n].score;
				h[n].id = temp.id;
				h[n].score = temp.score;
				int temp2 = ha[h[i].id];
				ha[h[i].id] = ha[h[n].id];
				ha[h[n].id] = temp2;
			}
			i = n;
			//cout << "i at end of loop" << i << endl;
		}
	}
	for(int i = 1 ; i < h.size() ; i++){
		ha[h[i].id]=i;
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
	vector<node> heap;
	vector<int> handle;
	node nullnode;
	nullnode.id=NULL;
	nullnode.score = NULL;
	heap.push_back(nullnode);
	handle.resize(size+1);
	handle[0]=-1;
	for(int i = 1 ; i < handle.size() ; i++){
		handle[i]=-1;
	}
	string method;
	while(input >> method){
		//cout << method << endl;
		if(method.compare("insertContestant")==0){
			string id;
			string score;
			input >> id;
			input >> score;
			int index1 = id.find('<');
			int index2 = id.find('>');
			int idnum = stoi(id.substr(index1+1,index2));
			//cout << idnum << endl;
			int index3 = score.find('<');
			int index4 = score.find('>');
			int scorenum = stoi(score.substr(index3+1,index4));
			//cout << scorenum << endl;
			output << "insertContestant <" << idnum <<"> <" << scorenum << ">" << endl;

			if(heap.size()>=size){
				//cout << "if flag" << endl;
				output << "Contestant <" << idnum << "> can not be inserted because the heap is full." << endl;

			}
			else if(handle[idnum]!=-1){
				//cout << "else if flag" << endl;
				output << "Contestant <" << idnum << "> is already in the extended heap: cannot insert." << endl;

			}
			else{
				//cout << "else " << endl;
				node temp;
				temp.id = idnum;
				temp.score = scorenum;
				temp.eliminated = false;
				heap.push_back(temp);
				handle.resize(heap.size());
				handle[idnum]=handle.size()-1;

				//cout << "handle size" << handle.size() << endl;
				heapify(heap, handle);
				//cout << "heapify flag" << endl;
				output << "Contestant <" << idnum << "> inserted with initial score <" << scorenum << ">." << endl;

			}
		}
		else if(method.compare("showContestants")==0){
			output << "showContestants" << endl;
			for(int i = 1 ; i < heap.size() ; i++){
					output << "Contestant <" << heap[i].id << "> in extended heap location <" << handle[heap[i].id] << "> with score of <" << heap[i].score << ">." << endl;
			}
		}
		else if(method.compare("findContestant")==0){
			string id;
			input >> id;
			int index1 = id.find('<');
			int index2 = id.find('>');
			int idnum = stoi(id.substr(index1+1,index2));
			output << "findContestant <" << idnum << ">" << endl;
			if(handle[idnum]==-1){
				output << "Contestant <" << idnum << "> is not in the extended heap." << endl;
			}
			else{
				output << "Contestant <" << idnum << "> is in the extended heap with score <" << heap[handle[idnum]].score << ">." << endl;
			}
		}
		else if(method.compare("eliminateWeakest")==0){
			output << "eliminateWeakest" << endl;
			if(heap.size()==1){
				output << "No contestant can be eliminated since the extended heap is empty." << endl;
			}
			else{
				int id = heap[1].id;
				int score = heap[1].score;
				//heap.erase(heap.begin()+1);
				//handle.erase(handle.begin()+1,handle.begin()+2);
				handle[id] = -1;
				heap[1].eliminated = true;
				heap[1] = heap[heap.size()-1];
				handle[heap[1].id]=-1;
				handle[heap.size()-1]=1;
				heap.resize(heap.size()-1);
				heapify(heap,handle);
				//handle[id]=-1;
				output << "Contestant <" << id << "> with current lowest score <" << score << "> eliminated." << endl;
			}
		}
		else if(method.compare("losePoints")==0){
			string id;
			input >> id;
			int index1 = id.find('<');
			int index2 = id.find('>');
			int idnum = stoi(id.substr(index1+1,index2));
			string points;
			input >> points;
			int index3 = points.find('<');
			int index4 = points.find('>');
			int scorenum = stoi(points.substr(index3+1,index4));
			output << "losePoints <" << idnum << "> <" <<scorenum <<">" <<endl;
			//cout << "idnum : " << idnum << " handle[idnum]: " << handle[idnum] << " heap[handle[idnum]].id: " << heap[handle[idnum]].id << " heap[handle[idnum]].score: " << heap[handle[idnum]].score << endl;
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
			int idnum = stoi(id.substr(index1+1,index2));
			string points;
			input >> points;
			int index3 = points.find('<');
			int index4 = points.find('>');
			int scorenum = stoi(points.substr(index3+1,index4));
			output << "earnPoints <" << idnum << "> <" <<scorenum <<">" <<endl;
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
			output << "showHandles" << endl;
			for(int i = 1 ; i < handle.size()+1 ; i++){
				if(handle[i]==-1){
					output << "There is no Contestant <" << i << "> in the extended heap: handle[<" << i <<">]=-1." << endl;
				}
				else if(i==handle.size()){
					output << "There is no Contestant <" << i << "> in the extended heap: handle[<" << i <<">]=-1." << endl;
				}
				else{
					output << "Contestant <" << i << "> stored in the extended heap location <" << handle[i] << ">." << endl;
				}
			}

		}
		else if(method.compare("crownWinner")==0){
			output << "crownWinner" << endl;
			heapify(heap, handle);
			for(int i = heap.size() ; i >= 2 ; i--){
				handle[heap[1].id]=-1;
				heap[1] = heap[heap.size()-1];
				heap.resize(heap.size()-1);
				heapify(heap, handle);
			}
			output << "Contestant <" << heap[1].id << "> wins with score of <" << heap[1].score << ">!" << endl;
		}
		else if(method.compare("showLocation")==0){
			string id;
			input >> id;
			int index1 = id.find('<');
			int index2 = id.find('>');
			int idnum = stoi(id.substr(index1+1,index2));
			int index = handle[idnum];
			output << "showLocation <" << idnum << ">" << endl;
			if(index == -1){
				output << "Contestant <" << idnum << "> stored in the extended heap location <" << handle[idnum] << ">." << endl;
			}
			else{
				output << "Contestant <" << idnum << "> stored in the extended heap location <" << handle[idnum] << ">." << endl;
			}
		}
		//cout << method << endl;
	}
	input.close();
	output.close();
}
