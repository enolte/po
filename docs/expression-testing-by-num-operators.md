
|||
|--------------|--------------------|
| created      | 24 July 2022       |
| last updated | 18 February 2023   |

# Expression Grammar

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

* `D` denotes partial differentiation.
* `A` denotes antidifferentiation.
* `I` denotes integration.

These three operator classes are treated as unary operators for test classification purposes.

## Taxonomy

Expressions are partially ordered by the number of operators in the expression string. This repo calls this the expression *level*. It is the depth of the expression tree constructed from a source character sequence.

For k >= 0, a level k expression is defined to be any supported expression with k many operators.

A level k expression x<sub>k</sub> is defined recursively as any of

* `D`x<sub>k-1</sub>
* `A`x<sub>k-1</sub>
* `I`x<sub>k-1</sub>
* `+`x<sub>k-1</sub>
* `-`x<sub>k-1</sub>
* x<sub>i</sub> `+` x<sub>j</sub>
* x<sub>i</sub> `-` x<sub>j</sub>
* x<sub>i</sub> `*` x<sub>j</sub>

where

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

## Testing

### Methodology

Expressions involving only constants are not parsed by this repo; these are implemented by the compiler's expression parser. This reduces the number of expression to be tested at each level.

TODO The s<sub>k</sub> table above does not represent this.

#### Current

At the moment, testing is done at levels 1, 2, and 3. For this first iteration, all expression-dependent tests are manual. Only partial coverage at level 3 is included. A few level-4 expressions are also verified, and one level-6 expression.

#### Next

A next step is to implement a simple stack machine interpreter which accepts a syntactically valid in-fix source string, and produces a type `x` which encodes
the string. For simplicity, constants and polynomials in the source string can be pre-registered with the stack machine.

Evaluation of all tests then proceeds for the resultant type. Even with `constexpr` source strings, this evaluation probably can be done only at runtime, due to compiler limitations.

### Types

An expression produces an instance of an expression type. An expression type `x` is a fully specified type template whose template type parameters are the expression types of `x`'s subexpressions, if any. If `x` is nullary, it is a polynomial or a constant.

The type `x` is unique to the fully parenthesized source character sequence which defines it, and is implicitly compatible with parenthesis elision and C++ parsing rules.

E.g., `(p - 3*q) + 2` has a different type (tree) than `p - (3*q + 2)`, but it is the identical type of `p - 3*q + 2`.

Subexpression types as implemented in `po` are `const`. Because of template type parameter deduction rules, this requires some very simple type transformation, which can not be implicitly deduced, so types of subexpressions are also verified for a few specific cases with tree depth <= 2. This testing could be better organized than it currently is.

This is relevant to ensure that, e.g., a polynomial lvalue terminal is not copied into subexpressions where it can be referenced, subject to lifetime and scoping. In the current implementation, polynomial rvalues are copied into every subexpression tree which references them. This is a known issue, and will be resolved when time available.

### Numerics

Numeric tests compare evaluation of non-identical tree structures which should be evaluation-identical (within tolerance) for all input parameters. Current numeric tests verify this.

### Object contents

These simple tests are expository, and detail the field values expected from a given algebraic expression. They are also highly dependent upon the storage model, so will require refactoring to support different storage specifications, such as flat vs. trie. (For this first iteration, only a flat model is uploaded, so the uploaded tests have been hard-coded for that.)





