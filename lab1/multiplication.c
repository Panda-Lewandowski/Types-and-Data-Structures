#include "const.h"
#include "libs.h"
#include "error.h"
#include "chislo.h"
#include "function.h"
/**
 * @brief mult_digit - перемножает число на массив и прибавляет к промежуточному массиву
 * @param temp_mass - промежуточный массиы
 * @param ch - массив исходный равен мантиссе
 * @param chislo - число
 * @param k - отступ порядка
 * @return
 */
int mult_digit(int *temp_mass,const int ch[],const int chislo,const int k)
{
    int ERROR = ERROR_ACCURATELY;
    int temp;
    //printf("BEFORE MULT: ");
    //print_array(temp_mass,LEN_TEMP_MASS);
    for (int j = 0;j < LEN_MANTIS;j++)
    {
        if (ch[j] != -1)
        {
            temp = chislo * ch[j];
            temp_mass[k + j] += temp;
        }
        else
        {
            break;
        }
    }
    //printf("AFTER  MULT: ");
    //print_array(temp_mass,LEN_TEMP_MASS);
    return ERROR;
}
/**
 * @brief round_temp_mass - округляет промежуточный массив
 * @param temp_mass - промежуточный массив
 * @return
 */
int round_temp_mass(int *temp_mass)
{
    if (temp_mass[LEN_MANTIS] >= 5)
    {
        temp_mass[LEN_MANTIS - 1] += 1;
    }
    return ERROR_ACCURATELY;
}
/**
 * @brief copy_mass - копирует один массив в другой
 * @param ch - массив куда копируют
 * @param mass - массив из которого берут элементы
 * @return
 */
int copy_mass(int *ch, int *mass)
{
    for (int i=0;i < LEN_MANTIS;i++)
    {
        ch[i] = mass[i];
    }
    return ERROR_ACCURATELY;
}
/**
 * @brief round_chislo 0 нормализует число и округляет его элементы до однозначного
 * @param chislo1 - число
 * @return
 */
int round_chislo(int *temp_mass,int *poriadok,int *i)
{
    int normal=0;
    while (normal == 0)
    {
        normal = 1;
        //printf("Befor sdvig: ");
        //print_array(temp_mass,LEN_TEMP_MASS);
        if (temp_mass[0] > 9)
        {
            *poriadok += 1;
            *i += 1;
            for (int j= LEN_TEMP_MASS - 1; j > 0; j--)
            {
                temp_mass[j] = temp_mass[j - 1];
            }
            temp_mass[0] = 0;
        }
        //printf("After sdvig: ");
        //print_array(temp_mass,LEN_TEMP_MASS);
        //printf("kek");
        for (int i = LEN_TEMP_MASS - 1; i > 0; i--)
        {
            if (temp_mass[i] > 9)
            {
                //printf("%d\n",i);
                normal = 0;
                temp_mass[i - 1] += temp_mass[i] / 10;
                temp_mass[i] %= 10;
            }
        }
        //printf("After round: ");
        //print_array(temp_mass,LEN_TEMP_MASS);
    }
    return ERROR_ACCURATELY;
}
/**
 * @brief multiplicate - перемножает 2 числа
 * @param chislo1 - первое число
 * @param chislo2 - второе число
 * @return
 */
int multiplicate(struct chislo *chislo1,struct chislo chislo2)
{
    int ERROR = ERROR_ACCURATELY;
    int temp_mass[LEN_TEMP_MASS];
    int k=0;
    set_array_null(temp_mass,LEN_TEMP_MASS);
    chislo1->znak_mantis *= chislo2.znak_mantis;
    chislo1->poriadok += chislo2.poriadok;
    if (chislo1->poriadok > 99999)
    {
        return ERROR_OVERFLOW;
    }
    if (ERROR == ERROR_ACCURATELY)
    {
        for (int i=0; i < LEN_MANTIS && chislo2.mantis[i] != -1; i++)
        {
            mult_digit(temp_mass,chislo1->mantis,chislo2.mantis[i],k);
            round_chislo(temp_mass,&chislo1->poriadok,&k);
            k++;
        }
        //print_array(temp_mass,LEN_TEMP_MASS);
        //printf("round_temp_mass");

        //print_array(temp_mass,LEN_TEMP_MASS);
        round_temp_mass(temp_mass);
        round_chislo(temp_mass,&chislo1->poriadok,0);
        //printf("copy_mass");
        copy_mass(chislo1->mantis,temp_mass);
        //printf("round_chislo");
        //printf("set_array_back");
        chislo1->poriadok -= 1;
        if (chislo1->mantis[0] == 0)
        {
            chislo1->poriadok = 0;
        }
        set_array_back(chislo1->mantis);
        //printf("%d",chislo1->poriadok);
        if (chislo1->poriadok > 99999 || chislo1->poriadok < -99999 )
        {
            ERROR = ERROR_OVERFLOW;
        }
    }
    return ERROR;
}
