#ifdef BUILDCLI
#include "../game/Console.hpp"
int main() {
    Console bash;
    std::cin >> bash;
    return 0;
}
#endif
#ifdef BUILDGUI
int main() {
    /*
    Zde bude tvuj main...
     */
}
#endif