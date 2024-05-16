#include "user.h" // Mengimpor header file user.h yang berisi deklarasi kelas User.
#include "ui_user.h" // Mengimpor header file ui_user.h yang berisi deklarasi kelas Ui::User.
#include <QStandardItem> // Mengimpor header file QStandardItem yang diperlukan untuk menggunakan kelas QStandardItem.
#include <QTextStream> // Mengimpor header file QTextStream yang diperlukan untuk manipulasi teks.

// Konstruktor untuk kelas User
User::User(QWidget *parent) :
    QMainWindow(parent), // Memanggil konstruktor kelas induk QMainWindow.
    ui(new Ui::User) // Menginisialisasi objek ui menggunakan konstruktor baru dari kelas Ui::User.
{
    ui->setupUi(this); // Mengatur UI yang telah dibuat menggunakan Qt Designer.

    // Inisialisasi model QStandardItemModel untuk tabel
    model = new QStandardItemModel(this); // Membuat objek model baru dari kelas QStandardItemModel.
    model->setColumnCount(4); // Mengatur jumlah kolom sesuai kebutuhan

    // Sembunyikan header horizontal QTableView secara default
    ui->tableView->horizontalHeader()->setVisible(false); // Mengatur header horizontal tabel agar tidak terlihat secara default.

    // Set header untuk tabel
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Nama Barang" << "Kategori" << "Jumlah");

    // Set model untuk QTableView
    ui->tableView->setModel(model); // Pastikan model diatur ke QTableView di sini

    // Set visibilitas header horizontal QTableView menjadi true setelah model diatur
    ui->tableView->horizontalHeader()->setVisible(true); // Menampilkan header horizontal tabel.
    ui->tableView->verticalHeader()->setVisible(false); // Menyembunyikan header vertikal tabel.
}

// Destruktor untuk kelas User
User::~User()
{
    delete ui; // Menghapus objek ui yang telah dibuat.
}

// Slot untuk tombol Tambah data
void User::on_pushButtonTambah_clicked()
{
    if (jumlahBarang < MAX_BARANG) { // Memastikan jumlah barang belum mencapai batas maksimum
        // Ambil data dari QLineEdit menggunakan text()
        QString id = ui->textEditID->text(); // Mengambil ID barang dari input teks.
        QString nama = ui->textEditNama->text(); // Mengambil nama barang dari input teks.
        QString kategori = ui->textEditKategori->text(); // Mengambil kategori barang dari input teks.
        int jumlah = ui->textEditJumlah->text().toInt(); // Mengambil jumlah barang dari input teks dan mengonversinya ke integer.

        // Simpan data ke dalam array dataBarang
        dataBarang[jumlahBarang].id = id;
        dataBarang[jumlahBarang].nama = nama;
        dataBarang[jumlahBarang].kategori = kategori;
        dataBarang[jumlahBarang].jumlah = jumlah;

        // Tambahkan jumlahBarang
        jumlahBarang++;

        // Tampilkan data ke dalam QTableView
        tampilkanData();
    }
}

// Menghapus data dari model dan array dataBarang
void User::hapusData(int index)
{
    if (index >= 0 && index < jumlahBarang) { // Memastikan indeks yang akan dihapus valid
        // Hapus data dari model
        model->removeRow(index);

        // Geser data pada array untuk menutup celah
        for (int i = index; i < jumlahBarang - 1; ++i) {
            dataBarang[i] = dataBarang[i + 1];
        }

        // Kurangi jumlahBarang karena satu data telah dihapus
        jumlahBarang--;
    }
}

// Slot untuk tombol Hapus data
void User::on_pushButtonHapus_clicked()
{
    // Dapatkan indeks baris yang dipilih
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty()) { // Memastikan ada baris yang dipilih
        // Hapus data dari model dan array
        int index = selectedIndexes.at(0).row(); // Mendapatkan indeks baris yang dipilih
        hapusData(index); // Menghapus data pada indeks yang dipilih
    }
}

// Slot untuk tombol Urutkan
void User::on_pushButtonUrutkan_clicked()
{
    // Panggil fungsi bubbleSort() untuk mengurutkan dataBarang
    bubbleSort();

    // Tampilkan data terurut ke dalam QTableView
    tampilkanData();
}

// Algoritma Bubble Sort untuk mengurutkan dataBarang berdasarkan ID barang
void User::bubbleSort()
{
    for (int i = 0; i < jumlahBarang - 1; ++i) {
        for (int j = 0; j < jumlahBarang - i - 1; ++j) {
            // Bandingkan ID barang setelah mengonversinya ke integer
            if (dataBarang[j].id.toInt() > dataBarang[j + 1].id.toInt()) {
                // Tukar posisi data
                Barangs temp = dataBarang[j];
                dataBarang[j] = dataBarang[j + 1];
                dataBarang[j + 1] = temp;
            }
        }
    }
}

// Menampilkan data dari array dataBarang ke dalam QTableView
void User::tampilkanData()
{
    // Bersihkan model sebelum menambahkan data baru
    model->clear();

    // Set header untuk tabel
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Nama Barang" << "Kategori" << "Jumlah");

    // Tampilkan data ke dalam QTableView
    for (int i = 0; i < jumlahBarang; ++i) {
        QList<QStandardItem *> rowItems;
        rowItems << new QStandardItem(dataBarang[i].id) // Menambahkan ID barang ke baris.
                 << new QStandardItem(dataBarang[i].nama) // Menambahkan nama barang ke baris.
                 << new QStandardItem(dataBarang[i].kategori) // Menambahkan kategori barang ke baris.
                 << new QStandardItem(QString::number(dataBarang[i].jumlah)); // Menambahkan jumlah barang ke baris.
        model->appendRow(rowItems); // Menambahkan baris ke model.
    }
}
