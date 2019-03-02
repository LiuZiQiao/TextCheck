#include "cppjieba/Jieba.hpp"
#include<Windows.h>
using namespace std;

const char* const DICT_PATH = "dict/jieba.dict.utf8";
const char* const HMM_PATH = "dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "dict/user.dict.utf8";
const char* const IDF_PATH = "dict/idf.utf8";
const char* const STOP_WORD_PATH = "dict/stop_words.utf8";	

string GBKTOUTF8(string& strGBK) {
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

string UTF8TOGBK(string& strUTF8) {

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

int main(int argc, char** argv) {
	cppjieba::Jieba jieba(DICT_PATH,
		HMM_PATH,
		USER_DICT_PATH,
		IDF_PATH,
		STOP_WORD_PATH);
	vector<string> words;
	vector<cppjieba::Word> jiebawords;
	string s;
	string result;

	s = "�����������׺��д���";
	cout << s << endl;
	cout << "[demo] Cut With HMM" << endl;
	jieba.Cut(GBKTOUTF8(s), words, true);
	for (auto &e: words)
	{
		cout << UTF8TOGBK(e) << "/";
	}
	cout << endl;

	//cout << limonp::Join(words.begin(), words.end(), "/") << endl;

	//cout << "[demo] Cut Without HMM " << endl;
	//jieba.Cut(s, words, false);
	//cout << limonp::Join(words.begin(), words.end(), "/") << endl;

	//s = "�����������廪��ѧ";
	//cout << s << endl;
	//cout << "[demo] CutAll" << endl;
	//jieba.CutAll(s, words);
	//cout << limonp::Join(words.begin(), words.end(), "/") << endl;

	//s = "С��˶ʿ��ҵ���й���ѧԺ�������������ձ�������ѧ����";
	//cout << s << endl;
	//cout << "[demo] CutForSearch" << endl;
	//jieba.CutForSearch(s, words);
	//cout << limonp::Join(words.begin(), words.end(), "/") << endl;

	//cout << "[demo] Insert User Word" << endl;
	//jieba.Cut("��ĬŮ��", words);
	//cout << limonp::Join(words.begin(), words.end(), "/") << endl;
	//jieba.InsertUserWord("��ĬŮ��");
	//jieba.Cut("��ĬŮ��", words);
	//cout << limonp::Join(words.begin(), words.end(), "/") << endl;

	//cout << "[demo] CutForSearch Word With Offset" << endl;
	//jieba.CutForSearch(s, jiebawords, true);
	//cout << jiebawords << endl;

	//cout << "[demo] Lookup Tag for Single Token" << endl;
	//const int DemoTokenMaxLen = 32;
	//char DemoTokens[][DemoTokenMaxLen] = { "������", "CEO", "123", "��" };
	//vector<pair<string, string> > LookupTagres(sizeof(DemoTokens) / DemoTokenMaxLen);
	//vector<pair<string, string> >::iterator it;
	//for (it = LookupTagres.begin(); it != LookupTagres.end(); it++) {
	//	it->first = DemoTokens[it - LookupTagres.begin()];
	//	it->second = jieba.LookupTag(it->first);
	//}
	//cout << LookupTagres << endl;

	//cout << "[demo] Tagging" << endl;
	//vector<pair<string, string> > tagres;
	//s = "����������ѧԺ�ַ�������רҵ�ġ����ö�ã��Ҿͻ���ְ��н������CEO�����������۷塣";
	//jieba.Tag(s, tagres);
	//cout << s << endl;
	//cout << tagres << endl;

	//cout << "[demo] Keyword Extraction" << endl;
	//const size_t topk = 5;
	//vector<cppjieba::KeywordExtractor::Word> keywordres;
	//jieba.extractor.Extract(s, keywordres, topk);
	//cout << s << endl;
	//cout << keywordres << endl;
	return EXIT_SUCCESS;
}
