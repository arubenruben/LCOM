#pragma once

/** @defgroup vetor vetor
 * @{
 *
 *  Functions to manipulate vectors
 */

#define W_KEY_MAKECODE 0x11
#define A_KEY_MAKECODE 0x1e
#define D_KEY_MAKECODE 0x20
#define S_KEY_MAKECODE 0x1f
#define R_KEY_MAKECODE 0x13
#define SPACE_KEY_MAKECODE 0x39

struct boot_resources;
struct Axe_taurus;
struct Fantasma;
struct fireball;

enum Element_type
{
    Is_Projectil, //if element is a fireball(projectile)
    Is_Enemy      // if elements is a enemy, axe_taurus, hell_dog, or ghost
};

enum Enemy_type
{
    Is_Axe_taurus, //if enemy tpye is a axe_taurus
    Is_Fantasma,   //if enemy type is a ghost
    Is_Helldog     // if enemy is a helldog
};

typedef struct
{
    enum Enemy_type type;
    union xwz {
        struct Axe_taurus *e1;
        struct Fantasma *e2;
        struct Helldog *e3;
    } union_enemies;
} enemies;

typedef struct
{
    struct fireball *obj;
} projectil;

typedef struct
{
    enum Element_type type;
    union xyz {
        enemies *obj;
        projectil *proj;
    } union_type_elementos;
} v_elements;

typedef struct
{
    /** number of elements of the vector */
    int tamanho;
    /** vector capacity */
    int capacidade;

    int n_balas;

    int n_enemies;
    /** array of elemnts*/
    v_elements *element;

} vector;

/**
 * @brief Tcreates a new vector 
 * 
 * alocates memory for a new vector
 * 
 * return pointer to a new vector
 */
vector *vetor_novo();

/**
 * @brief deletes a vector
 *
 * removes all elements from the vector and then frees the pointer
 *
 * @param vec the user wishes to delete
 * 
 * @return doesnt return anything
 */
void vetor_apaga(vector *vec);

/**
 * @brief gets the size of a vector
 * 
 * @param vector the user wants to know the size
 * 
 * @return returns the size of the vector
 */
int vetor_tamanho(vector *vec);

/**
 * @brief returns the pointer the a certain element of the vector
 *
 * @param vec, vector that holds the element the user want to get
 * @param indice, numbered place in the vector where the element is
 *
 *  @return Return a pointer to a struct v_elements
 */
v_elements *vetor_elemento(vector *vec, int indice);

/**
 * @brief inserts a elements of our choosing into a vector
 *
 * @param  vect, vector the user wants to insert the elemnt
 * @param  start, struct that contains all the varaibles, structs necessary to run the game
 * @param  type of element IS_projetil or IS_enemy
 * @param  ene_type, enemy type we want to insert if elemnt type is IS_enemy
 * @param  pos, position we want to insert the element on the vector , if -1 it inserts at the end of the vector

 * @return Return 0 upon success and non-zero otherwise
 */
int vetor_insere(vector *vec, struct boot_resources *start, enum Element_type type, enum Enemy_type ene_type, int pos, int player);

/**
 * @brief removes an element from a vector
 *
 * @param veec, vector we want to eliminate the element
 * @param pos, numbered position on the vector of the element the user wants to eliminate
 *
 *  @return Return 0 upon success and non-zero otherwise
 */
int vetor_remove(vector *vec, int pos);

/**
 * @brief verifies if the file exits or not
 * 
 * @param filename, name of the file 
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int fileExists(const char *filename);
