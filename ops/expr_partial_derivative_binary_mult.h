#ifndef PO_EXPR_PARTIAL_DERIVATIVE_BINARY_MULT_H
#define PO_EXPR_PARTIAL_DERIVATIVE_BINARY_MULT_H

namespace po
{
  template<typename E1, typename E2>
  struct expr_partial_derivative<expr_binary_mult<E1, E2>>
  {
    using _E1 = expr_binary_mult<E1, E2>;
    using F1 = subexpr_type<expr_binary_mult<E1, E2>>;

    const F1 expr1;
    const rank_type place;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return
        expr_partial_derivative<E1>{expr1.expr1, place}(x...) * expr1.expr2(x...)
        +
        expr_partial_derivative<E2>{expr1.expr2, place}(x...) * expr1.expr1(x...);
    }
  };

}

#endif



