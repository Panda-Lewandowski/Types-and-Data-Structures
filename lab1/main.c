#include "libs.h"
#include "const.h"
#include "function.h"
#include "error.h"
#include "chislo.h"
//TODO
//Проверить первое число на целое +
//Точка в порядке +
//Переполнение < -99999 +
//30 девяток на 2 округление +
int main()
{
    struct chislo ch1;//Первое число
    struct chislo ch2;//Второе число
    //Печать инструкции
    print_instruction();
    //Обнуление массивов мантиссы чисел
    set_array_null(ch1.mantis,LEN_MANTIS + 1);
    set_array_null(ch2.mantis,LEN_MANTIS + 1);
    int ERROR;
    printf("Input integer number\n");
    printf("-----------------------------|\n");
    ERROR = read_chislo(&ch1,0);
    //В случае удачного ввода первого числа вводит второе
    if (ERROR == ERROR_ACCURATELY)
    {
        printf("\nInput float number\n");
        printf("-----------------------------|\n");
        ERROR = read_chislo(&ch2,1);
    }
    //При необходимости печать
    if (ERROR == 100)
    {
        print_chislo(ch1);
        print_chislo(ch2);
    }
    //При корректном вводе перемножает 2 числа
    if (ERROR == ERROR_ACCURATELY)
    {
        ERROR = multiplicate(&ch1,ch2);
        if (ERROR == ERROR_ACCURATELY)
        {
            printf("\n\nRESULT: ");
            print_chislo(ch1);
        }
    }
    printf("\n\n");
    print_error(ERROR);
}
