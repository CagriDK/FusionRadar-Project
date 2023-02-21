#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

class TcpClient {
public:
    TcpClient(const std::string& host, unsigned short port);

    void send(const std::string& message);
private:
    void receive();
    io_service m_ioService;
    ip::tcp::socket m_socket;
    boost::asio::streambuf m_buffer;
    boost::system::error_code ec;
};