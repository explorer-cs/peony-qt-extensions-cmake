#ifndef SHAREMENUPLUGIN_H
#define SHAREMENUPLUGIN_H

#include <QObject>

#include <properties-window-tab-page-plugin-iface.h>

#include "net-usershare-helper.h"

namespace Peony {

class SharePropertiesPagePlugin : public QObject, public PropertiesWindowTabPagePluginIface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PropertiesWindowTabPagePluginIface_iid)
    Q_INTERFACES(Peony::PropertiesWindowTabPagePluginIface)
public:
    explicit SharePropertiesPagePlugin(QObject *parent = nullptr);
    static SharePropertiesPagePlugin *getInstance();

    const QList<ShareInfo> getCurrentShareInfos();
    void addShareInfo(ShareInfo info);
    void removeShareInfo(const QString &item);

    PluginInterface::PluginType pluginType() override {return PluginInterface::PropertiesWindowPlugin;}
    const QString name() override {return tr("Peony Qt Share Extension");}
    const QString description() override {return tr("Allow user share folders");}
    const QIcon icon() override {return QIcon::fromTheme("emblem-shared");}
    void setEnable(bool enable) override {m_enable = enable;}
    bool isEnable() override {return m_enable;}

    int tabOrder() override {return 99;}
    bool supportUris(const QStringList &uris) override;
    QWidget *createTabPage(const QStringList &uris) override;

    void closeFactory() {deleteLater();}

private:
    bool m_enable;
    QList<ShareInfo> m_share_infos;
};

}

#endif // SHAREMENUPLUGIN_H
