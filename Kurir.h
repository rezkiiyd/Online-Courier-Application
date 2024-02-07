#include <iostream>
#ifndef KURIR_H_INCLUDED
#define KURIR_H_INCLUDED

#define info(p) p->info
#define next(p) p->next
#define prev(p) p->prev
#define pesan(p) (p)->pesan
#define kirim(p) p->kirim
#define first(LO) LO.first
#define last(LO) LO.last

using namespace std;

typedef struct elmOrder *adrOrder;
typedef struct elmKurir *adrKurir;
typedef struct elmCustomer *adrCustomer;

struct order{
    string noOrder, tKeberangkatan, tTujuan, wKeberangkatan, wKedatangan, status;
    float ratingOrder;
};

struct kurir{
    string ID, namaKurir, kontakKurir;
    float ratingKurir;
};

struct customer{
    string NIK, namaCustomer, alamatCustomer, kontakCustomer;
};

struct elmOrder{
    order info;
    adrOrder next;
    adrCustomer pesan;
};

struct listCustomer{
    adrCustomer first, last;
};

struct listOrder{
    adrOrder first, last;
};

struct elmKurir{
    kurir info;
    adrKurir next, prev;
    listOrder kirim;
};

struct elmCustomer{
    customer info;
    adrCustomer next;
};

struct listKurir{
    adrKurir first, last;
};

void createListOrder(listOrder &LO);
void createListKurir(listKurir &LK);
void createListCustomer(listCustomer &LC);
adrOrder alokasiOrder(order x, adrCustomer c);
adrKurir alokasiKurir(kurir x);
adrCustomer alokasiCustomer(customer x);

void insertLastOrder(listOrder &LO, adrOrder p);
void insertLastKurir(listKurir &LK, adrKurir p);
void insertLastCustomer(listCustomer &LC, adrCustomer p);
void deleteOrder(listKurir &LK, string ID, string noOrder);
void deleteKurir(listKurir &LK, string IDKurir, adrKurir &p);
void deleteCustomer(listCustomer &LC, listKurir &LK, string NIK, adrCustomer &p);

void connect(listKurir &LK, string ID, listCustomer &LC, string NIK, order x);
void deleteConnectionKurirOrder(listKurir &LK, string IDKurir, string noOrder);
void deteleConnectionOrderCustomer(listOrder &LO, listCustomer &LC, customer c, string noOrder);

adrOrder searchOrder(listKurir LK, string noOrder);
adrKurir searchKurir(listKurir LK, string IDKurir);
adrCustomer searchCustomer(listCustomer LC, string NIK);

void changeTitikKeberangkatanOrder(listKurir &LK, string noOrder, string new_tKeberangkatan);
void changeTitikTujuanOrder(listKurir &LK, string noOrder, string new_tTujuan);
void changeWaktuKeberangkatanOrder(listKurir &LK, string noOrder, string new_wKeberangkatan);
void changeWaktuKedatanganOrder(listKurir &LK, string noOrder, string new_wKedatangan);
void changeStatusOrder(listKurir &LK, string noOrder, string new_status);
void changeRatingOrder(listKurir &LK, string noOrder, float new_ratingOrder);
void changeKurir(listOrder &LO, listKurir &LK, string noOrder, string new_IDKurir);

void changeNamaKurir(listKurir &LK, string ID, string new_namaKurir);
void changeKontakKurir(listKurir &LK, string ID, string new_kontakKurir);
void changeRatingKurir(listKurir &LK, string ID, float new_ratingKurir);

void changeNamaCustomer(listCustomer &LC, string NIK, string new_namaCustomer);
void changeAlamatCustomer(listCustomer &LC, string NIK, string new_alamatCustomer);
void changeKontakCustomer(listCustomer &LC, string NIK, string new_kontakCustomer);

void showOrder(listKurir LK);
void showKurir(listKurir LK);
void showCustomer(listCustomer LC);

void showAll(listKurir LK, listCustomer LC);

void showHistKurir(listKurir &LK, string IDKurir);
void showStatusOrder(listKurir LK, string noOrder);

int menu();
int menuSearchData();
int menuTambahData();
int menuShowData();
int menuEditData();
int menuHapusData();
#endif // KURIR_H_INCLUDED
