//
//  Exception.hpp
//  LeanCPP
//
//  Created by Zhang on 2018/8/25.
//  Copyright © 2018年 HansonStudio. All rights reserved.
//

#ifndef Exception_hpp
#define Exception_hpp

#include <exception>
#include <string>

class Exception: public std::exception
{
public:
    explicit Exception(const char* message) : message_(message)
    {
        FillStackTrace();
    }
    
    virtual ~Exception()
    {
        
    }
    virtual const char* what() const throw();
    const char* StackTrace() const throw();
    void FillStackTrace();
private:
    std::string message_;
    std::string stackTrace_;
};

class SyntaxError : public Exception
{
public:
    explicit SyntaxError(const char* message) : Exception(message)
    {
        
    }
    virtual ~SyntaxError() throw()
    {
        
    }
};

#endif /* Exception_hpp */
