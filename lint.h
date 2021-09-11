#ifndef LINT_H
#define LINT_H

#define _BIG 1
#define _SAME 0
#define _SMALL -1

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;

int comp(string x,string y){
    int len1 = x.length(), len2 = y.length();
    if(len1 > len2){
        return _BIG;
    }
    else if(len1 < len2){
        return _SMALL;
    }
    else{
        for(int i = 0;i < len1;i++){
            if(x[i] == y[i]){
                continue;
            }
            else if(x[i] > y[i]){
                return _BIG;
            }
            else return _SMALL;
        }
    }
    return _SAME;
}

string add(string str1,string str2){
    string str;
    int len1=str1.length();
    int len2=str2.length();
    if(len1<len2)
    {
        for(int i=1;i<=len2-len1;i++)
           str1="0"+str1;
    }
    else
    {
        for(int i=1;i<=len1-len2;i++)
           str2="0"+str2;
    }
    len1=str1.length();
    int cf=0;
    int temp;
    for(int i=len1-1;i>=0;i--)
    {
        temp=str1[i]-'0'+str2[i]-'0'+cf;
        cf=temp/10;
        temp%=10;
        str=char(temp+'0')+str;
    }
    if(cf!=0)  str=char(cf+'0')+str;
    return str;
}

string sub(string str1,string str2){
    string str;
    int tmp=str1.length()-str2.length();
    int cf=0;
    for(int i=str2.length()-1;i>=0;i--)
    {
        if(str1[tmp+i]<str2[i]+cf)
        {
            str=char(str1[tmp+i]-str2[i]-cf+'0'+10)+str;
            cf=1;
        }
        else
        {
            str=char(str1[tmp+i]-str2[i]-cf+'0')+str;
            cf=0;
        }
    }
    for(int i=tmp-1;i>=0;i--)
    {
        if(str1[i]-cf>='0')
        {
            str=char(str1[i]-cf)+str;
            cf=0;
        }
        else
        {
            str=char(str1[i]-cf+10)+str;
            cf=1;
        }
    }
    str.erase(0,str.find_first_not_of('0'));
    return str;
}

string mul(string str1,string str2){
    string str;
    int len1=str1.length();
    int len2=str2.length();
    string tempstr;
    for(int i=len2-1;i>=0;i--)
    {
        tempstr="";
        int temp=str2[i]-'0';
        int t=0;
        int cf=0;
        if(temp!=0)
        {
            for(int j=1;j<=len2-1-i;j++)
              tempstr+="0";
            for(int j=len1-1;j>=0;j--)
            {
                t=(temp*(str1[j]-'0')+cf)%10;
                cf=(temp*(str1[j]-'0')+cf)/10;
                tempstr=char(t+'0')+tempstr;
            }
            if(cf!=0) tempstr=char(cf+'0')+tempstr;
        }
        str=add(str,tempstr);
    }
    str.erase(0,str.find_first_not_of('0'));
    return str;
}

string div(string str1,string str2){
    string ans,yu;
    if(comp(str1,str2) == _SMALL){
        ans = "0";
        yu = str1;
        return ans;
    }
    string str,temp;
    int len1 = str1.length();
    int len2 = str2.length();
    int cnt = 0;
    while(cnt <= len1 - 1){
        temp = yu;
        int ylen = yu.length();
        bool flag = false;
        bool jie = false;
        bool first = false;
        for(int i = 0;i < len2 - ylen;i++){
            jie = true;
            if(cnt > len1 - 1){
                ans += "0";
                flag = true;
                break;
            }
            temp += str1[cnt];
            if(first){
                ans += "0";
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
                int leng = temp.length();
                ans += "0";
                break;
            }
            if(jie){
                ans += "0";
            }
            temp += str1[cnt];
            f2 = f2 * 10 + temp[1] - '0';
            cnt++;
        }
        int s = f2 / f1;
        string ss = to_string(s);
        while(true){
            str = mul(str2,ss);
            if(comp(temp,str) == _SMALL){
                s -= 1;
                ss = to_string(s);
                continue;
            }
            else{
                yu = sub(temp,str);
                if(comp(str2,yu) == _BIG){
                    break;
                }
            }
        }
        ans += ss;
        if(yu == ""){
            while(str1[cnt] == '0'){
                cnt++;
                ans += "0";
            }
        }
    }
    ans.erase(0,ans.find_first_not_of('0'));
    return ans;
}

class L_INT{
    private:
        string value;
        bool posiTive;
    public:
        L_INT(){
            posiTive = true;
        }
        string getValue(){
            return value;
        }
        string tostr(){
            if(posiTive == true){
                return value;
            }
            else return "-" + value;
        }
        int toint(){
            int len = value.length();
            if(len > 10){
                if(posiTive == true){
                    return 0x7f7f7f7f;
                }
                else return 2139062143 + 1;
            }
            else{
                int temp = 0;
                for(int i = 0;i < len;i++){
                    temp = temp * 10 + value[i] - '0';
                }
                if(posiTive == true){
                    return temp;
                }
                else return -temp;
            }
        }
        bool getPos(){
            return posiTive;
        }
        void setValue(string str){
            value = str;
        }
        void setPos(bool i){
            posiTive = i;
        }
        bool operator = (L_INT x){
            value = x.value;
            posiTive = x.posiTive;
            return true;
        }
        bool operator = (int x){
            if(x < 0){
                posiTive = false;
                x = -x;
            }
            else posiTive = true;
            value = to_string(x);
            return true;
        }
        bool operator = (long long x){
            if(x < 0){
                posiTive = false;
                x = -x;
            }
            else posiTive = true;
            value = to_string(x);
            return true;
        }
        L_INT operator + (L_INT x);
        void operator += (L_INT x){
            *this = *this + x;
        }
        L_INT operator - (L_INT x);
        void operator -= (L_INT x){
            *this = *this - x;
        }
        L_INT operator * (L_INT x);
        void operator *= (L_INT x){
            *this = *this * x;
        }
        L_INT operator / (L_INT x);
        void operator /= (L_INT x){
            *this = *this / x;
        }
        L_INT operator + (int x);
        void operator += (int x){
            *this = *this + x;
        }
        L_INT operator - (int x);
        void operator -= (int x){
            *this = *this + x;
        }
        L_INT operator * (int x);
        void operator *= (int x){
            *this = *this + x;
        }
        L_INT operator / (int x);
        void operator /= (int x){
            *this = *this + x;
        }
        friend L_INT lint(char* str);
};

L_INT L_INT::operator + (L_INT x){
    L_INT temp;
    temp.setValue(this->value);
    temp.setPos(this->posiTive);
    if(x.posiTive == false){
        if(temp.posiTive == false){
            temp.value = add(x.value,temp.value);
            temp.posiTive = false;
        }
        else{
            switch (comp(temp.value,x.value))
            {
            case _BIG:
                temp.value = sub(temp.value,x.value);
                break;
            case _SAME:
                temp.value = "0";
                break;
            case _SMALL:
                temp.value = sub(x.value,temp.value);
                temp.posiTive = false;
                break;
            }
        }
    }
    else{
        if(temp.posiTive == false){
            switch (comp(temp.value,x.value))
            {
            case _BIG:
                temp.value = sub(temp.value,x.value);
                break;
            case _SAME:
                temp.value = "0";
                temp.posiTive = true;
                break;
            case _SMALL:
                temp.value = sub(x.value,temp.value);
                temp.posiTive = true;
                break;
            }
        }
        else{
            temp.value = add(x.value,temp.value);
        }
    }
    return temp;
}

L_INT L_INT::operator - (L_INT x){
    L_INT temp;
    temp.setValue(this->value);
    temp.setPos(this->posiTive);
    x.posiTive ^= 1;
    temp += x;
    return temp;
}

L_INT L_INT::operator * (L_INT x){
    L_INT temp;
    temp.setValue(this->value);
    temp.setPos(this->posiTive);
    if(temp.value == "0" || x.value == "0"){
        temp.setValue("0");
        return temp;
    }
    temp.posiTive ^= x.posiTive;
    temp.posiTive = !temp.posiTive;
    temp.setValue(mul(temp.value,x.value));
    return temp;
}

L_INT L_INT::operator / (L_INT x){
    L_INT temp;
    temp.setValue(this->value);
    temp.setPos(this->posiTive);
    temp.setValue(div(temp.getValue(),x.getValue()));
    temp.posiTive ^= x.posiTive;
    temp.posiTive = !temp.posiTive;
    return temp;
}

L_INT L_INT::operator + (int x){
    L_INT temp;
    temp.setValue(this->value);
    temp.setPos(this->posiTive);
    bool isfu = false;
    if(x < 0){
        x = -x;
        isfu = true;
    }
    L_INT xx;
    xx.value = to_string(x);
    if(isfu){
        xx.posiTive = false;
    }
    return temp + xx;
}

L_INT L_INT::operator - (int x){
    L_INT temp;
    temp.setValue(this->value);
    temp.setPos(this->posiTive);
    bool isfu = false;
    if(x < 0){
        x = -x;
        isfu = true;
    }
    L_INT xx;
    xx.value = to_string(x);
    if(isfu){
        xx.posiTive = false;
    }
    return temp - xx;
}

L_INT L_INT::operator * (int x){
    L_INT temp;
    temp.setValue(this->value);
    temp.setPos(this->posiTive);
    bool isfu = false;
    if(x < 0){
        x = -x;
        isfu = true;
    }
    L_INT xx;
    xx.value = to_string(x);
    if(isfu){
        xx.posiTive = false;
    }
    return temp * xx;
}

L_INT L_INT::operator / (int x){
    L_INT temp;
    temp.setValue(this->value);
    temp.setPos(this->posiTive);
    bool isfu = false;
    if(x < 0){
        x = -x;
        isfu = true;
    }
    L_INT xx;
    xx.value = to_string(x);
    if(isfu){
        xx.posiTive = false;
    }
    return temp / xx;
}

ostream & operator << (ostream& output,L_INT x){
    if(x.getPos() == false){
        output << "-";
    }
    output << x.getValue();
    return output;
}

istream & operator >> (istream& input,L_INT &x){
    string temp;
    input >> temp;
    if(temp[0] == '-'){
        temp.erase(0,1);
        x.setPos(false);
    }
    else x.setPos(true);
    x.setValue(temp);
    return input;
}

L_INT lint(char* str){
    L_INT temp;
    if(str[0] == '-'){
        char str1[strlen(str)];
        strcpy(str1,str+1);
        temp.value += str1;
        temp.posiTive = false;
    }
    else temp.value += str;
    return temp;
}

#endif