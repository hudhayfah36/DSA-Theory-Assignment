#include <iostream>

using namespace std;

class Queue {
private:
    int* arr;
    int front, rear, capacity;

public:
    Queue(int size) {
        front = 0;
        rear = 0;
        arr = new int[capacity];
    }

    void enqueue(int carID) {
        if (rear == capacity) {
            cout << "Queue is full!\n";
            return;
        }
        arr[rear++] = carID;
    }

    int dequeue() {
        if (front == rear) {
            cout << "Queue is empty!\n";
            return -1;
        }
        return arr[front++];
    }

    bool isEmpty() {
        return front == rear;
    }
};

class Node {
public:
    int carID;
    Node* next;

    Node(int carID){
        this->carID = carID;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    void add(int carID) {
        Node* newNode = new Node(carID);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    int remove() {
        if (!head) {
            cout << "List is empty!\n";
            return -1;
        }
        int carID = head->carID;
        Node* temp = head;
        head = head->next;
        delete temp;
        return carID;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->carID << " ";
            temp = temp->next;
        }
    }
};

class ParkingLot {
private:
    int floors;
    int capacityPerFloor;
    int* parkedCars; // Single dynamic array to represent all floors
    Queue entryQueue; // Queue for cars waiting to enter
    LinkedList overflowWaitlist; // Linked list for overflow waitlist

    int getIndex(int floor, int spot) {
        return floor * capacityPerFloor + spot;
    }

public:
    ParkingLot(int floors, int capacityPerFloor) : floors(floors), capacityPerFloor(capacityPerFloor), entryQueue(100) {
        parkedCars = new int[floors * capacityPerFloor];
        for (int i = 0; i < floors * capacityPerFloor; ++i) {
            parkedCars[i] = -1; // Initialize with -1 to indicate empty spots
        }
    }

    ~ParkingLot() {
        delete[] parkedCars;
    }

    void addCar(int carID) {
        // Check for available space on floors
        for (int i = 0; i < floors * capacityPerFloor; ++i) {
            if (parkedCars[i] == -1) {
                parkedCars[i] = carID;
                cout << "Car " << carID << " parked on floor " << (i / capacityPerFloor) + 1 << "\n";
                return;
            }
        }
        
        // If no space, add to overflow waitlist
        overflowWaitlist.add(carID);
        cout << "Parking full! Car " << carID << " added to waitlist.\n";
    }

    void removeCar(int carID) {
        for (int i = 0; i < floors * capacityPerFloor; ++i) {
            if (parkedCars[i] == carID) {
                parkedCars[i] = -1;
                cout << "Car " << carID << " removed from floor " << (i / capacityPerFloor) + 1 << "\n";
                
                // If waitlist has cars, move first car to this spot
                if (!overflowWaitlist.isEmpty()) {
                    int waitlistCar = overflowWaitlist.remove();
                    parkedCars[i] = waitlistCar;
                    cout << "Car " << waitlistCar << " moved from waitlist to floor " << (i / capacityPerFloor) + 1 << "\n";
                }
                return;
            }
        }
        cout << "Car " << carID << " not found in the parking lot.\n";
    }

    void displayStatus() {
        cout << "\nParking Lot Status:\n";
        for (int i = 0; i < floors; ++i) {
            cout << "Floor " << i + 1 << ": ";
            for (int j = 0; j < capacityPerFloor; ++j) {
                int index = getIndex(i, j);
                if (parkedCars[index] != -1) {
                    cout << parkedCars[index] << " ";
                }
            }
            cout << "\n";
        }
        
        cout << "\nOverflow Waitlist: ";
        overflowWaitlist.display();
        cout << "\n";
    }

    void expandParking(int newFloors) {
        int* newParkedCars = new int[(floors + newFloors) * capacityPerFloor];
        for (int i = 0; i < (floors + newFloors) * capacityPerFloor; ++i) {
            if (i < floors * capacityPerFloor) {
                newParkedCars[i] = parkedCars[i];
            } else {
                newParkedCars[i] = -1; // Initialize new floors with -1
            }
        }

        delete[] parkedCars;
        parkedCars = newParkedCars;
        floors += newFloors;
        cout << "Parking lot expanded to " << floors << " floors.\n";
    }
};

int main() {
    ParkingLot lot(2, 3); // 2 floors, 3 cars per floor

    lot.addCar(101);
    lot.addCar(102);
    lot.addCar(103);
    lot.addCar(104);
    lot.addCar(105);
    lot.addCar(106);
    lot.addCar(107); // Should go to waitlist

    lot.displayStatus();

    lot.removeCar(103);
    lot.displayStatus();
    
    lot.expandParking(1);
    lot.addCar(108);
    lot.displayStatus();
    
    return 0;
}
