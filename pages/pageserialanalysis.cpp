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
    if (mSettings.contains("cmdText_14")) {
        ui->sendCmdText_14->setText(mSettings.value("cmdText_14").toString());
    }
    if (mSettings.contains("cmdText_15")) {
        ui->sendCmdText_15->setText(mSettings.value("cmdText_15").toString());
    }
    if (mSettings.contains("channalCmdText_1")) {
        ui->channalCmdText_1->setText(mSettings.value("channalCmdText_1").toString());
    }
    if (mSettings.contains("channalCmdText_2")) {
        ui->channalCmdText_2->setText(mSettings.value("channalCmdText_2").toString());
    }
    if (mSettings.contains("channalCmdText_3")) {
        ui->channalCmdText_3->setText(mSettings.value("channalCmdText_3").toString());
    }
    mTimer = new QTimer(this);
    mTimer->start(20);

    mSecondCounter = 0.0;
    mLastUpdateTime = 0;
    mMaxPoints = 1000;

    mUpdateGeneralPlot = false;
    mUpdateButtonCheck = true;

    ui->generalPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //general plot with ten channals
    QFont legendFont =font();
    legendFont.setPointSize(9);

    ui->generalPlot->legend->setVisible(true);
    ui->generalPlot->legend->setFont(legendFont);
    ui->generalPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->generalPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    ui->generalPlot->xAxis->setLabel("Second (s)");

    connect(mTimer, SIGNAL(timeout()),
            this, SLOT(timerSlot()));
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
    //qDebug()<<"received"<<values.ch0<<"  "<<values.ch1;
    (void)mask;
    updateMonitorLabel(values);
   // const int maxS = 1000;

   appendDoubleAndTrunc(&mCH0,values.ch0,mMaxPoints);
   //mCH1.append(values.ch0);
   appendDoubleAndTrunc(&mCH1,values.ch1,mMaxPoints);
   appendDoubleAndTrunc(&mCH2,values.ch2,mMaxPoints);
   appendDoubleAndTrunc(&mCH3,values.ch3,mMaxPoints);
   appendDoubleAndTrunc(&mCH4,values.ch4,mMaxPoints);
   appendDoubleAndTrunc(&mCH5,values.ch5,mMaxPoints);
   appendDoubleAndTrunc(&mCH6,values.ch6,mMaxPoints);
   appendDoubleAndTrunc(&mCH7,values.ch7,mMaxPoints);
   appendDoubleAndTrunc(&mCH8,values.ch8,mMaxPoints);
   appendDoubleAndTrunc(&mCH9,values.ch9,mMaxPoints);

    qint64 tNow = QDateTime::currentMSecsSinceEpoch();

    double elapsed = double((tNow - mLastUpdateTime)) / 1000.0;
    if (elapsed > 1.0) {
        elapsed = 1.0;
    }

    mSecondCounter += elapsed;

    appendDoubleAndTrunc(&mSeconds, mSecondCounter, mMaxPoints);

    mLastUpdateTime = tNow;

    mUpdateGeneralPlot = true;
}

void PageSerialAnalysis::appendDoubleAndTrunc(QVector<double> *vec, double num, int maxSize)
{
    vec->append(num);

    if(vec->size() > maxSize) {
        vec->remove(0, vec->size() - maxSize);
    }
}

void PageSerialAnalysis::timerSlot(){
    if(mUpdateButtonCheck&&mUpdateGeneralPlot){
        int dataSize = mSeconds.size();

        QVector<double> xAxis(dataSize);
        for(int i=0;i<mSeconds.size();i++){
            xAxis[i] = mSeconds[i];
        }
        ui->generalPlot->clearGraphs();

        int graphIndex = -1;

        if(ui->checkBox_0->isChecked()){
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::red));
        ui->generalPlot->graph(graphIndex)->setName(tr("CH-0"));
        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH0);
        }
        if(ui->checkBox_1->isChecked()){
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::blue));
        ui->generalPlot->graph(graphIndex)->setName("CH-1");
        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH1);
        }
        if(ui->checkBox_2->isChecked()){
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::magenta));
        ui->generalPlot->graph(graphIndex)->setName("CH-2");
        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH2);
}
        if(ui->checkBox_3->isChecked()){
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::green));
        ui->generalPlot->graph(graphIndex)->setName("CH-3");
        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH3);
}
        if(ui->checkBox_4->isChecked()){
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::cyan));
        ui->generalPlot->graph(graphIndex)->setName("CH-4");
        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH4);
}
        if(ui->checkBox_5->isChecked()){
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkGreen));
        ui->generalPlot->graph(graphIndex)->setName("CH-5");
        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH5);
}
        if(ui->checkBox_6->isChecked()){
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkRed));
        ui->generalPlot->graph(graphIndex)->setName("CH-6");
        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH6);
}
        if(ui->checkBox_7->isChecked()){
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::black));
        ui->generalPlot->graph(graphIndex)->setName("CH-7");
        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH7);
}
        if(ui->checkBox_8->isChecked()){
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkYellow));
        ui->generalPlot->graph(graphIndex)->setName("CH-8");
        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH8);
}
        if(ui->checkBox_9->isChecked()){
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkMagenta));
        ui->generalPlot->graph(graphIndex)->setName("CH-9");
        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH9);
}

        if(ui->autoScaleButton->isChecked()){
            ui->generalPlot->rescaleAxes();
        }
        ui->generalPlot->replot();
        mUpdateGeneralPlot = false;
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
    mSettings.setValue("cmdText_14",ui->sendCmdText_14->text());
    mSettings.setValue("cmdText_15",ui->sendCmdText_15->text());
    mSettings.setValue("channalCmdText_1",ui->channalCmdText_1->text());
    mSettings.setValue("channalCmdText_2",ui->channalCmdText_2->text());
    mSettings.setValue("channalCmdText_3",ui->channalCmdText_3->text());
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

void PageSerialAnalysis::updateZoom(){
    Qt::Orientations plotOrientations = Qt::Orientations(
            ((ui->zoomHButton->isChecked() ? Qt::Horizontal : 0) |
             (ui->zoomVButton->isChecked() ? Qt::Vertical : 0)));
    ui->generalPlot->axisRect()->setRangeZoom(plotOrientations);
}

void PageSerialAnalysis::updateMonitorLabel(MONITOR_VALUES values){
    ui->CH0_dataLabel->setText(QString("%1").arg(values.ch0));
    ui->CH1_dataLabel->setText(QString("%1").arg(values.ch1));
    ui->CH2_dataLabel->setText(QString("%1").arg(values.ch2));
    ui->CH3_dataLabel->setText(QString("%1").arg(values.ch3));
    ui->CH4_dataLabel->setText(QString("%1").arg(values.ch4));
    ui->CH5_dataLabel->setText(QString("%1").arg(values.ch5));
    ui->CH6_dataLabel->setText(QString("%1").arg(values.ch6));
    ui->CH7_dataLabel->setText(QString("%1").arg(values.ch7));
    ui->CH8_dataLabel->setText(QString("%1").arg(values.ch8));
    ui->CH9_dataLabel->setText(QString("%1").arg(values.ch9));

}

void PageSerialAnalysis::on_zoomHButton_toggled(bool checked)
{
    (void)checked;
    updateZoom();
}

void PageSerialAnalysis::on_zoomVButton_toggled(bool checked)
{
    (void)checked;
    updateZoom();
}

void PageSerialAnalysis::on_rescaleButton_clicked()
{
    ui->generalPlot->rescaleAxes();
}

void PageSerialAnalysis::on_cmdClearButton_clicked()
{
    ui->cmdBrowser->clear();
}

void PageSerialAnalysis::on_plotStopButton_toggled(bool checked)
{
    mUpdateButtonCheck = checked;
}

void PageSerialAnalysis::on_plotClearButton_clicked()
{
    mSecondCounter = 0.0;
    mLastUpdateTime = 0;
    mCH0.clear();
    mCH1.clear();
    mCH2.clear();
    mCH3.clear();
    mCH4.clear();
    mCH5.clear();
    mCH6.clear();
    mCH7.clear();
    mCH8.clear();
    mCH9.clear();
    ui->generalPlot->replot();
}

void PageSerialAnalysis::on_legendVisibleButton_toggled(bool checked)
{
    ui->generalPlot->legend->setVisible(checked);
    ui->generalPlot->replot();
}

void PageSerialAnalysis::on_pushButton_clicked()
{
    mMaxPoints = ui->maxPointsSpinBox->value();
}

void PageSerialAnalysis::on_sendCmdButton_14_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_14->text());
    }
}

void PageSerialAnalysis::on_sendCmdButton_15_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->sendCmdText_15->text());
    }
}

void PageSerialAnalysis::on_channalCmdSendButton_1_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->channalCmdText_1->text());
    }
}

void PageSerialAnalysis::on_channalCmdSendButton_2_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->channalCmdText_2->text());
    }
}

void PageSerialAnalysis::on_channalCmdSendButton_3_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd(ui->channalCmdText_3->text());
    }
}

void PageSerialAnalysis::on_pageHelpButton_clicked()
{
    if(mVesc){
        mVesc->commands()->sendSerialCmd("help");
    }
}
