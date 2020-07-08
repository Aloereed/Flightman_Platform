#include "seat_selection.h"
#include "ui_seat_selection.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QScroller>


seat_selection::seat_selection(QWidget *parent,QString flightID,QString classType,QString dep_date
                               ,QString UserID,QString order_start,QString order_end) :
    QWidget(parent),
    ui(new Ui::seat_selection)
{
    ui->setupUi(this);
    QScroller::grabGesture(ui->tableWidget_seats, QScroller::TouchGesture);
    ui->label_hint->setText(tr("Please click on the cell to select your seat."));
    ui->label_colorhint1->setText(tr("white : available"));
    ui->label_colorhint2->setText(tr("gray : NOT available"));
    ui->pushButton_Cancel->setText(tr("Cancel"));

    //赋值
    this->UserID = UserID;
    this->flightID = flightID;
    this->classType = classType;
    this->dep_date = dep_date;
    this->order_start = order_start;
    this->order_end = order_end;
    this->flightType = flightTypeQuery(flightID); //0是单通道，1是双通道
    this->business_No = businessNoQuery(flightID);
    this->economy_No = economyNoQuery(flightID);

    int MaxBuisRows = this->business_No.toInt();
    int MaxEconRows = this->economy_No.toInt();

    ui->label_hintBuis->setText(tr("Business Class Row :"));
    ui->label_NoBuis->setText(" 1—"+QString("%1").arg(MaxBuisRows));

    ui->label_hintEcon->setText(tr("Economy Class Row :"));
    ui->label_NoEcon->setText(" "+QString("%1").arg(MaxBuisRows+1)+"—"+QString("%1").arg(MaxBuisRows+MaxEconRows));

    ui->label_hintSeat->setText(tr("Your seat :"));
    ui->label_seat->setText(classType=="0"?"Business":"Economy");

    ui->tableWidget_seats->setRowCount(this->business_No.toInt()+this->economy_No.toInt());
    int colum = this->flightType=="0"?7:11;
    ui->tableWidget_seats->setColumnCount(colum);

    this->tableHeadersSet(this->flightType);
    this->tableContentsSet(this->flightType,MaxBuisRows,MaxEconRows,this->classType);
    ui->tableWidget_seats->resizeColumnsToContents();

    this->ui->tableWidget_seats->setEditTriggers(QAbstractItemView::NoEditTriggers);


    //    QTableWidgetItem *columnHeaderItem0 = ui->tableWidget_seats->horizontalHeaderItem(0);
    //    columnHeaderItem0->setFont(QFont("Helvetica")); //设置字体
    //    columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色
    //    columnHeaderItem0->setTextColor(QColor(200,111,30)); //设置文字颜色



}

seat_selection::~seat_selection()
{
    delete ui;
}

QString seat_selection::flightTypeQuery(QString flightID)
{
    QString flightType = "1";
    QString sql = QString("SELECT type FROM seat WHERE flight_id='%1'").arg(flightID);
    QSqlQuery *query = new QSqlQuery();
    query->exec(sql);
    if(query->next()){
        flightType = query->value(0).toString();
    }
    return flightType;
}

QString seat_selection::businessNoQuery(QString flightID)
{
    QString businessNo = "10";
    QString sql = QString("SELECT `business_No.` FROM seat WHERE flight_id='%1'").arg(flightID);
    QSqlQuery *query = new QSqlQuery();
    query->exec(sql);
    if(query->next()){
        businessNo = query->value(0).toString();
    }
    return businessNo;
}

QString seat_selection::economyNoQuery(QString flightID)
{
    QString economyNo = "30";
    QString sql = QString("SELECT `economy_No.` FROM seat WHERE flight_id='%1'").arg(flightID);
    QSqlQuery *query = new QSqlQuery();
    query->exec(sql);
    if(query->next()){
        economyNo = query->value(0).toString();
    }
    return economyNo;
}

QString seat_selection::ComputeSeatID(int row, int col, QString flightType)
{
    QString rowID = QString("%1").arg(row+1);
    QString colID = "";
    if(flightType=="0"){ //单通道
        if(col==0){
            colID = "A";
        }else if(col==1){
            colID = "B";
        }
        else if(col==2){
            colID = "C";
        }else if(col==4){
            colID = "J";
        }else if(col==5){
            colID = "K";
        }else if(col==6){
            colID = "L";
        }
    }else{ //双通道
        if(col==0){
            colID = "A";
        }else if(col==1){
            colID = "B";
        }
        else if(col==2){
            colID = "C";
        }else if(col==4){
            colID = "D";
        }else if(col==5){
            colID = "E";
        }else if(col==6){
            colID = "G";
        }else if(col==8){
            colID = "H";
        }else if(col==9){
            colID = "J";
        }else if(col==10){
            colID = "K";
        }
    }
    return rowID+colID;
}

bool seat_selection::IsSeatInUsage(QString flightID, QString start_order, QString dep_date, QString seatID)
{
    QString sql = QString("SELECT passengerID FROM seat_arrangement WHERE flight_ID='%1' "
                          "AND `order`=%2 AND departure_date='%3' AND seat_id='%4'")
                      .arg(flightID).arg(start_order).arg(dep_date).arg(seatID);
    QSqlQuery *query = new QSqlQuery();
    query->exec(sql);
    if(query->first()){//查询成功
        if(query->value(0).toString()==""?1:0){//查询到的passengerID为空，说明无人使用
            return false;
        }
        return true;
    }
    //查询失败，默认被占用
    return true;
}

QHash<QString, QString> seat_selection::SeatsInfo(QString flightID, QString order_start, QString dep_date)
{
    QHash<QString,QString> hash_seatidTopassengerid;
    QString sql = QString("SELECT seat_id,passengerID FROM seat_arrangement WHERE flight_ID='%1' AND `order`=%2 AND "
                          "departure_date='%3'")
                      .arg(flightID).arg(order_start).arg(dep_date);
    QSqlQuery *query = new QSqlQuery();
    if(query->exec(sql)){ //成功执行
        while(query->next()){
            hash_seatidTopassengerid.insert(query->value(0).toString(),query->value(1).toString());
        }
    }
    hash_seatidTopassengerid.insert("0","-1");//默认存量
    return hash_seatidTopassengerid;
}

void seat_selection::on_pushButton_Cancel_clicked()
{
    this->close();
}

void seat_selection::tableHeadersSet(QString flightType)
{
    QStringList headers;
    if(flightType=="0"){//表示为单通道
        headers << QStringLiteral("A") << QStringLiteral("B") << QStringLiteral("C")
                <<QStringLiteral("——")<<QStringLiteral("J")<<QStringLiteral("K")
                <<QStringLiteral("L");
    }else{  //表示为双通道
        headers << QStringLiteral("A") << QStringLiteral("B") << QStringLiteral("C")<<QStringLiteral("——")
                <<QStringLiteral("D")<<QStringLiteral("E")<<QStringLiteral("G")<<QStringLiteral("——")
                <<QStringLiteral("H")<<QStringLiteral("J")<<QStringLiteral("K");
    }
    ui->tableWidget_seats->setHorizontalHeaderLabels(headers);
    return;
}

void seat_selection::tableContentsSet(QString flightType, int busiNo, int econNo, QString classType)
{
    int cols = flightType=="0"?7:11;
    int rows = busiNo + econNo;
    int classTypeInt = classType.toUInt();
    QString seatID = "";
    QString seatUser = "";
    QHash<QString,QString> hash_seatidTopassengerid = this->SeatsInfo(this->flightID,this->order_start,this->dep_date);
    if(cols==7){ //说明本次航班是单通道的
        if(classTypeInt == 0){ //说明用户要选择单通道的公务舱
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    if(j==3) continue; //位于过道
                    if(i<busiNo && (j==1 || j==5)) continue; //位于公务舱两个位置的间隔
                    seatID = this->ComputeSeatID(i,j,flightType);
                    if(hash_seatidTopassengerid.find(seatID)!=hash_seatidTopassengerid.end())
                        seatUser = hash_seatidTopassengerid.find(seatID).value();
                    else seatUser = "-1";
                    QTableWidgetItem *item = new QTableWidgetItem("💺 "+seatID);
                    if(i>=business_No.toInt() || (seatUser!="" && seatUser!="-1")){
                        item->setBackgroundColor(QColor(Qt::lightGray));
                    }
                    ui->tableWidget_seats->setItem(i,j,item);
                }
            }
        }else{//说明用户要选择单通道的经济舱
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    if(j==3) continue; //位于过道
                    if(i<busiNo && (j==1 || j==5)) continue; //位于公务舱两个位置的间隔
                    seatID = this->ComputeSeatID(i,j,flightType);
                    if(hash_seatidTopassengerid.find(seatID)!=hash_seatidTopassengerid.end())
                        seatUser = hash_seatidTopassengerid.find(seatID).value();
                    else seatUser = "-1";
                    QTableWidgetItem *item = new QTableWidgetItem("💺 "+seatID);
                    if(i<business_No.toInt() || (seatUser!="" && seatUser!="-1")){
                        item->setBackgroundColor(QColor(Qt::lightGray));
                    }
                    ui->tableWidget_seats->setItem(i,j, item);
                }
            }
        }
    }else{ //本次航班是双通道的
        if(classTypeInt == 0){//说明用户要选择双通道的公务舱
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    if(j==3 || j==7) continue;
                    if(i<busiNo && (j==1 || j==5 || j==9)) continue;
                    seatID = this->ComputeSeatID(i,j,flightType);
                    if(hash_seatidTopassengerid.find(seatID)!=hash_seatidTopassengerid.end())
                        seatUser = hash_seatidTopassengerid.find(seatID).value();
                    else seatUser = "-1";
                    QTableWidgetItem *item = new QTableWidgetItem("💺 "+seatID);
                    if(i>=business_No.toInt() || (seatUser!="" && seatUser!="-1")){
                        item->setBackgroundColor(QColor(Qt::lightGray));
                    }
                    ui->tableWidget_seats->setItem(i,j, item);
                }
            }
        }else{
            for(int i=0;i<rows;i++){//说明用户要选择双通道的经济舱
                for(int j=0;j<cols;j++){
                    if(j==3 || j==7) continue;
                    if(i<busiNo && (j==1 || j==5 || j==9)) continue;
                    seatID = this->ComputeSeatID(i,j,flightType);
                    if(hash_seatidTopassengerid.find(seatID)!=hash_seatidTopassengerid.end())
                        seatUser = hash_seatidTopassengerid.find(seatID).value();
                    else seatUser = "-1";
                    QTableWidgetItem *item = new QTableWidgetItem("💺 "+seatID);
                    if(i<business_No.toInt() || (seatUser!="" && seatUser!="-1")){//该座位被人使用或者该座位不属于用户对应的舱位
                        item->setBackgroundColor(QColor(Qt::lightGray));
                    }
                    ui->tableWidget_seats->setItem(i,j,item);
                }
            }
        }
    }
    //tableWidget->setItem(0,1,new QTableWidgetItem(QIcon(":/Image/IED.png"), "Jan's month"));
}

void seat_selection::on_tableWidget_seats_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    if(this->classType=="1"){ //说明座位应该选经济舱，所以前排的位置不能选
        if(row < this->business_No.toInt()){ //说明选到公务舱去了，选的位置不对，本次不允许选择
            QMessageBox::information(this,tr("Hint:"),tr("You can only choose the economy class seat. Please choose another one."));
            return;
        }
    }else{ //说明座位应该选经济舱，所以后排的位置不能选
        if(row >= this->business_No.toInt()){ //说明选到经济舱去了，选的位置不对，本次不允许选择
            QMessageBox::information(this,tr("Hint:"),tr("You can only choose the business class seat. Please choose another one."));
            return;
        }
    }
    //通过则说明，舱位没有选错，现在检查选择的位置是否已被其他人所选择了
    QStringList strList = item->text().split(" ");
    int size = strList.length();
    QString seatID = strList[size-1];
    if(item->backgroundColor()==QColor(Qt::lightGray)){
        //说明座位正在被使用，此次选位非法
        QMessageBox::information(this,tr("Hint:"),tr("The seat has been selected. Please choose another one."));
        return;
    }
    QString sql = QString("CALL SeatsSelection('%1',%2,%3,'%4','%5','%6')")
              .arg(flightID).arg(order_start)
              .arg(order_end).arg(dep_date)
              .arg(seatID).arg(UserID);
    QSqlQuery query;
    if(query.exec(sql)){
        QMessageBox::information(this,tr("Hint"),tr("Success!"));
        this->close();
        return;
    }
    qDebug()<<"座位选择完毕"<<endl;
    return;
}
