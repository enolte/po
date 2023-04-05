#ifndef PO_EXPR_ANTIDERIVATIVE_DERIVATIVE_H
#define PO_EXPR_ANTIDERIVATIVE_DERIVATIVE_H



namespace po
{
  template<expression E1>
  struct expr_antiderivative<expr_partial_derivative<E1>>
  {
    using _E1 = expr_partial_derivative<E1>;
    using F1 = subexpr_type<expr_partial_derivative<E1>>;

    const F1 expr1;
    const rank_type place;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      if(place == expr1.place)
        return expr1.expr1(x...);
      else
        // TODO Without instantiation
        return instantiate(*this)(x...);
    }
  };

  template<expression E1>
  struct expr_antiderivative<const expr_partial_derivative<E1>&>
  {
    using _E1 = expr_partial_derivative<E1>;
    using F1 = subexpr_type<expr_partial_derivative<E1>>;

    const F1 expr1;
    const rank_type place;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      if(place == expr1.place)
        return expr1.expr1(x...);
      else
        // TODO Without instantiation
        return instantiate(*this)(x...);
    }
  };
}

#endif

