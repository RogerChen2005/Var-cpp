#include "_var.hpp"
#include <stdarg.h>

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