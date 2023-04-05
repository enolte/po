#ifndef PO_EXPR_ANTIDERIVATIVE_BINARY_MINUS_H
#define PO_EXPR_ANTIDERIVATIVE_BINARY_MINUS_H



namespace po
{
  template<typename E1, typename E2>
  struct expr_antiderivative<expr_binary_minus<E1, E2>>
  {
    using _E1 = expr_binary_minus<E1, E2>;
    using F1 = subexpr_type<expr_binary_minus<E1, E2>>;

    const F1 expr1;
    const rank_type place;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return
        expr_antiderivative<E1>{expr1.expr1, place}(x...) -
        expr_antiderivative<E2>{expr1.expr2, place}(x...);
    }
  };

}

#endif

