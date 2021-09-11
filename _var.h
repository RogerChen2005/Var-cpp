#ifndef _VAR_H
#define _VAR_H

#include <cstdio>
#include <string>
#include <iostream>
#include "lint.h"

using namespace std;

#define UNDEFINE 0
#define INT 1
#define CHAR 2
#define STR 3
#define FLOAT 4

class _var{
    private:
        short vtype;
    public:
    _var *pVar;
    void get(_var &a);
    _var(){vtype = UNDEFINE;}
    _var(const int i){vtype = UNDEFINE;*this = i;}
    _var(const char i){vtype = UNDEFINE;*this = i;}
    _var(const char* i){vtype = UNDEFINE;*this = i;}
    _var(const string i){vtype = UNDEFINE;*this = i;}
    _var(const double i){vtype = UNDEFINE;*this = i;}
    virtual void changeType(short i){vtype = i;}
    void add(_var &a);
    virtual void add(int i){throw "Can't Calculate";};
    virtual void add(char i){throw "Can't Calculate";};
    virtual void add(char* i){throw "Can't Calculate";};
    virtual void add(string i){throw "Can't Calculate";};
    virtual void add(double i){throw "Can't Calculate";};
    virtual void minus(int i){throw "Can't Calculate";};
    virtual void minus(char i){throw "Can't Calculate";};
    virtual void minus(char* i){throw "Can't Calculate";};
    virtual void minus(string i){throw "Can't Calculate";};
    virtual void minus(double i){throw "Can't Calculate";};
    virtual void multi(int i){throw "Can't Calculate";};
    virtual void multi(char* i){throw "Can't Calculate";};
    virtual void multi(double i){throw "Can't Calculate";};
    virtual void div(int i){throw "Can't Calculate";};
    virtual void div(char* i){throw "Can't Calculate";};
    virtual void div(double i){throw "Can't Calculate";};
    short getType(){return vtype;}
    virtual int igetValue(){return 0;};
    virtual char cgetValue(){return 0;};
    virtual string sgetValue(){string temp;return temp;};
    virtual double fgetValue(){return 0.0;};
    bool operator = (int a);
    bool operator = (const char &s);
    bool operator = (const char* str);
    bool operator = (const string &str);
    bool operator = (const double &a);
    bool operator = (_var a);
    _var(_var *i);
    void operator += (const int a){this->pVar->add(a);}
    void operator += (const char a){this->pVar->add(a);}
    void operator += (const char* &a){this->pVar->add(a);}
    void operator += (const string a){this->pVar->add(a);}
    void operator += (const double a){this->pVar->add(a);}
    void operator += (_var &a);
    _var operator + (const int a){
        _var temp;
        temp = *this;
        temp += a;
        return temp;
    }
    _var operator + (const char a){
        _var temp;
        temp = *this;
        temp += a;
        return temp;
    }
    _var operator + (const char* a){
        _var temp;
        temp = *this;
        temp += a;
        return temp;
    }
    _var operator + (const string a){
        _var temp;
        temp = *this;
        temp += a;
        return temp;
    }
    _var operator + (const double a){
        _var temp;
        temp = *this;
        temp += a;
        return temp;
    }
    _var operator + (_var a){
        _var temp;
        temp = *this;
        temp += a;
        return temp;
    }
    void operator -= (const int a){this->pVar->minus(a);}
    void operator -= (const char a){this->pVar->minus(a);}
    void operator -= (const char* a){this->pVar->minus(a);}
    void operator -= (const string a){this->pVar->minus(a);}
    void operator -= (const double a){this->pVar->minus(a);}
    void operator -= (_var &a);
    _var operator - (const int a){
        _var temp;
        temp = *this;
        temp -= a;
        return temp;
    }
    _var operator - (const char a){throw "Can't Calculate";};
    _var operator - (const char* a){
        _var temp;
        temp = *this;
        temp -= a;
        return temp;
    }
    _var operator - (const string a){
        _var temp;
        temp = *this;
        temp -= a;
        return temp;
    }
    _var operator - (const double a){
        _var temp;
        temp = *this;
        temp -= a;
        return temp;
    }
    _var operator - (_var a){
        _var temp;
        temp = *this;
        temp -= a;
        return temp;
    }
    void operator *= (const int a){this->pVar->multi(a);}
    void operator *= (const double a){this->pVar->multi(a); }
    void operator *= (_var &a);
    _var operator * (const int a){
        _var temp;
        temp = *this;
        temp *= a;
        return temp;
    }
    _var operator * (const double a){
        _var temp;
        temp = *this;
        temp *= a;
        return temp;
    }
    _var operator * (_var a){
        _var temp;
        temp = *this;
        temp *= a;
        return temp;
    }
    void operator /= (const int a){this->pVar->div(a);}
    void operator /= (const double a){this->pVar->div(a);}
    void operator /= (_var &a);
    _var operator / (const int a){
        _var temp;
        temp = *this;
        temp /= a;
        return temp;
    }
    _var operator / (const double a){
        _var temp;
        temp = *this;
        temp /= a;
        return temp;
    }
    _var operator / (_var a){
        _var temp;
        temp = *this;
        temp /= a;
        return temp;
    }
};

class Int:public _var{
    private:
        int value;
    public:
        int igetValue(){return value;}
        Int(int a){value = a;}
        void add(int i){value += i;}
        void add(double i){value += int(i);}
        void minus(int i){value -= i;}
        void minus(double i){value -= int(i);}
        void multi(int i){value *= i;}
        void multi(double i){value *= i;}
        void div(int i){value /= i;}
        void div(double i){value /= i;}
};

class Char:public _var{
    private:
        char value;
    public:
        Char(char s){value = s;}
        char cgetValue(){return value;}
        void add(int i){value += i;}
        void minus(int i){value -= i;}
};

class Str:public _var{
    private:
        string value;
    public:
        Str(string str){value = str;}
        Str(char* str){value = str;}
        string sgetValue(){return value;}
        void add(string i){value += i;}
        void add(char i){value += i;}
        void add(char* i){value += i;}
        void add(int i){value += to_string(i);}
};

class Float:public _var{
    private:
        double value;
    public:
        Float(double d){value = d;}
        double fgetValue(){return value;}
        void add(double i){value += i;}
        void add(int i){value += i;}
        void minus(int i){value -= i;}
        void minus(double i){value -= i;}
        void multi(int i){value *= i;}
        void multi(double i){value *= i;}
        void div(int i){value /= i;}
        void div(double i){value /= i;}
};

bool _var::operator = (const int a){
    pVar = new Int(a);
    changeType(INT);
    return true;
}

bool _var::operator = (const char &s){
    pVar = new Char(s);
    changeType(CHAR);
    return true;
}

bool _var::operator = (const string &str){
    pVar = new Str(str);
    changeType(STR);
    return true;
}

bool _var::operator = (const char *str){
    pVar = new Str(str);
    changeType(STR);
    return true;
}

bool _var::operator = (const double &d){
    pVar = new Float(d);
    changeType(FLOAT);
    return true;
}

ostream & operator << (ostream& output,_var x) {
    switch (x.getType())
    {
    case UNDEFINE:
        break;
    case INT:
        output << x.pVar->igetValue();
        break;
    case CHAR:
        output << x.pVar->cgetValue();
        break;
    case STR:
        output << x.pVar->sgetValue();
        break;
    case FLOAT:
        output << x.pVar->fgetValue();
        break;
    }
    return output;
}

void _var::operator += (_var &a){
    switch (a.getType())
    {
    case INT:
        this->pVar->add(a.pVar->igetValue());
        break;
    case CHAR:
        this->pVar->add(a.pVar->cgetValue());
        break;
    case STR:
        this->pVar->add(a.pVar->sgetValue());
        break;
    case FLOAT:
        this->pVar->add(a.pVar->fgetValue());
        break;
    default:
        break;
    }
}

void _var::operator -= (_var &a){
    switch (a.getType())
    {
    case INT:
        this->pVar->minus(a.pVar->igetValue());
        break;
    case CHAR:
        this->pVar->minus(a.pVar->cgetValue());
        break;
    case STR:
        this->pVar->minus(a.pVar->sgetValue());
        break;
    case FLOAT:
        this->pVar->minus(a.pVar->fgetValue());
        break;
    default:
        break;
    }
}

bool _var::operator = (_var a){
    switch (a.vtype){
    case INT:
        *this = a.pVar->igetValue();
        break;
    case CHAR:
        *this = a.pVar->cgetValue();
        break;
    case STR:
        *this = a.pVar->sgetValue();
        break;
    case FLOAT:
        *this = a.pVar->fgetValue();
        break;
    default:
        break;
    }
    vtype = a.vtype;
    return true;
}

_var::_var(_var *i){
    switch (i->vtype){
    case INT:
        *this = i->pVar->igetValue();
        break;
    case CHAR:
        *this = i->pVar->cgetValue();
        break;
    case STR:
        *this = i->pVar->sgetValue();
        break;
    case FLOAT:
        *this = i->pVar->fgetValue();
        break;
    default:
        break;
    }
}

void _var::operator *= (_var &a){
    switch (a.getType())
    {
    case INT:
        this->pVar->multi(a.pVar->igetValue());
        break;
    case FLOAT:
        this->pVar->multi(a.pVar->fgetValue());
        break;
    default:
        char str[13] = "RogerChen233";
        this->pVar->multi(str);
        break;
    }
}

void _var::operator /= (_var &a){
    switch (a.getType())
    {
    case INT:
        this->pVar->div(a.pVar->igetValue());
        break;
    case FLOAT:
        this->pVar->div(a.pVar->fgetValue());
        break;
    default:
        char str[13] = "RogerChen233";
        this->pVar->div(str);
        break;
    }
}

#endif