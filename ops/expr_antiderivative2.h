#ifndef PO_EXPR_ANTIDERIVATIVE_ANTIDERIVATIVE_H
#define PO_EXPR_ANTIDERIVATIVE_ANTIDERIVATIVE_H



namespace po
{
  template<expression E1>
  struct expr_antiderivative<expr_antiderivative<E1>>
  {
    using _E1 = expr_antiderivative<E1>;
    using F1 = subexpr_type<expr_antiderivative<E1>>;

    const F1 expr1;
    const rank_type place;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      // TODO Without instantiation, maybe
      return instantiate(*this)(x...);
    }
  };

  template<expression E1>
  struct expr_antiderivative<const expr_antiderivative<E1>&>
  {
    using _E1 = expr_antiderivative<E1>;
    using F1 = subexpr_type<expr_antiderivative<E1>>;

    const F1 expr1;
    const rank_type place;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      // TODO Without instantiation, maybe
      return instantiate(*this)(x...);
    }
  };
}

#endif

