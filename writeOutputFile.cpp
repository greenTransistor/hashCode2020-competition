void writeOutputFile(string name) {
	ofstream fout(name);

	fout << bestAnswer.libraries.size() << endl;

	for (long long i = 0; i < bestAnswer.libraries.size(); i++) {
		Library* library = bestAnswer.libraries[i];
		vector<Book*> books = bestAnswer.booksPerDay[i];

		fout << library->index << " " << books.size() << endl;
		for (Book* book: books) {
			fout << book->index << " ";
		}
		fout << endl;
	}
}