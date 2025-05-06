class HashTable:
    def __init__(self):
        self.m = int(input("Enter size of hash table: "))
        self.hashtable = [None] * self.m
        self.count = 0
        print(self.hashtable) 
        
    def hashfunction(self, key):
        return key % self.m
    
    def isFull(self):
        return self.count == self.m

    #linear probing insertion
    def LPInsert(self, phno, name):
        if self.isFull():
            print("Hash table is full")
            return

        index = self.hashfunction(phno)
        comparison = 1
        
        while self.hashtable[index] is not None:
            comparison += 1
            index = (index + 1) % self.m
            
        self.hashtable[index] = (phno, name)
        self.count += 1
        print(f"Inserted ({phno}, {name}) at index {index}. Comparisons: {comparison}")
    
    #linear probing searching
    def LPSearch(self, phno):
        index = self.hashfunction(phno)
        start_index = index
        comparison = 1
        
        while self.hashtable[index] is not None:
            if self.hashtable[index][0] == phno:
                print(f"{phno} found at index: {index}. Comparisons: {comparison}")
                return
            
            comparison += 1
            index = (index + 1) % self.m 
            if index == start_index:    
                break
            
        print(f"{phno} not found. Comparisons: {comparison}")

    #quadratic probing insertion
    def QPInsert(self, phno, name):
        if self.isFull():
            print("Hash table is full")
            return
        
        index = self.hashfunction(phno)
        i = 1
        comparison = 1
        
        while self.hashtable[index] is not None:
            comparison += 1
            index = (index + i**2) % self.m
            i += 1
        
        self.hashtable[index] = (phno, name)
        self.count += 1
        print(f"Inserted ({phno}, {name}) at index {index}. Comparisons: {comparison}")
        
    #quadratic probing search
    def QPSearch(self, phno):
        index = self.hashfunction(phno)
        start_index = index
        comparison = 1
        i = 1 
            
        while self.hashtable[index] is not None:
            if self.hashtable[index][0] == phno:
                print(f"{phno} found at index: {index}. Comparisons: {comparison}")
                return

            comparison += 1
            index = (index + i**2) % self.m
            i += 1
                
            if index == start_index:
                break
                
        print(f"{phno} not found. Comparisons: {comparison}")
        
    #display hashtable    
    def display(self):
        print("--- Hash Table ---")
        
        for index, entry in enumerate(self.hashtable):
            if entry:
                print(f"Index {index}:  {entry[0]} -> {entry[1]}")
            else:
                print(f"Index {index}:  Empty")
        print("------------------")
            
def menu():
    print("---- MENU ----")
    print("1. Linear Probing")
    print("2. Quadratic Probing")
    print("3. Display")
    print("4. Exit")
    
def main():
    ht = HashTable()
    
    while True:
        menu()
        ch = int(input("Enter ur choice: "))
        
        if ch == 1:
            while True:
                print("--- Linear Probing --- ")
                print("1. Insert ")
                print("2. Search")
                print("3. Back to main")
                
                ch = int(input("Enter ur choice: "))

                if ch == 1:
                    phno = int(input("Enter phone number: "))
                    name = input("Enter name: ")    
                    ht.LPInsert(phno, name)
                
                elif ch == 2:
                    phno = int(input("Enter phone number: "))    
                    ht.LPSearch(phno)
                    
                elif ch == 3:
                    break
        
        elif ch == 2: 
            while True:
                print("--- Quadratic Probing ---")
                print("1. Insert ")
                print("2. Search")
                print("3. Back to main")
                
                ch = int(input("Enter ur choice: "))

                if ch == 1:
                    phno = int(input("Enter phone number: "))
                    name = input("Enter name: ")    
                    ht.QPInsert(phno, name)
                
                elif ch == 2:
                    phno = int(input("Enter phone number: "))    
                    ht.QPSearch(phno)
                    
                elif ch == 3:
                    break
        
        elif ch == 3:
            ht.display()
            
        elif ch == 4:
            break
            
        else:
            print("Invalid choice...")
            
main()            