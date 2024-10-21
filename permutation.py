class Permutation:
    def __init__(self, items):
        self.items = items
        self.reset()
    
    def reset(self):
        self.completed = False
        self.ks = [i for i in range(len(self.items) - 1)]
        self.i = 0

    def __iter__(self):
        return self

    def __next__(self):
        self.i += 1
        if self.i > 1:
            self.next_permutation()
        if self.completed:
            raise StopIteration()
        return self.items
    
    def _rotate(self, k):
        temp = self.items[k]
        for i in range(k, len(self.items) - 1):
            self.items[i] = self.items[i + 1]
        self.items[len(self.items) - 1] = temp

    def next_permutation(self):
        if self.completed:
            return

        k = len(self.ks) - 1

        if self.ks[k] + 1 != len(self.items):
            self._rotate(k)
            self.ks[k] += 1
        else:
            while k >= 0 and self.ks[k] + 1 == len(self.items):
                self.ks[k] = k
                self._rotate(k)
                k -= 1
            
            if k >= 0:
                self._rotate(k)
                self.ks[k] += 1
            else:
                self.completed = True

indexes = list(range(4))
p = Permutation(indexes)

print('Some permutations:')
print(next(p))
print(next(p))
print(next(p))
print()

print('All permutations:')
for xs in p:
    print(xs)
print()
