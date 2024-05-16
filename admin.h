#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow> // Mengimpor kelas QMainWindow dari Qt
#include <QStandardItemModel> // Mengimpor kelas QStandardItemModel dari Qt

// Struktur data untuk barang
struct Barang {
    QString id; // ID barang
    QString nama; // Nama barang
    QString kategori; // Kategori barang
    int jumlah; // Jumlah barang
};

QT_BEGIN_NAMESPACE
namespace Ui { class Admin; } // Namespace untuk kelas UI
QT_END_NAMESPACE

class Admin : public QMainWindow
{
    Q_OBJECT // Macro Qt untuk mendukung fitur seperti slot dan sinyal

public:
    explicit Admin(QWidget *parent = nullptr); // Konstruktor dengan parameter parent yang default-nya nullptr
    ~Admin(); // Destruktor

private slots:
    void on_pushButtonTambah_clicked(); // Slot untuk menangani klik tombol Tambah data
    void on_pushButtonUrutkan_clicked(); // Slot untuk menangani klik tombol Urutkan data
    void on_pushButtonHapus_clicked(); // Slot untuk menangani klik tombol Hapus data
    void on_pushButtonUpdate_clicked(); // Slot untuk menangani klik tombol Update data

private:
    Ui::Admin *ui; // Pointer ke objek UI yang dibuat dari file .ui
    QStandardItemModel *model; // Pointer ke model yang digunakan untuk QTableView

    // Array untuk menyimpan data barang
    static const int MAX_BARANG = 100; // Konstanta untuk jumlah maksimum barang
    Barang dataBarang[MAX_BARANG]; // Array untuk menyimpan data barang
    int jumlahBarang = 0; // Variabel untuk melacak jumlah barang yang disimpan

    void tampilkanData(); // Fungsi untuk menampilkan data di dalam QTableView
    void hapusData(int index); // Fungsi untuk menghapus data dari tabel dan array berdasarkan indeks
    void bubbleSort(); // Fungsi untuk mengurutkan data barang berdasarkan ID menggunakan algoritma bubble sort
};

#endif // ADMIN_H
