#include <iostream>
#include <stddef.h>
#include "global.h"
#include "tubes.h"
#include <conio.h>
#include <stdio.h>
#include <cstdlib>

#define WINDOWS 1

void clrscr()
{
#ifdef WINDOWS
    system("cls");
#endif // WINDOWS
#ifdef LINUX
    system("clear");
#endif // LINUX
}

void inputCompany(List_C &L, List_R &L2, List_P &L1)
{
    address_C P;
    it_company X;

    clrscr();
    cout<<"-----------------------------------------------"<<endl;
    cout<<"                  INPUT COMPANY                "<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<endl;

    cout<<"Nama Perusahaan : " ;
    cin>>X.namaP;
    cout<<"Bidang          : ";
    cin>>X.bidang;
    cout<<"Kota            : ";
    cin>>X.kota;

    P = findElm_C(L,X);

    if(P != NULL)
    {
        //KALAU PERUSAHAAN UDAH ADA, UPDATE INFO
        info(P).bidang = X.bidang;
        info(P).kota = X.kota;
        cout<<endl;
        cout<<"Data berhasil diupdate.."<<endl;
        getch();
    }

    else
    {
        //KALAU BELUM, INSERT
        P = alokasi_C(X);
        insertLast_C(L,P);
        cout<<endl;
        inputProduct(L,L2,L1);
    }
}

void inputProduct(List_C &L, List_R &L2, List_P &L1)
{
    int jumlah;
    it_company X;
    it_product Y;
    address_C P;
    address_P Q,A;
    address_R R;

    clrscr();
    cout<<"-----------------------------------------------"<<endl;
    cout<<"                  INPUT PRODUCT                "<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<endl;

    cout<<"Nama Perusahaan : ";
    cin>>X.namaP;
    cout<<"Nama Barang     : ";
    cin>>Y.nama;
    cout<<"Jumlah Barang   : ";
    cin>>jumlah;

    Q = findElm_P(L1,Y);
    P = findElm_C(L,X);
    R = findelm_R_CP(L2,P,Q);
    if(R == NULL)
    {
        //KALAU RELASI GA ADA,
        if((Q != NULL) && (P != NULL))
        {
            //KALAU PRODUK DAN PERUSAHAAN UDAH ADA,
            info(P).jump++;
            insertFirst_R(L2,alokasi_R(P,Q,jumlah));

            cout<<endl;
            cout<<"Data berhasil diinputkan.."<<endl;
        }
        else if(Q == NULL && P != NULL)
        {
            //KALAU PRODUK BELUM ADA,
            info(P).jump = info(P).jump +1;
            A = alokasi_P(Y);
            insertFirst_P(L1,A);
            insertFirst_R(L2,alokasi_R(P,A,jumlah));

            cout<<endl;
            cout<<"Data berhasil diinputkan.."<<endl;
        }
        else if(P == NULL)
        {
            //KALAU PERUSAHAAN BELUM ADA,
            inputCompany(L,L2,L1);
        }
    }
    else
    {
        jumProd(R) = jumlah;

        cout<<endl;
        cout<<"Data berhasil diupdate.."<<endl;
        getch();
    }
}

void viewAll(List_C L, List_R L2)
{
    address_C P;
    address_R R;

    clrscr();
    cout<<"-----------------------------------------------"<<endl;
    cout<<"                 TAMPILKAN SEMUA               "<<endl;
    cout<<"-----------------------------------------------"<<endl;

    P = first(L);
    R = first(L2);

    while(P != NULL)
    {
        cout<<"Nama Perusahaan        : ";
        cout<<info(P).namaP<<endl;
        cout<<"Kota                   : ";
        cout<<info(P).kota<<endl;
        cout<<"Bidang                 : ";
        cout<<info(P).bidang<<endl;
        cout<<"Banyaknya Jenis Produk : ";
        cout<<info(P).jump<<endl;
        cout<<"Produk                 : "<<endl;

        while (R != NULL)
        {
            //SELAMA RELASI MASIH ADA,
            if (adrC(R)== P)
            {
                //JIKA ADRC RELASI MENUNJUK ADDRESS PERUSAHAAN,
                cout<<"- ";
                cout<<info(adrP(R)).nama;
                cout<<"     ( ";
                cout<<jumProd(R);
                cout<<" )"<<endl;
                cout<<endl;
            }
            R = next(R);
        }
        P = next(P);
        R = first(L2);
    }
    cout<<"-----------------------------------------------"<<endl;
}

int cariMaksimum(List_C C)
{
    int nMax = 0;
    address_C c = first(C);

    while(c != NULL)
    {
        //SELAMA LIST PERUSAHAAN MASIH ADA,
        if(info(c).jump > nMax)
            nMax = info(c).jump;
        c = next(c);
    }
    return nMax;
}

void viewTOP3(List_C L, List_R L2)
{
    address_C P;
    int nTOP = 1;
    int nMax = cariMaksimum(L); //CARI NILAI MAKSIMUM

    clrscr();
    cout<<"-----------------------------------------------"<<endl;
    cout<<"           TAMPILKAN PERUSAHAAN TOP 3          "<<endl;
    cout<<"-----------------------------------------------"<<endl;

    if(first(L)!= NULL)
    {
        //JIKA PEURAHAAN ADA,
        while((nTOP <= 3) && (nMax > -1))
        {
            P = first(L);

            while(P != NULL)
            {
                //SELAMA PERUSAHAAN MASIH ADA,
                if(info(P).jump == nMax)
                {
                    //JIKA JUMLAH PRODUK SI PERUSAHAAN SAMA DENGAN NILAI MAKSIMUM,
                    cout<<"TOP "<<nTOP<<" : "<<endl;
                    cout<<"Nama Perusahaan        : "<<info(P).namaP<<endl;
                    cout<<"Kota Perusahaan        : "<<info(P).kota<<endl;
                    cout<<"Bidang Perusahaan      : "<<info(P).bidang<<endl;
                    cout<<"Banyaknya Jenis Produk : "<<info(P).jump<<endl;
                    cout<<endl<<endl;
                    nTOP++;
                }
                P = next(P);
            }
            nMax--;
        }
    }
    else
    {
        cout<<"List Perusahaan Kosong"<<endl;
    }
    cout<<"-----------------------------------------------"<<endl;
}

address_R cariProdukAndalan(List_R R, address_C AdC)
{
    int nMax = 0;
    address_R adrMax = NULL;
    address_R P = first(R);

    while(P!= NULL)
    {
        //SELAMA RELASI MASIH ADA,
        if(adrC(P)== AdC && jumProd(P) > nMax)
        {
            nMax = jumProd(P);
            adrMax = P;
        }
        P = next(P);
    }
    return adrMax;
}

void viewProdAndalan(List_C L, List_R L1)
{
    address_C P = first(L);
    address_R R = first(L1);
    address_R TOP;

    clrscr();
    cout<<"-----------------------------------------------"<<endl;
    cout<<"             TAMPILKAN PRODUK ANDALAN          "<<endl;
    cout<<"-----------------------------------------------"<<endl;

    if (P != NULL && R != NULL)
    {
        //JIKA PERUSAHAAN DAN RELASI ADA,
        while(P != NULL)
        {
            //SELAMA PERUSAHAAN MASIH ADA,
            cout<<"Nama Perusahaan        : "<<info(P).namaP<<endl;
            cout<<"Kota                   : "<<info(P).kota<<endl;
            cout<<"Bidang                 : "<<info(P).bidang<<endl;
            cout<<"Banyaknya Jenis Produk : "<<info(P).jump<<endl;
            TOP = cariProdukAndalan(L1,P);

            if(jumProd(TOP) != 0)
            {
                //JIKA PERUSAHAAN MEMILIKI PRODUK,
                cout<<"Produk Andalan         : "<<info(adrP(TOP)).nama<<endl;
                cout<<"Jumlah Produk Andalan  : "<<jumProd(TOP)<<endl;
                cout<<endl;
            }
            else
            {
                //JIKA PERUSAHAAN TIDAK MEMILIKI PRODUK,
                cout<<"Perusahaan tidak memiliki produk"<<endl;
                cout<<endl;
            }
            P = next(P);
        }
    }
    cout<<"-----------------------------------------------"<<endl;
    getch();
}

void viewCbP(List_R L1, List_P L2)
{
    it_product X;
    address_R R;
    R = first(L1);

    clrscr();
    cout<<"-----------------------------------------------"<<endl;
    cout<<"               TAMPILKAN PERUSAHAAN            "<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<"Nama Produk yang Dicari: ";
    cin>>X.nama;
    cout<<endl<<endl;

    if(findElm_P(L2,X)!= NULL)
    {
        //JIKA PRODUK YANG DICARI KETEMU,
        cout<<"Perusahaan yang memproduksi "<<X.nama<<" adalah: "<<endl<<endl;

        while(R != NULL)
        {
            //SELAMA RELASI MASIH ADA,
            if(info(adrP(R)).nama == X.nama)
            {
                cout<<"Nama Perusahaan: ";
                cout<<info(adrC(R)).namaP<<endl;
                cout<<"Kota           : ";
                cout<<info(adrC(R)).kota<<endl;
                cout<<"Bidang         : ";
                cout<<info(adrC(R)).bidang<<endl;
                cout<<"Banyaknya Jenis Produk : ";
                cout<<info(adrC(R)).jump<<endl;
                cout<<" "<<endl;
            }
            R = next(R);
        }
    }
    else
        cout<<"Produk Tidak Ditemukan "<<endl;
    cout<<"-----------------------------------------------"<<endl;
}

void viewPbC(List_R L1, List_C L2)
{
    address_R R;
    it_company X;
    it_product Y;
    R = first(L1);

    clrscr();
    cout<<"-----------------------------------------------"<<endl;
    cout<<"                 TAMPILKAN PRODUK              "<<endl;
    cout<<"-----------------------------------------------"<<endl;

    cout<<"Nama Perusahaan yang Dicari: ";
    cin>>X.namaP;
    cout<<endl<<endl;

    if(findElm_C(L2,X) != NULL)
    {
        cout<<"Produk yang diproduksi oleh "<<X.namaP<<" adalah: "<<endl<<endl;

        while(R != NULL)
        {
            //SELAMA RELASI MASIH ADA,
            if(info(adrC(R)).namaP == X.namaP)
            {
                cout<<"- ";
                cout<<info(adrP(R)).nama;
                cout<<"     ( ";
                cout<<jumProd(R);
                cout<<" )"<<endl;
            }
            R = next(R);
        }
    }
    else
        cout<<"Perusahaan Tidak Ditemukan "<<endl;
    cout<<"-----------------------------------------------"<<endl;
}

void menuView(List_C C, List_P P, List_R R)
{
    clrscr();
    int pil;
    cout<<"-----------------------------------------------"<<endl;
    cout<<"                     MENU VIEW                 "<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<endl;
    cout<<"1. Tampilkan Semua"<<endl;
    cout<<"2. Tampilkan TOP 3 Perusahaan"<<endl;
    cout<<"3. Tampilkan Perusahaan dan Produk Andalan"<<endl;
    cout<<"4. Tampilkan Perusahaan berdasarkan Produk Tertentu"<<endl;
    cout<<"5. Tampilkan Produk berdasarkan Perusahaan Tertentu"<<endl;
    cout<<"0. Keluar"<<endl;
    cout<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<endl;
    cout<<"Masukkan pilihan :"<<" ";
    cin>>pil;

    if(pil == 1)
    {
        viewAll(C,R);
    }
    else if(pil == 2)
    {
        viewTOP3(C,R);
    }
    else if(pil == 3)
    {
        viewProdAndalan(C,R);
    }
    else if(pil == 4)
    {
        viewCbP(R,P);
    }
    else if(pil == 5)
    {
        viewPbC(R,C);
    }
    else if(pil == 0 )
    {

    }
    else
    {
        menuView(C,P,R);
    }
}

void deleteCompany(List_R &L, List_C &L2)
{
    it_company Z;
    address_C X;
    address_R P = first(L);

    clrscr();
    cout<<"-----------------------------------------------"<<endl;
    cout<<"                  DELETE COMPANY               "<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<endl;

    cout<<"Nama Perusahaan yang Ingin Dihapus : ";
    cin>>Z.namaP;
    cout<<endl;

    X = findElm_C(L2,Z);

    if (X == NULL)
        cout<<"Nama Perusahaan Tidak Ditemukann"<<endl;
    else
    {
        //JIKA PERUSAHAAN KETEMU,
        while(P != NULL)
        {
            //SELAMA RRELASI MASIH ADA,
            if(adrC(P) == X)
            {
                delete_R(L,P);
            }
            P = next(P);
        }
        delete_C(L2,X);
        cout<<"Data berhasil dihapus.."<<endl;
        getch();
    }
}

void deleteProduct(List_R &L, List_P &L2)
{
    it_product Z;
    address_P X;
    address_R P = first(L);

    clrscr();
    cout<<"-----------------------------------------------"<<endl;
    cout<<"                  DELETE PRODUCT               "<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<endl;
    cout<<"Nama Produk yang Ingin Dihapus : ";
    cin>>Z.nama;
    cout<<endl;

    X = findElm_P(L2,Z);

    if (X == NULL)
    {
        cout<<"Nama Produk Tidak Ditemukann"<<endl;
    }

    else
    {
        //JIKA PRODUK KETEMU,
        while(P != NULL)
        {
            //SELAMA RELASI MASIH ADA,
            if (adrP(P) == X)
            {
                info(adrC(P)).jump = info(adrC(P)).jump - 1;
                delete_R(L,P);
            }
            P = next(P);
        }
        delete_P(L2,X);
        cout<<"Data berhasil dihapus.."<<endl;
        getch();
    }
}

void menuDelete(List_C &C, List_P &P, List_R &R)
{
    int pil;

    clrscr();
    cout<<"-----------------------------------------------"<<endl;
    cout<<"                    MENU DELETE                "<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<endl;
    cout<<"1. Hapus Perusahaan"<<endl;
    cout<<"2. Hapus Produk"<<endl;
    cout<<"0. Keluar"<<endl;
    cout<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<endl;

    cout<<"Masukkan pilihan : ";
    cin>>pil;

    if(pil == 1)
    {
        deleteCompany(R,C);
    }
    else if(pil == 2)
    {
        deleteProduct(R,P);
    }
    else if(pil == 0 )
    {

    }
    else
    {
        menuDelete(C,P,R);
    }
}

void menuUtama(List_C &C, List_P &P, List_R &R)
{

    int pil;
    do
    {
        clrscr();
        cout<<"------------------ MENU UTAMA ------------------"<<endl;
        cout<<endl;
        cout<<"1. Input Company"<<endl;
        cout<<"2. Input Product"<<endl;
        cout<<"3. View"<<endl;
        cout<<"4. Delete"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<endl;
        cout<<"-----------------------------------------------"<<endl;
        cout<<endl;
        cout<<"Masukkan pilihan : ";
        cin>>pil;

        if(pil == 1)
        {
            inputCompany(C,R,P);
            getch();
        }
        else if(pil == 2)
        {
            inputProduct(C,R,P);
            getch();
        }
        else if(pil == 3)
        {
            menuView(C,P,R);
            getch();
        }
        else if(pil == 4)
        {
            menuDelete(C,P,R);
        }
    }
    while(pil != 0);
}
