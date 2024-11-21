#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXLEN 255
#define HASH_TABLE_SIZE 10


// structure for pncz table
typedef struct PNCZNode {
    int PId;
    char name[50];
    char city[50];
    char zip[10];
    struct PNCZNode *next;
} PNCZNode;

// structure for rpt table
typedef struct RPTNode {
    char race[50];
    int PId;
    char time[50];
    struct RPTNode *next;
} RPTNode;

// structure for rd table
typedef struct RDNode {
    char race[50];
    char date[50];
    struct RDNode *next;
} RDNode;

// structure for rs table
typedef struct RSNode {
    char race[50];
    char sponsor[50];
    struct RSNode *next;
} RSNode;

//structure for rq table
typedef struct RQNode {
    char race[50];
    char qualifier[50];
    struct RQNode *next;
} RQNode;

//hash table structure for each relative table 
typedef struct {
    PNCZNode *buckets[HASH_TABLE_SIZE];
} HashTablePNCZ;

typedef struct {
    RPTNode *buckets[HASH_TABLE_SIZE];
} HashTableRPT;

typedef struct {
    RSNode *buckets[HASH_TABLE_SIZE];
} HashTableRS;

typedef struct {
    RQNode *buckets[HASH_TABLE_SIZE];
} HashTableRQ;

typedef struct {
    RDNode *buckets[HASH_TABLE_SIZE];
} HashTableRD;

// hash function given an integer 
int hashFunction(int PId) {
    return PId % HASH_TABLE_SIZE;
}

// hash function given a string 
int stringHashFunction(char *string) {
    int hash = 0; 
    while (*string) {
        hash += (unsigned char)(*string);
        string++;
    }
    return hash % HASH_TABLE_SIZE;
}

// initialize the hash table for pncz
void initHashTablePNCZ(HashTablePNCZ *table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
}

// initialize the hash table for rpt
void initHashTableRPT(HashTableRPT *table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
}

// initialize the hash table for rd
void initHashTableRD(HashTableRD *table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
}

// initialize the hash table for rs
void initHashTableRS(HashTableRS *table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
}

// initialize the hash table for rq
void initHashTableRQ(HashTableRQ *table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
}

// insert function for pncz table 
void insert_PNCZ(HashTablePNCZ *table, int PId, char *name, char *city, char *zip) {
    int index = hashFunction(PId);
    PNCZNode *current = table->buckets[index];
    bool add = true; 

    // checks to see if the tuple is already in the table
    while(current != NULL) {
        if(current->PId == PId && strcmp(current->name, name) == 0 && strcmp(current->city, city) == 0 && strcmp(current->zip, zip) == 0) {
            add = false;
            break;
        }
        current = current->next;
    }

    // if it is return 
    if(!add) {
        return;
    }

    // initialize a new pncz tuple
    PNCZNode *newNode = (PNCZNode *)malloc(sizeof(PNCZNode));
    newNode->PId = PId;
    strncpy(newNode->name, name, 50);
    strncpy(newNode->city, city, 50);
    strncpy(newNode->zip, zip, 10);

    // add it into the table 
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

// insert function for rpt table
void insert_RPT(HashTableRPT *table, char *race, int PId, char* time) {
    int index = hashFunction(PId);

    RPTNode *current = table->buckets[index];
    bool add = true; 
    
    // checks to see if the tuple is already in the rpt table 
    while(current != NULL) {
        if(strcmp(current->race, race) == 0 && current->PId == PId && strcmp(current->time, time) == 0) {
            add = false;
            break;
        }
        current = current->next;
    }

    // if it is return
    if(!add) {
        return;
    }

    // initialize a new rpt tuple
    RPTNode *newNode = (RPTNode *)malloc(sizeof(RPTNode));
    newNode->PId = PId;
    strncpy(newNode->race, race, 50);
    strncpy(newNode->time, time, 50);

    //add it to the table 
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

// insert function for the rd table 
void insert_RD(HashTableRD *table, char *race, char* date) {
    int index = stringHashFunction(race); 
    RDNode *current = table->buckets[index];
    bool add = true; 

    // check if the tuple is already in there
    while(current != NULL) {
        if(strcmp(current->race, race) == 0 && strcmp(current->date, date) == 0) {
            add = false;
            break;
        }
        current = current->next;
    }

    // return if it is
    if(!add) {
        return;
    }

    //create a new rd note 
    RDNode *newNode = (RDNode *)malloc(sizeof(RDNode));
    strncpy(newNode->race, race, 50);
    strncpy(newNode->date, date, 50);

    // add it to the table 
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

// insert function for rs table 
void insert_RS(HashTableRS *table, char *race, char* sponsor) {
    int index = stringHashFunction(sponsor); 
    RSNode *current = table->buckets[index];
    bool add = true; 

    // check if the tuple is already in the table 
    while(current != NULL) {
        if(strcmp(current->race, race) == 0 && strcmp(current->sponsor, sponsor) == 0) {
            add = false;
            break;
        }
        current = current->next;
    }

    // if it is return 
    if(!add) {
        return;
    }

    // create a new rs node
    RSNode *newNode = (RSNode *)malloc(sizeof(RSNode));
    strncpy(newNode->race, race, 50);
    strncpy(newNode->sponsor, sponsor, 50);

    // add it to the rs table 
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

// insert function for the rq table 
void insert_RQ(HashTableRQ *table, char *race, char* qualifier) {
    int index = stringHashFunction(qualifier); 
    RQNode *current = table->buckets[index];
    bool add = true; 

    // check if it is in the table already
    while(current != NULL) {
        if(strcmp(current->race, race) == 0 && strcmp(current->qualifier, qualifier) == 0) {
            add = false;
            break;
        }
        current = current->next;
    }

    // if it is return
    if(!add) {
        return;
    }

    //if not create new node 
    RQNode *newNode = (RQNode *)malloc(sizeof(RQNode));
    strncpy(newNode->race, race, 50);
    strncpy(newNode->qualifier, qualifier, 50);

    // insert it into the table
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

// all insert, lookup, and delete functions have very similar framework but are slightly altered to 
// each indiviual table and what they contain

// lookup function for pncz 
void lookup_PNCZ(HashTablePNCZ *table, int PId, char *name, char *city, char *zip) {
    printf("Lookup results for: PId: %d, Name: %s, City: %s, Zip: %s\n", PId, name, city, zip);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        PNCZNode *current = table->buckets[i];
        while (current != NULL) {
            int match = 1;
            // -1 works as the * for integer values 
            // check each inidividual column in the row
            if (PId != -1 && current->PId != PId) match = 0;
            if (name != NULL && strcmp(name, "*") != 0 && strcmp(current->name, name) != 0) match = 0;
            if (city != NULL && strcmp(city, "*") != 0 && strcmp(current->city, city) != 0) match = 0;
            if (zip != NULL && strcmp(zip, "*") != 0 && strcmp(current->zip, zip) != 0) match = 0;
            
            // found it!
            if (match) {
                printf("Found: PId: %d, Name: %s, City: %s, Zip: %s\n", current->PId, current->name, current->city, current->zip);
            }
            current = current->next;
        }
    }
}

// lookup function for rpt 
void lookup_RPT(HashTableRPT *table, char *race, int PId, char* time) {
    printf("Lookup results for: PId: %d, race: %s, time: %s\n", PId, race, time);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RPTNode *current = table->buckets[i];
        while (current != NULL) {
            int match = 1;
            if (PId != -1 && current->PId != PId) match = 0;
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            if (time != NULL && strcmp(time, "*") != 0 && strcmp(current->time, time) != 0) match = 0;
            if (match) {
                printf("Found: PId: %d, race: %s, time: %s\n", current->PId, current->race, current->time);
            }
            current = current->next;
        }
    }
}

// lookup function for rd 
void lookup_RD(HashTableRD *table, char *race, char* date) {
    printf("Lookup results for: race: %s, date: %s\n", race, date);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RDNode *current = table->buckets[i];
        while (current != NULL) {
            int match = 1;
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            if (date != NULL && strcmp(date, "*") != 0 && strcmp(current->date, date) != 0) match = 0;
            if (match) {
                printf("Found: race: %s, date: %s\n", current->race, current->date);
            }
            current = current->next;
        }
    }
}

// lookup function for rs 
void lookup_RS(HashTableRS *table, char *race, char* sponsor) {
    printf("Lookup results for: race: %s, sponsor: %s\n", race, sponsor);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RSNode *current = table->buckets[i];
        while (current != NULL) {
            int match = 1;
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            if (sponsor != NULL && strcmp(sponsor, "*") != 0 && strcmp(current->sponsor, sponsor) != 0) match = 0;
            if (match) {
                printf("Found: race=%s, sponsor=%s\n", current->race, current->sponsor);
            }
            current = current->next;
        }
    }
}

// lookup function for rq 
void lookup_RQ(HashTableRQ *table, char *race, char* qualifier) {
    printf("Lookup results for: race: %s, qualifier: %s\n", race, qualifier);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RQNode *current = table->buckets[i];
        while (current != NULL) {
            int match = 1;
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            if (qualifier != NULL && strcmp(qualifier, "*") != 0 && strcmp(current->qualifier, qualifier) != 0) match = 0;
            if (match) {
                printf("Found: race=%s, qualifier=%s\n", current->race, current->qualifier);
            }
            current = current->next;
        }
    }
}

// delete function for pncz
void delete_PNCZ(HashTablePNCZ *table, int PId, char *name, char *city, char *zip) {
    printf("Deleting entries matching: PId: %d, Name: %s, City: %s, Zip: %s\n", PId, name, city, zip);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        PNCZNode *current = table->buckets[i];
        PNCZNode *prev = NULL;
        while (current != NULL) {
            int match = 1;
            if (PId != -1 && current->PId != PId) match = 0;
            if (name != NULL && strcmp(name, "*") != 0 && strcmp(current->name, name) != 0) match = 0;
            if (city != NULL && strcmp(city, "*") != 0 && strcmp(current->city, city) != 0) match = 0;
            if (zip != NULL && strcmp(zip, "*") != 0 && strcmp(current->zip, zip) != 0) match = 0;
            if (match) {
                if (prev == NULL) {
                    table->buckets[i] = current->next;
                } else {
                    prev->next = current->next;
                }
                
                printf("Deleted: PId: %d, Name: %s, City: %s, Zip: %s\n", current->PId, current->name, current->city, current->zip);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
    }
}

// delete function for rpt
void delete_RPT(HashTableRPT *table, char *race, int PId, char* time) {
    printf("Deleting entries matching: PId: %d, race: %s, time: %s\n", PId, race, time);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RPTNode *current = table->buckets[i];
        RPTNode *prev = NULL;
        while (current != NULL) {
            int match = 1;
            if (PId != -1 && current->PId != PId) match = 0;
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            if (time != NULL && strcmp(time, "*") != 0 && strcmp(current->time, time) != 0) match = 0;
            if (match) {
                if (prev == NULL) {
                    table->buckets[i] = current->next;
                } else {
                    prev->next = current->next;
                }
                printf("Deleted: PId: %d, race: %s, time: %s\n", current->PId, current->race, current->time);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
    }
}

// delete function for rd
void delete_RD(HashTableRD *table, char *race, char* date) {
    printf("Deleting entries matching: race: %s, date: %s\n", race, date);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RDNode *current = table->buckets[i];
        RDNode *prev = NULL;
        while (current != NULL) {
            int match = 1;
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            if (date != NULL && strcmp(date, "*") != 0 && strcmp(current->date, date) != 0) match = 0;
            if (match) {
                if (prev == NULL) {
                    table->buckets[i] = current->next;
                } else {
                    prev->next = current->next;
                }
                printf("Deleted: race: %s, date: %s\n",  current->race, current->date);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
    }
}

// delete function for rs
void delete_RS(HashTableRS *table, char *race, char* sponsor) {
    printf("Deleting entries matching: race: %s, sponsor: %s\n", race, sponsor);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RSNode *current = table->buckets[i];
        RSNode *prev = NULL;
        while (current != NULL) {
            int match = 1;
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            if (sponsor != NULL && strcmp(sponsor, "*") != 0 && strcmp(current->sponsor, sponsor) != 0) match = 0;
            if (match) {
                if (prev == NULL) {
                    table->buckets[i] = current->next;
                } else {
                    prev->next = current->next;
                }
                printf("Deleted: race: %s, sponsor: %s\n",  current->race, current->sponsor);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
    }
}

// delete function for rq
void delete_RQ(HashTableRQ *table, char *race, char* qualifier) {
    printf("Deleting entries matching: race: %s, qualifier: %s\n", race, qualifier);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RQNode *current = table->buckets[i];
        RQNode *prev = NULL;
        while (current != NULL) {
            int match = 1;
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            if (qualifier != NULL && strcmp(qualifier, "*") != 0 && strcmp(current->qualifier, qualifier) != 0) match = 0;
            if (match) {
                if (prev == NULL) {
                    table->buckets[i] = current->next;
                } else {
                    prev->next = current->next;
                } 
                printf("Deleted: race: %s, date: %s\n",  current->race, current->qualifier);
                free(current);
                break;
            } 
            prev = current;
            current = current->next;
        }
    }
}

void print_PNCZ(HashTablePNCZ *table) {
    printf("\n");
    printf("Contents of the PNCZ table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        PNCZNode *current = table->buckets[i];
        while (current != NULL) {
            printf("PId: %d, Name: %s, City: %s, Zip: %s\n", current->PId, current->name, current->city, current->zip);
            current = current->next;
        }
    }
    printf("\n");
}

void print_RPT(HashTableRPT *table) {
    printf("\n");
    printf("Contents of the RPT table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RPTNode *current = table->buckets[i];
        while (current != NULL) {
            printf("Race: %s, PId: %d, Time: %s\n", current->race, current->PId, current->time);
            current = current->next;
        }
    }
    printf("\n");
}

void print_RD(HashTableRD *table) {
    printf("\n");
    printf("Contents of the RD table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RDNode *current = table->buckets[i];
        while (current != NULL) {
            printf("Race: %s, Date: %s\n", current->race, current->date);
            current = current->next;
        }
    }
    printf("\n");
}

void print_RS(HashTableRS *table) {
    printf("\n");
    printf("Contents of the RS table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RSNode *current = table->buckets[i];
        while (current != NULL) {
            printf("Race: %s, Sponsor: %s\n", current->race, current->sponsor);
            current = current->next;
        }
    }
    printf("\n");
}

void print_RQ(HashTableRQ *table) {
    printf("\n");
    printf("Contents of the RQ table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RQNode *current = table->buckets[i];
        while (current != NULL) {
            printf("Race: %s, Qualifier: %s\n", current->race, current->qualifier);
            current = current->next;
        }
    }
    printf("\n");
}



void query_two(HashTablePNCZ *pnczTable2, HashTableRPT *rptTable2, HashTableRD *rdTable2, HashTableRS *rsTable2, char *name, char *sponsor) {
    bool found = false; 
    printf("Answering the query: On what date(s) did %s run a race sponsored by %s\n", name, sponsor);
    for (int t = 0; t < HASH_TABLE_SIZE; t++) {
        RSNode *currentRS = rsTable2->buckets[t];
        while (currentRS) {
            if (strcmp(currentRS->sponsor, sponsor) == 0) {
                char *race = currentRS->race; 
                for (int s = 0; s < HASH_TABLE_SIZE; s ++) {
                    RPTNode *currentRPT = rptTable2->buckets[s];
                    while (currentRPT) {
                        if (strcmp(currentRPT->race, race) == 0) {
                            int pid = currentRPT->PId;
                            for (int i = 0; i < HASH_TABLE_SIZE; i++) {
                                PNCZNode *currentPNCZ = pnczTable2->buckets[i];
                                while (currentPNCZ) {
                                    if (currentPNCZ->PId == pid && strcmp(currentPNCZ->name, name) == 0) {
                                        for (int j = 0; j < HASH_TABLE_SIZE; j++) {
                                            RDNode *currentRD = rdTable2->buckets[j];
                                            while (currentRD) {
                                                if (strcmp(currentRD->race, race) == 0) {
                                                    printf("Result: %s\n", currentRD->date);
                                                    found = true;
                                                    return; 
                                                }
                                                currentRD = currentRD->next;
                                            }
                                        }
                                    }
                                    currentPNCZ = currentPNCZ->next;
                                }
                            }
                        }
                        currentRPT = currentRPT->next;
                    }
                }
            }
            currentRS = currentRS->next;
        }
    }
    if (!found) {
        printf("Date not found\n");
    }
}

void query_one (HashTablePNCZ *pnczTable2, HashTableRPT *rptTable2, char *name, char *race){
    bool found = false;
    printf("Answering the query: What time did %s get in %s\n", name, race);
    for (int t = 0; t < HASH_TABLE_SIZE; t++) {
        PNCZNode *currentPNCZ = pnczTable2->buckets[t];
        while(currentPNCZ) {
            if (strcmp(currentPNCZ->name, name) == 0) {
                int pid = currentPNCZ->PId;
                for (int s = 0; s < HASH_TABLE_SIZE; s++) {
                    RPTNode *currentRPT = rptTable2->buckets[s];
                    while(currentRPT) {
                        if (strcmp(currentRPT->race, race) == 0 && currentRPT->PId == pid) {
                            printf("Result: %s\n", currentRPT->time);
                            found = true;
                        }
                        currentRPT = currentRPT->next;
                    }
                }
            }
            currentPNCZ = currentPNCZ->next; 
        }
    }
    if(!found) {
        printf("No matching record. \n");
    }
    
}

void read_input_query_one(HashTablePNCZ *pnczTable2, HashTableRPT *rptTable2) {
    printf("Running the query, what time did name get in race\n");
    char buffer[MAXLEN + 1];
    char buffer2[MAXLEN + 1];
    while (1) {
        printf("Enter a name (type \'quit\' to quit): ");
        char* name = fgets(buffer, MAXLEN + 1, stdin);
        name[strcspn(name, "\n")] = 0;
        if(!strcmp(name, "quit")) {
            break;
        }
        printf("Enter a race (type \'quit\' to quit): ");
        char* race = fgets(buffer2, MAXLEN + 1, stdin);
        race[strcspn(race, "\n")] = 0;
        if(!strcmp(race, "quit")) {
            break;
        }
        query_one(pnczTable2, rptTable2, name, race);
    }   
}

void read_input_query_two(HashTablePNCZ *pnczTable2, HashTableRPT *rptTable2, HashTableRD *rdTable2, HashTableRS *rsTable2) {
    printf("Running the query, On what date(s) did name run a race sponsored by sponsor\n");
    char buffer[MAXLEN + 1];
    char buffer2[MAXLEN + 1];
    while (1) {
        printf("Enter a name (type \'quit\' to quit): ");
        char* name = fgets(buffer, MAXLEN + 1, stdin);
        name[strcspn(name, "\n")] = 0;
        if(!strcmp(name, "quit")) {
            break;
        }
        printf("Enter a sponsor (type \'quit\' to quit): ");
        char* sponsor = fgets(buffer2, MAXLEN + 1, stdin);
        sponsor[strcspn(sponsor, "\n")] = 0;
        if(!strcmp(sponsor, "quit")) {
            break;
        }
        query_two(pnczTable2, rptTable2, rdTable2, rsTable2, name, sponsor);
    }   
}

HashTableRPT select_RPT_Race(HashTableRPT *rptTable, char *race) {
    HashTableRPT result = {.buckets = {NULL}};
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RPTNode *current = rptTable->buckets[i];
        while(current) {
            if (strcmp (current->race, race) == 0) {
                insert_RPT(&result, current->race, current->PId, current->time);
            }
            current = current->next;
        }
    }
    return result;
}

typedef struct PIdNode {
    int PId;
    struct PIdNode *next;
} PIdNode;

typedef struct {
    PIdNode *buckets[HASH_TABLE_SIZE];
} HashTablePId;

void PId_insert(HashTablePId *pidTable, int pid) {
    int index = hashFunction(pid);
    PIdNode *newNode = (PIdNode *)malloc(sizeof(PIdNode));
    newNode->PId = pid;
    newNode->next = pidTable->buckets[index];
    pidTable->buckets[index] = newNode;
}

HashTablePId project_RPT_PId(HashTableRPT *rptTable) {
    HashTablePId result = {.buckets = {NULL}};
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RPTNode *current = rptTable->buckets[i];
        while (current) {
            PId_insert(&result, current->PId);
            current = current->next;
        }
    }
    return result;
}

void print_pid(HashTablePId *pidTable) {
    printf("\n");
    printf("Contents of the pid table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        PIdNode *current = pidTable->buckets[i];
        while (current != NULL) {
            printf("PId: %d\n", current->PId);
            current = current->next;
        }
    }
    printf("\n");
}

typedef struct RDRSNode {
    char race[50];
    char date[50];
    char sponsor[50];
    struct RDRSNode *next;
} RDRSNode;

typedef struct {
    RDRSNode *buckets[HASH_TABLE_SIZE];
} HashTableJoin;

void insert_RSRD (HashTableJoin *rsrdTable, char *race, char *date, char *sponsor) {
    int index = stringHashFunction(race);
    RDRSNode *current = rsrdTable->buckets[index];
    bool add = true; 
    
    // checks to see if the tuple is already in the rsrd table 
    while(current != NULL) {
        if(strcmp(current->race, race) == 0 && strcmp(current->date, date) == 0 && strcmp(current->sponsor, sponsor) == 0) {
            add = false;
            break;
        }
        current = current->next;
    }

    // if it is return
    if(!add) {
        return;
    }

    // initialize a new rpt tuple
    RDRSNode *newNode = (RDRSNode *)malloc(sizeof(RDRSNode));
    strncpy(newNode->race, race, 50);
    strncpy(newNode->date, date, 50);
    strncpy(newNode->sponsor, sponsor, 50);

    //add it to the table 
    newNode->next = rsrdTable->buckets[index];
    rsrdTable->buckets[index] = newNode;
}

HashTableJoin join_RD_RS(HashTableRD *rdTable, HashTableRS *rsTable) {
    HashTableJoin result = {.buckets = {NULL}}; // this initializes the buckets to all null ptrs
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RDNode *rdCurrent = rdTable->buckets[i];
        while (rdCurrent) {
            for (int j = 0; j < HASH_TABLE_SIZE; j++) {
                RSNode *rsCurrent = rsTable->buckets[j];
                while (rsCurrent) {
                if (strcmp(rdCurrent->race, rsCurrent->race) == 0) {
                    insert_RSRD(&result, rdCurrent->race, rdCurrent->date, rsCurrent->sponsor);
                }
                rsCurrent = rsCurrent->next;
                }
            }
            
            rdCurrent = rdCurrent->next;
        }
    }
    return result;
}

void print_rdrs_join(HashTableJoin *rdrsTable) {
    printf("\n");
    printf("Contents of the joint table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RDRSNode *current = rdrsTable->buckets[i];
        while (current != NULL) {
            printf("Race: %s, Date: %s, Sponsor: %s\n", current->race, current->date, current->sponsor);
            current = current->next;
        }
    }
    printf("\n");
}

HashTableJoin select_RDRS_Date(HashTableJoin *rdrsTable, char *date) {
    HashTableJoin result = {.buckets = {NULL}};
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RDRSNode *current = rdrsTable->buckets[i];
        while(current) {
            if (strcmp (current->date, date) == 0) {
                insert_RSRD(&result, current->race, current->date, current->sponsor);
            }
            current = current->next;
        }
    }
    return result;
}

typedef struct SponsorNode {
    char sponsor[50];
    struct SponsorNode *next;
} SponsorNode;

typedef struct {
    SponsorNode *buckets[HASH_TABLE_SIZE];
} HashTableSponsor;

void sponsor_insert(HashTableSponsor *sponsorTable, char *sponsor) {
    int index = stringHashFunction(sponsor);
    SponsorNode *newNode = (SponsorNode *)malloc(sizeof(SponsorNode));
    strncpy(newNode->sponsor, sponsor, 50);
    newNode->next = sponsorTable->buckets[index];
    sponsorTable->buckets[index] = newNode;
}

HashTableSponsor project_RDRS_sponsor(HashTableJoin *rdrsTable) {
    HashTableSponsor result = {.buckets = {NULL}};
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RDRSNode *current = rdrsTable->buckets[i];
        while (current) {
            sponsor_insert(&result, current->sponsor);
            current = current->next;
        }
    }
    return result;
}

void print_sponsor(HashTableSponsor *sponsorTable) {
    printf("\n");
    printf("Contents of the sponsor table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        SponsorNode *current = sponsorTable->buckets[i];
        while (current != NULL) {
            printf("Sponsor: %s\n", current->sponsor);
            current = current->next;
        }
    }
    printf("\n");
}

int main() {
    HashTablePNCZ pnczTable;
    HashTableRPT rptTable;
    HashTableRD rdTable;
    HashTableRS rsTable;
    HashTableRQ rqTable; 

    initHashTablePNCZ(&pnczTable);
    initHashTableRPT(&rptTable);
    initHashTableRD(&rdTable);
    initHashTableRS(&rsTable);
    initHashTableRQ(&rqTable);

    insert_PNCZ(&pnczTable, 67815, "E. Allen", "Clarkson", "14642");
    insert_PNCZ(&pnczTable, 37435, "J. Thomas", "Churchville", "14643");
    insert_PNCZ(&pnczTable, 41222, "H. Evans", "North Gates", "14621");
    insert_PNCZ(&pnczTable, 31444, "E. Allen", "Pittsford", "14559");
    insert_PNCZ(&pnczTable, 89602, "J. Thomas", "Hamlin", "14651");
    insert_PNCZ(&pnczTable, 69441, "O. Price", "Hamlin", "14506");

    insert_RPT(&rptTable, "UTri", 69441, "01:45:12");
    insert_RPT(&rptTable, "CSC Marathon", 31444, "01:22:22");
    insert_RPT(&rptTable, "GVP Classic", 89602, "01:52:26");
    insert_RPT(&rptTable, "CSC Marathon", 67815, "00:32:32");
    insert_RPT(&rptTable, "Buffalo Stampede", 41222, "01:53:57");
    insert_RPT(&rptTable, "GVP Classic", 37435, "01:20:23");

    insert_RD(&rdTable, "RocRace", "2023-07-27");
    insert_RD(&rdTable, "Buffalo Stampede", "2023-05-16");
    insert_RD(&rdTable, "UTri", "2023-11-02");
    insert_RD(&rdTable, "GVP Classic", "2023-05-16");
    insert_RD(&rdTable, "CSC Marathon", "2023-11-11");

    insert_RS(&rsTable, "Buffalo Stampede", "Sadida");
    insert_RS(&rsTable, "CSC Marathon", "Psyke");
    insert_RS(&rsTable, "CSC Marathon", "URMC Ortho");
    insert_RS(&rsTable, "GVP Classic", "LizardAde");
    insert_RS(&rsTable, "Buffalo Stampede", "Run Club");
    insert_RS(&rsTable, "Roc Race", "Crooks");

    insert_RQ(&rqTable, "Roc Race", "Buffalo Stampede");
    insert_RQ(&rqTable, "GVP Classic", "CSC Marathon");
    insert_RQ(&rqTable, "GVP Classic", "RocRace");

    print_PNCZ(&pnczTable);
    print_RPT(&rptTable);
    print_RD(&rdTable);
    print_RS(&rsTable);
    print_RQ(&rqTable);

    lookup_RPT(&rptTable, "CSC Marathon", 67815, "*");
    printf("\n");
    lookup_PNCZ(&pnczTable, -1, "J. Thomas", "*", "*");
    printf("\n");
    lookup_RQ(&rqTable, "CSC Marathon", "GVP Classic"); 
    printf("\n");

    delete_RD(&rdTable, "UTri", "2023-11-02");
    print_RD(&rdTable);
    delete_RS(&rsTable, "GVP Classic", "McDavid's");
    print_RS(&rsTable);
    delete_RS(&rsTable, "*", "LizardAde");
    print_RS(&rsTable);
    
    printf("Inserting Race: GVP Classic and Qualifier: Newbie Classic into RQ");
    insert_RQ(&rqTable, "GVP Classic", "Newbie Classic");
    print_RQ(&rqTable);
    printf("Inserting Race: GVP Classic and Qualifier: CSC Marathon into RQ");
    insert_RQ(&rqTable, "GVP Classic", "CSC Marathon");
    print_RQ(&rqTable);


    HashTablePNCZ pnczTable2;
    HashTableRPT rptTable2;
    HashTableRD rdTable2;
    HashTableRS rsTable2;
    HashTableRQ rqTable2;

    initHashTablePNCZ(&pnczTable2);
    initHashTableRPT(&rptTable2);
    initHashTableRD(&rdTable2);
    initHashTableRS(&rsTable2);
    initHashTableRQ(&rqTable2);

    insert_PNCZ(&pnczTable2, 67815, "E. Allen", "Clarkson", "14642");
    insert_PNCZ(&pnczTable2, 37435, "J. Thomas", "Churchville", "14643");
    insert_PNCZ(&pnczTable2, 41222, "H. Evans", "North Gates", "14621");
    insert_PNCZ(&pnczTable2, 31444, "E. Allen", "Pittsford", "14559");
    insert_PNCZ(&pnczTable2, 89602, "J. Thomas", "Hamlin", "14651");
    insert_PNCZ(&pnczTable2, 69441, "O. Price", "Hamlin", "14506");

    insert_RPT(&rptTable2, "UTri", 69441, "01:45:12");
    insert_RPT(&rptTable2, "CSC Marathon", 31444, "01:22:22");
    insert_RPT(&rptTable2, "GVP Classic", 89602, "01:52:26");
    insert_RPT(&rptTable2, "CSC Marathon", 67815, "00:32:32");
    insert_RPT(&rptTable2, "Buffalo Stampede", 41222, "01:53:57");
    insert_RPT(&rptTable2, "GVP Classic", 37435, "01:20:23");

    insert_RD(&rdTable2, "RocRace", "2023-07-27");
    insert_RD(&rdTable2, "Buffalo Stampede", "2023-05-16");
    insert_RD(&rdTable2, "UTri", "2023-11-02");
    insert_RD(&rdTable2, "GVP Classic", "2023-05-16");
    insert_RD(&rdTable2, "CSC Marathon", "2023-11-11");

    insert_RS(&rsTable2, "Buffalo Stampede", "Sadida");
    insert_RS(&rsTable2, "CSC Marathon", "Psyke");
    insert_RS(&rsTable2, "CSC Marathon", "URMC Ortho");
    insert_RS(&rsTable2, "GVP Classic", "LizardAde");
    insert_RS(&rsTable2, "Buffalo Stampede", "Run Club");
    insert_RS(&rsTable2, "RocRace", "Crooks");

    insert_RQ(&rqTable2, "RocRace", "Buffalo Stampede");
    insert_RQ(&rqTable2, "GVP Classic", "CSC Marathon");
    insert_RQ(&rqTable2, "GVP Classic", "RocRace");

    read_input_query_one(&pnczTable2, &rptTable2); 
    read_input_query_two(&pnczTable2, &rptTable2, &rdTable2, &rsTable2);

    printf("1. Selection: Race=\"GVP Classic\"(RPT) \n");
    HashTableRPT selectedRPT = select_RPT_Race(&rptTable2, "GVP Classic");
    print_RPT(&selectedRPT);

    printf("2. Projection: PId(Selection GVP Classic(RPT))\n");
    HashTablePId projectedPId = project_RPT_PId(&selectedRPT);
    print_pid(&projectedPId);

    print_RD(&rdTable2);
    print_RS(&rsTable2);
    printf("3. Joining RD and RS tables\n");
    HashTableJoin jointRDRS = join_RD_RS(&rdTable2, &rsTable2);
    print_rdrs_join(&jointRDRS);

    printf("Selection: date=\"2023-10-02\"(RPT) \n");
    HashTableJoin selectedDate = select_RDRS_Date(&jointRDRS, "2023-10-02");
    print_rdrs_join(&selectedDate);

    printf("4. Printing sponsors\n");
    HashTableSponsor sponsor = project_RDRS_sponsor(&selectedDate);
    print_sponsor(&sponsor);
    
    return 0;
}
