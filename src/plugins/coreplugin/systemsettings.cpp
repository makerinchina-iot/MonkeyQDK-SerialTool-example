#include "systemsettings.h"

#include "ui_SystemSettings.h"

#include <QDebug>
#include <QColorDialog>

using namespace Core;

class SystemSettingsWidget : public Core::IOptionsPageWidget
{
public:
    SystemSettingsWidget() {
        m_ui.setupUi(this);

        m_ui.tableWidget->horizontalHeader()->setVisible(true);
        m_ui.tableWidget->setHorizontalHeaderLabels(QStringList()<<" Shortcuts "<<" Brief ");

        m_ui.comboLanguage->addItems(QStringList()<<"English"<<"Chinese");

        connect(m_ui.btnbackColor,&QToolButton::clicked,[=](){
           QColor color = QColorDialog::getColor();
           m_ui.btnbackColor->setStyleSheet("background:"+color.name());
        });

        connect(m_ui.btnForColor,&QToolButton::clicked,[=](){
           QColor color = QColorDialog::getColor();
           m_ui.btnForColor->setStyleSheet("background:"+color.name());
        });

        connect(m_ui.comboLanguage,&QComboBox::currentTextChanged,this,&SystemSettingsWidget::setLanguage);

    }

    void apply() override;

private:
    Ui::SystemSettings m_ui;

private slots:
    void setLanguage(const QString &language);
};

void SystemSettingsWidget::apply()
{
    qDebug()<<" system settings apply";
}

void SystemSettingsWidget::setLanguage(const QString &language)
{
    qDebug()<<" set language to:"<<language;
}

SystemSettings::SystemSettings()
{
    setId("SystemSetting");
    setCategory("System");
    setDisplayName("SystemSetting");
    setWidgetCreator([] {return new SystemSettingsWidget;});
}
