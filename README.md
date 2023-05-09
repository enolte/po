# [po](https://github.com/enolte/po)

Elementary computations in the real polynomial ring $\mathbb{R}[x_1, ..., x_r]$.

C++23 hobby project.

# Contents
* [Status](#status)
* [Terminology](#terminology)
* [Design Limitations](#design-limitations)
* [Running Unit Tests](#running-unit-tests)
* [Demo/Example](#example)
* [Plan Phase I (Done)](#plan-phase-i) ([Progress Index](#progress-index-phase-i))
  * [IO streams adaptation I](#io-streams-adaptation-i)
  * [Evaluation I](#evaluation-i)
  * [Operators I](#operators-i)
  * [Expression template instantiation](#expression-template-instantiation)
  * [Ring operations](#ring-operations)
* [Plan Phase II](#plan-phase-ii) ([Progress Index](#progress-index-phase-ii))
  * [Changing rank](#changing-rank)
  * [Signature extension (polynomials)](#signature-extension-polynomials)
  * [Storage](#storage-ii)
  * [Operators II](#operators-ii)
  * [Evaluation II](#evaluation-ii)
  * [IO streams adaptation II](#io-streams-adaptation-ii)
* [Plan Phase III](#plan-phase-iii) ([Progress Index](#progress-index-phase-iii))
  * [Induction](#induction)
  * [Quadrature](#quadrature)
  * [Elementary operator algebra](#elementary-operator-algebra)
  * [Signature extension (expressions)](#signature-extension-expressions)


# Status

(*02 July 2023*) Moved some things to Phase III. For Phase II, signature extension will be done only for polynomials, not for general expressions. (The general expression case may not be a real use case anyway.) Applied some minor docs clean up; more of that is coming when I have time. Unit tests for changes to expression accumulation are probably done, for now. Some further organization for expression unit tests is also needed. Will get to that when I have time.

Progress continues as time available.

<details>
<summary><h3>Previous updates</h3></summary>

(*29 April 2023*) Marking Phase I as done. Basic functionality is implemented and verified via unit tests. There are a few smaller clean-up items that remain. Those are coming up soon. Still not using Github issues to track to-do items. I probably should. Also, docs need some work, will get to that when I have time.

(*05 April 2023*) File organization is done for now. Support for variadic differentation and integration is implemented and verified. The remaining piece of Phase I is antiderivatives. This is in progress.

(*06 February 2023*) Moved some things to Phase II, including the completion of the prefix tree storage model. The trie is implemented. The interface for the polynomial type is partially implemented.

(*06 September 2022*) Having just started my new job, this project is in hibernation for now. Progress continues as time available, with reduced time available.

(*18 July 2022*) This code in this repo is ~9 days old, as is this documentation.

* The code is incomplete. (See [Plan](#plan-phase-i).)
* This documentation is incomplete.
* Test coverage and verification is incomplete. (See [Plan](#plan-phase-i).)
* The code is not optimized.
* It uses simple program entry points for unit tests (instead of GoogleTest/gunit, or others).
* There is no build system (a la cmake. etc.).
* There is no CI/CD pipeline.
* There is no installable package.

</details>


# Terminology

This repo uses the following terminology.

* `rank` refers to the number of variables. Others use "order" or "number of indeterminates" or something else, but for now, `rank` is consistent with the "tensor definition" of `rank`, which is related to the bijection between basis elements in a space of multilinear functions and monomials in the usual addition representation. With the introduction of derivative expressions, this may change, or it may not.

* `monomial`  refers to a product of powers together with a scalar coefficient. Some refer to the "power product" with unit coefficient as a monomial. This repo includes the coefficient value as part of a monomial.

* `exponents` refers to a sequence of non-negative integers whose length is equal to `rank`. With or without a vector x, this is sometimes called a "power product". A more general (and conventional) term for `exponents` is "multiindex", which also includes the case where x has "operator components", and not just scalar components. This is not implemented yet, so the more restrictive term `exponents` is used in this repo for now.




# Design Limitations

This list is not exhaustive.

## Representation

`po::polynomial` is a value type: it stores all of its own multiindices and coefficients. This is bad if many polynomials are instantiated with overlapping lifetimes, as it requires redundant data storage. A better approach with a flat storage model is to pre-generate and [pool](#pooled-exponents) multiindices to be used, to reference from individual monomial terms. A few [storage](#storage-ii) models are planned for experimentation in Phase II.

The currently implemented storage is a flat model, consisting of a sequence of independently stored monomials.

## Expressions

An rvalue subexpression is copied into its parent expression instance. This happens because there is no implemented mechanism for rvalue-referencing an rvalue constructed by a subexpression type instance.

This implies that an rvalue polynomial is copied into every superior subexpression type instance in a given expression. This is a to-do.

## Operators

For Phase I, arithmetic operators and assignment operators are implemented only for polynomials of the same rank. E.g., if
  * p(x, y, z) = 3xz - 2y
  * q(x, y) = 15y<sup>2</sup>

then `p + q` is not defined. With the current implementation (Phase I) `p + q` compiles, but the result is undefined behavior.

This is the subject of [signature extension](#signature-extension-polynomials) for Phase II.

## Partial evaluation

A partial evaluation compiles and deterministically executes, but the result is undefined for Phase I.

```c++
po::polynomial p{7.5, po::rank<6>{}};
assert(compare::equal(p.variable_degrees, 0, 0, 0, 0, 0, 0));

// Partial matches
assert(p.coefficient(0, 0, 0, 0) == 7.5);
assert(p.coefficient(0, 3, 0, 0) == 0.0);
```

This is a problem because (a) there is no guaranteed term storage order, and (b) the result
is ambiguous, even with a guaranteed storage order.

```c++
po::polynomial p{
  { 7.5, 0, 0, 0, 0, 0, 0},
  { 7.5, 1, 1, 1, 1, 0, 0},
  {-7.5, 1, 1, 1, 0, 0, 0}};

// What is expected?
assert(p.coefficient(1, 1, 1) == 7.5);
```

The above gives 7.5, but with a different order in the terms list above, -7.5 would
be expected instead.

This is the subject of [partial evaluation](#partial-evaluation-rank-decreasing) for Phase II.


# Running Unit Tests

As mentioned under [Status](#status), all unit tests are implemented by a simple program entry point, located at test/po.cpp.

From the repo root, a typical command line to compile and link all polynomial UTs is

```sh
g++ --std=c++23 test/po.cpp
```

`./a` then runs the unit tests from the repo root.

The resulting program implements every polynomial UT, which includes the expression template tests for numerical evaluation and polynomial instantiation. There are currently 1024 indexed unit tests, plus a few which are not yet indexed.

```sh
$ ./a | wc -l
1024
```

 Some of these are probably not necessary; they will remain anyway, for now.

# Example

The following program file ...

```c++
#include "../../polynomial.h"
#include "../../ostream/polynomial_ostream.h"
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
p = 2.3[4,2]+-3.07[5,3]+1.023[5,9]
q = 1[0,1]+22.4[3,1]+-5.1[7,1]
error = 0x1.ecp-15
```

(This output was generated using [dense generalized Horner evaluation](#generalized-horner-dense). [Naïve evaluation](#naïve) gives an identical result.)

The file [demos/00/demo.cpp](./demos/00/demo.cpp) contains the above program source. Other [demos](./demos) will be added when time available, as new features are implemented.






# Plan Phase I

In progress. See [Progress Index](#progress-index-phase-i) for current status.


## IO streams adaptation I

### Basic `std::basic_ostream<char>` support

E.g.,

```
po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};
std::cout << p;
```
emits

```
1.4[2, 3, 2, 1] + 0.5[4, 1, 4, 1]
```

to stdout, which serializes the polynomial $p(x, y, z, w) = 1.4x^2y^3z^2w + 0.5x^4yz^4w$, for named variables $x, y, z, w$.

### Basic `std::basic_istream<char>` support

E.g.,

```
std::stringstream ss{"1.4[2, 3, 2, 1] + 0.5[4, 1, 4, 1]"};
po::polynomial p{};
ss >> p;
```

should produce the polynomial $p$ above.


## Evaluation I

There are two evaluation algorithms implemented. Given a polynomial and parameter values such that each intermediate computational result value can be exactly represented in the scalar field numeric type, the two algorithms below produce identical outputs.

### Naïve

For the usual additive form. Does what you think it does. Iterates each additive term, computing the value of that term using a custom implementation, `po::pow`. `po::pow` runs in ~%60 of the time that `std::pow` does for identical actual parameter values.

### Generalized Horner (dense)

A generalization of Horner to `rank` many variables.

Compositional form: Given $p(x, y)$ in two variables, there are polynomials $q_k$ s.t.

$$p = q_0(y) + xq_1(y) + \dots + x^dq_d(y)$$

where $d = deg(x, p)$. Each $q_k$ has a compositional form, and the compositional form of $p$ is

$$p = q_0(y) + x(q_1(y) + x(q_2(y) + x( \cdots (xq_d(y)) \cdots )))$$

Generalized Horner evaluates this expression in the general case of all compositional subexpressions, for a polynomial of arbitrary rank $p(x_1, ..., x_r)$.

Evaluation recursively iterates every exponent sequence. This does not require storing temporary polynomials, nor does it use `std::bind`. This can be very slow on the typical case of term-wise-sparse polynomials. A sparse version of this is part of [Phase II](#generalized-horner-sparse).




## Operators I

### Binary operators

#### Assignment

The type of the resulting expression is `polynomial&`.

Supported operators are `=, +=, -=, *=`. Right-side types are

* polynomial
* scalar
* expr
* monomial

#### Arithmetic

The type of the resulting expression is a supported expression type.

Supported operators are `+, -, *`. Right-side and left-side types are

* polynomial
* scalar
* expr
* monomial

### Unary operators

The type of the resulting expression is a supported expression type.

Supported operators are `+, -, D, A, I`.

* `D` represents partial differentiation
* `A` represents antidifferentiation
* `I` represents integration

See [Ring operations](#ring-operations). Each of these is treated as a unary operator for test classification.

Support subexpression types are

* polynomial
* scalar
* expr
* monomial



## Expression template instantiation

The basic implementation supports instantiation of polynomial expressions.
E.g., for polynomials q, r, of 4 variables,

```
po::polynomial p = po::instantiate(2*(r-3)*r*r - 3.2*q, po::rank<5>{});
```

or, equivalently,

```
po::polynomial p = 2*(r-3)*r*r - 3.2*q;
```






## Ring operations

Elementary polynomial ring computations

### Partial derivatives

Given any supported expression `x`, of any rank >= 0, `D(x, 2)` should do the right thing when evaluated or instantiated. The type of `D(x, 2)` is a supported expression type. E.g., if $p(x, y, z) = xz^4 - 6y^3 + 3x^8yz$, then `D(3*p, 2)` yields $12xz^3 + 9x^8y$ when instantiated.

A variadic signature supports multiple partial derivatives. Differentiation is applied to place values in left-to-right order. E.g., `D(x, 1, 2)` differentiates the expression `x` in the first argument, then differentiates the result in the second argument.

E.g., the following are supported.

* `D(x, 1, 2)`
* `D(x*q - 9*D(3*p*x, 0, 2), 0, 2, 1)` given `p` and `q`

etc.


### Integrals

Given a rank 2 polynomial, $p(x, y) = 2x^2y - 4xy^3$, then integration over both $x$ and $y$ in $[-1,1] \times [-1, 1]$ is zero, a numerical value. The intent is to support this with

```
double v = integral(p, {0, {-1, 1}}, {0, {-1, 1}});
```

Integration over only one of its variables results in a polynomial in one variable. The intent is to support statements such as

```
integral-expr x = integral(p, {0, {-1, 1}});
integral-expr x = integral(p, {1, {-1, 1}});
```
which includes a positional specification, with variadic signatures in a "natural" way, for multiple integrals.

The above yields an instantiable `integral-expr` type instance for a polynomial of one variable.

Logically, the integral of $p$ on $[-1, 1] \times [-1, 1]$ is equivalent to either of

```
integral(integral(p, {1, {-1, 1}}), {0, {-1, 1}})  // integrate in y first, then x
integral(integral(p, {0, {-1, 1}}), {0, {-1, 1}})  // integrate in x first, then y
```

When an integral-expr is instantiated, the resulting polynomial is "the integral" of the input expression with respect to the given positional argument and interval end points.

For polynomials or expressions of arbitrary rank, the above generalizes in an obvious way.

#### Change of rank

The following uses zero-based enumeration of variables.

Given $rank(p) = 3$, say, $p(u, v, w) = 2u^5 - 3v^3w$, the integral of $p$ in place 1 ( $v$ ) from 0 to 1, say, is conventionally written as something like

$$P_1(u, w) = \int\limits_0^1 p(u, v, w) \ dv = 2u^5 - \frac 34 w$$

which implies that $rank(P_1) = 2$, because $v$ was "integrated out".

If instead $p$ is integrated from a to b with respect to some out-of-range place, say place 7, then

$$P_7(u, v, w) = P_7(u, v, w, \alpha, \beta, \gamma, \delta, \epsilon) = \int\limits_a^b p(u, v, w) \ d\epsilon = (b-a)p(u, v, w)$$

with no explicit dependence upon $\alpha, \beta, \gamma$, or $\delta$.

For integration, this repo implements the following conventions: $rank(\int\limits_a^b p) = rank(p)$ if place number $\ge rank(p)$, and $rank(\int\limits_a^b p) = rank(p) - 1$ if the place number $\lt rank(p)$.


### Antiderivatives

Only integral primitives are supported.

Given an expression `X`, expressions such as `antiderivative(X, 1, 0, 2)` are supported. Each argument after `X` refers to a place with respect to which to integrate. Integration is applied in parameter order, left to right.

The type of such an expression is an antiderivative expression type which, when instantiated, is a unique polynomial $P$ with $rank(P) \ge rank(X)$

#### Change of rank

The following uses zero-based enumeration of variables.

Given a rank-4 polynomial $p(u, v, w, x) = 2ux - 3v^3w$, with place numbers 0, 1, 2, 3, if we antidifferentiate with respect to, say, $v$ (place 1), the result is

$$P_1(u, v, w, x) = \int\ p(u, v, w, x) \ dx = 2uvx - \frac 34 v^4w$$

No change of rank is implied ( $rank(P_1) = rank(p)$ ), because the place number is less than $rank(p)$. Antidifferentiating $p$ with respect a hypothetical place 6 yields

$$P_6(u, v, w, x, \alpha, \beta, \gamma) = \int\ p(u, v, w, x) \ d\gamma = 2ux\gamma - 3v^3w\gamma = \gamma p(u, v, w, x)$$

a rank 7 polynomial.

This repo implements this convention: If the place number $\gt rank(p)$, then $rank(\int p)$ accommodates the place number. If place < $rank(p)$, then $rank(\int p) = rank(p)$.





# Progress Index Phase I


## Done
  * [IO streams adaptation](#io-streams-adaptation-i)
  * [Evaluation](#evaluation-i)
  * [Operators](#operators-i). See [expression-testing](./test/exprs) for current details.
  * [Expression template instantiation](#expression-template-instantiation)
  * [Ring operations](#ring-operations)

# Plan Phase II

## Changing rank

Two simple routines: `decrease_rank` and `increase_rank`. These are implementation-internal operations that unconditionally increase or decrease the rank of a polynomial object. It's probably faster to implement change-of-rank "inline" where it's used, but these may be useful later.

## Signature extension (polynomials)

To multiply two polynomials of different rank, a parameter map must be specified. E.g., for named variables $x, y, z$, an expression which is evaluation-equivalent to $p(x, y, z)q(y)$ may look like

```
(p * po::extend(q, 1))(x, y, z);
```

or for $p(x, y, z)r(x, z)$,

```
(p * po::extend(r, 0, 2))(x, y, z);
```

with rank of the result type of `extend` imputed by the rank of `p`.

The convention is that the arguments to $r$ are selected from the augmented signature (0 and 2 in the above example). So `po::extend(r, 0, 2)` has rank 3, and `po::extend(r, 0, 2)(x, y, z)` has an identical value to `r(x, z)` for any x, y, z.

If the number of positional args does not equal the rank of the expression, the result is undefined.

`po::extend` looks like
```
expr_extend extend(Expr&& expr, X&&... x)
```

When paired with
```
polynomial instantiate(expr_extend&&)
```

a partial evaluation may be instantiated, with expression grammar support, supporting statements like
```
polynomial xr = extend(r, 1, 3);
```
This Phase implements this only for polynomials.



## Storage II

A few polynomial storage models may be undertaken.

### Flat

Stores each monomial separately, as a seqence of independent monomial terms.

This is the currently implemented model.

### Trie

Stores a prefix tree of exponent sequences, with coefficients as leaf data. This is asymptotically more space-efficient, but some algorithms may have greater asymptotic time than with a flat model.

The trie is implemented. The goal is to implement an evaluation algorithm which this repo calls "[sparse generalized Horner](#generalized-horner-sparse)". This algorithm may be faster than a naïve evaluation on a flat storage model.

A prefix tree representation can not benefit from pre-generated multiindices.

This storage model is amenable to evaluation of homogeneous polynomials, which may provide a substitute for a flat or trie model.

This also has some advantages for look-up, but is probably slower than flat for numerical evaluation. Unclear as yet.

### Pooled exponents

Each monomial stores a coefficient and an offset / key to its own exponents. The exponents themselves are stored in a singleton data structure. Exponent storage is either sparse (smaller) or dense (faster).

If sparse storage with a good hash function, then lookup may be amortized Θ(1). If dense, it is constant.

This is probably slower to evaluate than a value-intrinsic flat implementation, with any evaluation algorithm. Unclear as yet. Will be investigated as time available.

### Tensor (maybe)

Stores polynomial terms by degree, with equal-degree terms stored in a tensor of the implied tensor rank.
If the resulting tensors are totally symmetric, memory requirements per tensor object are substantially reduced, even with a componentwise-sparse tensor implementation.

### Polynomial forms

A few polynomial forms can be naturally realized among these storage models

* Euclidean
* Homogeneous
* Compositional (maybe)




## Operators II

### Binary operators

#### Assignment

Operators `=, +=, -=, *=` extended to a right-side type of `initializer_list` as *braced-init-list*.

Additional overloads for a left-side type of `polynomial&&` may be implemented later.

#### Arithmetic

The type of the resulting expression is a supported expression type.

Operators `+, -, *` extended to `initializer_list` as *braced-init-list*, for either right-side or left-side but not both.

With these extensions, source code expressions such as

```
po::polynomial p = 2*(r-3)*r*r - {{4, {3, 0, 3, 2, 1}}, {5.4, {3, 6, 4, 1, 2}}} * 3.2*q;
```

without insantiating temporary monomial objects for the *braced-init-list* entries.

This extension is not currently implemented, and it may not be.



## Evaluation II

### Generalized Horner (sparse)

A generalization of Horner to `rank` many variables.

Compositional form: Given p(x, y) in two variables, there are polynomials q<sub>k</sub> s.t.

$$p = q_0(y) + xq_1(y) + \cdots + x^dq_d(y)$$

where d = deg(x, p). Each of polynomials q<sub>k</sub> has a compositional form, and the compositional form of p is

$$p = q_0(y) + x(q_1(y) + x(q_2(y) + x(\cdots(xq_d(y))\cdots)))$$

Generalized Horner evaluates this expression in the general case of all compositional subexpressions, for a polynomial of arbitrary rank.

A prefix tree is a natural storage model for this. The trie is implemented. The algorithm is not.

### Multivariate de Casteljau

TODO details here

### Partial evaluation (rank-decreasing)

For Phase II, this applies only to polynomials, not to general supported expressions.

If p has rank R, and if fewer than R numeric arguments are specified, the result is an instantiable bind-expression.

The polynomial constructed from a bind-expression is the polynomial defined by a partial evaluation of p.

As a special case, given $rank(p) = 4$, implementing $r(z, w) = p(1.7, -4, w, z)$ would look like

```
po::polynomial r = p(1.7, -4);
```
which is equivalent to
```
po::expr_bind x = po::bind(p, {0, 1.7}, {1, -4});
po::polynomial q = x;
```

This special case will be first. For a typical general case, if

$$p(x, y, z, w) = 1.4x^2y^3z^2w + \frac 12 x^4yz^4w$$

is evaluated with $x = 2$ and $w = 0.5$, the result when instantiated is

$$q(y, z) = p(2, y, z, 0.5) = 2.8y^3x^2 + 4yz^4$$

This may look like

```
po::polynomial q = po::bind(p, {1, 2}, {3, 0.5});
```
which is equivalent to
```
po::expr_bind x = po::bind(p, {1, 2}, {3, 0.5});
po::polynomial q = x;
```

This general case may come later, or not at all.

The special case

```
po::polynomial r = p(1.7, -4);
```
is equivalent to
```
po::expr_bind x = po::bind(p, {0, 1.7}, {1, -4});
po::polynomial q = x;
```

Why not use `std::bind`? Doing so would require implementing conversion from `expr_bind` to polynomial (instantiation) in terms of the implementation details of `std::bind`; those details are not standardized.



### Composition

To instantiate, this is probably best done with a Generalized Horner type of expression evaluation.

For the general case, this requires a [binding operator](#binding-operators).

### Convolution

Formally, this a special case of composition.






## IO streams adaptation II

Any of these may or may not be useful. If it turns out that none of them are, this entire heading will be dropped.

Only `<<` is described below. Each of these entails support for `<<` and `>>`.

### JSON

This may also be valuable for testing. If this turns out to be useful, then the following code fragment...

```
po::polynomial p{{7.1, {4, 2, 3}}, {2.4, {2, 0, 1}}, {-4.5, {6, 3 ,6}}};
std::cout << po::json << p;
```

...could emit something like...

```
polynomial{{coefficient:"7.1", exponents{4, 2, 3}},{coefficient:"2.4", exponents{2, 0, 1}},{coefficient:"-4.5", exponents{6, 3 ,6}}}
```

...to stdout.

### Compositional form

This might be useful for validation.

Given
$$p(x, y, z) = 7.1x^4y^2z^{15} + 2.4x^4y^3 - 4.5x^6y^2 + 13x$$

A left-to-right compositional form (there are seveal) is

$$p(x, y, z) = x^4(y^2(z^{15}(7.1)) + y^3(2.4)) + x^6(y^2(-4.5)) + x(13)$$

For stdout, this tree could be serialized with this code fragment:

```
po::polynomial p{{7.1, {4, 2, 15}}, {2.4, {2, 0, 0}}, {-4.5, {6, 2, 0}}};
std::cout << po::compositional << p;
```

where the result would be something like

```
1{13},4{2{15{7.1}},3{2.4}},6{2{-4.5}}
```

(This string is a sparse / tree representation of p. Serializing to a "general" dense form is clearly not scalable.)

### Source code string format

A simple stream adaptor `po::source` can do this.

The following code fragment...

```
po::polynomial p{{7.1, {4, 2, 3, 1, 3}}, {2.4, {2, 0, 0, 1, 1}}, {-4.5, {6, 2, 4, 3 ,6}}};
std::cout << po::source << p;
```

...should emit...

```
{7.1, {4, 2, 3, 1, 3}}, {2.4, {2, 0, 0, 1, 1}}, {-4.5, {6, 2, 4, 3 ,6}}
```

...to stdout.


# Progress Index Phase II

## Done

  * [Changing rank](#changing-rank)
  * [Signature extension (polynomials)](#signature-extension-polynomials)

## In progress

  * [Storage](#storage-ii)

## Not started

  * [Operators II](#operators-ii)
  * [Evaluation II](#evaluation-ii)
  * [IO streams adaptation II](#io-streams-adaptation-ii)




# Plan Phase III

## Induction

* point fitting
* multivariate Lagrange interpolants
* solver for simplex basis
* Orthonormal basis. Start with an n-dimensional rectangular domain.
* "Multinomial Bernstein" basis
* series induction
  * begins with Taylor and orthonormal Taylor
* Multivariate Lagrange basis
* Bernstein-Bezier approximation for piecewise continuous functions



## Quadrature

For the inner product of a polynomial operator and any suitable function : $\mathbb{R}^n → \mathbb{R}$.

* Simpson
* Dormand-Prince
* Some others



## Elementary operator algebra

### Differential operators

The intent is to support expressions such as

```
D(0) + 1.8*D(4)*D(1)
```

where the expression type is a partial differential operator type.

Applying such an expression to an expression, e.g.,

```
(D(0) + 1.8*D(4)*D(1))((p - 3) * q)
```

gives an appropriate expression type as the result.

### Integral operators

The intent is to support expressions such as `integral(1, {0, 1}) - 2*integral(3, {-2, 2})`, or maybe `integral(3, {2, 4}) + 3*q*q*integral(2, {0, 1})` if given some polynomial `q`. The type of such an expression is an integral operator type.

When applied to an expression `X`, the result looks like

```
(integral(3, {2, 4}) + 3*q*q*integral(2, {0, 1})(X)
```

and the resulting expression type is identical to the type of

```
integral(X, 3, {2, 4}) + 3*q*q*integral(X, 2, {0, 1})
```

### Antiderivative operators

Only integral primitives are supported.

The intent is to support expressions such as `antiderivative(1)`, or maybe `antiderivative(3) + 3*q*q*antiderivative(2)` (given polynomial `q`). The type of such an expression is an antiderivative operator type.

When applied to an expression `X`, the result is an expression which, when instantiated, is a unique polynomial $P$ with $rank(P) \ge rank(X)$.

The expression

```
(antiderivative(3) + 3*q*q*antiderivative(2))(X)
```

has identical type to

```
antiderivative(3)(X) + 3*q*q*antiderivative(2)(X)
```

## Signature Extension (expressions)

TODO Description here.


# Progress Index Phase III

## Done

## In progress


## Not started

  * [Induction](#induction)
  * [Quadrature](#quadrature)
  * [Elementary operator algebra](#elementary-operator-algebra)
  * [Signature extension (expressions)](#signature-extension-expressions)


