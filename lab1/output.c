#include "error.h"
#include "libs.h"
#include "function.h"
#include "chislo.h"
#include "const.h"
/**
 * @brief print_instruction - печатает инструкцию
 */
void print_instruction(void)
{

}

/**
 * @brief print_error - печатает ошибку
 * @param ERROR - код ошибки
 */
void print_error(const int ERROR)
{
    if (ERROR == ERROR_ACCURATELY)
    {
        printf("Entry was successful.\n");
    }
    if (ERROR == ERROR_OVERFLOW)
    {
        printf("ERROR: overflow.\n");
    }
    if (ERROR == ERROR_UNCORRECT_INPUT)
    {
        printf("ERROR: incorrect input.\n");
    }
    if (ERROR == ERROR_NOT_INPUT)
    {
        printf("ERROR: not input.\n");
    }
    if (ERROR == ERROR_OVERFLOW_MANTIS)
    {
        printf("ERROR: overflow mantis.\n");
    }
}
/**
 * @brief print_array - печатает массив
 * @param mass - массив
 * @param size - размер массива
 */
void print_array(const int mass[],const int size)
{
    for (int i=0;i < size;i++)
    {
        if (i == LEN_MANTIS)
        {
            printf("| ");
        }
        printf("%d ",mass[i]);
    }
    printf("\n");
}
/**
 * @brief print_chislo - печатает число хранящаеся в структуре
 * @param chislo - структура хранящая число
 */
void print_chislo(struct chislo chislo)
{
    if (chislo.znak_mantis == -1)
    {
        printf("%c",'-');
    }
    else
    {
        printf("%c",'+');
    }
    printf("0.");
    for (int i=0;i<LEN_MANTIS;i++)
    {
        if (chislo.mantis[i] != -1)
        {
            printf("%d",chislo.mantis[i]);

        }
    }
    printf(" E ");
    if (chislo.poriadok >= 0)
    {
        printf("+%d\n",chislo.poriadok);
    }
    else
    {
        printf("%d\n",chislo.poriadok);
    }
}
