#include "SmartLinkForDrCOM.h"
#include <QtWidgets/QApplication>
#include "entity/UserEntity.h"
#include "models/DataMaid.h"
#include "core/AccountManager.h"
#include "core/KeepLiveManager.h"

int main(int argc, char* argv[])
{
	qRegisterMetaType<QList<UserEntity>>("QList<UserEntity>");
	qRegisterMetaTypeStreamOperators<QList<UserEntity>>("QList<UserEntity>");
	qRegisterMetaType<UserEntity>("UserEntity");
	qRegisterMetaTypeStreamOperators<UserEntity>("UserEntity");

	QApplication app(argc, argv);
	QApplication::setOrganizationName(ORG_NAME);
	QApplication::setApplicationName(APP_NAME);

	// Because they inherit Singleton, we pass their instances directly
	SmartLinkForDrCOM window(&DataMaid::instance(), &AccountManager::instance());
	window.show();

	// Start Keep-Alive tasks if needed
	KeepLiveManager::instance();

	return app.exec();
}
