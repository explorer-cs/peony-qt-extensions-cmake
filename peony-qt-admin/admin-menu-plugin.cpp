#include "admin-menu-plugin.h"
#include "file-info.h"

#include <QProcess>
#include <QtConcurrent>
#include <QUrl>

#include <QDebug>

using namespace Peony;

AdminMenuPlugin::AdminMenuPlugin(QObject *parent) : QObject(parent)
{

}

QList<QAction *> AdminMenuPlugin::menuActions(Types types, const QString &uri, const QStringList &selectionUris)
{
    QList<QAction *> l;
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
    if (selectionUris.isEmpty()) {
        auto directoryAction = new QAction(tr("Open Directory as Admin"));
        l<<directoryAction;
        directoryAction->connect(directoryAction, &QAction::triggered, [=](){
            QtConcurrent::run([=](){
                QProcess p;
                QUrl url = uri;
                p.setProgram("pkexec");
                p.setArguments(QStringList()<<"peony-qt"<<url.toEncoded());
                p.start();
                p.waitForFinished();
            });
        });
    } else if (selectionUris.count() == 1) {
        auto info = FileInfo::fromUri(selectionUris.first());
        if (info->isDir()) {
            auto directoryAction = new QAction(tr("Open Directory as Admin"));
            l<<directoryAction;
            directoryAction->connect(directoryAction, &QAction::triggered, [=](){
                QtConcurrent::run([=](){
                    QProcess p;
                    QUrl url = selectionUris.first();
                    p.setProgram("pkexec");
                    p.setArguments(QStringList()<<"peony-qt"<<url.toEncoded());
                    p.start();
                    p.waitForFinished();
                });
            });
        }
        if (info->mimeType().startsWith("text")) {
            auto directoryAction = new QAction(tr("Open Text as Admin"));
            l<<directoryAction;
            directoryAction->connect(directoryAction, &QAction::triggered, [=](){
                QtConcurrent::run([=](){
                    QProcess p;
                    QUrl url = selectionUris.first();
                    p.setProgram("pkexec");
                    p.setArguments(QStringList()<<"pluma"<<url.toEncoded());
                    p.start();
                    p.waitForFinished();
                });
            });
        }
    }
#else
#endif
    return l;
}
