#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 8

int pegs[3][MAX_DISKS];
int pegCount[3] = {0, 0, 0};
int numDisks;
int step = 1;


void printRepeated(char c, int n) {
    for (int i = 0; i < n; i++) putchar(c);
}

void printPegs() {
    int maxWidth = numDisks * 2 - 1;

    for (int level = numDisks - 1; level >= 0; level--) {
        for (int peg = 0; peg < 3; peg++) {
            int diskVal = (level < pegCount[peg]) ? pegs[peg][level] : 0;

            if (diskVal > 0) {
                int diskWidth = diskVal * 2 - 1;
                int left = (maxWidth - diskWidth) / 2;
                int right = maxWidth - left - diskWidth;
                printRepeated(' ', left);
                printRepeated('|', diskWidth);
                printRepeated(' ', right);
            } else {
                printRepeated(' ', maxWidth);
            }

            if (peg < 2) printRepeated(' ', 3);
        }
        putchar('\n');
    }

    for (int peg = 0; peg < 3; peg++) {
        printRepeated('_', maxWidth);
        if (peg < 2) printRepeated(' ', 3);
    }
    putchar('\n');

    for (int peg = 0; peg < 3; peg++) {
        int left = (maxWidth - 1) / 2;
        printRepeated(' ', left);
        putchar('A' + peg);
        printRepeated(' ', maxWidth - left - 1);
        if (peg < 2) printRepeated(' ', 3);
    }
    putchar('\n');
    putchar('\n');
}

int moveDisk(int from, int to) {
    if (pegCount[from] == 0) {
        printf(" Invalid move! Peg %c is empty.\n", 'A' + from);
        return 0;
    }
    if (pegCount[to] > 0 && pegs[from][pegCount[from] - 1] > pegs[to][pegCount[to] - 1]) {
        printf(" Invalid move! Cannot place larger disk on smaller disk.\n");
        return 0;
    }

    pegs[to][pegCount[to]++] = pegs[from][--pegCount[from]];
    printf("Step %d: Move disk from %c to %c\n", step++, 'A' + from, 'A' + to);
    printPegs();
    return 1;
}

int isSolved() {
    return pegCount[2] == numDisks;  
}

int main() {
    printf("===== Tower of Hanoi Puzzle =====\n");
    printf("Enter number of disks (1-%d): ", MAX_DISKS);
    if (scanf("%d", &numDisks) != 1) return 1;
    if (numDisks < 1 || numDisks > MAX_DISKS) {
        printf("Invalid number of disks. Choose between 1 and %d.\n", MAX_DISKS);
        return 1;
    }

    for (int i = numDisks; i > 0; i--) pegs[0][pegCount[0]++] = i;

    printf("\nInitial State:\n");
    printPegs();

    while (!isSolved()) {
        char from, to;
        printf("Enter move (e.g., A C): ");

        int read = scanf(" %c %c", &from, &to);
        if (read != 2) {
            printf(" Invalid input! Please enter two pegs like: A C\n");
            while (getchar() != '\n');
            continue;
        }

        if (from < 'A' || from > 'C' || to < 'A' || to > 'C') {
            printf(" Invalid input! Use A, B, C.\n");
            continue;
        }

        if (from == to) {
            printf(" Invalid move! Source and destination cannot be the same.\n");
            continue;
        }

        moveDisk(from - 'A', to - 'A');
    }

    printf("\n  Congratulations! You solved the puzzle in %d steps!\n", step - 1);
    return 0;
}