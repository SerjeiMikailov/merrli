#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main()
{
  FILE *html_data;
  html_data = fopen("index.html", "r");
  if (html_data == NULL) {
    perror("Erro ao abrir o arquivo index.html");
    exit(EXIT_FAILURE);
}

  char response_data[1024];
  fgets(response_data, 1024, html_data);

  char http_header[2048] = "HTTP/1.1 200 OK\r\n\r\n";
  strcat(http_header, response_data);

  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_adress;
  server_adress.sin_family = AF_INET;
  server_adress.sin_port = htons(8001);
  server_adress.sin_addr.s_addr = INADDR_ANY;

  bind(server_socket, (struct sockaddr *) &server_adress, sizeof(server_adress));
  
  listen(server_socket, 5);

  int client_socket;
  while(1)
  {
    client_socket = accept(server_socket, NULL, NULL);
    send(client_socket, http_header, sizeof(http_header), 0);
  }
  return 0;
}
