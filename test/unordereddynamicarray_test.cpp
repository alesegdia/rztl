#include "../module/xstf/include/xstf.h"

XSTF_TESTCASE(test_simple_ops)
{

}

bool test_simple_ops()
{
    XSTF_TESTBENCH_INIT("Testing simple operations");

    XSTF_TESTBENCH_FINISH;
}

int main()
{
    XSTF_INIT;

    XSTF_RUN(test_simple_ops);

    return XSTF_ALL_SUCCESS;
}
