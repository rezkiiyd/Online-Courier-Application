#include <iostream>
#include "Kurir.h"

using namespace std;

void createListOrder(listOrder &LO){
    first(LO) = NULL;
    last(LO) = NULL;
}

void createListKurir(listKurir &LK){
    first(LK) = NULL;
    last(LK) = NULL;
}

void createListCustomer(listCustomer &LC){
    first(LC) = NULL;
    last(LC) = NULL;
}

adrOrder alokasiOrder(order x, adrCustomer c){
    adrOrder p = new elmOrder;
    info(p).noOrder = x.noOrder;
    info(p).tKeberangkatan = x.tKeberangkatan;
    info(p).tTujuan = x.tTujuan;
    info(p).wKeberangkatan = x.wKeberangkatan;
    info(p).wKedatangan = x.wKedatangan;
    info(p).status = x.status;
    info(p).ratingOrder = x.ratingOrder;
    pesan(p) = c;
    next(p) = NULL;
    return p;

}

adrKurir alokasiKurir(kurir x){
    adrKurir p = new elmKurir;
    info(p).ID = x.ID;
    info(p).namaKurir = x.namaKurir;
    info(p).kontakKurir = x.kontakKurir;
    info(p).ratingKurir = x.ratingKurir;
    next(p) = NULL;
    prev(p) = NULL;
    createListOrder(kirim(p));
    return p;
}

adrCustomer alokasiCustomer(customer x){
    adrCustomer p = new elmCustomer;
    info(p).NIK = x.NIK;
    info(p).namaCustomer = x.namaCustomer;
    info(p).alamatCustomer = x.alamatCustomer;
    info(p).kontakCustomer = x.kontakCustomer;
    next(p) = NULL;
    return p;
}

void insertLastOrder(listOrder &LO, adrOrder p){
    if ((first(LO) == NULL) && (last(LO) == NULL)){
        first(LO) = p;
        last(LO) = p;
    }else{
        next(last(LO)) = p;
        last(LO) = p;
    }
}

void insertLastKurir(listKurir &LK, adrKurir p){
    if((first(LK) == NULL) && (last(LK) == NULL)){
        first(LK) = p;
        last(LK) = p;
        next(p) = first(LK);
        prev(p) = last(LK);
    }else{
        prev(p) = last(LK);
        next(last(LK)) = p;
        last(LK) = p;
        next(p) = first(LK);
    }
}

void insertLastCustomer(listCustomer &LC, adrCustomer p){
    if ((first(LC) == NULL) && (last(LC) == NULL)){
        first(LC) = p;
        last(LC) = p;
        next(p) = first(LC);
    }else{
        next(last(LC)) = p;
        last(LC) = p;
    }
}

void deleteKurir(listKurir &LK, string IDKurir, adrKurir &p){
    p = searchKurir(LK, IDKurir);

    if (p != NULL){
        if (first(kirim(p)) != NULL){
            adrOrder o = first(kirim(p));
            while (o != NULL){
                adrOrder temp = o;
                o = next(o);
                delete temp;
            }
            first(kirim(p)) = NULL;
        }

        if (p == first(LK)){
            if (next(p) != first(LK)){
                first(LK) = next(p);
                next(last(LK)) = first(LK);
                prev(first(LK)) = last(LK);
                next(p) = NULL;
                prev(p) = NULL;
            } else {
                first(LK) = NULL;
                last(LK) = NULL;
            }
        } else if (p == last(LK)){
            last(LK) = prev(last(LK));
            next(last(LK)) = first(LK);
            prev(first(LK)) = last(LK);
            prev(p) = NULL;
            next(p) = NULL;
        } else {
            adrKurir prec = prev(p);
            next(prec) = next(p);
            prev(next(p)) = prec;
            next(p) = NULL;
            prev(p) = NULL;
        }
        delete p;
    } else {
        cout << "Data Tidak Ditemukan" << endl;
    }
}

void deleteCustomer(listCustomer &LC, listKurir &LK, string NIK, adrCustomer &p){
    p = searchCustomer(LC, NIK);

    if (p != NULL){
        adrKurir k = first(LK);
        bool berhenti = false;
        while (!berhenti){
            adrOrder o = first(kirim(k));
            while (o != NULL){
                if (info(pesan(o)).NIK == NIK){
                    adrOrder temp = o;
                    o = next(o);
                    if (temp == first(kirim(k))){
                        first(kirim(k)) = o;
                    } else {
                        adrOrder prec = first(kirim(k));
                        while (next(prec) != temp){
                            prec = next(prec);
                        }
                        next(prec) = o;
                    }
                    next(temp) = NULL;
                    pesan(temp) = NULL;
                } else {
                    o = next(o);
                }
            }
            k = next(k);
            berhenti = k == first(LK);
        }
        if (p == first(LC)){
            first(LC) = next(p);
        } else if (p == last(LC)){
            adrCustomer q = first(LC);
            while (next(q) != p){
                q = next(q);
            }
            last(LC) = q;
            next(last(LC)) = NULL;
        } else {
            adrCustomer prec = first(LC);
            while (next(prec) != p){
                prec = next(prec);
            }
            next(prec) = next(p);
        }
        next(p) = NULL;
        p = NULL;
    } else {
        cout << "Data Tidak Ditemukan" << endl;
    }
}

void connect(listKurir &LK, string ID, listCustomer &LC, string NIK, order x){
    adrKurir k;
    adrCustomer c;
    adrOrder o;

    k = searchKurir(LK, ID);
    c = searchCustomer(LC, NIK);

    if (k != NULL && c != NULL){
        o = alokasiOrder(x, c);
        insertLastOrder(kirim(k), o);
    }else{
        cout << "Data Kurir atau Customer Tidak Tersedia" << endl;
    }
}

void deleteOrder(listKurir &LK, string ID, string noOrder){
    adrKurir k = first(LK);
    adrOrder o;
    do {
        o = first(kirim(k));
        while (o != NULL) {
            if (info(o).noOrder == noOrder){
                if (o != NULL){
                    if (o == first(kirim(k))){
                        if (next(o) != NULL){
                            first(kirim(k)) = next(o);
                            next(o) = NULL;
                            pesan(o) = NULL;
                        } else {
                            pesan(o) = NULL;
                        }
                    } else if (o == last(kirim(k))){
                        adrOrder q = first(kirim(k));
                        while (next(q) != last(kirim(k))){
                            q = next(q);
                        }
                        last(kirim(k)) = q;
                        next(q) = NULL;
                        pesan(o) = NULL;
                    } else {
                        adrOrder prec = first(kirim(k));
                        while (next(prec) != o){
                            prec = next(prec);
                        }
                        next(prec) = next(o);
                        next(o) = NULL;
                        pesan(o) = NULL;
                    }
                }
            }
            o = next(o);
        }
        k = next(k);
    } while(k != first(LK));
}


adrOrder searchOrder(listKurir LK, string noOrder){
    adrKurir k = first(LK);
    adrOrder o;
    do {
        o = first(kirim(k));
        while (o != NULL) {
            if (info(o).noOrder == noOrder){
                return o;
            }
            o = next(o);
        }
        k = next(k);
    } while(k != first(LK));
    return NULL;
}

adrKurir searchKurir(listKurir LK, string IDKurir){
    adrKurir p = first(LK);
    if ((first(LK) == NULL) && (last(LK) == NULL)){
        return NULL;
    }else{
        bool berhenti = false;
        while (!berhenti){
            if (info(p).ID == IDKurir){
                return p;
            }
            p = next(p);
            berhenti = p == first(LK);
        }
    }
    return NULL;
}

adrCustomer searchCustomer(listCustomer LC, string NIK){
    adrCustomer p = first(LC);
    if ((first(LC) == NULL) && (last(LC) == NULL)){
        return NULL;
    }else{
        while (p != NULL){
            if (info(p).NIK == NIK){
                return p;
            }
            p = next(p);
        }
    }
    return NULL;
}

void changeTitikKeberangkatanOrder(listKurir &LK, string noOrder, string new_tKeberangkatan){
    adrOrder p = searchOrder(LK, noOrder);
    if (p != NULL){
        info(p).tKeberangkatan = new_tKeberangkatan;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Order Tidak Ditemukan";
    }
}
void changeTitikTujuanOrder(listKurir &LK, string noOrder, string new_tTujuan){
    adrOrder p = searchOrder(LK, noOrder);
    if (p != NULL){
        info(p).tTujuan = new_tTujuan;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Order Tidak Ditemukan";
    }
}
void changeWaktuKeberangkatanOrder(listKurir &LK, string noOrder, string new_wKeberangkatan){
    adrOrder p = searchOrder(LK, noOrder);
    if (p != NULL){
        info(p).wKeberangkatan = new_wKeberangkatan;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Order Tidak Ditemukan";
    }
}
void changeWaktuKedatanganOrder(listKurir &LK, string noOrder, string new_wKedatangan){
    adrOrder p = searchOrder(LK, noOrder);
    if (p != NULL){
        info(p).wKedatangan= new_wKedatangan;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Order Tidak Ditemukan";
    }
}
void changeStatusOrder(listKurir &LK, string noOrder, string new_status){
    adrOrder p = searchOrder(LK, noOrder);
    if (p != NULL){
        info(p).status = new_status;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Order Tidak Ditemukan";
    }
}
void changeRatingOrder(listKurir &LK, string noOrder, float new_ratingOrder){
    adrOrder p = searchOrder(LK, noOrder);
    if (p != NULL){
        info(p).ratingOrder = new_ratingOrder;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Order Tidak Ditemukan";
    }
}

void changeNamaKurir(listKurir &LK, string ID, string new_namaKurir){
    adrKurir p = searchKurir(LK, ID);
    if (p != NULL){
        info(p).namaKurir = new_namaKurir;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Kurir Tidak Ditemukan";
    }
}
void changeKontakKurir(listKurir &LK, string ID, string new_kontakKurir){
    adrKurir p = searchKurir(LK, ID);
    if (p != NULL){
        info(p).kontakKurir = new_kontakKurir;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Kurir Tidak Ditemukan";
    }
}
void changeRatingKurir(listKurir &LK, string ID, float new_ratingKurir){
    adrKurir p = searchKurir(LK, ID);
    if (p != NULL){
        info(p).ratingKurir = new_ratingKurir;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Kurir Tidak Ditemukan";
    }
}

void changeNamaCustomer(listCustomer &LC, string NIK, string new_namaCustomer){
    adrCustomer p = searchCustomer(LC, NIK);
    if (p != NULL){
        info(p).namaCustomer = new_namaCustomer;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Customer Tidak Ditemukan";
    }
}

void changeAlamatCustomer(listCustomer &LC, string NIK, string new_alamatCustomer){
    adrCustomer p = searchCustomer(LC, NIK);
    if (p != NULL){
        info(p).alamatCustomer = new_alamatCustomer;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Customer Tidak Ditemukan";
    }
}

void changeKontakCustomer(listCustomer &LC, string NIK, string new_kontakCustomer){
    adrCustomer p = searchCustomer(LC, NIK);
    if (p != NULL){
        info(p).kontakCustomer = new_kontakCustomer;
        cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
    }else{
        cout << "Data Customer Tidak Ditemukan";
    }
}

void showOrder(listKurir LK){
    adrKurir k = first(LK);
    cout << "============================================================" << endl;
    if (first(LK) == NULL && last(LK) == NULL){
        cout << "Data Kosong" << endl;
    }else{
        bool berhenti = false;
        while (!berhenti){
            adrOrder o = (first(kirim(k)));
            while (o != NULL){
                cout << "Nomor Order: " << info(o).noOrder << endl;
                cout << "Titik Keberangkatan: " << info(o).tKeberangkatan << endl;
                cout << "Titik Tujuan: " << info(o).tTujuan << endl;
                cout << "Waktu Keberangkatan: " << info(o).wKeberangkatan << endl;
                cout << "Waktu Kedatangan: " << info(o).wKedatangan << endl;
                cout << "Status Order: " << info(o).status << endl;
                cout << "Rating Order: " << info(o).ratingOrder << endl;
                cout << endl;
                o = next(o);
            }
            k = next(k);
            berhenti = k == first(LK);
        }
    }
    cout << endl;
}

void showKurir(listKurir LK){
    adrKurir p = first(LK);
    cout << "============================================================" << endl;
    if (first(LK) == NULL && last(LK) == NULL){
        cout << "Data Kurir Kosong" << endl;
    }else{
        bool berhenti = false;
        while (!berhenti){
            cout << "ID Kurir: " << info(p).ID << endl;
            cout << "Nama Kurir: " << info(p).namaKurir << endl;
            cout << "Kontak Kurir: " << info(p).kontakKurir << endl;
            cout << "Rating Kurir: " << info(p).ratingKurir << endl;
            cout << endl;
            p = next(p) ;
            berhenti = p == first(LK);
        }
    }
}

void showCustomer(listCustomer LC){
    adrCustomer p = first(LC);
    cout << "============================================================" << endl;
    if (first(LC) == NULL && last(LC) == NULL){
        cout << "Data Order Kosong" << endl;
    }else{
        while (p != NULL){
            cout << "NIK Customer: " << info(p).NIK << endl;
            cout << "Nama Customer: " << info(p).namaCustomer << endl;
            cout << "Alamat Customer: " << info(p).alamatCustomer << endl;
            cout << "Kontak Customer: " << info(p).kontakCustomer << endl;
            cout << endl;
            p = next(p) ;
        }
    }
}

void showAll(listKurir LK, listCustomer LC){
    adrKurir k = first(LK);
    int i = 1;
    cout << "============================================================" << endl;
    if (first(LK) == NULL && last(LK) == NULL){
        cout << "Data Kosong";
    }else{
        bool berhenti = false;
        while (!berhenti){
            int j = 1;
            cout << "[ Kurir ke-" << i << " ]" << endl;
            cout << "ID Kurir: " << info(k).ID << " || Nama Kurir: " << info(k).namaKurir << endl;
            cout << "------------------------------------------------------------" << endl;
            adrOrder o = (first(kirim(k)));
            if (o == NULL){
                cout << "Kurir Tidak Memiliki Orderan" << endl << endl;
            }else{
                while (o != NULL){
                    cout << "[ Order ke-" << j << " ]" << endl;
                    cout << "No. Order: " << info(o).noOrder << " || Status: " << info(o).status << endl;
                    cout << "NIK Customer: " << info(pesan(o)).NIK << " || Nama Customer: " << info(pesan(o)).namaCustomer << endl;
                    cout << endl;
                    o = next(o);
                    j++;
                }
            }
            cout << "============================================================" << endl;
            k = next(k);
            i++;
            berhenti = k == first(LK);
        }
    }
    adrCustomer c = first(LC);
    int z = 1;
    cout << "[ Customer Yang Belum Mengorder ]" << endl;
    while (c != NULL){
        bool found = false;
        bool berhenti = false;
        k = first(LK);
        while (!berhenti && !found){
            adrOrder o = first(kirim(k));
            while (o != NULL && !found){
                if (info(pesan(o)).NIK == info(c).NIK){
                    found = true;
                }
                o = next(o);
            }
            k = next(k);
            berhenti = k == first(LK);
        }
        if (!found){
            cout << "[" << z << "] NIK Customer: " << info(c).NIK << " || Nama Customer: " << info(c).namaCustomer << endl << endl;
        }
        c = next(c);
    }
}


void showHistKurir(listKurir &LK, string IDKurir){
    adrKurir p = searchKurir(LK, IDKurir);
    cout << "-----------------------------------------------------------" << endl;
    if (p != NULL){
        adrOrder o = (first(kirim(p)));
        int i = 0;
        while (o != NULL){
            cout << "Nomor Order: " << info(o).noOrder << endl;
            cout << "Titik Keberangkatan: " << info(o).tKeberangkatan << endl;
            cout << "Titik Tujuan: " << info(o).tTujuan << endl;
            cout << "Waktu Keberangkatan: " << info(o).wKeberangkatan << endl;
            cout << "Waktu Kedatangan: " << info(o).wKedatangan << endl;
            cout << "Status Order: " << info(o).status << endl;
            cout << "Rating Order: " << info(o).ratingOrder << endl;
            cout << "-----------------------------------------------------------" << endl;
            i++;
            o = next(o);
        }
        cout << endl << "Banyak Orderan yang dikirim: " << i << endl;
    }else{
        cout << "Data Kurir Tidak Ditemukan";
    }
    cout << endl;
}

void showStatusOrder(listKurir LK, string noOrder){
    adrKurir k = first(LK);
    bool berhenti = false;
    while (!berhenti){
        adrOrder o = (first(kirim(k)));
        while (o != NULL){
            if (info(o).noOrder == noOrder){
                cout << "Status Order: " << info(o).status << endl;
            }
            o = next(o);
        }
        k = next(k);
        berhenti = k == first(LK);
    }
    cout << endl;
}

int menu(){
    cout << "===========================================================" << endl;
    cout << "Yasmin Amelia         - 1305220099" << endl;
    cout << "Rezki Yulia Damayanti - 1305223012" << endl;
    cout << "===========================================================" << endl;
    cout << "==================== MENU KURIR ONLINE ====================" << endl;
    cout << "1. Menambahkan Data" << endl;
    cout << "2. Menampilkan Data" << endl;
    cout << "3. Edit Data" << endl;
    cout << "4. Menghapus Data" << endl;
    cout << "5. Search Data" << endl;
    cout << "6. Histori Kurir" << endl;
    cout << "0. Keluar" << endl;
    cout << "===========================================================" << endl;
    cout << "Masukan Pilihan: ";
    int x = 0;
    cin >> x;
    return x;
}

int menuTambahData(){
    cout << "===================== MENU TAMBAH DATA =====================" << endl;
    cout << "1. Tambah Data Kurir" << endl;
    cout << "2. Tambah Data Customer" << endl;
    cout << "3. Tambah Data Order" << endl;
    cout << "0. Kembali" << endl;
    cout << "============================================================" << endl;
    cout << "Masukan Pilihan: ";
    int x = 0;
    cin >> x;
    return x;
}

int menuShowData(){
    cout << "====================== MENU SHOW DATA ======================" << endl;
    cout << "1. Show All Data" << endl;
    cout << "2. Show Data Kurir" << endl;
    cout << "3. Show Data Customer" << endl;
    cout << "4. Show Data Order" << endl;
    cout << "0. Kembali" << endl;
    cout << "============================================================" << endl;
    cout << "Masukan Pilihan: ";
    int x = 0;
    cin >> x;
    return x;
}

int menuEditData(){
    cout << "===================== MENU EDIT DATA =====================" << endl;
    cout << "1. Edit Data Kurir" << endl;
    cout << "2. Edit Data Customer" << endl;
    cout << "3. Edit Data Order" << endl;
    cout << "0. Kembali" << endl;
    cout << "==========================================================" << endl;
    cout << "Masukan Pilihan: ";
    int x = 0;
    cin >> x;
    return x;
}

int menuHapusData(){
    cout << "===================== MENU TAMBAH DATA =====================" << endl;
    cout << "1. Hapus Data Kurir" << endl;
    cout << "2. Hapus Data Customer" << endl;
    cout << "3. Hapus Data Order" << endl;
    cout << "0. Kembali" << endl;
    cout << "============================================================" << endl;
    cout << "Masukan Pilihan: ";
    int x = 0;
    cin >> x;
    return x;
}

int menuSearchData(){
    cout << "===================== MENU SEARCH DATA =====================" << endl;
    cout << "1. Search Data Kurir" << endl;
    cout << "2. Search Data Customer" << endl;
    cout << "3. Search Data Order" << endl;
    cout << "0. Kembali" << endl;
    cout << "============================================================" << endl;
    cout << "Masukan Pilihan: ";
    int x = 0;
    cin >> x;
    return x;
}
