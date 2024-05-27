#ifndef PO_INSTANTIATE_CONSTANT_H
#define PO_INSTANTIATE_CONSTANT_H



namespace po
{
  static polynomial& instantiate(polynomial& p, const expr_constant& expr, rank_type rank)
  {
    p.zero(rank);
    return p += expr.expr1;
  }

  static polynomial& instantiate(polynomial& p, const scalar_type& expr, rank_type rank)
  {
    p.zero(rank);
    return p += expr;
  }
}

#endif

