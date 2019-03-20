#include "finalProject.h"
#include "ui_widget.h"
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QFileDialog>
#include<QUrl>
#include<QDir>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlTableModel>
#include<QMenu>
#include<QPainter>
#include<qmath.h>
#include<QShortcut>
#include<QMessageBox>
#include<QProgressBar>
#include<QProgressDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
    CreateSortCut();

    clearAll=new QAction(this);
    clearAll_1=new QAction(this);
    clearAll->setIcon(QIcon(":/icons/icons/clear.png"));
    clearAll->setText(tr("Clear"));
    clearAll_1->setText(tr("Clear Playlist"));
    QMenu *M=new QMenu(this);
    M->addAction(clearAll_1);
    clearAll->setMenu(M);

    mission1=new QAction(this);
    mission1->setIcon(QIcon(":/icons/icons/playlist.png"));
    mission1->setText(tr("Adding songs to Playlist"));
    QMenu *menu1=new QMenu(this);
    menu1->addAction(mission1);
    ui->pushButton_1->setMenu(menu1);

    mission2=new QAction(this);
    mission2->setIcon(QIcon(":/icons/icons/last1.png"));
    mission2->setText(tr("Previous Song"));

    mission3=new QAction(this);
    mission3->setIcon(QIcon(":/icons/icons/next1.png"));
    mission3->setText(tr("Next Song"));

    mission4=new QAction(this);
    mission4->setIcon(QIcon(":/icons/icons/play 1.png"));
    mission4->setText(tr("Play/Pause"));

    mission5=new QAction(this);
    mission5->setIcon(QIcon(":/icons/icons/mode.png"));
    mission5->setText(tr("Play Mode"));
    mission5_1=new QAction(this);
    mission5_1->setIcon(QIcon(":/icons/icons/repeatall.png"));
    mission5_1->setText(tr("Repeat All"));
    mission5_2=new QAction(this);
    mission5_2->setIcon(QIcon(":/icons/icons/shuffle.png"));
    mission5_2->setText(tr("Random"));
    mission5_3=new QAction(this);
    mission5_3->setIcon(QIcon(":/icons/icons/repeatone.png"));
    mission5_3->setText(tr("Repeat One"));
    QMenu *temp1=new QMenu(this);
    temp1->addAction(mission5_1);
    temp1->addAction(mission5_2);
    temp1->addAction(mission5_3);
    mission5->setMenu(temp1);

    mission6=new QAction(this);
    mission6->setIcon(QIcon(":/icons/icons/quit.png"));
    mission6->setText(tr("Quit"));

    QSqlQuery query;
    query.exec("select * from wallPaperData");
    query.next();
    QString FileName=query.value(0).toString();
    if(FileName=="")
    {
        pix.load(":/icons/icons/skin.png");
    }

    query.exec("select * from transparancyData");
    query.next();
    QString Values=query.value(0).toString();
    if(Values=="")
    {
        transparency=1;
    }
    setWindowOpacity(transparency);
    pal.setBrush(QPalette::Window,QBrush(pix.scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(pal);

    music=new QMediaPlayer(this);

    playlist_1=new QMediaPlaylist(this);
    playlist_1->setPlaybackMode(QMediaPlaylist::Loop);

    ui->pushButton_1->setToolTip(tr("Add Song"));
    ui->pushButton_2->setIconSize(QSize(48,48));
    ui->pushButton_2->setIcon(QIcon(":/icons/icons/play.png"));
    ui->pushButton_2->setToolTip(tr("Play/Pause"));
    ui->pushButton_3->setToolTip(tr("Next Song"));
    ui->pushButton_4->setToolTip(tr("Last Song"));
    ui->pushButton_5->setIconSize(QSize(32,32));
    ui->pushButton_5->setIcon(QIcon(":/icons/icons/volume1.png"));
    ui->pushButton_5->setToolTip(tr("Volume"));
    ui->pushButton_6->setIconSize(QSize(32,32));
    ui->pushButton_6->setIcon(QIcon(":/icons/icons/repeatall.png"));
    ui->pushButton_6->setToolTip(tr("Repeat All"));
    ui->pushButton_7->setToolTip(tr("PlayList"));
    ui->pushButton_8->setToolTip(tr("Minimize"));
    ui->pushButton_9->setToolTip(tr("Quit"));
    ui->horizontalSlider->setToolTip(tr("Progress Bar"));

    ui->verticalSlider->hide();
    ui->verticalSlider->setValue(100);

    ui->horizontalSlider->setValue(0);
    ui->stackedWidget->setCurrentIndex(0);

    mode_1=new QSqlTableModel(this);
    mode_1->setTable("dataSet1");
    mode_1->select();
    mode_2=new QSqlTableModel(this);
    mode_2->setTable("dataSet2");
    mode_2->select();
    mode_3=new QSqlTableModel(this);
    mode_3->setTable("dataSet3");
    mode_3->select();

    connect(music,&QMediaPlayer::positionChanged,this,&Widget::updatePosition);
    connect(music,&QMediaPlayer::durationChanged,this,&Widget::updateDuration);
    connect(ui->horizontalSlider,&QSlider::sliderMoved,music,&QMediaPlayer::setPosition);
    connect(playlist_1,&QMediaPlaylist::currentIndexChanged,this,&Widget::updatalistwidget);
    connect(mission1,&QAction::triggered,this,&Widget::action1_slot);
    connect(clearAll_1,&QAction::triggered,this,&Widget::ClearALL_1_slot);
    connect(mission2,&QAction::triggered,this,&Widget::action2_slot);
    connect(mission3,&QAction::triggered,this,&Widget::action3_slot);
    connect(mission4,&QAction::triggered,this,&Widget::action4_slot);
    connect(mission5_1,&QAction::triggered,this,&Widget::action5_1_slot);
    connect(mission5_2,&QAction::triggered,this,&Widget::action5_2_slot);
    connect(mission5_3,&QAction::triggered,this,&Widget::action5_3_slot);
    connect(mission6,&QAction::triggered,this,&Widget::action6_slot);
    connect(ui->verticalSlider,&QSlider::valueChanged,this,&Widget::changeVolume);
    connect(music,&QMediaPlayer::stateChanged,this,&Widget::music_stateChange);

    query.exec("select * from dataSet3");
    while(query.next())
    {
        QString Name=query.value(1).toString();
        QString FileName=query.value(2).toString();
        if(Name!=""&&FileName!="")
        {
        QListWidgetItem *item5=new QListWidgetItem;
       item5->setIcon(QIcon(":/icons/icons/music.png"));
       item5->setText(Name);
        ui->listWidget->addItem(item5);
        playlist_1->addMedia(QUrl::fromLocalFile(FileName));
        }

    }
    music->setPlaylist(playlist_1);
}


Widget::~Widget()//destructor
{
    delete ui;
}
static QString Time(qint64 time)//transform time from seconds to minutes
{
    qint64 seconds=time/1000;
    const qint64 minutes=seconds/60;
    seconds-=minutes*60;
    return QStringLiteral("%1:%2")
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'));
}

void Widget::updatePosition(qint64 position)//update playing position of the song
{
    ui->horizontalSlider->setValue(position);
    ui->label_2->setText(Time(position)+"/"+Time(music->duration()));
}
void Widget::updateDuration(qint64 duration)//update the time of the song
{

    ui->horizontalSlider->setRange(0,duration);
    ui->horizontalSlider->setEnabled(duration>0);
    ui->horizontalSlider->setPageStep(duration/10);
}
void Widget::pushbuttonstyle_3()//set the playlist icon
{

    ui->pushButton_7->setStyleSheet("QPushButton"
                                     "{"
                                     "	background-image: url(:/icons/icons/playlist.png);"
                                     "background-color: rgba(255, 255, 255,100);"
                                     "border-style:outset;"
                                     "border-color:rgba(255,255,255,0);"
                                     "border-radius:4px;"
                                     "}"
                                     "QPushButton:hover{"
                                     "background-color: rgb(255, 255, 255,100);"
                                     "}"
                                     "QPushButton:pressed{"
                                     " background-color: rgba(95, 95, 95,100);"
                                     "border-color:rgba(255,255,255,30);"
                                     "border-style:inset;"
                                     "color:rgba(0,0,0,100);"
                                    " }");
}

void Widget::on_pushButton_7_clicked()//open the playlist
{
    ui->stackedWidget->setCurrentIndex(2);
    pushbuttonstyle_3();
}

void Widget::ClearALL_1_slot()//clear the playlist
{
    int values=QMessageBox::information(this,tr("Clear PlayList"),tr("Clear PlayList?                              ."),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(values==QMessageBox::Yes)
    {
        QSqlQuery query;
    query.exec("select * from dataSet3");
    query.exec("delete from dataSet3");
    ui->listWidget->clear();
    playlist_1->clear();

    }
}

void Widget::action1_slot()//add music to the playlist in right click menu
{
  ui->stackedWidget->setCurrentIndex(2);
  pushbuttonstyle_3();
    QSqlQuery query;
    query.exec("select *from dataSet3");
    QStringList list = QFileDialog::getOpenFileNames(this,tr("All Files"),"D:/",tr("Audio files(*.mp3)"));
   if(!list.isEmpty())
   {
    QProgressDialog *progressdialog=new QProgressDialog(this);
    progressdialog->setWindowModality(Qt::WindowModal);
    progressdialog->setMinimumDuration(100);
    progressdialog->resize(500,200);
    progressdialog->setWindowTitle(tr("Add Song"));
    progressdialog->setLabelText(tr("Adding                             ."));
    progressdialog->setCancelButtonText(tr("Quit"));
    progressdialog->setRange(0,list.size()-1);
    int i=0;
    while(i<list.size())
    {
        QListWidgetItem *item=new QListWidgetItem;
        item->setIcon(QIcon(":/icons/icons/music.png"));
        QString path=QDir::toNativeSeparators(list.at(i));
        progressdialog->setValue(i);
        if(i==list.size()-1)
        {
            progressdialog->close();
        }
        if(progressdialog->wasCanceled())
            progressdialog->close();
        if(!path.isEmpty())
        {

            playlist_1->addMedia(QUrl::fromLocalFile(path));
            QString Name=path.split("\\").last();
            Name.remove(QString(".mp3"));
            item->setText(QString("%1").arg(Name));
            ui->listWidget->addItem(item);
            query.exec(QString("insert into dataSet3 values (%1,'%2','%3')").arg(qrand()%10000).arg(Name).arg(path));
        }
        i++;
      }
   }
}

void Widget::action6_slot()//close the window in right click menu
{
   close();
}
void Widget::action2_slot()//play previous song in right click menu
{

    if(music->playlist()==playlist_1)
    {
        int currentIndex=playlist_1->currentIndex();
        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
        if(--currentIndex<0)
        {
            currentIndex=0;
        }
        playlist_1->setCurrentIndex(currentIndex);
    }
     music->play();
}
void Widget::action3_slot()//play next song in right click menu
{

    if(music->playlist()==playlist_1)
    {
        int currentIndex=playlist_1->currentIndex();
        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
        if(++currentIndex==playlist_1->mediaCount())
        {
            currentIndex=0;

        }
        playlist_1->setCurrentIndex(currentIndex);
    }
    music->play();
}
void Widget::action4_slot()//pause and play in the right click menu
{
   if(music->state()==QMediaPlayer::PlayingState)
   {
       music->pause();
   }
   else
   {
       music->play();
   }

}
void Widget::action5_1_slot()//set repeat all play in the right click menu
{
    ui->pushButton_6->setIcon(QIcon(":/icons/icons/repeatall.png"));
    ui->pushButton_6->setToolTip(tr("Repeat All"));

    playlist_1->setPlaybackMode(QMediaPlaylist::Loop);

}
void Widget::action5_2_slot()//set shuffle play in the right click menu
{
    ui->pushButton_6->setIcon(QIcon(":/icons/icons/shuffle.png"));
    ui->pushButton_6->setToolTip(tr("Random"));

    playlist_1->setPlaybackMode(QMediaPlaylist::Random);
}
void Widget::action5_3_slot()//set repeat one in the right click menu
{
    ui->pushButton_6->setIcon(QIcon(":/icons/icons/repeatone.png"));
    ui->pushButton_6->setToolTip(tr("Repeat One"));

    playlist_1->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

}

void Widget::on_pushButton_2_clicked()//play/pause
{

   if(music->state()==QMediaPlayer::PlayingState)
    {
       ui->pushButton_2->setIcon(QIcon(":/icons/icons/pause.png"));
       ui->pushButton_2->setToolTip(tr("Pause"));
       music->pause();
    }
    else
    {
       ui->pushButton_2->setIcon(QIcon(":/icons/icons/play.png"));
       ui->pushButton_2->setToolTip(tr("Play"));
       music->play();
    }
}

void Widget::on_pushButton_3_clicked()//play next song
{

    if(music->playlist()==playlist_1)
    {
        int currentIndex=playlist_1->currentIndex();
        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
        if(++currentIndex==playlist_1->mediaCount())
        {
            currentIndex=0;

        }
        playlist_1->setCurrentIndex(currentIndex);

    }
    music->play();

}

void Widget::on_pushButton_4_clicked()//play previous song
{

    if(music->playlist()==playlist_1)
    {
        int currentIndex=playlist_1->currentIndex();
        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
        if(--currentIndex<0)
        {
            currentIndex=0;
        }
        playlist_1->setCurrentIndex(currentIndex);
    }
     music->play();
}

void Widget::updatalistwidget(int value)//update list Widget
{
    ui->listWidget->item(value)->setSelected(true);
}

void Widget::music_stateChange(QMediaPlayer::State state)//change the play state
{
    if(state==QMediaPlayer::PlayingState)
    {
        ui->pushButton_2->setIcon(QIcon(":/icons/icons/pause.png"));
        ui->pushButton_2->setToolTip(tr("Pause"));
    }
    else
    {
        ui->pushButton_2->setIcon(QIcon(":/icons/icons/play.png"));
        ui->pushButton_2->setToolTip(tr("Play"));
    }
}

void Widget::on_pushButton_6_clicked()//change play mode
{

    if(playlist_1->playbackMode()==QMediaPlaylist::Loop)
    {
        ui->pushButton_6->setIcon(QIcon(":/icons/icons/shuffle.png"));
        ui->pushButton_6->setToolTip(tr("Random"));
        playlist_1->setPlaybackMode(QMediaPlaylist::Random);
    }
    else if(playlist_1->playbackMode()==QMediaPlaylist::Random)
    {
        ui->pushButton_6->setIcon(QIcon(":/icons/icons/repeatone.png"));
        ui->pushButton_6->setToolTip(tr("Repeat One"));
        playlist_1->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }
    else if(playlist_1->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
    {
        ui->pushButton_6->setIcon(QIcon(":/icons/icons/repeatall.png"));
        ui->pushButton_6->setToolTip(tr("Repeat All"));
        playlist_1->setPlaybackMode(QMediaPlaylist::Loop);
    }
}

void Widget::on_listWidget_doubleClicked(const QModelIndex &index)//double click to play songs in playlist
{

       music->setPlaylist(playlist_1);
       playlist_1->setCurrentIndex( ui->listWidget->currentIndex().row());
       music->play();
}


void Widget::mousePressEvent(QMouseEvent *event)//the mouse click event
{
        offset=event->globalPos()-pos();
        event->accept();
        ui->verticalSlider->hide();
}
void Widget::mouseMoveEvent(QMouseEvent *event)//the mouse move event
{
 move(event->globalPos()-offset);
        event->accept();
}
void Widget::mouseReleaseEvent(QMouseEvent *event)//when release the mouse click
{

    offset=QPoint();
    event->accept();

}

void Widget::contextMenuEvent(QContextMenuEvent *event)//show the right click menu
{

    menu = new QMenu(this);

    menu->addAction(mission1);
    menu->addAction(mission2);
    menu->addAction(mission3);
    menu->addAction(mission4);
    menu->addAction(mission5);
    menu->addAction(clearAll);
    menu->addAction(mission6);
    menu->exec(QCursor::pos());

}

void Widget::on_pushButton_8_clicked()//minimize the window
{
    showMinimized();
}

void Widget::on_pushButton_9_clicked()//close the window
{
    close();
}

void Widget::on_pushButton_5_clicked()//hide the vertical-slider of volume
{


if(ui->verticalSlider->isHidden())
        ui->verticalSlider->show();
else
{
    ui->verticalSlider->hide();
}

}
void Widget::changeVolume(int values)//change volume
{
    if(values==0)
    {

        ui->pushButton_5->setIcon(QIcon(":/icons/icons/mute.png"));
    }
    else
    {
        ui->pushButton_5->setIcon(QIcon(":/icons/icons/volume1.png"));

    }
    music->setVolume(values);

}


void Widget::on_listWidget_customContextMenuRequested(const QPoint &pos)//right click on the song in the playlist
{
    QListWidgetItem *curItem2=ui->listWidget->itemAt(pos);
    if(curItem2==NULL)
    {
        return ;
    }
    QMenu *Menu2=new QMenu(this);
    QAction *Action1_3=new QAction(this);
    QAction *Action2_3=new QAction(this);
    Action1_3->setIcon(QIcon(":/icons/icons/play 1.png"));
    Action1_3->setText(tr("Play/Pause"));
    Action2_3->setIcon(QIcon(":/icons/icons/delete.png"));
    Action2_3->setText(tr("Remove from the Playlist"));
    Menu2->addAction(Action1_3);
    Menu2->addAction(Action2_3);
    connect(Action1_3,&QAction::triggered,this,&Widget::Action1_3_slot);
    connect(Action2_3,&QAction::triggered,this,&Widget::Action2_3_slot);
    Menu2->exec(QCursor::pos());
    delete Menu2;
    delete Action1_3;
    delete Action2_3;

}
void Widget::Action1_3_slot()//pause and play by right click on the song in the playlist
{

    if(music->playlist()==playlist_1)
    {


    if(ui->listWidget->item(playlist_1->currentIndex())->isSelected())
    {

        if(music->state()==QMediaPlayer::PlayingState)
        {
            music->pause();
        }
        else
        {
            music->play();
        }
    }
    else
    {

        playlist_1->setCurrentIndex(ui->listWidget->currentIndex().row());
        music->play();
    }

    }
    else
    {
        music->setPlaylist(playlist_1);
    playlist_1->setCurrentIndex(ui->listWidget->currentIndex().row());
    music->play();
    }

}

void Widget::Action2_3_slot()//delete song from the playlist by right click on the song in the playlist
{
    if(music->playlist()==playlist_1)
    {

        int Row=playlist_1->currentIndex();
        int row=ui->listWidget->currentIndex().row();
        if(row<Row)
        {
            int Position;
            if(music->state()==QMediaPlayer::PlayingState)
            {

                Position=music->position();
            }
            playlist_1->setCurrentIndex(0);
            ui->listWidget->takeItem(row);
            playlist_1->removeMedia(row,row);
            mode_3->setTable("dataSet3");
            mode_3->select();
            mode_3->removeRow(row);
            mode_3->submitAll();

            music->setPlaylist(playlist_1);
            playlist_1->setCurrentIndex(Row-1);
            music->setPosition(Position);
            ui->horizontalSlider->setValue(Position);
            music->play();
        }
        else
        {
            ui->listWidget->takeItem(row);
            playlist_1->removeMedia(row,row);
            mode_3->setTable("dataSet3");
            mode_3->select();
            mode_3->removeRow(row);
            mode_3->submitAll();

        }
    }
    else
    {
        int row=ui->listWidget->currentIndex().row();
        ui->listWidget->takeItem(row);
        playlist_1->removeMedia(row,row);
        mode_3->setTable("dataSet3");
        mode_3->select();
        mode_3->removeRow(row);
        mode_3->submitAll();
    }

}

void Widget::Data_slot(int row,int position,QMediaPlaylist *list,QMediaPlayer::State state,QMediaPlaylist::PlaybackMode model)
{

    playlist_1->setPlaybackMode(model);
    if(list==playlist_1)
    {
       playlist_1->setCurrentIndex(row);
       music->setPosition(position);
       if(state==QMediaPlayer::PlayingState)
       music->play();

    }

}

void Widget::CreateSortCut()//create short-cut for play/pause and previous/next song
{
    QShortcut *QUIT=new QShortcut(QKeySequence::Quit,this);
    connect(QUIT,&QShortcut::activated,QCoreApplication::quit);
    QShortcut *play=new QShortcut(Qt::Key_Space,this);
    connect(play,&QShortcut::activated,this,&Widget::action4_slot);
    QShortcut *next=new QShortcut(Qt::Key_Right,this);
    connect(next,&QShortcut::activated,this,&Widget::Next_slot);
    QShortcut *pre=new QShortcut(Qt::Key_Left,this);
    connect(pre,&QShortcut::activated,this,&Widget::Pre_slot);
}

void Widget::Next_slot()//play next song when press right arrow in the keyboard
{

    if(music->playlist()==playlist_1)
    {

        int currentIndex=playlist_1->currentIndex();
        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
        if(++currentIndex==playlist_1->mediaCount())
        {
            currentIndex=0;

        }
        playlist_1->setCurrentIndex(currentIndex);

    }
    music->play();
}

void Widget::Pre_slot()//play previous song when press left arrow in the keyboard
{
    if(music->playlist()==playlist_1)
    {
        int currentIndex=playlist_1->currentIndex();
        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
        if(--currentIndex<0)
        {
            currentIndex=0;
        }
        playlist_1->setCurrentIndex(currentIndex);
    }
     music->play();
}
