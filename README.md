# Var-cpp
Var variables for c++.

Write by RogerChen233.

## Functions

Access to a universal variable container that supports to store many types in c++.

And plenty of functions is waiting to be added.

## How To Use

First you should include the var.h file you download.

```c++
#include "var.h"
```

Then use "var [variable name] " to declare variables

```c++
var a = 0, b = "str", c = 'c'; //Example
```

Use operator "+" " -" "\*" "/" "+=" "-=" "\*=" "/=" to calculate

```c++
a = a * 1;
b = b + "str";//Example
```

Use int() , char() , str() , lint() , double() to transfer variables to another type

```c++
a = str(a);
int temp = 123456789;
a = lint(temp);
```

Input by a function input()

```c++
input("%d%s%f",a,b,c);
cin >> b;
//Tips:If you use cin to input, the default type of the variable would be string.
```

Output by cout

```c++
cout << a << b << c << endl;
```

Stored as an array, subscripts can even be strings

```c++
var a = Array();
a[1] = 0;
a[2] = "str";
a[3] = 'c';
a["str"] = "RogerChen233";
cout << a << endl;
/*
Output:
[0,str,c]
["str" = RogerChen233]
*/
```

