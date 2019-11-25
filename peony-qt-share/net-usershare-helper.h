#ifndef NETUSERSHAREHELPER_H
#define NETUSERSHAREHELPER_H

#include <QObject>

class ShareInfo
{
public:
    ShareInfo(const QString &item = nullptr, bool init = false);

    bool operator ==(const ShareInfo &info) {return this->name == info.name;}

    QString name;
    QString originalPath;
    QString comment;
    bool readOnly = true;
    bool allowGuest = false;

    bool isShared = false;
};

class NetUsershareHelper : public QObject
{
    Q_OBJECT
public:
    static const QStringList getSharedItems();
    static ShareInfo getShareItemInfo(const QString &item);

    /*!
     * \brief addShareCmd
     * \param itemDisplayName
     * \param orignalPath
     * \param comment
     * \param readonly
     * \param allowGuest
     *
     * \details
     * Add/modify user defined share
     */
    static void addShareCmd(const QString &itemDisplayName,
                            const QString &orignalPath,
                            const QString &comment,
                            bool readonly,
                            bool allowGuest);

    static bool updateShareInfo(ShareInfo &info);

    static void removeShared(const QString &item);

private:
    explicit NetUsershareHelper(QObject *parent = nullptr);
};

#endif // NETUSERSHAREHELPER_H
