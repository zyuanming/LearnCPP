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
#include "Exception.hpp"

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
            try {
                status = parser.Parse();
                if (status == STATUS_OK)
                {
                    std::cout<<parser.Calculate()<<std::endl;
                }
            } catch (SyntaxError& se) {
                status = STATUS_QUIT;
                std::cout<<se.what()<<std::endl;
//                std::cout<<se.StackTrace()<<std::endl;
            } catch (Exception& e) {
                status = STATUS_QUIT;
                std::cout<<e.what()<<std::endl;
            } catch (std::bad_alloc& e) {
                status = STATUS_QUIT;
                std::cout<<e.what()<<std::endl;
            } catch(...) {
                status = STATUS_QUIT;
                std::cout<<"Internal error."<<std::endl;
            }
        }
        else
        {
            status = STATUS_QUIT;
            std::cout<<"Expression is empty."<<std::endl;
        }
        
    } while(status != STATUS_QUIT);
    
    return 0;
}
