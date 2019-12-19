#include "net-usershare-helper.h"
#include "share-properties-page-plugin.h"
#include <glib.h>

#include <QProcess>
#include <QDebug>

ShareInfo::ShareInfo(const QString &item, bool init)
{
    name = item;

    if (init) {
        QProcess p;
        p.start("net", QStringList()<<"usershare"<<"info"<<item);
        p.waitForFinished();
        auto out = p.readAll();
        auto l = out.split('\n');
        qDebug()<<l;
        for (auto s : l) {
            if (s.startsWith("path")) {
                originalPath = s.split('=').last();
                continue;
            }
            if (s.startsWith("comment")) {
                comment = s.split('=').last();
                continue;
            }
            if (s.startsWith("usershare_acl")) {
                readOnly = s.contains("EveryOne:R");
                continue;
            }
            if (s.startsWith("guest_ok")) {
                allowGuest = s.split('=').last() == "y";
                continue;
            }
        }
        qDebug()<<"info:"<<name<<originalPath<<comment<<readOnly<<allowGuest;
    }
}

NetUsershareHelper::NetUsershareHelper(QObject *parent) : QObject(parent)
{

}

const QStringList NetUsershareHelper::getSharedItems()
{
    QProcess p;
    p.start("net", QStringList()<<"usershare"<<"list");
    p.waitForFinished();
    auto result = p.readAll();
    auto l = result.split('\n');
    QStringList items;
    for (auto s : l) {
        qDebug()<<"share name:"<<s;
        items<<QString(s);
    }
    return items;
}

ShareInfo NetUsershareHelper::getShareItemInfo(const QString &item)
{
    return ShareInfo(item);
}

bool NetUsershareHelper::updateShareInfo(ShareInfo &info)
{
    QProcess p;
    QStringList args;
    args<<info.name;
    args<<info.originalPath;
    args<<(info.comment.isNull()? "Peony-Qt-Share-Extension" : info.comment);
    //args<<(info.readOnly? QString("EveryOne:R")/*.arg(g_get_user_name())*/: "EveryOne:F");
    args<<(info.readOnly? "Everyone:R": "Everyone:F");
    args<<(info.allowGuest? "guest_ok=y": "guest_ok=n");
    qDebug()<<args;
    p.start("net", QStringList()<<"usershare"<<"add"<<args);
    p.waitForFinished();
    auto result = p.readAllStandardError();

    //if sucessed
    info.isShared = result.isEmpty();
    if (info.isShared) {
        Peony::SharePropertiesPagePlugin::getInstance()->addShareInfo(info);
    }
    return info.isShared;
}

void NetUsershareHelper::removeShared(const QString &item)
{
    Peony::SharePropertiesPagePlugin::getInstance()->removeShareInfo(item);
    QProcess p;
    p.start("net", QStringList()<<"usershare"<<"delete"<<item);
    p.waitForFinished();
    qDebug()<<"result:"<<p.readAll();
}
