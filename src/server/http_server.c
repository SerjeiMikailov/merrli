#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int sendall(int socket, const char *buffer, int length) {
    int total = 0;
    int bytesleft = length;
    int n;

    while (total < length) {
        n = send(socket, buffer + total, bytesleft, 0);
        if (n == -1) {
            break;
        }
        total += n;
        bytesleft -= n;
    }

    return (n == -1) ? -1 : 0;
}

int main(void) {
    FILE *html_data;
    html_data = fopen("../page/index.html", "r");
    if (html_data == NULL) {
        perror("Error opening file index.html");
        exit(EXIT_FAILURE);
    }

    fseek(html_data, 0, SEEK_END);
    long file_size = ftell(html_data);
    fseek(html_data, 0, SEEK_SET);

    char *response_data = (char *)malloc(file_size);
    fread(response_data, 1, file_size, html_data);

    char http_header[2048] = "HTTP/1.1 200 OK\r\n\r\n";
    strcat(http_header, response_data);

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    listen(server_socket, 5);

    int client_socket;
    while (1) {
        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1) {
            perror("Error accepting connection");
            continue;
        }

        char request_buffer[1024];
        recv(client_socket, request_buffer, sizeof(request_buffer), 0);
        sscanf(request_buffer, "GET %*s HTTP/1.1"); // Read GET request line

        if (strstr(request_buffer, "favicon.ico") != NULL) {
            FILE *favicon_data = fopen("../../favicon.ico", "rb");
            if (favicon_data == NULL) {
                // If unable to open file, send a 404 error response
                char error_response[] = "HTTP/1.1 404 Not Found\r\n\r\n";
                sendall(client_socket, error_response, strlen(error_response));
                close(client_socket);
                continue;
            }

            fseek(favicon_data, 0, SEEK_END);
            long favicon_size = ftell(favicon_data);
            fseek(favicon_data, 0, SEEK_SET);

            char favicon_header[2048];
            snprintf(favicon_header, sizeof(favicon_header), "HTTP/1.1 200 OK\r\nContent-Type: image/x-icon\r\nContent-Length: %ld\r\n\r\n", favicon_size);
            sendall(client_socket, favicon_header, strlen(favicon_header));

            char buffer[1024];
            int bytes_read;
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), favicon_data)) > 0) {
                sendall(client_socket, buffer, bytes_read);
            }

            fclose(favicon_data);
            close(client_socket);
            continue;
        }
        if (strstr(request_buffer, "styles.css") != NULL) {
            FILE *css_data = fopen("../page/styles.css", "r");
            if (css_data == NULL) { 
                char error_response[] = "HTTP/1.1 404 Not Found\r\n\r\n";
                sendall(client_socket, error_response, strlen(error_response));
                close(client_socket);
                continue;
            }

            fseek(css_data, 0, SEEK_END);
            long css_size = ftell(css_data);
            fseek(css_data, 0, SEEK_SET);

            char css_header[2048];
            snprintf(css_header, sizeof(css_header), "HTTP/1.1 200 OK\r\nContent-Type: text/css\r\nContent-Length: %ld\r\n\r\n", css_size);
            sendall(client_socket, css_header, strlen(css_header));

            char buffer[1024];
            int bytes_read;
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), css_data)) > 0) {
                sendall(client_socket, buffer, bytes_read);
            }

            fclose(css_data);
            close(client_socket);
            continue;
        }
        if (strstr(request_buffer, "script.js") != NULL) {
            FILE *js_data = fopen("../page/script.js", "r");
            if (js_data == NULL) {
                char error_response[] = "HTTP/1.1 404 Not Found\r\n\r\n";
                sendall(client_socket, error_response, strlen(error_response));
                close(client_socket);
                continue;
            }

            fseek(js_data, 0, SEEK_END);
            long js_size = ftell(js_data);
            fseek(js_data, 0, SEEK_SET);

            char js_header[2048];
            snprintf(js_header, sizeof(js_header), "HTTP/1.1 200 OK\r\nContent-Type: application/javascript\r\nContent-Length: %ld\r\n\r\n", js_size);
            sendall(client_socket, js_header, strlen(js_header));

            char buffer[1024];
            int bytes_read;
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), js_data)) > 0) {
                sendall(client_socket, buffer, bytes_read);
            }

            fclose(js_data);
            close(client_socket);
            continue;
        }

        sendall(client_socket, http_header, strlen(http_header));

        close(client_socket);
    }

    free(response_data);
    fclose(html_data);

    return 0;
}
