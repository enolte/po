#ifndef PO_EXPR_INTEGRAL_UNARY_MINUS_H
#define PO_EXPR_INTEGRAL_UNARY_MINUS_H



namespace po
{
  template<typename E1>
  struct expr_integral<expr_unary_minus<E1>>
  {
    using _E1 = expr_unary_minus<E1>;
    using F1 = expr_field_type<expr_unary_minus<E1>>;

    const F1 expr1;
    const rank_type place;
    const scalar_type a, b;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return -expr_integral<E1>{expr1.expr1, place, a, b}(x...);
    }
  };

}

#endif

