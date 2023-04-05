#ifndef PO_EXPR_INTEGRAL_ANTIDERIVATIVE_H
#define PO_EXPR_INTEGRAL_ANTIDERIVATIVE_H

namespace po
{
  template<expression E1>
  struct expr_antiderivative;

  template<expression E1>
  struct expr_integral<expr_antiderivative<E1>>
  {
    using _E1 = expr_antiderivative<E1>;
    using F1 = subexpr_type<expr_antiderivative<E1>>;

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
  struct expr_integral<const expr_antiderivative<E1>&>
  {
    using _E1 = const expr_antiderivative<E1>&;
    using F1 = subexpr_type<const expr_antiderivative<E1>&>;

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

