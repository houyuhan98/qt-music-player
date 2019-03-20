#ifndef FINALPROJECT_H
#define FINALPROJECT_H

#include<QWidget>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QPixmap>
#include<QPalette>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QAction>
#include<QMouseEvent>
#include<QList>
#include<QPaintEvent>
#include<QSqlTableModel>
class QMediaPlayer;
class QMediaPlaylist;
class QMenu;
class QAction;
class QSqlTableModel;
class Form;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);

    void updatalistwidget(int value);
    void changeVolume(int values);

    void pushbuttonstyle_3();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    ~Widget();
private slots:
    void on_pushButton_7_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void action1_slot();
    void ClearALL_1_slot();
    void action2_slot();
    void action3_slot();
    void action4_slot();
    void action5_1_slot();
    void action5_2_slot();
    void action5_3_slot();
    void action6_slot();
    void Action1_3_slot();
    void Action2_3_slot();

    void contextMenuEvent(QContextMenuEvent *event);
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_5_clicked();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);
    void music_stateChange(QMediaPlayer::State state);
    void Next_slot();
    void Pre_slot();
    void Data_slot(int row,int position,QMediaPlaylist *list,QMediaPlayer::State state,QMediaPlaylist::PlaybackMode mode_1);

private:
    void CreateSortCut();

    Ui::Widget *ui;
    QMediaPlayer *music=NULL;

    QMediaPlaylist *playlist_1=NULL;

    QPixmap pix;
    QPalette pal;

    QAction *clearAll;
    QAction *clearAll_1;
    QAction *mission1;
    QAction *mission2;
    QAction *mission3;
    QAction *mission4;
    QAction *mission5;
    QAction *mission5_1;
    QAction *mission5_2;
    QAction *mission5_3;
    QAction *mission6;
    QMenu *menu;
    QPoint offset;
    double transparency;

    QSqlTableModel *mode_1;
    QSqlTableModel *mode_2;
    QSqlTableModel *mode_3;

    QList<int> load;

};

#endif // FINALPROJECT_H
