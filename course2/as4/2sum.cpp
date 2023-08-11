using namespace std;

#include <iostream>
#include <fstream>
#include <unordered_set>
void findSums(unordered_set<long int> numbers){

	int count = 0;
	for(long int t = -10000; t <= 10000; t++){
		for (auto x = numbers.begin(); x != numbers.end(); x++){
			long int y = (t - *x);
			if ((numbers.find(y) != numbers.end()) && (*x != y)){
				count++;	
				break;
		}	
	}


	
	}
	cout << "answer: " << count << endl;
}
int main(){
	unordered_set<long int> numbers;
	ifstream inFile("2sum.txt");
	
	if (!inFile){
		cerr << "Could not open the file" << endl;
		exit(1);
	}

	long int num;

	while(inFile >> num){
		numbers.insert(num);
	}

//	for (const auto &number : numbers) {
//		cout << "num: " << number << endl;
//	}
//
	findSums(numbers);
	return 0;
}
