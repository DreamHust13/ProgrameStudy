/*
	程序功能：
		允许用户在给定文件中查询单词。查询结果是单词在文件中出现的次数及其所在行的列表。
		若给定单词在一行中出现多次，此行只列出一次。
		行会按照升序输出。
		
	!!!看的并不够深刻，还有待再看再学习
	C++ Primer ch12.3 p430
*/
#include "stdafx.h"
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>

#include <cstddef>
#include <cctype>
#include <cstring>
#include <utility>
using namespace std;
/*
	***********TestResult.h**************
*/
class QueryResult
{
	friend ostream& print(ostream&, const QueryResult&);
public:
	typedef vector<string>::size_type line_no;
	typedef set<line_no>::const_iterator line_it;
	QueryResult(string s,shared_ptr<set<line_no>> p,shared_ptr<vector<string>> f):
		sought(s), lines(p), file(f) { }
	set<line_no>::size_type size() const
	{
		return lines->size();
	}
	line_it begin() const
	{
		return lines->cbegin();
	}
	line_it end() const
	{
		return lines->cend();
	}
	shared_ptr<vector<string>> get_file()
	{
		return file;
	}
private:
	string sought;					//查询单词
	shared_ptr<set<line_no>> lines; //出现的行号
	shared_ptr<vector<string>> file;//输入文件
};

ostream &print(ostream&, const QueryResult&);
/*
	end ***********TestResult.h**************
*/


/*
	***********TestQurey.h**************
	注：头文件中不应包括using声明，所以，都该加上std::
*/
class QueryResult;	//为定义函数query的返回类型，这个定义是必须的

class TextQuery    //类名写错，找了好久的原因!!
{
public:
	typedef vector<string>::size_type line_no ; //!!!
	TextQuery(ifstream& is);//

	QueryResult query(const string&) const;
	void display_map();      //调试帮助：打印map
private:
	shared_ptr<vector<string>> file; //输入文本；两类的共享数据
	//每个单词到它所在的行号的集合的映射
	map<string,shared_ptr<set<line_no>>> wm;
	static string cleanup_str(const std::string&);
};
/*
	end ***********TestQurey.h**************
*/

/*
	***********make_plura.h**************
*/
//如果ctr大于1，返回复数形式
inline string make_plural(size_t ctr, const string &word,
                          const string &ending)
{
	return (ctr > 1) ? word + ending : word;
}
/*
	end***********make_plura.h**************
*/

//读取输入文件并建立单词到行号的映射
TextQuery::TextQuery(ifstream &is): file(new vector<string>)
{
	string text;
	while(getline(is,text))
	{
		//对文件中每一行
		file->push_back(text);		//保存此行文本
		int n = file->size()-1;    //当前行号
		istringstream line(text);	//将行文本分解为单词
		string word;
		while(line >> word)			//对行中的每个单词
		{
			//如果单词不在wm中，以之下标在wm中添加一项
			auto &lines = wm[word];    //lines是一个shared_ptr
			if(!lines)                 //当我们第一次遇到此单此时，此指针为空
				lines.reset(new set<line_no>); //分配一个新的set
			lines->insert(n);			//将此行号插入set中
		}
	}
}


string TextQuery::cleanup_str(const string &word)
{
	string ret;
	for (auto it = word.begin(); it != word.end(); ++it)
	{
		if (!ispunct(*it))
			ret += tolower(*it);
	}
	return ret;
}

QueryResult TextQuery::query(const string &sought) const
{
	// 如果未找到sought，我们将返回一个指向此set的指针
	static shared_ptr<set<line_no>> nodata(new set<line_no>);

	// 使用find而不是下标运算符来查找单词，避免将单词添加到wm中！
	auto loc = wm.find(cleanup_str(sought));

	if (loc == wm.end())
		return QueryResult(sought, nodata, file);  //未找到
	else
		return QueryResult(sought, loc->second, file);
}

ostream &print(ostream & os, const QueryResult &qr)
{
	// 如果找到了单词，打印出现次数和所有出现的位置
	os << qr.sought << " occurs " << qr.lines->size() << " "
	   << make_plural(qr.lines->size(), "time", "s") << endl;

	//打印单词出现的每一行
for (auto num : *qr.lines) //对set中每个单词
		// 避免行号从0开始给用户带来的困惑
		os << "\t(line " << num + 1 << ") "
		   << *(qr.file->begin() + num) << endl;

	return os;
}

// debugging routine, not covered in the book
void TextQuery::display_map()
{
	auto iter = wm.cbegin(), iter_end = wm.cend();

	// for each word in the map
	for ( ; iter != iter_end; ++iter)
	{
		cout << "word: " << iter->first << " {";

		// fetch location vector as a const reference to avoid copying it
		auto text_locs = iter->second;
		auto loc_iter = text_locs->cbegin(),
		     loc_iter_end = text_locs->cend();

		// print all line numbers for this word
		while (loc_iter != loc_iter_end)
		{
			cout << *loc_iter;

			if (++loc_iter != loc_iter_end)
				cout << ", ";

		}

		cout << "}\n";  // end list of output this word
	}
	cout << endl;  // finished printing entire map
}
/*
	end***********TestQurey.cpp**************
*/

/*
	***********querymain.cpp**************
*/
void runQueries(ifstream &infile)
{
	//infile是一个ifstream，指向我们要处理的文件
	TextQuery tq(infile);			//保存文件并建立查询map
	//与用户交互：提示用户输入要查询的单词，完成查询并打印结果
	while(true)
	{
		cout << "enter word to look for,or q to quit:";
		string s;
		//当遇到文件尾或用户输入了'q'时循环终止
		if(!(cin>>s) || s=="q")
			break;
		print(cout,tq.query(s)) << endl;
	}
}


// program takes single argument specifying the file to query
int main(int argc, char **argv)
{
	// open the file from which user will query words
	ifstream infile;
	// open returns void, so we use the comma operator XREF(commaOp)
	// to check the state of infile after the open
	if (argc < 2 || !(infile.open(argv[1]), infile))
	{
		cerr << "No input file!" << endl;
		return EXIT_FAILURE;
	}
	runQueries(infile);
	return 0;
}
/*
	end***********querymain.cpp**************
*/
