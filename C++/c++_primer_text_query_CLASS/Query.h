#ifndef QUERY_H
#define QUERY_H

#include "Version_test.h"
#include "TextQuery.h"
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

//这是一个抽象基类（含纯虚函数），具体的查询类型从中派生，
//所有成员都是private的（因为不希望用户或派生类直接使用Query_base）
class Query_base 
{
    friend class Query; //Query需要调用Query_base的虚函数
protected:
#ifdef TYPE_ALIAS_DECLS
    using line_no = TextQuery::line_no; // 用于eval函数
#else
    typedef TextQuery::line_no line_no; // 用于eval函数
#endif

#ifdef DEFAULT_FCNS
    virtual ~Query_base() = default;
#else
	virtual ~Query_base() { }//受保护的，将（隐式地）在派生类析构函数中使用
#endif
private:
    //eval返回与当前Query匹配的QueryResult		//纯虚函数
    virtual QueryResult eval(const TextQuery&) const = 0; 
    //rep是表示查询的一个string		//纯虚函数
	virtual std::string rep() const = 0;
};

// 这是一个管理Query_base继承体系的接口类：对外提供接口，同时隐藏了Query_base的继承体系
class Query 
{
    // 这些运算符需要访问接受shared_ptr的构造函数，而该函数是私有的
    friend Query operator~(const Query &);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
	// 构建一个新的WordQuery；故要先定义WordQuery类，才能定义接受string的Query构造函数
    Query(const std::string&);  
	

    // 接口函数：调用对应的Query_base操作
    QueryResult eval(const TextQuery &t) const 
                            { return q->eval(t); }
	std::string rep() const { return q->rep(); }//虚调用当前Query所指对象的rep成员
private:
    Query(std::shared_ptr<Query_base> query): q(query) { }
    std::shared_ptr<Query_base> q;
};

//输出运算符
inline std::ostream &operator<<(std::ostream &os, const Query &query) 
{
	// Query::rep通过它的Query_base指针对rep进行了徐调用
	return os << query.rep(); 
}

class WordQuery: public Query_base 
{
    friend class Query; // Query uses the WordQuery constructor
    WordQuery(const std::string &s): query_word(s) { }

    // concrete class: WordQuery defines all inherited pure virtual functions
    QueryResult eval(const TextQuery &t) const
                     { return t.query(query_word); }
	std::string rep() const { return query_word; }
    std::string query_word;   // word for which to search 
};

inline Query::Query(const std::string &s): q(new WordQuery(s)) { }

class NotQuery: public Query_base 
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q) { }

    // concrete class: NotQuery defines all inherited pure virtual functions
	std::string rep() const {return "~(" + query.rep() + ")";}
    QueryResult eval(const TextQuery&) const;
    Query query;
};

class BinaryQuery: public Query_base 
{
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s): 
          lhs(l), rhs(r), opSym(s) { }

    // abstract class: BinaryQuery doesn't define eval 
	std::string rep() const { return "(" + lhs.rep() + " " 
	                                     + opSym + " " 
		                                 + rhs.rep() + ")"; }

    Query lhs, rhs;    // right- and left-hand operands
    std::string opSym; // name of the operator
};
    
class AndQuery: public BinaryQuery 

{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right): 
                        BinaryQuery(left, right, "&") { }

    // concrete class: AndQuery inherits rep and defines the remaining pure virtual
    QueryResult eval(const TextQuery&) const;
};

class OrQuery: public BinaryQuery 
{
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right): 
                BinaryQuery(left, right, "|") { }

    QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

std::ifstream& open_file(std::ifstream&, const std::string&);
TextQuery get_file(int, char**);
bool get_word(std::string&);
bool get_words(std::string&, std::string&);
std::ostream &print(std::ostream&, const QueryResult&);

#endif
