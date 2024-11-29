#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void merge(int g_a[], int l_i, int r_i, int m) {
    int l = l_i;
    int y = 0;
    int x = m + 1;
    int g_a_temp[16];
    while (l <= m && x <= r_i) {
        if (g_a[l] <= g_a[x]) {
            g_a_temp[y] = g_a[l];
            y++;
            l++;
        } else {
            g_a_temp[y] = g_a[x];
            y++;
            x++;
        }
    }
    while (l <= m) {
        g_a_temp[y] = g_a[l];
        y++;
        l++;
    }
    while (x <= r_i) {
        g_a_temp[y] = g_a[x];
        y++;
        x++;
    }
    for (int i = 0; i < y; i++) {
        g_a[l_i + i] = g_a_temp[i];
    }
}

void mergesort(int g_a[], int l_i, int r_i) {
    if (l_i >= r_i) {
        return;
    }

    int m = (r_i + l_i) / 2;

    int pipe1[2];
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    int l_i_merge = fork();
    if (l_i_merge == 0) {
        mergesort(g_a, l_i, m);
        write(pipe1[1], g_a + l_i, 1024);
        exit(0);
    }
    wait(NULL);
    int r_i_merge = fork();
    if (r_i_merge == 0) {
        mergesort(g_a, m + 1, r_i);
        write(pipe2[1], g_a + m + 1, 1024);
        exit(0);
    }
    wait(NULL);

    read(pipe1[0], g_a + l_i, 1024);
    read(pipe2[0], g_a + m + 1, 1024);


    merge(g_a, l_i, r_i, m);
}

int main() {
    int g_a[16] = {2, 1, 4, 3, 1, 3, 5, 6, 12, 43, 11, 32, 21, 43, 12, 54};
    int l_i = 0;
    int r_i = 15;
    printf("Unsorted Array is: ");
    for (int i = 0; i < 16; i++) {
        printf("%d ", g_a[i]);
    }
    printf("\n");
    mergesort(g_a, l_i, r_i);
    printf("Sorted Array is: ");
    for (int i = 0; i < 16; i++) {
        printf("%d ", g_a[i]);
    }
    printf("\n");
    return 0;
}
