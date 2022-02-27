#include "time.h"
#include "var.hpp"
using namespace std;

int main(){
    clock_t start,end;

    /*
        赋值测试
    */
    var value;
    start = clock();
    for(int i = 0;i < 50000;i ++){
        value = "123";
        value = "321";
    }
    end = clock();
    printf("100000:%.3llfs\n",(double)(end - start) / CLOCKS_PER_SEC);
    for(int i = 0;i < 500000;i ++){
        value = "123";
        value = "321";
    }
    start = clock();
    printf("1000000:%.3llfs\n",(double)(start - end) / CLOCKS_PER_SEC);
    for(int i = 0;i < 5000000;i ++){
        value = "123";
        value = "321";
    }
    end = clock();
    printf("10000000:%.3llfs\n",(double)(end - start) / CLOCKS_PER_SEC);

    /*
        高精测试
    */
    L_INT a,b,c;
    a = 6789040043230;
    b = 123436040430;
    cout << "a = "<< a << endl << "b = " << b << endl;
    start = clock();
    for (int i = 0; i < 1000000; i++){
        c = a + b;
    }
    end = clock();
    printf("+:%.3llfs\n",(double)(end - start) / CLOCKS_PER_SEC);
    cout << a << "+" << b << "="<< c << endl;
    start = clock();
    for (int i = 0; i < 1000000; i++){
        c = a - b;
    }
    end = clock();
    printf("-:%.3llfs\n",(double)(end - start) / CLOCKS_PER_SEC);
    cout << a << "-" << b << "=" << c << endl;
    start = clock();
    for (int i = 0; i < 1000000; i++){
        c = a * b;
    }
    end = clock();
    printf("*:%.3llfs\n",(double)(end - start) / CLOCKS_PER_SEC);
    cout << a << "*" << b << "=" << c << endl;
    start = clock();
    for (int i = 0; i < 1000000; i++){
        c = a / b;
    }
    end = clock();
    printf("/:%.3llfs\n",(double)(end - start) / CLOCKS_PER_SEC);
    cout << a << "/" << b << "=" << c << endl;

    /*
        内置数组测试
    */
    var aa = Array();
    var bb = Array();
    var cc = Array();
    start = clock();
    for (int i = 0; i < 5000; i++)
    {
        aa.push_back("Castle");
    }
    end = clock();
    cout << "Length:" << aa.len() << endl;
    printf("5000:%.3llfs\n",(double)(end - start) / CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 10000; i++)
    {
        bb.push_back("Castle");
    }
    end = clock();
    cout << "Length:" << bb.len() << endl;
    printf("10000:%.3llfs\n",(double)(end - start) / CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 50000; i++)
    {
        cc.push_back("Castle");
    }
    end = clock();
    cout << "Length:" << cc.len() << endl;
    printf("50000:%.3llfs\n",(double)(end - start) / CLOCKS_PER_SEC);

    system("pause");
}