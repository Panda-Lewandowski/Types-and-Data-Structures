#ifndef CHISLO_H
#define CHISLO_H

#include "const.h"
struct chislo
{
    int znak_mantis;// -1 - отрицательное 1 - положительное
    int mantis[LEN_MANTIS];//Мантисса
    int poriadok;//Порядок
};

#endif // CHISLO_H

