#include <QApplication>
#include <QLabel>

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    QLabel ventana("Holaaaa");
    ventana.resize(640, 480);
    ventana.show();

    return app.exec();

}