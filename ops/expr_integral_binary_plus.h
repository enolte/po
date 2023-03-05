#ifndef PO_EXPR_INTEGRAL_BINARY_PLUS_H
#define PO_EXPR_INTEGRAL_BINARY_PLUS_H



namespace po
{
  template<typename E1, typename E2>
  struct expr_integral<expr_binary_plus<E1, E2>>
  {
    using _E1 = expr_binary_plus<E1, E2>;
    using F1 = expr_field_type<expr_binary_plus<E1, E2>>;

    const F1 expr1;
    const rank_type place;
    const scalar_type a, b;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return expr_integral<E1>{expr1.expr1, place, a, b}(x...) + expr_integral<E2>{expr1.expr2, place, a, b}(x...);
    }
  };

}

#endif

