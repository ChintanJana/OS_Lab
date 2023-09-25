#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>

#define FILE_SIZE (1 * 1024 * 1024 * 1024) /* 1GB */

int main() {
    int fd_fifo1, fd_fifo2;
    pid_t pid;
    struct timeval start_time, end_time;

    /* Create FIFOs */
    if (mkfifo("team1_fifo1", 0666) == -1 || mkfifo("team1_fifo2", 0666) == -1) {
        perror("mkfifo already exists");
        return 1;
    }

    /* Fork a child process */
    pid = fork();

    if (pid == 0) {
        /* Child process (Process 1) */
        gettimeofday(&start_time, NULL);

        /* Open FIFOs */
        fd_fifo1 = open("team1_fifo1", O_RDONLY);
        fd_fifo2 = open("team1_fifo2", O_WRONLY);

        /* Transfer file from Process 1 to Process 2 */
        char buffer[4096];
        ssize_t bytes_read, bytes_written;
        int file_fd = open("/tmp/team1_large_file.txt", O_RDONLY); /* Updated file path */
        while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0) {
            bytes_written = write(fd_fifo2, buffer, bytes_read);
            if (bytes_written != bytes_read) {
                perror("write");
                return 1;
            }
        }

        gettimeofday(&end_time, NULL);
        long long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000LL + (end_time.tv_usec - start_time.tv_usec);

        printf("Process 1 to Process 2 Transfer Time: %lld microseconds\n", elapsed_time);

        close(file_fd);
        close(fd_fifo1);
        close(fd_fifo2);
    } 
    else if (pid > 0) {
        /* Parent process (Process 2) */
        gettimeofday(&start_time, NULL);

        /* Open FIFOs */
        fd_fifo1 = open("team1_fifo1", O_WRONLY);
        fd_fifo2 = open("team1_fifo2", O_RDONLY);

        /* Transfer file from Process 2 to Process 1 */
        char buffer[4096];
        ssize_t bytes_read, bytes_written;
        int file_fd = open("/tmp/team1_received_file.txt", O_WRONLY | O_CREAT, 0666); /* Updated file path */
        while ((bytes_read = read(fd_fifo2, buffer, sizeof(buffer))) > 0) {
            bytes_written = write(file_fd, buffer, bytes_read);
            if (bytes_written != bytes_read) {
                perror("write");
                return 1;
            }
        }

        gettimeofday(&end_time, NULL);
        long long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000LL + (end_time.tv_usec - start_time.tv_usec);

        printf("Process 2 to Process 1 Transfer Time: %lld microseconds\n", elapsed_time);

        close(file_fd);
        close(fd_fifo1);
        close(fd_fifo2);

        int compare_result = system("diff -q /tmp/team1_large_file.txt /tmp/team1_received_file.txt");
        if (compare_result == 0) {
            printf("Sent and received files are the same!\n");
        } else {
            printf("Sent and received files are different.\n");
        }

        /* Clean up FIFOs */
        /* unlink("team1_fifo1"); */
        /* unlink("team1_fifo2"); */
    } 
    else {
        perror("fork");
        return 1;
    }

    return 0;
}

