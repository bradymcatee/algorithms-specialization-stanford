using namespace std;
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

double score(pair<double, double> job){
	return job.first / job.second;
}
bool sortbyscore(const pair<double, double> &a,
		const pair<double, double> &b){
	return (score(a) < score(b));
}


long int subtractionSequence(vector<pair<double, double>> jobs){
	long int sum = 0;
	long int finish = 0;
	//sort jobs by weight	
	sort(jobs.begin(), jobs.end());
	//stable sort jobs by score after they are already sorted by weight
	stable_sort(jobs.begin(), jobs.end(), sortbyscore);
	for (int i = jobs.size() - 1; i >= 0; i--){ 		
		finish += jobs[i].second;
		sum += (jobs[i].first * finish);
	}
		

	return sum;




}
int main(){
	
	vector<pair<double, double>> jobs;
	ifstream inFile("jobs.txt");

	if (!inFile){
		cerr << "Unable to open file" << endl;
		exit(1);
	}

	int numJobs;	

	inFile >> numJobs;
	for (int i = 0; i < numJobs; i++){
		double weight, length;
		inFile >> weight >> length;
		jobs.push_back(make_pair(weight, length));
	}


	
	cout << "Sum from subtraction sequence: " << subtractionSequence(jobs) << endl;

	return 0;
}
