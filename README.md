# Var-cpp
Var variables for c++.

Write by RogerChen233.

## Functions

Access to a universal variable container that supports to store many types in c++.

And plenty of functions is waiting to be added.

## How To Use

First you should include the var.hpp file you download.

```c++
#include "var.hpp"
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

Use int() , char() , str() , lint() , double() to transfer variables to another type //Disabled currently because of bugs.

```c++
a = str(a);
int temp = 123456789;
a = L_INT(temp);
```

Input by a c-like function input()

```c++
input("%d%s%f",$(a),$(b),$(c));
/*
	%d:Integer
	%s:String
	%f:Float(double)
	%c:Character
*/
```

Output by cout

```c++
cout << a << b << c << endl;
```

Stored as an array, subscripts can even be strings

```c++
var a = Array(3);//Array length = 3
a[1] = 0;
a[2] = "str";
a[3] = 'c';
//a["str"] = "RogerChen233";
cout << a << endl;
/*
Output:
[0,"str",c]
//["str" = RogerChen233]
*/
```

