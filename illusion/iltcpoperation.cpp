#include "iltcpoperation.hpp"
#include <google/protobuf/message.h>

namespace il {

ILTcpOperation::ILTcpOperation(ILMessagePtr rq)
    :   ILOperation(),
        socket_(nullptr),
        bytesSent_(0),
        bytesReceived_(0)
{
    request_ = rq;
}

void ILTcpOperation::connect(const asio::ip::tcp::endpoint& endpoint) {
    if (!socket_)
        socket_ = ILTcpSocketPtr(new ILTcpSocket(Illusion::instance()->getService()));

    start();

    if (socket_->is_open())
        onConnect(std::error_code());
    else
        socket_->async_connect(endpoint, std::bind(&ILTcpOperation::onConnect,
                                               this, std::placeholders::_1));
}

ILTcpOperation& ILTcpOperation::operator=(const ILTcpOperation& other) {
    ILOperation::operator=(other);
    socket_ = other.socket();
    bytesSent_ = other.bytesSent();
    bytesReceived_ = other.bytesReceived();
    return *this;
}

ILTcpOperation::~ILTcpOperation()
{

}

} // namespace il

