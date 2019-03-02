#include"TextSimilarity.h"
#include<fstream>
#include<iostream>

using namespace std;

TextSimilarity::TextSimilarity(string dict)
	:DICT(dict)
	,DICT_PATH(dict + "/jieba.dict.utf8")
	,HMM_PATH(dict+"/hmm_model.utf8")
	,USER_DICT_PATH(dict+"/user.dict.utf8")
	,IDF_PATH(dict+"/idf.utf8")
	,STOP_WORD_PATH(dict+"/stop_words.utf8")
	,_maxWordNumber(58)
	,_jieba(DICT_PATH,
		HMM_PATH,
		USER_DICT_PATH,
		IDF_PATH,
		STOP_WORD_PATH)
{
	getStopWordTable(STOP_WORD_PATH.c_str());
}

string TextSimilarity::GBKTOUTF(std::string strGBK)
{
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);

	WCHAR *str1 = new WCHAR[n];

	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);

	int len = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char *str2 = new char[len];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, len, NULL, NULL);
	string temp(str2);
	delete[] str1;
	delete[] str2;

	return temp;
}

string TextSimilarity::UTFTOGBK(string strUTF8) {

	int n = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	WCHAR *str1 = new WCHAR[n];
	MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, str1, n);

	int len = WideCharToMultiByte(CP_ACP, 0, str1, -1, NULL, 0, NULL, NULL);
	char *str2 = new char[len];
	WideCharToMultiByte(CP_ACP, 0, str1, -1, str2, len, NULL, NULL);

	string temp(str2);
	delete[] str1;
	delete[] str2;

	return temp;
}

void TextSimilarity::getStopWordTable(const char* stopWordFile)
{
	ifstream fin(stopWordFile);
	string line;
	while (!fin.eof())
	{
		getline(fin, line);
		_stopWordSet.insert(line);
	}
	fin.close();
}


TextSimilarity::wordFreq TextSimilarity::getWordFreq(const char* filename)
{
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "open file:" << filename << endl;
		return wordFreq();
	}
	string line;
	wordFreq wf;
	
	while (!fin.eof())
	{
		getline(fin, line);
		line = GBKTOUTF(line);
		vector<string> words;

		_jieba.Cut(line, words,true);

		//
		for (const auto &e : words)
		{
			if (_stopWordSet.count(e))
			{
				continue;
			}
			else 
			{
				//unordered_map
				if(wf.count(e))
				{
					wf[e]++;
				}
				else {
					wf[e] = 1;
				}
			}
		}
		fin.close();
	}
	return wf;
}

bool cmpReverse(pair<string, int> lp, pair<string, int> rp)
{
	return lp.second > rp.second;
}

vector<std::pair<std::string, int>> TextSimilarity::sortByValueReverse(TextSimilarity::wordFreq& wf)
{
	//由于unorder_map不能直接用于sort排序，因此拷贝到vector后进行排序
	vector<std::pair<std::string, int>> vec(wf.begin(),wf.end());
	sort(vec.begin(), vec.end(), cmpReverse);
	for (size_t i = 0; i < _maxWordNumber; i++)
	{
		cout << UTFTOGBK(vec[i].first) << vec[i].second << " ";
	}
	cout << endl;
	return vec;
}

void TextSimilarity::selectAimWords(std::vector<std::pair<std::string, int>>& wfvec, wordSet& wset)
{
	int len = wfvec.size();
	int sz = len > _maxWordNumber ? _maxWordNumber : len;
	for (int i=0;i<sz;++i)
	{
		//unordered_set去重功能
		wset.insert(wfvec[i].first);
	}
}


vector<double> TextSimilarity::getOntHot(wordSet& wset, wordFreq& wf)
{
	vector<double> vec;
	for (auto &e :wset)
	{
		if (wf.count(e))
		{
			vec.push_back(wf[e]);
		}
		else
		{
			vec.push_back(0);
		}
	}
	return vec;
}

double TextSimilarity::consine(vector<double>& vect, vector<double>& vect1)
{
	double moudel1 = 0, moudel2 = 0, moudel3 = 0;
	for (size_t i = 0; i < vect.size(); i++)
	{
		moudel1 += vect[i] * vect1[i];
	}
	
	for (size_t i = 0; i < vect.size(); i++)
	{
		moudel2 += pow(vect[i], 2);
	}
	moudel2 = pow(moudel2, 0.5);

	for (size_t i = 0; i < vect1.size(); i++)
	{
		moudel3 += pow(vect1[i], 2);
	}
	moudel3 = pow(moudel3, 0.5);

	return moudel1 / (moudel2*moudel3);
}

//double TextSimilarity::getTextSimilariry(const char* file1, const char* file2)
//{
//	double moudel1;
//
//}

