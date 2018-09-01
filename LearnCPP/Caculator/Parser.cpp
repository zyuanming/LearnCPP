//
//  Parser.cpp
//  LeanCPP
//
//  Created by Zhang Yuanming on 2018/8/3.
//  Copyright © 2018 HansonStudio. All rights reserved.
//

#include <cassert>
#include <iostream>
#include "Parser.hpp"
#include "Scanner.hpp"
#include "Calc.hpp"
#include "Node.hpp"
#include "Exception.hpp"
#include "Debug.hpp"


Parser::Parser(Scanner& scanner, Calc& calc) : scanner_(scanner), calc_(calc), tree_(0), status_(STATUS_OK)
{
    
}

Parser::~Parser()
{

}

STATUS Parser::Parse()
{
    tree_ = Expr();
    if (!scanner_.IsDone())
    {
        status_ = STATUS_ERROR;
    }
    return status_;
}

std::auto_ptr<Node> Parser::Expr()
{
    std::auto_ptr<Node> node = Term();
    EToken token = scanner_.Token();
    
    
//    if (token == TOKEN_PLUS)
//    {
//        scanner_.Accept();
//        Node* nodeRight = Expr();
//        node = new AddNode(node, nodeRight);
//    }
//    else if (token == TOKEN_MINUS)
//    {
//        scanner_.Accept();
//        Node* nodeRight = Expr();
//        node = new SubNode(node, nodeRight);
//    }
    
    
    if (token == TOKEN_PLUS || token == TOKEN_MINUS)
    {
//        MultipleNode* multipleNode = new SumNode(node);
        std::auto_ptr<MultipleNode> multipleNode(new SumNode(node));
        do
        {
            scanner_.Accept();
            std::auto_ptr<Node> nextNode = Term();
            multipleNode->AppendChild(nextNode, token == TOKEN_PLUS);
            token = scanner_.Token();
        } while(token == TOKEN_PLUS || token == TOKEN_MINUS);
        
        node = multipleNode;
    }
    else if (token == TOKEN_ASSIGN)
    {
        // Expr := Term = Expr
        scanner_.Accept();
        std::auto_ptr<Node> nodeRight = Expr();
        if (node->IsLvalue()) {
            node = std::auto_ptr<Node>(new AssignNode(node, nodeRight));
        } else {
            status_ = STATUS_ERROR;
//            std::cout<<"The left-hand side of an assignment must be a variable"<<std::endl;
            // TODO throw exception
            throw SyntaxError("The left-hand side of an assignment must be a variable.");
        }
    }
    
    return node;
}

std::auto_ptr<Node> Parser::Term()
{
    std::auto_ptr<Node> node = Factor();
    EToken token = scanner_.Token();
//    if (token == TOKEN_MULTIPLY)
//    {
//        scanner_.Accept();
//        Node* nodeRight = Term();
//        node = new MultiplyNode(node, nodeRight);
//    }
//    else if (token == TOKEN_DIVIDE)
//    {
//        scanner_.Accept();
//        Node* nodeRight = Term();
//        node = new DivideNode(node, nodeRight);
//    }
    
    if (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE)
    {
//        MultipleNode* multipleNode = new ProductNode(node);
        std::auto_ptr<MultipleNode> multipleNode(new ProductNode(node));
        
        do
        {
            scanner_.Accept();
            std::auto_ptr<Node> nextNode = Factor();
            multipleNode->AppendChild(nextNode, token == TOKEN_MULTIPLY);
            token = scanner_.Token();
        } while(token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE);
        
        node = multipleNode;
    }
    
    
    return node;
}

std::auto_ptr<Node> Parser::Factor()
{
    std::auto_ptr<Node> node;
    EToken token = scanner_.Token();
    if (token == TOKEN_LPARENTHESIS)
    {
        scanner_.Accept();
        node = Expr();
        if (scanner_.Token() == TOKEN_RPARENTHESIS)
        {
            scanner_.Accept();
        }
        else
        {
            status_ = STATUS_ERROR;
            throw SyntaxError("Missing right parenthesis.");
        }
    }
    else if (token == TOKEN_NUMBER)
    {
        node = std::auto_ptr<Node>(new NumberNode(scanner_.Number()));
        scanner_.Accept();
    }
    else if (token == TOKEN_IDENTIFIER)
    {
        std::string symbol = scanner_.GetSymbol();
        unsigned int id = calc_.FindSymbol(symbol);
        scanner_.Accept();
        
        if (scanner_.Token() == TOKEN_LPARENTHESIS) {
            scanner_.Accept();
            node = Expr();
            if (scanner_.Token() == TOKEN_RPARENTHESIS)
            {
                scanner_.Accept();
                
                if (id != SymbolTable::IDNOTFOUND && calc_.IsFunction(id))
                {
                    node = std::auto_ptr<Node>(new FunctionNode(node, calc_.GetFunction(id)));
                }
                else
                {
                    status_ = STATUS_ERROR;
                    char buf[256] = {0};
                    sprintf(buf, "Unknown function \"%s\".", symbol.c_str());
                    throw SyntaxError(buf);
                }
            }
            else
            {
                status_ = STATUS_ERROR;
                throw SyntaxError("Missing parenthesis in a function call.");
            }
        } else {
            
            if (id == SymbolTable::IDNOTFOUND)
            {
                id = calc_.AddSymbol(symbol);
            }
            
            node = std::auto_ptr<Node>(new VariableNode(id, calc_.GetStorage()));
        }
    }
    else if (token == TOKEN_MINUS)
    {
        scanner_.Accept();
        // if write : std::auto_ptr<Node>(new UMinusNode(Factor()));
        // will compile error.
        // i have no idea why.
        std::auto_ptr<Node> tmpNode = Factor();
        node = std::auto_ptr<Node>(new UMinusNode(tmpNode));
    }
    else {
        status_ = STATUS_ERROR;
        throw SyntaxError("Not a valid expression.");
    }
    return node;
}

double Parser::Calculate() const
{
//    assert(tree_ != 0);
    if (tree_.get() == 0) {
        std::cout<<"some thing wrong.."<<std::endl;
        return -1;
    } else {
        return tree_->Calc();
    }
}
