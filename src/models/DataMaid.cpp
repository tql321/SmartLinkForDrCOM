#include "dataMaid.h"
#include<QSettings>
#include<algorithm>
#include<QComboBox>
#include<QTimer>
#include"ConfigHelper.h"
#include"./models/DataMaid.h"
#include"ConfigHelper.h"
DataMaid::DataMaid()
{
	memberIni();
	
}

void DataMaid::memberIni()
{

	//读取账号信息并按照时间顺序排序
	QVariant usersVar = ConfigHelper::getSetting("users", QVariant());
	if (usersVar.isValid()) {
		m_users = usersVar.value<QList<UserEntity>>();
	}
	// 按照最后登录时间排序，最近登录的用户排在前面
	std::sort(m_users.begin(), m_users.end(), [](const UserEntity& a, const UserEntity& b) {
		return a.lastLoginTime > b.lastLoginTime;
		});
	//从用户列表中获取当前用户名和密码
	m_curUsername = m_users.begin() != m_users.end() ? m_users.begin()->username : "";
	m_curPassword = m_users.begin() != m_users.end() ? m_users.begin()->password : "";
	//不得构造与初始化阶段释放信号
	//emit sigUsersChanged(m_users);
	//emit sigUsersInit(m_curUsername, m_curPassword);

	m_enableAutoStart = ConfigHelper::getSetting("enableAutoStart", true).toBool();
	m_simulatedBrowseInterval = ConfigHelper::getSetting("simulatedBrowseInterval", 60).toInt();
	m_enableAutoLoginCB = ConfigHelper::getSetting("enableAutoLoginCB", true).toBool();
	m_enableForceLogin = ConfigHelper::getSetting("enableForceLogin", true).toBool();
}

void DataMaid::curUsernameChanged(const QString& username)
{
	if (username == m_curUsername) {
		return;
	}
	m_curUsername = username;
	emit sigCurUsernameChanged();
}
void DataMaid::curPasswordChanged(const QString& password)
{
	if (password == m_curPassword) {
		return;
	}
	m_curPassword = password;
	ConfigHelper::setSetting("curPassword", m_curPassword);
	emit sigCurPasswordChanged();
}

void DataMaid::enableAutoLoginChanged(bool checked)
{
	if (checked == m_enableAutoLoginCB) {
		return;
	}
	m_enableAutoLoginCB = checked;
	ConfigHelper::setSetting("enableAutoLoginCB", m_enableAutoLoginCB);
	emit sigEnableAutoStartChanged();
}

void DataMaid::enableForceLoginChanged(bool checked)
{
	if (checked == m_enableForceLogin) {
		return;
	}
	m_enableForceLogin = checked;
	ConfigHelper::setSetting("enableForceLogin", m_enableForceLogin);
	emit sigEnableForceLoginChanged();
}

void DataMaid::addUser(const UserEntity& user)
{
	// 检查用户列表中是否已经存在该用户，如果存在则更新其信息，否则添加新用户
	for (UserEntity& existingUser : m_users) {
		if (existingUser.username == user.username) {
			existingUser.password = user.password;
			existingUser.lastLoginTime = user.lastLoginTime;
			ConfigHelper::setSetting("users", QVariant::fromValue(m_users));
			return;
		}
	}
	// 如果用户列表中不存在该用户，则添加新用户
	m_users.append(user);
	sortUsers();
	// 将用户列表保存到设置中
	ConfigHelper::setSetting("users", QVariant::fromValue(m_users));
	emit sigUsersChanged(m_users);
}
void DataMaid::loginSuccess(const UserEntity& user)
{
	addUser(user);
}
void DataMaid::sortUsers()
{
	std::sort(m_users.begin(), m_users.end(), [](const UserEntity& a, const UserEntity& b) {
		return a.lastLoginTime > b.lastLoginTime;
		});
}
void DataMaid::userItemChanged(int index) {
	UserEntity user = m_users.at(index);
	m_curUsername = user.username;
	m_curPassword = user.password;
	emit sigCurUsernameChanged();
	emit sigCurPasswordChanged();
}
void DataMaid::simulatedBrowseIntervalChanged(int value)
{
	if (m_simulatedBrowseInterval != value) {
		m_simulatedBrowseInterval = value;
		ConfigHelper::setSetting("simulatedBrowseInterval", m_simulatedBrowseInterval);
		emit sigSimulatedBrowseIntervalChanged();
	}
}



void DataMaid::enableAutoStartChanged(bool value)
{
	if (m_enableAutoStart != value) {
		m_enableAutoStart = value;
		ConfigHelper::setSetting("enableAutoStart", m_enableAutoStart);
		emit sigEnableAutoStartChanged();
	}
}
