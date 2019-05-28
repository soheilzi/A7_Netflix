#include "notification_repos.h"

using namespace std;

void NotificationRepos::add_notif(Notification* notif) {
	notifs.push_back(notif);
}

std::vector<std::string> NotificationRepos::get_all_notifs(int limit) {
	vector<string> notifications;
	for(int i = notifs.size() - 1; i >= notifs.size() - limit && i >= 0; i--) {
		notifications.push_back(notifs[i]->get_notif());
		notifs[i]->mark_as_read();
	}
	return notifications;
}

std::vector<std::string> NotificationRepos::get_unread_notifs() {
	vector<string> notifications;
	for(int i = notifs.size() - 1; i >= 0; i--) {
		if(!(notifs[i]->is_read())) {
			notifications.push_back(notifs[i]->get_notif());
			notifs[i]->mark_as_read();
		}
	}
	return notifications;
}