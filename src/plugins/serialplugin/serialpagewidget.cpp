#include "serialpagewidget.h"
#include "ui_serialpagewidget.h"
#include "serialcombobox.h"

#include <QDebug>


SerialPageWidget::SerialPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialPageWidget)
{
    ui->setupUi(this);

    m_baudRates = QSerialPortInfo::standardBaudRates();
    foreach(qint32 baud, m_baudRates){
        ui->baudComboBox->addItem(QString::number(baud));
    }

    ui->databitComboBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->databitComboBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->databitComboBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->databitComboBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->databitComboBox->setCurrentIndex(3);

    ui->paraityComboBox->addItem(tr("None"), QSerialPort::NoParity);
    ui->paraityComboBox->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->paraityComboBox->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->paraityComboBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->paraityComboBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->stopbitComboBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    ui->stopbitComboBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
    ui->stopbitComboBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    ui->editRecv->setReadOnly(true);

    m_sendCnt = 0;
    m_recvCnt = 0;
    ui->labelSendcnt->setText(QString::number(m_sendCnt));
    ui->labelRecvCnt->setText(QString::number(m_recvCnt));

    ui->btnOpen->setText("Open");
    ui->labelOpenState->setPixmap(QPixmap(":/icon/image/state_close.png"));

    //signal
    connect(ui->serialportComboBox, &SerialComboBox::opened, this, &SerialPageWidget::updatePortList);
    connect(ui->btnOpen,&QPushButton::clicked,this,&SerialPageWidget::openSerial);
    connect(ui->btnClearRecv,&QPushButton::clicked,this,&SerialPageWidget::clearRecv);
    connect(ui->btnClearSend,&QPushButton::clicked,this,&SerialPageWidget::clearSend);
    connect(ui->btnSend,&QPushButton::clicked,this,&SerialPageWidget::sendInput);

    //init color from saved settings
    SerialPluginSettings *settings = new SerialPluginSettings;

    Utils::QtcSettings *s = ExtensionSystem::PluginManager::settings();
    settings->fromSettings(s);
    applySettings(settings);

}

SerialPageWidget::~SerialPageWidget()
{
    delete ui;
}

void SerialPageWidget::applySettings(SerialPluginSettings *settings)
{
    QString backColor = settings->m_backColor;
    QString foreColor = settings->m_foreColor;
    ui->editRecv->setStyleSheet("QPlainTextEdit{background-color:"+backColor+ "; color:" + foreColor + ";}");
}

void SerialPageWidget::sendInput()
{
    qDebug()<<" send data";

    if(!m_serialContrl){
        qDebug()<<" serial control null";
        showInfo("serial control not valid");
        return;
    }

    if(!m_serialContrl->isRunning()){
        showInfo("pls open serial port first");
        return;
    }

    m_sendCnt = m_serialContrl->writeData(ui->editSend->toPlainText().toUtf8());

    ui->labelSendcnt->setText(QString::number(m_sendCnt));
}

void SerialPageWidget::openSerial()
{

    QString portName = ui->serialportComboBox->currentText();

    if(portName.isEmpty()){
        showInfo("No Serial port available");
        return;
    }

    qint32 baud = ui->baudComboBox->currentText().toInt();

    SerialControlUtils::Settings setting;

    setting.portName = portName;
    setting.baudRate = baud;

    setting.stopBits = static_cast<QSerialPort::StopBits>(
                    ui->stopbitComboBox->itemData(ui->stopbitComboBox->currentIndex()).toInt());
    setting.parity = static_cast<QSerialPort::Parity>(
                    ui->paraityComboBox->itemData(ui->paraityComboBox->currentIndex()).toInt());
    setting.dataBits = static_cast<QSerialPort::DataBits>(
                    ui->databitComboBox->itemData(ui->databitComboBox->currentIndex()).toInt());

    if(m_serialContrl){
        if(m_serialContrl->isRunning()){
            qDebug()<<" is aready run";

            m_serialContrl->stop(true);

            ui->btnOpen->setText("Open");
            ui->labelOpenState->setPixmap(QPixmap(":/icon/image/state_close.png"));

            return;
        }
    }

    m_serialContrl = new SerialControl(setting);

    connect(m_serialContrl,&SerialControl::appendMessageRequested,this, &SerialPageWidget::serialControlMsg);

    m_serialContrl->start();

    ui->btnOpen->setText("Close");
    ui->labelOpenState->setPixmap(QPixmap(":/icon/image/state_open.png"));
}

void SerialPageWidget::serialControlMsg(SerialControl *control, const QString &msg, Settings::OutputFormat format)
{
//    showInfo(msg);
    if(format == Settings::OutputFormat::StdOutFormat){
        showInfo("recv>"+msg);

        m_recvCnt = msg.size();

        ui->labelRecvCnt->setText(QString::number(m_recvCnt));
    }
    else if(format == Settings::OutputFormat::ErrorMessageFormat){
        showInfo("Err>"+msg);
    }else{
        showInfo("Info>"+msg);
    }
}

void SerialPageWidget::clearSend()
{
    ui->editSend->clear();

    ui->labelSendcnt->setText("0");
}

void SerialPageWidget::clearRecv()
{
    ui->editRecv->clear();
    ui->labelRecvCnt->setText("0");
}

void SerialPageWidget::updatePortList()
{
    m_ports.clear();
    ui->serialportComboBox->clear();

    const QList<QSerialPortInfo> serialportInfos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : serialportInfos){
        const QString portName = info.portName();

        if(!portName.isEmpty()){
            m_ports.append(info);

            //TODO,
            //use qmodel
            ui->serialportComboBox->addItem(info.portName());
        }
    }

}

void SerialPageWidget::showInfo(const QString &info)
{
    ui->editRecv->appendPlainText(info);
}
