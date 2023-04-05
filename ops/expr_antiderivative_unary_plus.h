#ifndef PO_EXPR_ANTIDERIVATIVE_UNARY_PLUS_H
#define PO_EXPR_ANTIDERIVATIVE_UNARY_PLUS_H



namespace po
{
  template<typename E1>
  struct expr_antiderivative<expr_unary_plus<E1>>
  {
    using _E1 = expr_unary_plus<E1>;
    using F1 = subexpr_type<expr_unary_plus<E1>>;

    const F1 expr1;
    const rank_type place;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return expr_antiderivative<E1>{expr1.expr1, place}(x...);
    }
  };

}

#endif

