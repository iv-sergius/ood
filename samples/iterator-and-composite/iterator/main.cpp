#include "GoF-iterator.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <boost/format.hpp>

using namespace std;

class CBook
{
public:
	CBook(const string& title, const string& author, int publicationYear)
		: m_title(title)
		, m_author(author)
		, m_publicationYear(publicationYear)
	{
	}
	string GetTitle()const
	{
		return m_title;
	}
	string GetAuthor()const
	{
		return m_author;
	}
	int GetPublicationYear()const
	{
		return m_publicationYear;
	}
private:
	string m_title;
	string m_author;
	int m_publicationYear;
};

typedef IIterator<const CBook> IConstBookIterator;

class CLibrary
{
public:
	typedef unique_ptr<CBook> CBookPtr;

	void AddBook(const CBook& book)
	{
		m_books.emplace_back(make_unique<CBook>(book));
	}

	size_t GetBooksCount()const
	{
		return m_books.size();
	}

	CBook & GetBookAtIndex(size_t index)
	{
		return *m_books.at(index);
	}

	CBook const& GetBookAtIndex(size_t index)const
	{
		return *m_books.at(index);
	}

	unique_ptr<IConstBookIterator> GetIterator()const;
private:
	vector<CBookPtr> m_books;
};

template <typename T, typename UnderlyingIteratorType>
class CMapValueIterator : public IIterator<T>
{
public:
	CMapValueIterator(const UnderlyingIteratorType& begin, const UnderlyingIteratorType & end)
		: m_begin(begin), m_end(end)
	{
	}

	bool HasNext() const override
	{
		return m_begin != m_end;
	}

	const CBook & Get() const override
	{
		return *(m_begin->second);
	}

	void Next() override
	{
		++m_begin;
	}

	unique_ptr<IConstBookIterator> Clone() const override
	{
		return make_unique<CMapValueIterator>(*this);
	}
private:
	UnderlyingIteratorType m_begin;
	UnderlyingIteratorType m_end;
};

template <typename T, typename UnderlyingIteratorType>
unique_ptr<IIterator<T>> MakeMapValueIterator(const UnderlyingIteratorType & begin, const UnderlyingIteratorType & end)
{
	return make_unique<CMapValueIterator<T, UnderlyingIteratorType>>(begin, end);
}


class CBookCatalog
{
public:
	typedef shared_ptr<const CBook> CConstBookPtr;
	typedef multimap<string, CConstBookPtr> BooksByTitle;

	void AddBook(const CBook & book)
	{
		auto bookCopy = make_shared<CBook>(book);

		m_booksByTitle.emplace(book.GetTitle(), bookCopy);
	}

	unique_ptr<IConstBookIterator> GetIterator()const
	{
		return MakeMapValueIterator<const CBook>(m_booksByTitle.cbegin(), m_booksByTitle.cend());
	}

	const auto & GetBooks()const
	{
		return m_booksByTitle;
	}
private:
	BooksByTitle m_booksByTitle;
};

ostream & operator << (ostream & out, const CBook & book)
{
	out << (boost::format(R"("%1%" by %2%, %3%)") 
		% book.GetTitle() 
		% book.GetAuthor()
		% book.GetPublicationYear()).str();
	return out;
}

void PrintLibraryBooks(const CLibrary & library)
{
	for (size_t i = 0; i < library.GetBooksCount(); ++i)
	{
		cout << library.GetBookAtIndex(i) << endl;
	}
}

void PrintCatalogBooksSortedByTitle(const CBookCatalog & catalog)
{
	auto & books = catalog.GetBooks();
	for (auto & titleAndBook : books)
	{
		cout << *titleAndBook.second << endl;
	}
}

class CConstLibraryBookIterator : public IConstBookIterator
{
public:
	CConstLibraryBookIterator(const CLibrary & library)
		: m_library(library)
	{
	}

	bool HasNext() const override
	{
		return m_index < m_library.GetBooksCount();
	}

	const CBook & Get() const override
	{
		return m_library.GetBookAtIndex(m_index);
	}

	void Next() override
	{
		if (!HasNext())
		{
			throw logic_error("Can't move next");
		}
		++m_index;
	}

	unique_ptr<IConstBookIterator> Clone() const override
	{
		return make_unique<CConstLibraryBookIterator>(*this);
	}
private:
	const CLibrary & m_library;
	size_t m_index = 0;

};

unique_ptr<IConstBookIterator> CLibrary::GetIterator() const
{
	return make_unique<CConstLibraryBookIterator>(*this);
}

void PrintBooks(CIteratorWrapper<const CBook> it)
{
	while (it.HasNext())
	{
		cout << it.Get() << endl;
		it.Next();
	}
}

int main()
{
	CLibrary lib;
	lib.AddBook(CBook("Moby Dick", "Herman Melville", 1851));
	lib.AddBook(CBook("The Adventures of Tom Sawyer", "Mark Twain", 1876));
	lib.AddBook(CBook("Crime and Punishment", "Fyodor Dostoevsky", 1866));
	lib.AddBook(CBook("White Fang", "Jack London", 1906));
	lib.AddBook(CBook("The Hound of the Baskervilles", "Arthur Conan Doyle", 1902));

	CBookCatalog catalog;
	catalog.AddBook(CBook("Moby Dick", "Herman Melville", 1851));
	catalog.AddBook(CBook("The Adventures of Tom Sawyer", "Mark Twain", 1876));
	catalog.AddBook(CBook("Crime and Punishment", "Fyodor Dostoevsky", 1866));
	catalog.AddBook(CBook("White Fang", "Jack London", 1906));
	catalog.AddBook(CBook("The Hound of the Baskervilles", "Arthur Conan Doyle", 1902));

	cout << "==== Books from Library ====" << endl;
	PrintLibraryBooks(lib);
	cout << endl << "==== Catalog books sorted by title ====" << endl;
	PrintCatalogBooksSortedByTitle(catalog);

	cout << endl << "==== Books library books using iterator ====" << endl;
	PrintBooks(lib.GetIterator());
	cout << endl << "==== Catalog books sorted by title uning iterator ====" << endl;
	PrintBooks(catalog.GetIterator());

	return 0;
}


