//
// Created by Leticia Mejia/Marcel Ghisi.
//

#include "functions_structures.h"
#include "run_functions.h"
#include <stdlib.h>

///////////// append block
int append_block(t_block *start, t_block *new_block) {
    while (start->next != NULL) {
        start = start->next;
    }
    start->next = new_block;
    return 0;
}

////////// create block
t_block *create_block(char *bid) {
    t_block *new_block;

    new_block = (t_block *) malloc(sizeof(t_block));
    new_block->next = NULL;
    if (bid == NULL) {
        new_block->bid = NULL;
    } else {
        new_block->bid = (char *) malloc(my_strlen(bid) + 1);
        my_strcpy(new_block->bid, bid);
    }
    return new_block;
}

/////////////// create node
t_node *create_node(int nid) {
    t_node *new_node;

    new_node = (t_node *) malloc(sizeof(t_node));

    if (new_node == NULL) {
        return NULL;
    }
    new_node->next = NULL;
    new_node->start = create_block(NULL);
    new_node->root_pointer = 0;
    new_node->nid = nid;

    return new_node;
}

/////////////////// execute cmd


int lsh_execute(char *cmd, t_node **nodes) {
    int error;

    switch (parse_cmd(cmd)) {
        case ADD_NID:
            error = add_node(nodes, cmd);
            break;
        case ADD_BID:
            error = add_block(nodes, cmd);
            break;
        case RM_NID:
            error = rm_node(nodes, cmd);
            break;
        case RM_BID:
            error = rm_block(nodes, cmd);
            break;
        case LS:
            error = list_nodes(nodes);
            break;
        case LS_L:
            error = list_nodes_and_blocks(nodes);
            break;
        case SYNC:
            error = sync_nodes(nodes);
            break;
        case QUIT:
            save_and_quit(nodes);
            error = QUIT;
            break;
        default:
            error = command_not_found;
            break;
    }
    return error;
}

static int parse_cmd(char *cmd) {
    char *commands[] = {"add node ",
                        "add block ", "rm node ",
                        "rm block ", "ls -l", "ls",
                        "sync", "quit"};

    for (int i = 0; i < 8; i++) {
        if (my_strncmp(cmd, commands[i], my_strlen(commands[i])) == 0) {
            return i + 1;
        }
    }
    return -1;
}

///////////////// generate hash
int generate_hash(t_block *start) {
    int b_hash;
    int r_hash = 0;

    start = start->next;
    while (start != NULL) {
        b_hash = 0;
        for (int i = 0; start->bid[i] != '\0'; i++) {
            b_hash += start->bid[i];
        }
        start->next_pointer = b_hash;
        r_hash += b_hash;
        start = start->next;
    }
    return r_hash;
}

//////////////////// get word
char *get_word(char *str, int n) {
    int i = 0;
    int j = 0;
    char buf[50];
    char *word;

    while (n-- > 1) {
        while (str[i++] <= ' ');
        while (str[i++] > ' ');
    }
    while (str[i] > ' ') {
        buf[j] = str[i];
        i++;
        j++;
    }
    buf[j] = '\0';
    word = my_strdup(buf);
    printf("%s\n", word);
    return word;
}

//////////////////////////// cmd

char *start_prompt(t_node *nodes) {
    int node_count;
    int bytes_read;
    bool sync;
    char *user_cmd;

    // get the number of nodes
    node_count = count_nodes(nodes);
    /// check the status of the sync (-s)
    sync = check_sync(nodes);
    write(1, "[", 1);
    sync == true ? write(1, "s", 1) : write(1, "-", 1);
    my_putnbr(node_count);
    write(1, "]> ", 3);

    // Take input from user
    user_cmd = (char *) malloc(101);
    bytes_read = read(0, user_cmd, 100);
    user_cmd[bytes_read] = '\0';

    return user_cmd;
}

static bool check_sync(t_node *nodes) {
    int ret = 0;

    while (nodes != NULL) {
        nodes->root_pointer = generate_hash(nodes->start);
        if (nodes->next != NULL) {
            ret = nodes->root_pointer - nodes->next->root_pointer;
        } else {
            return 1;
        }
        if (ret != 0) {
            return 0;
        }
        nodes = nodes->next;
    }
    return 1;
}

static int count_nodes(t_node *list) {
    int count = 0;

    while (list != NULL) {
        count++;
        list = list->next;
    }
    return count;
}

////////////////////// back up
int insert_to_backup(int fd, t_node **nodes) {
    int ret;
    char buf[10];

    while ((ret = read(fd, buf, 10)) != 0) {
        if (buf[0] == '\0') {
            nodes = &(*nodes)->next;
        } else if (*nodes == NULL) {
            *nodes = create_node(my_atoi(buf));
        } else {
            append_block((*nodes)->start, create_block(buf));
            (*nodes)->root_pointer = generate_hash((*nodes)->start);
        }
    }
    return 0;
}


///////////////// send error if a command did not proceeded
void send_status(int error) {
    switch (error) {
        case no_more_resources:
            printf("No more resources\n");
            break;
        case node_exists:
            printf("Node already exists\n");
            break;
        case block_exists:
            printf("Block already exists\n");
            break;
        case node_doesnt_exist:
            printf("Node doesn't exist\n");
            break;
        case block_doesnt_exist:
            printf("Block doesn't exist\n");
            break;
        case command_not_found:
            printf("Command not found\n");
            break;
        case QUIT:
            printf("Backing up blockchain...\nQuitting\n");
            break;
        default:
            printf("Unknown error\n");
            break;
    }
}

