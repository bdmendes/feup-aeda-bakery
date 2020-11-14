//
// Created by bdmendes on 14/11/20.
//

#include "login_menu.h"

void LoginMenu::show() {
    printLogo();
}

LoginMenu::LoginMenu(Store &store) : UI(store) {

}
