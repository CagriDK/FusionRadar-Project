#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <json_reader_writer.h> 

using namespace boost::asio;
/**
 * @brief TcpClient_Sınıfı
 * 
 */
class TcpClient {
public:
    /**
     * @brief Construct a new Tcp Client:: Tcp Client object
     * TcpClient Ctor çağırıldığında "personClient.json" oluşturulur. 
     * Bir timer aracılığı ile bağlantı yapılana kadar bekleme yapılır.
     * Bağlantı yapıldıktan sonra döngüden çıkar.
     * @param host // Hangi Adrese bağlantı yapılacağı
     * @param port // Hangi Porta bağlantı yapılacağı
     */
    TcpClient(const std::string& host, unsigned short port);

    /**
     * @brief Sockete veri yazdırma bloğu
     * async_write fonksiyonu ile buffera arguman olarak gönderilen mesaj yazdırılır.
     * Mesajın ulaşamama durumunda hata komutu ekrana yazdırılır.
     * @param message 
     */
    void send(const std::string& message);

    /**
     * @brief Json dönderen blok
     * Serverden gelen json verisini geri dönderir.
     * @return json 
     */
    json getJData()const{
        return jData;
    };
private:
    /**
     * @brief Socketden veri okuma bloğu
     * Bufferdan veri okuma yapılır.
     * async_read_until ile veri gelene kadar bekleme yapar. Geldiği anda veriyi bufferdan okuyarak message içerisine yazdılır.
     * Okunan byte kadar bufferda blok ilerlenir.
     */
    void receive();

    /**
     * @brief Boost::asio service parametresi
     * 
     */
    io_service m_ioService;

    /**
     * @brief Boost::asio socket parametresi
     * 
     */
    ip::tcp::socket m_socket;

    /**
     * @brief Boost::asio buffer parametresi
     * 
     */
    boost::asio::streambuf m_buffer;

    /**
     * @brief Boost::asio hata kodu parametresi
     * 
     */
    boost::system::error_code ec;

    /**
     * @brief Json Değişkeni
     * Serverden gelen verilerin tutulduğu değişken
     */
    json jData;
};