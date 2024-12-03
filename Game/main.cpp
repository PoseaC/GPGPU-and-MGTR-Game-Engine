#include "SampleGame.h"
#include <iostream>

using namespace std;

int main()
{
	try
	{
		SampleGame game;
		game.Run();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}