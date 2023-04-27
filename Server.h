#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <include/json_reader_writer.h>

/**
 * @brief TcpServer_Sınıfı
 * 
 */
class TcpServer
{
public:
    /**
     * @brief Construct a new Tcp Server object
     * JsonReaderWriter ile "personServer.json" oluşturulur.
     * jData içerisine içerik kayıt edilir.
     * Server bağlantısı başlatılır.
     * @param port
     */
    TcpServer(unsigned short port);

    /**
     * @brief Manuel Server kapatma
     * 
     */
    void stop();

    /**
     * @brief Server-Socket bağlantı kontrolü
     * 
     * @return true 
     * @return false 
     */
    bool getm_IsConnected();

private:
    /**
     * @brief Tcp bağlantı kabul etme fonksiyonu
     * Ctor ile çağırılır ve socket bağlantısı kontrol edilir.
     */
    void start_accept();

    /**
     * @brief start_accept handle fonksiyonu
     * Ctor ile çağırılır ve bağlantı sonucunu dönderir.(Terminale yazdırır.)
     * @param error 
     */
    void handle_accept(const boost::system::error_code &error);

    /**
     * @brief Okuma bloğu
     * Ctor ile çağırılır. Sockete yazılan bir veri var ise geldiği anda okuması yapılır. Gelene kadar bekler.
     */
    void start_read();

    /**
     * @brief Okuma bloğu   
     * Ctor ile çağırılır(MultiChain bir başkası bir başkasını çağırarak vs vs) Socketde veri gelmiş ise start_read, handle_read'i çağırır
     * handle_read socketi okuyarak json dosyasını stringden jsona parse eder. Terminale yazdırırken formatlı olması için dump eder.
     * @param error 
     * @param bytes_transferred 
     */
    void handle_read(const boost::system::error_code &error, size_t bytes_transferred);

    /**
     * @brief Sockete yazdırma bloğu
     * 
     * @param message 
     */
    void start_write(std::string message);

    /**
     * @brief Sockete yazdırma bloğu
     * 
     * @param error 
     */
    void handle_write(const boost::system::error_code &error);

    /**
     * @brief Bağlantı olması durumunda true, aksi durumda false veri tutar.
     * 
     */
    bool m_IsConnected;

    /**
     * @brief Boost::asio service parametresi
     * 
     */
    boost::asio::io_service m_ioService;

    /**
     * @brief Boost::asio bağlantı kontrol parametresi
     * 
     */
    boost::asio::ip::tcp::acceptor m_acceptor;

    /**
     * @brief Boost::asio socket parametresi
     * 
     */
    boost::asio::ip::tcp::socket m_socket;

    /**
     * @brief Boost::asio buffer parametresi
     * 
     */
    boost::asio::streambuf m_buffer;

private:
    /**
     * @brief 
     * 
     */
    json jData;
};
