#include <QApplication>
#include <QDebug>
#include <QStringList>
#include <QVariant>
#include <QMessageBox>
#include <QTableView>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("checkOn.db");
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database",
            "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    query.exec("create table student (name varchar(20) primary key, "
               "time int)");
    query.exec("insert into student values('Gental', 0)");
    query.exec("insert into student values('LiuTao', 1)");
    query.exec("insert into student values('WangHong', 2)");
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int numRows;

    // 创建数据库连接
    if(!createConnection()) return 1;
    // 使用QSqlQuery查询整张表
    QSqlQuery query;
    query.exec("select * from student");
    while(query.next())
    {
        qDebug() << query.value(0).toString() << query.value(1).toInt();
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from student");
    model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("名字"));
    model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("签到次数"));

    QTableView *view = new QTableView();
    view->setModel(model);
    view->show();

    return a.exec();

}

