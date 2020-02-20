
std::pair<Library*, std::vector<Book*> > pickBestLibrary3(long long daysRemained){
	Library* bestLib = nullptr;
	std::vector<Book*> bestLibBooks;
	long long bestScore = 0;
	long long bestDaysToSignIn = 1;

	for (auto& library : libraries){
		if (library.isSigned || library.daysToSignIn >= daysRemained) continue;
		long long score = 0;
		std::vector<Book*> books;

		long long cnt = 0;
		for (long long i = 0; i < library.books.size() && cnt < (daysRemained-library.daysToSignIn)*library.booksPerDay; i++){
			auto book = library.books[i];
			if (book->isScanned) continue;

			score += book->score;
			books.push_back(book);
			cnt++;
		}

		if (score / library.daysToSignIn > bestScore / bestDaysToSignIn){
			bestScore = score;
			bestDaysToSignIn = library.daysToSignIn;
			bestLib = &library;
			bestLibBooks = books;
		}
	}

	return {bestLib, bestLibBooks};
}
