//
// Created by Leticia Mejia/Marcel Ghisi.
//

#ifndef MY_BLOCKCHAIN_RUN_FUNCTIONS_H
#define MY_BLOCKCHAIN_RUN_FUNCTIONS_H

int append_block(t_block *start, t_block *new_block);
t_block *create_block(char* bid);
t_node* create_node(int nid);
static int parse_cmd(char *cmd);
int lsh_execute(char* cmd, t_node **nodes);
static int parse_cmd(char *cmd);
int generate_hash(t_block *start);
char* get_word(char* str, int n);
static int count_nodes(t_node* list);
static bool check_sync(t_node *nodes);
char* start_prompt(t_node *nodes);
static bool check_sync(t_node *nodes);
static int count_nodes(t_node* list);
int insert_to_backup(int fd, t_node **nodes);
void send_status(int error);

#endif //MY_BLOCKCHAIN_RUN_FUNCTIONS_H

