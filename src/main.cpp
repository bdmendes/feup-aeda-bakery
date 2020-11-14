#include <iostream>
#include <ui/menu/intro_menu.h>

#include "model/store/store.h"
#include "ui/ui.h"

int main() {
    Store s;
    IntroMenu menu(s);
    menu.show();
}
