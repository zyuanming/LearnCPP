//
//  Calc.hpp
//  LeanCPP
//
//  Created by Zhang on 2018/8/25.
//  Copyright © 2018年 HansonStudio. All rights reserved.
//

#ifndef Calc_hpp
#define Calc_hpp

#include <string>
#include "SymbolTable.hpp"
#include "Storage.hpp"
#include "FunctionTable.hpp"

class Parser;

class Calc
{
    friend class Parser;
public:
    Calc() : funTbl_(symTbl_) , storage_(symTbl_) {}
private:
     Storage& GetStorage()
    {
        return storage_;
    }
    PtrFun GetFunction(unsigned int id) const
    {
        return funTbl_.GetFunction(id);
    }
    bool IsFunction(unsigned int id) const
    {
        return id < funTbl_.Size();
    }
    unsigned int AddSymbol(const std::string& str);
    unsigned int FindSymbol(const std::string& str) const;
    SymbolTable symTbl_;
    FunctionTable funTbl_;
    Storage storage_;
};

#endif /* Calc_hpp */
