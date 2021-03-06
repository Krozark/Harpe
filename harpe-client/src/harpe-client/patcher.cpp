#include <QApplication>
#include <patcher/Patcher.hpp>
#include <patcher/Config.hpp>
#include <utils/string.hpp>

#if _WIN32
#include <QCoreApplication>
#include <QSettings>

extern "C" {
    int _get_output_format( void ){ return 0; } //to avoid linker error on windows
}
#endif


int main(int argc,char* argv[])
{
    QApplication App(argc, argv);
    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());

     #if _WIN32
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    QString value = QCoreApplication::applicationFilePath(); //get absolute path of running exe
    value.replace("/","\\");
    settings.setValue("harpe-client-patcher", value);
    #endif


    patcher::Patcher patcher("harpe-client");
    patcher.show();

    patcher.start();
    std::string url = patcher::Config::getUrl();
    std::vector<std::string> sp = utils::string::split(url,":");

    if(sp.size() >= 2)
    {
        auto sp_ip = utils::string::split(sp[sp.size()-2],"/");
        std::string ip = sp_ip[sp_ip.size()-1];
        std::string port = utils::string::split(sp[sp.size()-1],"/")[0];

        patcher.add_arg(ip);
        patcher.add_arg(port);

        patcher.runSoft();
    }

    return App.exec();
}
