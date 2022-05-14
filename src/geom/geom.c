#include <stdio.h>
#include <string.h>
#include <etry/etry.h>

int main(void)
{
    unsigned short i;
    FILE *f1;
    FILE *f2;
    FILE *f3;
    FILE *f4;
    char arr[1000]; // запись из input
    char mas[1000]; // запись из temp
    char mass[1000]; // запись из tempor и добавление \n при выводе в output 
    short flag = 0;
    f1 = fopen("../bin/data/input.txt", "r+"); 
    if (f1 == NULL)  // защита от "дурака". Создает пустой input.txt если окажется, что такого файла не существует
    {
        f1 = fopen("../bin/data/input.txt", "w");
        fclose(f1);
        printf("Dlya raboti neobhodim input.txt \nSozdan automaticheski.\n");
        return 0;
    }
    fgets(arr, 990, f1);  // записывает из исходного файла строку в массив arr
    fclose(f1);

    f2 = fopen ("../bin/data/temp.txt", "w");   // автосоздание вспомогательного temp.txt
    fclose(f2);
    f3 = fopen ("../bin/data/tempor.txt", "w"); // автосоздание вспомогательного tempor.txt
    fclose(f3);
    f4 = fopen ("../bin/data/output.txt", "w"); // автосоздание вспомогательного output.txt
    fclose(f4);


    f1 = fopen("../bin/data/input.txt", "r+");
    
    for (i=0; i< strlen(arr); i++)                // понижает регистр всех букв (CIrclE => circle)
    {
        if (arr[i] >= 'A' && arr[i] <= 'Z')
        {
            arr[i] += ' ';
        }
    }

    f2 = fopen("../bin/data/temp.txt", "r+"); 
    for (i=0; arr[i]!= '\0'; i++)       // убирает лишние пробелы, оставляя всего лишь один пробел
    {   
        if (arr[i] == ' ' && arr[i+1] == ' ') continue;
        fprintf(f2, "%c", arr[i]);
    }
    fclose(f2);

    f2 = fopen("../bin/data/temp.txt", "r+");       
    fgets(mas, strlen(arr) + 1, f2);    // тут же записывает строку без пробелов и регистров в массив mas
    fclose(f2);

    f3 = fopen("../bin/data/tempor.txt", "r+");     // в этом случае появляется возможность убрать едичиничные пробелы в некоторых местах, еще и для того, чтобы потом можно было без косяков поставить \n
    for (i=0; mas[i]!= '\0'; i++)
    {   
        if (mas[i-1] == '[' && mas[i] == ' ') continue; // не записывает пробел между откр кв скобками
        if (mas[i] == ' ' && mas[i+1] == ']') continue; // не записывает пробел между закр кв скобками
        if (mas[i-1] == '{' && mas[i] == ' ') continue; // не записывает пробел между откр фиг скобками
        if (mas[i] == ' ' && mas[i+1] == '}') continue; // не записывает пробел между закр фиг скобками
        // if (mas[i-1] == '(' && mas[i] == ' ') continue; // не записывает пробел между откр скобками
        if (mas[i-1] == '(' && mas[i] == ' ' && (mas[i+1] != 'p' && mas[i+1] != 't' && mas[i+1] != 'c')) continue; // не записывает пробел между откр скобками
        if (mas[i] == ' ' && mas[i+1] == ')') continue; // не записывает пробел между закр скобками
        if (mas[i-1] >= 'a' && mas[i-1] <= 'z' && mas[i] == ' ') continue; // не записывает пробел после слов
        if (mas[i] == ' ' && mas[i+1] == '.') continue; // не записывает пробел перед точкой (приведет к ошибке вскоре)
        if (mas[i] == ' ' && mas[i+1] == ',') continue; // не записывает пробел перед запятой (между аргументами)
        fprintf(f2, "%c", mas[i]);
    }
    fclose(f3);

    f3 = fopen("../bin/data/tempor.txt", "r+"); // сохраняет изменения уже в массиве mass для записи в выходной файл (output)
    fgets(mass, strlen(mas), f3);
    fclose(f3);

    f4 = fopen("../bin/data/output.txt", "r+"); 
    for (i=0; mass[i]!= '\0'; i++)
    {   

        if (mass[i+1] == '\0') mass[i] = '\n'; // последний символ
        if (mass[i] == ' ' && mass[i+1] == 'p') mass[i] = '\n'; // переносит polygon
        if (mass[i] == ' ' && mass[i+1] == 't') mass[i] = '\n'; // переносит triangle
        if (mass[i] == ' ' && mass[i+1] == 'c') mass[i] = '\n'; // переносит circle
        fprintf(f4, "%c", mass[i]);
    }    
    fclose(f4);

    printf("----------OUTPUT.TXT----------\n"); // отображение массива mass (выходного файла) в консоли
    for (i=0; mass[i]!= '\0'; i++) 
    { 
        printf("%c", mass[i]);
    }

    printf("\n");
    flag = error_detector(mass);

    if (flag == 0)  numcalculator(mass, c);
}