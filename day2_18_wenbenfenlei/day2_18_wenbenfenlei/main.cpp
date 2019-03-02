#include"TextSimilarity.h"
#include<iostream>
using namespace std;
int main(int argc,char ** argv)
{
	TextSimilarity ts("dict");
	TextSimilarity::wordFreq wf = ts.getWordFreq("test.txt");
	TextSimilarity::wordFreq wf1 = ts.getWordFreq("test1.txt");

	vector<std::pair<std::string, int>> vec = ts.sortByValueReverse(wf);
	vector<std::pair<std::string, int>> vec1 = ts.sortByValueReverse(wf1);
	
	TextSimilarity::wordSet wset;
	ts.selectAimWords(vec, wset);
	ts.selectAimWords(vec1, wset);

	vector<double> vect = ts.getOntHot(wset, wf);
	vector<double> vect1 = ts.getOntHot(wset, wf1);

	for (size_t i = 0; i < vect.size(); i++)
	{
		cout << vect[i] << " ";
	}
	cout << endl;

	for (size_t i = 0; i < vect1.size(); i++)
	{
		cout << vect1[i] << " ";
	}
	cout << endl;

	double cons = ts.consine(vect, vect1);

	cout << cons << endl;
}