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
#include "greedyAlgorithm2/greedyAlgorithm2.cpp"

#include "writeOutputFile.cpp"

const int FILES_COUNT = 6;
const string FILE_NAMES[FILES_COUNT] = {"a_example", "b_read_on", "c_incunabula", "d_tough_choices", "e_so_many_books", "f_libraries_of_the_world"};
string fileName, inputFileName, outputFileName;

bool booksComparator(Book* book1, Book* book2) {
	return (book1->score > book2->score);
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
		newBook.index = i;
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
		newLibrary.index = i;
		libraries[i] = newLibrary;
	}

	inf.close();
}

void registerAnswer(Answer newAnswer) {
	long long newScore = 0;

	for (long long i = 0; i < newAnswer.libraries.size(); i++) {
		vector<Book*> booksForLib = newAnswer.booksPerLibrary[i];

		for (Book* book: booksForLib) {
			newScore += book->score;
		}
	}

	if (newScore > bestScore) {
		bestScore = newScore;
		bestAnswer = newAnswer;
	}
}

int main() {
	long long scoreSum = 0;
	for (size_t fileIndex = 0; fileIndex < FILES_COUNT; fileIndex++) {
		fileName = FILE_NAMES[fileIndex];
		inputFileName = fileName + ".in";
		outputFileName = fileName + ".out";
		readInputFile(inputFileName);

		bestScore = 0;
		init();
		registerAnswer(greedyAlgorithm());

		init();
		registerAnswer(greedyAlgorithm2());

		writeOutputFile(outputFileName);
		cout << "For dataset #" << fileIndex << " '" << fileName << "' the best score is " << bestScore << "\n";

		scoreSum += bestScore;
	}

	cout << "Total score is " << scoreSum << endl;

	return 0;
}
