#include "student_code.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/***********
 * Strings *
 ***********/

/**
 * This function takes in a c-string and returns it's length.  It **does not** use the strlen(...) function in string.h
 * @param str The string that we will be finding the length of.  It will be null terminated
 * @return The lenght of the inpurt string
 */
int get_str_length(char* str) {
  //     Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  // Question: How do we know that we've gotten to the end of a c-string?
  //   Answer: A c-string should be null terminated, so if we've reached that, it's the end of the road ... or string.
    int str_index = 0;

    while(str[str_index] != '\0') {
        str_index++;
    }

    return str_index;
}

/**
 * Returns a pointer to a copy of the original string.  It **does not** use strcpy or any related function (but may use strlen)
 * @param str An input string that is null terminated
 * @return a new char* that copies the input string str
 */
char* copy_str(char* str) {
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0

    int str_len = get_str_length(str);
    char *copied_str = (char *)malloc((str_len + 1) * sizeof(char));

    for(int i=0; i < str_len; i++) {
        copied_str[i] = str[i];
    }
    copied_str[str_len] = '\0';

    return copied_str;
}

/**
 * Truncates a string to a the given length, not including the null terminator.  If the given length is longer than the original string the original string is returned unchanged.
 * @param str A null-terminated input string
 * @param new_length The length of the output string.
 */
void truncate_string(char* str, int new_length) {
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0

    int str_len = get_str_length(str);
    if (new_length < str_len) {
        str[new_length] = '\0';
    }
}

/**
 * Converts a given string, str, to all uppercase letters
 * @param str A null-terminated input string
 */
void to_uppercase(char* str) {
    int str_len = get_str_length(str);

    for(int i=0; i < str_len; i++) {
        if((str[i] >= 97) && (str[i] <=122)) {
            str[i] = str[i] - 32;
        }
    }
}

/**
 * Converts a given string, str, to all lowercase letters
 * @param str A null-terminated input string
 */
void to_lowercase(char* str) {
    int str_len = get_str_length(str);

    for(int i=0; i < str_len; i++) {
        if((str[i] >= 65) && (str[i] <=90)) {
            str[i] = str[i] + 32;
        }
    }
}

/**
 * Finds the index of the first usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the first usage of the target character in the string
 */
int find_first_index(char* str, char target) {
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
    int str_len = get_str_length(str);

    for(int i=0; i < str_len; i++) {
        if(str[i] == target) {
            return i;
        }
    }
    return -1;
}

/**
 * Finds the index of the last usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the last usage of the target character in the string
 */
int find_last_index(char* str, char target) {
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
    int str_len = get_str_length(str);

    for(int i=str_len-1; i > 0; i--) {
        if(str[i] == target) {
            return i+1;
        }
    }
    return -1;
}


/**************
 * Structures *
 **************/
/**
 * Create a new person object and return the object
 * @param first_name The first name of the new person as a null-terminated string
 * @param last_name The last name of the new person as a null-terminated string
 * @param age The age of the person as an int
 * @return A Person struct containing the new person
 */
Person person_make_new(char* first_name, char* last_name, int age) {
    struct Person newPerson;

    newPerson.age = age;
    strcpy(newPerson.first_name, first_name);
    strcpy(newPerson.last_name, last_name);

    return newPerson;
}
/**
 * Return a string containing the full name and age of the person in the format "First Last (age)"
 * @param person The person to get the relevant string for
 * @return A string containing the name of the person
 */
char* person_to_string(Person person) {
  // hint: sprintf
    int max_len = sizeof person + 1;
    char *str = malloc(max_len);
    snprintf(str, max_len, "%s %s (%d)", person.first_name, person.last_name, person.age);

    return str;
}

/**
 * A function to create a new empty group
 * @param group_name A null-terminuated string to name the new group
 * @return A new Group struct
 */
Group group_make_new(char* group_name) {
    struct Group emptyGroup;

    strcpy(emptyGroup.group_name, group_name);
    emptyGroup.num_members = 0;
    
    return emptyGroup;
}

/**
 * A function to find the total number of people in the group
 * @param group A Group struct that contains some number of people
 * @return The number of users in the group
 */
int num_people_in_group(Group group) {
  return group.num_members;
}
/**
 * Get the number of free spaces remaining in the group
 * @param group A Group struct that contains some number of people
 * @return The number of free spaces in the group
 */
int free_spaces_in_group(Group group) {
  return GROUP_MAX_SIZE - num_people_in_group(group);
}

/**
 * Add a person to the group if possible and return the total number of free space in the group. Otherwise return -1.
 * @param group A group struct that contains some number of people
 * @param person_to_add The person to add to the group
 * @return The number of free spaces after add the new person, -1 if the group was already full
 */
int add_person(Group* group, Person* person_to_add) {
  // Question: Say we have already added a person to the group and try to add them again.  What should be we do?  Where can we check what the expected behavior is?
  //   Answer: We can check the unit tests for what the expected outcome is and help guide us.
    if (free_spaces_in_group(*group) <= 0) {
        return -1;
    }

    for(int i = 0; i < group->num_members; i++) {
        if((strcmp(group->group_members[i]->first_name, person_to_add->first_name) == 0) &&
            (strcmp(group->group_members[i]->last_name, person_to_add->last_name) == 0) &&
            group->group_members[i]->age == person_to_add->age) {
            return free_spaces_in_group(*group);
        }
    }

    int addIndex = GROUP_MAX_SIZE - free_spaces_in_group(*group);
    group->num_members++;
    group->group_members[addIndex] = person_to_add;

    return free_spaces_in_group(*group);
    
}

/**
 * Remove a person from the group if they are in the group, otherwise return -1
 * @param group A Group struct that contains some number of people
 * @param person_to_remove A person to remove from the group
 * @return The number of people remaining in the group, -1 if the person was not in the group
 */
int remove_person(Group* group, Person* person_to_remove) {
    
    for(int i = 0; i < group->num_members; i++) {
        if((strcmp(group->group_members[i]->first_name, person_to_remove->first_name) == 0) &&
        (strcmp(group->group_members[i]->last_name, person_to_remove->last_name) == 0) &&
        (group->group_members[i]->age == person_to_remove->age)) {
            for(int j = i; j < group->num_members-1; j++) {
                group->group_members[j] = group->group_members[j + 1];
            }
            group->num_members--;
            return free_spaces_in_group(*group);
        }
    }
  return -1;
}



/*
 * Caesar Cipher
 */
/**
 * Shift a character 'left' by the shift amount by subtracting the shift size.
 *  e.g. 'a' with a shift_size = 1 will become 'z'
 * @param input_char
 * @param shift_size
 * @return
 */
char shift_left(char input_char, int shift_size) {

    char shifted = input_char;

    if (isalpha(input_char)) {
        shifted = (tolower(input_char) - 'a' - shift_size + 26) % 26 + 'a';
    }

    return shifted;
}

/**
 * Shift a character 'right' by the shift amount by subtracting the shift size.
 *  e.g. 'z' with a shift_size = 1 will become 'a'
 * @param input_char
 * @param shift_size
 * @return
 */
char shift_right(char input_char, int shift_size) {
    char shifted = input_char;

    if (isalpha(input_char)) {
        shifted = (tolower(input_char) - 'a' + shift_size + 26) % 26 + 'a';
    }

    return shifted;
}

/**
 * Encrypts a string using a given shift.  Note: All characters should be converted to lowercase
 * @param input_str
 * @param shift_size
 * @return
 */
char* encrypt_caesar(char* input_str, int shift_size) {
    int str_len = get_str_length(input_str);
    char *encrypted_str = (char *)malloc((str_len + 1) * sizeof(char));

    for(int i=0; i < str_len; i++) {
        encrypted_str[i] = shift_left(input_str[i], shift_size);
    }
    encrypted_str[str_len] = '\0';
    return encrypted_str;
}

/**
 * Decrypts a string using a given shift.  Note: All characters should be converted to lowercase
 * @param input_str
 * @param shift_size
 * @return
 */
char* decrypt_caesar(char* input_str, int shift_size) {
    int str_len = get_str_length(input_str);
    char *decrypted_str = (char *)malloc((str_len + 1) * sizeof(char));

    for(int i=0; i < str_len; i++) {
        decrypted_str[i] = shift_right(input_str[i], shift_size);
    }
    decrypted_str[str_len] = '\0';
    return decrypted_str;
}

/*
 * General substitution Cipher
 */

/**
 * Returns true if a given encryption key has a valid decryption key.
 * @param encryption_key
 * @return
 */
bool is_reversible(int* encryption_key) {
    for (int i = 0; i < 26; i++) {
        for (int j = i+1; j < 26; j++) {
            if (encryption_key[i] == encryption_key[j]) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Generates a decryption key based on the encryption key, if one exists.  Otherwise returns NULL
 * @param encryption_key
 * @return
 */
int* get_decryption_key(int* encryption_key) {
    if (!is_reversible(encryption_key)) {
        return NULL;
    }

    int *decryption_key = malloc (sizeof (int) * 26);

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (encryption_key[j] == i) {
                decryption_key[i] = encryption_key[j];
            }
        }
    }

    return decryption_key;
}

/**
 * Takes the input string and the encryption key and encrypts the input string in place
 * @param input_str
 * @param encryption_key
 */
void encrypt_substitution(char* input_str, int* encryption_key) {
    int str_len = get_str_length(input_str);

    for (int i = 0; i < 26; i++) {
        // printf("%c: %d: %d\n", 97+i, i, encryption_key[i]);
    }

    for(int i = 0; i < str_len; i++) {
        if(isalpha(input_str[i])) {
            // printf("i: %d c:%c e: %d\n", i, input_str[i], input_str[i]-97);
            if(input_str[i]-97 != encryption_key[input_str[i]-97]){
                // printf("swap needed: %c\n", encryption_key[input_str[i]-97]+97);
                input_str[i] = encryption_key[input_str[i]-97]+97;
            }
        }
    }
    return;
}

/**
 * Takes an encrypted input string and a decryption key and decrypts a string in place
 * @param input_str
 * @param decryption_key
 */
void decrypt_substitution(char* input_str, int* decryption_key) {
    int str_len = get_str_length(input_str);

    for (int i = 0; i < 26; i++) {
        // printf("%c: %d: %d\n", 97+i, i, decryption_key[i]);
    }
    for(int i = 0; i < str_len; i++) {
        // printf("%d: %c\n", i, input_str[i]);
    }

    for(int i = 0; i < str_len; i++) {
        if(isalpha(input_str[i])) {
            // printf("i: %d c:%c e: %d\n", i, input_str[i], input_str[i]-97);
            if(input_str[i]-97 != decryption_key[input_str[i]-97]){
                // printf("swap needed: %c\n", decryption_key[input_str[i]-97]+97);
                input_str[i] = decryption_key[input_str[i]-97]+97;
            }
        }
    }
    for(int i = 0; i < str_len; i++) {
        // printf("%d: %c\n", i, input_str[i]);
    }
    
  return;
}




