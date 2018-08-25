//
//  FunctionTable.hpp
//  LeanCPP
//
//  Created by Zhang on 2018/8/25.
//  Copyright © 2018年 HansonStudio. All rights reserved.
//

#ifndef FunctionTable_hpp
#define FunctionTable_hpp

class SymbolTable;

typedef double (*PtrFun)(double);

class FunctionTable
{
public:
    FunctionTable(SymbolTable& tbl);
    ~FunctionTable();
    
    void Init(SymbolTable& tbl);
    unsigned int Size() const
    {
        return size_;
    }
    PtrFun GetFunction(unsigned int id) const
    {
        return pFuns_[id];
    }
private:
    PtrFun* pFuns_;
    unsigned int size_;
};

#endif /* FunctionTable_hpp */
