#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <string>

class TcpServer {
public:
    TcpServer(unsigned short port);
    void stop();
    bool getm_IsConnected();
private:
    bool m_IsConnected;
    void start_accept();
    void handle_accept(const boost::system::error_code& error);
    void start_read();
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    void start_write(std::string message);
    void handle_write(const boost::system::error_code& error);

    boost::asio::io_service m_ioService;
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::ip::tcp::socket m_socket;
    boost::asio::streambuf m_buffer;
};
