//
// Created by Leticia Mejia/Marcel Ghisi.
//

#include "functions_structures.h"
//////////////////// add block

int add_block(t_node **nodes, char* cmd) {
    char* str_nid;
    int nid;
    char* bid;
    t_block *new_block;

    bid = get_word(cmd, 3);
    str_nid = get_word(cmd, 4);
    if (*str_nid == '*') {
        add_block_to_all_nodes(nodes, bid);
        free(bid);
        return 0;
    }
    nid = my_atoi(str_nid);
    while (*nodes && (*nodes)->next != NULL && (*nodes)->nid != nid) {
        nodes = &(*nodes)->next;
    }
    if (!*nodes || (*nodes)->nid != nid) {
        free(str_nid);
        free(bid);
        return node_doesnt_exist;
    }
    new_block = create_block(bid);
    free(bid);
    free(str_nid);
    if (new_block == NULL) {
        return no_more_resources;
    }
    if (append_block((*nodes)->start, new_block) == block_exists) {
        return block_exists;
    }
    (*nodes)->root_pointer = generate_hash((*nodes)->start);
    return 0;
}

static int add_block_to_all_nodes(t_node **nodes, char* bid) {
    t_block *new_block;

    while (*nodes != NULL) {
        new_block = create_block(bid);
        if (new_block == NULL) {
            return no_more_resources;
        }
        append_block((*nodes)->start, new_block);
        (*nodes)->root_pointer = generate_hash((*nodes)->start);
        nodes = &(*nodes)->next;
        if (*nodes == NULL) {
            return 0;
        }
    }
    return 0;
}

//////////////////////// add node
int add_node(t_node **nodes, char* cmd) {
    int nid;
    char* str_nid;

    str_nid = get_word(cmd, 3);
    nid = my_atoi(str_nid);
    free(str_nid);
    if (nid == 0) {
        return command_not_found;
    }
    while (*nodes) {
        if ((*nodes)->nid == nid) {
            return node_exists;
        }
        nodes = &(*nodes)->next;
    }
    *nodes = create_node(nid);
    return *nodes == NULL ? no_more_resources : 0;
}

/////////////////////// list nodes
int list_nodes(t_node **nodes) {
    t_node *temp = *nodes;

    while (temp != NULL) {
        printf("%d\n", temp->nid);
        temp = temp->next;
    }
    return 0;
}
///////////////////// list nodes and blocks

int list_nodes_and_blocks(t_node **nodes) {
    t_node *temp = *nodes;

    while (temp != NULL) {
        printf("%d:", temp->nid);
        list_blocks(temp->start);
        printf("\n");
        temp = temp->next;
    }
    return 0;
}

static void list_blocks(t_block *block) {
    while (block->next != NULL) {
        printf(" %s", block->next->bid);
        if (block->next->next != NULL) {
            printf(",");
        }
        block = block->next;
    }
}

//////////////////////// remove block

int rm_block(t_node **nodes, char* cmd) {
    char *bid;
    char *str_nid;
    int nid;

    bid = get_word(cmd, 3);
    str_nid = get_word(cmd, 4);
    while (*str_nid == '*') {
        if (free_block((*nodes)->start, bid) != 0) {
            return block_doesnt_exist;
        }
        nodes = &(*nodes)->next;
        if (*nodes == NULL) {
            free(bid);
            free(str_nid);
            return 0;
        }
    }
    nid = my_atoi(str_nid);
    while ((*nodes)->next != NULL && (*nodes)->nid != nid) {
        nodes = &(*nodes)->next;
    }
    if ((*nodes)->next == NULL && (*nodes)->nid != nid) {
        free(bid);
        free(str_nid);
        return node_doesnt_exist;
    }
    if (free_block((*nodes)->start, bid) != 0) {
        free(bid);
        free(str_nid);
        return block_doesnt_exist;
    }
    free(bid);
    free(str_nid);
    return 0;
}

static int free_block(t_block *start, char* bid) {
    t_block *temp;

    while (start->next != NULL && my_strcmp(start->next->bid, bid) != 0) {
        start = start->next;
    }
    if (start->next == NULL) {
        return block_doesnt_exist;
    }
    temp = start->next->next;
    free(start->next->bid);
    free(start->next);
    start->next = temp;
    return 0;
}

////////////////////////////// remove node
int rm_node(t_node **nodes, char* cmd) {
    char* str_nid;
    int nid;
    t_node *temp = NULL;

    str_nid = get_word(cmd, 3);
    printf("es:%s\n",str_nid);
    if (*str_nid == '*') {
        free(str_nid);
        //marcelfree_all_nodes(nodes);
        return 0;
    }
    nid = my_atoi(str_nid);
    while (*nodes && (*nodes)->nid != nid) {
        temp = *nodes;
        nodes = &(*nodes)->next;
    }
    if (!*nodes || (*nodes)->nid != nid) {
        free(str_nid);
        str_nid = NULL;
        return node_doesnt_exist;
    }
    temp = (*nodes)->next;
    free_node(*nodes);
    *nodes = temp;
    free(str_nid);
    return 0;
}
/////////////////////////////////////////////////
/*static int free_all_nodes(t_node **nodes) {
    if (!nodes) {
        return 0;
    }
    if (*nodes && (*nodes)->next != NULL) {
        free_all_nodes(&(*nodes)->next);
    }
    free_node(*nodes);
    return 0;
}*/

static int free_all_nodes(t_node **nodes) {
    if (!nodes) {
        return 0;
    }
    //marcel strange
    //if ((*nodes)-> != NULL) {
      //  free_all_nodes(&(*nodes)->next);
    //}
    free_node(*nodes);
    return 0;
}


/////////////////////////////////////////////
static void free_node(t_node *node) {
    free_all_blocks(node->start);
    free(node);
    node = NULL;
}

static int free_all_blocks(t_block *blocks) {
    if (blocks == NULL) return 0;
    if (blocks->next != NULL) {
        free_all_blocks(blocks->next);
    }
    if (blocks->bid != NULL) {
        free(blocks->bid);
        blocks->bid = NULL;
    }
    free(blocks);
    blocks = NULL;
    return 0;
}

////////////////////////// save and quit
int save_and_quit(t_node **nodes) {
    if (nodes == NULL) return 0;
    t_block *blocks;
    t_node **head = nodes;
    int fd;
    char *buf;

    fd = open("file_", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    buf = (char*)malloc(10);
    my_memset(buf, '\0', 10);
    while (nodes  != NULL && *nodes != NULL) {
        my_itoa((*nodes)->nid, buf, 10);
        write(fd, buf, 10);
        blocks = (*nodes)->start->next;
        while (blocks != NULL) {
            my_memset(buf, '\0', 10);
            my_strcpy(buf, blocks->bid);
            write(fd, buf, 10);
            blocks = blocks->next;
        }
        my_memset(buf, '\0', 10);
        write(fd, buf, 10);
        nodes = &(*nodes)->next;
    }
    free(buf);
    close(fd);
    if (*head) {
        rm_node(head, "rm node *");
    }
    return 0;
}

////////////////////////// sync nodes


int sync_nodes(t_node **nodes) {
    bool modified = true;
    t_node **head = nodes;

    while (modified == true) {
        modified = false;
        head = nodes;
        while (*head != NULL && (*head)->next != NULL) {
            if ((*head)->root_pointer != (*head)->next->root_pointer) {
                match_blocks(*head, (*head)->next);
                modified = true;
                (*head)->root_pointer = generate_hash((*head)->start);
                (*head)->next->root_pointer = generate_hash((*head)->next->start);
            }
            head = &(*head)->next;
        }
    }
    return 0;
}

static void match_blocks(t_node *a_node, t_node *b_node) {
    t_block *a_blocks = a_node->start->next;
    t_block *b_blocks;
    bool duplicate;

    while (a_blocks != NULL) {
        b_blocks = b_node->start->next;
        duplicate = false;
        while (b_blocks != NULL) {
            if (my_strcmp(b_blocks->bid, a_blocks->bid) == 0) {
                duplicate = true;
                break;
            }
            b_blocks = b_blocks->next;
        }
        if (duplicate == false) {
            append_block(b_node->start, create_block(a_blocks->bid));
        }
        a_blocks = a_blocks->next;
    }
    b_blocks = b_node->start->next;
    a_blocks = a_node->start->next;
    while (b_blocks != NULL) {
        a_blocks = a_node->start->next;
        duplicate = false;
        while (a_blocks != NULL) {
            if (my_strcmp(a_blocks->bid, b_blocks->bid) == 0) {
                duplicate = true;
                break;
            }
            a_blocks = a_blocks->next;
        }
        if (duplicate == false) {
            append_block(a_node->start, create_block(b_blocks->bid));
        }
        b_blocks = b_blocks->next;
    }
}

