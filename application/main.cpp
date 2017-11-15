#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTranslator>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QDebug>

#include "application.h"

#ifdef _WIN32
#include <Windows.h>
#endif

int main(int argc, char *argv[])
{
    Application a(argc, argv);

    /*if (!a.lock())
    {
        QMessageBox::warning(NULL, "Prodejna is running", "Prodejna is allready running. Only one instance can be started.");
        return -42;
    }*/

#ifdef _WIN32
    QString exePath = a.applicationDirPath();
    exePath = exePath.append("\\plugins");

    wchar_t Path[10000];
    ::GetEnvironmentVariable(L"PATH", Path, sizeof(Path) / sizeof(TCHAR));
    QString pathVar = QString::fromWCharArray(Path);
    QString newPath = exePath.append(";").append(pathVar);

    ::SetEnvironmentVariable(TEXT("PATH"), newPath.toStdWString().c_str());
#endif

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load(":/translations/timetracker_" + QLocale::system().name());
    a.installTranslator(&myappTranslator);

    MainWindow w;
    w.move(QApplication::desktop()->screen()->rect().center() - w.rect().center());
    w.showMaximized();

    return a.exec();
}
