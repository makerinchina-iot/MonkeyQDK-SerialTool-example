#include "serialsettings.h"

#include <QColorDialog>
#include <QDebug>

static const char *SERIAL_SETTING_GROUP = "SerialPluginSetting";

static const char *BACK_COLOR = "backgroundColor";
static const char *FORE_COLOR = "foregroundColor";

void SerialPluginSettings::toSettings(Utils::QtcSettings *s)
{
    s->beginGroup(SERIAL_SETTING_GROUP);

    s->setValueWithDefault(BACK_COLOR,m_backColor, QString("#ffffff"));
    s->setValueWithDefault(FORE_COLOR,m_foreColor, QString("#000000"));

    s->endGroup();
}

void SerialPluginSettings::fromSettings(QSettings *s)
{
    s->beginGroup(SERIAL_SETTING_GROUP);

    m_backColor = s->value(QLatin1String(BACK_COLOR)).toString();
    m_foreColor = s->value(QLatin1String(FORE_COLOR)).toString();

    s->endGroup();
}

SerialSettingsWidget::SerialSettingsWidget():m_ui(new Ui::SerialSettingsWidget),m_settings(new SerialPluginSettings)
{

    m_ui->setupUi(this);

    //get saved settings
    Utils::QtcSettings *settings = ExtensionSystem::PluginManager::settings();
    m_settings->fromSettings(settings);
    m_ui->btnBackColor->setStyleSheet("background:"+m_settings->m_backColor);
    m_ui->btnForeColor->setStyleSheet("background:"+m_settings->m_foreColor);

    qDebug()<<" get saved setting of serial plugin";

    connect(m_ui->btnBackColor,&QPushButton::clicked,[=](){
       QColor color = QColorDialog::getColor();
       m_ui->btnBackColor->setStyleSheet("background:"+color.name());

       m_settings->m_backColor = color.name();
    });

    connect(m_ui->btnForeColor,&QPushButton::clicked,[=](){
       QColor color = QColorDialog::getColor();
       m_ui->btnForeColor->setStyleSheet("background:"+color.name());

       m_settings->m_foreColor = color.name();
    });
}

SerialSettingsWidget::~SerialSettingsWidget()
{
    delete m_ui;
}

void SerialSettingsWidget::apply()
{
//    qDebug()<<" serial apply settings";

    //send signal to plugin widget

    emit settingsUpdate(m_settings);
}

SerialPluginSettings *SerialSettingsWidget::settings()
{
    return m_settings;
}

SerialSettings::SerialSettings()
{
    setId("Serial");
    setCategory("Serial");
    setDisplayName("Serial");

    setWidgetCreator([=](){

        qDebug()<<" new setting page widget";

        m_settingWidget = new SerialSettingsWidget;

        connect(m_settingWidget,&SerialSettingsWidget::settingsUpdate,this,&SerialSettings::settingsUpdate);

        return m_settingWidget;
    });
}

void SerialSettings::finish()
{
    //save settings to file
    qDebug()<<" save settings file to:";

    Utils::QtcSettings *settings = ExtensionSystem::PluginManager::settings();
    qDebug()<<" settings file:"<<settings->fileName();

    m_settingWidget->settings()->toSettings(settings);

    delete m_settingWidget;
}


