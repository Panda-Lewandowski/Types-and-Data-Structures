#include "const.h"
#include "libs.h"
#include "error.h"
#include "chislo.h"
#include "function.h"

/**
 * @brief set_array_back - меняет незначащие нули на -1
 * @param chislo - массив мантиссы
 * @return
 */
int set_array_back(int *chislo)
{
    for (int i=LEN_MANTIS - 1;chislo[i] == 0;i--)
    {
        chislo[i] = -1;
    }
    return ERROR_ACCURATELY;
}

/**
 * @brief check_count_simbol - проверяет количество вхождений '.' '-' '+' 'E'
 * @param ch1 - cтрока ввода
 * @return
 */
int check_count_simbol(char *ch1)
{
    int ERROR = ERROR_ACCURATELY;
    int e = count('E',ch1);
    int plus = count('+',ch1);
    int minus = count('-',ch1);
    int point = count('.',ch1);
    if (e > 1)
    {
        printf("count e = %d\n",e);
        ERROR = ERROR_UNCORRECT_INPUT;
    }
    if (point > 1)
    {
        printf("count . = %d\n",point);
        ERROR = ERROR_UNCORRECT_INPUT;
    }
    if ((plus + minus) > 2)
    {
        ERROR = ERROR_UNCORRECT_INPUT;
    }
    return ERROR;
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
/**
 * @brief take_mantis - берет из введенной строки мантиссу
 * @param str - строка
 * @param mantis - массив под мантиссу
 * @param poriadok - порядок
 * @param znak_mantis - знак мантиссы
 * @return
 */
int take_mantis(char *str,int *mantis,int *poriadok,int *znak_mantis)
{
    //printf("take_mantis start.\n");
    int ERROR = ERROR_ACCURATELY;
    int index_str=0,index_mantis=0;
    int flag_point = 0;
    int flag_znak = 0;
    *poriadok = 0;
    //Взятие знака
    if (str[0] == '-')
    {
        flag_znak = 1;
        *znak_mantis = -1;
        index_str += 1;
    }
    else
    {
        if (str[0] == '+')
        {
            flag_znak = 1;
            index_str += 1;
        }
        *znak_mantis = 1;
    }
    //Проверка если в строке 1 символ
    //printf("str[index_str] = %c\n",str[index_str]);
    //printf("str[index_str + 1] = %c\n",str[index_str + 1]);
    //printf("str[index_str + 3] = %d\n",str[index_str + 3]);
    if (str[index_str + 1] == '\0')
    {
        //printf("1 simvol");
        if (str[index_str] >= '0' && str[index_str] <= '9')
        {
            mantis[0] = str[index_str] - '0';
            if (str[index_str] != '0')
            {
                *poriadok += 1;
            }
            return ERROR;
        }
        else
        {
            return ERROR_UNCORRECT_INPUT;
        }
    }
    //Проверка на 0. ...
    if (str[index_str] == '0' && str[index_str + 1] == '.' && str[index_str + 2] != '\0')
    {
        //printf("0. ...");
        flag_point = 1;
        index_str += 2;
        if (str[index_str] == '0')
        {
            while (str[index_str] == '0')
            {
                *poriadok -= 1;
                index_str += 1;
            }
            if ((str[index_str] == '\0' || str[index_str] == 'E') && index_str > 3)
            {
                return ERROR_UNCORRECT_INPUT;
            }
            if ((str[index_str] == '\0' || str[index_str] == 'E') && index_str == 3)
            {
                *poriadok = 0;
            }
        }
    }
    //Проверка на .1254 .0000001241
    if (str[index_str] == '.' && str[index_str + 1] != '\0' && str[index_str + 2] != '\0' )
    {
        //printf(".1254");
        //printf("%c",str[index_str]);
        index_str += 1;
        flag_point = 1;
        if (str[index_str] == '0')
        {
            while (str[index_str] == '0')
            {
                *poriadok -= 1;
                index_str += 1;
            }
            //printf(" %d ",'\0');
            //printf(" %d ",str[index_str]);
            if (str[index_str] == '\0' || str[index_str] == 'E')
            {
                if (index_str > 30)
                {
                    return ERROR_OVERFLOW_MANTIS;
                }
                else
                {
                    return ERROR_UNCORRECT_INPUT;
                }
            }
        }
    }
    //Проверка 0.
    if (str[index_str] == '0' && str[index_str + 1] == '.' && str[index_str + 2] == '\0')
    {
        //printf("0.");
        return ERROR;
    }
    //Проверка .0
    if (str[index_str] == '.' && str[index_str + 1] == '0' && str[index_str + 2] == '\0')
    {
        //printf(".0");
        return ERROR;
    }
    //Проверка 002. число начинается с нуля
    if (str[0] == '0' && str[1] >= '0' && str[1] <= '9')
    {
        return ERROR_UNCORRECT_INPUT;
    }
    if (ERROR == ERROR_ACCURATELY)
    {
        //printf("Cickle");
        while (!(str[index_str] == 'E' || str[index_str] == '\0'))
        {
            //проверка на встречу знака + - в мантисе второй раз
            if ((str[index_str] == '+' || str[index_str] == '-') && flag_znak == 1)
            {
                ERROR = ERROR_UNCORRECT_INPUT;
                break;
            }
            //сигнал встречи точки
            if (str[index_str] == '.')
            {
                flag_point = 1;
                index_str += 1;
            }
            else if (flag_point == 0)
            {
                if (str[index_str] >= '0' && str[index_str] <= '9')
                {
                    mantis[index_mantis] = str[index_str] - '0';
                    index_mantis += 1;
                    *poriadok += 1;
                }
                index_str += 1;
            }
            else
            {
                if (str[index_str] >= '0' && str[index_str] <= '9')
                {
                    mantis[index_mantis] = str[index_str] - '0';
                    index_mantis += 1;
                }
                index_str += 1;
            }
        }
    }
    if (index_str > 30)
    {
        ERROR = ERROR_OVERFLOW_MANTIS;
    }
    //printf("take_mantis end.\n\n");
    return ERROR;
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
/**
 * @brief take_poriadok - берет из строки порядок
 * @param str - строка
 * @param poriadok - порядок
 * @return
 */
int take_poriadok(char *str,int *poriadok)
{
   //printf("take_poriadok start.\n");
   int ERROR = ERROR_ACCURATELY;
   int flag_e = 0, flag_znak = 0;
   int tempp;
   char temp[7];
   int i=0,ii=0;
   int max_por = 5;
   for (i = 0; i < 7; i++)
       temp[i] = '\0';
   i = 0;
   while (str[i] != '\0')
   {

       if (flag_e == 1)
       {
           if (str[i] == '-' || str[i] == '+')
           {
               if (flag_znak == 1)
               {
                   ERROR = ERROR_UNCORRECT_INPUT;
                   break;
               }
               max_por = 6;
           }
           flag_znak = 1;
           temp[ii] = str[i];
           if (str[i] == '.')
           {
               ERROR = ERROR_UNCORRECT_INPUT;
               break;
           }
           if (ii > max_por)
           {
               ERROR = ERROR_OVERFLOW;
               break;
           }
           ii++;
       }
       if (str[i] == 'E')
       {
           flag_e = 1;
           if (str[i + 1] == '0')
           {
               ERROR = ERROR_UNCORRECT_INPUT;
               break;
           }
       }
       i++;
   }
   tempp = atoi(temp);
   //printf("HERE IS TEMP:\n");
//   for (i = 0; i < 7; i++)
//       printf("%c ", temp[i]);   
   if (*poriadok > 99999 && *poriadok < -99999)
   {
       ERROR = ERROR_OVERFLOW;
   }
   *poriadok = *poriadok + tempp;
   //printf("tempp = %d\n", tempp);
   //printf("take_poriadok end.\n\n");
   return ERROR;
}
/**
 * @brief read_chislo вводит число и заполняет структуру
 * @param chislo - структура под число
 * @param type - 1 - вещественное 0 - целое
 * @return
 */
int read_chislo(struct chislo *chislo,int type)
{
    char str[MAX_LEN + 1];
    int ch, i = 0;
    int ERROR = ERROR_ACCURATELY;
    chislo->poriadok = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if ((ch == '.' || ch == 'E') && type == 0)
        {
            ERROR = ERROR_UNCORRECT_INPUT;
            break;
        }
        if (check_simbol(ch) == 0)
        {
            ERROR = ERROR_UNCORRECT_INPUT;
            break;
        }
        if (i > MAX_LEN)
        {
            ERROR = ERROR_UNCORRECT_INPUT;
            break;
        }
        str[i++] = ch;
    }
    if (i == 0 && ERROR != ERROR_UNCORRECT_INPUT)
    {
        ERROR = ERROR_NOT_INPUT;
    }
    str[i] = '\0';
    if (ERROR == ERROR_ACCURATELY)
    {
        ERROR = check_count_simbol(str);
    }
    if (ERROR == ERROR_ACCURATELY)
    {
        //printf("Kek\n");
        ERROR = take_mantis(str,chislo->mantis,&chislo->poriadok,&chislo->znak_mantis);
        //printf("Kek1\n");
        //print_array(chislo->mantis,LEN_MANTIS);
        //print_error(ERROR);
    }
    if (ERROR == ERROR_ACCURATELY && type == 1)
    {
        ERROR = take_poriadok(str, &chislo->poriadok);
    }
    if (ERROR == ERROR_ACCURATELY)
    {
        //printf("SET ARRAY.\n");
        set_array_back(chislo->mantis);
    }
    return ERROR;
}
