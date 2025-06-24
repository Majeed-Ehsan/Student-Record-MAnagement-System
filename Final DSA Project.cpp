#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;


class Student;
class BSTNode;
class BST;
class QueueNode;
class Queue;

// Student Class 
class Student {
private:
    string name;
    int rollNumber;
    float gpa;

public:
    Student();
    Student(string name, int rollNumber, float gpa);
    void input();
    void display() const;
    int getRollNumber() const;
    string getName() const;
    float getGPA() const;
    void setName(string name);
    void setRollNumber(int rollNumber);
    void setGPA(float gpa);
};

//  BST Node 
class BSTNode {
public:
    Student data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Student student);
};

//  BST Class 
class BST {
private:
    BSTNode* root;
    BSTNode* insert(BSTNode* node, Student student);
    void inOrder(BSTNode* node) const;
    Student* search(BSTNode* node, int rollNumber);
    BSTNode* remove(BSTNode* node, int rollNumber);
    BSTNode* findMin(BSTNode* node);
    void deleteTree(BSTNode* node);
    void collectAll(BSTNode* node, vector<Student>& students) const;

public:
    BST();
    ~BST();
    void insert(Student student);
    void inOrderTraversal() const;
    Student* searchByRoll(int rollNumber);
    void remove(int rollNumber);
    vector<Student> getAllStudents() const;
};

//  Queue Node 
class QueueNode {
public:
    int data;
    QueueNode* next;
    QueueNode(int data);
};

//  Queue Class 
class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
    void clear();

public:
    Queue();
    ~Queue();
    void enqueue(int data);
    int dequeue();
    bool isEmpty() const;
};

// Utility Function Declarations
void bubbleSortByRoll(vector<Student>& students);
void mergeSortByName(vector<Student>& students, int left, int right);
void mergeByName(vector<Student>& students, int left, int mid, int right);
Student* linearSearchByName(vector<Student>& students, const string& name);
int binarySearchByRoll(vector<Student>& students, int rollNumber);

//  Student Implementation 
Student::Student() {
    name = "";
    rollNumber = 0;
    gpa = 0.0;
}

Student::Student(string name, int rollNumber, float gpa) {
    this->name = name;
    this->rollNumber = rollNumber;
    this->gpa = gpa;
}

void Student::input() {
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Roll Number: ";
    cin >> rollNumber;
    cout << "Enter GPA: ";
    cin >> gpa;
    cin.ignore(); 
}

void Student::display() const {
    cout << "\nName: " << name << "\nRoll Number: " << rollNumber << "\nGPA: " << gpa << "\n";
}

int Student::getRollNumber() const {
    return rollNumber;
}

string Student::getName() const {
    return name;
}

float Student::getGPA() const {
    return gpa;
}

void Student::setName(string name) {
    this->name = name;
}

void Student::setRollNumber(int rollNumber) {
    this->rollNumber = rollNumber;
}

void Student::setGPA(float gpa) {
    this->gpa = gpa;
}

// --- BSTNode Implementation ---
BSTNode::BSTNode(Student student) {
    data = student;
    left = right = NULL;
}

//  BST Implementation 
BST::BST() {
    root = NULL;
}

BST::~BST() {
    deleteTree(root);
}

void BST::deleteTree(BSTNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void BST::insert(Student student) {
    root = insert(root, student);
}

BSTNode* BST::insert(BSTNode* node, Student student) {
    if (!node)
        return new BSTNode(student);

    if (student.getRollNumber() < node->data.getRollNumber())
        node->left = insert(node->left, student);
    else
        node->right = insert(node->right, student);

    return node;
}

void BST::inOrderTraversal() const {
    inOrder(root);
}

void BST::inOrder(BSTNode* node) const {
    if (!node) return;
    inOrder(node->left);
    node->data.display();
    inOrder(node->right);
}

Student* BST::searchByRoll(int rollNumber) {
    return search(root, rollNumber);
}

Student* BST::search(BSTNode* node, int rollNumber) {
    if (!node) return NULL;

    if (rollNumber == node->data.getRollNumber())
        return &node->data;
    else if (rollNumber < node->data.getRollNumber())
        return search(node->left, rollNumber);
    else
        return search(node->right, rollNumber);
}

void BST::remove(int rollNumber) {
    root = remove(root, rollNumber);
}

BSTNode* BST::remove(BSTNode* node, int rollNumber) {
    if (!node) return NULL;

    if (rollNumber < node->data.getRollNumber()) {
        node->left = remove(node->left, rollNumber);
    } else if (rollNumber > node->data.getRollNumber()) {
        node->right = remove(node->right, rollNumber);
    } else {
        // Node to be deleted found
        if (!node->left && !node->right) {
            delete node;
            return NULL;
        } else if (!node->left) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        } else {
            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data.getRollNumber());
        }
    }
    return node;
}

BSTNode* BST::findMin(BSTNode* node) {
    while (node->left)
        node = node->left;
    return node;
}

vector<Student> BST::getAllStudents() const {
    vector<Student> students;
    collectAll(root, students);
    return students;
}

void BST::collectAll(BSTNode* node, vector<Student>& students) const {
    if (!node) return;
    collectAll(node->left, students);
    students.push_back(node->data);
    collectAll(node->right, students);
}

// --- QueueNode Implementation ---
QueueNode::QueueNode(int data) {
    this->data = data;
    this->next = NULL;
}

//  Queue Implementation 
Queue::Queue() {
    front = rear = NULL;
}

Queue::~Queue() {
    clear();
}

void Queue::enqueue(int data) {
    QueueNode* newNode = new QueueNode(data);
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

int Queue::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty. Cannot dequeue.\n";
        return -1;
    }
    QueueNode* temp = front;
    int data = temp->data;
    front = front->next;

    if (front == NULL)
        rear = NULL;

    delete temp;
    return data;
}

bool Queue::isEmpty() const {
    return front == NULL;
}

void Queue::clear() {
    while (!isEmpty())
        dequeue();
}

//  Utility Functions Implementation 
void bubbleSortByRoll(vector<Student>& students) {
    int n = students.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (students[j].getRollNumber() > students[j + 1].getRollNumber()) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

void mergeByName(vector<Student>& students, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Student> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = students[left + i];
    for (int i = 0; i < n2; ++i) R[i] = students[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].getName() <= R[j].getName()) {
            students[k++] = L[i++];
        } else {
            students[k++] = R[j++];
        }
    }

    while (i < n1) students[k++] = L[i++];
    while (j < n2) students[k++] = R[j++];
}

void mergeSortByName(vector<Student>& students, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSortByName(students, left, mid);
        mergeSortByName(students, mid + 1, right);
        mergeByName(students, left, mid, right);
    }
}

Student* linearSearchByName(vector<Student>& students, const string& name) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].getName() == name)
            return &students[i];
    }
    return NULL;
}

int binarySearchByRoll(vector<Student>& students, int rollNumber) {
    int left = 0, right = students.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int midRoll = students[mid].getRollNumber();

        if (midRoll == rollNumber)
            return mid;
        else if (midRoll < rollNumber)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

// Main Program 
void menu() {
    cout << "\n--- Student Record Management System ---\n";
    cout << "1. Add Student Record\n";
    cout << "2. Display All Records (In-order Traversal)\n";
    cout << "3. Search by Roll Number (Binary Search)\n";
    cout << "4. Search by Name (Linear Search)\n";
    cout << "5. Sort by Name (Merge Sort)\n";
    cout << "6. Sort by Roll Number (Bubble Sort)\n";
    cout << "7. Update Student Record\n";
    cout << "8. Queue Deletion Request\n";
    cout << "9. Execute Deletion Requests\n";
    cout << "10. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    BST bst;
    Queue deletionQueue;

    int choice;
    do {
        menu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                Student s;
                s.input();
                bst.insert(s);
                break;
            }
            case 2:
                cout << "\n--- Student Records (In-order BST Traversal) ---\n";
                bst.inOrderTraversal();
                break;
            case 3: {
                int roll;
                cout << "Enter Roll Number to Search: ";
                cin >> roll;
                Student* found = bst.searchByRoll(roll);
                if (found) {
                    found->display();
                } else {
                    cout << "Student not found.\n";
                }
                break;
            }
            case 4: {
                string name;
                cout << "Enter Name to Search: ";
                getline(cin, name);
                vector<Student> allStudents = bst.getAllStudents();
                Student* found = linearSearchByName(allStudents, name);
                if (found) {
                    found->display();
                } else {
                    cout << "Student not found.\n";
                }
                break;
            }
            case 5: {
                vector<Student> all = bst.getAllStudents();
                mergeSortByName(all, 0, all.size() - 1);
                cout << "\n--- Sorted by Name (Merge Sort) ---\n";
                for (size_t i = 0; i < all.size(); i++) all[i].display();
                break;
            }
            case 6: {
                vector<Student> all = bst.getAllStudents();
                bubbleSortByRoll(all);
                cout << "\n--- Sorted by Roll Number (Bubble Sort) ---\n";
                for (size_t i = 0; i < all.size(); i++) all[i].display();
                break;
            }
            case 7: {
                int roll;
                cout << "Enter Roll Number to Update: ";
                cin >> roll;
                cin.ignore();
                Student* s = bst.searchByRoll(roll);
                if (s) {
                    cout << "Current Record:\n";
                    s->display();
                    cout << "Enter Updated Details:\n";
                    s->input();
                    cout << "Record Updated Successfully.\n";
                } else {
                    cout << "Student not found.\n";
                }
                break;
            }
            case 8: {
                int roll;
                cout << "Enter Roll Number to Queue for Deletion: ";
                cin >> roll;
                deletionQueue.enqueue(roll);
                cout << "Request Queued.\n";
                break;
            }
            case 9: {
                cout << "\n--- Processing Deletion Requests ---\n";
                while (!deletionQueue.isEmpty()) {
                    int roll = deletionQueue.dequeue();
                    cout << "Deleting Roll Number: " << roll << "\n";
                    bst.remove(roll);
                }
                cout << "All queued deletions completed.\n";
                break;
            }
            case 10:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 10);

    return 0;
}
