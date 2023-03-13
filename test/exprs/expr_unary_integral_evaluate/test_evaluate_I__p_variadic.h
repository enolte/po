#include "test_evaluate_I__p_variadic_rank_2_2_integrations.h"
#include "test_evaluate_I__p_variadic_rank_3_3_integrations.h"
#include "test_evaluate_I__p_variadic_rank_3_2_integrations.h"
#include "test_evaluate_I__p_variadic_rank_4_1_integration.h"
#include "test_evaluate_I__p_variadic_rank_4_2_integrations.h"

void test_evaluate_I__p_variadic()
{
  test_evaluate_I__p_variadic_rank_2_2_integrations();
  test_evaluate_I__p_variadic_rank_3_3_integrations();
  test_evaluate_I__p_variadic_rank_3_2_integrations();
  test_evaluate_I__p_variadic_rank_4_1_integration();
  test_evaluate_I__p_variadic_rank_4_2_integrations();
}
