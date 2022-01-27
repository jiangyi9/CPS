#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME   "/server"
#define MAX_MSG_SIZE 256
#define CLIENT_SIZE 16


void concatenate_client_and_message(char *temp, char client_queue_name[CLIENT_SIZE], char *message_buffer){

    // concatenate client and message, dividing by '#'.
    strcat(temp, client_queue_name);
    strcat(temp, "#");
    strcat(temp, message_buffer);
    /* 
        Now, (char*) temp is like: "/cliend-2872#abcd",
        where "/cliend-2872" is the client queue, and "abcd" is the message. 
    */

}


int main (int argc, char **argv)
{
    // Initialization
    mqd_t qd_server, qd_client;
    char client_queue_name[CLIENT_SIZE];

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    char in_buffer [MAX_MSG_SIZE];
    char message_buffer [MAX_MSG_SIZE];

    // create the client queue
    sprintf (client_queue_name, "/client-%d", getpid ());

    // open the client queue
    if ((qd_client = mq_open (client_queue_name, O_RDONLY | O_CREAT, 0600, &attr)) == -1) {
        perror ("Client: mq_open (client)");
        exit (1);
    }

    // open the server queue
    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) {
        perror ("Client: mq_open (server)");
        exit (1);
    }

    printf("Client %s begins to work!\n\n", client_queue_name);
    printf("Please enter a message: ");

    while (1) {
        
        // input a message, and store it in (char*) message_buffer
        fgets(message_buffer, MAX_MSG_SIZE, stdin);

        // allocates 256+16+1 bytes of memory
        char *temp = (char *)malloc(sizeof(char)*(MAX_MSG_SIZE+CLIENT_SIZE+1));

        // concatenate client and message to (char*) temp
        concatenate_client_and_message(temp, client_queue_name, message_buffer);

        // send message to server
        if (mq_send (qd_server, temp, strlen(temp)+1, 0) == -1) {
            perror ("Client: Not able to send message to server");
            continue;
        }

        // free the space
        free(temp);

        // receive response from server queue
        if (mq_receive (qd_client, in_buffer, MAX_MSG_SIZE+1, NULL) == -1) {
            perror ("Client: mq_receive");
            exit (1);
        }

        // print the response
        printf ("%s\n\n", in_buffer);
        printf ("Please enter a message: ");
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