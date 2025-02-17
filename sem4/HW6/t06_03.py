
EMPTY = "EMPTY"
DELETED = "DELETED"
size: int = 100
count: int = 0
authors: list[str]
books: list[str]


def is_prime(n: int) -> bool:
    if n <= 1:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True

def rehash() -> None:
    global count, size, authors, books

    nauthors = authors
    nbooks = books
    nsize = size

    size = size * 2 + 1

    while not is_prime(size):
        size = size * 2 + 1

    count = 0
    init()

    for i in range(nsize):
        if nauthors[i] not in (EMPTY, DELETED):
            addBook(nauthors[i], nbooks[i])


def myhash(s: str) -> int:
    h = 0
    for i in range(len(s)):
        h = h * 31 + ord(s[i])
    return h % size


def init() -> None:
    global authors, books, count, size
    authors = [EMPTY] * size
    books = [EMPTY] * size
    count = 0


def addBook(author, title):
    global authors, size, count, books

    if size * 0.7 < count:
        rehash()

    i = myhash(author)

    while books[i] not in (EMPTY, DELETED):
        if authors[i] == author and books[i] == title:
            return
        i = (i+1) % size

    count += 1
    authors[i] = author
    books[i] = title


def find(author, title):
    global authors, books, size, count

    i = myhash(author)

    while authors[i] != EMPTY:
        if authors[i] != DELETED:
            if authors[i] == author and books[i] == title:
                return True
        i = (i + 1) % size

    return False


def delete(author, title):

    global authors, books, size, count

    i = myhash(author)

    while authors[i] != EMPTY:
        if authors[i] != DELETED:
            if  authors[i] == author and books[i] == title:
                authors[i] = DELETED
                books[i] = DELETED
                count -= 1
                return
        i = (i + 1) % size


def findByAuthor(author):
    global authors, books, size, count

    result = []

    i = myhash(author)

    while authors[i] != EMPTY:
        if authors[i] != DELETED and authors[i] == author:
            result.append(books[i])
        i = (i+1) % size

    return result
