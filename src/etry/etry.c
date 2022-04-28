#include <stdio.h>
#include "etry.h"
#include <stdlib.h>
#include <math.h>
#define PI 3.14

short error_detector(char *m)
{
    short column = 1;
    short i;
    short flag;  
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


    if (m[i+1] == 'i' && m[i+2] == 'r' && m[i+3] == 'c' && m[i+4] == 'l' && m[i+5] == 'e' && m[i+6] == '(')   return 0;   
        
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

    if (m[i+1] == 'r' && m[i+2] == 'i' && m[i+3] == 'a' && m[i+4] == 'n' && m[i+5] == 'g' && m[i+6] == 'l'  && m[i+7] == 'e' && m[i+8] == '(')   return 0;   
        
        printf("Detected syntax error: ");       
        for (; m[i] != '('; i++)
        {
            
            printf("%c", m[i]);
        }
        printf(" -> triangle. In column %d.\n", column);
        i += 9; 
        return 1;
}

// short polygon(char *m, short i, short column)
// {

//     if (m[i+1] == 'o' && m[i+2] == 'l' && m[i+3] == 'y' && m[i+4] == 'g' && m[i+5] == 'o' && m[i+6] == 'n' && m[i+7] == '(')   return 0;   
        
//         printf("Detected syntax error: ");       
//         for (short g = i + 8; m[i] != '('; i++)
//         {
            
//             printf("%c", m[i]);
//         }
//         printf(" -> polygon. In column %d.\n", column);
//         i += 8;
//         return 1;
// }

short argc(char *m, short i, short column)
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


short argt(char *m, short i, short column)
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
    short i = 0;
    short a = 0;
    short arg = 1;
    char value[9];
    char *endvalue;
    float carea, cper;
    float tarea, tper;
    float ab, bc, ac;
    for (a = 0; a < 9; a++)
    {
        value[a] = ' ';
    }
    a = 0;
    printf("----------FIGURES----------\n");
    for (i = 0; m[i] != '\0'; i++)
    {
        if (m[i] == '\n') // видит, что осмотр фигуры завершен, приступает к вычислениям площади и периметра 
        {   
            c[figure].id = figure + 1; // id фигуры тоже хранится
            if (arg == 9)
            {
                printf("%d triangle((%.3f %.3f, %.3f %.3f, %.3f %.3f, %.3f %.3f))\n", c[figure].id, c[figure].x, c[figure].y, c[figure].x1, c[figure].y1, c[figure].x2, c[figure].y2, c[figure].x3, c[figure].y3);
                if ((c[figure].x == c[figure].x3) && (c[figure].y == c[figure].y3))
                {
                    ab = sqrt(((c[figure].x1 - c[figure].x) * (c[figure].x1 - c[figure].x)) + ((c[figure].y1 - c[figure].y) * (c[figure].y1 - c[figure].y)));
                    bc = sqrt(((c[figure].x2 - c[figure].x1) * (c[figure].x2 - c[figure].x1)) + ((c[figure].y2 - c[figure].y1) * (c[figure].y2 - c[figure].y1)));
                    ac = sqrt(((c[figure].x3 - c[figure].x2) * (c[figure].x3 - c[figure].x2)) + ((c[figure].y3 - c[figure].y2) * (c[figure].y3 - c[figure].y2)));
                    tarea = 0.5 * (((c[figure].x - c[figure].x2) * (c[figure].y1 - c[figure].y2)) - ((c[figure].x1 - c[figure].x2) * (c[figure].y - c[figure].y2)));
                    if (tarea < 0) tarea = -tarea;
                    tper = ab + bc + ac;

                    printf("\t--perimeter: %.5f \n", tper);
                    printf("\t--area: %.5f \n", tarea);
                } 
                else
                {
                    printf("\t--triangle is not closed!\n" ); 
                }
                arg = 1; 
                figure++; // переход от треугольника к следующей фигуре
                continue;
            }
            if (arg == 3)
            { 
                carea = PI * c[figure].radius * c[figure].radius;
                cper = 2 * PI * c[figure].radius;
                printf("%d circle(%.3f %.3f, %.3f)\n", c[figure].id, c[figure].x, c[figure].y, c[figure].radius);
                printf("\t--perimeter: %.5f \n", cper);
                printf("\t--area: %.5f \n", carea);

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
            continue;
        }
    }   

}