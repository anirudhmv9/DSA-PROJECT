#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_MOVIES 5
#define MAX_SHOWTIMES 3
#define MAX_SEATS 100

struct Movie {
    char title[50];
    int duration;
};

struct Showtime {
    char time[10];
    bool seats[MAX_SEATS];
};

struct Reservation {
    char customerName[50];
    int movieIndex;
    int showtimeIndex;
    int seatNumber;
    float amountPaid;  // New field for payment
};

struct PaymentInfo {
    char cardNumber[20];
    char cardHolderName[50];
    char expiryDate[10];
    int cvv;
};

void displayMovies(struct Movie movies[], int numMovies) {
    printf("\nMovies available:\n");
    for (int i = 0; i < numMovies; ++i) {
        printf("%d. %s (%d mins)\n", i + 1, movies[i].title, movies[i].duration);
    }
}

void displayShowtimes(struct Showtime showtimes[], int numShowtimes) {
    printf("\nShowtimes available:\n");
    for (int i = 0; i < numShowtimes; ++i) {
        printf("%d. %s\n", i + 1, showtimes[i].time);
    }
}

void displaySeatingChart() {
    printf("\n  Seating Chart\n\n");

    for (int i = 1; i <= MAX_SEATS; ++i) {
        if (i % 10 == 0) {
            printf("\n");
        }

        printf("%3d ", i);
    }
    printf("\n");
}

float calculateTotalAmount(int movieDuration) {
    // Basic calculation: $0.1 per minute of movie duration
    return 0.1 * movieDuration;
}

void processPayment(struct PaymentInfo *paymentInfo, float totalAmount) {
    printf("\nPayment Details:\n");
    printf("Enter Card Number: ");
    scanf("%s", paymentInfo->cardNumber);

    printf("Enter Card Holder Name: ");
    scanf("%s", paymentInfo->cardHolderName);

    printf("Enter Expiry Date (MM/YYYY): ");
    scanf("%s", paymentInfo->expiryDate);

    printf("Enter CVV: ");
    scanf("%d", &paymentInfo->cvv);

    // Assume the payment is successful
    printf("\nPayment successful! Total Amount: $%.2f\n", totalAmount);
}

void makeReservation(struct Reservation reservations[], int *numReservations,
                     struct Movie movies[], int numMovies,
                     struct Showtime showtimes[], int numShowtimes) {
    char name[50];
    int movieIndex, showtimeIndex, seatNumber;

    printf("\nEnter your name: ");
    scanf("%s", name);

    displayMovies(movies, numMovies);
    printf("Enter the movie number: ");
    scanf("%d", &movieIndex);

    displayShowtimes(showtimes, numShowtimes);
    printf("Enter the showtime number: ");
    scanf("%d", &showtimeIndex);

    displaySeatingChart();
    printf("Enter the seat number: ");
    scanf("%d", &seatNumber);

    // Check if the seat is available
    if (seatNumber < 1 || seatNumber > MAX_SEATS || showtimes[showtimeIndex - 1].seats[seatNumber - 1]) {
        printf("\nInvalid seat selection or seat is already taken. Please choose a valid and available seat.\n");
        return;
    }

    // Reserve the seat
    showtimes[showtimeIndex - 1].seats[seatNumber - 1] = true;

    // Save the reservation details
    struct Reservation newReservation;
    strcpy(newReservation.customerName, name);
    newReservation.movieIndex = movieIndex - 1;
    newReservation.showtimeIndex = showtimeIndex - 1;
    newReservation.seatNumber = seatNumber;

    // Add the reservation to the array
    reservations[*numReservations] = newReservation;
    (*numReservations)++;

    // Display the total amount and proceed to payment
    float totalAmount = calculateTotalAmount(movies[newReservation.movieIndex].duration);
    printf("\nTotal Amount: $%.2f\n", totalAmount);

    // Payment
    struct PaymentInfo paymentInfo;
    processPayment(&paymentInfo, totalAmount);

    // Save payment details in the reservation
    newReservation.amountPaid = totalAmount;
    // Note: In a real-world scenario, you should securely handle and store payment information.

    printf("\nTicket booked successfully!\n");
}

void displayReservations(struct Reservation reservations[], int numReservations,
                         struct Movie movies[], struct Showtime showtimes[]) {
    printf("\nReservation Details:\n");
    for (int i = 0; i < numReservations; ++i) {
        struct Reservation currentReservation = reservations[i];
        printf("%s reserved a seat for %s (%d mins) at %s (Seat %d) - $%.2f paid\n",
               currentReservation.customerName,
               movies[currentReservation.movieIndex].title,
               movies[currentReservation.movieIndex].duration,
               showtimes[currentReservation.showtimeIndex].time,
               currentReservation.seatNumber,
               currentReservation.amountPaid);
    }
}

int main() {
    struct Movie movies[MAX_MOVIES] = {
        {"Inception", 150},
        {"The Shawshank Redemption", 142},
        {"The Dark Knight", 152},
        {"Pulp Fiction", 154},
        {"Forrest Gump", 142}
    };

    struct Showtime showtimes[MAX_SHOWTIMES] = {
        {"10:00 AM", {0}},
        {"02:30 PM", {0}},
        {"07:00 PM", {0}}
    };

    struct Reservation reservations[MAX_SEATS];
    int numReservations = 0;

    int choice;
    do {
        printf("\nMovie Reservation System\n");
        printf("1. Display Movies\n");
        printf("2. Display Showtimes\n");
        printf("3. Make a Reservation\n");
        printf("4. Display Reservations\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMovies(movies, MAX_MOVIES);
                break;
            case 2:
                displayShowtimes(showtimes, MAX_SHOWTIMES);
                break;
            case 3:
                makeReservation(reservations, &numReservations, movies, MAX_MOVIES, showtimes, MAX_SHOWTIMES);
                break;
            case 4:
                displayReservations(reservations, numReservations, movies, showtimes);
                break;
            case 5:
                printf("\nExiting the program. Thank you!\n");
                break;
            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}