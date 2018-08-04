//
//  Node.hpp
//  LeanCPP
//
//  Created by Zhang Yuanming on 2018/7/29.
//  Copyright © 2018 HansonStudio. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp
#include <vector>

class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}
private:
    Noncopyable(const Noncopyable&);
    const Noncopyable& operator=(const Noncopyable&);
};


/*
 为了让Node对象实现对象语义，让它继承Noncopyable,让它不能拷贝或者赋值，
 推荐用private继承，因为Node并非是为了继承Noncopyable的接口，不是
 接口继承，而是实现继承
 
 */
class Node: private Noncopyable
{
public:
    virtual double Calc() const = 0;
    virtual ~Node() {};
};


class NumberNode : public Node
{
public:
    NumberNode(double number) : number_(number) {}
    double Calc() const;
private:
    const double number_;
};



class BinaryNode : public Node
{
public:
    BinaryNode(Node* left, Node* right) : left_(left), right_(right) {}
    ~BinaryNode();
protected:
    Node* const left_;
    Node* const right_;
};


class UnaryNode : public Node
{
public:
    UnaryNode(Node* child) : child_(child) {}
    ~UnaryNode();
protected:
    Node* const child_;
};

class AddNode : public BinaryNode
{
public:
    AddNode(Node* left, Node* right) : BinaryNode(left, right) {}
    double Calc() const;
};



class SubNode : public BinaryNode
{
public:
    SubNode(Node* left, Node* right) : BinaryNode(left, right) {}
    double Calc() const;
};



class MultiplyNode : public BinaryNode
{
public:
    MultiplyNode(Node* left, Node* right) : BinaryNode(left, right) {}
    double Calc() const;
};


class DivideNode : public BinaryNode
{
public:
    DivideNode(Node* left, Node* right) : BinaryNode(left, right) {}
    double Calc() const;
};


class UMinusNode : public UnaryNode
{
public:
    UMinusNode(Node* child) : UnaryNode(child) {}
    double Calc() const;
};



class MultipleNode : public Node
{
public:
    MultipleNode(Node* node)
    {
        AppendChild(node, true);
    }
    void AppendChild(Node* node, bool positive)
    {
        childs_.push_back(node);
        positives_.push_back(positive);
    }
    ~MultipleNode();
protected:
    std::vector<Node*> childs_;
    std::vector<bool> positives_;
};


class SumNode: public MultipleNode
{
public:
    SumNode(Node* node) : MultipleNode(node) {}
    double Calc() const;
};


class ProductNode: public MultipleNode
{
public:
    ProductNode(Node* node) : MultipleNode(node) {}
    double Calc() const;
};


#endif /* Node_hpp */
