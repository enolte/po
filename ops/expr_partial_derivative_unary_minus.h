#ifndef PO_EXPR_PARTIAL_DERIVATIVE_UNARY_MINUS_H
#define PO_EXPR_PARTIAL_DERIVATIVE_UNARY_MINUS_H



namespace po
{
  template<typename E1>
  struct expr_partial_derivative<expr_unary_minus<E1>>
  {
    using _E1 = expr_unary_plus<E1>;
    using F1 = subexpr_type<expr_unary_minus<E1>>;

    const F1 expr1;
    const rank_type place;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return -1. * D(expr1, place);
    }
  };

}

#endif

