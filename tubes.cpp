#include <iostream>
#include <stddef.h>
#include "tubes.h"
#include <conio.h>
#include <stdio.h>

using namespace std;

void createList_C(List_C &L)
{
    first(L) = NULL;
    last(L) = NULL;
}

void createList_P(List_P &L)
{
    first(L) = NULL;
}

void createList_R(List_R &L)
{
    first(L) = NULL;
}

address_C alokasi_C(it_company X)
{
    address_C P = new ElmList_C;
    X.jump = 0;
    info(P) = X;
    next(P) = NULL;
    prev(P) = NULL;
    return P;
}

address_P alokasi_P(it_product X)
{
    address_P P = new ElmList_P;
    info(P) = X;
    next(P) = NULL;
    return P;
}
address_R alokasi_R(address_C X, address_P Y, int jumlah)
{
    address_R P = new ElmList_R;
    adrC(P) = X;
    adrP(P) = Y;
    jumProd(P) = jumlah;
    next(P) = NULL;
    return P;
}

void insertFirst_C(List_C &L, address_C P)
{
    if (first(L)!=NULL && last(L) != NULL)
    {
        next(P) = first(L);
        prev(first(L)) = P;
        first(L) = P;
    }
    else
    {
        first(L) = P;
        last(L) = P;
    }
}

void insertFirst_P(List_P &L, address_P P)
{
    if (first(L) != NULL)
    {
        next(P) = first(L);
        first(L) = P;
    }
    else
    {
        first(L) = P;
    }
}

void insertFirst_R(List_R &L, address_R P)
{
    if (first(L) != NULL)
    {
        next(P) = first(L);
        first(L) = P;
    }
    else
    {
        first(L) = P;
    }
}

void insertLast_C(List_C &L, address_C P)
{
    if(first(L)!= NULL && last(L) != NULL)
    {
        prev(P) = last(L);
        next(last(L)) = P;
        last(L) = P;
    }
    else
    {
        insertFirst_C(L,P);
    }
}

void insertLast_P(List_P &L, address_P P)
{
    address_P Q = first(L);

    if (first(L) != NULL)
    {
        while(next(Q) != NULL)
        {
            Q = next(Q);
        }
        next(Q) = P;
    }
    else
    {
        insertFirst_P(L,P);
    }
}

void insertLast_R(List_R &L, address_R P)
{
    address_R Q = first(L);

    if (first(L) != NULL)
    {
        while(next(Q) != NULL)
        {
            Q = next(Q);
        }
        next(Q) = P;
    }
    else
    {
        insertFirst_R(L,P);
    }
}

void deleteFirst_C(List_C &L, address_C &P)
{
    if (first(L) != NULL && last(L) != NULL)
    {
        P = first(L);

        if (first(L) == last(L))
        {
            first(L) = NULL;
            last(L) = NULL;
        }
        else
        {
            next(prev(P)) = next(P);
            prev(next(P)) = prev(P);
            next(P) = NULL;
            prev(P) = NULL;
        }
    }
    else
    {
        cout<<"List Perusahaan Kosong"<<endl;
    }
}

void deleteFirst_P(List_P &L, address_P &P)
{
    if (first(L) != NULL)
    {
        P = first(L);

        if(next(first(L)) == NULL)
        {
            first(L) = NULL;
        }
        else
        {
            first(L) = next(first(L));
            next(P) = NULL;
        }
    }
    else
    {
        cout<<"LIST PRODUK KOSONG"<<endl;
    }
}

void deleteFirst_R(List_R &L, address_R &P)
{
    if (first(L)!=NULL)
    {
        P = first(L);

        if(next(first(L)) == NULL)
        {
            first(L)= NULL;
        }
        else
        {
            first(L) = next(first(L));
            next(P) = NULL;
        }
    }
}

void deleteLast_C(List_C &L, address_C &P)
{
    if(first(L) != NULL && last(L) != NULL)
    {
        if(first(L) == last(L))
        {
            deleteFirst_C(L,P);
        }
        else
        {
            last(L) = prev(P);
            next(last(L)) = NULL;
            prev(P) = NULL;
        }
    }
    else
    {
        cout<<"List Perusahaan Kosong"<<endl;
    }
}

void deleteLast_P(List_P &L, address_P &P)
{
    address_P Q = first(L);

    if(first(L) != NULL)
    {
        if(next(first(L)) == NULL)
            deleteFirst_P(L,P);
        else
        {
            while(next(next(Q)) != NULL)
            {
                Q = next(Q);
            }
            next(Q) = NULL;
        }
    }
    else
    {
        cout<<"LIST PRODUK KOSONG"<<endl;
    }
}

void deleteLast_R(List_R &L, address_R &P)
{
    address_R Q = first(L);

    if(first(L)!= NULL)
    {
        if(next(first(L)) == NULL)
            deleteFirst_R(L,P);
        else
        {
            while(next(next(Q)) != NULL)
            {
                Q = next(Q);
            }
            next(Q) = NULL;
        }
    }
}

void delete_C(List_C &L, address_C &P)
{
    if (first(L) != NULL && last(L) != NULL)
    {
        if (P == first(L))
        {
            deleteFirst_C(L,P);
        }
        else if (P == last(L))
        {
            deleteLast_C(L,P);
        }
        else
        {
            next(prev(P)) = next(P);
            prev(next(P)) = prev(P);
            prev(P) = NULL;
            next(P) = NULL;
        }
    }
    else
    {
        cout<<"List Perusahaan Kosong"<<endl;
    }
}

void delete_P(List_P &L, address_P &X)
{
    address_P Q = first(L);

    if(X == first(L))
    {
        deleteFirst_P(L,X);
    }
    else if(next(X)==NULL)
    {
        deleteLast_P(L,X);
    }
    else
    {
        while(next(Q) != X)
        {
            Q = next(Q);
        }
        next(Q) = next(X);
        next(X) = NULL;
    }
}

void delete_R(List_R &L, address_R &X)
{
    address_R Q = first(L);

    if (X == first(L))
    {
        deleteFirst_R(L,X);
    }
    else if(next(X) == NULL)
    {
        deleteLast_R(L,X);
    }
    else
    {
        while(next(Q) != X)
        {
            Q = next(Q);
        }
        next(Q) = next(X);
        next(X) = NULL;
    }
}

address_R findelm_R_C(List_R L, address_C X)
{
    address_R P;
    P = first(L);
    while(P!= NULL)
    {
        if(adrC(P) == X)
            return P;
        else
            P = next(P);
    }
    return NULL;
}

address_R findelm_R_P(List_R L, address_P X)
{
    address_R P;
    P = first(L);
    while(P!= NULL)
    {
        if(adrP(P) == X)
            return P;
        else
            P = next(P);
    }
    return NULL;
}

address_R findelm_R_CP(List_R L, address_C X, address_P Y)
{
    address_R P;
    P = first(L);
    while(P!= NULL)
    {
        if((adrC(P) == X) && (adrP(P) == Y))
            return P;
        else
            P = next(P);
    }
    return NULL;
}

address_C findElm_C(List_C L, it_company X)
{
    address_C P;
    P = first(L);
    while(P!= NULL)
    {
        if(info(P).namaP == X.namaP)
            return P;
        else
            P = next(P);
    }
    return NULL;
}

address_P findElm_P(List_P L, it_product X)
{
    address_P P;
    P = first(L);
    while(P!= NULL)
    {
        if(info(P).nama == X.nama)
            return P;
        else
            P = next(P);
    }
    return NULL;
}

