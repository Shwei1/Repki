
dct: list[str]

count = 0

size = 100003

class Node:
    def __init__(self, author,  title):
        self.author: str = author
        self.title: str = title
        self.next = None


def myhash(string: str) -> int:
    h = 0
    for i in range(len(string)):
        h = h * 31 + ord(string[i])
    return h % size

def init():
    global dct, count

    dct = [None] * size


def addBook(author, title):
    global dct, count

    i = myhash(author)

    current = dct[i]

    while current is not None:
        if current.author == author and current.title == title:
            return
        current = current.next

    count += 1
    new_node = Node(author, title)
    new_node.next = dct[i]
    dct[i] = new_node


def find(author, title):
    global dct, count
    i = myhash(author)
    current = dct[i]

    while current is not None:
        if current.author == author and current.title == title:
            return True
        current = current.next

    return False


def delete(author, title):
    global dct, count
    i = myhash(author)
    current = dct[i]

    if current is None:
        return

    if current.author == author and current.title == title:
        dct[i] = current.next
        count -= 1
        return

    prev = current
    while current is not None:
        if current.title == title and current.author == author:
            prev.next = current.next
            count -= 1
            return
        prev = current
        current = current.next


def findByAuthor(author):
    global dct, count

    result = []

    i = myhash(author)
    current = dct[i]

    while current is not None:
        if current.author == author:
            result.append(current.title)
        current = current.next

    return result

