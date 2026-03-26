#include "../Define.hpp"
#include "../Server.hpp"

typedef struct sockaddr SOCKADDR;


int main () {

  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

  SOCKADDR_IN sin;

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(6697);

  bind(sock, (SOCKADDR*)&sin, sizeof(sin));

  SOCKADDR_IN csin;
  socklen_t size = sizeof(csin);

  int sock_err = listen(sock, 5);
  while (1) {
    SOCKET csocket = accept(sock, (SOCKADDR *)&csin, &size);
    if (csocket != SOCKET_ERROR) {
      std::cout << "New client is connected";
    }
  }
}