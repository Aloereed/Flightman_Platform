#include "search_result.h"
#include "ui_search_result.h"

search_result::search_result(QSqlTableModel *search_input,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search_result)
{
    ui->setupUi(this);
    search = search_input;
    ui->tableView->setModel(search);
}

search_result::~search_result()
{
    delete ui;
}

void search_result::on_pushButton_clicked()
{
    QProgressDialog dialog(tr("Returning to the search window"),tr("cancel"), 0, 3000, this);
    dialog.setWindowTitle(tr("process"));
    dialog.setWindowModality(Qt::WindowModal);
    dialog.show();
    for(int k = 0; k < 3000; k++)
    {
        dialog.setValue(k);
        QCoreApplication::processEvents();
        if(dialog.wasCanceled())
        {
            break;
        }
    }
    dialog.setValue(3000);
   this->close();

}

void search_result::on_submit_clicked()
{
#ifdef Q_OS_ANDROID
    QSqlQuery transaction;
    transaction.exec("start transaction");
#else
     search->database().transaction();
#endif
    if(search->submitAll()){
#ifdef Q_OS_ANDROID
        transaction.exec("commit");
#else
        search->database().commit();
#endif
    }
    else{
#ifdef Q_OS_ANDROID
        transaction.exec("rollback");
#else
        search->database().rollback();
#endif
        QMessageBox::warning(this,tr("submission failed"),tr("error:%1").arg(search->lastError().text()));
    }
}

void search_result::on_retract_clicked()
{
    search->revertAll();
}
