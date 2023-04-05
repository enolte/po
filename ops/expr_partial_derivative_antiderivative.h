#ifndef PO_EXPR_PARTIAL_DERIVATIVE_ANTIDERIVATIVE_H
#define PO_EXPR_PARTIAL_DERIVATIVE_ANTIDERIVATIVE_H

namespace po
{
  template<expression E1>
  struct expr_antiderivative;

  template<expression E1>
  struct expr_partial_derivative<expr_antiderivative<E1>>
  {
    using _E1 = expr_antiderivative<E1>;
    using F1 = subexpr_type<expr_antiderivative<E1>>;

    const F1 expr1;

    const rank_type place;

    template<scalar ...X>
    scalar_type operator()(X... x) const
    {
      // TODO without instantitation
      auto p = instantiate(expr1);
      return D(p, place)(x...);
    }
  };

  template<expression E1>
  struct expr_partial_derivative<const expr_antiderivative<E1>&>
  {
    using _E1 = expr_antiderivative<E1>;
    using F1 = subexpr_type<const expr_antiderivative<E1>&>;

    const F1 expr1;

    const rank_type place;

    template<scalar ...X>
    scalar_type operator()(X... x) const
    {
      // TODO without instantitation
      auto p = instantiate(expr1);
      return D(p, place)(x...);
    }
  };

}

#endif



