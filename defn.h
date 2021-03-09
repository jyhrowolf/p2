#define	CAT_NAME_LEN	25
#define	APP_NAME_LEN	50
#define	VERSION_LEN	10
#define	UNIT_SIZE	3
#include <string>

struct app_info {
    std::string category; // Name of category
    std::string app_name; // Name of the application
    std::string version; // Version number
    float size; // Size of the application
    std::string units; // GB or MB
    float price; // Price in $ of the application
};

struct bst { // A binary search tree
    struct app_info record; // Information about the application
    struct bst* left;  // Pointer to the left subtree
    struct bst* right;  // Pointer to the right subtree
};

struct categories {
    std::string category; // Name of category
    struct bst* root;  // Pointer to root of search tree for this category
};

struct hash_table_entry {
    std::string app_name; // Name of the application
    struct bst* app_node; // Pointer to node in BST containing the application information
    struct hash_table_entry* next; // Next pointer for chain in separate chaining
};
