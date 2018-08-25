//
//  Calc.cpp
//  LeanCPP
//
//  Created by Zhang on 2018/8/25.
//  Copyright © 2018年 HansonStudio. All rights reserved.
//

#include "Calc.hpp"

unsigned int Calc::FindSymbol(const std::string& str) const
{
    return symTbl_.Find(str);
}

unsigned int Calc::AddSymbol(const std::string& str)
{
    return symTbl_.Add(str);
}
