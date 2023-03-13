#ifndef PO_EXPR_INTEGRAL_INTEGRAL_H
#define PO_EXPR_INTEGRAL_INTEGRAL_H



namespace po
{
  template<expression E1>
  struct expr_integral<expr_integral<E1>>
  {
    using _E1 = expr_integral<E1>;
    using F1 = subexpr_type<expr_integral<E1>>;

    const F1 expr1;
    const rank_type place;
    const scalar_type a, b;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      // TODO Without instantiation, maybe
      return instantiate(*this)(x...);
    }
  };

  template<expression E1>
  struct expr_integral<const expr_integral<E1>&>
  {
    using _E1 = expr_integral<E1>;
    using F1 = subexpr_type<expr_integral<E1>>;

    const F1 expr1;
    const rank_type place;
    const scalar_type a, b;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      // TODO Without instantiation, maybe
      return instantiate(*this)(x...);
    }
  };
}

#endif

