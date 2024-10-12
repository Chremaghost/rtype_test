/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

#include "create_server.hpp"

using boost::asio::ip::udp;

server::server()
{
}

server::~server()
{
}

std::string server::make_daytime_string()
{
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

void server::create_server(char **argv)
{
    try {
        boost::asio::io_context io_context;

        udp::socket socket (io_context, udp::endpoint(udp::v4(), atoi(argv[1])));
        for (;;) {
            std::array<char, 1> recv_buf;
            udp::endpoint remote_endpoint;
            server *self = this;
            socket.async_receive_from(boost::asio::buffer(recv_buf), remote_endpoint, [self, &socket, &remote_endpoint](const boost::system::error_code& error_code, std::size_t size){
                if (!error_code) {
                    std::string message = self->make_daytime_string();
                    socket.async_send_to(boost::asio::buffer(message), remote_endpoint, [](const boost::system::error_code& error, std::size_t){
                        std::cout << "Server is available" << std::endl;
                    });
                }
            });
        }
        std::cout << "R-Type Server Running..." << std::endl;
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
