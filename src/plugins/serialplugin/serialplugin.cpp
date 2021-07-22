#include "serialplugin.h"

#include "serialsettings.h"
#include "serialpage.h"

SerialPlugin::SerialPlugin()
{

}

bool SerialPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorString);

    SerialPage *serialPage = new SerialPage();
    SerialSettings *serialSetting = new SerialSettings();

    ExtensionSystem::PluginManager::addObject(serialPage);

    connect(serialSetting,&SerialSettings::settingsUpdate,serialPage,&SerialPage::updateSetting);


    return true;
}

void SerialPlugin::extensionsInitialized()
{

}
