#include <iostream>
#include <stddef.h>
#include "tubes.h"
#include "global.h"
#include <conio.h>
#include <stdio.h>

using namespace std;

int main()
{
    List_C C;
    List_P P;
    List_R R;

    createList_C(C);
    createList_P(P);
    createList_R(R);


    menuUtama(C,P,R);
    return 0;
}
