def input_array(arr):
    n = int(input("Enter the size of the table: "))
    for i in range(n):
        arr.append([0, ""])  

def display(arr):
    print("\nCurrent Table:")
    for i in range(len(arr)):
        print(f"Name: {arr[i][0]}, Telephone No: {arr[i][1]}")

def double_hash(arr):
    name = input("Enter the name of the person: ")
    a = int(input("Enter the telephone no: "))
    index = a % len(arr)  
    
    h = index
    i = 0  
    h2 = 7 - (a % 7)  

    while arr[h][0] != 0:  
        if arr[h][0] == a:  
            print("Key already exists.")
            return
        
        i += 1  
        h = (index + i * h2) % len(arr)

        if i > len(arr):  
            print("Hash table is full.")
            return

    arr[h][0] = name
    arr[h][1] = a
    print(f"Inserted key at index {h}")

def search_double(arr):
    b = int(input("Enter the telephone number to search: "))
    key = b % len(arr)  
    
    h = key  
    i = 0  
    h2 = 7 - (b % 7)  

    while arr[h][0] != 0:  
        if arr[h][1] == b:  
            print(f"Found: Name: {arr[h][0]}, Telephone No: {arr[h][1]}")
            return
        i += 1  
        h = (key + i * h2) % len(arr)  

        if i >= len(arr):  
            break 

    print("Key not found in the hash table.")  

def linear_probing(arr):
    name = input("Enter the name of the person: ")
    a = int(input("Enter the telephone no: "))
    index = a % len(arr)  # Hash function

    h = index
    while arr[h][0] != 0:  # Find the next available slot
        if arr[h][1] == a:  # If the key already exists
            print("Key already exists.")
            return
        h = (h + 1) % len(arr)  # Linear probing
        if h == index:  # If we've come full circle
            print("Hash table is full.")
            return

    arr[h][0] = name
    arr[h][1] = a
    print(f"Inserted key at index {h}") 

def search_linear(arr):
    b = int(input("Enter the telephone number to search: "))
    key = b % len(arr)  # Hash function

    h = key
    while arr[h][0] != 0:  # Search until an empty slot is found
        if arr[h][1] == b:  # If the key is found
            print(f"Found: Name: {arr[h][0]}, Telephone No: {arr[h][1]}")
            return
        h = (h + 1) % len(arr)  # Linear probing
        if h == key:  # If we've come full circle
            break

    print("Key not found in the hash table.")

    
def menu():
    print("\nMenu:")
    print("1. Double Hash")
    print("2. Linear Probing")
    print("3. Search by double hashing")
    print("4. Search by linear probing ")
    print("5. Display hash table")
    print("6. Exit")
    
def main():
    arr = []
    input_array(arr)  

    while True:
        menu()  
        choice = int(input("Choose an option (1/2/3): "))
        
        if choice == 1:
            double_hash(arr)  
        elif choice == 2:
            linear_probing(arr)  
        elif choice == 3:
            search_double(arr) 
        elif choice == 4:
            search_linear(arr)     
        elif choice == 5:
            display(arr)  # Display the hash table      
        elif choice == 6:
            print("Exiting program...")
            break  
        else:
            print("Invalid choice. Please try again.")

main()



