# Plan Phase II

* [Progress Index](#progress-index-phase-ii)
* [Changing rank](#changing-rank)
* [Signature extension (polynomials)](#signature-extension-polynomials)

[Progress Index](#progress-index-phase-ii)

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



### Composition

To instantiate, this is probably best done with a Generalized Horner type of expression evaluation.

For the general case, this requires a [binding operator](#binding-operators).

### Convolution

Formally, this a special case of composition.


# Progress Index Phase II

## Done

  * [Changing rank](#changing-rank)
  * [Signature extension (polynomials)](#signature-extension-polynomials)

## In progress

## Not started

