#include <etry/etry.h>
#include "../thirdparty/ctest.h"

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

CTEST(ctest, circle_error_detector)
{
    char m[] = "circle(-2.86 2.345, 4.53)\n";
    int flag_exp = 0;
    int flag = error_detector(m);
    ASSERT_EQUAL(flag_exp, flag);
}

CTEST(ctest, triangle_error_detector)
{
    char m[] = "triangle((-2 9, 2 6, -8 0, -2 9))\n";
    int flag_exp = 0;
    int flag = error_detector(m);
    ASSERT_EQUAL(flag_exp, flag);
}

CTEST(ctest, t_area_test)
{
    struct Ct c1;
    char m[] = "triangle((-2 9, 2 6, -8 0, -2 9))\n";
    c1.area = 27;
    numcalculator(m, c);
    ASSERT_EQUAL(c1.area, c[0].area);
}

CTEST(ctest, c_area_test)
{
    struct Ct c1;
    char m[] = "circle(-7.82 10.3, 12)\n";
    c1.area = 452.16;
    numcalculator(m, c);
    ASSERT_EQUAL(c1.area, c[0].area);
}

CTEST(ctest, t_perimeter_test)
{
    struct Ct c1;
    char m[] = "triangle((-2 9, 2 6, -8 0, -2 9))\n";
    c1.perimeter = 27.47;
    numcalculator(m, c);
    ASSERT_EQUAL(c1.perimeter, c[0].perimeter);
}

CTEST(ctest, c_perimeter_test)
{
    struct Ct c1;
    char m[] = "circle(-7.82 10.3, 12)\n";
    c1.perimeter = 75.36;
    numcalculator(m, c);
    ASSERT_EQUAL(c1.perimeter, c[0].perimeter);
}

CTEST(ctest, c_intersection_test)
{
    short flag;
    char m[] = "circle(-7.82 10.3, 12)\ncircle(-2.86 2.345, 4.53)\n";
    short flag_exp = 2;
    flag = numcalculator(m, c);
    ASSERT_EQUAL(flag_exp, flag);
}

CTEST(ctest, t_intersection_test)
{
    short flag;
    char m[] = "triangle((-3 -2, -1 0, -3 2, -3 -2))\ntriangle((-1 7, 2 9, 13 -5, -1 7))\n";
    short flag_exp = 0;
    flag = numcalculator(m, c);
    ASSERT_EQUAL(flag_exp, flag);
}
