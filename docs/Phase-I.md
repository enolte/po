# Plan Phase I

* [IO streams adaptation I](#io-streams-adaptation-i)
* [Evaluation I](#evaluation-i)
* [Operators I](#operators-i)
* [Expression template instantiation](#expression-template-instantiation)
* [Ring operations](#ring-operations)

[Progress Index](#progress-index-phase-i)

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

Evaluation recursively iterates every exponent sequence. This does not require storing temporary polynomials, nor does it use `std::bind`. This can be very slow on the typical case of term-wise-sparse polynomials. A sparse version of this is part of [Phase II](./Phase-II.md#generalized-horner-sparse).




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


