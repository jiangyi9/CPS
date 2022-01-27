#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME   "/server"
#define MAX_MSG_SIZE 256
#define CLIENT_SIZE 16


void split_client_and_message(char *temp, char *client_pointer, char client_array[CLIENT_SIZE], char *message_buffer){

        // split the content before "#" to get client queue
        client_pointer = strtok(temp, "#"); 

        // copy the client_pointer to client_array
        strcpy(client_array, client_pointer);  /* Without this line, the system will print "bad file descriptor" error! */

        // split the content after "#" to get message
        message_buffer = strtok(NULL, "#"); 

        // print the received message on server
        printf( "%s: %s\n", client_pointer, message_buffer); 
}


int main (int argc, char **argv)
{
    // Initialization
    mqd_t qd_server, qd_client;

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    char client_array[CLIENT_SIZE]; // an array to store client queue
    char response[MAX_MSG_SIZE]; // a buffer to store response

    // open the server queue
    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_RDONLY | O_CREAT, 0600, &attr)) == -1) {
        perror ("Server: mq_open (server)");
        exit (1);
    }

    printf("Server begins to work!\n\n");

    while (1) {

        char *temp = (char *)malloc(sizeof(char)*(MAX_MSG_SIZE+CLIENT_SIZE+1)); // allocates 256+16+1 bytes of memory to temp
        char *client_pointer = (char *)malloc(sizeof(char)*CLIENT_SIZE); // a pointer to store client queue
        char *message_buffer = (char *)malloc(sizeof(char)*MAX_MSG_SIZE);; // a buffer to store message

        // receive the oldest message in server queue, and store it in (char*) temp.
        if (mq_receive (qd_server, temp, MAX_MSG_SIZE+CLIENT_SIZE+1, NULL) == -1) {
            perror ("Server: mq_receive");
            exit (1);
        }

        // split the content before and after "#" to get client queue and message, respectively
        split_client_and_message(temp, client_pointer, client_array, message_buffer);

        // free the space
        free(temp);
        free(client_pointer);
        free(message_buffer);

        // open the client queue
        if ((qd_client = mq_open (client_array, O_WRONLY)) == 1) {
            perror ("Server: Not able to open client queue");
            continue;
        }

        // create a response
        sprintf (response, "This is an ACK from server.");

        // send the response to client
        if (mq_send (qd_client, response, strlen(response)+1, 0) == -1) {
            perror ("Server: Not able to send message to client");
            continue;
        }
    }

    // close the client queue
    if (mq_close (qd_client) == -1) {
        perror ("Client: mq_close");
        exit (1);
    }

    // unlink the client queue
    if (mq_unlink (client_queue_name) == -1) {
        perror ("Client: mq_unlink");
        exit (1);
    }

    return 0;
}