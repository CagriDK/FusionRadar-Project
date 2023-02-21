#include <Client.h>
#include <pthread.h>
#include <unistd.h>

TcpClient::TcpClient(const std::string& host, unsigned short port)
    : m_socket(m_ioService)
{
    std::cout<<"Client waiting for connection\n";
    ip::tcp::resolver resolver(m_ioService);
    ip::tcp::resolver::query query(host, std::to_string(port));
    ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

    // Create a timer to wait for one second
    boost::asio::deadline_timer timer(m_ioService);
    timer.expires_from_now(boost::posix_time::seconds(1));
    timer.wait();

    for(;;)
    {
        boost::asio::connect(m_socket, endpointIterator,ec);
        if (!ec) {
            std::cout << "Client connected to port " << port << std::endl;
            break;
        } 
        else {
            std::cerr << "Error connecting to server: " << ec.message() << std::endl;
            std::cerr << "Trying connection ...";
            timer.wait();
        }
    }
}

void TcpClient::send(const std::string &message)
{
    boost::asio::async_write(m_socket, boost::asio::buffer(message + '\n'), [this,message](const boost::system::error_code& ec, size_t bytes) {
        #pragma unused(bytes) // Suppress unused variable warning
            if (!ec) {
                std::cout << "Sent message: " << message << std::endl;
                receive();
            }
            else {
                std::cerr << "Error writing to socket: " << ec.message() << std::endl;
            }
        });
}

void TcpClient::receive() {
    boost::asio::async_read_until(m_socket, m_buffer, '\n', [this](const boost::system::error_code& ec, size_t bytes) {
        if (!ec) {
            std::string message = boost::asio::buffer_cast<const char*>(m_buffer.data());
            std::cout << "Received message: " << message << std::endl;
            m_buffer.consume(bytes);
        }
        else {
            std::cerr << "Error reading from socket: " << ec.message() << std::endl;
        }
    });
}

void* clientThread(void* arg)
{
    static int timerCount;
    TcpClient* client = static_cast<TcpClient*>(arg);
    while(true)
    {
        std::cout<<"Sending Message \n";
        client->send("Test");
        client->send("Case");
        client->send("Working");
        timerCount+=1;
        sleep(1);
        
        if(timerCount >= 10)
        {
            pthread_exit(nullptr);
        }
    }
    pthread_exit(nullptr);
};

int main(int, char**){
    TcpClient client("127.0.0.1",1234);

    pthread_t thread;
    int result = pthread_create(&thread,nullptr,clientThread,&client);

    if (result != 0) {
        std::cerr << "Failed to create thread: " << strerror(result) << std::endl;
        return -1;
    }

    pthread_join(thread, nullptr); // wait for the thread to finish

    return 0;
}