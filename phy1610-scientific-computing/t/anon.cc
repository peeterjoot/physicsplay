#include <stdio.h>

enum node_type {
    t_int, t_double
};

struct int_node {
    int value;
};

struct double_node {
    double value;
};

struct node {
    enum node_type type;
    union {
        struct int_node int_n;
        struct double_node double_n;
    };
};

struct n2 {
    enum node_type type;
    struct {
        struct int_node int_n;
        struct double_node double_n;
    };
};

int main()
{
   node n ;
   n2 m ;
  
   n.int_n.value = 0 ;
   m.int_n.value = 0 ;
 
   return 0 ;
}
