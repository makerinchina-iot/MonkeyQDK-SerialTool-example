#include "homepage.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QCoreApplication>

#include <fancytabwidget/fancytabwidget.h>
#include <fancytabwidget/fancybutton.h>

using namespace FancyTabWidgetUtils;

HomePage::HomePage()
{

    QWidget *homepageWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(homepageWidget);
    homepageWidget->setLayout(mainLayout);

    QLabel *homelabel = new QLabel(homepageWidget);
    homelabel->setText("<center><font size='6' color='gray'>关于MakerInChina</font><p></p></center>\
                       <p></p><p></p><p></p>\
                       <p><center><font size='4' color='red'>技术文章分享    </font>    \
                        <font size='3' color='green'>开源项目制作    </font>    <font size='4' color='blue'>开发问题记录</font></center></p>");

    QLabel *labelWeblogo = new QLabel(homepageWidget);
    labelWeblogo->setPixmap(QPixmap(":/icon/image/logo.png").scaled(64,48));
    QLabel *labelWebsite = new QLabel(homepageWidget);
    labelWebsite->setText("<p><center><font size='4'>Website:<a target='_blank' href='https://www.makerinchina.cn' rel='noopener noreferrer'>Blog of MakerInChina</a> </font></center></p>");
    labelWebsite->setOpenExternalLinks(true);
    QHBoxLayout *layoutWebinfo = new QHBoxLayout(homepageWidget);
    layoutWebinfo->addWidget(labelWeblogo);
    layoutWebinfo->addWidget(labelWebsite);
    layoutWebinfo->setAlignment(Qt::AlignCenter);

    QLabel *labelGitLog = new QLabel(homepageWidget);
    labelGitLog->setPixmap(QPixmap(":/icon/image/github.svg"));
    QLabel *labelGitsite = new QLabel(homepageWidget);
    labelGitsite->setText("<p><center><font size='4'> Github:<a target='_blank' href='https://github.com/makerinchina-iot/' rel='noopener noreferrer'>Git of MakerInChina</a> </font></center></p>");
    labelGitsite->setOpenExternalLinks(true);
    QHBoxLayout *layoutGitInfo = new QHBoxLayout(homepageWidget);
    layoutGitInfo->addWidget(labelGitLog);
    layoutGitInfo->addWidget(labelGitsite);
    layoutGitInfo->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(homelabel);
    mainLayout->addLayout(layoutWebinfo);
    mainLayout->addLayout(layoutGitInfo);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(24);

    setButtonName("Home");
    setButtonIcon(QIcon(":/icon/image/home.png"));
    setWidget(homepageWidget);

}
