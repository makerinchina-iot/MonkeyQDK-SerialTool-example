#ifndef SERIALSETTINGS_H
#define SERIALSETTINGS_H

#include <coreplugin/dialogs/ioptionspage.h>
#include <serial_global.h>
#include <extensionsystem/pluginmanager.h>
#include <utils/qtcsettings.h>

#include "ui_SerialSettingsWidget.h"

class SERIALPLUGIN_EXPORT  SerialPluginSettings{
public:
    QString m_backColor;
    QString m_foreColor;

    void toSettings(Utils::QtcSettings *s);
    void fromSettings(QSettings *s);
};

class SerialSettingsWidget : public Core::IOptionsPageWidget
{
    Q_OBJECT
public:
    explicit SerialSettingsWidget();
    ~SerialSettingsWidget();

    void apply() override;

    SerialPluginSettings *settings();

private:
    Ui::SerialSettingsWidget *m_ui;

    SerialPluginSettings *m_settings;

signals:
    void settingsUpdate(SerialPluginSettings *settings);
};

class SerialSettings : public Core::IOptionsPage
{
    Q_OBJECT
public:
    explicit SerialSettings();
    void finish() override;

signals:
    void settingsUpdate(SerialPluginSettings *settings);

private:
    SerialSettingsWidget *m_settingWidget;
};

#endif // SERIALSETTINGS_H
