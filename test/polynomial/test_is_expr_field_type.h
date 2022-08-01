#include "../../ops/is_expr_field_type.h"

void test_is_expr_field_type()
{
  PO_LINE;
}

// std::is_const implements these facts:
static_assert(std::is_const_v<const int>);
static_assert(!std::is_const_v<const int&>);
static_assert(!std::is_const_v<const int&&>);

static_assert(!std::is_const_v<int>);
static_assert(!std::is_const_v<int&>);
static_assert(!std::is_const_v<int&&>);

// is_expr_field_type implements these:
static_assert(po::is_expr_field_type<const int>);
static_assert(po::is_expr_field_type<const int&>);
static_assert(po::is_expr_field_type<const int&&>);

static_assert(!po::is_expr_field_type<int>);
static_assert(!po::is_expr_field_type<int&>);
static_assert(!po::is_expr_field_type<int&&>);







