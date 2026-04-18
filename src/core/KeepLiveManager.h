#pragma once
#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include "../mould/Singleton.h"
#include "NetworkDetector.h"

class KeepLiveManager : public QObject, public Singleton<KeepLiveManager>
{   
    Q_OBJECT
    friend class Singleton<KeepLiveManager>;
public:
	void startBrowseTimer();
	void stopBrowseTimer();
	void sendHeartbeat();
    
public slots:
    void handleNetworkState(NetworkDetector::NetworkState state);
private:
    KeepLiveManager();
    ~KeepLiveManager() = default;

    QTimer* m_browseTimer;
    QTimer* m_loginTimer;
    QNetworkAccessManager* m_networkManager;
	NetworkDetector* m_networkDetector;
};