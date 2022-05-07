#include <etry/etry.h>
#include <ctest.h>

CTEST(ctest, circle_args)
{
    int i = 0;
    char m[] = "(-7.82 10.3, 12)\n";
    int flag_exp = 0;
    int flag = argc(m, i, 1);
    ASSERT_EQUAL(flag_exp, flag);
}

CTEST(ctest, triangle_args)
{
    int i = 0;
    char m[] = "((-1 7, 2 9, 13 -5, -1 7))\n";
    int flag_exp = 0;
    int flag = argt(m, i, 1);
    ASSERT_EQUAL(flag_exp, flag);
}

CTEST(ctest, circle_word)
{
    int i = 0;
    char m[] = "circle";
    int flag_exp = 0;
    int flag = circle(m, i, 1);
    ASSERT_EQUAL(flag_exp, flag);
}

CTEST(ctest, triangle_word)
{
    int i = 0;
    char m[] = "triangle";
    int flag_exp = 0;
    int flag = triangle(m, i, 1);
    ASSERT_EQUAL(flag_exp, flag);
}