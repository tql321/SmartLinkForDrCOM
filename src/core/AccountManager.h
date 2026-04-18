#pragma once
#include <QObject>
#include "../entity/JsonReturnEntity.h"
#include "../mould/Singleton.h"
class QNetworkAccessManager;
struct UserEntity;

class AccountManager : public QObject, public Singleton<AccountManager>
{
Q_OBJECT
    
friend class Singleton<AccountManager>;

public:
JsonReturnEntity parseNetworkReply(const QString& responseString);

private:
AccountManager();
~AccountManager() = default;

signals:
void sigLoginSuccess(const UserEntity& user);

public slots:
void onLogin(const QString& username, const QString& password);
void onLogout();
private:
QNetworkAccessManager* networkManager;
};