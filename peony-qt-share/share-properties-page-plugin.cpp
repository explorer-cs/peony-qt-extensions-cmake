#include "share-properties-page-plugin.h"
#include "share-page.h"

#include <PeonyFileInfo>
#include <PeonyFileInfoJob>

#include <QLabel>
#include <QTranslator>
#include <QApplication>
#include <QFile>

#include <QDebug>

using namespace Peony;

SharePropertiesPagePlugin *global_instance = nullptr;

SharePropertiesPagePlugin *SharePropertiesPagePlugin::getInstance()
{
    return global_instance;
}

SharePropertiesPagePlugin::SharePropertiesPagePlugin(QObject *parent) : QObject(parent)
{
    qDebug()<<"init";
    QTranslator *t = new QTranslator(this);
    qDebug()<<"\n\n\n\n\n\n\n SharePropertiesPagePlugin translate:"<<t->load(":/translations/peony-qt-share-extension_"+QLocale::system().name());
    QFile file(":/translations/peony-qt-share-extension_"+QLocale::system().name()+".ts");
    qDebug()<<"file:"<<file.exists();
    QApplication::installTranslator(t);

    auto items = NetUsershareHelper::getSharedItems();
    for (auto item : items) {
        auto shareInfo = ShareInfo(item, true);
        m_share_infos<<shareInfo;
    }
    qDebug()<<"items:"<<items;
    global_instance = this;
}

void SharePropertiesPagePlugin::addShareInfo(ShareInfo info)
{
    if (m_share_infos.contains(info)) {
        m_share_infos.removeOne(info);
    }
    m_share_infos<<info;
}

const QList<ShareInfo> SharePropertiesPagePlugin::getCurrentShareInfos()
{
    QList<ShareInfo> l;
    return m_share_infos;
}

void SharePropertiesPagePlugin::removeShareInfo(const QString &item)
{
    for (auto info : m_share_infos) {
        if (info.name == item) {
            m_share_infos.removeOne(info);
            break;
        }
    }
}

bool SharePropertiesPagePlugin::supportUris(const QStringList &uris)
{
    if (uris.count() != 1) {
        return false;
    }
    auto info = FileInfo::fromUri(uris.first());
    if (info->displayName().isNull()) {
        FileInfoJob j(info);
        j.querySync();
    }
    if (!info->isDir() || info->isVirtual() || !info->uri().startsWith("file:///")) {
        return false;
    }
    return true;
}

QWidget *SharePropertiesPagePlugin::createTabPage(const QStringList &uris)
{
    return new SharePage(uris.first());
}
