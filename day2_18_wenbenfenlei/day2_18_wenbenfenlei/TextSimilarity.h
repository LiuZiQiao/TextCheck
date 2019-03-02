#pragma once
#include<cppjieba/Jieba.hpp>
#include<string>
#include<unordered_map>
#include<Windows.h>
#include<vector>
class TextSimilarity
{
public:
	typedef std::unordered_map<std::string, int> wordFreq;
	typedef std::unordered_set<std::string> wordSet;
	TextSimilarity(std::string dict);
//	double getTextSimilariry(const char* file1, const char* file2);
	
	wordFreq getWordFreq(const char* filename);
	std::string GBKTOUTF(std::string strGBK);
	std::string UTFTOGBK(std::string strUTF);
	std::vector<double> getOntHot(wordSet& wset, wordFreq& wf);

	std::vector<std::pair<std::string,int>> sortByValueReverse(wordFreq& wf);
	void selectAimWords(std::vector<std::pair<std::string, int>>& wfvec, wordSet& wset);

	double consine(std::vector<double>& vect, std::vector<double>& vect1);

private:

	void getStopWordTable(const char* stopWordFile);

	std::string DICT;
	std::string DICT_PATH;
	std::string HMM_PATH;
	std::string USER_DICT_PATH;
	std::string IDF_PATH;
	std::string STOP_WORD_PATH;
	cppjieba::Jieba _jieba;
	wordSet _stopWordSet;
	int _maxWordNumber;
};