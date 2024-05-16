#ifndef SIINVENTARIS_H // Guard header: mencegah inklusi ganda dari file header yang sama.
#define SIINVENTARIS_H // Mendefinisikan makro SIINVENTARIS_H untuk menandai awal dari file header.

#include <QMainWindow> // Sertakan file header yang diperlukan untuk QMainWindow.

QT_BEGIN_NAMESPACE // Mulai namespace Qt.
namespace Ui {
class SiInventaris; // Deklarasikan kelas SiInventaris dalam namespace Ui.
}
QT_END_NAMESPACE // Akhiri namespace Qt.

class SiInventaris : public QMainWindow // Tentukan kelas SiInventaris, mewarisi dari QMainWindow.
{
    Q_OBJECT // Makro yang diperlukan untuk mendukung sinyal dan slot.

public:
    SiInventaris(QWidget *parent = nullptr); // Deklarasi konstruktor dengan parameter parent opsional.
    ~SiInventaris(); // Deklarasi destruktor.

private slots:
    void on_loginButton_clicked(); // Deklarasi slot privat untuk menangani acara klik tombol login.

private:
    Ui::SiInventaris *ui; // Pointer ke kelas UI yang dihasilkan oleh Qt Designer.

};

#endif // SIINVENTARIS_H // Akhir dari file header dan makro SIINVENTARIS_H.
