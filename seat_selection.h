#ifndef SEAT_SELECTION_H
#define SEAT_SELECTION_H

#include <QWidget>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QHash>

namespace Ui {
class seat_selection;
}

class seat_selection : public QWidget {
    Q_OBJECT

  public:
    explicit seat_selection(QWidget *parent = nullptr,QString flightID="",QString classType="1",QString dep_date=""
                            ,QString UserID="",QString order_start="0",QString order_end="-1");
    ~seat_selection();

    QString flightTypeQuery(QString flightID);
    QString businessNoQuery(QString flightID);
    QString economyNoQuery(QString flightID);
    QString ComputeSeatID(int row,int col,QString flightType);
    bool IsSeatInUsage(QString flightID,QString start_order,QString dep_date,QString seatID);
    QHash<QString,QString> SeatsInfo(QString flightID,QString order_start,QString dep_date);

    QString getflightID() {
        return this->flightID;
    }
    QString getorder_start() {
        return this->order_start;
    }
    QString getorder_end() {
        return this->order_end;
    }
    QString getdep_date() {
        return this->dep_date;
    }


  private slots:
    void on_pushButton_Cancel_clicked();

    void on_tableWidget_seats_itemClicked(QTableWidgetItem *item);

  private:
    Ui::seat_selection *ui;
    QString flightID;
    QString flightType;
    QString business_No;
    QString economy_No;
    QString classType;
    QString dep_date;// 出发时间
    QString UserID; //将用户与对应座位绑定
    QString order_start;
    QString order_end;
    //flightID、flightType、busiNo、econNo将决定整个座位区域
    //classType 表示用户可以选择的座位区域
    //flightID与后面四项确定哪些座位将被该用户占据

    void tableHeadersSet(QString flightType);
    void tableContentsSet(QString flightType,int busiNo,int econNo,QString classType);
};

//class MySeatTable:public QTableWidget{
//public:
//    QVariant data(,)
//};

//class CancelledOrderModel:public QSqlQueryModel{
//public:
//    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
//};

#endif // SEAT_SELECTION_H
