//Ali Burak Pekýþýk - 22118080062

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20 //Defining fixed size of 1D array.

//Function that adds values to circular queues by taking their name as parameter, rear and front values.
//Based on Lecture 5 notes.
void enqueue(int intArray[], char queue_num[], int value, int *rear, int *front, int *front_other, int *rear_other) {
    *rear = (*rear + 1) % MAX_SIZE; //Pointer rear increases by one for adding values to queue and also used for checking if there is any conflict between two queues.
    if (*front == *rear || *front == *front_other || *rear == *rear_other) { //Checking if queue is full by comparing front and rear pointers and also this is working on 1D so we have to check if there is any conflict between two queue.
        printf("Queue %s is full\n", queue_num); //Printing "Queue is full" if the current queue is full.
        *rear = (*rear - 1) % MAX_SIZE; //Because we did not add any new values we have to decrease rear point by 1.
    } else {
        printf("%d\tis inserted to queue %s\n", value, queue_num); //Queue that we currently working on and added value is printed out.
        intArray[*rear] = value; //New value added to the rear pointer index of our 1D integer Array called intArray.
    }
}

//Function that deletes last of of queue by making that index unreachable.
//Based on Lecture 5 notes.
void dequeue(int intArray[], char queue_num[], int *rear, int *front, int *front_other, int *rear_other) {
    if (*front == *rear || *front == *front_other || *rear == *rear_other) { //Checking if queue is empty by comparing front and rear pointers and also this is working on 1D so we have to check if there is any conflict between two queue.
        printf("Queue %s is empty\n", queue_num); //Checking if queue is empty by comparing front and rear pointers and also this is working on 1D so we have to check if there is any conflict between two queue.
    } else {
        *front = (*front + 1) % MAX_SIZE; //To delete value we increase front value by 1 so we made unwanted value unreachable.
        printf("%d\tis deleted from queue %s\n", intArray[*front], queue_num); //Queue that we currently working on and deleted value is printed out.
    }
}

//Function that prints the wanted queue's elements.
void print(int intArray[], char queue_num[], int *rear, int *front) {
    int size = (*rear - *front + MAX_SIZE) % MAX_SIZE; //Calculating size of queue by substituting rear and front pointers. MAX_SIZE is used because we are working on circular queues.
    printf("QUEUE:%-9s FRONT:%-4d REAR:%-4d SIZE:%d\n", queue_num, *front, *rear, size); //Printing QUEUE Name, FRONT, REAR and SIZE values. Values with - are used for \t.

    if (size == 0) { //If working queue does not have any values. It is going to print NO_CONTENT;
        printf("NO_CONTENT\n");
    } else { //If working queue has values. Then they are going to be printed with do-while loop.
        int i = *front; //Because front value gets the first value we equal i with front pointer.

        do {
            printf("%d\t", intArray[i+1]); //Because we use pointers the first index of array will be an address. So we increase i by 1.
            i = (i + 1) % MAX_SIZE; //i is increased by 1 because, we need to get to the next index.
        } while (i != *rear);
        printf("\n");
    }
}

int main() {
    char command[20]; //Char array that keeps if the command is ENQUEUE, DEQUEUE or PRINT.
    char queue_num[20]; //Char array that keeps if the queue we want to work is FIRST or SECOND.
    int value; //Integer value that keeps ENQUEUE value.
    int intArray[MAX_SIZE]; //1D array that keeps 2 circular queue's values with size of MAX_SIZE.
    int first_front = 0; //FIRST queue's front value. Used for enqueue, dequeue and print functions.
    int first_rear = 0; //FIRST queue's rear value. Used for enqueue, dequeue and print functions.
    int second_front = 10; //SECOND queue's front value. Used for enqueue, dequeue and print functions.
    int second_rear = 10; //SECOND queue's rear value. Used for enqueue, dequeue and print functions.

    FILE *file; //FILE pointer used for taking values of input.txt file.
    file = fopen("input.txt", "r"); //Opening input.txt file for accessing content.

    if (file == NULL) { //Printing out an error if input.txt file is not found.
        printf("File not found.\n");
        return 1;
    }

    while (fscanf(file, "%s %s %d", command, queue_num, &value) != EOF) { //Taking values of input.txt by dividing It into parts using fscanf. EOF is used for if we reached the last row of input.txt file.
        if (strcmp(command, "ENQUEUE") == 0) { //Checking if the row we are currently in contains ENQUEUE function. Using strcmp function.
            if (strcmp(queue_num, "FIRST") == 0) { //If the queue name is FIRST for then we call enqueue function for queue named FIRST.
                enqueue(intArray, queue_num, value, &first_rear, &first_front, &second_front, &second_rear);
            } else if (strcmp(queue_num, "SECOND") == 0) { //If the queue name SECOND is for then we call enqueue function for queue named SECOND.
                enqueue(intArray, queue_num, value, &second_rear, &second_front, &first_front, &first_rear);
            }
        } else if (strcmp(command, "DEQUEUE") == 0) { //Checking if the row we are currently in contains dequeue function. Using strcmp function.
            if (strcmp(queue_num, "FIRST") == 0) { //If the queue name is FIRST for then we call dequeue function for queue named FIRST.
                dequeue(intArray, queue_num, &first_rear, &first_front, &second_front, &second_rear);
            } else if (strcmp(queue_num, "SECOND") == 0) { //If the queue name is SECOND for then we call dequeue function for queue named SECOND.
                dequeue(intArray, queue_num, &second_rear, &second_front, &first_front, &first_rear);
            }
        } else if (strcmp(command, "PRINT") == 0) { //Checking if the row we are currently in contains PRINT function. Using strcmp function.
            if (strcmp(queue_num, "FIRST") == 0) { //If the queue name is first for then we call print function for queue named FIRST.
                print(intArray, queue_num, &first_rear, &first_front);
            } else if (strcmp(queue_num, "SECOND") == 0) { //If the queue name is second for then we call print function for queue named SECOND.
                print(intArray, queue_num, &second_rear, &second_front);
            }
        }
    }

    fclose(file); //Closing input.txt file because we do not need It anymore.
    return 0; //Closing the code by returning 0.
}
