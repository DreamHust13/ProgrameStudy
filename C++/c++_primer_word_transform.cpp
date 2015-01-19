/*
	程序功能：
		给定一个string，将它转换为另一个string。
		程序的输入是两个文件。
		第一个文件保存的是一些规则，用来转换第二个文件中的文本。
			每个规则由两部分组成：一个可能出现在输入文件中的单词和一个用来替换它的短语。
			当第一个单词出现在输入中时，就将它转换为对应的短语。
		第二个输入文件包含要转换的文本。

	如果单词转换文件如下：
		brb be right back
		k okay?
		y why
		r are
		u you
		pic picture
		thk thanks!
		18r later
	希望转换的文本为“
		where r u
		y dont u send me a pic
		k thk 18r
	则程序输出应为：
		where are you
		why dont you send me a picture
		okay? thanks! later

*/

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

//buildMap读取转换规则文件，并创建一个map，用于保存每个单词到其转换内容的映射
map<string, string> buildMap(ifstream &map_file)
{
    map<string, string> trans_map;   //保存转换规则
    string key;                      //要转换的单词
	string value;				     //替换后的内容（不一定是单词）
	//读取第一个单词存入key中，行中剩余内容存入value！！！
	while (map_file >> key && getline(map_file, value))
		if (value.size() > 1)        //检查是否有转换规则
        	trans_map[key] = value.substr(1); // 跳过前导空格 
		else
			throw runtime_error("no rule for " + key);
	return trans_map;
}

//word_transform接收两个参数：第一个绑定到单词转换文件，第二个绑定到要转换的文本文件
const string &transform(const string &s, const map<string, string> &m)
{
	// 实际转换工作；程序的核心！！
	auto map_it = m.find(s);
	// 如果单词在转换规则中
	if (map_it != m.cend()) 
		return map_it->second; // 使用替换短语
	else
		return s;              // 否则返回原string
}

 
//管理整个过程，两个参数：第一个参数绑定到单词转换文件，第二个参数绑定到要转换的文本文件
void word_transform(ifstream &map_file, ifstream &input)
{
	auto trans_map = buildMap(map_file); // 保存转换规则

	//输出转换规则
    cout << "Here is our transformation map: \n\n";
	for (auto entry : trans_map)
        cout << "key: "   << entry.first
             << "\tvalue: " << entry.second << endl;
    cout << "\n\n";

	// 对给定文件进行转换
    string text;                    // 保存输入中的每一行
    while (getline(input, text)) 
	{  // 读取一行文本
		istringstream stream(text); // 读取每个单词 //由于没有include相关文件，出过错!!
				
        string word;
        bool firstword = true;      // 控制是否打印空格
        while (stream >> word)
		{
           if (firstword)
               firstword = false;
           else
               cout << " ";  //在单词间打印一个空格
           // transform返回它的第一个参数或其转换后的形式 
           cout << transform(word, trans_map); //打印输出 
        }
        cout << endl;        //完成一行的转换
    }
}

int main(int argc, char **argv)
{
	//C++ Primer ch11.3.6P391
	// 打开并检查两个文件
    if (argc != 3)
        throw runtime_error("wrong number of arguments");

    ifstream map_file(argv[1]); //打开转换规则文件
    if (!map_file)              //检查打开是否成功
        throw runtime_error("no transformation file");
    
    ifstream input(argv[2]);    //打开要转换的文件
    if (!input)                 //检查打开是否成功
        throw runtime_error("no input file");

	word_transform(map_file, input);

    return 0;
}