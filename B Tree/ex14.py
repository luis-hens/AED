class BTree:
    def __init__(self, size, root):
        self.values
        self.size = size
        self.childs
        self.quantity = 0
        self.leaf = root
    
    def insert(self, value):
        i = self.quantity-1
        if self.quantity < self.size:
            if self.quantity == 0:
                self.values[0] = value
                self.quantity += 1
            else:
                while i>=0 and self.values[i] > value:
                    self.values[i+1] = self.values[i]
                    i -= 1
            self.values[i+1] = value
            self.quantity += 1
        