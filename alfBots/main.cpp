#include <iostream>
#include "bots.h"
#include <stdlib.h>
#include <set>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>


using boost::asio::ip::tcp;

void send(tcp::socket &socket, const std::string & str) {
    boost::asio::write(socket, boost::asio::buffer(str + "\n"), boost::asio::transfer_all());
}

const int _LADO=10;

/*
void pinta_escenario()
{	
	// Linea superior
	for(int n = 0; n < _LADO + 2; ++n)
	{
		std::cout << 'X';		
	}
	std::cout << std::endl;
 	
	// Lineas intermedias
	for(int n = 0; n < _LADO; ++n)
	{
		std::cout << 'X';
		for(int n = 0; n < _LADO; ++n)
		{
			std::cout << ' ';
		}
		std::cout << 'X';
		std::cout << std::endl;			
	}

	// Linea inferior
	for(int n = 0; n < _LADO + 2; ++n)
	{
		std::cout << 'X';		
	}
	std::cout << std::endl; 	
}
*/


void pinta_escenario(bots _Bots)
{	
	// Linea superior
	for(int n = 0; n < _LADO + 2; ++n)
	{
		std::cout << 'X';		
	}
	std::cout << std::endl;
 	
	// Lineas intermedias
	for(int fila = 0; fila < _LADO; ++fila)
	{
		std::cout << 'X';
		for(int columna = 0; columna < _LADO; ++columna)
		{
			bot * posBot = _Bots.find_at( {columna, fila} );
			if(posBot == nullptr)
				std::cout << ' ';
			else
				std::cout << posBot->get_team();
		}
		std::cout << 'X';
		std::cout << std::endl;			
	}

	// Linea inferior
	for(int n = 0; n < _LADO + 2; ++n)
	{
		std::cout << 'X';		
	}
	std::cout << std::endl; 	
}

int main(int argc, char* argv[])
{
	std::string pause;
	int step_num = 0;
	std::cout << "¡¡A jugar!!" << std::endl;
	//const int _LADO =  10;

	bot::team_id id = 1000;	

	bot::field_size field_width;
    bot::field_size field_height;

    int win_width = 500;
    int win_height = 500;
	

	//bots myBots = bots(_LADO, _LADO); mal!
	//bots myBost(_LADO, _LADO);
	bots myBots;
	// bots *myBots = new bots(10, 10);

	//myBots.generate(2, 10);
	// myBots->generate(2, 10);

	boost::mutex state_mutex;
		
	// Comunicacion servidor-cliente
	boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
	auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
	std::shared_ptr<tcp::socket> socket(new tcp::socket(io_service));

    boost::asio::connect(*socket, endpoint_iterator);	
	
	bool gameover = false;

	bool connected = false;
    	
	boost::asio::streambuf buf;

	// read from server
	read_until(*socket, buf, "\n");

    std::string data;
    std::istream is(&buf);
    std::getline(is, data);


    std::istringstream ilstream(data);

    std::string command;
    ilstream >> command;

    if(command == "welcome") {
        ilstream >> id;
        std::cout << "team id: " << id << std::endl;
        //ai.set_team(id);

        ilstream >> field_width;
        ilstream >> field_height;
        myBots.set_size(field_width, field_height);
        std::cout << "setting field: " << field_width << " x " << field_height << std::endl;
        std::cout << "setting " << win_width << ", " << win_height << std::endl;
        //set_screen(win_width, win_height, field_width, field_height);
    }

 /*
			else if(command == "state") {

			    std::stringstream state;
			    while(!ilstream.eof()) {
			        std::string a;
			        ilstream >> a;
				    state << a << " ";
				}
				boost::archive::text_iarchive ia(state);
				{
				    // mutex:
				    // segfaults if it draws during a state update (drawing +
				    // incomplete state is fatal)
				    boost::mutex::scoped_lock lock(state_mutex);
				    ia >> bots;
				}
			}*/
	while(!gameover)
	{
		myBots.step();		 
		//std::cout << "\x1B[2J\x1B[H";
		std::cout << "xxxx\tStep number: " << ++step_num << "\txxxx" << std::endl;
		myBots.for_each_bot([&] (bot & b) {
			
			// send to server			
			std::stringstream stream;
            stream << "move " << b.get_x() << " " << b.get_y() << " " << bot::W;
            send(*socket, stream.str());			
			
			
			//myBots.can_move(b, bot::W);	
			//if(b.get_team() == 0)			
			//	b.try_to_do(bot::W);		
			//std::cout << b.get_team() << "\t"; // << std::endl;
			//std::cout << b.get_x() << "\t";
			//std::cout << b.get_y() << "\t";
			//std::cout << b.get_energy() << std::endl;		
			
		});

		pinta_escenario(myBots);

		std::cout << "xxxx\tStep number: " << step_num << "\txxxx" << std::endl;

		
		//std::cin.get();
		//system("PAUSE");		
		std::cin >> pause;
	}
	
	std::cout << "Lo has ejecutado!" << std::endl;
	return 0;	
}
