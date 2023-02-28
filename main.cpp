#include <iostream>
#include <boost/asio.hpp>
#include <Server.h>
#include <pthread.h>

using boost::asio::ip::tcp;
/**
 * @brief PThread fonksiyon tanımı yapılan blok
 * Threadın çalışması bir döngüye alınmıştır.
 * Bağlantı kurulana kadar threadı bekletir.
 * Eğer bağlantı kapandı mesajı gelir ise (getm_IsConnected) thread kapatılır.
 * Serverden socketden okunan mesaj tekrardan karşı tarafa yazdırılır. Yazdırma null yada false döner ise m_IsConnected false olur.
 * @param arg 
 * @return void* 
 */
void* ServerThread(void* arg)
{
  TcpServer* server = static_cast<TcpServer*>(arg);

  while(true){
      if (!server->getm_IsConnected()) 
      {
            std::cout << "Server thread stopping..." << std::endl;
            server->stop();
            pthread_exit(nullptr);
            return nullptr;
      }
  }

  pthread_exit(nullptr);
}

/**
 * @brief Ana fonksiyon bloğu
 * Thread ve TcpServer oluşturulur.
 * Terminale "exit" yazdırılır ise manuel olarak server durdurulabilir.
 * @return int 
 */
int main(int, char**) 
{
  TcpServer server(1234);
  pthread_t thread;
  int result = pthread_create(&thread,nullptr,ServerThread,&server);

  if (result != 0) {
        std::cerr << "Failed to create thread: " << strerror(result) << std::endl;
        return -1;
  }

  std::string input;
  while (std::getline(std::cin, input)) {
        if (input == "exit") {
            server.stop();
            break;
        }
    }

  pthread_join(thread, nullptr); // wait for the thread to finish

  return 0;
}
