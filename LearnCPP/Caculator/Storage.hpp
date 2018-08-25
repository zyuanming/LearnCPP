//
//  Storage.hpp
//  LeanCPP
//
//  Created by Zhang on 2018/8/23.
//  Copyright © 2018年 HansonStudio. All rights reserved.
//

#ifndef Storage_hpp
#define Storage_hpp

#include <vector>

class SymbolTable;

class Storage
{
public:
    Storage(SymbolTable& tbl);
    void Clear();
    bool IsInit(unsigned int id) const;
    void AddConstants(SymbolTable& tbl);
    double GetValue(unsigned int id) const;
    void SetValue(unsigned int id, double val);
    void AddValue(unsigned int id, double val);
    
private:
    std::vector<double> cells_;
    std::vector<bool> inits_;
};

#endif /* Storage_hpp */
