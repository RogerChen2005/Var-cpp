#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
#include <stdarg.h>

#ifndef CBIGNUM_H
#define CBIGNUM_H

#define _BIG 1
#define _SAME 0
#define _SMALL -1

namespace bignum{

int max(int x,int y){
    return x > y ? x : y;
}

void itostr(char* Dest,int x){
    sprintf(Dest,"%d",x);
}

int comp(char* x,char* y){
    int len1 = strlen(x), len2 = strlen(y);
    if(len1 > len2){return _BIG;}
    else if(len1 < len2){return _SMALL;}
    else{
        for(int i = 0;i < len1;i++){
            if(x[i] == y[i]){continue;}
            else if(x[i] > y[i]){return _BIG;}
            else return _SMALL;
        }
    }
    return _SAME;
}

int comp(char*x,int lenx,char*y,int leny){
    if(lenx > leny){return _BIG;}
    else if(lenx < leny){return _SMALL;}
    else{
        for(int i = 0;i < lenx;i++){
            if(x[i] == y[i]){continue;}
            else if(x[i] > y[i]){return _BIG;}
            else return _SMALL;
        }
    }
    return _SAME;
}

void add(char *Dest,char *str1,char *str2){ //只能正数相加
    int len1=strlen(str1);
    int len2=strlen(str2);
    int need = max(len1,len2)+2;
    char *str = new char[need];
    memset(str,'0',need);
    str[need-1] = 0;
    int temp = 0,cf = 0,cnt = max(len1,len2);
    for(int i=len1-1,j = len2 -1;i>=0||j>=0;i--,j--){
        temp = cf;
        if(i >= 0){temp += str1[i] - '0';}
        if(j >= 0){temp += str2[j] - '0';}
        cf=temp/10;
        temp %= 10;
        str[cnt]=char(temp+'0');cnt--;
    }
    if(cf!=0)  str[cnt]=char(cf+'0');
    int pos = 0;
    while(str[pos] == '0'){
        pos++;
    }
    Dest = (char*)realloc(Dest, sizeof(char)*(max(len1,len2) + 2));
    int length = strlen(str) - pos;
    memcpy(Dest,str + pos,length);
    delete[] str;
    Dest[length] = 0;
}

void add_NOfree(char *Dest,char *str1,char *str2){ //需要保证空间充足
    int len1=strlen(str1);
    int len2=strlen(str2);
    int need = max(len1,len2)+2;
    char *str = new char[need];
    memset(str,'0',need);
    str[need - 1] = 0;
    int temp = 0,cf = 0,cnt = max(len1,len2);
    for(int i=len1-1,j = len2 -1;i>=0||j>=0;i--,j--){
        temp = cf;
        if(i >= 0){temp += str1[i] - '0';}
        if(j >= 0){temp += str2[j] - '0';}
        cf=temp/10;
        temp %= 10;
        str[cnt]=char(temp+'0');cnt--;
    }
    if(cf!=0)  str[cnt]=char(cf+'0');
    int pos = 0;
    while(str[pos] == '0'){
        pos++;
    }
    int length = strlen(str) - pos;
    memcpy(Dest,str + pos,length);
    delete str;
    Dest[length] = 0;
}

void sub(char* Dest,char* str1,char* str2){//只能大数减小数
    int len1 = strlen(str1),len2 = strlen(str2);
    char *str = new char[len1 + 1];
    memset(str,'0',len1 + 1);
    str[len1] = 0;
    int tmp = len1-len2;
    int cf = 0,cnt = len1 - 1,pos = 0;
    for(int i=len2-1;i>=0;i--){
        if(str1[tmp+i]<str2[i]+cf){
            str[cnt]=char(str1[tmp+i]-str2[i]-cf+'0'+10);cnt--;
            cf=1;
        }
        else{
            str[cnt]=char(str1[tmp+i]-str2[i]-cf+'0');cnt--;
            cf=0;
        }
    }
    for(int i=tmp-1;i>=0;i--){
        if(str1[i]-cf>='0'){
            str[cnt]=char(str1[i]-cf);cnt--;
            cf=0;
        }else{
            str[cnt]=char(str1[i]-cf+10);cnt--;
            cf=1;
        }
    }
    while(str[pos] == '0'){
        pos++;
    }
    Dest = (char*)realloc(Dest,len1+1);
    int length = strlen(str) - pos;
    memcpy(Dest,str + pos,length);
    delete str;
    Dest[length] = 0;
}

void sub_NOfree(char* Dest,char* str1,char* str2){//需要保证空间充足
    int len1 = strlen(str1),len2 = strlen(str2);
    char *str = new char[len1 + 1];
    memset(str,'0',len1 + 1);
    str[len1] = 0;
    int tmp = len1-len2;
    int cf = 0,cnt = len1-1,pos = 0;
    for(int i=len2-1;i>=0;i--){
        if(str1[tmp+i]<str2[i]+cf){
            str[cnt]=char(str1[tmp+i]-str2[i]-cf+'0'+10);cnt--;
            cf=1;
        }
        else{
            str[cnt]=char(str1[tmp+i]-str2[i]-cf+'0');cnt--;
            cf=0;
        }
    }
    for(int i=tmp-1;i>=0;i--){
        if(str1[i]-cf>='0'){
            str[cnt]=char(str1[i]-cf);cnt--;
            cf=0;
        }else{
            str[cnt]=char(str1[i]-cf+10);cnt--;
            cf=1;
        }
    }
    while(str[pos] == '0'){
        pos++;
    }
    int length = strlen(str) - pos;
    memcpy(Dest,str + pos,length);
    delete[] str;
    Dest[length] = 0;
}

void mul(char* Dest,char* str1,char* str2){ //两个正数相乘
    int len1=strlen(str1),len2=strlen(str2),pos = 0;
    char *str = new char[len1 + len2+1];
    memset(str,'0',len1 + len2+1);
    str[len1 + len2] = 0;
    char *tempstr = new char[len1 + len2 + 2];
    for(int i = len2 - 1;i >= 0;i--){
        int cnt = len1;
        memset(tempstr,'0',len1 + len2-i+1);
        int temp=str2[i]-'0',t=0,cf=0;
        tempstr[len1+len2-i] = 0;
        if(temp!=0){
            for(int j=len1-1;j>=0;j--){
                t=(temp*(str1[j]-'0')+cf)%10;
                cf=(temp*(str1[j]-'0')+cf)/10;
                tempstr[cnt]=char(t+'0');cnt--;
            }
            if(cf!=0) tempstr[cnt]=char(cf+'0');cnt--;
        }
        add_NOfree(str,str,tempstr);
    }
    while(str[pos] == '0'){
        pos++;
    }
    Dest = (char*)realloc(Dest,sizeof(char)*(len1 + len2 + 1));
    int length = strlen(str) - pos;
    memcpy(Dest,str + pos,length);
    delete[] str;
    delete[] tempstr;
    Dest[length] = 0;
}

void mul_NOfree(char* Dest,char* str1,char* str2){ //两个正数相乘
    int len1=strlen(str1),len2=strlen(str2),pos = 0;
    char *str = new char[len1 + len2+1];
    memset(str,'0',len1 + len2+1);
    str[len1 + len2] = 0;
    char *tempstr = new char[len1 + len2 + 2];
    for(int i = len2 - 1;i >= 0;i--){
        int cnt = len1;
        memset(tempstr,'0',len1 + len2-i+1);
        int temp=str2[i]-'0',t=0,cf=0;
        tempstr[len1+len2-i] = 0;
        if(temp!=0){
            for(int j=len1-1;j>=0;j--){
                t=(temp*(str1[j]-'0')+cf)%10;
                cf=(temp*(str1[j]-'0')+cf)/10;
                tempstr[cnt]=char(t+'0');cnt--;
            }
            if(cf!=0) tempstr[cnt]=char(cf+'0');cnt--;
        }
        add_NOfree(str,str,tempstr);
    }
    while(str[pos] == '0'){
        pos++;
    }
    int length = strlen(str) - pos;
    memcpy(Dest,str + pos,length);
    delete[] str;
    delete[] tempstr;
    Dest[length] = 0;
}

void div(char* Dest,char* str1,char* str2){
    int len1 = strlen(str1),len2 = strlen(str2);
    if(comp(str1,len1,str2,len2) == _SMALL){
        Dest = (char*)realloc(Dest,sizeof(char)*2);
        Dest[0] = '0';Dest[1] = 0;
        return;
    }
    char* ans = new char[len1+3],*yu = new char[len2+3];
    char* str = new char[len2+3],*temp = new char[len2+3];
    memset(ans,0,sizeof(ans));
    memset(yu,0,sizeof(yu));
    memset(str,0,sizeof(str));
    memset(temp,0,sizeof(temp));
    int cnt = 0,ans_cur = 0,temp_cur = 0;
    while(cnt <= len1 - 1){
        int ylen = strlen(yu);
        memcpy(temp,yu,ylen);temp[ylen] = 0;temp_cur = ylen;
        bool flag = false,jie = false,first = false;
        for(int i = 0;i < len2 - ylen;i++){
            jie = true;
            if(cnt > len1 - 1){
                ans[ans_cur] = '0';ans_cur++;
                flag = true;
                break;
            }
            temp[temp_cur] = str1[cnt];temp_cur++;temp[temp_cur] = 0;
            if(first){
                ans[ans_cur] = '0';ans_cur++;
            }
            else first = true;
            cnt++;
        }
        if(flag){
            break;
        }
        int f1 = str2[0] - '0',f2 = temp[0] - '0';
        if(f1 > f2 || comp(str2,temp) == _BIG){
            if(cnt > len1 - 1){
                int leng = strlen(temp);
                ans[ans_cur] = '0';ans_cur++;
                break;
            }
            if(jie){ans[ans_cur] = '0';ans_cur++;}
            temp[temp_cur] = str1[cnt];temp_cur++;temp[temp_cur] = 0;
            f2 = f2 * 10 + temp[1] - '0';
            cnt++;
        }
        int s = f2 / f1;
        while(true){
            char ss[3];
            sprintf(ss,"%d",s);
            mul_NOfree(str,str2,ss);
            if(comp(temp,str) == _SMALL){
                s -= 1;
                continue;
            }
            else{
                sub_NOfree(yu,temp,str);
                if(comp(str2,yu) == _BIG){
                    break;
                }
            }
        }
        ans[ans_cur] = char(s + '0');ans_cur++;
        if(yu[0] == '0'){
            while(str1[cnt] == '0'){
                cnt++;
                ans[ans_cur] = '0';ans_cur++;
            }
        }
    }
    int pos = 0;
    while(ans[pos] == '0'){
        pos++;
    }
    Dest = (char*)realloc(Dest,sizeof(char)*(len1 + 3));
    int length = strlen(ans) - pos;
    memcpy(Dest,ans + pos,length);
    delete[] str;
    delete[] ans;
    delete[] yu;
    delete[] temp;
    Dest[length] = 0;
}

void div_NOfree(char* Dest,char* str1,char* str2){
    int len1 = strlen(str1),len2 = strlen(str2);
    if(comp(str1,len1,str2,len2) == _SMALL){
        Dest = (char*)realloc(Dest,sizeof(char)*2);
        Dest[0] = '0';Dest[1] = 0;
        return;
    }
    char* ans = new char[len1+3],*yu = new char[len2+3];
    char* str = new char[len2+3],*temp = new char[len2+3];
    memset(ans,0,sizeof(ans));
    memset(yu,0,sizeof(yu));
    memset(str,0,sizeof(str));
    memset(temp,0,sizeof(temp));
    int cnt = 0,ans_cur = 0,temp_cur = 0;
    while(cnt <= len1 - 1){
        int ylen = strlen(yu);
        memcpy(temp,yu,ylen);temp[ylen] = 0;temp_cur = ylen;
        bool flag = false,jie = false,first = false;
        for(int i = 0;i < len2 - ylen;i++){
            jie = true;
            if(cnt > len1 - 1){
                ans[ans_cur] = '0';ans_cur++;
                flag = true;
                break;
            }
            temp[temp_cur] = str1[cnt];temp_cur++;temp[temp_cur] = 0;
            if(first){
                ans[ans_cur] = '0';ans_cur++;
            }
            else first = true;
            cnt++;
        }
        if(flag){
            break;
        }
        int f1 = str2[0] - '0',f2 = temp[0] - '0';
        if(f1 > f2 || comp(str2,temp) == _BIG){
            if(cnt > len1 - 1){
                int leng = strlen(temp);
                ans[ans_cur] = '0';ans_cur++;
                break;
            }
            if(jie){ans[ans_cur] = '0';ans_cur++;}
            temp[temp_cur] = str1[cnt];temp_cur++;temp[temp_cur] = 0;
            f2 = f2 * 10 + temp[1] - '0';
            cnt++;
        }
        int s = f2 / f1;
        while(true){
            char ss[3];
            sprintf(ss,"%d",s);
            mul_NOfree(str,str2,ss);
            if(comp(temp,str) == _SMALL){
                s -= 1;
                continue;
            }
            else{
                sub_NOfree(yu,temp,str);
                if(comp(str2,yu) == _BIG){
                    break;
                }
            }
        }
        ans[ans_cur] = char(s + '0');ans_cur++;
        if(yu[0] == '0'){
            while(str1[cnt] == '0'){
                cnt++;
                ans[ans_cur] = '0';ans_cur++;
            }
        }
    }
    int pos = 0;
    while(ans[pos] == '0'){
        pos++;
    }
    int length = strlen(ans) - pos;
    memcpy(Dest,ans + pos,length);
    delete[] str;
    delete[] ans;
    delete[] yu;
    delete[] temp;
    Dest[length] = 0;
}

void sur(char* Dest,char* str1,char* str2){
    int len1 = strlen(str1),len2 = strlen(str2);
    if(comp(str1,len1,str2,len2) == _SMALL){
        Dest = (char*)realloc(Dest,len1 + 1);
        int length = strlen(str1);
        memcpy(Dest,str1,length);
        Dest[length] = 0;
        return;
    }
    char *yu = new char[len2+2],*str = new char[len2+2],*temp = new char[len2+2];
    memset(yu,0,sizeof(yu));
    memset(str,0,sizeof(str));
    memset(temp,0,sizeof(temp));
    int cnt = 0,temp_cur;
    while(cnt <= len1 - 1){
        int ylen = strlen(yu);
        memcpy(temp,yu,ylen);temp[ylen] = 0;temp_cur = ylen;
        bool flag = false;
        for(int i = 0;i < len2 - ylen;i++){
            if(cnt > len1 - 1){
                flag = true;
                break;
            }
            temp[temp_cur] = str1[cnt];temp_cur++;temp[temp_cur] = 0;
            cnt++;
        }
        if(flag){
            break;
        }
        int f1 = str2[0] - '0',f2 = temp[0] - '0';
        if(f1 > f2 || comp(str2,temp) == _BIG){
            temp[temp_cur] = str1[cnt];temp_cur++;temp[temp_cur] = 0;
            f2 = f2 * 10 + temp[1] - '0';
            cnt++;
        }
        int s = f2 / f1;
        while(true){
            char ss[3];
            sprintf(ss,"%d",s);
            mul_NOfree(str,str2,ss);
            if(comp(temp,str) == _SMALL){
                s -= 1;
                continue;
            }
            else{
                sub_NOfree(yu,temp,str);
                if(comp(str2,yu) == _BIG){break;}
            }
        }
        if(yu[0] == '0'){while(str1[cnt] == '0'){cnt++;}}
    }
    if(!yu[0]){yu[0] = '0';yu[1] = 0;}
    Dest = (char*)realloc(Dest,sizeof(char)*(len1 + 2));
    int length = strlen(yu);
    memcpy(Dest,yu,length);
    Dest[length] = 0;
    delete[] str;
    delete[] yu;
    delete[] temp;
}
}

#endif

#ifndef LINT_H
#define LINT_H

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
        friend std::ostream & operator << (std::ostream & output,L_INT x);
        friend std::istream & operator >> (std::istream & output,L_INT x);
        friend int comp(L_INT *x,L_INT *y);
        bool operator < (L_INT &y){return comp(this,&y) == _SMALL;}
        bool operator > (L_INT &y){return comp(this,&y) == _BIG;}
        bool operator >= (L_INT &y){return !(comp(this,&y) == _SMALL);}
        bool operator <= (L_INT &y){return !(comp(this,&y) == _BIG);}
        friend void add(L_INT *str1,L_INT *str2);
        L_INT operator + (L_INT x){L_INT temp;temp = *this;temp += x;return temp;}
        void operator += (L_INT x);
        L_INT operator - (L_INT x){L_INT temp = *this;temp -= x;return temp;}
        void operator -= (L_INT x);
        L_INT operator * (L_INT x){L_INT temp = *this;temp *= x;return temp;}
        void operator *= (L_INT x);
        L_INT operator / (L_INT x){L_INT temp = *this;temp /= x;return temp;}
        void operator /= (L_INT x);
        L_INT operator % (L_INT x){L_INT temp = *this;temp %= x;return temp;}
        void operator %= (L_INT x);
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

void L_INT::operator += (L_INT x){
    char *temp = new char[bignum::max(this->length,x.length)+2];
    if(this->posTive == x.posTive){
        bignum::add_NOfree(temp,this->value,x.value);
    }
    else{
        int CHECK = bignum::comp(this->value,this->length,x.value,x.length);
        if(CHECK == _SAME){
            SetValue0();return;
        }
        else if(CHECK == _BIG){
            bignum::sub_NOfree(temp,this->value,x.value);
        }
        else{
            this->posTive = !this->posTive;
            bignum::sub_NOfree(temp,x.value,this->value);
        }
    }
    length = strlen(temp);
    this->value = (char*)realloc(this->value,length + 1);
    memcpy(this->value,temp,length);
    this->value[length] = 0;
    delete[] temp;
}

void L_INT::operator -= (L_INT x){
    x.posTive = !x.posTive;
    *this += x;
}

void L_INT::operator *= (L_INT x){
    if(this->value == "0" || x.value == "0"){
        SetValue0();return;
    }
    char *temp = new char[this->length + x.length+1];
    this->posTive ^= x.posTive;
    this->posTive = !this->posTive;
    bignum::mul_NOfree(temp,this->value,x.value);
    length = strlen(temp);
    this->value = (char*)realloc(this->value,length + 1);
    memcpy(this->value,temp,length);
    this->value[length] = 0;
    delete[] temp;
}

void L_INT::operator /= (L_INT x){
    if(x.value == "0"){
        throw "INFINATE!";
        return;
    }
    if(this->value == "0"){
        SetValue0();return;
    }
    char *temp = new char[this->length + 2];
    bignum::div_NOfree(temp,this->value,x.value);
    this->posTive ^= x.posTive;
    this->posTive = !this->posTive;
    length = strlen(temp);
    this->value = (char*)realloc(this->value,length + 1);
    memcpy(this->value,temp,length);
    this->value[length] = 0;
    delete[] temp;
}

void L_INT::operator %= (L_INT x){
    if(x.value == "0"){
        throw "INFINATE!";
        return;
    }
    if(this->value == "0"||strcmp(x.value,"1") == 0){
        SetValue0();return;
    }
    char *temp = new char[x.length+2];
    bignum::sur(temp,this->value,x.value);
    length = strlen(temp);
    this->value = (char*)realloc(this->value,length + 1);
    memcpy(this->value,temp,length);
    this->value[length] = 0;
    delete[] temp;
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

std::ostream & operator << (std::ostream & output,L_INT x){
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

#ifndef _VAR_H
#define _VAR_H

#define UNDEFINE 0
#define INT 1
#define CHAR 2
#define STR 3
#define FLOAT 4
#define OBJECT 5

class _var{
    private:
        short vtype;
    public:
    _var *pVar;
    //void get(_var &a);
    _var* get(){
        return this;
    }
    _var(){vtype = UNDEFINE;pVar = NULL;}
    _var(const int i){vtype = INT;pVar = NULL;*this = i;}
    _var(const char i){vtype = CHAR;pVar = NULL;*this = i;}
    _var(const char* i){vtype = STR;pVar = NULL;*this = i;}
    _var(const std::string i){vtype = STR;pVar = NULL;*this = i;}
    _var(const double i){vtype = FLOAT;pVar = NULL;*this = i;}
    _var(_var* i);
    virtual void changeType(short i){vtype = i;}
    //void add(_var &a);
    virtual void add(int i){throw "Can't Calculate";};
    virtual void add(char i){throw "Can't Calculate";};
    virtual void add(char* i){throw "Can't Calculate";};
    virtual void add(std::string i){throw "Can't Calculate";};
    virtual void add(double i){throw "Can't Calculate";};
    virtual void add(L_INT i){throw "Can't Calculate";};
    virtual void minus(int i){throw "Can't Calculate";};
    virtual void minus(char i){throw "Can't Calculate";};
    virtual void minus(char* i){throw "Can't Calculate";};
    virtual void minus(std::string i){throw "Can't Calculate";};
    virtual void minus(double i){throw "Can't Calculate";};
    virtual void minus(L_INT i){throw "Can't Calculate";};
    virtual void multi(int i){throw "Can't Calculate";};
    virtual void multi(char* i){throw "Can't Calculate";};
    virtual void multi(double i){throw "Can't Calculate";};
    virtual void multi(L_INT i){throw "Can't Calculate";};
    virtual void div(int i){throw "Can't Calculate";};
    virtual void div(char* i){throw "Can't Calculate";};
    virtual void div(double i){throw "Can't Calculate";};
    virtual void div(L_INT i){throw "Can't Calculate";};

    virtual void sur(L_INT i){throw "Can't Calculate";};
    short getType(){return vtype;}
    virtual L_INT & igetValue(){L_INT *temp = new L_INT; return *temp;};
    virtual char cgetValue(){return 0;};
    virtual std::string sgetValue(){std::string temp;return temp;};
    virtual double fgetValue(){return 0.0;};
    bool operator = (int a);
    bool operator = (const char &s);
    bool operator = (const char* str);
    bool operator = (const std::string &str);
    bool operator = (const double &a);
    bool operator = (_var a);
    bool operator = (L_INT a);
    template<typename dType>
    void operator += (const dType a){this->pVar->add(a);}
    // void operator += (const int a){this->pVar->add(a);}
    // void operator += (const char a){this->pVar->add(a);}
    // void operator += (const char* &a){this->pVar->add(a);}
    // void operator += (const string a){this->pVar->add(a);}
    // void operator += (const double a){this->pVar->add(a);}
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
    _var operator + (const std::string a){
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
    void operator -= (const std::string a){this->pVar->minus(a);}
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
    _var operator - (const std::string a){
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

    template<typename dType>
    void operator %= (dType a){L_INT temp = a;this->pVar->sur(temp);}
    _var operator % (_var a){
        _var temp;
        temp = *this;
        if(a.getType() == INT){
            temp %= a.pVar->igetValue();
        }
        return temp;
    }

    operator int() const;
    operator char() const;
    friend std::string str(_var x);
    operator double() const;
    friend L_INT lint(_var x);
};

class Int:public _var{
    private:
        L_INT value;
    public:
        L_INT & igetValue(){return value;}
        Int(int a){value = a;}
        Int(L_INT a){value = a;}
        void add(int i){value += i;}
        void add(L_INT i){value += i;}
        void add(double i){value += int(i);}
        void minus(int i){value -= i;}
        void minus(L_INT i){value -= i;}
        void minus(double i){value -= int(i);}
        void multi(int i){value *= i;}
        void multi(L_INT i){value *= i;}
        void multi(double i){value *= int(i);}
        void div(int i){value /= i;}
        void div(L_INT i){value /= i;}
        void div(double i){value /= int(i);}
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
        std::string value;
    public:
        Str(std::string str){value = str;}
        Str(char* str){value = str;}
        std::string sgetValue(){return value;}
        void add(std::string i){value += i;}
        void add(char i){value += i;}
        void add(char* i){value += i;}
        void add(int i){value += std::to_string(i);}
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
    if(pVar != NULL){
        delete pVar;
        pVar = NULL;
    }
    pVar = new Int(a);
    changeType(INT);
    return true;
}

bool _var::operator = (L_INT a){
    if(pVar != NULL){
        delete pVar;
        pVar = NULL;
    }
    pVar = new Int(a);
    changeType(INT);
    return true;
}

bool _var::operator = (const char &s){
    if(pVar != NULL){
        delete pVar;
        pVar = NULL;
    }
    pVar = new Char(s);
    changeType(CHAR);
    return true;
}

bool _var::operator = (const std::string &str){
    if(pVar != NULL){
        delete pVar;
        pVar = NULL;
    }
    pVar = new Str(str);
    changeType(STR);
    return true;
}

bool _var::operator = (const char *str){
    if(pVar != NULL){
        delete pVar;
        pVar = NULL;
    }
    pVar = new Str(str);
    changeType(STR);
    return true;
}

bool _var::operator = (const double &d){
    if(pVar != NULL){
        delete pVar;
        pVar = NULL;
    }
    pVar = new Float(d);
    changeType(FLOAT);
    return true;
}

std::ostream & operator << (std::ostream& output,_var x) {
    switch (x.getType())
    {
    case UNDEFINE:
        output << "<None>";
        break;
    case INT:
        output << x.pVar->igetValue();
        break;
    case STR:
        output << x.pVar->sgetValue();
        break;
    case CHAR:
        output << x.pVar->cgetValue();
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

void (*Copy[6])(_var *dist,_var *src) = {
    NULL,
    [](_var *dist,_var *src){
        dist->pVar = new Int(src->pVar->igetValue());
    },
    [](_var *dist,_var *src){
        dist->pVar = new Char(src->pVar->cgetValue());
    },
    [](_var *dist,_var *src){
        dist->pVar = new Str(src->pVar->sgetValue());
    },
    [](_var *dist,_var *src){
        dist->pVar = new Float(src->pVar->fgetValue());
    },
    NULL
};

bool _var::operator = (_var a){
    Copy[a.vtype](this,&a);
    vtype = a.vtype;
    return true;
}

_var::_var(_var *i){
    Copy[i->vtype](this,i);
    vtype = i->vtype;
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

_var::operator int() const{
    if(vtype == INT){
        return pVar->igetValue().toint();
    }
    else if(vtype == CHAR){
        return int(pVar->cgetValue());
    }
    else if(vtype == FLOAT){
        return int(pVar->fgetValue());
    }
    else return 0;
}

_var::operator char() const{
    if(vtype == CHAR){
        return pVar->cgetValue();
    }
    else if(vtype == INT){
        return char(pVar->igetValue().toint());
    }
    else return 0;
}

std::string str(_var x){
    if(x.vtype == STR){
        return x.pVar->sgetValue();
    }
    else if(x.vtype == INT){
        return x.pVar->igetValue().tostr();
    }
    else if(x.vtype == CHAR){
        std::string temp;
        temp += x.pVar->cgetValue();
        return temp;
    }
    else if(x.vtype == FLOAT){
        return std::to_string(x.pVar->fgetValue());
    }
    else{
        std::string roger;
        return roger;
    }
}

_var::operator double() const{
    if(vtype == FLOAT){
        return pVar->fgetValue();
    }
    else if(vtype == INT){
        return double(pVar->igetValue().toint());
    }
    else return 0.0;
}

L_INT lint(_var x){
    if(x.vtype == INT){
        return x.pVar->igetValue();
    }
    else if(x.vtype == FLOAT){
        L_INT temp;
        temp = int(x.pVar->fgetValue());
        return temp;
    }
    else{
        L_INT roger;
        return roger;
    }
}

#endif

#ifndef VAR_HPP
#define VAR_HPP


//Use Array to make var become an array
//使用Array对象使var成为一个数组
struct Array{
    int len;
    Array(){
        len = 1;
    }
    Array(int x){
        len = x;
    }
};


//Below are main class of the project
//以下是核心实现
class var{
    private:
        _var* data;
        int Len; // Length of the Array , if not , len would equal to 1;
    public:
        /*
            These are constructors 构造函数
        */
        var(){
            data = new _var;
            Len = 1;
        }
        var(Array ary){
            data = new _var[ary.len];
            Len = ary.len;
        }
        var(Array *ary){
            data = new _var[ary->len];
            Len = ary->len;
        }
        var(const var &x) {
            data = new _var[x.Len];
            for(int i = 0;i < x.Len;i++){
                data[i] = x.data[i];
            }
            Len = x.Len;
        }
        template<typename dType>
        var(dType _value){
            data = new _var;
            *data = _value;
            Len = 1;
        }

        /*
            Methods 方法
        */
        template<typename dType>
        // push_back() allows to append an element into is object
        // push_back() 允许在队尾添加一个新对象
        void push_back(dType _value){
            Len++;
            _var* tmp = new _var[Len];
            memcpy(tmp, data, sizeof(_var)*(Len - 1));
            delete[] data;
            data = tmp;
            data[Len-1] = _value;
        }
        _var *get(){
            return data;
        }

        /*
            Operators 运算符
        */
        template<typename dType>
        bool operator = (dType _value){
            *data = _value;
            return true;
        }
        bool operator = (Array ary){
            data = new _var[ary.len];
            Len = ary.len;
            return true;
        }
        bool operator =  (Array* ary) {
            data = new _var[ary->len];
            Len = ary->len; 
            return true;
        }
        _var & operator [] (int index){
            return data[index];
        }
        int len(){return Len;}
        _var* begin(){return data;}
        _var* end(){return &data[Len];}
        bool isArray(){
            return Len > 1;
        }
        /*
            Add a number 加
        */
        template<typename dType>
        var operator + (dType x) {
            var temp = x;
            *temp.data += *data;
            return temp;
        }
        template<typename dType>
        void operator += (dType x) {*data += x;}
        template<typename dType>
        friend var operator + (dType x, var &y);
        /*
            Minus a number 减
        */
        template<typename dType>
        var operator - (dType x) {
            var temp = *this;
            *temp.data -= x;
            return temp;
        }
        template<typename dType>
        void operator -= (dType x) {*data -= x;}
        template<typename dType>
        friend var operator - (dType x, var &y);
        /*
            Plus a number 乘
        */
        template<typename dType>
        var operator * (dType x) {
            var temp = *this;
            *temp.data *= x;
            return temp;
        }
        template<typename dType>
        void operator *= (dType x) {*data *= x;}
        template<typename dType>
        friend var operator * (dType x, var &y);
        /*
            Divide by a number 除
        */
        template<typename dType>
        var operator / (dType x) {
            var temp = *this;
            *temp.data /= x;
            return temp;
        }
        template<typename dType>
        void operator /= (dType x) {*data /= x;}
        template<typename dType>
        friend var operator / (dType x, var &y);
        /*
            Surplus a number 求余
        */
        template<typename dType>
        var operator % (dType x) {
            var temp = *this;
            *temp.data %= x;
            return temp;
        }
        template<typename dType>
        void operator %= (dType x) {*data %= x;}
        template<typename dType>
        friend var operator % (dType x, var &y);
};

//a number add it
template<typename dType>
var operator + (dType x, var &y) {
    var temp = y;
    *temp.data += x;
    return temp;
}

//a number minus it
template<typename dType>
var operator - (dType x, var &y) {
    var temp = y;
    *temp.data += x;
    return temp;
}

//a number plus it
template<typename dType>
var operator * (dType x, var &y) {
    var temp = y;
    *temp.data *= x;
    return temp;
}

//a number divide it
template<typename dType>
var operator / (dType x, var &y) {
    var temp = y;
    *temp.data /= x;
    return temp;
}

//a number surplus it
template<typename dType>
var operator % (dType x, var &y) {
    var temp = y;
    *temp.data %= x;
    return temp;
}

//Output by cout
//使用cout输出
std::ostream & (*out[2])(std::ostream &os,var &a) = {
    [](std::ostream &os,var &a) -> std::ostream &{
        os << "[";
        int length = a.len();
        _var *cur = a.begin();
        for (int i = 0;i < length;i++){
            if (cur->getType() == STR) {
                os << "\"" << *cur << "\"";
            }
            else os << *cur << ","[i == length - 1];
            cur++;
        }
        os << "]";
        return os;
    },
    [](std::ostream &os,var &a) -> std::ostream &{
        os << *a.begin();
        return os;
    }
};

std::ostream & operator << (std::ostream &os,var &x){
    return out[x.len() == 1](os,x);
}

namespace Var
{
    bool check(char s){
        if(s >= 'a' && s <= 'z'){
            return true;
        }
        else return false;
    }
} // namespace Var

#define $(x) x.get()

void input(const char* format,...){
    va_list ap;
    va_start(ap,format);
    _var* value;
    int len = strlen(format);
    int type;
    for(int i = 0;i < len;i++){
        value = va_arg(ap,_var*);
        if(format[i] == '%'){
            i++;
            while(Var::check(format[i] == false)){
                i++;
            }
            switch (format[i])
            {
            case 'd':
                {L_INT dtemp;
                std::cin >> dtemp;
                *value = dtemp;
                break;}
            case 'f':
                {double ftemp;
                scanf("%lf",&ftemp);
                *value = ftemp;
                break;}
            case 's':
                {std::string stemp;
                std::cin >> stemp;
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
    }
    va_end(ap);
}

std::string input(){
    std::string temp;
    std::cin >>temp;
    return temp;
}

#endif