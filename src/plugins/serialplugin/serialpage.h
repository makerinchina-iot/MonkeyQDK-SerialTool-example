#ifndef SERIALPAGE_H
#define SERIALPAGE_H

#include <coreplugin/fancypage.h>
#include <serialsettings.h>
#include "serialpagewidget.h"

class SerialPage : public Core::FancyPage
{
    Q_OBJECT
public:
    explicit SerialPage();

private:
    SerialPageWidget *m_serialPageWidget;

public slots:
    void updateSetting(SerialPluginSettings *settings);

};

#endif // SERIALPAGE_H
