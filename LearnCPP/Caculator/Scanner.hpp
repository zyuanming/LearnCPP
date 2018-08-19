//
//  Scanner.hpp
//  LeanCPP
//
//  Created by Zhang Yuanming on 2018/8/3.
//  Copyright © 2018 HansonStudio. All rights reserved.
//

#ifndef Scanner_hpp
#define Scanner_hpp
#include <string>

enum EToken
{
    TOKEN_END,
    TOKEN_ERROR,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPARENTHESIS,
    TOKEN_RPARENTHESIS,
    TOKEN_IDENTIFIER,
    TOKEN_ASSIGN
};

class Scanner {
public:
    Scanner(const std::string& buf);
    ~Scanner();
    void Accept();
    bool IsEmpty() const;
    bool IsDone() const;
    double Number() const;
    EToken Token() const;
private:
    void SkipWhite();
    const std::string buf_;
    unsigned int curPos_;
    EToken token_;
    double number_;
    bool isEmpty_;
};

#endif /* Scanner_hpp */
