#include "admin.h" // Mengimpor header file admin.h yang berisi deklarasi kelas Admin.
#include "ui_admin.h" // Mengimpor header file ui_admin.h yang berisi deklarasi kelas Ui::Admin.
#include <QStandardItem> // Mengimpor header file QStandardItem yang diperlukan untuk menggunakan kelas QStandardItem.
#include <QTextStream> // Mengimpor header file QTextStream yang diperlukan untuk manipulasi teks.

// Konstruktor untuk kelas Admin
Admin::Admin(QWidget *parent) :
    QMainWindow(parent), // Memanggil konstruktor kelas induk QMainWindow dengan parent sebagai parameter.
    ui(new Ui::Admin) // Menginisialisasi objek ui menggunakan konstruktor baru dari kelas Ui::Admin.
{
    ui->setupUi(this); // Mengatur UI yang telah dibuat menggunakan Qt Designer.

    // Inisialisasi model QStandardItemModel untuk tabel
    model = new QStandardItemModel(this); // Membuat objek model baru dari kelas QStandardItemModel.
    model->setColumnCount(4); // Menentukan jumlah kolom sesuai kebutuhan (4 kolom).

    // Sembunyikan header horizontal QTableView secara default
    ui->tableView->horizontalHeader()->setVisible(false); // Mengatur header horizontal tabel agar tidak terlihat secara default.

    // Set header untuk tabel
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Nama Barang" << "Kategori" << "Jumlah"); // Mengatur label header untuk kolom tabel.

    // Set model untuk QTableView
    ui->tableView->setModel(model); // Menetapkan model ke QTableView.

    // Set visibilitas header horizontal QTableView menjadi true setelah model diatur
    ui->tableView->horizontalHeader()->setVisible(true); // Mengatur header horizontal tabel agar terlihat setelah model diatur.
    ui->tableView->verticalHeader()->setVisible(false); // Mengatur header vertikal tabel agar tidak terlihat.
}

// Destruktor untuk kelas Admin
Admin::~Admin()
{
    delete ui; // Menghapus objek ui yang telah dibuat untuk mencegah kebocoran memori.
}

// Slot untuk tombol Tambah data
void Admin::on_pushButtonTambah_clicked()
{
    if (jumlahBarang < MAX_BARANG) { // Memeriksa apakah jumlahBarang masih di bawah batas maksimum.
        // Ambil data dari QLineEdit menggunakan text()
        QString id = ui->textEditID->text(); // Mengambil ID barang dari input teks.
        QString nama = ui->textEditNama->text(); // Mengambil nama barang dari input teks.
        QString kategori = ui->textEditKategori->text(); // Mengambil kategori barang dari input teks.
        int jumlah = ui->textEditJumlah->text().toInt(); // Mengambil jumlah barang dari input teks dan mengonversinya ke integer.

        // Simpan data ke dalam array dataBarang
        dataBarang[jumlahBarang].id = id; // Menyimpan ID barang ke dalam array.
        dataBarang[jumlahBarang].nama = nama; // Menyimpan nama barang ke dalam array.
        dataBarang[jumlahBarang].kategori = kategori; // Menyimpan kategori barang ke dalam array.
        dataBarang[jumlahBarang].jumlah = jumlah; // Menyimpan jumlah barang ke dalam array.

        // Tambahkan jumlahBarang
        jumlahBarang++; // Menambahkan nilai jumlahBarang.

        // Tampilkan data ke dalam QTableView
        tampilkanData(); // Memanggil fungsi tampilkanData untuk memperbarui tampilan tabel.
    }
}

// Slot untuk tombol Urutkan
void Admin::on_pushButtonUrutkan_clicked()
{
    // Panggil fungsi bubbleSort() untuk mengurutkan dataBarang
    bubbleSort(); // Memanggil fungsi bubbleSort untuk mengurutkan data barang.

    // Tampilkan data terurut ke dalam QTableView
    tampilkanData(); // Memanggil fungsi tampilkanData untuk memperbarui tampilan tabel dengan data yang sudah diurutkan.
}

// Algoritma Bubble Sort untuk mengurutkan dataBarang berdasarkan ID barang
void Admin::bubbleSort()
{
    for (int i = 0; i < jumlahBarang - 1; ++i) { // Looping untuk setiap elemen kecuali yang terakhir.
        for (int j = 0; j < jumlahBarang - i - 1; ++j) { // Looping untuk membandingkan elemen bersebelahan.
            // Bandingkan ID barang setelah mengonversinya ke integer
            if (dataBarang[j].id.toInt() > dataBarang[j + 1].id.toInt()) { // Mengonversi ID ke integer dan membandingkannya.
                // Tukar posisi data
                Barang temp = dataBarang[j]; // Menyimpan sementara dataBarang[j] ke dalam temp.
                dataBarang[j] = dataBarang[j + 1]; // Menukar posisi dataBarang[j] dengan dataBarang[j + 1].
                dataBarang[j + 1] = temp; // Menempatkan nilai temp ke dataBarang[j + 1].
            }
        }
    }
}

// Menampilkan data dari array dataBarang ke dalam QTableView
void Admin::tampilkanData()
{
    // Bersihkan model sebelum menambahkan data baru
    model->clear(); // Membersihkan data model sebelum menambahkan data baru.

    // Set header untuk tabel
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Nama Barang" << "Kategori" << "Jumlah"); // Mengatur label header untuk kolom tabel.

    // Tampilkan data ke dalam QTableView
    for (int i = 0; i < jumlahBarang; ++i) { // Looping melalui semua data barang.
        QList<QStandardItem *> rowItems; // Membuat list untuk menyimpan item baris.
        rowItems << new QStandardItem(dataBarang[i].id) // Menambahkan item ID ke dalam list.
                 << new QStandardItem(dataBarang[i].nama) // Menambahkan item nama barang ke dalam list.
                 << new QStandardItem(dataBarang[i].kategori) // Menambahkan item kategori barang ke dalam list.
                 << new QStandardItem(QString::number(dataBarang[i].jumlah)); // Menambahkan item jumlah barang ke dalam list.
        model->appendRow(rowItems); // Menambahkan list item ke dalam model sebagai baris baru.
    }
}

// Menghapus data dari model dan array dataBarang
void Admin::hapusData(int index)
{
    if (index >= 0 && index < jumlahBarang) { // Memeriksa apakah indeks valid.
        // Hapus data dari model
        model->removeRow(index); // Menghapus baris dari model berdasarkan indeks.

        // Geser data pada array untuk menutup celah
        for (int i = index; i < jumlahBarang - 1; ++i) { // Looping untuk menggeser data di array.
            dataBarang[i] = dataBarang[i + 1]; // Menggeser data ke posisi sebelumnya.
        }

        // Kurangi jumlahBarang karena satu data telah dihapus
        jumlahBarang--; // Mengurangi jumlahBarang setelah data dihapus.
    }
}

// Slot untuk tombol Hapus data
void Admin::on_pushButtonHapus_clicked()
{
    // Dapatkan indeks baris yang dipilih
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows(); // Mengambil daftar indeks baris yang dipilih.
    if (!selectedIndexes.isEmpty()) { // Memeriksa apakah ada baris yang dipilih.
        // Hapus data dari model dan array
        int index = selectedIndexes.at(0).row(); // Mengambil indeks baris pertama yang dipilih.
        hapusData(index); // Memanggil fungsi hapusData untuk menghapus data pada indeks tersebut.
    }
}

// Slot untuk tombol update data
void Admin::on_pushButtonUpdate_clicked()
{
    // Mendapatkan indeks baris yang dipilih dari QTableView
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows(); // Mengambil daftar indeks baris yang dipilih.
    if (!selectedIndexes.isEmpty()) { // Memeriksa apakah ada baris yang dipilih.
        int index = selectedIndexes.at(0).row(); // Mengambil indeks baris pertama yang dipilih.

        // Ambil data dari input teks yang ingin diupdate
        QString id = ui->textEditID->text(); // Mengambil ID barang dari input teks.
        QString nama = ui->textEditNama->text(); // Mengambil nama barang dari input teks.
        QString kategori = ui->textEditKategori->text(); // Mengambil kategori barang dari input teks.
        int jumlah = ui->textEditJumlah->text().toInt(); // Mengambil jumlah barang dari input teks dan mengonversinya ke integer.

        // Update data di dalam array
        dataBarang[index].id = id; // Memperbarui ID barang di dalam array.
        dataBarang[index].nama = nama; // Memperbarui nama barang di dalam array.
        dataBarang[index].kategori = kategori; // Memperbarui kategori barang di dalam array.
        dataBarang[index].jumlah = jumlah; // Memperbarui jumlah barang di dalam array.

        // Tampilkan data yang telah diupdate di dalam QTableView
        tampilkanData(); // Memanggil fungsi untuk menampilkan data yang telah diupdate di dalam tabel.
    }
}
