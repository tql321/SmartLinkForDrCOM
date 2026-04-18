#pragma once
#include <QObject>
class QSystemTrayIcon;
class QMenu;
class SystemTrayManager : public QObject {
Q_OBJECT
public:
explicit SystemTrayManager(QObject* parent = nullptr);
~SystemTrayManager();
void setIcon(const QIcon& icon);
void showMessage(const QString& title, const QString& msg);
bool isVisible() const;
signals:
void showWindowRequested();
void quitRequested();
private:
void setupMenu();
private:
QSystemTrayIcon* m_trayIcon;
QMenu* m_trayMenu;
};