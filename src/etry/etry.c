#include <stdio.h>
#include "etry.h"
#include <stdlib.h>
#include <math.h>
#define PI 3.14
#define FIGURELIMIT 10 // установленное макс количество всех хранящихся фигур

short error_detector(char *m) // анализ ошибок
{
    short column = 1;
    short i;
    short flag = 0;  //  в случае, если ошибок нет - flag остается равным нулю, проводит запуск счета фигур
    for (i = 0; m[i] != '\0'; i++)
    {
        if (m[i] == '\n'){
            column++; // подсчет столбцов
            continue;
        }


        if (m[i] == 'c' && m[i+1] == 'l' && m[i+2] == 'e') continue; // не считает конец слова circle как новое слово
        if (m[i] == 'c') flag += circle(m, i, column);  
        if (m[i] == 't') flag += triangle(m, i, column);  
        // if (m[i] == 'p') flag += polygon(m, i, column);  
        if (m[i] == '{' || m[i] == '[')
        {
            printf("Detected syntax error: %c -> ( . In column %d.\n", m[i], column);  
            flag++;
            break;
        }
        if (m[i] == '}' || m[i] == ']')
        {
            printf("Detected syntax error: %c -> ) . In column %d.\n", m[i], column);
            flag++;
            break;  
        }
        if (m[i-1] >= 'a' && m[i-1] <= 'z' && m[i] == '(' && m[i+1] == '(') // ошибки в аргументах треугольника
        {
            flag += argt(m, i, column);
            
        }
        if (m[i-1] >= 'a' && m[i-1] <= 'z' && m[i] == '(' && m[i+1] != '(') // ошибки в аргументах круга
        {
            flag += argc(m, i, column);
            
        }

    }
    return flag;
}


short circle(char *m, short i, short column)
{


    if (m[i+1] == 'i' && m[i+2] == 'r' && m[i+3] == 'c' && m[i+4] == 'l' && m[i+5] == 'e')   return 0;   
        
        printf("Detected syntax error: ");       
        for (; m[i] != '('; i++)
        {
            
            printf("%c", m[i]);
        }
        printf(" -> circle. In column %d.\n", column);
        i += 7;
        return 1;
}


short triangle(char *m, short i, short column)
{

    if (m[i+1] == 'r' && m[i+2] == 'i' && m[i+3] == 'a' && m[i+4] == 'n' && m[i+5] == 'g' && m[i+6] == 'l' && m[i+7] == 'e')   return 0;   
        
        printf("Detected syntax error: ");       
        for (; m[i] != '('; i++)
        {
            
            printf("%c", m[i]);
        }
        printf(" -> triangle. In column %d.\n", column);
        i += 9; 
        return 1;
}

short argc(char *m, short i, short column) // проверка для круга
{   
    short flag = 0;
    short a = 0;
    i++;
    for (; m[i] != '\n'; i++)
    {
        if (m[i] == ' ') a++;
        if (m[i] >= '0' && m[i] <= '9' && m[i+1] == '\n')
        {
            flag++;
            printf("Unexpected token! In column %d.\n", column);
        }    
            
        if (m[i] >= '0' && m[i] <= '9' && m[i+1] == '(') 
        {
            flag++;    
            printf("Detected function error: expected ')' . In column %d.\n", column);
        }
        if (m[i] >= '0' && m[i] <= '9') continue;
        if (m[i] == ',' && m[i+1] != ' ')
        {
            flag++;
            printf("Detected number error: argument has a floating comma (expected a floating point). In column %d.\n", column);
        } 
        
    }
    if (a > 2)
    {
        flag++;
        printf("Too many circle arguments!. In column %d.\n", column);  
    } 
    if (a < 2)
    {
        flag++;
        printf("Too low circle arguments!. In column %d.\n", column);
    }  
    
    return flag;
}


short argt(char *m, short i, short column) // проверка для треугольника
{   
    short flag = 0;
    short a = 0;
    i+=2;
    for (; m[i] != '\n'; i++)
    {   
        if (m[i] == ' ') a++;
        if (m[i] >= '0' && m[i] <= '9' && m[i+1] == '\n' ) 
        {
            flag++;   
            printf("Unexpected token! In column %d.\n", column);
        }
        if (m[i] >= '0' && m[i] <= '9' && m[i+1] == '(')
        {
            flag++;
            printf("Detected function error: expected ')' . In column %d.\n", column);
        }
        if (m[i] >= '0' && m[i] <= '9') continue;
        if (m[i] == ',' && m[i+1] != ' ')
        {
            flag++;
            printf("Detected number error: argument has a floating comma (expected a floating point). In column %d.\n", column); 
        } 
        if (m[i] == ')' && m[i+1] == '(') 
        {
            flag++;
            printf("Detected function error: expected ')' . In column %d.\n", column); 
        }    
            
        
    }
    if (a > 7) 
    {
        flag++;
        printf("Too many triangle arguments!. In column %d.\n", column);
    }
    if (a < 7)
    {
        flag ++;
        printf("Too low triangle arguments!. In column %d.\n", column);
    }
    
    return flag;
}

void numcalculator(char *m, struct Ct* c)
{
    short figure = 0;
    short i = 0, j;
    short a = 0;
    short arg = 1;
    char value[9] = {' '}; // подстрока, идущая под запись вещественного числа в массив структур
    char *endvalue; // указатель на конец подстроки для записи вещественного числа
    float r;
    float ab, bc, ac;
    float ob, aob, ab2, ob2, oc, aoc, ac2, oc2, bc2;
    float t, t1, t2;
    float z, x, v;

    printf("\n----------FIGURES----------\n");
    for (i = 0; m[i] != '\0'; i++)
    {
        if (m[i] == '\n') // видит, что осмотр фигуры завершен, приступает к вычислениям площади и периметра 
        {   
            c[figure].id = figure + 1; // id фигуры тоже хранится
            if (arg == 9) // треугольник
            {
              
                if ((c[figure].x == c[figure].x3) && (c[figure].y == c[figure].y3)) // сохраняет площадь и периметр
                {
                    ab = sqrt(((c[figure].x1 - c[figure].x) * (c[figure].x1 - c[figure].x)) + ((c[figure].y1 - c[figure].y) * (c[figure].y1 - c[figure].y)));
                    bc = sqrt(((c[figure].x2 - c[figure].x1) * (c[figure].x2 - c[figure].x1)) + ((c[figure].y2 - c[figure].y1) * (c[figure].y2 - c[figure].y1)));
                    ac = sqrt(((c[figure].x3 - c[figure].x2) * (c[figure].x3 - c[figure].x2)) + ((c[figure].y3 - c[figure].y2) * (c[figure].y3 - c[figure].y2)));
                    c[figure].area = 0.5 * (((c[figure].x - c[figure].x2) * (c[figure].y1 - c[figure].y2)) - ((c[figure].x1 - c[figure].x2) * (c[figure].y - c[figure].y2)));
                    if (c[figure].area < 0) c[figure].area = -c[figure].area;
                    c[figure].perimeter = ab + bc + ac;
                } 
                arg = 1; 
                figure++; // переход от треугольника к следующей фигуре
                continue;
            }
            if (arg == 3) // круг
            { 
                c[figure].area = PI * c[figure].radius * c[figure].radius;
                c[figure].perimeter = 2 * PI * c[figure].radius;

            }
            arg = 1;
            figure++; // переход от круга к следующей фигуре
            continue;
        }

        if ((m[i-1] == '-' || m[i-1] == '(' || m[i-1] == ' ') && m[i] == '0' && m[i+1] != '.') continue; // не считает лишние нули перед числом или точкой
        if (m[i] == '-' || m[i] == '.') // запись точки или минуса в value
        {
            value[a] = m[i];
            a++;
            continue;
        }
        if (m[i] >= '0' && m[i] <= '9') // запись цифр в value
        {
            value[a] = m[i];
            a++;
            continue;
        }
        if ((m[i] == ' ') && (arg == 1))
        {
            c[figure].x = strtod(value, &endvalue); // преобразует временную строку в вещественное число
            for (a = 0; a < 9; a++)   
	        { 
		        value[a] = ' '; // опустошает массив для следующих чисел
	        } 
            arg++; // переходит к следующему аргументу
            a = 0;
            continue;
        }

        if ((m[i] == ',') && (arg == 2))
        {
            i++;
            c[figure].y = strtod(value, &endvalue); // преобразует временную строку в вещественное число
            for (a = 0; a < 9; a++)    
	        { 
		        value[a] = ' '; // опустошает массив для следующих чисел
	        } 
            arg++; // переходит к следующему аргументу
            a = 0;
            continue;
        }

        if ((m[i] == ')') && (arg == 3))    // определяет круг и записывает его радиус
        {
            c[figure].radius = strtod(value, &endvalue); // преобразует временную строку в вещественное число
            for (a = 0; a < 9; a++)    
	        { 
		        value[a] = ' '; // опустошает массив для следующих чисел
	        }
            a = 0;
            c[figure].type = 'c'; // метка "круг"
            continue;
        }

        /* TRIANGLE READ*/
        
        if ((m[i] == ' ') && (arg == 3)) // определяет треугольник и продолжает заполнять аргументы
        {
            c[figure].x1 = strtod(value, &endvalue); // преобразует временную строку в вещественное число
            for (a = 0; a < 9; a++)   
	        {
		        value[a] = ' '; // опустошает массив для следующих чисел
	        }
            arg++; // переходит к следующему аргументу
            a = 0;
            continue;
        }
        if ((m[i] == ',') && (arg == 4))
        {
            i++;
            c[figure].y1 = strtod(value, &endvalue); // преобразует временную строку в вещественное число
            for (a = 0; a < 9; a++)    
	        {
		        value[a] = ' '; // опустошает массив для следующих чисел
	        }
            arg++; // переходит к следующему аргументу
            a = 0;
            continue;
        }

        if ((m[i] == ' ') && (arg == 5))
        {
            c[figure].x2 = strtod(value, &endvalue); // преобразует временную строку в вещественное число
            for (a = 0; a < 9; a++)   
	        { 
		        value[a] = ' '; // опустошает массив для следующих чисел
	        } 
            arg++; // переходит к следующему аргументу
            a = 0;
            continue;
        }
        if ((m[i] == ',') && (arg == 6))
        {
            i++;
            c[figure].y2 = strtod(value, &endvalue); // преобразует временную строку в вещественное число
            for (a = 0; a < 9; a++)    
	        { 
		        value[a] = ' '; // опустошает массив для следующих чисел
	        } 
            arg++; // переходит к следующему аргументу
            a = 0;
            continue;
        }

        if ((m[i] == ' ') && (arg == 7))
        {
            c[figure].x3 = strtod(value, &endvalue); // преобразует временную строку в вещественное число
            for (a = 0; a < 9; a++)   
	        { 
		        value[a] = ' '; // опустошает массив для следующих чисел
	        } 
            arg++; // переходит к следующему аргументу
            a = 0;
            continue;
        }
        if ((m[i] == ')') && (arg == 8))
        {
            c[figure].y3 = strtod(value, &endvalue); // преобразует временную строку в вещественное число
            for (a = 0; a < 9; a++)    
	        {
	 	        value[a] = ' '; // опустошает массив для следующих чисел
	        } 
            arg++;
            a = 0;
            c[figure].type = 't'; // метка, что это треугольник
            continue;
        }
    }   

    /* CONSOLE OUTPUT AND INTERSECTIONS */
    for (figure = 0; figure < FIGURELIMIT; figure++) // фигура
    {
        if (c[figure].type == 't') // пересечение для треугольника
        {
            printf("%d triangle((%.3f %.3f, %.3f %.3f, %.3f %.3f, %.3f %.3f))\n", c[figure].id, c[figure].x, c[figure].y, c[figure].x1, c[figure].y1, c[figure].x2, c[figure].y2, c[figure].x3, c[figure].y3);
            if ((c[figure].x == c[figure].x3) && (c[figure].y == c[figure].y3))
            {
                printf("\t--perimeter: %.5f \n", c[figure].perimeter);
                printf("\t--area: %.5f \n", c[figure].area);   

                for (j = 0; j < FIGURELIMIT; j++) // поиск пересечений других фигур с этой
                {
                    if (figure == j) continue;
                    if (c[j].type == 'c') // пересечение треугольника с кругом
                    {
                        /* Проверка со стороной аb */
                        ob = (c[figure].x1 - c[j].x) * (c[figure].y1 - c[j].y);
                        ab = (c[figure].x1 - c[figure].x) * (c[figure].y1 - c[figure].y);
                        aob = ob + ab;
                        ab2 = ((c[figure].x1 - c[figure].x) * (c[figure].x1 - c[figure].x)) + ((c[figure].y1 - c[figure].y) * (c[figure].y1 - c[figure].y));
                        ob2 =  ((c[figure].x1 - c[j].x) * (c[figure].x1 - c[j].x)) + ((c[figure].y1 - c[j].y) * (c[figure].y1 - c[j].y));
                        r = c[j].radius * c[j].radius;
                        if ((((aob) * (aob)) - (ab2 * ( ob2 - r ))) >= 0)
                        {
                            t1 = (aob + sqrt(((aob) * (aob)) - (ab2 * ( ob2 - r )))) / ab2;
                            t2 = (aob - sqrt(((aob) * (aob)) - (ab2 * ( ob2 - r )))) / ab2;
                            if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1)) // условие для пересечения треугольника с кругом
                            {
                                printf("\t--intersects with circle:%d \n", c[j].id);
                                continue;
                            }  
                        }
                        /* Проверка со стороной аc */
                        oc = (c[figure].x2 - c[j].x) * (c[figure].y2 - c[j].y);
                        ac = (c[figure].x2 - c[figure].x) * (c[figure].y2 - c[figure].y);
                        aoc = oc + ac;
                        ac2 = ((c[figure].x2 - c[figure].x) * (c[figure].x2 - c[figure].x)) + ((c[figure].y2 - c[figure].y) * (c[figure].y2 - c[figure].y));
                        oc2 =  ((c[figure].x2 - c[j].x) * (c[figure].x2 - c[j].x)) + ((c[figure].y2 - c[j].y) * (c[figure].y2 - c[j].y));
                        if ((((aoc) * (aoc)) - (ac2 * ( oc2 - r ))) >= 0)
                        {
                            t1 = (aoc + sqrt(((aoc) * (aoc)) - (ac2 * ( oc2 - r )))) / ac2;
                            t2 = (aoc - sqrt(((aoc) * (aoc)) - (ac2 * ( oc2 - r )))) / ac2;
                            if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1)) // условие для пересечения треугольника с кругом
                            {
                                printf("\t--intersects with circle:%d \n", c[j].id);
                                continue;
                            }  
                        }
                        /* Проверка со стороной bc */
                        oc = (c[figure].x2 - c[j].x) * (c[figure].y2 - c[j].y);
                        bc = (c[figure].x2 - c[figure].x1) * (c[figure].y2 - c[figure].y1);
                        aoc = oc + bc;
                        bc2 = ((c[figure].x2 - c[figure].x1) * (c[figure].x2 - c[figure].x1)) + ((c[figure].y2 - c[figure].y1) * (c[figure].y2 - c[figure].y1));
                        oc2 =  ((c[figure].x2 - c[j].x) * (c[figure].x2 - c[j].x)) + ((c[figure].y2 - c[j].y) * (c[figure].y2 - c[j].y));
                        if ((((aoc) * (aoc)) - (bc2 * ( oc2 - r ))) >= 0)
                        {
                            t1 = (aoc + sqrt(((aoc) * (aoc)) - (bc2 * ( oc2 - r )))) / bc2;
                            t2 = (aoc - sqrt(((aoc) * (aoc)) - (bc2 * ( oc2 - r )))) / bc2;
                            if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1)) // условие для пересечения треугольника с кругом
                            {
                                printf("\t--intersects with circle:%d \n", c[j].id);
                                continue;
                            }  
                        }
                    }
                    if (c[j].type == 't') // пересечение треугольника с треугольником
                    {
                        /* Проверка с точкой x; y */
                        z = (((c[figure].x - c[j].x) * (c[figure].y1 - c[figure].y)) - ((c[figure].x1 - c[figure].x) * (c[figure].y - c[j].y)));
                        x = (((c[figure].x1 - c[j].x) * (c[figure].y2 - c[figure].y1)) - ((c[figure].x2 - c[figure].x1) * (c[figure].y1 - c[j].y)));
                        v = (((c[figure].x2 - c[j].x) * (c[figure].y3 - c[figure].y2)) - ((c[figure].x3 - c[figure].x2) * (c[figure].y2 - c[j].y)));
                        if (z == 0 || x == 0 || v == 0) // условие для пересечения треугольников
                        {
                            printf("\t--intersects with triangle:%d \n", c[j].id);
                            continue;   
                        }
                        /* Проверка с точкой x1; y1 */
                        z = (((c[figure].x - c[j].x1) * (c[figure].y1 - c[figure].y)) - ((c[figure].x1 - c[figure].x) * (c[figure].y - c[j].y1)));
                        x = (((c[figure].x1 - c[j].x1) * (c[figure].y2 - c[figure].y1)) - ((c[figure].x2 - c[figure].x1) * (c[figure].y1 - c[j].y1)));
                        v = (((c[figure].x2 - c[j].x1) * (c[figure].y3 - c[figure].y2)) - ((c[figure].x3 - c[figure].x2) * (c[figure].y2 - c[j].y1)));
                        if (z == 0 || x == 0 || v == 0) // условие для пересечения треугольников
                        {
                            printf("\t--intersects with triangle:%d \n", c[j].id);
                            continue;   
                        }
                        /* Проверка с точкой x2; y2 */    
                        z = (((c[figure].x - c[j].x2) * (c[figure].y1 - c[figure].y)) - ((c[figure].x1 - c[figure].x) * (c[figure].y - c[j].y2)));
                        x = (((c[figure].x1 - c[j].x2) * (c[figure].y2 - c[figure].y1)) - ((c[figure].x2 - c[figure].x1) * (c[figure].y1 - c[j].y2)));
                        v = (((c[figure].x2 - c[j].x2) * (c[figure].y3 - c[figure].y2)) - ((c[figure].x3 - c[figure].x2) * (c[figure].y2 - c[j].y2)));
                        if (z == 0 || x == 0 || v == 0) // условие для пересечения треугольников
                        {
                            printf("\t--intersects with triangle:%d \n", c[j].id);
                            continue;   
                        }
                    } 
                }             
            }
            else
            {
                printf("\t--triangle is not closed!\n" ); 
            }

        }

        if (c[figure].type == 'c') // пересечение для круга
        {
            printf("%d circle(%.3f %.3f, %.3f)\n", c[figure].id, c[figure].x, c[figure].y, c[figure].radius);
            printf("\t--perimeter: %.5f \n", c[figure].perimeter);
            printf("\t--area: %.5f \n", c[figure].area);

            for (j = 0; j < FIGURELIMIT; j++)
            {
                if (figure == j) continue;
                if (c[j].type == 't') // пересечение круга с теугольником
                {
                    /* Проверка со стороной аb */
                    ob = (c[j].x1 - c[figure].x) * (c[j].y1 - c[figure].y);
                    ab = (c[j].x1 - c[j].x) * (c[j].y1 - c[j].y);
                    aob = ob + ab;
                    ab2 = ((c[j].x1 - c[j].x) * (c[j].x1 - c[j].x)) + ((c[j].y1 - c[j].y) * (c[j].y1 - c[j].y));
                    ob2 =  ((c[j].x1 - c[figure].x) * (c[j].x1 - c[figure].x)) + ((c[j].y1 - c[figure].y) * (c[j].y1 - c[figure].y));
                    r = c[figure].radius * c[figure].radius;
                    if ((((aob) * (aob)) - (ab2 * ( ob2 - r ))) >= 0)
                    {
                        t1 = (aob + sqrt(((aob) * (aob)) - (ab2 * ( ob2 - r )))) / ab2;
                        t2 = (aob - sqrt(((aob) * (aob)) - (ab2 * ( ob2 - r )))) / ab2;
                        if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1)) // условие для пересечения круга с треугольником
                        {
                            printf("\t--intersects with triangle:%d \n", c[j].id);
                            continue;
                        }  
                    }
                    /* Проверка со стороной аc */
                    oc = (c[j].x2 - c[figure].x) * (c[j].y2 - c[figure].y);
                    ac = (c[j].x2 - c[j].x) * (c[j].y2 - c[j].y);
                    aoc = oc + ac;
                    ac2 = ((c[j].x2 - c[j].x) * (c[j].x2 - c[j].x)) + ((c[j].y2 - c[j].y) * (c[j].y2 - c[j].y));
                    oc2 =  ((c[j].x2 - c[figure].x) * (c[j].x2 - c[figure].x)) + ((c[j].y2 - c[figure].y) * (c[j].y2 - c[figure].y));
                    if ((((aoc) * (aoc)) - (ac2 * ( oc2 - r ))) >= 0)
                    {
                        t1 = (aoc + sqrt(((aoc) * (aoc)) - (ac2 * ( oc2 - r )))) / ac2;
                        t2 = (aoc - sqrt(((aoc) * (aoc)) - (ac2 * ( oc2 - r )))) / ac2;
                        if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1)) // условие для пересечения круга с треугольником
                        {
                            printf("\t--intersects with triangle:%d \n", c[j].id);
                            continue;
                        }  
                    }
                    /* Проверка со стороной bc */
                    oc = (c[j].x2 - c[figure].x) * (c[j].y2 - c[figure].y);
                    bc = (c[j].x2 - c[j].x1) * (c[j].y2 - c[j].y1);
                    aoc = oc + bc;
                    bc2 = ((c[j].x2 - c[j].x1) * (c[j].x2 - c[j].x1)) + ((c[j].y2 - c[j].y1) * (c[j].y2 - c[j].y1));
                    oc2 =  ((c[j].x2 - c[figure].x) * (c[j].x2 - c[figure].x)) + ((c[j].y2 - c[figure].y) * (c[j].y2 - c[figure].y));
                    if ((((aoc) * (aoc)) - (bc2 * ( oc2 - r ))) >= 0)
                    {
                        t1 = (aoc + sqrt(((aoc) * (aoc)) - (bc2 * ( oc2 - r )))) / bc2;
                        t2 = (aoc - sqrt(((aoc) * (aoc)) - (bc2 * ( oc2 - r )))) / bc2;
                        if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1)) // условие для пересечения круга с треугольником
                        {
                            printf("\t--intersects with triangle:%d \n", c[j].id);
                            continue;
                        }  
                    }
                }
                if (c[j].type == 'c') // пересечение круга с кругом
                {
                    t = sqrt(((c[j].x - c[figure].x) * (c[j].x - c[figure].x)) + ((c[j].y - c[figure].y) * (c[j].y - c[figure].y)));
                    if (t <= (c[figure].radius + c[j].radius)) // условие для пересечения кругов
                    {
                        printf("\t--intersects with circle:%d \n", c[j].id);      
                    }
                }       
            }
        }
    }

}