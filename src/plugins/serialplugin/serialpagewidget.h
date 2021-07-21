#ifndef SERIALPAGEWIDGET_H
#define SERIALPAGEWIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <serialcontrol.h>

namespace Ui {
class SerialPageWidget;
}

class SerialPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPageWidget(QWidget *parent = nullptr);
    ~SerialPageWidget();

private:
    Ui::SerialPageWidget *ui;

    QList<QSerialPortInfo> m_ports;
    QList<qint32> m_baudRates;


    SerialControl *m_serialContrl;

    quint64 m_sendCnt;
    quint64 m_recvCnt;

private slots:
    void sendInput();
    void openSerial();
    void serialControlMsg(SerialControl *control, const QString &msg, Settings::OutputFormat format);
    void clearSend();
    void clearRecv();

private:
    void updatePortList();

    void showInfo(const QString &info);
};

#endif // SERIALPAGEWIDGET_H
