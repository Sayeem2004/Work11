#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define INFILE "/dev/random"
#define OUTFILE "random.txt"
const int ARR_SIZE = 10;

unsigned int get_random_number(int fin) {
    unsigned int ret;
    int err = read(fin, &ret, sizeof(ret));
    if (err < 0) {
        printf("Error Found While Reading File INFILE, More Info Below");
        printf("%s\n", strerror(errno));
        return 0;
    }
    return ret;
}

int main() {
    printf("OPENING INFILE...\n");
    int fin1 = open(INFILE, O_RDONLY);
    if (fin1 == -1) {
        printf("Error Found While Opening File INFILE, More Info Below:\n");
        printf("%s\n", strerror(errno));
        return 0;
    }
    printf("\n");

    printf("GENERATING RANDOM NUMBERS...\n");
    unsigned int A[ARR_SIZE], i;
    for (i = 0; i < ARR_SIZE; i++) {
        A[i] = get_random_number(fin1);
        printf("\trandom %3u: %10u\n", i, A[i]);
    }
    printf("\n");

    printf("CREATING OUTFILE...\n");
    int fout = open(OUTFILE, O_WRONLY | O_CREAT, 0644);
    if (fout == -1) {
        printf("Error Found While Creating File OUTFILE, More Info Below:\n");
        printf("%s\n", strerror(errno));
        return 0;
    }
    printf("\n");

    printf("WRITING TO OUTFILE...\n");
    int err1 = write(fout, A, sizeof(A));
    if (err1 == -1) {
        printf("Error Found While Writing To File OUTFILE, More Info Below:\n");
        printf("%s\n", strerror(errno));
        return 0;
    }
    printf("\n");

    printf("OPENING OUTFILE...\n");
    int fin2 = open(OUTFILE, O_RDONLY);
    if (fin2 == -1) {
        printf("Error Found While Opening File OUTFILE, More Info Below:\n");
        printf("%s\n", strerror(errno));
        return 0;
    }
    printf("\n");

    printf("READING FROM OUTFILE...\n");
    unsigned int B[ARR_SIZE];
    int err2 = read(fin2, B, sizeof(B));
    if (err2 == 1) {
        printf("Error Found While Reading From File OUTFILE, More Info Below:\n");
        printf("%s\n", strerror(errno));
        return 0;
    }
    printf("\n");

    printf("VERIFYING READ CONTENTS...\n");
    for (i = 0; i < ARR_SIZE; i++) {
        printf("\trandom %3u: %10u\n", i, A[i]);
    }
    printf("\n");
}
