/**
Author: Ichiro Miyasato
Date: 25 June 2024
 */


#include "student_code.h"
#include "stdlib.h"
#include "string.h"



/***********
 * Strings *
 ***********/

/**
 * This function takes in a c-string and returns it's length.  It **does not** use the strlen(...) function in string.h
 * @param str The string that we will be finding the length of.  It will be null terminated
 * @return The length of the input string
 */
int get_str_length(char* str) {
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  // Question: How do we know that we've gotten to the end of a c-string?
  // Answer: When we encounter a null terminator '\0'.
  int stringLength = 0;
  while(str[stringLength] != '\0'){
    stringLength++;
  }
  return stringLength;

}

/**
 * Returns a pointer to a copy of the original string.  It **does not** use strcpy or any related function (but may use strlen)
 * @param str An input string that is null terminated
 * @return a new char* that copies the input string str
 */
char* copy_str(char* str) {
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  int stringLength = get_str_length(str);
  // allocate enough memory to account for the number of chars in the string and the null terminator
  char * copyString = (char *)malloc((stringLength + 1) * sizeof(char));
  // if the string to copy is empty, simply return an empty string
  if (copyString == NULL) {
    return "";
  }
  for(int i = 0; i <= stringLength; i++) {
    copyString[i] = str[i];
  }
  return copyString;
}

/**
 * Truncates a string to a the given length, not including the null terminator.  If the given length is longer than the original string the original string is returned unchanged.
 * @param str A null-terminated input string
 * @param new_length The length of the output string.
 */
void truncate_string(char* str, int new_length) {
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  int lengthTrack = get_str_length(str);
  if (new_length >= lengthTrack) {
    return;
  }
  str[new_length] = '\0';

}

/**
 * Converts a given string, str, to all uppercase letters
 * @param str A null-terminated input string
 */
void to_uppercase(char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      // The difference between uppercase and lowercase in ASCII is 32.
      str[i] -= 32;
    }
  }
}

/**
 * Converts a given string, str, to all lowercase letters
 * @param str A null-terminated input string
 */
void to_lowercase(char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      // The difference between uppercase and lowercase in ASCII is 32.
      str[i] += 32;
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
  if (target >= 'A' && target <= 'Z') {
    target += 32;
  }
  // We want to make everything in the string lowercase since the function will not be case sensitive.
  char lowercaseChar;
  for (int i = 0; str[i] != '\0'; i++) {
    lowercaseChar = str[i];
    if (lowercaseChar >= 'A' && lowercaseChar <= 'Z') {
      lowercaseChar += 32;
    }
    if (lowercaseChar == target) {
      return i;
    }
  }
  // If the character wasn't found in the for loop, then it doesn't exist in the string.
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
  if (target >= 'A' && target <= 'Z') {
    target += 32;
  }
  int stringLength = get_str_length(str);
  int last_index = -1;
  // We want to make everything in the string lowercase since the function will not be case sensitive.
  char lowercaseChar;
  for(int i = stringLength - 1; i >= 0; i--) {
    lowercaseChar = str[i];
    if (lowercaseChar >= 'A' && lowercaseChar <= 'Z') {
      lowercaseChar += 32;
    }  
    if (lowercaseChar == target) {
      last_index = i;
      break;
    }
  }
  return last_index;
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
  Person retPerson;
  strcpy(retPerson.first_name, first_name);
  strcpy(retPerson.last_name, last_name);
  retPerson.age = age;
  return retPerson;
}
/**
 * Return a string containing the full name and age of the person in the format "First Last (age)"
 * @param person The person to get the relevant string for
 * @return A string containing the name of the person
 */
char* person_to_string(Person person) {
  // hint: sprintf
  // The +10 is to account for 2 spaces, 3 assumed age digits, 2 parentheses, 1 null terminator, and 2 characters of wiggle space just in case.
  int personStrLength = strlen(person.first_name) + strlen(person.last_name) + 10;

  // Allocate enough space for the resulting string
  char* personStr = (char *)malloc(personStrLength * sizeof(char));

  // Format the string
  sprintf(personStr, "%s %s (%d)", person.first_name, person.last_name, person.age);

  return personStr;
}

/**
 * A function to create a new empty group
 * @param group_name A null-terminuated string to name the new group
 * @return A new Group struct
 */
Group group_make_new(char* group_name) {
  // Initialize all the variables in the struct.
  Group retGroup;
  retGroup.group_name = (char*)malloc((strlen(group_name) + 1) * sizeof(char));
  strcpy(retGroup.group_name, group_name);

  for (int i = 0; i < GROUP_MAX_SIZE; i++) {
    retGroup.group_members[i] = NULL;
  }

  retGroup.num_members = 0;
  
  return retGroup;
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
  return GROUP_MAX_SIZE - group.num_members;
}

/**
 * Add a person to the group if possible and return the total number of free space in the group. Otherwise return -1.
 * @param group A group struct that contains some number of people
 * @param person_to_add The person to add to the group
 * @return The number of free spaces after add the new person, -1 if the group was already full
 */
int add_person(Group* group, Person* person_to_add) {
  // Question: Say we have already added a person to the group and try to add them again.  What should be we do?  Where can we check what the expected behavior is?
  // Answer: We compare each of the variables of the Person struct between the person in the group and the person to add. If all of the variables are the same,
  //then it is safe to assume that it is the same person. We check this before we add the new person.
  if (group->num_members >= GROUP_MAX_SIZE) {
    return -1;
  }
  
  Person* personInGroup = NULL;
  // Check if the person to add is already in the group.
  for (int i = 0; i < group->num_members; i++) {
    personInGroup = group->group_members[i];
    if(strcmp(personInGroup->first_name, person_to_add->first_name) == 0 &&
      strcmp(personInGroup->last_name, person_to_add->last_name) == 0 &&
      personInGroup->age == person_to_add->age) {
      return -1;
    }
  }

  // Add the person at the position designated by the number of members and then increment number of members.
  group->group_members[group->num_members] = person_to_add;
  (group->num_members)++;

  return free_spaces_in_group(*group);

}



/**
 * Remove a person from the group if they are in the group, otherwise return -1
 * @param group A Group struct that contains some number of people
 * @param person_to_remove A person to remove from the group
 * @return The number of people remaining in the group, -1 if the person was not in the group
 */
int remove_person(Group* group, Person* person_to_remove) {
  Person* personInGroup = NULL;
  for (int i = 0; i < group->num_members; i++) {
    personInGroup = group->group_members[i];
    if (strcmp(personInGroup->first_name, person_to_remove->first_name) == 0 &&
      strcmp(personInGroup->last_name, person_to_remove->last_name) == 0 &&
      personInGroup->age == person_to_remove->age) {
      // if the person is found, shift all the proceeding members down by one index
      for (int j = i; j < group->num_members - 1; j++) {
        group->group_members[j] = group->group_members[j + 1];
      }
      // Make the former index of the number of members NULL.
      group->group_members[group->num_members - 1] = NULL;
      // Decrement the number of members
      (group->num_members)--;
      return group->num_members;
    }
  }
  
  // In the case that the person was not in the group, return -1.
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
  // There are 26 letters in the alphabet.
  // If we take the input character and subtract by the first letter, we get its initial position in the alphabet.
  // If we subtract that amount by the shift_size, we get its new position relative to 'a'.
  // Add 26 to that and we get a positive alphabet position value instead of a negative one.
  // Modulo 26 handles wrap around
  // Adding the result to 'a' gets the accurate ASCII value of the shifted character.
  if (input_char >= 'a' && input_char <= 'z') {
    return (input_char - 'a' - shift_size + 26) % 26 + 'a';
  } 
  // For capital letters, it is the same idea except the positions are relative to 'A' instead.
  // To convert to lowercase, the final modulo is added to lowercase 'a'.
  if (input_char >= 'A' && input_char <= 'Z') {
    return (input_char - 'A' - shift_size + 26) % 26 + 'a';
  } 

  // If the character is not a letter, leave it as is.
  return input_char;
  
}

/**
 * Shift a character 'right' by the shift amount by subtracting the shift size.
 *  e.g. 'z' with a shift_size = 1 will become 'a'
 * @param input_char
 * @param shift_size
 * @return
 */
char shift_right(char input_char, int shift_size) {
  // This function is the similar to shift_left above, but we add the shift size instead of subtracting it.
  // This makes it unnecessary to add the 26 to account for negatives.
  if (input_char >= 'a' && input_char <= 'z') {
    return (input_char - 'a' + shift_size) % 26 + 'a';
  } 
  if (input_char >= 'A' && input_char <= 'Z') {
    return (input_char - 'A' + shift_size) % 26 + 'a';
  } 
  return input_char;
    
}

/**
 * Encrypts a string using a given shift.  Note: All characters should be converted to lowercase
 * @param input_str
 * @param shift_size
 * @return
 */
char* encrypt_caesar(char* input_str, int shift_size) {
  int encryptLength = strlen(input_str);
  char* encryptStr = (char*)malloc((encryptLength + 1) * sizeof(char));
  // Copy each character of the input into a new character array and "shift" all character values left.
  for (int i = 0; i < encryptLength; i++) {
    encryptStr[i] = shift_left((input_str[i]), shift_size);
  }
  // Don't forget the null terminator at the end.
  encryptStr[encryptLength] = '\0';
  return encryptStr;
}

/**
 * Decrypts a string using a given shift.  Note: All characters should be converted to lowercase
 * @param input_str
 * @param shift_size
 * @return
 */
char* decrypt_caesar(char* input_str, int shift_size) {
  // todo
  // To decrypt, do the same process as encrypt above but shift right instead.
  int decryptLength = strlen(input_str);
  char* decryptStr = (char*)malloc((decryptLength + 1) * sizeof(char));
  for (int i = 0; i < decryptLength; i++) {
    decryptStr[i] = shift_right((input_str[i]), shift_size);
  }
  decryptStr[decryptLength] = '\0';
  return decryptStr;
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
  // Make an array to keep track of alphabets that have been used as offsets. Initialize with 0s to denote false
  int alphaLeft[26];
  memset(alphaLeft, 0, 26 * sizeof(int));
  // If an offset is out of bounds of the alphabet or already used, this key does not have a valid decryption key.
  for (int i = 0; i < 26; i++) {
    int offset = encryption_key[i];
    if (offset < 0 || offset >= 26 || alphaLeft[offset] == 1) {
        return false;
    }
    alphaLeft[offset] = 1;
  }
  // If all the offsets are unique, then this encyption is decryptable
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

  int* decryption_key = (int*)malloc(26 * sizeof(int));
  memset(decryption_key, 0, 26 * sizeof(int));

  // match the layout for the unit tests in substitution
  for (int i = 0; i < 26; i++) {
      decryption_key[encryption_key[i]] = encryption_key[i];
  }

  return decryption_key;
}

/**
 * Takes the input string and the encryption key and encrypts the input string in place
 * @param input_str
 * @param encryption_key
 */
void encrypt_substitution(char* input_str, int* encryption_key) {
  // We simply need to add the amount specified in encryption key to the character specified in the current string index.
  while (*input_str != '\0') {
    if (*input_str >= 'a' && *input_str <= 'z') {
      *input_str = (char)('a' + encryption_key[*input_str - 'a']);
    }
    input_str++;
  }
}

/**
 * Takes an encrypted input string and a decryption key and decrypts a string in place
 * @param input_str
 * @param decryption_key
 */
void decrypt_substitution(char* input_str, int* decryption_key) {
  // We simply need to add the amount specified in encryption key to the character specified in the current string index.
  while (*input_str != '\0') {
    if (*input_str >= 'a' && *input_str <= 'z') {
      *input_str = (char)('a' + decryption_key[*input_str - 'a']);
    }
    input_str++;
  }
}




