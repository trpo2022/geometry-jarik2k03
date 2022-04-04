#include <stdio.h>

void args(char *m, short i, short column);
void circle(char *m, short i, short column);
void triangle(char *m, short i, short column);
void polygon(char *m, short i, short column);
void error_detector(char *m);

int main()
{
    char key;
    unsigned short i;
    FILE *f;
    FILE *f1;
    FILE *f2;
    FILE *f3;
    FILE *f4;
    char arr[1000]; // запись из input
    char mas[1000]; // запись из temp
    char mass[1000]; // запись из tempor и добавление \n при выводе в output 
    f1 = fopen("input.txt", "r+"); 
    if (f1 == NULL)  // защита от "дурака". Создает пустой input.txt если окажется, что такого файла не существует
    {
        f1 = fopen("input.txt", "w");
        fclose(f1);
        printf("Dlya raboti neobhodim input.txt \nSozdan automaticheski.\n");
        return 0;
    }
    fgets(arr, 900, f1);                 // записывает из исходного файла строку в массив arr
    fclose(f1);

    f2 = fopen ("temp.txt", "w");   // автосоздание вспомогательного temp.txt
    fclose(f2);
    f3 = fopen ("tempor.txt", "w"); // автосоздание вспомогательного tempor.txt
    fclose(f3);
    f4 = fopen ("output.txt", "w"); // автосоздание вспомогательного output.txt
    fclose(f4);

    f1 = fopen("input.txt", "r+");


    
    for (i=0; i<900; i++)                // понижает регистр всех букв (CIrclE => circle)
    {
        if (arr[i] >= 'A' && arr[i] <= 'Z')
        {
            arr[i] += ' ';
        }
    }

    f2 = fopen("temp.txt", "r+"); 
    for (i=0; arr[i]!= '\0'; i++)       // убирает лишние пробелы, оставляя всего лишь один пробел
    {   
        if (arr[i] == ' ' && arr[i+1] == ' ') continue;
        fprintf(f2, "%c", arr[i]);
    }
    fclose(f2);

    f2 = fopen("temp.txt", "r+");       
    fgets(mas, 900, f2);    // тут же записывает строку без пробелов и регистров в массив mas
    fclose(f2);

    f3 = fopen("tempor.txt", "r+");     // в этом случае появляется возможность убрать едичиничные пробелы в некоторых местах, еще и для того, чтобы потом можно было без косяков поставить \n
    for (i=0; mas[i]!= '\0'; i++)
    {   
        if (mas[i-1] == '[' && mas[i] == ' ') continue; // не записывает пробел между откр кв скобками
        if (mas[i] == ' ' && mas[i+1] == ']') continue; // не записывает пробел между закр кв скобками
        if (mas[i-1] == '{' && mas[i] == ' ') continue; // не записывает пробел между откр фиг скобками
        if (mas[i] == ' ' && mas[i+1] == '}') continue; // не записывает пробел между закр фиг скобками
        // if (mas[i-1] == '(' && mas[i] == ' ') continue; // не записывает пробел между откр скобками
        if (mas[i-1] == '(' && mas[i] == ' ' && (mas[i+1] != 'p' && mas[i+1] != 't' && mas[i+1] != 'c')) continue; // не записывает пробел между откр скобками
        if (mas[i] == ' ' && mas[i+1] == ')') continue; // не записывает пробел между закр скобками
        if (mas[i-1] == 'e' && mas[i] == ' ') continue; // не записывает пробел после слова triangle/cirle 
        if (mas[i-1] == 'n' && mas[i] == ' ') continue; // не записывает пробел после polygon
        if (mas[i] == ' ' && mas[i+1] == '.') continue; // не записывает пробел перед точкой (приведет к ошибке вскоре)
        if (mas[i] == ' ' && mas[i+1] == ',') continue; // не записывает пробел перед запятой (между аргументами)
        fprintf(f2, "%c", mas[i]);
    }
    fclose(f3);

    f3 = fopen("tempor.txt", "r+"); // сохраняет изменения уже в массиве mass для записи в выходной файл (output)
    fgets(mass, 900, f3);
    fclose(f3);

    f4 = fopen("output.txt", "r+"); 
    for (i=0; mass[i]!= '\0'; i++)
    {   
        if (mass[i-1] == ']' && mass[i] == ' ') mass[i] = '\n'; // ставится \n и записывается в итоговый файл
        if (mass[i-1] == '}' && mass[i] == ' ') mass[i] = '\n'; // ставится \n и записывается в итоговый файл
        if (mass[i-1] == ')' && mass[i] == ' ') mass[i] = '\n'; // ставится \n и записывается в итоговый файл
        if (mass[i] == ' ' && mass[i+1] == 'p') mass[i] = '\n'; // переносит polygon
        if (mass[i] == ' ' && mass[i+1] == 't') mass[i] = '\n'; // переносит triangle
        if (mass[i] == ' ' && mass[i+1] == 'c') mass[i] = '\n'; // переносит circle
        fprintf(f4, "%c", mass[i]);
    }    
    fclose(f4);

    printf("Vihodnye znacheniya iz faila output.txt:\n"); // отображение массива mass (выходного файла) в консоли
    for (i=0; mass[i]!= '\0'; i++) 
    { 
        printf("%c", mass[i]);
    }

    error_detector(mass);
}



void error_detector(char *m)
{
    short column = 1;
    short i;
    for (i = 0; m[i] != '\0'; i++)
    {
        if (m[i] == '\n'){
            column++;           // подсчет столбцов
            continue;
        }

        if (m[i] == '{' || m[i] == '[')
        {
            printf("Detected syntax error: %c -> ( . In column %d.\n", m[i], column);  
            break;
        }
        if (m[i] == '}' || m[i] == ']')
        {
            printf("Detected syntax error: %c -> ) . In column %d.\n", m[i], column);
            break;  
        }

        if (m[i] == '(')                                // анализ ошибок в скобках
        {
                args(m, i, column);
        }
        if (m[i] == 'c' && m[i+1] == 'l' && m[i+2] == 'e') continue; // не считает конец слова circle как новое слово
        if (m[i] == 'c') circle(m, i, column);  
        if (m[i] == 't') triangle(m, i, column);  
        if (m[i] == 'p') polygon(m, i, column);  
    }
    
}

void circle(char *m, short i, short column)
{

    if (m[i+1] == 'i' && m[i+2] == 'r' && m[i+3] == 'c' && m[i+4] == 'l' && m[i+5] == 'e' && m[i+6] == '(')   return;   
        
        printf("Detected syntax error: ");       
        for (short g = i + 7; m[i] != '('; i++)
        {  
            printf("%c", m[i]);
        }
        printf(" -> circle. In column %d\n.", column);
        i += 7;
}

void triangle(char *m, short i, short column)
{

    if (m[i+1] == 'r' && m[i+2] == 'i' && m[i+3] == 'a' && m[i+4] == 'n' && m[i+5] == 'g' && m[i+6] == 'l'  && m[i+7] == 'e' && m[i+8] == '(')   return;   
        
        printf("Detected syntax error: ");       
        for (short g = i + 9; m[i] != '('; i++)
        {      
            printf("%c", m[i]);
        }
        printf(" -> triangle. In column %d\n.", column);
        i += 9; 
    
}

void polygon(char *m, short i, short column)
{

    if (m[i+1] == 'o' && m[i+2] == 'l' && m[i+3] == 'y' && m[i+4] == 'g' && m[i+5] == 'o' && m[i+6] == 'n'  && m[i+7] == '(')   return;   
        
        printf("Detected syntax error: ");       
        for (short g = i + 8; m[i] != '('; i++)
        {    
            printf("%c", m[i]);
        }
        printf(" -> polygon. In column %d\n.", column);
        i += 8;    
}

void args(char *m, short i, short column)
{   
    i++;
    for (i; m[i] != '\n'; i++)
    {

        if (m[i] >= '0' && m[i] <= '9') continue;
        if (m[i] >= 'a' && m[i] <= 'z') printf("Detected arg error: argument has a symbol type. In column %d\n.", column);
        if (m[i] == ',' && m[i+1] != ' ') printf("Detected number error: argument has a floating comma (expected a floating point). In column %d\n.", column);
        if (m[i] == ')' && m[i+1] == '(') printf("Detected function error: expected ')' . In column %d\n.", column);
    }   
}
