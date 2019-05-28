#ifndef __notif_repos
#define __notif_repos

#include "notification.h"
#include <vector>
#include <iostream>

class NotificationRepos {
public:
	void add_notif(Notification* notif);
	std::vector<std::string> get_all_notifs(int limit);
	std::vector<std::string> get_unread_notifs();
private:
	std::vector<Notification*> notifs;
};


#endif