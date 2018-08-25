//
//  Storage.cpp
//  LeanCPP
//
//  Created by Zhang on 2018/8/23.
//  Copyright © 2018年 HansonStudio. All rights reserved.
//

#include "Storage.hpp"
#include "SymbolTable.hpp"
#include <cmath>
#include <iostream>

Storage::Storage(SymbolTable& tbl)
{
    AddConstants(tbl);
}

void Storage::Clear()
{
    cells_.clear();
    inits_.clear();
}

bool Storage::IsInit(unsigned int id) const
{
    return id < cells_.size() && inits_[id];
}

void Storage::AddConstants(SymbolTable& tbl)
{
    std::cout<<"variable list:"<<std::endl;
    unsigned int id = tbl.Add("e");
    AddValue(id, exp(1.0));
    std::cout<<"e = "<<exp(1.0)<<std::endl;
    
    id = tbl.Add("pi");
    AddValue(id, 2.0 * acos(0.0));  // 反余弦 pi = 2 * acos(0)
    std::cout<<"pi = "<<2.0 * acos(0.0)<<std::endl;
}

double Storage::GetValue(unsigned int id) const
{
    assert(id < cells_.size());
    return cells_[id];
}

void Storage::SetValue(unsigned int id, double val)
{
    assert(id < cells_.size());
    if (id < cells_.size()) {
        cells_[id] = val;
        inits_[id] = true;
    } else if (id == cells_.size()) {
        AddValue(id, val);
    }
}

void Storage::AddValue(unsigned int id, double val)
{
    // 我们希望cells_里有多少个元素，size就是多大，如果这里用 cells_.push_back(val);
    // 那么这时cells_的size不一定等于实际元素个数，会大
    cells_.resize(id+1);
    inits_.resize(id+1);
    cells_[id] = val;
    inits_[id] = true;
}
