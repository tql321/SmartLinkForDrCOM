#include "SystemTrayManager.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>

SystemTrayManager::SystemTrayManager(QObject* parent) : QObject(parent) {
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon(":/resources/logo/logo.png"));
    setupMenu();
    m_trayIcon->show();
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::DoubleClick) {
            emit showWindowRequested();
        }
    });
}

SystemTrayManager::~SystemTrayManager() {
    if (m_trayMenu) {
        delete m_trayMenu;
    }
}

void SystemTrayManager::setIcon(const QIcon& icon) { m_trayIcon->setIcon(icon); }

void SystemTrayManager::showMessage(const QString& title, const QString& msg) {
    m_trayIcon->showMessage(title, msg, QSystemTrayIcon::Information, 2000);
}

bool SystemTrayManager::isVisible() const { return m_trayIcon->isVisible(); }

void SystemTrayManager::setupMenu() {
    m_trayMenu = new QMenu();
    QAction* showAction = new QAction(QString::fromUtf8("显示主界面"), m_trayMenu);
    QAction* quitAction = new QAction(QString::fromUtf8("彻底退出"), m_trayMenu);
    
    connect(showAction, &QAction::triggered, this, &SystemTrayManager::showWindowRequested);
    connect(quitAction, &QAction::triggered, this, &SystemTrayManager::quitRequested);
    
    m_trayMenu->addAction(showAction);
    m_trayMenu->addAction(quitAction);
    m_trayIcon->setContextMenu(m_trayMenu);
}
