# [po](https://github.com/enolte/po)

Elementary computations in the real polynomial ring $\mathbb{R}[x_1, ..., x_r]$.

C++23 hobby project.

Mono-repo: *No submodules*.

# Contents
* [Status](#status)
* [Terminology](#terminology)
* [Design Limitations](#design-limitations)
* [Running Unit Tests](#running-unit-tests)
* [Demo/Example](#example)
* [Plan Phase I (Done)](docs/Phase-I.md)
  * IO streams adaptation I
  * Evaluation I
  * Operators I
  * Expression template instantiation
  * Ring operations
* [Plan Phase II (Done)](docs/Phase-II.md)
  * Changing rank
  * Signature extension (polynomials)
* [Plan Phase III](#plan-phase-iii) ([Progress Index](#progress-index-phase-iii))
  * [Induction](#induction)
  * [Quadrature](#quadrature)
  * [Elementary operator algebra](#elementary-operator-algebra)
* [Plan Phase IV](#plan-phase-iv) ([Progress Index](#progress-index-phase-iv))
  * [Evaluation II](#evaluation-ii)
  * [IO streams adaptation II](#io-streams-adaptation-ii)
  * [Signature extension (expressions)](#signature-extension-expressions)
  * [Storage](#storage-ii)
  * [Operators II](#operators-ii)

# Status


| phase  | status      |
|:------:|-------------|
| I      | done        |
| II     | done        |
| III    | in progress |
| IV     | not started |

(*04 May 2024*) Lagrange basis induction is in progress. All of the internals are implemented, with basic test coverage for some low-compute cases. More unit tests are coming, and probably some minor improvements to test organization. The docs for Lagrange need to be improved, too. Also, the solver is not conditioned in any way; this will probably have to change, depending upon further testing.

Progress continues as time available.

<details>
<summary><h3>Previous updates</h3></summary>

(*09 March 2024*) Moved Phase I and II details to separate docs in docs/ folder, because those are done. Added Phase IV, which essentially splits what was Phase III. Looking at doing induction next. The code is already written and tested. Just need to import it here. It's not a great topic for a self-contained mono-repo like this one, but it's interesting to do in the same repo anyway. It's essentially least-squares and subset iteration, in addition to multivariate polynomials.


(*23 January 2024*) It's been about 6 months since I've touched this repo, so moving some things to Phase IV, and marking Phase II as Done. Cleaned up the docs a bit, more of that coming next. Maybe need to add some examples, too.

In Phase III, induction may best be done with a separate repo. It could be a large topic, and it entails some things that are not relevant to elementary multivariate polynomial operations, (least-squares, subset iteration, and other things). Whether to do that in a separate repo is currently undecided.

(*02 July 2023*) Moved some things to Phase III. For Phase II, signature extension will be done only for polynomials, not for general expressions. (The general expression case may not be a real use case anyway.) Applied some minor docs clean up; more of that is coming when I have time. Unit tests for changes to expression accumulation are probably done, for now. Some further organization for expression unit tests is also needed. Will get to that when I have time.

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

For Phase I, arithmetic operators and assignment operators are implemented only for polynomials of the same rank. E.g., if $p(x, y, z) = 3xz - 2y$ and $q(x, y) = 15y^2$, then `p + q` is not defined. With the current implementation (Phase I) `p + q` compiles, but the result is undefined behavior.

This is the subject of [signature extension](./docs/Phase-II.md#signature-extension-polynomials) for Phase II.

## Partial evaluation

A partial evaluation compiles and deterministically executes, but the result is undefined for Phase I. This is a problem because (a) there is no guaranteed term storage order, and (b) the result is ambiguous, even with a guaranteed storage order.

```c++
po::polynomial p{
  { 7.5, 0, 0, 0, 0, 0, 0},
  { 7.5, 1, 1, 1, 1, 0, 0},
  {-7.5, 1, 1, 1, 0, 0, 0}};

// What is expected?
assert(p.coefficient(1, 1, 1) == 7.5);
```

The above gives 7.5, but with a different order in the terms list above, -7.5 would be expected instead.

This is the subject of [partial evaluation](#partial-evaluation-rank-decreasing) for Phase II.


# Running Unit Tests

As mentioned under [Status](#status), all unit tests are implemented by a simple program entry point, located at test/po.cpp.

From the repo root, a typical command line to compile and link all polynomial UTs is

```sh
g++ --std=c++23 test/po.cpp
```

`./a` then runs the unit tests from the repo root.

The resulting program implements every polynomial UT, which includes the expression template tests for numerical evaluation and polynomial instantiation. The entire test suite runs in ~7.4s on my host. There are currently 1340 indexed unit tests, plus a few which are not yet indexed.

```sh
$ time ./a | grep ^po: | wc -l
1340

real    0m7.377s
user    0m0.000s
sys     0m0.030s
```

Some of these UTs are probably not necessary; they will remain anyway, for now.

# Example

The following program file ...

```c++
// g++ --std=c++23 demo.cpp
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

(This output was generated using [dense generalized Horner evaluation](#./docs/Phase-I.md#generalized-horner-dense). [Naïve evaluation](./docs/Phase-I.md#naïve) gives an identical result.)

The file [demos/00/demo.cpp](./demos/00/demo.cpp) contains the above program source. Other [demos](./demos) will be added when time available, as new features are implemented.





# Plan Phase III


## Induction

### Lagrange interpolation: interface

For a given set of points in $\mathbb{R}^n$, this looks something like

```c++
std::vector basis = po::lagrange_basis(f, n, degree);
```

where `degree` > 0 is chosen.

`f` is a function (functor) of two indices. This repo uses the convention that `f(i,j)` is the ith component value of the jth point in the point set. As a matrix, with `n` = 2, `f` would represents the points (0, 0), (1, 1), (2, 3), as column vectors:

$$
\left[f\right] =
\begin{bmatrix}
0 & 1 & 2\\
0 & 1 & 3
\end{bmatrix}
$$

so $f( \cdot, j)$ is the $j^{th}$ knot point.

With this convention, `basis` is a std::vector of polynomials, one polynomial for each column in the matrix of `f`. The ith polynomial $p_i$ and the jth knot point $x_j$ satisfy $p_i(x_j) = \delta_{ij}$. With `degree` = 1, and the above points, the resulting polynomials are

$$
\begin{array}{l}
p_1(x, y) = 1 - 2x + y\\
p_2(x, y) = 3x - 2y\\
p_3(x, y) = -x + y
\end{array}
$$

This program...

```c++
// g++ --std=c++23 demo.cpp
#include "../../polynomial.h"
#include "../../ostream/polynomial_ostream.h"
#include "../../induction/lagrange_basis.h"
#include <iostream>

int main()
{
  static constexpr double points[3][2]
  {
    {0, 0},
    {1, 1},
    {2, 3},
  };

  // Select knot points by column
  auto f = [](std::size_t r, std::size_t c) { return points[c][r]; };

  auto basis = po::lagrange_basis(f, 2, 1);

  for(auto i{0zu}; i < basis.size(); ++i)
    std::cout << "basis[" << i << "] = " << basis[i] << std::endl;

  return 0;
}
```
...prints this to stdout:

```
$ ./a
basis[0] = 1[0,0]+-2[1,0]+1[0,1]
basis[1] = 0[0,0]+3[1,0]+-2[0,1]
basis[2] = 0[0,0]+-1[1,0]+1[0,1]
```

These are the polynomials listed above. The file [demos/01/demo.cpp](./demos/01/demo.cpp) contains the above program source. This is also a unit test case for Lagrange(rank=2, degree=1).

The interface for Lagrange interpolation on knot points in a simplex is similar.
```c++
std::vector basis = po::lagrange_basis(f, n, degree, simplex_dimension);
```
The resulting polynomials $p_i$ satisfying $p_i(x_j) = \delta_{ij}$ as above. The difference here is that only the simplex vertices and a degree are provided; the knot points are generated from these in a natural way. More info on this is pending.

### Lagrange interpolation: general point set

The goal is to invert the square Vandermonde matrix, $V$, for any number of variables, to solve for a set of separating polynomials for a point collection $S = \left\\{x_0, ..., x_{n-1}\right\\}$. This repo assumes $V$ for the point collection $S$ is invertible.

In one variable, the Lagrange basis polynomials for $S$ are $\lambda_{k}(x) = \prod_i' \left(\frac{x - x_i}{x_{k} - x_i}\right)$, where the prime denotes $i \neq k$. $\lambda_i$ separates the $i^{th}$ point from the others: $\lambda_i(x_j)=\delta_{ij}$, $i = 0, ..., n-1$. The termwise coefficients of $\lambda_i$ are the ith-row entries of $V^{-1}$ for one variable. Each of these polynomials has degree $\leq n - 1$.

This repo sets the ones across the top row. (Others define $V$ with ones down the first column instead.) So the $(k,j)$-term in $V$ is $x_j^k$ for $j, k = 0, ..., n-1$.

For $n$ variables, and for a chosen degree $d$, there are $R = \binom{n+d}{d}$ many knot points for $R$ many polynomials, so we need a set of $R$ many points in $\mathbb{R}^n$. The polynomial terms are enumerated by the sequence of all multiindices $\alpha$ with length $\lvert \alpha \rvert \leq d$, in a natural order. Enumerating rows (terms) in $V$, in the $j^{th}$ column by this order, the $(\alpha, j)$-term in $V$ is $x_j^{\alpha}$, where each $x_j$ is an $n$-dimensional vector, and $V$ is $R \times R$.

$V$ is assumed invertible, so there is a $P$ such that $PV=I$. The $i^{th}$ row of $P$ is the coefficients of $\lambda_i$, in iteration order. That is, $\lambda_i(x_j) = \delta_{ij}$ for each knot point $x_j$.

A natural formula for the multivariate case is $\lambda_i(x) = \frac{det(V_i(x))}{det(V)}$, where $V_i(x)$ is $V$ with the $i^{th}$ column generated by the components of $x$ instead of the knot point $x_i$. Then, $det(V_i(x_i)) = det(V)$, and $det(V_i(x_j)) = 0$ for $i \neq j$. That is, $\lambda_i(x_j) = \delta_{ij}$.

To implement this, this repo uses a QR decomposition and right-triangular linear solver to compute a direct numeric solution to the equation $PV = I$. This repo doesn't compute determinants explicitly, because there is a also a generalization to tall, non-square $V$ included for the case that the knots points in $\mathbb{R}^n$ lie in a $k$-dimensional simplex, with $k \leq n$.


### Lagrange interpolation: simplex points

To guarantee that $V$ has full rank, knot points may be generated from the vertex points of a non-degenerate $k$-simplex $K \subset \mathbb{R}^n$, and a degree $d > 0$.

We can choose $C = \binom{k+d}{d}$ many knot points in $K$. (These points are chosen "isotropically". There is no preferred relative orientation of points in $K$.) Knot points are convex combinations of the vertex points, so $C$ is the number of _knot multiindices_ $\beta$ of $k+1$ items, with length $\lvert \beta \rvert = d$, and $K$ spans a $k$-dimensional linear space.

An interpolating polynomial in $n$ variables of degree $d$ has $R = \binom{n+d}{d}$ additive terms, so that $V$ is $R \times C$. The $(\alpha, \beta)$-entry of $V$ is $(k_{\beta})^{\alpha}$, for knot point $k_{\beta} \in K$ generating a single column in $V$.

With a non-degenerate $K$, $V$ has full rank, so there is a matrix $P$ of polynomial coefficients that satisfies $PV = I_{C \times C}$. Each row in $P$ defines the coefficients of a separating polynomial. $P$ is a least-squares solution, generally one member of an affine space of solutions. The QR decomposition chooses the solution given by the minimal number of non-zero entries in $R$. That is, the basis with the affine zero component is selected.

If $k=n$, then $V$ and $P$ are square, and we have the usual Lagrange interpolation, with a specific point arrangement that guarantees a unique solution. Generally, $k \leq n$, so that $V$ is tall and $P$ is wide.

As with the general case, this is directly, numerically solved with a simple QR-based solver.


### Orthonormal basis.

Start with an n-dimensional rectangular domain.

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



# Progress Index Phase III

## Done

## In progress

  * [Induction](#induction)

## Not started

  * [Quadrature](#quadrature)
  * [Elementary operator algebra](#elementary-operator-algebra)



# Plan Phase IV

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




## Signature Extension (expressions)

TODO Description here.

# Progress Index Phase IV

## Done

## In progress

## Not started

  * [Evaluation II](#evaluation-ii)
  * [IO streams adaptation II](#io-streams-adaptation-ii)
  * [Signature extension (expressions)](#signature-extension-expressions)
  * [Storage](#storage-ii)
  * [Operators II](#operators-ii)

