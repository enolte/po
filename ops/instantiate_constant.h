#ifndef PO_INSTANTIATE_CONSTANT_H
#define PO_INSTANTIATE_CONSTANT_H

namespace po
{
  template<typename Rank>
  polynomial& instantiate(polynomial& p, const expr_constant& expr, Rank&&)
  {
    p = polynomial(expr.expr1, Rank{});
    return p;
  }
}

#endif