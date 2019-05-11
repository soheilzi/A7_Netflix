#include "notification_repos.h"

using namespace std;

void Notification_repos::add_notif(Notification* notif) {
	notifs.push_back(notif);
}

void Notification_repos::show_all_notifs(int limit) {
	for(int i = notifs.size(); i >= notifs.size() - limit && i >= 0; i--) {
		cout << notifs[i]->get_notif() << endl;
	}
}

void Notification_repos::show_unread_notifs() {
	for(int i = notifs.size(); i >= 0; i--) {
		if(!notifs[i]->is_read()) {
			cout << notifs[i]->get_notif() << endl;
		}
	}
}