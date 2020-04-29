#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED

#include <iostream>
#include <cstddef>

#define Nil NULL
#define first(A) (A).first
#define next(A) (A)->next
#define info(A) (A)->info
#define last(A) (A).last
#define prev(A) (A)->prev
#define adrC(A) (A)->adrC
#define adrP(A) (A)->adrP
#define jumProd(A) (A)->jumProd



using namespace std;

struct it_company{
    string nama;
    string kota;
    string bidang;
    int jump;
};

struct it_product{
    string namaP;
};

typedef struct ElmList_C *address_C;
typedef struct ElmList_P *address_P;
typedef struct ElmList_R *address_R;

struct ElmList_C{
    address_C next;
    address_C prev;
    it_company info;
};

struct ElmList_P{
    address_P next;
    it_product info;
};

struct ElmList_R{
    address_C adrC;
    address_P adrP;
    address_R next;
    int jumProd;
};

struct List_C{
    address_C first;
    address_C last;
};

struct List_P{
    address_P first;
};

struct List_R{
    address_R first;
};

void createList_C(List_C &L);
void createList_P(List_P &L);
void createList_R(List_R &L);

address_C alokasi_C(it_company X);
address_P alokasi_P(it_product X);
address_R alokasi_R(address_C X, address_P Y,int jumlah);

void insertFirst_C(List_C &L, address_C P);
void insertFirst_P(List_P &L, address_P P);
void insertFirst_R(List_R &L, address_R P);

void insertLast_C(List_C &L, address_C P);
void insertLast_P(List_P &L, address_P P);
void insertLast_R(List_R &L, address_R R);

void deleteFirst_C(List_C &L, address_C &P);
void deleteFirst_P(List_P &L, address_P &P);
void deleteFirst_R(List_R &L, address_R &P);

void deleteLast_C(List_C &L, address_C &P);
void deleteLast_P(List_P &L, address_P &P);
void deleteLast_R(List_R &L, address_R &P);

void delete_C(List_C &L, address_C &X);
void delete_P(List_P &L, address_P &X);
void delete_R(List_R &L, address_R &X);

address_C findElm_C(List_C L, it_company X);
address_P findElm_P(List_P L, it_product X);
address_R findelm_R_C(List_R L, address_C X);
address_R findelm_R_P(List_R L, address_P X);
address_R findelm_R_CP(List_R L, address_C X, address_P Y);

#endif // TUBES_H_INCLUDED
