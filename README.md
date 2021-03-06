# my_blockchain

#### My blockchain is a program that allows for the creation and management of a blockchain,
#### users can create nodes and add data to the node, which is called blocks. 
#### The program will update data in to the chain if there is a backup data, otherwise, you 
#### will start with from scratch data.

#### To compile and test the program, you should follow the next steps:

#### 1. To compile execute:
##### $ make

#### 2. To run the program execute:
##### $ ./my_block_chain

#### NOTE: 
##### The program will display information about the blockchain at the begining with the following information:
###### - The prompt will have character and a digit. 
###### - The character can be either an s for synchronized and -  if the blockchain is not synchronized.
###### - The digit will let you know number of nodes in the chain
###### - The NID is an integer, BID is a string

#### Command options to test the program:

##### 1. add node nid: add a nid identifier to the blockchain node, example:
###### - [s0]> add node 5 (this should be a number) 

##### 2. rm node nid: remove nodes from the blockchain with a nid identifier. 
#####    If nid is '*', then all nodes are impacted. Exmaple:
######   [s0]> rm node 5 (this should be a number) or
######   [s0]> rm node * (will remove all nodes)

##### 3. add block bid nid: add a bid identifier block to nodes identified by nid. 
#####    If nid is '*', then all nodes are impacted. Example:
######   [s0]> add block 89 5 (89 is the block(BID) and the 5 the node(NID) which the block will be added)
######   or
######   [s0]> add block 89 * (89 is the block(BID) and * means that 89 will be applied to all nodes(NID))

##### 4. rm block bid: remove the bid identified blocks from all nodes where these blocks are present
#####    or you can pass an especific node to remove the block. Example:
######   [s0]> rm block 89 5 (89(BID) is the block and 5 is the node(NID))
######   or instead of passing an specific node you can pass a * to remove the block
######   from all nodes where these blocks are present as follow:
######   [s0]> rm block 89 * (89(BID) is the block and * means to remove from all nodes where exist)

##### 5. ls list all nodes by their identifiers. Example:
######   [s0]> ls (will list all the nodes)
#####    The option -l attaches the blocks bid's associated with each node. Example:
######   [s0]> ls -l (will list all the nodes and their block)

##### 6. sync: synchronize all of the nodes with each other. Upon issuing this command, all of the nodes are composed of the same blocks.
######   [s0]> sync

##### 7. quit: save and leave the blockchain. Note: if the user press ^c, the data wont be saved.
######   [s0]> quit

