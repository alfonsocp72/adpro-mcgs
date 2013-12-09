#include <iostream>
#include "bots.h"

#include <stdlib.h>
#include <set>

#define _LADO 10
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

	bots myBots = bots(_LADO, _LADO);	        
	// bots *myBots = new bots(10, 10);

	myBots.generate(2, 10);
	// myBots->generate(2, 10);

		

	while(true)
	{
		myBots.step();		 
		std::cout << "\x1B[2J\x1B[H";
		std::cout << "xxxx\tStep number: " << ++step_num << "\txxxx" << std::endl;
		myBots.for_each_bot([&] (bot & b) {
			
			//myBots.can_move(b, bot::W);	
			if(b.get_team() == 0)			
				b.try_to_do(bot::W);		
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
