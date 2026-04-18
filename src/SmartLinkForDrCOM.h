#pragma once
#include <QtWidgets/QMainWindow>
#include <QList>
#include "entity/UserEntity.h"

namespace Ui { class SmartLinkForDrCOMClass; }
class AccountManager;
class DataMaid;
class SystemTrayManager;
class SmartLinkForDrCOM : public QMainWindow
{
    Q_OBJECT

public:
    SmartLinkForDrCOM(DataMaid *dataMaid,AccountManager *accountManager,QWidget *parent = nullptr);
    ~SmartLinkForDrCOM();
void initUI();
void closeEvent(QCloseEvent* event) override;
public slots:
    void usersChanged(QList<UserEntity>& users);
private:
    void initUserUI();
    void initKeepLiveUI();
private:
    Ui::SmartLinkForDrCOMClass *ui;
DataMaid* m_dataMaid;
AccountManager* m_accountManager;
SystemTrayManager* m_trayManager;
};