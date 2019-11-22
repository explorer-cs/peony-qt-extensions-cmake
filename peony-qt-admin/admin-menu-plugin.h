#ifndef ADMINMENUPLUGIN_H
#define ADMINMENUPLUGIN_H

#include "menu-plugin-iface.h"

#include <QObject>

namespace Peony {

class AdminMenuPlugin : public QObject, public MenuPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MenuPluginInterface_iid)
    Q_INTERFACES(Peony::MenuPluginInterface)
public:
    explicit AdminMenuPlugin(QObject *parent = nullptr);

    PluginInterface::PluginType pluginType() override {return PluginInterface::MenuPlugin;}
    const QString name() override {return "Peony Qt Admin Extension";}
    const QString description() override {return "Allow user lauch file/directory as admin";}
    const QIcon icon() override {return QIcon::fromTheme("system-users-symbolic");}
    void setEnable(bool enable) override {m_enable = enable;}
    bool isEnable() override {return m_enable;}

    QString testPlugin() override {return "";}
    QList<QAction *> menuActions(Types types, const QString &uri, const QStringList &selectionUris) override;

private:
    bool m_enable;
};

}

#endif // ADMINMENUPLUGIN_H
