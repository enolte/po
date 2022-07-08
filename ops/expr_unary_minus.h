#ifndef PO_EXPR_UNARY_MINUS_H
#define PO_EXPR_UNARY_MINUS_H

namespace po
{
  template<typename E1>
  struct expr_unary_minus
  {
    // TODO const lvalue refs for lvalue args
    const E1 expr1;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return scalar_type{-1} * expr1(x...);
    }
  };

  template<typename E>
  constexpr expr_unary_minus<E> operator-(const E& expr)
  {
    return {expr};
  }

}

#endif


