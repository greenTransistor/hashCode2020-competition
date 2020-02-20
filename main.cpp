#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Book {
	long long score;
	bool isScanned;
}

struct Library {
	long long booksPerDay;
	long long daysToSignIn;
	vector<long long> books;
};

// GLOBAL VARS {

vector<Book> books;
vector<Library> libraries;
long long totalDays;

long long bestScore = 0;

// }

const int FILES_COUNT = 6;
const string FILE_NAMES[FILES_COUNT] = {"a_example", "b_read_on", "c_incunabula", "d_tough_choices", "e_so_many_books", "f_libraries_of_the_world"};
string fileName, inputFileName, outputFileName;

void readInputFile(string name) {
	ifstream inf(name);
	long long booksCount;
	long long librariesCount;
	book newBook;
	library newLibrary;

	inf >> booksCount >> librariesCount >> totalDays;
	books.resize(booksCount);
	libraries.resize(librariesCount);

	inf.close();
}

int main() {
	for (size_t fileIndex = 0; fileIndex < FILES_COUNT; fileIndex++) {
		fileName = FILE_NAMES[fileIndex];
		inputFileName = fileName + ".in";
		outputFileName = fileName + ".out";
		readInputFile(inputFileName);

		bestScore = 0;
		init();
		//algorithm1();

		//init();
		//algorithm2();

		writeOutputFile(outputFileName);
		cout << "For dataset #" << fileIndex << " '" << fileName << "' the best score is " << bestScore << "\n";
	}

	return 0;

	return 0;
}
