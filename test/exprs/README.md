
|||
|--------------|--------------------|
| created      | 24 July 2022       |
| last updated | 18 February 2023   |

# Expression Grammar Testing

There are 8 supported operators

* unary `D`
* unary `A`
* unary `I`
* unary `+`
* unary `-`
* binary `+`
* binary `-`
* binary `*`

and 2 terminal symbols, constant (`c`) and polynomial (`p`).

These three operator classes are treated as unary expression operators for test classification purposes:

* `D` denotes partial differentiation.
* `A` denotes antidifferentiation.
* `I` denotes integration.


## Taxonomy

Expressions are partially ordered by the number of operators in the expression string. This repo calls this the expression *level*. It is the depth of the expression tree constructed from a source character sequence.

For k >= 0, a level k expression is defined to be any supported expression with k many operators. A level k expression x<sub>k</sub> is defined recursively as any of

* `D`x<sub>k-1</sub>
* `A`x<sub>k-1</sub>
* `I`x<sub>k-1</sub>
* `+`x<sub>k-1</sub>
* `-`x<sub>k-1</sub>
* x<sub>i</sub> `+` x<sub>j</sub>
* x<sub>i</sub> `-` x<sub>j</sub>
* x<sub>i</sub> `*` x<sub>j</sub>

 where x<sub>0</sub> denotes either `c` or `p`, and

* x<sub>i</sub> is any supported level i expression, i = 0, ..., k
* i + j + 1 = k for i, j = 0, ..., k.


The terminal symbols define level 0. There are s<sub>0</sub> = 2 such expressions. At level k, there are

* s<sub>k</sub> = 3(s<sub>k-1</sub>s<sub>0</sub> + ... + s<sub>0</sub>s<sub>k-1</sub>) + 5s<sub>k-1</sub>

many supported expressions. The first few values in this sequence are

|   k   | s<sub>k</sub> |
|-------|--------------:|
|   0   |             2 |
|   1   |            22 |
|   2   |           374 |
|   3   |          7810 |
|   4   |        182813 |

## Organization

Grammar tests for individual expressions are partially sorted by the top-level operator (the operator at the root of the expression tree). For each top-level operator, tests are sub-ordered by the level of the expression(s) to which this operator is applied.

For a top-level unary operator, such as differentiation (D), there are:

2 level 1 expressions: (D applied to 2 level 0 expressions)
* D(c)
* D(p)

22 level 2 expression: (D applied to each of 22 level 1 expressions)
* D(+p)
* D(-p)
* D(D(p))
* D(A(p))
* D(I(p))
* D(+c)
* D(-c)
* D(D(c))
* D(A(c))
* D(I(c))
* D(p + p)
* D(p - p)
* D(p * p)
* D(p + c)
* D(p - c)
* D(p * c)
* D(c + p)
* D(c - p)
* D(c * p)
* D(c + c)
* D(c - c)
* D(c * c)

For a top-level binary operator (e.g., +), there are:

4 level 1 expressions: (2 x 2 = 4 level 0 expression)
* p + p
* p + c
* c + p
* c + c

88 level 2 expressions: (2 x (2 x 22) = 88 expression)
* x<sub>0</sub> + x<sub>1</sub>, 44 expressions
* x<sub>1</sub> + x<sub>0</sub>, 44 expressions

where x<sub>0</sub> is any level 0 expression, idem for x<sub>1</sub>.

At level 2, there are

* 264 expression: 88 for each of +, -, *.
* 110 expression: 22 for each of D, A, I, unary +, and unary -.

This is a total of s<sub>2</sub> = 374 tests, as in the table above.

### Hierarchy

Tests are organized first by top-level operator. All test expressions with a top-level of binary `+` are contained in subdir `expr_binary_plus_evaluate` and `expr_binary_plus_instantiate`.

* The *_instaniate directories verify that an expression is interpreted the intended polynomial.
* The *_evaluate contains spot tests of numerical evaluation of expressions at various input point vectors.
* The file `test_expr_binary_plus_subexpressions.h` contains the corresponding subexpression tests (generally implemented as `static_assert`s).

There are eight such directory pairs. Within each, tests are next organized by expression level. E.g., `test_evaluate_bplus__level_1.h` includes all level-one test expressions whose top-level operator is binary `+`. Each expr level has its own header file, in each of the eight expression directories. If an expression level is not present, there are no unit tests for that top-level operator at that level.

TODO Some subexpression tests are non-static, and some are static_assert. This could be better organized.

### Methodology

For the current phase (Phase I), expression tests are generally done with individually implemented unit tests. It is possible to replace this with a simple stack-machine interpreter for automation. This may be done in a later phase.

Expressions involving only constants are not parsed by this repo; these are implemented by the compiler's expression parser. This reduces the number of expression to be tested at each level.

TODO The s<sub>k</sub> table above does not represent this.

At the moment, testing is thoroughly but not exhaustively done at levels 1, 2. There are a few individual tests at levels 3 - 7.

### Types

Tests are classified by purpose.

* subexpressions: verification that subexpr types of a given expr are as expected.
* evaluation: numerical evaluation at individual point vectors
* instantiation: an interpreted source code symbol string should produce the expected polynomial

#### Subexpressions

An expression produces an instance `x` of an expression type, a fully specified type template whose template parameters are transformed to the expression types of `x`'s subexpressions, if any.

The type `x` is unique to the fully parenthesized source character sequence which defines it, and is implicitly compatible with parenthesis elision and C++ parsing rules.

Subexpression types as implemented in `po` are `const`. Because of template type parameter deduction rules, this requires some very simple type transformation, which can not be implicitly deduced, so types of subexpressions and addresses of subexpression objects are also verified for a few specific cases with tree depth <= 2. This testing could be better organized than it currently is.

This ensures that, e.g., a polynomial lvalue terminal is not copied into subexpressions where it can be referenced, subject to lifetime and scoping. In the current implementation, polynomial rvalues are copied into every subexpression tree which references them. This is a known issue, and will be resolved when time available.

#### Numerics

Numeric tests compare evaluation of non-identical tree structures which should be evaluation-identical (within tolerance) for all input parameters. Current numeric tests verify this.

#### Object contents

Validating expression instantiation compares the produced polynomial with the expected polynomial by comparing object contents.

These simple tests are expository, and detail the field values expected from a given algebraic expression. In teh current implementation, there is some implied dependency upon the storage model, so will require refactoring to support different storage specifications, such as flat vs. trie. (For this first iteration, only a flat model is uploaded, so the uploaded tests have been hard-coded for that.)

