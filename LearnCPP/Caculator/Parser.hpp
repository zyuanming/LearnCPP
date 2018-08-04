//
//  Parser.hpp
//  LeanCPP
//
//  Created by Zhang Yuanming on 2018/8/3.
//  Copyright © 2018 HansonStudio. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

// 前向声明
class Scanner;


/*
 Parser类和Scanner类在这里是关联关系，不是组合关系，否则多一次
 拷贝，效率低一些，因此Parser
 不负责Scanner的生命周期
 */
class Parser {
public:
    Parser(Scanner& scanner);
    void Parse();
    double Calculate() const;
private:
    Scanner& scanner_;  // 这里如果不是引用，就是组合关系了
};

#endif /* Parser_hpp */
