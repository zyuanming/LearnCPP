//
//  SymbolTable.hpp
//  LeanCPP
//
//  Created by Zhang on 2018/8/23.
//  Copyright © 2018年 HansonStudio. All rights reserved.
//

#ifndef SymbolTable_hpp
#define SymbolTable_hpp

#include <map>
#include <string>

class SymbolTable
{
public:
    enum { IDNOTFOUND = 0xffffffff };
    SymbolTable() : curId_(0) {}
    unsigned int Add(const std::string& str);
    unsigned int Find(const std::string& str) const;
    void Clear();
    std::string GetSymbolName(unsigned int id) const;
    
private:
    std::map<const std::string, unsigned int> dictionary_;
    unsigned int curId_;
};


#endif /* SymbolTable_hpp */
