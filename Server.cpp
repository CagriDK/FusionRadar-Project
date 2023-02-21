#include "Server.h"

TcpServer::TcpServer(unsigned short port) :
    m_acceptor(m_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    m_socket(m_ioService) 
{
    start_accept();
    m_ioService.run();
}

void TcpServer::start_accept() 
{
    m_acceptor.async_accept(m_socket, [this](const boost::system::error_code& error){handle_accept(error);});
}

void TcpServer::handle_accept(const boost::system::error_code& error) 
{
    if (!error) {
        std::cout << "New client connected: " << m_socket.remote_endpoint().address().to_string() << std::endl;
        start_read();
    }
    else {
        std::cerr << "Error accepting connection: " << error.message() << std::endl;
    }
}

void TcpServer::start_read() 
{
    boost::asio::async_read_until(m_socket, m_buffer, '\n', [this](const boost::system::error_code& error, size_t bytes_transferred) {
        handle_read(error, bytes_transferred);
    });
}

void TcpServer::handle_read(const boost::system::error_code& error, size_t bytes_transferred) 
{
    if (!error) {
        std::string message = boost::asio::buffer_cast<const char*>(m_buffer.data());
        std::cout << "Received message: " << message << std::endl;
        m_buffer.consume(bytes_transferred);
        // Echo the message back to the client
        start_write(message);
    }
    else {
        std::cerr << "Error reading from socket: " << error.message() << std::endl;
        m_socket.close();
    }
}

void TcpServer::start_write(std::string message) 
{
    boost::asio::async_write(m_socket, boost::asio::buffer(message), [this](const boost::system::error_code& error, size_t) {
        handle_write(error);
    });
}

void TcpServer::handle_write(const boost::system::error_code& error) 
{
    if (error) {
        std::cerr << "Error writing to socket: " << error.message() << std::endl;
        m_socket.close();
        m_IsConnected = false;
    }
    else {
        m_IsConnected = true;
        start_read();
    }
}

void TcpServer::stop()
{
    m_socket.close();
    m_IsConnected = false;
}

bool TcpServer::getm_IsConnected(){
    return m_IsConnected;
}