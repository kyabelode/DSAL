class Set:
    def __init__(self, init_list=None):
        self._data = []
        if init_list is not None:
            for item in init_list:
                if not self._contains(item):
                    self._data.append(item)

    def _contains(self, item):
        for x in self._data:
            if x == item:
                return True
        return False

    def add(self, item):
        if not self._contains(item):
            self._data.append(item)

    def remove(self, item):
        index = -1
        for i in range(self.size()):
            if self._data[i] == item:
                index = i
                break
        if index == -1:
            print("Item not found in set")
        else:
            for i in range(index, self.size() - 1):
                self._data[i] = self._data[i + 1]
            self._data.pop()

    def size(self):
        count = 0
        for _ in self._data:
            count += 1
        return count

    def is_empty(self):
        return self.size() == 0

    def clear(self):
        self._data = []

    def intersection(self, other_set):
        result = Set()
        for item in self._data:
            if other_set._contains(item):
                result.add(item)
        return result

    def union(self, other_set):
        result = Set()
        for item in self._data:
            result.add(item)
        for item in other_set._data:
            result.add(item)
        return result

    def difference(self, other_set):
        result = Set()
        for item in self._data:
            if not other_set._contains(item):
                result.add(item)
        return result

    def is_subset(self, other_set):
        for item in self._data:
            if not other_set._contains(item):
                return False
        return True

    def display(self):
        print("Set: ", end="")
        for item in self._data:
            print(item, end=" ")
        print()

# Example usage
s1 = Set([1, 2, 3, 4])
s2 = Set([3, 4, 5])

print("Initial Sets:")
s1.display()
s2.display()

print("\nUnion:")
s1.union(s2).display()

print("Intersection:")
s1.intersection(s2).display()

print("Difference (s1 - s2):")
s1.difference(s2).display()

print("Is s1 subset of s2?:", s1.is_subset(s2))
print("Is s1 subset of Set([1, 2, 3, 4, 5])?:", s1.is_subset(Set([1, 2, 3, 4, 5])))

print("\nAdding 5 to s1:")
s1.add(5)
s1.display()

print("Removing 2 from s1:")
s1.remove(2)
s1.display()

print("Clearing s1:")
s1.clear()
s1.display()
