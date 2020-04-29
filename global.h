#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <iostream>
#include <cstddef>
#include <conio.h>
#include <stdio.h>
#include "tubes.h"

#define Nil NULL
#define first(A) (A).first
#define next(A) (A)->next
#define info(A) (A)->info
#define last(A) (A).last
#define prev(A) (A)->prev
#define adrC(A) (A)->adrC
#define adrP(A) (A)->adrP

using namespace std;

void clrscr();

void inputCompany(List_C &L, List_R &L2, List_P &L1);
void inputProduct(List_C &L, List_R &L2, List_P &L1);

int cariMaksimum(List_C C);
address_R cariProdukAndalan(List_R R, address_C Ad);

void viewAll(List_C L, List_R L2);
void viewTOP3(List_C L, List_R L2);
void viewProdAndalan(List_C L, List_R L1);
void viewCbP(List_R L1,List_P L2);
void viewPbC(List_R L1,List_C L2);

void menuDelete(List_C &C, List_P &P, List_R &R);
void deleteCompany(List_R &L, List_C &L2);
void deleteProduct(List_R &L, List_P &L2);


void menuView(List_C C, List_P P, List_R R);
void menuDelete(List_C &C, List_P &P, List_R &R);
void menuUtama(List_C &C, List_P &P, List_R &R);

#endif // GLOBAL_H_INCLUDED
