#ifndef PO_EXPR_H
#define PO_EXPR_H

namespace po
{
  template<typename E>
  struct expr
  {
    using expr_type = E;

    template<typename ...X>
    constexpr scalar_type operator()(X... x) const
    {
      // PO_LINE;
      return ((const E&)(*this))(x...);
    }
  };
}

#endif


