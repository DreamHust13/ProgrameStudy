/*
	文本查询程序：
		实现单词查询、逻辑非查询、逻辑或查询、逻辑与查询
*/
#include "Query.h"
#include "TextQuery.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using std::set;
using std::string;
using std::map;
using std::vector;
using std::cerr;
using std::cout;
using std::cin;
using std::ifstream;
using std::endl;

int main(int argc, char **argv)
{
	//C++ Primer ch15.9 P562
    TextQuery file = get_file(argc, argv);

    // 用户重复输入: 提示输入并打印结果
    do {
        string sought;
        if (!get_word(sought)) break;

        // 找到所有要求出现的string
        // define synonym for the line_no set 
        Query name(sought);
        const auto results = name.eval(file);
        cout << "\nExecuting Query for: " << name << endl;

        // 报告没有匹配结果
        print(cout, results) << endl;
    } while (true);  // loop indefinitely; the exit is inside the loop
    return 0;
}
