#include <stdio.h>

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

    f2 = fopen ("temp.txt", "w");   // автосоздание вспомогательного temp.txt
    fclose(f2);
    f3 = fopen ("tempor.txt", "w"); // автосоздание вспомогательного tempor.txt
    fclose(f3);
    f4 = fopen ("output.txt", "w"); // автосоздание вспомогательного output.txt
    fclose(f4);

    f1 = fopen("input.txt", "r+");
    fgets(arr, 900, f1);                 // записывает из исходного файла строку в массив arr
    fclose(f1);
    
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
        if (mas[i-1] == '(' && mas[i] == ' ') continue; // не записывает пробел между откр скобками
        if (mas[i] == ' ' && mas[i+1] == ')') continue; // не записывает пробел между закр скобками
        if (mas[i-1] == 'e' && mas[i] == ' ') continue; // не записывает пробел после слова triangle/cirle 
        if (mas[i-1] == 'n' && mas[i] == ' ') continue; // не записывает пробел после polygon
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
        if (mass[i-1] == ')' && mass[i] == ' ') mass[i] = '\n'; // ставится \n и записывается в итоговый файл
        fprintf(f4, "%c", mass[i]);
    }    
    fclose(f4);

    printf("Vihodnye znacheniya iz faila output.txt:\n"); // отображение массива mass (выходного файла) в консоли
    for (i=0; mass[i]!= '\0'; i++) 
    { 
        printf("%c", mass[i]);
    }
}
