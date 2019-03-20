#ifndef CONNECTION_H
#define CONNECTION_H
#include<QSqlDatabase>
#include<QSqlQuery>
static bool CreatConnection()
{

QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("music.db");
if(!db.open())
{

    return false;
}
QSqlQuery query;
query.exec(QString("create table dataSet1 (id int primary key,MusicName varchar,FileName varchar,biaoji int)"));
query.exec(QString("create table dataSet2 (id int primary key,MusicName varchar,FileName varchar)"));
query.exec(QString("create table dataSet3 (id int primary key,MusicName varchar,FileName varchar)"));
query.exec(QString("create table wallPaperData (FileName varchar primary key)"));
query.exec(QString("create table transparancyData (TRA double primary key)"));
return true;
}

#endif // CONNECTION_H
