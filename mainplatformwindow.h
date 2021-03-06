#ifndef MAINPLATFORMWINDOW_H
#define MAINPLATFORMWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStringList>
#include <QSettings>
#include <QDebug>
#include<QMessageBox>
#include <QStyle>
#include<QFile>
#include <QTranslator>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSysInfo>
#include <QDesktopWidget>
#include <QFileInfoList>
#include <QDir>
#include <QLibrary>
#include <QTimer>
#include <QHostInfo>
#include <QListWidgetItem>
#include <QSignalMapper>
#include <QStandardItemModel>
#include <QDateTime>
#include <QDate>
#include <QScroller>

namespace Ui {
class mainplatformwindow;
}

class mainplatformwindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit mainplatformwindow(QWidget *parent = nullptr);
    void _init();
    void userRefresh();
    void flightRefresh();
    void ticketRefresh(int page=1);
    void fliarrangeRefresh(int page=1);
    void airportRefresh(int page =1);
    void compRefresh(int page=1);
    void adminRefresh();

    void annoucementRefresh(int page=1);

    QString ticketOrderStartQuery(QString ticketID);
    QString ticketOrderEndQuery(QString ticketID);

    ~mainplatformwindow();

  public slots:
    void on_horizontalSlider_2_valueChanged(int value);
  private slots:
    void on_listWidget_clicked(const QModelIndex &index);
    void on_actionAbout_Qt_triggered();
    void on_actionLog_out_triggered();
    void on_actionE_xit_triggered();
    void on_actionA_bout_triggered();
    //void on_listWidget_4_clicked(const QModelIndex &index);


    void on_listWidget_user_currentRowChanged(int currentRow);

    void on_listWidget_user_itemClicked(QListWidgetItem *item);

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_listWidget_3_itemClicked(QListWidgetItem *item);


    void updatetime();
    void updatest();
    //bool onTableDelBtnClicked(QString id);
    //bool onTableModBtnClicked(QString id);
    //bool onCompTableDelBtnClicked(QString id);
    //bool onCompTableModBtnClicked(QString id);
    void on_listWidget_5_itemClicked(QListWidgetItem *item);



    void on_horizontalSlider_valueChanged(int value);

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_4_clicked(const QModelIndex &index);

    void on_plainTextEdit_returnPressed();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();







    void on_pushButton_3_clicked();

    void on_plainTextEdit_2_returnPressed();

    void on_pushButton_4_clicked();

    void on_listWidget_6_itemClicked(QListWidgetItem *item);

    void on_tableView_5_clicked(const QModelIndex &index);

    void on_comboBox_activated(int index);



    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_listWidget_7_itemClicked(QListWidgetItem *item);

    void on_spinBox_valueChanged(int arg1);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_tableView_6_clicked(const QModelIndex &index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_2_activated(int index);

    void on_tableView_7_clicked(const QModelIndex &index);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_plainTextEdit_3_returnPressed();

    void on_horizontalSlider_3_valueChanged(int value);

    void on_fontComboBox_currentFontChanged(const QFont &f);


    void on_tableView_8_clicked(const QModelIndex &index);

    void on_listWidget_8_itemClicked(QListWidgetItem *item);

    void on_deliver_clicked();

    void on_listWidget_9_itemClicked(QListWidgetItem *item);

    void on_tableView_9_clicked(const QModelIndex &index);

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();


    void on_plainTextEdit_4_returnPressed();

    void on_horizontalSlider_4_valueChanged(int value);


    void on_horizontalSlider_5_valueChanged(int value);

    void on_pushButton_11_clicked();

    void on_plainTextEdit_5_returnPressed();

    void on_pushButton_12_clicked();



    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

private:
    Ui::mainplatformwindow *ui;
    //void mainplatformwindow::ExecAdd(QVariantMap userinfo)
};

class mycompmodel:public QSqlQueryModel {
        Q_OBJECT
  public:
    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
};
class myticketmodel:public QSqlQueryModel {
        Q_OBJECT
  public:
    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
};
class myusermodel:public QSqlQueryModel {
        Q_OBJECT
  public:
    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
};
class myflightmodel:public QSqlQueryModel {
        Q_OBJECT
  public:
    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
};
class myannouncementmodel:public QSqlQueryModel {
        Q_OBJECT
  public:
    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
};
class myadminmodel:public QSqlQueryModel {
        Q_OBJECT
  public:
    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
};
class myfliarrangemodel:public QSqlQueryModel {
        Q_OBJECT
  public:
    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
};

#endif // MAINPLATFORMWINDOW_H
