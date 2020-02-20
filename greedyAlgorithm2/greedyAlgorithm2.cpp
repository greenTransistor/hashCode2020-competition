#include "pickBestLibrary2.cpp"

void addBestLibrary2(Answer& answer, long long& daysRemaining, bool& allLibrariesSigned) {
	pair<Library*, vector<Book*>> bestLibraryAndBooks = pickBestLibrary2(daysRemaining);
	Library* bestLibrary = bestLibraryAndBooks.first;

	if (bestLibrary == nullptr) {
		allLibrariesSigned = true;
		return;
	}

	vector<Book*> books = bestLibraryAndBooks.second;

	bestLibrary->isSigned = true;
	for (Book* book: books) {
		book->isScanned = true;
	}

	answer.libraries.push_back(bestLibrary);
	answer.booksPerLibrary.push_back(books);

	daysRemaining -= bestLibrary->daysToSignIn;
}

Answer greedyAlgorithm2() {
	Answer answer;
	long long daysRemaining = totalDays;
	bool allLibrariesSigned = false;
	while (daysRemaining > 0 && !allLibrariesSigned) {
		addBestLibrary2(answer, daysRemaining, allLibrariesSigned);
	}
	return answer;
}
