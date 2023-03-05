# Expression Testing

Current status tables are below.

Tests are implemented per-expression, where expressions are partially [sorted into levels by number of operators](./expression-testing-by-num-operators.md). Verification is generally limited to levels 0 - 2, with some additional expressions with more than 2 operators already verified. Expressions at level > 2 will be unit-tested, but these tests will not cover every expression at level > 2.

The following tables summarize expressions at levels 1 and 2 which have been systematically tested and verified. Not all level 2 expression have been individually verified. Compiler front-end limitations prevent translation of a single translation unit with all level 2 expressions.

## Unary

| status     |scalar       |polynomial   |unary expr   |binary expr  |
|:-----------|:-----------:|:-----------:|:-----------:|:-----------:|
| complete   | `+ - D   I` | `+ - D   I` | `+ -      ` | `+ -      ` |
| incomplete | `      A `  | `      A  ` | `    D A I` | `    D A I` |

## Binary assignment

| status     |                  |polynomial  |scalar      |unary expr  |binary expr |monomial    |
|:-----------|-----------------:|:----------:|:----------:|:----------:|:----------:|:----------:|
| complete   | **polynomial**   |`= += -= *=`|`= += -= *=`|`= +=      `|`  +=    *=`|`= += -= *=`|
| incomplete | **polynomial**   |            |            |`     -= *=`|`=    -=   `|`          `|

## Binary arithmetic

### Complete

|                    |polynomial |scalar     |unary expr |binary expr|
|-------------------:|:---------:|:---------:|:---------:|:---------:|
| **polynomial**     | `+  -  *` | `+  -  *` | `+  -  *` | `+  -  *` |
| **scalar**         | `+  -  *` |     X     | `+  -  *` | `+  -  *` |
| **unary expr**     | `+  -  *` | `+  -  *` |(level > 2)| `+  -  *` |
| **binary expr**    | `+  -  *` | `+  -  *` | `+  -  *` |(level > 2)|




