# po

Elementary computations in the real polynomial ring R[x<sub>1</sub>, ..., x<sub>r</sub>].

C++23 hobby project.

## Contents
* [Status](#status)
* [Terminology](#terminology)
* [Design Limitations](#design-limitations)
* [Running Unit Tests](#running-unit-tests)
* [Demo/Example](#example)
* [Plan](#plan)
  * [IO streams adaptation](#io-streams-adaption)
  * [Evaluation](#evaluation)
  * [Induction](#induction)
  * [Quadrature](#quadrature)
  * [Operators](#operators)
  * [Expression template instantiation](#expression-template-instantiation)
  * [Binding operators](#binding-operators)
  * [Storage](#storage)
  * [Ring operations](#ring-operations)
* [Progress Index](#progress-index)





## Status

(*06 September 2022*) Having just start my new job, this project is in hibernation for now. Progress continues as time available, with reduced time available.

(*18 July 2022*) This code in this repo is ~9 days old, as is this documentation.

* The code is incomplete. (See [Plan](#plan).)
* This documentation is incomplete.
* Test coverage and verification is incomplete. (See [Plan](#plan).)
* The code is not optimized.
* It uses simple program entry points for unit tests (instead of GoogleTest/gunit, or others).
* There is no build system (a la cmake. etc.).
* There is no CI/CD pipeline.
* There is no installable package.

Progress continues as time available.





## Terminology

This repo uses the following terminology.

* `rank` refers to the number of variables. Others use "order" or "number of indeterminates" or something else, but for now, `rank` is consistent with the "tensor definition" of `rank`, which is related to the bijection between basis elements in a space of multilinear functions and monomials in the usual addition representation. With the introduction of derivative expressions, this may change, or it may not.

* `monomial`  refers to a product of powers together with a scalar coefficient. Some refer to the "power product" with unit coefficient as a monomial. This repo includes the coefficient value as part of a monomial.

* `exponents` refers to a sequence of non-negative integers whose length is equal to `rank`. With or without a vector x, this is sometimes called a "power product". A more general (and conventional) term for `exponents` is "multiindex", which also includes the case where x has "operator components", and not just scalar components. This is not implemented yet, so the more restrictive term `exponents` is used in this repo for now.




## Design Limitations

### Representation

`po::polynomial` is a value type: it stores all of its own multiindices and coefficients. This is bad if many polynomials are instantiated with overlapping lifetimes, as it requires redundant data storage. A better approach with a flat storage model is to pre-generate multiindices to be used, to reference from individual monomial terms. A few [storage](#storage) models are planned for experimentation.

### Expressions

An rvalue subexpression is copied into its parent expression instance. This happens because there is no implemented mechanism for rvalue-referencing an rvalue constructed by a subexpression type instance.

This implies that an rvalue polynomial is copied into every superior expression type instance. This is a to-do.




# Running Unit Tests

As mentioned under [Status](#status), all unit tests are implemented by a simple program entry point, located at test/polynomial/polynomial.cpp.

From the repo root, a typical command line to compile all polynomial UTs is

```
g++ --std=c++23 test/polynomial/polynomial.cpp
```

`./a` then runs the unit tests from the repo root.

The resulting program implements every polynomial UT, which includes the expression template tests for numerical evaluation and polynomial instantiation.





# Example

The following program file ...

```
#include "../../polynomial.h"
#include <iostream>

int main()
{
  po::polynomial p{{2.3, {4, 2}}, {-3.07, {5, 3}}, {1.023, {5, 9}}};
  po::polynomial q{{1, {0, 1}}, {22.4, {3, 1}}, {-5.1, {7, 1}}};
  std::cout << "p = " << p << std::endl;
  std::cout << "q = " << q << std::endl;

  const auto y = q(3, 4);
  const auto error = (p*q + q*(q - p))(3, 4) - y*y;

  std::cout << "error = " << std::hexfloat << error << std::endl;
  return 0;
}
```
...computes the error in the evaluation of `q*q` from the above expression, without computing any temporary polynomials. On my host, the resulting program emits
```
$ ./a
p = 2.3[4, 2] + -3.07[5, 3] + 1.023[5, 9]
q = 1[0, 1] + 22.4[3, 1] + -5.1[7, 1]
error = 0x1.ecp-15
```

(This output was generated using [dense generalized Horner evaluation](#generalized-horner). [Naïve evaluation](#naïve) gives an identical result.)

The file [demos/00/demo.cpp](./demos/00/demo.cpp) contains the above program source. Other [demos](./demos) will be added when time available, as new features are implemented.






# Plan

In progress. See [Progress Index](#Progress-Index) for current status.


## IO streams adaption

###  basic `std::basic_ostream<char>` support

E.g.,

```
po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};
std::cout << p;
```
emits

```
1.4[2, 3, 2, 1] + 0.5[4, 1, 4, 1]
```

to stdout, which serializes the polynomial

p(x, y, z, w) = 1.4*x*<sup>2</sup>*y*<sup>3</sup>*z*<sup>2</sup>*w* + 0.5*x*<sup>4</sup>*yz*<sup>4</sup>*w*

for named variables *x, y, z, w*.

### basic `std::basic_istream<char>` support

E.g.,

```
std::string source = "1.4[2, 3, 2, 1] + 0.5[4, 1, 4, 1]";
po::polynomial p;
std::stringstream ss;
ss >> p;
```

should produce the polynomial

p(x, y, z, w) = 1.4*x*<sup>2</sup>*y*<sup>3</sup>*z*<sup>2</sup>*w* + 0.5*x*<sup>4</sup>*yz*<sup>4</sup>*w*

for named variables *x, y, z, w*.

### Extension

Maybe these too.

* A simple I|O interchange format (such as JSON)  may also be valuable for testing.
* Also, compositional form, at least for validation.
* Source code string format. This may or may not be useful.



## Evaluation

There are two evaluation algorithms implemented. Given a polynomial and parameter values such that each intermediate computational result value can be exactly represented in the scalar field numeric type, the two algorithms below produce identical outputs.

### naïve

For the usual additive form. Does what you think it does. Iterates each additive term, computing the value of that term using a custom implementation, `po::pow`. `po::pow` runs in ~%60 of the time that `std::pow` does for identical actual parameter values.

### generalized Horner

A generalization of Horner to `rank` many variables.

Compositional form: Given p(x, y) in two variables, there are polynomials q<sub>k</sub> s.t.

* p = q<sub>0</sub>(y) + xq<sub>1</sub>(y) + ∙∙∙ + x<sup>d</sup>q<sub>d</sub>(y),

where d = deg(x, p). Each of polynomials q<sub>k</sub> has a compositional form, and the compositional form of p is

* p = q<sub>0</sub>(y) + x(q<sub>1</sub>(y) + x(q<sub>2</sub>(y) + x(∙∙∙(xq<sub>d</sub>(y))∙∙∙)))

Generalized Horner evaluates this expression in the general case of all compositional subexpressions, for a polynomial of arbitrary `rank` p(x<sub>1</sub>, ..., x<sub>r</sub>).

* dense Horner. Recursively iterate every exponent sequence. This does not require storing temporary polynomials, nor does it use `std::bind`. Very slow on the typical case of term-wise-sparse polynomials. Dynamic programming can optimize this, but a prefix tree is probably the same approach.

* sparse Horner. Probably requires a prefix tree. The tree is implemented. The algorithm is not.

### multivariate de Casteljau

TODO details here






## Induction

* point fitting
* multivariate Lagrange interpolants
* solver for simplex basis
* Orthonormal basis polynomials. Start with an n-dimensional rectangular domain.
* "Multinomial Bernstein" basis
* series induction
  * begins with Taylor and orthonormal Taylor
* Lagrange basis
* Bernstein-Bezier approximation for piecewise continuous functions





## Quadrature

For the inner product of a polynomial operator and any suitable function : R<sup>n</sup> → R.

* Simpson
* Dormand-Prince
* Some others





## Operators

"*ext*" denotes a possible extension which may or may not be implemented later.

### Binary operators

#### Assignment

The type of the resulting expression is `polynomial&`.

Supported operators are `=, +=, -=, *=`. Right-side types are

* polynomial
* scalar
* expr
* monomial
* init-list (*ext*)

Additional overloads for a left-side type of `polynomial&&` may be implemented later.

#### Arithmetic

The type of the resulting expression is a supported expression type.

Supported operators are `+, -, *`. Right-side and left-side types are

* polynomial
* scalar
* expr
* monomial
* init-list (*ext*, right-side XOR left-side)

#### Extension

An extended grammar would include *braced-init-list*s, perhaps as initialization expressions for
`std::initializer_list`s or `po::monomial`s. E.g.,

```
po::polynomial p = 2*(r-3)*r*r - {{4, {3, 0, 3, 2, 1}}, {5.4, {3, 6, 4, 1, 2}}} * 3.2*q;
```
This extension is not currently implemented, and it may not be.


### Unary operators

The type of the resulting expression is a supported expression type.

Supported operators are `+, -, D`. `D` represents partial differentiation, treated as a unary operator for test classification.

Support subexpression types are

* polynomial
* scalar
* expr
* monomial



## Expression template instantiation

The basic implementation supports instantiation of polynomial expressions.
E.g., for polynomials q, r, of 4 variables,

```
po::polynomial p = po::instantiate(2*(r-3)*r*r - 3.2*q, po::rank<4>{});
```

The goal is to support

```
po::polynomial p = 2*(r-3)*r*r - 3.2*q;
```

which is not supported yet.






## Binding operators

To multiply two polynomials of different rank, a parameter map must be specified. E.g., for named variables *x*,*y*,*z*, an expression which is evaluation-equivalent to evaluate p(x, y, z) * q(y) may look like

```
p * po::bind(q, 2);
```

or for p(x, y, z) * r(x, z),

```
p * po::bind(r, 1, 3);
```

with the result of `po::bind` imputed by the rank of the polynomial `p`. This approach may not work to implement q(x) * p(x, y, z), because of class template argument deduction rules. This will be investigated as time available.





## Storage

  Individual polynomial storage models.

### flat

  Stores each monomial separately, as a seqence of independent monomial terms.

  This is the currently implemented model.

### trie

Stores a prefix tree of exponent sequences, with coefficients as leaf data. This is asymptotically more space-efficient, but some algorithms may have greater asymptotic time than with a flat model.

An implementation of a polynomial trie is in progress. The goal is to implement an evaluation algorithm which this repo calls "sparse [generalized Horner](#generalized-horner)". This algorithm may be faster than a naïve evaluation on a flat storage model.

A prefix tree representation can not benefit from pre-generated multiindices.

### tensor

Stores polynomial terms by degree, with equal-degree terms stored in a tensor of the implied tensor rank.
The resulting tensors are totally symmetric, which substantially reduces memory requirements per tensor object, even with a componentwise-sparse tensor implementation.

This storage model is amenable to evaluation of homogeneous polynomials, which may provide a substitute for a flat or trie model.

This also has some advantages for look-up, but may be slower for numerical evaluation. Unclear as yet.

### Polynomial forms

A few polynomial forms can be realized among these storage models

* Euclidean
* Homogeneous
* Compositional (maybe)





## Ring operations

TODO. This section is incomplete.

### antiderivative

This is a completely evaluated sequence of antiderivative operators.

### composition

To instaniate, this is probably bext done with a Generalized Horner type of expression evaluation.

For the general case, this requires a binding operator.

### differential operators

The intent is to support expressions such as

```
D(0) + 1.8*D(4)*D(1)
```

where the expression type is a partial differential operator type.

For instantiation, this is, e.g.,

```
(D(0) + 1.8*D(4)*D(1))((p - 3) * q)
```

with `polynomial` as the type of the expression evaluation.


### integral operators
This induces a polynomial / expression of lesser rank.

### antiderivative operators
This induces a polynomial / expression of greater rank.

### convolution
Formally, this a special case of composition.

### elementary rational field computations




# Progress Index

## Done

(This implies unit test coverage and verification, obviously.)

  * [IO streams adaptation](#io-streams-adaption)
    * basic `std::basic_ostream<char>` support
  * [Evaluation](#evaluation)
    * naïve
    * generalized Horner (dense)
  * [Operators](#operators)
    * See [expression-testing](./docs/expression-testing-status.md) for current status.
  * [Storage](#storage)
    * flat
  * [Ring operations](#ring-operations)
    * partial derivative



## In progress
  * [Operators](#operators) (Needs further testing and verification.)
    |scalar    |polynomial|unary expr|binary expr|
    |:--------:|:--------:|:--------:|:---------:|
    |          |          |[`+  - D`]|[`+  - D`] |
    * See [expression-testing](./docs/expression-testing-status.md) for current status.
  * [Expression template instantiation](#expression-template-instantiation) (Needs further testing and verification. See the plan section.)
  * [Storage](#storage)
    * trie
  * [Ring operations](#ring-operations)
    * differential operators



## Not started

  * [IO streams adaptation](#io-streams-adaption)
    * basic `std::basic_istream<char>` support
  * [Evaluation](#evaluation)
    * sparse Horner
  * [Induction](#induction)
    * Orthonormal basis polynomials. Start with an n-dimensional rectangular domain.
    * "Multinomial Bernstein" basis
    * series induction
    * Lagrange basis
    * Bernstein-Bezier approximation for piecewise continuous functions
  * [Operators](#operators)
    * See [expression-testing](./docs/expression-testing-status.md) for current status.
  * [Induction](#induction)
  * [Quadrature](#quadrature)
  * [Binding operators](#binding-operators)
  * [Storage](#storage)
    * tensor / homogeneous
    * compositional
  * [Ring operations](#ring-operations)
    * antiderivative
    * convolution
    * composition
    * integral operators
    * antiderivative operators
    * elementary rational field computations







