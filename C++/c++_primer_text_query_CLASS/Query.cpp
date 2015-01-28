#include "Query.h"
#include "TextQuery.h"

#include <memory>
using std::shared_ptr; using std::make_shared;

#include <set>
using std::set;

#include <algorithm>
using std::set_intersection;

#include <iostream>
using std::ostream;

#include <cstddef>
using std::size_t;

#include <iterator>
using std::inserter; 


/*
 * eval函数是整个查询系统的核心
	每个eval函数作用于各自的运算对象，同时遵循的内在逻辑也有所区别：
		OrQuery的eval操作返回两个运算对象查询结果的并集；
		AndQuery返回交集；
		NotQuery的更复杂些：需要返回运算对象没有出现的文本行
*/

// returns the lines not in its operand's result set
QueryResult
NotQuery::eval(const TextQuery& text) const
{
    // virtual call to eval through the Query operand 
    auto result = query.eval(text);

	// start out with an empty result set
    auto ret_lines = make_shared<set<line_no>>();

	// we have to iterate through the lines on which our operand appears
	auto beg = result.begin(), end = result.end();

    // for each line in the input file, if that line is not in result,
    // add that line number to ret_lines
	auto sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n) {
		// if we haven't processed all the lines in result
		// check whether this line is present
		if (beg == end || *beg != n) 
			ret_lines->insert(n);  // if not in result, add this line 
		else if (beg != end) 
			++beg; // otherwise get the next line number in result if there is one
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}

// 返回运算对象查询结果set的交集
QueryResult AndQuery::eval(const TextQuery& text) const
{
    // 通过Query成员lhs和rhs进行的虚调用,以获得运算对象的查询结果set
    auto left = lhs.eval(text), right = rhs.eval(text);

	// 保存left和right交集的set
    auto ret_lines = make_shared<set<line_no>>();  

    // 将两个范围的交集写入一个目的迭代器中
    // 本次调用的目的迭代器向ret添加元素
	//使用的是标准库算法set_intersection
    set_intersection(left.begin(), left.end(), 
                   right.begin(), right.end(),
                   inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}

// 返回运算对象查询结果set的并集
QueryResult OrQuery::eval(const TextQuery& text) const
{
    // 通过Query成员lhs和rhs进行的虚调用
	// 调用eval返回每个运算对象的QueryResult
    auto right = rhs.eval(text), left = lhs.eval(text);  

	// 将左侧运算对象的行号拷贝到结果set中
	auto ret_lines = 
	     make_shared<set<line_no>>(left.begin(), left.end());

	// 插入右侧运算对象所得的行号
	ret_lines->insert(right.begin(), right.end());
	// 返回一个新的QueryResult，它表示lhs和rhs的并集
    return QueryResult(rep(), ret_lines, left.get_file());
	
	/*
	 * QueryResult的构造函数接收三个实参：一个表示查询的string、一个指向匹配行号set的shared_ptr
										  和一个指向输入文件vector的shared_ptr
	*/
}

