/*
 * Author: Matejka Jiri, Misova Miroslava
 * login:  xmatej52, xmisov00
 * school: VUT FIT
 * date:   TODO
 */
#ifdef BUILDCLI
#include "../game/Console.hpp"
int main() {
    Console bash;
    std::cin >> bash;
    return 0;
}
#endif
#ifdef BUILDGUI
#include "../gui/main_window.hpp"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Main_Window w;
    w.show();
    return a.exec();
}
#endif
