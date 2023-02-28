#include "Server.h"
/**
 * @brief Construct a new Tcp Server:: Tcp Server object
 * JsonReaderWriter ile "personServer.json" oluşturulur.
 * jData içerisine içerik kayıt edilir.
 * Server bağlantısı başlatılır.
 * @param port 
 */
TcpServer::TcpServer(unsigned short port) :
    m_acceptor(m_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    m_socket(m_ioService) 
{
    JsonReaderWriter jsonWriter("personServer.json"); //make it create a file if not exist
     //Class Ctor verilmez ise boş bir json oluşturması için yeni bir ctor yaz. Sadece dosyayı oluştursun.
    jData=jsonWriter.read("personServer.json");
    start_accept();
    m_ioService.run();
}

/**
 * @brief Tcp bağlantı kabul etme fonksiyonu
 * Ctor ile çağırılır ve socket bağlantısı kontrol edilir.
 */
void TcpServer::start_accept() 
{
    m_acceptor.async_accept(m_socket, [this](const boost::system::error_code& error){handle_accept(error);});
}

/**
 * @brief start_accept handle fonksiyonu
 * Ctor ile çağırılır ve bağlantı sonucunu dönderir.(Terminale yazdırır.)
 * @param error 
 */
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

/**
 * @brief Okuma bloğu
 * Ctor ile çağırılır. Sockete yazılan bir veri var ise geldiği anda okuması yapılır. Gelene kadar bekler.
 */
void TcpServer::start_read() 
{
    boost::asio::async_read_until(m_socket, m_buffer, '\n', [this](const boost::system::error_code& error, size_t bytes_transferred) {
        handle_read(error, bytes_transferred);
    });
}

/**
 * @brief Okuma bloğu   
 * Ctor ile çağırılır(MultiChain bir başkası bir başkasını çağırarak vs vs) Socketde veri gelmiş ise start_read, handle_read'i çağırır
 * handle_read socketi okuyarak json dosyasını stringden jsona parse eder. Terminale yazdırırken formatlı olması için dump eder.
 * @param error 
 * @param bytes_transferred 
 */
void TcpServer::handle_read(const boost::system::error_code& error, size_t bytes_transferred) 
{
    if (!error) {
        std::string message = (boost::asio::buffer_cast<const char*>(m_buffer.data()));
        // [    "age",    "30"]
        json jdata = json::parse(message);
        std::cout << "Received message: " << jdata.dump(4) << std::endl;
        m_buffer.consume(bytes_transferred);
        // Echo the message back to the client
        start_write("Message Received");
    }
    else {
        std::cerr << "Error reading from socket: " << error.message() << std::endl;
        m_socket.close();
    }
}

/**
 * @brief Sockete yazdırma bloğu
 * 
 * @param message 
 */
void TcpServer::start_write(std::string message) 
{
    boost::asio::async_write(m_socket, boost::asio::buffer(message), [this](const boost::system::error_code& error, size_t) {
        handle_write(error);
    });
}

/**
 * @brief Sockete yazdırma bloğu
 * 
 * @param error 
 */
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

/**
 * @brief Manuel Server kapatma
 * 
 */
void TcpServer::stop()
{
    m_socket.close();
    m_IsConnected = false;
}

/**
 * @brief Server-Socket bağlantı kontrolü
 * 
 * @return true 
 * @return false 
 */
bool TcpServer::getm_IsConnected(){
    return m_IsConnected;
}