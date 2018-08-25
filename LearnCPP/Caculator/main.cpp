//
//  main.cpp
//  LeanCPP
//
//  Created by Zhang Yuanming on 2018/6/23.
//  Copyright © 2018 HansonStudio. All rights reserved.
//

#include <iostream>
#include <string>
#include "Scanner.hpp"
#include "Parser.hpp"
#include "Calc.hpp"

int main(void)
{
    Calc calc;
    STATUS status = STATUS_OK;
    do
    {
        std::cout<<"> ";
        std::string buf;
        std::getline(std::cin, buf);
//        std::cout<<buf<<std::endl;
        Scanner scanner(buf);
        if (!scanner.IsEmpty())
        {
            Parser parser(scanner, calc);
            status = parser.Parse();
            if (status == STATUS_OK)
            {
                std::cout<<parser.Calculate()<<std::endl;
            }
            else
            {
                std::cout<<"Syntax Error."<<std::endl;
            }
        }
        else
        {
            std::cout<<"Expression is empty."<<std::endl;
        }
        
    } while(status != STATUS_QUIT);
    
    return 0;
}
