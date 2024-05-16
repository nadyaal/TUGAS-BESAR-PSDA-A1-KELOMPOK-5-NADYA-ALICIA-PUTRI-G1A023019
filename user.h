#ifndef USER_H // Guard header: mencegah inklusi ganda dari file header yang sama.
#define USER_H // Mendefinisikan makro USER_H untuk menandai awal dari file header.

#include <QMainWindow> // Sertakan file header yang diperlukan untuk QMainWindow.
#include <QStandardItemModel> // Sertakan file header yang diperlukan untuk QStandardItemModel.

// Struktur data untuk barang
struct Barangs {
    QString id; // ID barang
    QString nama; // Nama barang
    QString kategori; // Kategori barang
    int jumlah; // Jumlah barang
};

QT_BEGIN_NAMESPACE // Mulai namespace Qt.
namespace Ui { class User; } // Deklarasikan kelas User dalam namespace Ui.
QT_END_NAMESPACE // Akhiri namespace Qt.

class User : public QMainWindow // Tentukan kelas User, mewarisi dari QMainWindow.
{
    Q_OBJECT // Makro yang diperlukan untuk mendukung sinyal dan slot.

public:
    explicit User(QWidget *parent = nullptr); // Deklarasi konstruktor dengan parameter parent opsional.
    ~User(); // Deklarasi destruktor.

private slots:
    void on_pushButtonTambah_clicked(); // Slot untuk menangani acara klik tombol Tambah data.
    void on_pushButtonUrutkan_clicked(); // Slot untuk menangani acara klik tombol Urutkan data.
    void on_pushButtonHapus_clicked(); // Slot untuk menangani acara klik tombol Hapus data.

private:
    Ui::User *ui; // Pointer ke objek UI yang dihasilkan oleh Qt Designer.
    QStandardItemModel *model; // Pointer ke model tabel.

    // Array untuk menyimpan data barang
    static const int MAX_BARANG = 100; // Konstanta untuk jumlah maksimum barang.
    Barangs dataBarang[MAX_BARANG]; // Array untuk menyimpan data barang.
    int jumlahBarang = 0; // Variabel untuk melacak jumlah barang yang disimpan.

    void tampilkanData(); // Fungsi untuk menampilkan data di dalam QTableView.
    void hapusData(int index); // Fungsi untuk menghapus data dari tabel dan array berdasarkan indeks.
    void bubbleSort(); // Fungsi untuk mengurutkan data barang berdasarkan ID menggunakan algoritma bubble sort.
};

#endif // USER_H // Akhir dari file header dan makro USER_H.
