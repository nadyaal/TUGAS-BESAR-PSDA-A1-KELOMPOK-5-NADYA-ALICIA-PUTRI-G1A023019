#include "siinventaris.h" // Mengimpor header file siinventaris.h yang berisi deklarasi kelas SiInventaris.

#include <QApplication> // Mengimpor header file QApplication yang diperlukan untuk membuat aplikasi Qt.

int main(int argc, char *argv[]) // Fungsi main, titik masuk utama untuk aplikasi.
{
    QApplication a(argc, argv); // Membuat objek QApplication yang mengelola aplikasi Qt.
    SiInventaris w; // Membuat objek SiInventaris, yang merupakan jendela utama aplikasi.
    w.show(); // Menampilkan jendela utama aplikasi.
    return a.exec(); // Memulai loop utama aplikasi Qt dan menjalankan aplikasi hingga aplikasi ditutup.
}
