#ifndef PO_EXPR_INTEGRAL_PARTIAL_DERIVATIVE_H
#define PO_EXPR_INTEGRAL_PARTIAL_DERIVATIVE_H

namespace po
{
  template<expression E1>
  struct expr_integral<expr_partial_derivative<E1>>
  {
    using _E1 = expr_partial_derivative<E1>;
    using F1 = expr_field_type<expr_partial_derivative<E1>>;

    const F1 expr1;
    const rank_type place;
    const scalar_type a, b;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      // TODO Without instantiation, probably
      return instantiate(*this)(x...);
    }
  };

  template<typename E1>
  struct expr_integral<const expr_partial_derivative<E1>&>
  {
    using _E1 = const expr_partial_derivative<E1>&;
    using F1 = expr_field_type<const expr_partial_derivative<E1>&>;

    const F1 expr1;
    const rank_type place;
    const scalar_type a, b;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      // TODO Without instantiation, probably
      return instantiate(*this)(x...);
    }
  };

}

#endif

