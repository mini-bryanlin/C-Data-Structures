struct Node;

struct Node * create(void);

void add_to_list (struct Node ** list, int num );

void print_list (struct Node * list);

int len (struct Node *list);

void del (struct Node ** list, int num);