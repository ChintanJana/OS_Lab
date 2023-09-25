/* 
TEAM NUMBER - 1
MEMBERS -
ANANYA BHOWMICK       002111001016
ARIJIT SAHA           002111001118
ROHEENA PAL           002111001096
CHINTAN JANA          002111001115

ASSIGNMENT DETAILS - 
ASSIGNMENT NUMBER 3
Assignment Details - Create two processes. Transfer 1GB file from process1 to process2 using a
                     Socket. Now, transfer that file from process2 to process1 using the same
                     Socket.Now, compare the two files to make sure that the same file has returned back.
                     Also, print the time required to do this double transfer. Attach this output to the
                     source file as a comment. Please note that, you can see the socket which your program creates. There
                     are also various bash shell commands available to see the sockets created by
                     the program. So, once your program creates the socket, make sure you use
                     proper command to see the socket info and paste that output as a comment in
                     your source file.

COMPILATION COMMAND -
gcc -o 01_3 01_3.c
EXECUTION SEQUENCE -
dd if=/dev/zero of=/tmp/large_file.txt bs=1M count=1000
./01_3

OUTPUT - 
Netid         State          Recv-Q          Send-Q                                        Local Address:Port                    Peer Address:Port          Process
u_str         LISTEN         0               4096                                     /run/WSL/1_interop 19492                              * 0
u_str         LISTEN         0               4096                                     /run/WSL/1_interop 17617                              * 0
u_str         LISTEN         0               4096                        /var/run/dbus/system_bus_socket 153                                * 0
u_str         LISTEN         0               4096                                   /run/WSL/251_interop 17648                              * 0
u_seq         LISTEN         0               1                              /mnt/wslg/weston-notify.sock 20493                              * 0
u_str         LISTEN         0               128                         /mnt/wslg/runtime-dir/wayland-0 22545                              * 0
u_str         LISTEN         0               1                                         /tmp/.X11-unix/X0 22546                              * 0
u_dgr         UNCONN         0               0                              /var/run/chrony/chronyd.sock 136                                * 0
u_str         LISTEN         0               5                                          /tmp/socket_file 17825                              * 0
u_str         LISTEN         0               5                        /mnt/wslg/runtime-dir/pulse/native 21546                              * 0
u_str         LISTEN         0               5                                     /mnt/wslg/PulseServer 21551                              * 0
u_str         LISTEN         0               100                           /mnt/wslg/PulseAudioRDPSource 22574                              * 0
u_str         LISTEN         0               100                             /mnt/wslg/PulseAudioRDPSink 21559                              * 0
u_str         LISTEN         0               4096                                   /tmp/dbus-gsJEpzfQHo 152                                * 0
u_str         ESTAB          0               0                                                         * 155                                * 154
u_str         ESTAB          0               0                                                         * 19487                              * 19486
u_str         ESTAB          0               0                                                         * 17633                              * 17239
u_str         ESTAB          0               0                                                         * 17232                              * 17231
u_str         ESTAB          0               0                                                         * 22555                              * 22556
u_str         ESTAB          0               0                                         /tmp/.X11-unix/X0 20528                              * 21549
u_str         ESTAB          0               0                                                         * 154                                * 155
u_str         ESTAB          0               0                                                         * 19486                              * 19487
u_str         ESTAB          0               0                                                         * 21633                              * 17826
u_str         ESTAB          0               0                                                         * 17231                              * 17232
u_str         ESTAB          0               0                                                         * 22556                              * 22555
u_str         ESTAB          0               0                                                         * 21552                              * 17238
u_str         ESTAB          0               0                                                         * 22557                              * 22558
u_str         ESTAB          0               0                                                         * 17626                              * 0
u_str         UNCONN         0               0                                                         * 17824                              * 0
u_str         ESTAB          0               0                                          /tmp/socket_file 17826                              * 21633
u_str         ESTAB          0               0                                      /tmp/dbus-gsJEpzfQHo 17238                              * 21552
u_str         ESTAB          0               0                                                         * 22558                              * 22557
u_str         ESTAB          0               0                                                         * 21549                              * 20528
u_str         ESTAB          0               0                               /mnt/wslg/PulseAudioRDPSink 17239                              * 17633
Transfer Time: 10435 microseconds
Sent and received files are the same!
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> // Added for time measurement

#define CHUNK_SIZE 4096

int main(){
    int sockfd;
    // struct sockaddr_in serv_addr;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_addrlen = sizeof(client_addr);
    int newsockfd, listen_fd;

    char buffer[CHUNK_SIZE];
    ssize_t bytes_received;

	char* socket_path = "/tmp/socket_file";

    // Fork to create Process 2 (child process)
    pid_t child_pid = fork();

    if (child_pid == -1){
        perror("fork");
        return 1;
    }

    if (child_pid == 0){
        // This is Process 2 (child process)
        memset(&server_addr, 0, sizeof server_addr);
        server_addr.sun_family = AF_UNIX;
        strncpy(server_addr.sun_path, socket_path, sizeof(server_addr.sun_path) - 1);

        sleep(2); // wait for server to set up socket

        newsockfd = socket(AF_UNIX, SOCK_STREAM, 0);
        connect(newsockfd, (struct sockaddr *)&server_addr, sizeof server_addr);

        // Create a data structure (e.g., an array) to temporarily store chunks
        char data_store[CHUNK_SIZE];
        size_t data_store_size = 0;

        while ((bytes_received = read(newsockfd, (void *)buffer, CHUNK_SIZE)) > 0){
            if (write(newsockfd, (void *)buffer, bytes_received) < 0){
                perror("write to socket_recv failed in P2");
				exit(1);
			}
            if (bytes_received < CHUNK_SIZE)
                break;
        }
        // Close the socket and exit
        close(newsockfd);
    }
    else{
        // This is Process 1 (parent process)
        // Create a TCP socket
        sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sockfd == -1){
            perror("socket");
            return 1;
        }

        // Set up the server address structure
        memset(&server_addr, 0, sizeof server_addr);
        server_addr.sun_family = AF_UNIX;
        strncpy(server_addr.sun_path, socket_path, sizeof(server_addr.sun_path) - 1);

        if((listen_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
			perror("Listen failed");
			exit(1);
		}
        if((bind(listen_fd, (struct sockaddr *)&server_addr, sizeof server_addr)) < 0){
			perror("Bind failed");
			exit(1);
		}
		if(listen(listen_fd, 5) < 0){
			perror("Listening failed");
			exit(1);
		}
        newsockfd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addrlen);

        // Open the file to send (large_file.txt in /tmp)
        FILE *file = fopen("/tmp/large_file.txt", "rb");
        if (file == NULL){
            perror("fopen");
            return 1;
        }

        // Create and open the received file in /tmp
        FILE *received_file = fopen("/tmp/received_file.txt", "wb");
        if (received_file == NULL){
            perror("fopen received_file");
            return 1;
        }

        struct timeval start_time, end_time; // Added for time measurement

        gettimeofday(&start_time, NULL); // Start timing

		if(system("ss -x -a") < 0){ // For socket information
			perror("Internal error in command");
			exit(1);
		}

        // Send the file in chunks
        while ((bytes_received = fread(buffer, 1, CHUNK_SIZE, file)) > 0){
            if ((send(newsockfd, buffer, bytes_received, 0)) < 0){
                perror("Write to socket_path failed in P1");
				exit(1);
			}
            /* continuously read from the receive FIFO and keep writing to the new large file */
            if ((bytes_received = recv(newsockfd, buffer, CHUNK_SIZE, 0)) > 0){
                if (fwrite(buffer, 1, bytes_received, received_file) < 0){
                    perror("write to lfile_recv failed in P1");
					exit(1);
				}
            }
        }

        gettimeofday(&end_time, NULL); // End timing

        long long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000LL + (end_time.tv_usec - start_time.tv_usec);
        printf("Transfer Time: %lld microseconds\n", elapsed_time);

        if(fclose(file) < 0 || fclose(received_file) < 0 || close(newsockfd) < 0){ // Closing the files
			perror("Problem occured in closing the files");
			exit(1);
		}

        // Compare the sent and received files
        int compare_result = system("diff -q /tmp/large_file.txt /tmp/received_file.txt");
        if (compare_result == 0){
            printf("Sent and received files are the same!\n");
        }
        else{
            printf("Sent and received files are different.\n");
        }
		if(unlink(socket_path) < 0){ // Unlinking the socket file
			perror("Socket file could not be removed");
			exit(1);
		}
		// if(system("rm /tmp/socket_file") < 0){
		//	perror("Cannot remove socket file");
		//	exit(1);
		// }
    }
    return 0;
}
