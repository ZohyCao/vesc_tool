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
    void timerSlot();
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

    void on_zoomHButton_toggled(bool checked);

    void on_zoomVButton_toggled(bool checked);

    void on_rescaleButton_clicked();

    void on_cmdClearButton_clicked();

    void on_plotStopButton_toggled(bool checked);

    void on_plotClearButton_clicked();

    void on_legendVisibleButton_toggled(bool checked);

//    void on_checkBox_0_clicked(bool checked);

//    void on_checkBox_1_clicked(bool checked);

//    void on_checkBox_2_clicked(bool checked);

//    void on_checkBox_3_clicked(bool checked);

//    void on_checkBox_4_clicked(bool checked);

//    void on_checkBox_5_clicked(bool checked);

//    void on_checkBox_6_clicked(bool checked);

//    void on_checkBox_7_clicked(bool checked);

//    void on_checkBox_8_clicked(bool checked);

//    void on_checkBox_9_clicked(bool checked);

    void on_pushButton_clicked();

    void on_sendCmdButton_14_clicked();

    void on_sendCmdButton_15_clicked();

    void on_channalCmdSendButton_1_clicked();

    void on_channalCmdSendButton_2_clicked();

    void on_channalCmdSendButton_3_clicked();

    void on_pageHelpButton_clicked();

private:
    Ui::PageSerialAnalysis *ui;
    QSettings mSettings;
    VescInterface *mVesc;
    QTimer *mTimer;


    QVector<double> mCH0;
    QVector<double> mCH1;
    QVector<double> mCH2;
    QVector<double> mCH3;
    QVector<double> mCH4;


    QVector<double> mCH5;
    // QVector<double> mNewV;
    // QVector<double> mWHY;
   QVector<double> mCH6;
   QVector<double> mCH7;
   QVector<double> mCH8;
   QVector<double> mCH9;

//    double mCH0;
//    double mCH1;
//    double mCH2;
//    double mCH3;
//    double mCH4;
//    double mCH5;
//    double mCH6;
//    double mCH7;
//    double mCH8;
//    double mCH9;

    QVector<double> mSeconds;

    double mSecondCounter;
    qint64 mLastUpdateTime;
    int mMaxPoints;

    bool mUpdateGeneralPlot;
    bool mUpdateButtonCheck;

    void appendDoubleAndTrunc(QVector<double> *vec, double num, int maxSize);
    void updateZoom();
    void updateMonitorLabel(MONITOR_VALUES values);
};

#endif // PAGESERIALANALYSIS_H
