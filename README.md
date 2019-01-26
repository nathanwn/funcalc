# Calculator Program

## Introduction
This is a simple console calculator which can calculate multiple expressions at once.

## Implementation
This project does not use any library related to data structures and algorithms. All data structures and algorithms are implemented from scratch.

## Build
This project can be built using CMake and the CMakeLists.txt file. Otherwise, any IDE would be sufficient.

Note: This project was built with the C++14 flag. Enable this flag to avoid compiling errors.

## Usage
The program supports two different modes: input directly in the console, or input with a text file.
Both relative or absolute path can be used for the file mode.

Each line must have the following syntax:
```
<variable> = <expression>
```

Supported operators:
* `+`, `-`, `*`, `/`, `^`
* `div`, `mod` (integers only)
* functions: `sin`, `cos`, `tan`, `cot`, `exp`

`pi` constant is also supported.

Example:
* Input file:
```
a = 2 + 3 + (3)
b = a + 4
c = 3 * b - 3^2
d = c mod 4
e = 10 - 3 * 4
f = 100 - (2 + 3 * 4)
g = (1 + (10 * (3 - 2)))
h = sin(0.5)
i = exp(exp(0.5))
k = pi
x = 2
y = 3
z = x^2 + y^3
```
* Output:
```
Evaluation Result:
[a] = 8.000000
[b] = 12.000000
[c] = 27.000000
[d] = 3.000000
[e] = -2.000000
[f] = 86.000000
[g] = 11.000000
[h] = 0.479426
[i] = 5.200326
[k] = 3.141593
[x] = 2.000000
[y] = 3.000000
[z] = 31.000000
```
