#include"TextSimilarity.h"
#include<iostream>
using namespace std;

void Demo(const char* dict, const char* f1, const char* f2)
{

	TextSimilarity ts(dict);
	TextSimilarity::wordFreq wf = ts.getWordFreq(f1);
	TextSimilarity::wordFreq wf1 = ts.getWordFreq(f2);

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

	cout <<f1<<"and "<<f2<<"simiary:  " <<cons << endl;
}


void Usage()
{
	std::cout<<"Please Input dictPath and Two FilePath:" << std::endl;
}

int main(int argc,char ** argv)
{
	if (argc != 4)
	{
		Usage();
	//	exit(0);
	}

	const char* dictpath = argv[1];
	const char* filepath1 = argv[2];
	const char* filepath2 = argv[3];
//	std::cin >> dictpath >> filepath1 >> filepath2;

	//const char*  dictpath = "dict";
	//const char*  filepath1 = "test.txt";
	//const char*  filepath2 = "test1.txt";

	Demo(dictpath,filepath1, filepath1);
	return 0;
}