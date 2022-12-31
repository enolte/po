#ifndef PO_INSTANTIATE_CONSTANT_H
#define PO_INSTANTIATE_CONSTANT_H



namespace po
{
  polynomial& instantiate(polynomial& p, const expr_constant& expr, rank_type rank)
  {
    p = polynomial::make_zero(rank);
    p += expr.expr1;
    return p;
  }

  polynomial& instantiate(polynomial& p, const scalar_type& expr, rank_type rank)
  {
    p = polynomial::make_zero(rank);
    p += expr;
    return p;
  }
}

#endif