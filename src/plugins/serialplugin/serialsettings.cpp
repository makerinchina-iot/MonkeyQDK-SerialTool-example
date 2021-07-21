#include "serialsettings.h"

#include "ui_SerialSettingsWidget.h"

#include <QColorDialog>
#include <QDebug>

class SerialSettingsWidget : public Core::IOptionsPageWidget
{
public:
    SerialSettingsWidget() {
        m_ui.setupUi(this);

        connect(m_ui.btnBackColor,&QPushButton::clicked,[=](){
           QColor color = QColorDialog::getColor();
           m_ui.btnBackColor->setStyleSheet("background:"+color.name());
        });

        connect(m_ui.btnForeColor,&QPushButton::clicked,[=](){
           QColor color = QColorDialog::getColor();
           m_ui.btnForeColor->setStyleSheet("background:"+color.name());
        });
    }

    void apply() override;

private:
    Ui::SerialSettingsWidget m_ui;
};

void SerialSettingsWidget::apply()
{
    qDebug()<<" apply settings";

    //send signal to plugin widget ??
}

SerialSettings::SerialSettings()
{
    setId("Serial");
    setCategory("Serial");
    setDisplayName("Serial");
    setWidgetCreator([]{return new SerialSettingsWidget;});
}

void SerialSettings::apply()
{

}

void SerialSettings::finish()
{

}
