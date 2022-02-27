#ifndef CBIGNUM_H
#define CBIGNUM_H

#include <cstring>
#include <cstdlib>
#include <cstdio>

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