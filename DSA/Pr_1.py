class HashTable:
    def __init__(self):
        self.m = int(input("Enter size of the hash table: "))
        self.hashtable = [None] * self.m
        self.count = 0
        self.comparisons = 0
        print(self.hashtable)

    def hashFunction1(self, key):
        return key % self.m

    def hashFunction2(self, key):
        return 1 + (key % (self.m - 1))

    def isFull(self):
        return self.count == self.m

    def quadraticProbingInsert(self, phno, name):
        if self.isFull():
            print("\nHash Table is full! Cannot Insert")
            return
        
        index = self.hashFunction1(phno)
        i = 1
        comparisons = 1
        
        while self.hashtable[index] is not None:
            comparisons += 1
            index = (index + i**2) % self.m
            i += 1
            
        self.hashtable[index] = (phno, name)
        self.count += 1
        self.comparisons += comparisons
        print(f"Inserted ({phno}, {name}) at index {index}. Comparisons: {comparisons}")
        
    def doubleHashingInsert(self, phno, name):
        if self.isFull():
            print("\nHash Table is full! Cannot Insert")
            return
            
        index = self.hashFunction1(phno)
        step = self.hashFunction2(phno)
        
        comparisons = 1
        
        while self.hashtable[index] is not None:
            comparisons += 1
            index = (index + step) % self.m
            
        self.hashtable[index] = (phno, name)
        self.count += 1
        self.comparisons += comparisons
        print(f"Inserted ({phno}, {name}) at index {index}. Comparisons: {comparisons}")
        
    def quadraticProbingSearch(self, phno):
        index = self.hashFunction1(phno)
        comparisons = 1
        i = 1
        
        while self.hashtable[index] is not None:
            if self.hashtable[index][0] == phno:
                self.comparisons += comparisons
                return self.hashtable[index]
            comparisons += 1
            index = (index + i**2) % self.m
            i += 1
        self.comparisons += comparisons
        return None
        
    def doubleHashingSearch(self, phno):
        index = self.hashFunction1(phno)
        step = self.hashFunction2(phno)
        comparisons = 1
        
        while self.hashtable[index] is not None:
            if self.hashtable[index][0] == phno:
                self.comparisons += comparisons
                return self.hashtable[index]
            comparisons += 1
            index = (index + step) % self.m
        self.comparisons += comparisons
        return None
        
    def display(self):
        for index, entry in enumerate(self.hashtable):
            if entry:
                print(f"Index {index}: {entry[0]} -> {entry[1]}")
            else:
                print(f"Index {index}: Empty")
                
def displayMenu():
    print("\n*** MENU ***")
    print("1. Quadratic Probing")
    print("2. Double Hashing")
    print("3. Exit")

def main():
    hash_table = HashTable()

    while True:
        displayMenu()
        choice = int(input("Enter your choice: "))
        
        if choice == 1:
            while True:
                print("\n*** Quadratic Probing ***")
                print("1. Insert")
                print("2. Search")
                print("3. Back to Main Menu")
                option = int(input("Enter your choice: "))
                
                if option == 1:
                    phone_number = int(input("Enter phone number: "))
                    name = input("Enter name: ")
                    hash_table.quadraticProbingInsert(phone_number, name)
                elif option == 2:
                    phone_number = int(input("Enter phone number to search: "))
                    result = hash_table.quadraticProbingSearch(phone_number)
                    if result:
                        print(f"Found: {result[0]} -> {result[1]}")
                    else:
                        print("Not found!")
                elif option == 3:
                    break
                else:
                    print("Invalid choice! Please try again.")
        
        elif choice == 2:
            while True:
                print("\n*** Double Hashing ***")
                print("1. Insert")
                print("2. Search")
                print("3. Back to Main Menu")
                option = int(input("Enter your choice: "))
                
                if option == 1:
                    phone_number = int(input("Enter phone number: "))
                    name = input("Enter name: ")
                    hash_table.doubleHashingInsert(phone_number, name)
                elif option == 2:
                    phone_number = int(input("Enter phone number to search: "))
                    result = hash_table.doubleHashingSearch(phone_number)
                    if result:
                        print(f"Found: {result[0]} -> {result[1]}")
                    else:
                        print("Not found!")
                elif option == 3:
                    break
                else:
                    print("Invalid choice! Please try again.")
        
        elif choice == 3:
            print("Exiting...")
            break
        else:
            print("Invalid choice! Please try again.")

if __name__ == "__main__":
    main()

