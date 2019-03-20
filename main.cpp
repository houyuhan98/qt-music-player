#include "finalProject.h"
#include <QApplication>
#include"connection.h"
#include<QTime>
int main(int argc, char *argv[])
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QApplication a(argc, argv);
    if(!CreatConnection())
    {
        return 1;
    }
    Widget w;
    w.setWindowIcon(QIcon(":/icons/icons/qtplayer.png"));
    w.setWindowTitle(QObject::tr("QT Music Player"));

    w.setWindowFlags(Qt::FramelessWindowHint);

    w.show();
    return a.exec();
}

