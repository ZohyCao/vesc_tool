#ifndef PAGESERIALANALYSIS_H
#define PAGESERIALANALYSIS_H

#include <QWidget>
#include <QVector>
#include <QTimer>
#include "vescinterface.h"

namespace Ui {
class PageSerialAnalysis;
}

class PageSerialAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit PageSerialAnalysis(QWidget *parent = 0);
    ~PageSerialAnalysis();

    VescInterface *vesc() const;
    void setVesc(VescInterface *vesc);

private slots:
    void monitorReceived(MONITOR_VALUES values,unsigned int mask);
    void printCmdFeedback(QString str);
    void on_cmdSendButton_clicked();

    void on_cmdEdit_returnPressed();

    void on_sendCmdButton_1_clicked();

    void on_sendCmdButton_2_clicked();

    void on_sendCmdButton_3_clicked();

    void on_sendCmdButton_4_clicked();

    void on_sendCmdButton_5_clicked();

    void on_sendCmdButton_6_clicked();

    void on_sendCmdButton_7_clicked();

    void on_sendCmdButton_8_clicked();

    void on_sendCmdButton_9_clicked();

    void on_sendCmdButton_10_clicked();

    void on_sendCmdButton_11_clicked();

    void on_sendCmdButton_12_clicked();

    void on_sendCmdButton_13_clicked();

private:
    Ui::PageSerialAnalysis *ui;
    QSettings mSettings;
    VescInterface *mVesc;
    QTimer *mTimer;

    QVector<double> mSeconds;
    double mSecondCounter;
    qint64 mLastUpdateTime;

    void appendDoubleAndTrunc(QVector<double> *vec, double num, int maxSize);
};

#endif // PAGESERIALANALYSIS_H
