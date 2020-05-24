#include "Edmonds_Karp_algorithm.h"
using namespace std;

int main()
{
	EdmondsKarp_algorithm example;
	bool there_is_no_error = true;

	try
	{
		example.input("info.txt");
	}
	catch (invalid_argument ex)
	{
		cout << "Error. " << ex.what() << endl; 
		there_is_no_error = false;
	}

	if (there_is_no_error == true)
	{
		try
		{
			cout << "The maximum network flow is equal to " << example.max_flow() << "." << endl;
		}
		catch (invalid_argument ex)
		{
			cout << "Error. " << ex.what() << endl;
		}
	}

	system("pause");
	return 0;
}