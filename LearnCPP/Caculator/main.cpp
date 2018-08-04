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

int main(void)
{
    STATUS status = STATUS_OK;
    do
    {
        std::cout<<"> ";
        std::string buf;
        std::getline(std::cin, buf);
//        std::cout<<buf<<std::endl;
        Scanner scanner(buf);
        Parser parser(scanner);
        parser.Parse();
        std::cout<<parser.Calculate()<<std::endl;
    } while(status != STATUS_QUIT);
    
    return 0;
}
