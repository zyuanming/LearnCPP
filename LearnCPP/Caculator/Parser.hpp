//
//  Parser.hpp
//  LeanCPP
//
//  Created by Zhang Yuanming on 2018/8/3.
//  Copyright © 2018 HansonStudio. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <memory>
// 前向声明
class Scanner;
class Node;
class Calc;

enum STATUS
{
    STATUS_OK,
    STATUS_ERROR,
    STATUS_QUIT
};

/*
 Parser类和Scanner类在这里是关联关系，不是组合关系，否则多一次
 拷贝，效率低一些，因此Parser
 不负责Scanner的生命周期
 
 
 采用递归下降法解析
 
 Expression(表达式) is Term + Expression
 or Term - Expression
 or Term = Expression
 or just Term
 
 Term(项) is Factor * Term
 or Factor / Term
 or just Factor
 
 Factor(因式) is Number
 or Identifier(变量，标识符)
 or Identifier(Expression)
 or -Factor
 or (Expression)
 
 */
class Parser {
public:
    Parser(Scanner& scanner, Calc& calc);
    ~Parser();
    STATUS Parse();
    // 对表达式进行解析
    std::auto_ptr<Node> Expr();
    std::auto_ptr<Node> Term();
    std::auto_ptr<Node> Factor();
    double Calculate() const;
private:
    Scanner& scanner_;  // 这里如果不是引用，就是组合关系了
    Calc& calc_;
    std::auto_ptr<Node> tree_;
    STATUS status_;
};

#endif /* Parser_hpp */
