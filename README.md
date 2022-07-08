# po

Elementary computations in the real polynomial ring R[x<sub>1</sub>, ..., x<sub>r</sub>].

C++23 hobby project.

(18 July 2022) This code in this repo is ~9 days old, as is this documentation. It is incomplete. It is not optimized.
Progress continues as time available.

* [Terminology](#terminology)
* [Design Limitations](#design-limitations)
* [Plan](#plan)
  * Output stream adaptation
  * Evaluation
  * Induction
  * Quadrature
  * Operators
  * Expression template instantiation
  * Ring operations

## Terminology

This repo uses the following terminology.

* `rank` refers to the number of variables. Others use "order" or "num vars" or something else, but `rank` is consistent with the "tensor definition" of `rank`, which clarifies the bijection between basis elements in a space of multilinear functions and monomials in the usual addition representation.

* `monomial`  refers to a product of powers together a scalar coefficient. Some refer to the "power product" with unit coefficient as a monomial. This repo includes the coefficient value as part of a monomial.

* `exponents` refers to a sequence of non-negative integers whose length is equal to `rank`. Together with a vector x, this is sometimes called a "power product". A more general (and conventional) term for `exponents` is "multiindex", which also includes the case where x has "operator components", and not just scalar components. This is not implemented yet, so the more restrictive term `exponents` is used in this repo for now.

## Design Limitations

### Representation

`po::polynomial` is a value type: it stores all of its own multiindices and coefficients. This is bad if many polynomials are instantiated with overlapping lifetimes, as it requires redundant data storage. A better approach is to pre-generate multiindices to be used, so that they may be referenced from a individual monomial terms. This is relevant only to a "flat" memory layout, which stores each monomial separately.

### Expressions

All expression types at this moment store lvalue references to arguments. This probably needs to be separated, to store (move) polynomials from rvalue references, and store lvalue references from lvalue references as is currently done. This change does not affect algebraic instantiation, but it does inform the scope and lifetime of an expression type for any purpose.

### Experiment

A prefix tree representation can not benefit from pre-generated multiindices as such. An implementation of a polynomial trie is in progress, even though its scalability is worse than a flat model. The goal is to implement a custom evaluation algorithm which this repo calls "[generalized de Castelau](#generalized-de-Castelau)".




# Plan

Work in progress. (The label "implemented" imples unit test coverage and verification, obviously.)

## ostream adaption

###  basic `std::basic_ostream<char>` support

E.g.,

```
po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}}
std::cout << p;
```
emits

```
1.4[2, 3, 2, 1] + 0.5[4, 1, 4, 1]
```

to stdout, which serializes the polynomial

p(x, y, z, w) = 1.4*x*<sup>2</sup>*y*<sup>3</sup>*z*<sup>2</sup>*w* + 0.5*x*<sup>4</sup>*yz*<sup>4</sup>*w*

for named variables *x, y, z, w*.

#### not implemented

A simple I|O interchange format (such as JSON)  may also be valuable for testing.

Also, compositional form, at least for validation.

## Evaluation

There are two evaluation algorithms implemented. Given a polynomial and parameter values such that each intermediate computational result value can be exactly represented in the scalar field numeric type, the two algorithms below produce identical outputs.

### naïve

Does what you think it does. Iterates each additive term, computing the value of that term using a custom implementation `po::pow` which replaces `std::pow`. `po::pow` is typically runs in ~%60 of the time that `std::pow` does for identical actual parameter values.

This is evaluation in the usual term-wise additive form.

### generalized de Castelau

A generalization of de Castelau to `rank` many variables.

Compositional form: Given p(x, y) in two variables, there are polynomials q<sub>k</sub> s.t.

* p = q<sub>0</sub>(y) + xq<sub>1</sub>(y) + ∙∙∙ + x<sup>d</sup>q<sub>d</sub>(y),

where d = deg(x, p). Each of polynomials has a compositional form (Horner evaluation), and the compositional form of p is

* p = q<sub>0</sub>(y) + x(q<sub>1</sub>(y) + x(q<sub>2</sub>(y) + x(∙∙∙(xq<sub>d</sub>(y))∙∙∙)))

gDC evaluates this expression in the general case of all compositional subexpressions, for a polynomial p(x<sub>1</sub>, ..., x<sub>r</sub>). This does not require storing temporary polynomials, nor does it use `std::bind`.

#### dense

Recursively iterate every exponent sequence. Very slow on the typical case of term-wise-sparse polynomials.

#### sparse (partially implemented)

This is a generalization of de Castelau for 2 or 3 (or maybe 4) variables, which generalizes Horner's evaluation algorithm. Probably requires a prefix tree. The tree is implemented. The algorithm is not.


## Induction

#### partially implemented

* point fitting
* multivariate Lagrange interpolants

#### not implemented

* Solver for simplex basis
* Orthonormal basis polynomials

## Quadrature

#### not implemented

* Simpson
* Dormand-Prince
* Some others

## Operators

### Assignment

* polynomial [`+=, -=, *=`] monomial
* polynomial [`+=, -=, *=`] constant
* polynomial [`+=, -=, *=`] init-list
* polynomial [`*=`] polynomial

#### not implemented

* polynomial [`+=, -=`] polynomial

### Binary Operations (expression templates)

* polynomial [`+, -, *`] scalar
* polynomial [`+, -, *`] polynomial
* scalar [`+, -, *`] polynomial

#### not implemented

* polynomial [`+, -, *`] monomial
* polynomial [`+, -, *`] init-list
* monomial [`+, -, *`] polynomial
* init-list [`+, -, *`] polynomial

### Unary Operations (expression templates)

* [`-, +`]polynomial

## Expression template instantiation

In progress.

The basic implementation supports instantiation of polynomial expressions.
E.g., for polynomials p, q, r,

```
po::polynomial p = 2*(r-3)*r*r - 3.2*q;
```


Design in progress, while the following instantiations are implemented. The table of test cases is quite large, so is not included in this document.

* [`-, +`] polynomial
* [`-, +`] unary expr
* polynomial [`+, -, *`] scalar expr
* polynomial [`+, -, *`] polynomial
* scalar expr [`+, -, *`] polynomial
* scalar expr [`+, -, *`] polynomial

#### testing incomplete

These are tested and verified for some expressions. Not all tests are implemented yet.

* polynomial [`+, -, *`] unary expr
* polynomial [`+, -, *`] binary expr
* scalar expr [`+, -, *`] unary expr
* scalar expr [`+, -, *`] binary expr
* unary expr [`+, -, *`] polynomial
* unary expr [`+, -, *`] scalar expr
* unary expr [`+, -, *`] unary expr
* unary expr [`+, -, *`] binary expr
* binary expr [`+, -, *`] polynomial
* binary expr [`+, -, *`] unary expr
* binary expr [`+, -, *`] binary expr

### Extension

An extended grammar would include *braced-init-list*s, perhaps as initialization expressions for
`std::initiailizer_list`s or `po::monomial`s. E.g.,

```
po::polynomial p = 2*(r-3)*r*r - {{4, {3, 0, 3, 2, 1}}, {3.3, {4 {3, 6, 4, 1, 2}}}} * 3.2*q;
```
This extension is not currently implemented, and it may not be.


## Ring operations

#### partially implemented

* derivative

#### not implemented

* antiderivative
* convolution
* composition

#### not implemented (expression templates)

* differential operators
* integral operators
* Euclidean form --> Homogeneous form
* Homogeneous form --> Euclidean form

