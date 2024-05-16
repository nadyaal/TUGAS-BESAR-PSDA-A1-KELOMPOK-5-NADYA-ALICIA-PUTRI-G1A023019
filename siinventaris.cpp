#include "siinventaris.h" // Mengimpor file header siinventaris.h yang berisi deklarasi kelas SiInventaris.
#include "admin.h" // Mengimpor file header admin.h yang berisi deklarasi kelas Admin.
#include "user.h" // Mengimpor file header user.h yang berisi deklarasi kelas User.
#include "ui_siinventaris.h" // Mengimpor file header ui_siinventaris.h yang berisi deklarasi kelas Ui::SiInventaris.
#include "ui_admin.h" // Mengimpor file header ui_admin.h yang berisi deklarasi kelas Ui::Admin.
#include "ui_user.h" // Mengimpor file header ui_user.h yang berisi deklarasi kelas Ui::User.
#include <QMessageBox> // Mengimpor header file QMessageBox yang diperlukan untuk menampilkan pesan dialog.

SiInventaris::SiInventaris(QWidget *parent)
    : QMainWindow(parent) // Memanggil konstruktor kelas induk QMainWindow.
    , ui(new Ui::SiInventaris) // Menginisialisasi objek ui menggunakan konstruktor baru dari kelas Ui::SiInventaris.
{
    ui->setupUi(this); // Mengatur UI yang telah dibuat menggunakan Qt Designer.
}

SiInventaris::~SiInventaris() // Destruktor untuk kelas SiInventaris.
{
    delete ui; // Menghapus objek ui yang telah dibuat.
}

void SiInventaris::on_loginButton_clicked() // Slot untuk tombol login yang diklik.
{
    QString username = ui->usernameLineEdit->text(); // Mendapatkan username dari input line edit.
    QString password = ui->passwordLineEdit->text(); // Mendapatkan password dari input line edit.

    // Memeriksa apakah username dan password sesuai dengan yang diinginkan
    if (username == "admin" && password == "admin") { // Jika login sebagai admin
        // Jika sesuai, tampilkan pesan berhasil dan lanjutkan ke aplikasi utama
        QMessageBox::information(this, "Login", "Login sebagai admin berhasil!");
        // Lanjutkan ke aplikasi utama, yaitu HalamanAdmin
        Admin *admin = new Admin(); // Membuat objek Admin
        admin->show(); // Menampilkan Admin
        this->close(); // Menutup jendela login
    }
    else if (username == "user" && password == "user") { // Jika login sebagai user
        QMessageBox::information(this, "Login", "Login sebagai user berhasil!");
        User *user = new User(); // Membuat objek User
        user->show(); // Menampilkan User
        this->close(); // Menutup jendela login
    }
    else {
        // Jika tidak sesuai, tampilkan pesan gagal login
        QMessageBox::warning(this, "Login", "Username atau password salah!");
    }
}
