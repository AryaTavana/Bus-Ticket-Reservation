#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Colors (ANSI) ---------- */
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

/* ---------- Constants ---------- */
#define MAX_SEATS 20
#define NAME_LEN 30
#define CODE_LEN 11

/* ---------- Struct ---------- */
typedef struct Seat {
    int seat_number;
    int reserved;                  // 0 = free, 1 = reserved
    char name[NAME_LEN];
    char national_code[CODE_LEN];
    struct Seat *next;
} Seat;

/* ---------- Function Declarations ---------- */
Seat *init_seats();
void show_seats(Seat *head);
void reserve_seat(Seat *head);
void cancel_reservation(Seat *head);
void search_passenger(const Seat *head);
Seat *find_seat_by_number(Seat *head, int seat_number);
int national_code_exists(const Seat *head, const char *code);
void menu();
void clear_input_buffer();

/* ---------- Clear Input Buffer ---------- */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ---------- Main ---------- */
int main() {
    Seat *seats = init_seats();
    int choice;

    do {
        menu();
        printf("Select an option: ");
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1:
                show_seats(seats);
                break;
            case 2:
                reserve_seat(seats);
                break;
            case 3:
                cancel_reservation(seats);
                break;
            case 4:
                search_passenger(seats);
                break;
            case 0:
                printf(RED "Exiting program...\n" RESET);
                break;
            default:
                printf(RED "Invalid option. Please try again.\n" RESET);
        }
    } while (choice != 0);

    return 0;
}

/* ---------- Menu ---------- */
void menu() {
    printf(CYAN "\n--- Bus Ticket Reservation System ---\n" RESET);
    printf("1. Show seat status\n");
    printf("2. Reserve a seat\n");
    printf("3. Cancel reservation\n");
    printf("4. Search passenger\n");
    printf(RED "0. Exit\n" RESET);
}

/* ---------- Initialize Seats (Linked List) ---------- */
Seat *init_seats() {
    Seat *head = NULL, *temp = NULL;

    for (int i = 1; i <= MAX_SEATS; i++) {
        Seat *new_seat = (Seat *) malloc(sizeof(Seat));
        new_seat->seat_number = i;
        new_seat->reserved = 0;
        strcpy(new_seat->name, "XX");
        strcpy(new_seat->national_code, "XX");
        new_seat->next = NULL;

        if (head == NULL) {
            head = new_seat;
        } else {
            temp->next = new_seat;
        }
        temp = new_seat;
    }
    return head;
}

/* ---------- Show Seats ---------- */
void show_seats(Seat *head) {
    printf(CYAN "\nSeat Status:\n" RESET);
    while (head != NULL) {
        if (head->reserved) {
            printf("Seat %2d : " GREEN "%s\n" RESET,
                   head->seat_number, head->name);
        } else {
            printf("Seat %2d : XX\n", head->seat_number);
        }
        head = head->next;
    }
}

/* ---------- Find Seat ---------- */
Seat *find_seat_by_number(Seat *head, int seat_number) {
    while (head != NULL) {
        if (head->seat_number == seat_number)
            return head;
        head = head->next;
    }
    return NULL;
}

/* ---------- Check Duplicate National Code ---------- */
int national_code_exists(const Seat *head, const char *code) {
    while (head != NULL) {
        if (head->reserved && strcmp(head->national_code, code) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

/* ---------- Reserve Seat ---------- */
void reserve_seat(Seat *head) {
    int seat_number;
    char name[NAME_LEN];
    char code[CODE_LEN];

    printf("Enter seat number (1-20): ");
    scanf("%d", &seat_number);
    clear_input_buffer();

    if (seat_number < 1 || seat_number > MAX_SEATS) {
        printf(RED "Invalid seat number.\n" RESET);
        return;
    }

    Seat *seat = find_seat_by_number(head, seat_number);

    if (seat->reserved) {
        printf(YELLOW "This seat is already reserved.\n" RESET);
        return;
    }

    printf("Enter passenger name: ");
    scanf("%29s", name);

    printf("Enter national code: ");
    scanf("%10s", code);

    if (national_code_exists(head, code)) {
        printf(YELLOW "This national code already exists.\n" RESET);
        return;
    }

    seat->reserved = 1;
    strcpy(seat->name, name);
    strcpy(seat->national_code, code);

    printf(GREEN "Seat reserved successfully.\n" RESET);
}

/* ---------- Cancel Reservation ---------- */
void cancel_reservation(Seat *head) {
    int seat_number;
    char code[CODE_LEN];

    printf("Enter seat number: ");
    scanf("%d", &seat_number);
    clear_input_buffer();

    Seat *seat = find_seat_by_number(head, seat_number);

    if (seat == NULL || !seat->reserved) {
        printf(RED "No reservation found for this seat.\n" RESET);
        return;
    }

    printf("Enter national code: ");
    scanf("%10s", code);

    if (strcmp(seat->national_code, code) != 0) {
        printf(YELLOW "National code does not match.\n" RESET);
        return;
    }

    seat->reserved = 0;
    strcpy(seat->name, "XX");
    strcpy(seat->national_code, "XX");

    printf(GREEN "Reservation cancelled successfully.\n" RESET);
}

/* ---------- Search Passenger ---------- */
void search_passenger(const Seat *head) {
    char key[NAME_LEN];

    printf("Enter passenger name or national code: ");
    scanf("%29s", key);

    while (head != NULL) {
        if (head->reserved &&
            (strcmp(head->name, key) == 0 ||
             strcmp(head->national_code, key) == 0)) {
            printf(GREEN "Passenger is seated at seat number %d.\n" RESET,
                   head->seat_number);
            return;
        }
        head = head->next;
    }

    printf(YELLOW "Passenger not found.\n" RESET);
}
