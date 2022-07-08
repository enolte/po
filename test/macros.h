#define PO_TRACE_OSTREAM(o, v) o << v << std::endl

#define PO_MARKER "po: " << __FILE__ << ", " << __LINE__
#define PO_LINE PO_TRACE(PO_MARKER)
#define PO_FUNC PO_TRACE(PO_MARKER << " " << __func__)
#define PO_TRACE(v) PO_TRACE_OSTREAM(std::cout, v)

#define PO_ASSERT(expr, x) \
 ((expr) ||                \
  (                        \
    PO_LINE,               \
    PO_TRACE(PO_MARKER << " : "#expr" evaluated to false, "#x" = " << x), \
    assert(false),         \
    false                  \
  ))                       \

