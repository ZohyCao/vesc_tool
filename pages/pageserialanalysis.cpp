#include "pageserialanalysis.h"
#include "ui_pageserialanalysis.h"

PageSerialAnalysis::PageSerialAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageSerialAnalysis)
{
    ui->setupUi(this);
    mVesc = 0;

    if (mSettings.contains("cmdText_1")) {
        ui->sendCmdText_1->setText(mSettings.value("cmdText_1").toString());
    }
    if (mSettings.contains("cmdText_2")) {
        ui->sendCmdText_2->setText(mSettings.value("cmdText_2").toString());
    }
    if (mSettings.contains("cmdText_3")) {
        ui->sendCmdText_3->setText(mSettings.value("cmdText_3").toString());
    }
    if (mSettings.contains("cmdText_4")) {
        ui->sendCmdText_4->setText(mSettings.value("cmdText_4").toString());
    }
    if (mSettings.contains("cmdText_5")) {
        ui->sendCmdText_5->setText(mSettings.value("cmdText_5").toString());
    }
    if (mSettings.contains("cmdText_6")) {
        ui->sendCmdText_6->setText(mSettings.value("cmdText_6").toString());
    }
    if (mSettings.contains("cmdText_7")) {
        ui->sendCmdText_7->setText(mSettings.value("cmdText_7").toString());
    }
    if (mSettings.contains("cmdText_8")) {
        ui->sendCmdText_8->setText(mSettings.value("cmdText_8").toString());
    }
    if (mSettings.contains("cmdText_9")) {
        ui->sendCmdText_9->setText(mSettings.value("cmdText_9").toString());
    }
    if (mSettings.contains("cmdText_10")) {
        ui->sendCmdText_10->setText(mSettings.value("cmdText_10").toString());
    }
    if (mSettings.contains("cmdText_11")) {
        ui->sendCmdText_11->setText(mSettings.value("cmdText_11").toString());
    }
    if (mSettings.contains("cmdText_12")) {
        ui->sendCmdText_12->setText(mSettings.value("cmdText_12").toString());
    }
    if (mSettings.contains("cmdText_13")) {
        ui->sendCmdText_13->setText(mSettings.value("cmdText_13").toString());
    }
    mTimer = new QTimer(this);
    mTimer->start(20);

    mSecondCounter = 0.0;
    mLastUpdateTime = 0;

    ui->generalPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //general plot with ten channals
    int graphIndex = 0;
    ui->generalPlot->addGraph();
    ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::blue));
    ui->generalPlot->graph(graphIndex)->setName("Channal 1");

}

VescInterface *PageSerialAnalysis::vesc() const
{
    return mVesc;
}

void PageSerialAnalysis::setVesc(VescInterface *vesc)
{
    mVesc = vesc;

    if (mVesc) {
          connect(mVesc->commands(),SIGNAL(monitorReceived(MONITOR_VALUES,uint)),
                  this,SLOT(monitorReceived(MONITOR_VALUES,uint)));
          connect(mVesc->commands(),SIGNAL(printCmdFeedback(QString)),
                  this, SLOT(printCmdFeedback(QString)));
    }
}

void PageSerialAnalysis::monitorReceived(MONITOR_VALUES values,unsigned mask){
    (void)mask;
    qint64 tNow = QDateTime::currentMSecsSinceEpoch();

    const int maxS = 500;

    double elapsed = double((tNow - mLastUpdateTime)) / 1000.0;
    if (elapsed > 1.0) {
        elapsed = 1.0;
    }

    mSecondCounter += elapsed;

    appendDoubleAndTrunc(&mSeconds, mSecondCounter, maxS);

    mLastUpdateTime = tNow;
}

void PageSerialAnalysis::appendDoubleAndTrunc(QVector<double> *vec, double num, int maxSize)
{
    vec->append(num);

    if(vec->size() > maxSize) {
        vec->remove(0, vec->size() - maxSize);
    }
}
PageSerialAnalysis::~PageSerialAnalysis()
{
    mSettings.setValue("cmdText_1",ui->sendCmdText_1->text());
    mSettings.setValue("cmdText_2",ui->sendCmdText_2->text());
    mSettings.setValue("cmdText_3",ui->sendCmdText_3->text());
    mSettings.setValue("cmdText_4",ui->sendCmdText_4->text());
    mSettings.setValue("cmdText_5",ui->sendCmdText_5->text());
    mSettings.setValue("cmdText_6",ui->sendCmdText_6->text());
    mSettings.setValue("cmdText_7",ui->sendCmdText_7->text());
    mSettings.setValue("cmdText_8",ui->sendCmdText_8->text());
    mSettings.setValue("cmdText_9",ui->sendCmdText_9->text());
    mSettings.setValue("cmdText_10",ui->sendCmdText_10->text());
    mSettings.setValue("cmdText_11",ui->sendCmdText_11->text());
    mSettings.setValue("cmdText_12",ui->sendCmdText_12->text());
    mSettings.setValue("cmdText_13",ui->sendCmdText_13->text());
    delete ui;
}

void PageSerialAnalysis::printCmdFeedback(QString str)
{
    ui->cmdBrowser->append(str);
}

void PageSerialAnalysis::on_cmdSendButton_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->cmdEdit->text());
        ui->cmdEdit->clear();
    }
}

void PageSerialAnalysis::on_cmdEdit_returnPressed()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->cmdEdit->text());
        ui->cmdEdit->clear();
    }
}

void PageSerialAnalysis::on_sendCmdButton_1_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_1->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_2_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_2->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_3_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_3->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_4_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_4->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_5_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_5->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_6_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_6->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_7_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_7->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_8_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_8->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_9_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_9->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_10_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_10->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_11_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_11->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_12_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_12->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_13_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_13->text());
    }
}
