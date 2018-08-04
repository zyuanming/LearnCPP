//
//  Parser.cpp
//  LeanCPP
//
//  Created by Zhang Yuanming on 2018/8/3.
//  Copyright © 2018 HansonStudio. All rights reserved.
//

#include "Parser.hpp"
#include "Scanner.hpp"
#include "Node.hpp"
#include <cassert>
#include <iostream>

Parser::Parser(Scanner& scanner) : scanner_(scanner), tree_(0)
{
    
}

Parser::~Parser()
{
    std::cout<<"Parser deinit.."<<std::endl;
}

void Parser::Parse()
{
    tree_ = Expr();
}

Node* Parser::Expr()
{
    Node* node = Term();
    EToken token = scanner_.Token();
    if (token == TOKEN_PLUS)
    {
        scanner_.Accept();
        Node* nodeRight = Expr();
        node = new AddNode(node, nodeRight);
    }
    else if (token == TOKEN_MINUS)
    {
        scanner_.Accept();
        Node* nodeRight = Expr();
        node = new SubNode(node, nodeRight);
    }
    return node;
}

Node* Parser::Term()
{
    Node* node = Factor();
    EToken token = scanner_.Token();
    if (token == TOKEN_MULTIPLY)
    {
        scanner_.Accept();
        Node* nodeRight = Term();
        node = new MultiplyNode(node, nodeRight);
    }
    else if (token == TOKEN_DIVIDE)
    {
        scanner_.Accept();
        Node* nodeRight = Term();
        node = new DivideNode(node, nodeRight);
    }
    return node;
}

Node* Parser::Factor()
{
    Node* node = 0;
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
            // TODO: throw exception
            std::cout<<"missing right parenthesis"<<std::endl;
            node = 0;
        }
    }
    else if (token == TOKEN_NUMBER)
    {
        node = new NumberNode(scanner_.Number());
        scanner_.Accept();
    }
    else if (token == TOKEN_MINUS)
    {
        scanner_.Accept();
        node = new UMinusNode(Factor());
    }
    else {
        status_ = STATUS_ERROR;
        // TODO: throw exception
        std::cout<<"not a valid expression"<<std::endl;
        node = 0;
    }
    return node;
}

double Parser::Calculate() const
{
//    assert(tree_ != 0);
    if (tree_ == 0) {
        std::cout<<"some thing wrong.."<<std::endl;
        return -1;
    } else {
        return tree_->Calc();
    }
}
