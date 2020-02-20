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
	long long index;
	bool isScanned; // Mutable
	long long score;
};

struct Library {
	vector<Book*> books;
	long long booksPerDay;
	long long daysToSignIn;
	long long index;
	bool isSigned; // Mutable
};

struct Answer {
	vector<Library*> libraries;
	vector<vector<Book*> > booksPerLibrary;
};

// GLOBAL VARS {

vector<Book> books;
vector<Library> libraries;
long long totalDays;

long long bestScore;
Answer bestAnswer;

// }

#include "greedyAlgorithm/greedyAlgorithm.cpp"

const int FILES_COUNT = 6;
const string FILE_NAMES[FILES_COUNT] = {"a_example", "b_read_on", "c_incunabula", "d_tough_choices", "e_so_many_books", "f_libraries_of_the_world"};
string fileName, inputFileName, outputFileName;

bool booksComparator(Book* book1, Book* book2) {
	return (book1->score < book2->score);
}

void init() {
	for (size_t i = 0; i < books.size(); i++) {
		books[i].isScanned = false;
	}
	for (size_t i = 0; i < libraries.size(); i++) {
		libraries[i].isSigned = false;
	}
}

void readInputFile(string name) {
	ifstream inf(name);
	long long booksCount;
	long long booksCountInCurrentLibrary;
	long long librariesCount;
	long long bookIndex;
	Book newBook;
	Library newLibrary;
	long long i;
	long long j;

	inf >> booksCount >> librariesCount >> totalDays;
	books.resize(booksCount);
	libraries.resize(librariesCount);
	for (i = 0; i < booksCount; i++) {
		newBook = Book();
		inf >> newBook.score;
		books[i] = newBook;
	}
	for (i = 0; i < librariesCount; i++) {
		newLibrary = Library();
		inf >> booksCountInCurrentLibrary;
		newLibrary.books.resize(booksCountInCurrentLibrary);
		inf >> newLibrary.daysToSignIn >> newLibrary.booksPerDay;
		for (j = 0; j < booksCountInCurrentLibrary; j++) {
			inf >> bookIndex;
			newLibrary.books[j] = &books[bookIndex];
		}
		sort(newLibrary.books.begin(), newLibrary.books.end(), booksComparator);
		libraries[i] = newLibrary;
	}

	inf.close();
}

void writeOutputFile(string name) {
	// bestAnswer
}

int main() {
	for (size_t fileIndex = 0; fileIndex < FILES_COUNT; fileIndex++) {
		fileName = FILE_NAMES[fileIndex];
		inputFileName = fileName + ".in";
		outputFileName = fileName + ".out";
		readInputFile(inputFileName);

		bestScore = 0;
		init();
		greedyAlgorithm();

		//init();
		//algorithm2();

		writeOutputFile(outputFileName);
		cout << "For dataset #" << fileIndex << " '" << fileName << "' the best score is " << bestScore << "\n";
	}

	return 0;
}
