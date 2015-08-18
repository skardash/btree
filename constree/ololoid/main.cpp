#include <QCoreApplication>
#include <iostream>
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    std::cout << "we are here!" << std::endl;
    // int i; std::cin >> i;
    std::cout << "we are there!" << std::endl;
    QApplication::quit();
    return a.exec();
}
