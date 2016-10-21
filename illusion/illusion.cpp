#include "illusion.hpp"
#include "benchmark/ilconnectionbenchmark.hpp"
#include <glog/logging.h>
#include <QCommandLineParser>
#include <QApplication>

namespace il {

Illusion* Illusion::instance_ = nullptr;

Illusion::Illusion()
    :   QObject(nullptr),
        work_(nullptr)
{

}

void Illusion::init() {
    cmdLine_.setApplicationDescription("Benchmark your server");
    cmdLine_.addHelpOption();
    cmdLine_.addVersionOption();

    QCommandLineOption hostOption(QStringList() << "H" << "host",
        QCoreApplication::translate("main", "Specify the host"),
        QCoreApplication::translate("main", "IP Address"));
    cmdLine_.addOption(hostOption);

    QCommandLineOption portOption(QStringList() << "p" << "port",
        QCoreApplication::translate("main", "Specify server's port"),
        QCoreApplication::translate("main", "port number"));
    cmdLine_.addOption(portOption);

    QCommandLineOption connOption(QStringList() << "c" << "connection-benchmark",
        QCoreApplication::translate("main", "Start connection benchmark"));
    cmdLine_.addOption(connOption);

    QCommandLineOption connNumOpion(QStringList() << "cn" << "connection-number",
        QCoreApplication::translate("main", "Set max connections for connection benchmark (default is 60 which means 60k)"));
    cmdLine_.addOption(connNumOpion);

    cmdLine_.process(*QApplication::instance());

    if (!cmdLine_.value(hostOption).length()) {
        LOG(ERROR) << "No host specified via the command-line";
        return;
    } else if (!cmdLine_.value(portOption).length()){
        LOG(ERROR) << "No port specified via the command-line";
        return;
    }

    endpoint_ = asio::ip::tcp::endpoint(asio::ip::address_v4::from_string(cmdLine_.value(hostOption).toStdString()),
                                        cmdLine_.value(portOption).toUInt());

    if (cmdLine_.isSet(connOption)) {
        int num = 60;

        if (cmdLine_.value(connNumOpion).length())
            num = cmdLine_.value(connNumOpion).toInt();

        ILConnectionBenchmark bench(endpoint_.address().to_string().c_str(), endpoint_.port());
        bench.run(num);
    }
}

Illusion::~Illusion() {

}

} // namespace il
