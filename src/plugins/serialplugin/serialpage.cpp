#include "serialpage.h"

#include <QDebug>

SerialPage::SerialPage()
{
    setButtonName("Serial");
    setButtonIcon(QIcon(":/icon/image/serialmonitor.png"));

    m_serialPageWidget = new SerialPageWidget;
    setWidget(m_serialPageWidget);
}

void SerialPage::updateSetting(SerialPluginSettings *settings)
{
    //here apply the settings in setting page

    m_serialPageWidget->applySettings(settings);
}
