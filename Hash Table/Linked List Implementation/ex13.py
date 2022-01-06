class HashTable:
    def __init__(self, value):
        self.capacity = value
        self.position = [None] * self.capacity

    def hash(self, key):
        return key % self.capacity

    def insert(self, value):
        index = self.hash(value)
        self.position[index]
        if self.position[index] is None:
            self.position[index] = Node(value, index)
        else:
            node = self.position[index]
            prev = node
            while node is not None:
                prev = node
                node = node.next
            prev.next = Node(value, index)
    
    def search(self, value):
        index = self.hash(value)
        node = self.position[index]
        while node is not None:
            if node.value == value:
                return node
            node = node.next
        return None

    def remove(self, value):
        node = self.position[self.hash(value)]
        result = None
        prev = None
        while node is not None:
            if node.value==value:
                result = node.value
                if prev is not None:
                    prev.next = prev.next.next
                else:
                    self.position[self.hash(value)] = node.next
                del node
                return result
            prev = node
            node = node.next
        return result
    
    def print_line(self, value):
        if self.position[self.hash(value)]:
            self.position[self.hash(value)].print_list()
        

class Node:
    def __init__(self, value, ha):
        self.key = ha
        self.value = value
        self.next = None

    def print_list(self):
        node = self
        while node is not None:
            print(" ", node.value, end="", sep="")
            node = node.next

capacity = int(input())
ht = HashTable(capacity)

n = [int(x) for x in input().split()]


for x in n:
    if x==-1: break
    ht.insert(x)

s = ht.search(int(input()))

if s:
    ht.remove(s.value)
else:
    print("Valor nao encontrado")

line = int(input())
print("[", line, "]", sep="", end="")
ht.print_line(line)

