//
// Created by Leticia Mejia/Marcel Ghisi.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions_structures.h"
#include "run_functions.h"

 int main() {
    t_node *nodes = NULL;
    int fd;
    char* command;
    int status_cmd;

    fd = open("file_", O_RDONLY);
    printf("%s\n", fd == -1 ? "No initial data founded" : "Reading existing data");
    if (fd != -1) {
        insert_to_backup(fd, &nodes);
    }
    printf("Type 'quit' to save and leave the blockchain.\n");
    while(true){
        command = start_prompt(nodes);
        status_cmd = lsh_execute(command, &nodes);
        free(command);
        if (status_cmd == QUIT) {
            send_status(status_cmd);
            return 0;
        }
        if (status_cmd != 0) {
            printf("NOK: ");
            send_status(status_cmd);
        }
        else {
            printf("OK\n");
        }
    }

    free_node(nodes);

    return 0;
}

