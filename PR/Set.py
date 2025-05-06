def addEle(set1):
    ele = int(input("Enter element: "))

    print("Before adding: ")
    print(set1)

    set1.add(ele)        

    print("After adding: ")
    print(set1)

def removeEle(set1):
    ele = int(input("Enter element to delete: "))
    
    print("Before deleting: ")
    print(set1)

    set1.remove(ele)
    
    print("After deleting: ")
    print(set1)
    
def getSize(set1, set2):
    print("Size of set 1: ", len(set1))
    print("Size of set 2: ", len(set2))

def contains(set1):
    ele = int(input("Enter element: "))
    print(ele in set1)
    
def intersectionOfSet(set1, set2):
    res = set1.intersection(set2)
    print(res)
    
def unionOfSet(set1, set2):
    res = set1.union(set2)
    print(res)
    
def differenceOfSet(set1, set2):
    res = set1.difference(set2)
    print(res)
    
def isSubset(set1, set2):
    res = set1.issubset(set2)
    print(res)
    
def display(set1, set2):
    print("Set 1: ", set1)
    print("Set 2: ", set2)
    



def main():
    set1 = set()
    set2 = set()
    
    n1 = int(input("Enter number of elements in set A: "))
    for i in range(n1):
        n = int(input(f"Enter element {i+1}: "))
        set1.add(n)
        
    n2 = int(input("Enter number of elements in set B: "))
    for i in range(n2):
        n = int(input(f"Enter element {i+1}: "))
        set2.add(n)
        
    while True:
        print("---- MENU ----")
        print("1. Add element")
        print("2. Remove element ")
        print("3. Get size")
        print("4. Contains element")
        print("5. Intersection")
        print("6. Union")
        print("7. Difference")
        print("8. Subset")
        print("9. Display")
        print("10. Exit")
        
        ch = int(input("Enter ur choice: "))
        
        if ch == 1:
            addEle(set1)
        elif ch == 2:
            removeEle(set1)
        elif ch == 3:
            getSize(set1, set2)
        elif ch == 4:
            contains(set1)
        elif ch == 5:
            intersectionOfSet(set1, set2)
        elif ch == 6:
            unionOfSet(set1, set2)
        elif ch == 7:
            differenceOfSet(set1, set2)
        elif ch == 8:
            isSubset(set1, set2)
        elif ch == 9:
            display(set1, set2)
        elif ch == 10:
            break
        else:
            print("Invalid choice")
    
main()