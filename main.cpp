#include <iostream>
#include "Kurir.h"

using namespace std;

int main()
{
    listOrder LO;
    listKurir LK;
    listCustomer LC;

    adrCustomer c;
    adrKurir k;
    adrOrder o;

    order ord;
    kurir kur;
    customer cust;

    createListKurir(LK);
    createListCustomer(LC);

    int m, n;
    m = menu();
    while (m != 0){
        if (m == 1){
            n = menuTambahData();
            cout << "===========================================================" << endl;
            if (n == 1){
                int nKurir;
                kurir kur;
                cout << "Jumlah kurir yang ingin ditambahkan: ";
                cin >> nKurir;
                cout << "-----------------------------------------------------------" << endl;
                for (int j = 0; j < nKurir; j++){
                    cout << "ID Kurir: ";
                    cin >> kur.ID;
                    cout << "Nama Kurir: ";
                    cin >> kur.namaKurir;
                    cout << "Kontak Kurir: ";
                    cin >> kur.kontakKurir;
                    cout << "Rating Kurir: ";
                    cin >> kur.ratingKurir;
                    cout << endl;

                    adrKurir k;
                    k = alokasiKurir(kur);
                    insertLastKurir(LK, k);
                }
                m = menu();
            } else if (n == 2){
                int nCust;
                customer cust;
                cout << "Jumlah Customer yang ingin ditambahkan: ";
                cin >> nCust;
                cout << "-----------------------------------------------------------" << endl;
                for (int j = 0; j < nCust; j++){
                    cout << "NIK Customer: ";
                    cin >> cust.NIK;
                    cout << "Nama Customer: ";
                    cin >> cust.namaCustomer;
                    cout << "Alamat Customer: ";
                    cin >> cust.alamatCustomer;
                    cout << "Kontak Customer: ";
                    cin >> cust.kontakCustomer;
                    cout << endl;
                    adrCustomer c;
                    c = alokasiCustomer(cust);
                    insertLastCustomer(LC, c);
                }
                m = menu();
            } else if (n == 3){
                int nOrder;
                order ord;
                cout << "Jumlah Order yang ingin ditambahkan: ";
                cin >> nOrder;
                cout << "-----------------------------------------------------------" << endl;
                for (int j = 0; j < nOrder; j++){

                    string IDKurir, NIK_penerima;
                    cout << "ID Kurir Pengantar: ";
                    cin >> IDKurir;
                    cout << "NIK Customer Penerima: ";
                    cin >> NIK_penerima;
                    cout << "No Order: ";
                    cin >> ord.noOrder;
                    cout << "Titik Keberangkatan: ";
                    cin >> ord.tKeberangkatan;
                    cout << "Titik Tujuan: ";
                    cin >> ord.tTujuan;
                    cout << "Tanggal Pengiriman: ";
                    cin >> ord.wKeberangkatan;
                    cout << "Estimasi Barang Sampai: ";
                    cin >> ord.wKedatangan;
                    cout << "Status Pengiriman: ";
                    cin >> ord.status;

                    string stat = ord.status;
                    if (stat == "Sampai"){
                        cout << "Rating Order: ";
                        cin >> ord.ratingOrder;
                    } else {
                        ord.ratingOrder = 0;
                    }
                    cout << endl;
                    connect(LK, IDKurir, LC, NIK_penerima, ord);
                }
                m = menu();
            } else if (n == 0){
                m = menu();
            }
        } else if (m == 2){
            m = menuShowData();
            if (m == 1){
                showAll(LK, LC);
                m = menu();
            } else if (m == 2){
                showKurir(LK);
                m = menu();
            } else if (m == 3){
                showCustomer(LC);
                m = menu();
            } else if (m == 4){
                showOrder(LK);
                m = menu();
            } else if (m == 0){
                m = menu();
            }
        } else if (m == 3){
            m = menuEditData();
            if (m == 1){
                cout << "===================== MENU EDIT KURIR =====================" << endl;
                cout << "1. Edit Nama Kurir" << endl;
                cout << "2. Edit Kontak Kurir" << endl;
                cout << "3. Edit Rating Kurir" << endl;
                cout << "0. Kembali" << endl;
                cout << "===========================================================" << endl;
                cout << "Data yang ingin diubah: ";
                int ubah;
                string IDkurir;
                cin >> ubah;

                showKurir(LK);
                cout << "-----------------------------------------------------------" << endl;
                cout << "ID Kurir yang ingin di-edit: ";
                cin >> IDkurir;

                if (ubah == 1){
                    string Nama_baru;
                    cout << "Nama kurir (yang baru): ";
                    cin >> Nama_baru;
                    changeNamaKurir(LK, IDkurir, Nama_baru);
                    m = menu();
                } else if (ubah == 2){
                    string kontak_baru;
                    cout << "Kontak kurir (yang baru): ";
                    cin >> kontak_baru;
                    changeKontakKurir(LK, IDkurir, kontak_baru);
                    m = menu();
                } else if (ubah == 3){
                    float rating_baru;
                    cout << "Rating kurir (yang baru): ";
                    cin >> rating_baru;
                    changeRatingKurir(LK, IDkurir, rating_baru);
                    m = menu();
                } else if (ubah == 0){
                    m = menu();
                }
            } else if (m == 2){
                cout << "=================== MENU EDIT CUSTOMER ===================" << endl;
                cout << "1. Edit Nama Customer" << endl;
                cout << "2. Edit Alamat Customer" << endl;
                cout << "3. Edit Kontak Customer" << endl;
                cout << "0. Kembali" << endl;
                cout << "==========================================================" << endl;
                cout << "Data yang ingin diubah: ";
                int ubah1;
                cin >> ubah1;
                string NIKcust;

                showCustomer(LC);
                cout << "-----------------------------------------------------------" << endl;
                cout << "NIK yang ingin di-edit: ";
                cin >> NIKcust;

                if (ubah1 == 1){
                    string nama_barucust;
                    cout << "Nama customer (yang baru): ";
                    cin >> nama_barucust;
                    changeNamaCustomer(LC, NIKcust, nama_barucust);
                    m = menu();
                } else if (ubah1 == 2){
                    string alamat_baru;
                    cout << "Alamat customer (yang baru): ";
                    cin >> alamat_baru;
                    changeAlamatCustomer(LC, NIKcust, alamat_baru);
                    m = menu();
                } else if (ubah1 == 3){
                    string kontakcust_baru;
                    cout << "Kontak customer (yang baru): ";
                    cin >> kontakcust_baru;
                    changeKontakCustomer(LC, NIKcust, kontakcust_baru);
                    m = menu();
                } else if (ubah1 == 0){
                    m = menu();
                }
            } else if (m == 3){
                cout << "===================== MENU EDIT ORDER =====================" << endl;
                cout << "1. Edit Titik Keberangkatan Order" << endl;
                cout << "2. Edit Titik Tujuan Order" << endl;
                cout << "3. Edit Waktu Keberangkatan Order" << endl;
                cout << "4. Edit Waktu Kedatangan Order" << endl;
                cout << "5. Edit Status Order" << endl;
                cout << "6. Edit Rating Order" << endl;
                cout << "0. Kembali" << endl;
                cout << "===========================================================" << endl;
                cout << "Data yang ingin diubah: ";
                int ubah2;
                cin >> ubah2;
                string noOrd;

                showCustomer(LC);
                cout << "-----------------------------------------------------------" << endl;
                cout << "No. Order yang ingin di-edit: ";
                cin >> noOrd;

                if (ubah2 == 1){
                    string new_tberangkat;
                    cout << "Titik Keberangkatan (yang baru): ";
                    cin >> new_tberangkat;
                    changeTitikKeberangkatanOrder(LK, noOrd, new_tberangkat);
                    cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
                    m = menu();
                } else if (ubah2 == 2){
                    string new_ttujuan;
                    cout << "Titik Tujuan (yang baru): ";
                    cin >> new_ttujuan;
                    changeTitikTujuanOrder(LK, noOrd, new_ttujuan);
                    cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
                    m = menu();
                } else if (ubah2 == 3){
                    string new_wberangkat;
                    cout << "Waktu Keberangkatan (yang baru): ";
                    cin >> new_wberangkat;
                    changeWaktuKeberangkatanOrder(LK, noOrd, new_wberangkat);
                    cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
                    m = menu();
                } else if (ubah2 == 4){
                    string new_wdatang;
                    cout << "Waktu Kedatangan (yang baru): ";
                    cin >> new_wdatang;
                    changeWaktuKedatanganOrder(LK, noOrd, new_wdatang);
                    cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
                    m = menu();
                } else if (ubah2 == 5){
                    string new_stat;
                    cout << "Status Order (yang baru): ";
                    cin >> new_stat;
                    changeStatusOrder(LK, noOrd, new_stat);
                    cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
                    m = menu();
                } else if (ubah2 == 6){
                    string new_rating;
                    cout << "Rating Order (yang baru): ";
                    cin >> new_rating;
                    changeStatusOrder(LK, noOrd, new_rating);
                    cout << "------------------ Data Berhasil Diubah! ------------------" << endl;
                    m = menu();
                } else {
                    m = menu();
                }
            } else if(m == 0){
                m = menu();
            }
        } else if (m == 4){
            m = menuHapusData();
            cout << "===========================================================" << endl;
            if (m == 1){
                string IDKurir;
                adrKurir p;
                showKurir(LK);
                cout << "===========================================================" << endl;
                cout << "ID Kurir (yang ingin dihapus): ";
                cin >> IDKurir;
                deleteKurir(LK, IDKurir, p);
                cout << "------------------ Data Berhasil Dihapus ------------------" << endl;
                m = menu();
            } else if(m == 2){
                string NIK;
                adrCustomer p;
                showCustomer(LC);
                cout << "===========================================================" << endl;
                cout << "NIK Customer (yang ingin dihapus): ";
                cin >> NIK;
                deleteCustomer(LC, LK, NIK, p);
                cout << "------------------ Data Berhasil Dihapus ------------------" << endl;
                m = menu();
            } else if (m == 3){
                string IDKurir, noOrder;
                showAll(LK, LC);
                cout << "===========================================================" << endl;
                cout << "ID Kurir (untuk order yang akan dihapus): ";
                cin >> IDKurir;
                cout << "Nomor Order (yang ingin dihapus): ";
                cin >> noOrder;
                deleteOrder(LK, IDKurir, noOrder);
                cout << "------------------ Data Berhasil Dihapus ------------------" << endl;
                m = menu();
            } else if (m == 0){
                m = menu();
            }
        } else if (m == 5){
            m = menuSearchData();
            cout << "===========================================================" << endl;
            if (m == 1){
                string IDKurir;
                cout << "ID Kurir (yang ingin dicari): ";
                cin >> IDKurir;
                cout << "-----------------------------------------------------------" << endl;
                adrKurir k = searchKurir(LK, IDKurir);
                if (k != NULL){
                    cout << "[ Informasi Kurir ]" << endl;
                    cout << "Nama Kurir: " << info(k).namaKurir << endl;
                    cout << "Kontak Kurir: " << info(k).kontakKurir << endl;
                    cout << "Rating Kurir: " << info(k).ratingKurir << endl;
                } else {
                    cout << "Data Tidak Ditemukan" << endl;
                }
                m = menu();
            } else if (m == 2){
                string NIK;
                cout << "NIK Customer (yang ingin dicari): ";
                cin >> NIK;
                cout << "-----------------------------------------------------------" << endl;
                adrCustomer c = searchCustomer(LC, NIK);
                if (c != NULL){
                    cout << "[ Informasi Customer ]" << endl;
                    cout << "Nama Customer: " << info(c).namaCustomer << endl;
                    cout << "Alamat Customer: " << info(c).alamatCustomer << endl;
                    cout << "Kontak Customer: " << info(c).kontakCustomer << endl;
                } else {
                    cout << "Data Tidak Ditemukan" << endl;
                }
                m = menu();
            } else if (m == 3){
                string noOrder;
                cout << "No. Order (yang ingin dicari): ";
                cin >> noOrder;
                cout << "-----------------------------------------------------------" << endl;
                adrOrder o = searchOrder(LK, noOrder);
                if (o != NULL){
                    cout << "[ Informasi Order ]" << endl;
                    cout << "Titik Keberangkatan: " << info(o).tKeberangkatan << endl;
                    cout << "Tujuan: " << info(o).tTujuan << endl;
                    cout << "Tanggal Pengiriman: " << info(o).wKeberangkatan << endl;
                    cout << "Estimasi Kedatangan: " << info(o).wKedatangan << endl;
                    cout << "Status: " << info(o).status << endl;
                    cout << "Rating Order: " << info(o).ratingOrder << endl;
                } else {
                    cout << "Data Tidak Ditemukan" << endl;
                }
                m = menu();
            } else if (m == 0){
                m = menu();
            }
        } else if (m == 6){
            cout << "===========================================================" << endl;
            string IDKurir;
            cout << "ID Kurir (yang ingin dicari): ";
            cin >> IDKurir;
            showHistKurir(LK, IDKurir);
            m = menu();
        }
    }
    cout << "===========================================================" << endl;
    cout << "              ANDA TELAH KELUAR DARI PROGRAM               " << endl;
    cout << "===========================================================" << endl;
    return 0;
}
