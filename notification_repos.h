#ifndef __notif_repos
#define __notif_repos

#include "notification.h"
#include <vector>
#include <iostream>

class Notification_repos {
public:
	void add_notif(Notification* notif);
	void show_all_notifs(int limit);
	void show_unread_notifs();
private:
	std::vector<Notification*> notifs;
};


#endif