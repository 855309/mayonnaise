# Quick Look
Hello, World! This is mayonnaise, an interpreted language written from scratch.

Let's take a quick look.

# Variables

The easiest part of this language, you can assign variables like python and ruby.

```ruby
a = 1
b = 2
c = "this is a string"
```

# Importing
Easy!

Example directory structure:
+ /
    - main.mayo
    - lib.mayo

To import **lib.mayo**;

```py
import lib
```

mayonnaise automatically finds the file in the directory **and the subdirectories**.

Subdirectory example:

Example directory structure:
+ /
    - main.mayo
    + include
        - lib.mayo

```py
import lib
```

# Functions

## Initializing functions
Quick example:
```ruby
def demo
    return 0
enddef
```

## Built-in functions
There is some essential built-in functions like **log**, **stdin** or **construct**.
The other functions can be found in the [Documentation](docs).

### log
This function is just for writing data to out stream (stdout).

A simple example about **log** function:
```ruby
log("Hello, World!")
```

But, this also writes ``"\n"`` to end of the stream.
To prevent this, you should add the ``false`` option to the 2nd argument.

```ruby
log("Hello, ", false)
log("World!")
```

**Output:**
```
Hello, World!
```

### stdin
This function gets data from stdin. (std::cin type)

Quick Example:
```ruby
a = stdin()
log(a)
```

### readin
This function gets data from stdin. (std::readline type)

Quick Example:
```ruby
a = readin()
log(a)
```

### construct (BETA)
Beta alert!

This function helps creating **structs** and **classes**.

Function structure:
```ruby
construct ( arg1,        arg2,          arg3...arg99  )
            ^            ^              ^
            object type  |              |
                         object name    |
                                        member names

```

#### **Creating Structures**
The object type for struct is **type:struct**.

Example:
```ruby
construct(type:struct, "demo", "name", "val")
```

C++ equivalent:
```cpp
struct demo{
    <obj> name;
    <obj> val;
};
```

#### **Creating Classes**
The object type for class is **type:class**.

Unlike struct, **you can link functions to class**.

Example:
```ruby
def function
    return 123
enddef

construct(type:class, "demo", "name", "val", func:function)
                                           # in this point,
                                           # the function is
                                           # linked to:
                                           # demo.function()

## calling linked function
demo.function()
```

[//]: (ez)

C++ equivalent:
```cpp
class demo{
    public:
        <obj> name;
        <obj> val;

        <obj> function(){
            // linked code
        }
};
```

## Expression Blocks

### If
Classic if block.

Example:
```ruby
a = 3
b = 4

if a < b
    log("b is greater than a")
endif
```

### For
Classic for block.

Example:
```ruby
a = 1
limit = 10

for a <= limit
    log(a)
endfor 
```

### Rangeloop
Mayonnaise special feature.

Creating a loop with a range:
```ruby
rangeloop x in range(0, 10)
    log(x + 1)
endrange
```

[Documentation](docs)
