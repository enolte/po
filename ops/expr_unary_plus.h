#ifndef PO_EXPR_UNARY_PLUS_H
#define PO_EXPR_UNARY_PLUS_H

namespace po
{
  template<typename E1>
  struct expr_unary_plus
  {
    // TODO const lvalue refs for lvalue args
    const E1 expr1;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return expr1(x...);
    }
  };

  template<typename E>
  constexpr expr_unary_plus<E> operator+(E expr)
  {
    return {expr};
  }

}

#endif

