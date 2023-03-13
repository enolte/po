#include "ctors/test_ctor_constant_term_initialization.h"
#include "ctors/test_ctor_exprs.h"
#include "ctors/test_ctor_rank_initialization.h"
#include "ctors/test_ctor_terms_initialization.h"
#include "ctors/test_ctor_variable_degrees_initialization.h"

void test_ctors()
{
  test_ctor_exprs();
  test_ctor_constant_term_initialization();
  test_ctor_variable_degrees_initialization();
  test_ctor_rank_initialization();
  test_ctor_terms_initialization();
}