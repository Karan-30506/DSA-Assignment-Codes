#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// In this Implementation the Linked List is Initialized with Sample Data
// But my Code also works with an empty Linked List
// Initialise an Empty Linked List by changing head to -1 in main function

#define MAX 100

int data[MAX];
int next[MAX];
int head = -1;
int avail_id = 0;

void init_FreeList() {
    for (int i = 0; i < MAX - 1; i++) {
        next[i] = i + 1;
    }
    next[MAX - 1] = -1;
    avail_id = 0;
    head = -1;
}

int init_Node() {
    if (avail_id == -1) {
        printf("No free space available\n");
        exit(1);
    }
    int newNode = avail_id;
    avail_id = next[avail_id];
    next[newNode] = -1;
    return newNode;
}

void freeNode(int index) {
    next[index] = avail_id;
    avail_id = index;
}

int convertArrtoLL(int *a, int len) {
    if (len == 0) {
        head = -1;
        return head;
    }

    head = init_Node();
    int mover = head;
    data[mover] = a[0];

    for (int i = 1; i < len; i++) {
        next[mover] = init_Node();
        mover = next[mover];
        data[mover] = a[i];
    }
    next[mover] = -1;

    return head;
}

void TraverseLL(int head) {
    if (head == -1) {
        printf("(NULL)\n");
        return;
    }
    int temp = head;
    while (temp != -1) {
        printf(" %d -->", data[temp]);
        temp = next[temp];
    }
    printf("(NULL)\n");
}

int LengthofLL(int head) {
    int count = 0;
    int temp = head;
    while (temp != -1) {
        count++;
        temp = next[temp];
    }
    return count;
}

int giveRandomNode(int head) {
    int len = LengthofLL(head);
    if (len == 0) return -1;

    srand(time(NULL));
    int ran_num = rand() % len;

    int temp = head;
    for (int i = 0; i < ran_num; i++) {
        temp = next[temp];
    }
    return temp;
}

int insertAtBeginning(int head, int value) {
    int newHead = init_Node();
    data[newHead] = value;
    next[newHead] = head;
    return newHead;
}

void insertAfterNode(int gnode, int value) {
    if (gnode == -1) {
        printf("Invalid Node!\n");
        return;
    }
    int toInsert = init_Node();
    data[toInsert] = value;
    next[toInsert] = next[gnode];
    next[gnode] = toInsert;
}

int deleteFromBeginning(int head) {
    if (head == -1) {
        printf("Linked List is Empty\n");
        return head;
    }
    int newHead = next[head];
    freeNode(head);
    return newHead;
}

void deleteAfterNode(int gnode) {
    if (gnode == -1 || next[gnode] == -1) {
        printf("Given Node is the Last Node\n");
        printf("Deletion Failed\n");
        return;
    }
    int toDelete = next[gnode];
    next[gnode] = next[toDelete];
    freeNode(toDelete);
}

int main() {
    init_FreeList();

    int sample_data[] = {30, 24, 7, 31, 9, 16, 100};
    int len = sizeof(sample_data) / sizeof(sample_data[0]);

    head = convertArrtoLL(sample_data, len);
    printf("Given Linked List:- ");
    TraverseLL(head);

    int value = 0;
    int ran_node = -1;

    printf("\nChoose an Operation To Perform:-\n");
    printf("1) Traverse and print the Elements of the Linked List\n");
    printf("2) Insert an Element at the Beginning of the LL\n");
    printf("3) Insert an Element after a given Node in the LL\n");
    printf("4) Delete an Element in the Beginning of the LL\n");
    printf("5) Delete an Element after a given Node in the LL\n");
    printf("6) Print the Length of the Linked List\n");
    printf("7) Exit the Program\n");

    int user_choice = 0;
    while (printf("\nEnter Your Choice: ") && (scanf("%d", &user_choice) == 1)) {
        switch (user_choice) {
            case 1:
                printf("\nLinked List:- ");
                TraverseLL(head);
                break;
            case 2:
                printf("\nEnter the Value to Insert: ");
                scanf("%d", &value);
                head = insertAtBeginning(head, value);
                printf("\nUpdated LL:- ");
                TraverseLL(head);
                break;
            case 3:
                printf("\nLinked List: ");
                TraverseLL(head);
                ran_node = giveRandomNode(head);
                printf("Given random Node with data = %d\n", data[ran_node]);
                printf("\nEnter the Value to Insert: ");
                scanf("%d", &value);
                insertAfterNode(ran_node, value);
                printf("\nUpdated LL:- ");
                TraverseLL(head);
                break;
            case 4:
                head = deleteFromBeginning(head);
                printf("\nUpdated LL:- ");
                TraverseLL(head);
                break;
            case 5:
                printf("\nLinked List: ");
                TraverseLL(head);
                ran_node = giveRandomNode(head);
                printf("Given random Node with data = %d\n", data[ran_node]);
                deleteAfterNode(ran_node);
                printf("\nUpdated LL:- ");
                TraverseLL(head);
                break;
            case 6:
                printf("\nThe Length of the Linked List is: %d\n", LengthofLL(head));
                break;
            case 7:
                printf("\nProgram Terminated\n");
                exit(0);
            default:
                printf("\nInvalid Input\n");
                break;
        }
    }
    return 0;
}
