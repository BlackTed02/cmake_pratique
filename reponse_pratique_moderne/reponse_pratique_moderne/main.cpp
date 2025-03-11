#include "exo4.h"
#include "exo6.h"
#include "exo7.h"
#include "exo9.h"
#include "exo10.h"
#include "exo11.h"

int main()
{
	///Exo4
	std::cout << "Exo 4:\n";
	processResource();

	///exo6
	std::cout << "Exo 6:\n";
	printStudentScores("Alice");
	printStudentScores("Teddy");

	///exo7
	std::cout << "Exo 7:\n";
	constexpr int gcdValue = gcd(48, 18);
	static_assert(gcdValue, "GCD of 48 and 18 should be 6");
	std::cout << gcdValue << std::endl;

	///Exo9
	std::cout << "Exo 9:\n";
	Counter counter;
	incrementInThreads(counter, 2, 4);
	std::cout << counter.get() << std::endl;

	///Exo10
	std::cout << "Exo 10:\n";
	std::cout << sum(10.7f, 20, 30.5f);

	///Exo11
	std::cout << "\nExo 11:\n";
	print();
	return EXIT_SUCCESS;
}