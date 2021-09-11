#ifndef LINT_H
#define LINT_H

#define _BIG 1
#define _SAME 0
#define _SMALL -1

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;

int comp(string str1,string str2){
    int len1 = str1.length();
    int len2 = str2.length();
    if(len1 > len2){
        return _BIG;
    }
    else if(len2 > len1){
        return _SMALL;
    }
    else return str1.compare(str2);
}

string add(string str1,string str2)//
{
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

string sub(string str1,string str2)
{
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

string mul(string str1,string str2)
{
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

void div(string str1,string str2,string &quotient,string &residue)
{
    quotient=residue="";
    if(str2=="0")
    {
        quotient=residue="ERROR";
        return;
    }
    if(str1=="0")
    {
        quotient=residue="0";
        return;
    }
    int res=comp(str1,str2);
    if(res<0)
    {
        quotient="0";
        residue=str1;
        return;
    }
    else if(res==0)
    {
        quotient="1";
        residue="0";
        return;
    }
    else
    {
        int len1=str1.length();
        int len2=str2.length();
        string tempstr;
        tempstr.append(str1,0,len2-1);
        for(int i=len2-1;i<len1;i++)
        {
            tempstr=tempstr+str1[i];
            tempstr.erase(0,tempstr.find_first_not_of('0'));
            if(tempstr.empty())
              tempstr="0";
            for(char ch='9';ch>='0';ch--)
            {
                string str,tmp;
                str=str+ch;
                tmp=mul(str2,str);
                if(comp(tmp,tempstr)<=0)
                {
                    quotient=quotient+ch;
                    tempstr=sub(tempstr,tmp);
                    break;
                }
            }
        }
        residue=tempstr;
    }
    quotient.erase(0,quotient.find_first_not_of('0'));
    if(quotient.empty()) quotient="0";
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
};

L_INT L_INT::operator + (L_INT x){
    L_INT temp = *this;
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
    L_INT temp = *this;
    x.posiTive ^= 1;
    temp += x;
    return temp;
}

L_INT L_INT::operator * (L_INT x){
    L_INT temp = *this;
    if(temp.value == "0" || x.value == "0"){
        temp.setValue("0");
        return temp;
    }
    if(temp.posiTive == false){
        if(x.posiTive == true){
            temp.setPos(false);
        }
        else temp.setPos(true);
    }
    else{
        if(x.posiTive == true){
            temp.setPos(true);
        }
        else temp.setPos(false);
    }
    temp.setValue(mul(temp.value,x.value));
    return temp;
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

#endif