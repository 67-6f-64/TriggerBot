#include "classes.h"

using namespace std;

TriggerBot trigger;
Memory mem;
Entity entity;

int main()
{
	cout << "Searching game..." << endl;
	thread findGame(&trigger.FindGame);
	cout << endl;
	if(findGame.joinable())
		findGame.join();	
	
	return 0;
}
