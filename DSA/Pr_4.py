#Practical No 4: Set operations

def take_input():
    set1 = set()
    n = int(input("Enter number of elements in set 1: "))
    for i in range(n):
        ele = int(input(f"Enter element {i+1} : "))
        set1.add(ele)

    set2 = set()
    n2 = int(input("Enter number of elements in set 2: "))
    for i in range(n2):
        ele2 = int(input(f"Enter element {i+1} : "))
        set2.add(ele2)
        
    return set1, set2

def Menu():
    set1 = set() 
    set2 = set()  

    while True:
        print("\n********* MENU *********")
        print("1. Add Element")
        print("2. Remove Element")
        print("3. Get Size")
        print("4. Contains Element")
        print("5. Intersection")
        print("6. Union")
        print("7. Difference")
        print("8. Subset")
        print("9. Display")
        print("10. Exit")
        
        ch = int(input("Enter your choice: "))
        
        if ch == 1:  
            ele = int(input("Enter element to add: "))
            set1.add(ele)
            print(f"{ele} added to set")
        
        elif ch == 2:  
            ele = int(input("Enter element to remove: "))
            if ele in set1:
                set1.remove(ele)
                print(f"{ele} removed from set")
            else:
                print("Element not found in set.")
        
        elif ch == 3:  
            print("The size of set is: ", len(set1))
        
        elif ch == 4:  
            ele = int(input("Enter element to search: "))
            print(f"Element {ele} is in set: {ele in set1}")
        
        elif ch == 5:
            set1, set2 = take_input()
            result = set1.intersection(set2)
            print("Intersection of set1 and set2 is: ", result)
        
        elif ch == 6:
            set1, set2 = take_input()
            result = set1.union(set2)
            print("Union of set1 and set2 is: ", result)
        
        elif ch == 7:
            set1, set2 = take_input()
            result = set1.difference(set2)
            print("Difference of set1 and set2 is: ", result)
        
        elif ch == 8:
            set1, set2 = take_input()
            result = set1.issubset(set2)
            print("Is set1 a subset of set2? : ", result)
        
        elif ch == 9:
            print("Elements of set1 are: ")
            for i in set1:
                print(i)
        
        elif ch == 10:
            print("Exiting program...")
            break
        
        else:
            print("Invalid choice. Please try again.")

Menu()

