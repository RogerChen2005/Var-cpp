#ifndef VAR_H
#define VAR_H

#include "_var.h"
#include "lint.h"
#include <vector>
#include <map>
#include <cstring>
#include <stdarg.h>

#define _VALUE 0
#define _ARRAY 1

class _array{
    private:
        long long len;
    public:
        vector<_var> value1;
        map<string,_var> value2;
        _array(){
            len = 0;
        }
        long long getLength(){
            return len;
        } 
        void addlen(){
            len++;
        }
};

bool check(char s){
    if(s >= 'a' && s <= 'z'){
        return true;
    }
    else return false;
}

class var{
    private:
        _var value;
        int type;
        _array* pAry;
    public:
        var() { type = _VALUE; pAry = NULL; }
        var(_var a){type = _VALUE;value = a;}
        var(int a){type = _VALUE;value = a;}
        var(char a){type = _VALUE;value = a;}
        var(string a){type = _VALUE;value = a;}
        var(char* a){type = _VALUE;value = a;}
        var(const char* a) { type = _VALUE; value = a; }
        var(double a){type = _VALUE;value = a;}
        var(_array a){type = _ARRAY;pAry = new _array();*pAry = a;}
        _var& operator [] (int pos){
            _var temp;
            while(pAry->getLength() <= pos){
                pAry->value1.push_back(temp);
                pAry->addlen();
            }
            return pAry->value1[pos];
        }
        _var& operator [] (string pos){
            return pAry->value2[pos];
        }
        bool operator = (_array a){
            type = _ARRAY;
            pAry = new _array();
            *pAry = a;
            return true;
        }
        bool operator = (int a){
            if(type == _VALUE){
                value = a;
                return true;
            }
            else{
                throw "This is an array";
                return false;
            }
        }
        bool operator = (L_INT a){
            if(type == _VALUE){
                value = a;
                return true;
            }
            else{
                throw "This is an array";
                return false;
            }
        }
        bool operator = (char a){
            if(type == _VALUE){
                value = a;
                return true;
            }
            else{
                throw "This is an array";
                return false;
            }
        }
        bool operator = (string a){
            if(type == _VALUE){
                value = a;
                return true;
            }
            else{
                throw "This is an array";
                return false;
            }
        }
        bool operator = (char* a){
            if(type == _VALUE){
                value = a;
                return true;
            }
            else{
                throw "This is an array";
                return false;
            }
        }
        bool operator = (double a){
            if(type == _VALUE){
                value = a;
                return true;
            }
            else{
                throw "This is an array";
                return false;
            }
        }
        void operator += (const int a){this->value += a;}
        void operator += (const char a){this->value += a;}
        void operator += (const char* &a){this->value += a;}
        void operator += (const string a){this->value += a;}
        void operator += (const double a){this->value += a;}
        void operator += (var &a){this->value += a.value;}
        var operator + (const int a){
            var temp = this->value;
            temp += a;
            return temp;
        }
        var operator + (const char a){
            var temp = this->value;
            temp += a;
            return temp;
        }
        var operator + (const char* a){
            var temp = this->value;
            temp += a;
            return temp;
        }
        var operator + (const string a){
            var temp = this->value;
            temp += a;
            return temp;
        }
        var operator + (const double a){
            var temp = this->value;
            temp += a;
            return temp;
        }
        var operator + (var a){
            var temp = this->value;
            temp += a;
            return temp;
        }
        void operator -= (const int a){this->value -= a;}
        void operator -= (const char a){this->value -= a;}
        void operator -= (const char* a){this->value -= a;}
        void operator -= (const string a){this->value -= a;}
        void operator -= (const double a){this->value -= a;}
        void operator -= (var &a){this->value -= a.value;}
        var operator - (const int a){
            var temp = this->value;
            temp -= a;
            return temp;
        }
        var operator - (const char a){throw "Can't Calculate";};
        var operator - (const char* a){
            var temp = this->value;
            temp -= a;
            return temp;
        }
        var operator - (const string a){
            var temp = this->value;
            temp -= a;
            return temp;
        }
        var operator - (const double a){
            var temp = this->value;
            temp -= a;
            return temp;
        }
        var operator - (var a){
            var temp = this->value;
            temp -= a;
            return temp;
        }
        void operator *= (const int a){this->value *= a;}
        void operator *= (const double a){ this->value *= a;}
        void operator *= (var &a){this->value *= a.value;}
        var operator * (const int a){
            var temp = this->value;
            temp *= a;
            return temp;
        }
        var operator * (const double a){
            var temp = this->value;
            temp *= a;
            return temp;
        }
        var operator * (var a){
            var temp = this->value;
            temp *= a;
            return temp;
        }
        void operator /= (const int a){this->value /= a;}
        void operator /= (const double a){this->value /= a;}
        void operator /= (var &a){this->value /= a.value;}
        var operator / (const int a){
            var temp = this->value;
            temp /= a;
            return temp;
        }
        var operator / (const double a){
            var temp = this->value;
            temp /= a;
            return temp;
        }
        var operator / (var a){
            var temp = this->value;
            temp /= a;
            return temp;
        }
        friend ostream & operator << (ostream& output,var x);
        friend istream & operator >> (istream& input,var &x);
};

_array Array(){
    _array temp;
    return temp;
}

ostream & operator << (ostream& output,var x){
    if(x.type == _VALUE){
        output << x.value;
    }
    else{
        int length = x.pAry->getLength();
        if(length != 0){
            output << "[";
            for(int i = 0;i < length;i++){
                if(x.pAry->value1[i].getType() != UNDEFINE){
                    output << x.pAry->value1[i] << ",";
                }
            }
            output << "\b \b]" << endl;
        }
        if(!x.pAry->value2.empty()){
            output << "[";
            for(map<string,_var>::iterator i = x.pAry->value2.begin();i != x.pAry->value2.end();i++){
                output << "\"" << i->first << "\" = " << i->second << ",";
            }
            output << "\b \b]";
        }
    }
    return output;
}

istream & operator >> (istream& input,var &x){
    string temp;
    if(x.type == _VALUE){
        input >> temp;
        x.value = temp;
    }
    return input;
}

void input(const char* format,...){
    va_list ap;
    va_start(ap,format);
    var* value = va_arg(ap,var*);
    int len = strlen(format);
    int type;
    for(int i = 0;i < len;i++){
        if(format[i] == '%'){
            i++;
            while(check(format[i] == false)){
                i++;
            }
            switch (format[i])
            {
            case 'd':
                {L_INT dtemp;
                cin >> dtemp;
                *value = dtemp;
                break;}
            case 'f':
                {double ftemp;
                scanf("%f",&ftemp);
                *value = ftemp;
                break;}
            case 's':
                {string stemp;
                cin >> stemp;
                *value = stemp;
                break;}
            case 'c':
                {char ctemp;
                scanf("%c",&ctemp);
                *value = ctemp;
                break;}
            default:
                break;
            }
        }
        value = va_arg(ap,var*);
    }
    va_end(ap);
}

#endif