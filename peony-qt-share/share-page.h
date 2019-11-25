#ifndef SHAREPAGE_H
#define SHAREPAGE_H

#include <QWidget>

#include "net-usershare-helper.h"

class SharePage : public QWidget
{
    Q_OBJECT
public:
    explicit SharePage(const QString &uri, QWidget *parent = nullptr);

private:
    ShareInfo m_share_info = ShareInfo("", false);
};

#endif // SHAREPAGE_H
