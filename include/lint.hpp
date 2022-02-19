#ifndef LINT_H
#define LINT_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cmath>
#include "CBigNum.hpp"

char * itostr(int x,int len){
    char *s = NULL;
    s = (char*)realloc(s,len+1);
    sprintf(s,"%d",x);
    s[len] = 0;
    return s;
}

char * itostr(long long x,int len){
    char *s = NULL;
    s = (char*)realloc(s,len+1);
    sprintf(s,"%lld",x);
    s[len] = 0;
    return s;
}

class L_INT{
    private:
        char* value;
        int length;
        bool posTive;
    public:
        L_INT(){value = NULL;length = 0;posTive = 0;}
        ~L_INT(){
            if(value[0] <= '9' && value[0]>='0'){
                free(value);
            }
            value = NULL;
        }
        L_INT(const L_INT &x){
            length = x.length;
            value = NULL;
            value = (char*)realloc(value,length+1);
            memcpy(value,x.value,length);
            posTive = x.posTive;
            value[length] = 0;
        }
        L_INT(L_INT *x){value = NULL;*this = *x;}
        L_INT(int x){value = NULL;*this = x;}
        L_INT(long long x){value = NULL;*this = x;}
        void SetValue0(){
            value = (char*)realloc(value,sizeof(char) * 2);
            value[0] = '0';value[1] = 0;
            posTive = true;
            length = 1;
        }
        bool operator = (L_INT x){
            length = x.length;
            value = (char*)realloc(value,length+1);
            memcpy(value,x.value,length);
            posTive = x.posTive;
            value[length] = 0;
            return true;
        }
        bool operator = (int x){
            if(x == 0){SetValue0();return true;}
            if(x < 0){
                x = -x;posTive = false;
            }else posTive = true;
            length = log10(x) + 1;
            value = itostr(x,length);
            return true;
        }
        bool operator = (long long x){
            if(x == 0){SetValue0();return true;}
            if(x < 0){
                x = -x;posTive = false;
            }else posTive = true;
            length = log10(x) + 1;
            value = itostr(x,length);
            return true;
        }
        friend std::ostream & operator << (std::ostream & output,L_INT &x);
        friend std::istream & operator >> (std::istream & output,L_INT x);
        friend int comp(L_INT *x,L_INT *y);
        bool operator < (L_INT &y){return comp(this,&y) == _SMALL;}
        bool operator > (L_INT &y){return comp(this,&y) == _BIG;}
        bool operator >= (L_INT &y){return !(comp(this,&y) == _SMALL);}
        bool operator <= (L_INT &y){return !(comp(this,&y) == _BIG);}
        friend void add(L_INT *str1,L_INT *str2);
        L_INT operator + (L_INT &x){L_INT temp;temp = *this;temp += x;return temp;}
        void operator += (L_INT &x);
        L_INT operator - (L_INT &x){L_INT temp = *this;temp -= x;return temp;}
        void operator -= (L_INT &x);
        L_INT operator * (L_INT &x){L_INT temp = *this;temp *= x;return temp;}
        void operator *= (L_INT &x);
        L_INT operator / (L_INT &x){L_INT temp = *this;temp /= x;return temp;}
        void operator /= (L_INT &x);
        L_INT operator % (L_INT &x){L_INT temp = *this;temp %= x;return temp;}
        void operator %= (L_INT &x);
        L_INT operator + (int x){L_INT temp = *this;temp += x;return temp;}
        void operator += (int x){L_INT temp = x;*this += temp;};
        L_INT operator - (int x){L_INT temp = *this;temp -= x;return temp;}
        void operator -= (int x){L_INT temp = x;*this -= temp;};
        L_INT operator * (int x){L_INT temp = *this;temp *= x;return temp;}
        void operator *= (int x){L_INT temp = x;*this *= temp;};
        L_INT operator / (int x){L_INT temp = *this;temp /= x;return temp;}
        void operator /= (int x){L_INT temp = x;*this /= temp;};
        L_INT operator % (int x){L_INT temp = *this;temp %= x;return temp;}
        void operator %= (int x){L_INT temp = x;*this %= temp;};
        L_INT operator + (long long x){L_INT temp = *this;temp += x;return temp;}
        void operator += (long long x){L_INT temp = x;*this += temp;};
        L_INT operator - (long long x){L_INT temp = *this;temp -= x;return temp;}
        void operator -= (long long x){L_INT temp = x;*this -= temp;};
        L_INT operator * (long long x){L_INT temp = *this;temp *= x;return temp;}
        void operator *= (long long x){L_INT temp = x;*this *= temp;};
        L_INT operator / (long long x){L_INT temp = *this;temp /= x;return temp;}
        void operator /= (long long x){L_INT temp = x;*this /= temp;};
        L_INT operator % (long long x){L_INT temp = *this;temp %= x;return temp;}
        void operator %= (long long x){L_INT temp = x;*this %= temp;};
        int toint(){
            if(length > 10){
                return 0x7fffffff;
            }
            int temp = 0;
            return temp;
        }
        std::string tostr(){
            std::string temp;
            if(posTive == false){temp+='-';}
            temp+=value;
            return temp;
        } 
};

void L_INT::operator += (L_INT &x){
    if(this->posTive == x.posTive){
        bignum::add(this->value,this->value,x.value);return;
    }
    else{
        int CHECK = bignum::comp(this->value,this->length,x.value,x.length);
        if(CHECK == _SAME){
            SetValue0();return;
        }
        else if(CHECK == _BIG){
            bignum::sub(this->value,this->value,x.value);return;
        }
        else{
            this->posTive = !this->posTive;
            bignum::sub(this->value,x.value,this->value);return;
        }
    }
    length = strlen(value);
}

void L_INT::operator -= (L_INT &x){
    x.posTive = !x.posTive;
    *this += x;
}

void L_INT::operator *= (L_INT &x){
    if(this->value == "0" || x.value == "0"){
        SetValue0();return;
    }
    this->posTive ^= x.posTive;
    this->posTive = !this->posTive;
    bignum::mul(this->value,this->value,x.value);
    length = strlen(value);
}

void L_INT::operator /= (L_INT &x){
    if(x.value == "0"){
        throw "INFINATE!";
        return;
    }
    if(this->value == "0"){
        SetValue0();return;
    }
    bignum::div(this->value,this->value,x.value);
    this->posTive ^= x.posTive;
    this->posTive = !this->posTive;
    length = strlen(value);
}

void L_INT::operator %= (L_INT &x){
    if(x.value == "0"){
        throw "INFINATE!";
        return;
    }
    if(this->value == "0"||strcmp(x.value,"1") == 0){
        SetValue0();return;
    }
    bignum::sur(this->value,this->value,x.value);
    length = strlen(value);
}

int comp(L_INT *x,L_INT *y){
    if(x->length > y->length){return _BIG;}
    else if(x->length < y->length){return _SMALL;}
    else{for(int i = 0;i < x->length;i++){
        if(x->value[i] == y->value[i]){continue;}
        else if(x->value[i] > y->value[i]){return _BIG;}
        else return _SMALL;
        }}
    return _SAME;
}

std::ostream & operator << (std::ostream & output,L_INT &x){
    if(!x.posTive){output << "-";}
    output << x.value;
    return output;
}

std::istream & operator >> (std::istream & input,L_INT x){
    std::string str;
    input >> str;
    if(str[0] == '-'){
        x.posTive = false;
    }
    str.erase(0,1);
    x.length = str.length();
    x.value = (char*)malloc(x.length);
    memcpy(x.value,str.c_str(),sizeof(char) * x.length);
    return input;
}

#endif