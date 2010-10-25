#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QImage>
#include <QLabel>

#include <iostream>
#include <fstream>
using namespace std;

class MyWidget: public QWidget {
public:
    MyWidget(QWidget *parent = 0);
};

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent) {
    QPushButton *quit = new QPushButton("Quit");
    quit->setFont(QFont("Times", 18, QFont::Bold));

    QLabel * imageLabel = new QLabel;
    //    QImage image("../img.png");

    QPixmap pix;
    //
    ifstream::pos_type size;
    char * memblock;
    //
    ifstream file("../img.raw", ios::in | ios::binary | ios::ate);
    if (file.is_open()) {
        size = file.tellg();
        memblock = new char[size];
        file.seekg(0, ios::beg);
        file.read(memblock, size);
        file.close();

        cout << "the complete file content is in memory: " << size << endl;

        uchar * n = (uchar *) memblock;

        QImage img(n, 640, 320, 640 * 3, QImage::Format_RGB888); // 2 pixels width, 2 pixels height, 6 bytes per line, RGB888 format

        QImage scaled = img.scaled(100, 100); // Scale image to show results better
        QPixmap pix = QPixmap::fromImage(img); // Create pixmap from image
        imageLabel->setPixmap(pix); // Show result on a form

        //        pix.loadFromData((const uchar*) memblock, size);

        //            delete[] memblock;
    }
    //
    //    imageLabel->setPixmap(pix);


    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(quit);
    layout->addWidget(imageLabel);

    setLayout(layout);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget;
    widget.show();
    return app.exec();
}
