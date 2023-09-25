/* 
TEAM NUMBER - 1
MEMBERS -
ANANYA BHOWMICK       002111001016
ARIJIT SAHA           002111001118
ROHEENA PAL           002111001096
CHINTAN JANA          002111001115

ASSIGNMENT DETAILS - 
ASSIGNMENT NUMBER 4
Objective of this programming assignment is to use mmap() call and observe page-fault using the ‘sar’ command.

A big file (about 8GB) should be created using the ‘fallocate’ command. This big file should be written with a single integer value (say X) at a specific offset (say F). Both the integer value and the offset should be generated using a random function. Please do remember this random function should generate a quantity anywhere between 0 and 8G.

The above big file should also be mapped in the virtual address space using mmap() call. Once it is mapped, the data should be read from the same specific offset (F). Now, if the data read is X`; then verify that X and X` are the same. In case of verification failure, an error message is to be printed. Note that, the offset value F can be anywhere between 0 and 8G.

This sequence of writing and reading data to/from a specific offset and also verification should be put in a while loop to go forever.

In another terminal execute the command ‘sar –B 1 1000’ to observe for the page fault. This command should be started before the above program is put under execution. So, one can observe that the page faults are increasing, once the above program starts executing.

OUTPUT - The output of the program and the ‘sar’ command should be pasted as a comment at the beginning of the program file as indicated by the guidelines.

COMPILATION COMMAND -
gcc -o 01_4 01_4.c
./01_4

OUTPUT - 
Data written: 395839 at Offset: 0x1c87cbe4
Data read: 395839 at Offset: 0x1c87cbe4
Verification successful.

Data written: 652678 at Offset: 0x10a553480
Data read: 652678 at Offset: 0x10a553480
Verification successful.

Data written: 435514 at Offset: 0x130c78c70
Data read: 435514 at Offset: 0x130c78c70
Verification successful.

Data written: 415089 at Offset: 0x17f4285a8
Data read: 415089 at Offset: 0x17f4285a8
Verification successful.

Data written: 11154 at Offset: 0x6c2dc248
Data read: 11154 at Offset: 0x6c2dc248
Verification successful.

Data written: 721358 at Offset: 0x11f842230
Data read: 721358 at Offset: 0x11f842230
Verification successful.

Data written: 156253 at Offset: 0x11c2601c4
Data read: 156253 at Offset: 0x11c2601c4
Verification successful.

Data written: 534403 at Offset: 0x2bce4eb0
Data read: 534403 at Offset: 0x2bce4eb0
Verification successful.

Data written: 905992 at Offset: 0x101d70b1c
Data read: 905992 at Offset: 0x101d70b1c
Verification successful.

Data written: 459884 at Offset: 0x16595dffc
Data read: 459884 at Offset: 0x16595dffc
Verification successful.

Data written: 121490 at Offset: 0x3d059f8c
Data read: 121490 at Offset: 0x3d059f8c
Verification successful.

Data written: 994005 at Offset: 0x616bbf14
Data read: 994005 at Offset: 0x616bbf14
Verification successful.

Data written: 377990 at Offset: 0x783e0b8
Data read: 377990 at Offset: 0x783e0b8
Verification successful.

Data written: 960368 at Offset: 0x654194bc
Data read: 960368 at Offset: 0x654194bc
Verification successful.

Data written: 414905 at Offset: 0x14d0346f4
Data read: 414905 at Offset: 0x14d0346f4
Verification successful.

Data written: 168107 at Offset: 0x1626c56d4
Data read: 168107 at Offset: 0x1626c56d4
Verification successful.

Data written: 420978 at Offset: 0x2423a9d4
Data read: 420978 at Offset: 0x2423a9d4
Verification successful.

Data written: 878179 at Offset: 0x13a01f878
Data read: 878179 at Offset: 0x13a01f878
Verification successful.

Data written: 748482 at Offset: 0x16b4a9a28
Data read: 748482 at Offset: 0x16b4a9a28
Verification successful.

Data written: 69506 at Offset: 0x1521ba834
Data read: 69506 at Offset: 0x1521ba834
Verification successful.

Data written: 364560 at Offset: 0x15080a910
Data read: 364560 at Offset: 0x15080a910
Verification successful.

Data written: 332133 at Offset: 0x133e417b0
Data read: 332133 at Offset: 0x133e417b0
Verification successful.

Data written: 415391 at Offset: 0x16ee8d14
Data read: 415391 at Offset: 0x16ee8d14
Verification successful.

Data written: 212127 at Offset: 0x11780c170
Data read: 212127 at Offset: 0x11780c170
Verification successful.

Data written: 788886 at Offset: 0x160663480
Data read: 788886 at Offset: 0x160663480
Verification successful.

Data written: 572523 at Offset: 0x38cb1c24
Data read: 572523 at Offset: 0x38cb1c24
Verification successful.

COMMAND: ls -l
OUTPUT -
total 244
-rwxr-xr-x 1 roheenapal roheenapal      16704 Aug 26 12:19 01_4
-rw-r--r-- 1 roheenapal roheenapal      10401 Aug 26 12:24 01_4.c
-rw-r--r-- 1 roheenapal roheenapal 6435808145 Aug 26 12:19 big_file.txt

COMMAND TO CHECK PAGE FAULT: sar -B 1 1000
OUTPUT - 
Linux 5.15.90.1-microsoft-standard-WSL2 (LAPTOP-R7R9GS91)       08/26/23        _x86_64_        (8 CPU)

14:29:36     pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s    %vmeff
14:29:37         0.00      0.00     19.00      0.00     35.00      0.00      0.00      0.00      0.00
14:29:38         0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00
14:29:39         0.00      0.00      0.00      0.00      2.00      0.00      0.00      0.00      0.00
14:29:40         0.00      0.00      1.00      0.00      0.00      0.00      0.00      0.00      0.00
14:29:41         0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00
14:29:42         0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00
14:29:43         0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00
14:29:44         0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00
14:29:45         0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00
14:29:46         0.00    432.00    270.00      0.00    147.00      0.00      0.00      0.00      0.00
14:29:47         0.00      0.00     10.00      0.00      1.00      0.00      0.00      0.00      0.00
14:29:48         0.00      0.00     10.00      0.00      0.00      0.00      0.00      0.00      0.00
14:29:49         0.00      0.00     10.00      0.00      0.00      0.00      0.00      0.00      0.00
14:29:50         0.00      0.00     10.00      0.00      7.00      0.00      0.00      0.00      0.00
14:29:51         0.00    440.00     10.00      0.00    188.00      0.00      0.00      0.00      0.00
14:29:52         0.00      0.00     10.00      0.00      0.00      0.00      0.00      0.00      0.00
14:29:53         0.00      0.00     10.00      0.00      0.00      0.00      0.00      0.00      0.00
14:29:54         0.00    392.00      9.00      0.00      1.00      0.00      0.00      0.00      0.00
14:29:55         0.00      0.00      9.90      0.00      3.96      0.00      0.00      0.00      0.00
14:29:56         0.00     64.00     10.00      0.00      0.00      0.00      0.00      0.00      0.00
^C
Average:         0.00     66.37     19.44      0.00     19.24      0.00      0.00      0.00      0.00
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>

#define FILE_SIZE (8LL * 1024 * 1024 * 1024) // 8GB

void generate_random_offset_and_value(off_t *offset, int *value) {
    // generates two 32-bit random numbers and combine them to form a 64-bit number
    *offset = (((off_t)rand() << 32) | rand()) % FILE_SIZE;

	// makes sure the offset is a multiple of sizeof(int)
    *offset -= *offset % sizeof(int);
	
	// generates a random value between 0 and 999999
    *value = rand() % 1000000;
}

int main() {
    srand(time(NULL)); // seeds the random number generator with the current time

    // allocates the file size on the disk
    if ((system("fallocate -l 8G big_file.txt")) == -1) {
        perror("Could not allocate the file size");
        exit(1);
    }
	
	// O_RDWR to open the file for both reading and writing
	// O_CREAT to create the file if it doesn't exist
	// O_TRUNC to make sure that if the file exists and is writable, it will be cleared when opened.
	int fd = open("big_file.txt", O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1) { // checks whether the file is created
        perror("File could not be created or opened or properly truncated");
        exit(1);
    }

    // creates a memory mapping of the file
    int *map = (int *)mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    while (1) {
        off_t offset;
        int value, read_value;

        // generates a random offset and value
        generate_random_offset_and_value(&offset, &value);

		// writes the generated value to the file at the specific offset using pwrite
        ssize_t bytes_written = pwrite(fd, &value, sizeof(value), offset);
        if (bytes_written != sizeof(value)) {
            perror("pwrite");
            exit(1);
        }
		else{
			printf("Data written: %d at Offset: 0x%" PRIx64 "\n", value, (uint64_t)offset);
		}

        // reads the value from the mapped memory at the same offset
        read_value = map[offset / sizeof(int)];
		printf("Data read: %d at Offset: 0x%" PRIx64 "\n", read_value, (uint64_t)offset);
		
		// verifies whether the written value and the read value are the same
        if (read_value != value) {
            fprintf(stderr, "Verification failed: Expected %d, Read %d\n", value, read_value);
        } 
		else {
            printf("Verification successful.\n\n");
        }

        usleep(100000); // sleep for 100 millisecond before the next iteration
    }

    // unmaps the memory
	if (munmap(map, FILE_SIZE) == -1) {
        perror("Could not free the memory space");
        exit(1);
    }

    // closes the file
    if (close(fd) == -1) {
        perror("Could not close the file");
        exit(1);
    }

    return 0;
}
