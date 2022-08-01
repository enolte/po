# Expression Testing

Current status tables. Tests are implemented per-expression, where expressions are partially [sorted into levels by number of operators](./expression-testing-by-num-operators.md). Verification is generally limited to levels 0 - 2, with some additional expressions with more than 2 operators already verified. Expressions at level > 2 will be systematically unit-tested as time available.

The following tables summarize expressions at level 2 which have been systematically tested and verified. Compiler front-end limitations prevent translation of a single translation unit with all level 2 expressions.

"*ext*" denotes a possible extension which may or may not be implemented later.

## Unary


### Complete

| status     |scalar   |polynomial|unary expr|binary expr|monomial (*ext*)|
|:-----------|:-------:|:--------:|:--------:|:---------:|:--------------:|
| complete   | `+ - D` | `+ - D`  |          |           |                |
| incomplete |         |          | `+ - D`  | `+ - D`   | `+ - D`        |

Unary and binary exprs need further testing.


## Binary assignment

| status     |                  |polynomial    |scalar        |unary expr    |binary expr   |monomial      |init-list (*ext*)|
|:-----------|-----------------:|:------------:|:------------:|:------------:|:------------:|:------------:|:---------------:|
| complete   | **polynomial**   |`= +=  -=  *=`|`= +=  -=  *=`|              |              |`  +=  -=  *=`|`= +=  -=  *=`   |
| incomplete | **polynomial**   |              |              |`= +=  -=  *=`|`= +=  -=  *=`|`=`           |                 |



## Binary arithmetic


### Complete

|                    |polynomial |scalar     |unary expr |binary expr|monomial   |init-list(ext)|
|-------------------:|:---------:|:---------:|:---------:|:---------:|:---------:|:------------:|
| **polynomial**     | `+  -  *` | `+  -  *` | `+  -  *` | `+  -  *` |           |              |
| **scalar**         | `+  -  *` |     X     | `+  -  *` | `+  -  *` |           |              |
| **unary expr**     | `+  -  *` | `+  -  *` |(level > 2)| `+  -  *` |           |              |
| **binary expr**    | `+  -  *` | `+  -  *` | `+  -  *` |(level > 2)|           |              |
| **monomial**       |           |           |           |           |           |              |
| **init-list(ext)** |           |           |           |           |           |      X       |

### Incomplete

|                    |polynomial |scalar     |unary expr |binary expr|monomial   |init-list(ext)|
|-------------------:|:---------:|:---------:|:---------:|:---------:|:---------:|:------------:|
| **polynomial**     |           |           |           |           | `+  -  *` | `+  -  *`    |
| **scalar**         |           |     X     |           |           | `+  -  *` | `+  -  *`    |
| **unary expr**     |           |           |(level > 2)|           | `+  -  *` | `+  -  *`    |
| **binary expr**    |           |           |           |(level > 2)| `+  -  *` | `+  -  *`    |
| **monomial**       |           |           |           |           | `+  -  *` | `+  -  *`    |
| **init-list(ext)** | `+  -  *` | `+  -  *` | `+  -  *` | `+  -  *` | `+  -  *` |      X       |







