/********* definitions.c ********/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "a2_nodes.h"
#include "a2_functions.h"




/*
   Function that creates a new user and adds it to a sorted (ascending order)
   linked list at the proper sorted location. Return the head of the list.
*/
user_t* add_user(user_t* users, const char* username, const char* password)
{
  user_t* new_user = malloc(sizeof(user_t));
  assert(new_user != NULL);
  strcpy(new_user->username, username);
  strcpy(new_user->password, password);

  new_user->posts = NULL;
  new_user->friends = NULL;
  user_t* current = users;
  user_t* prev = NULL;

  if (users == NULL || strcmp(users->username, new_user->username) > 0) {
    new_user->next = users;
    return new_user;
  }

  while (current != NULL && strcmp(current->username, new_user->username) < 0) {
    prev = current;
    current = current->next;
  }

  if (current == NULL) {
    prev->next = new_user;
  } else {
    prev->next = new_user;
    new_user->next = current;
  }

  return users;
}

/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t* find_user(user_t* users, const char* username)
{

  for (; users != NULL;) {
    if (strcmp(users->username, username) == 0) {
      return users;
    } else {
      users = users->next;
    }
  }
  return NULL;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t* create_friend(const char* username)
{

  friend_t* newfriend = malloc(sizeof(friend_t));
  strcpy(newfriend->username, username);
  newfriend->next = NULL;
  return newfriend;
}

/*
   Function that links a friend to a user. The friend's name should be added
   into a sorted (ascending order) linked list.
*/

void add_friend(user_t* user, const char* friend_name)
{
    friend_t* friend = create_friend(friend_name);

    user_t* friend_user = find_user(user, friend_name);

    if (friend_user != NULL) {
        friend->posts = &(friend_user->posts);
    } else {
        friend->posts = NULL; 
    }

    if (user->friends == NULL ||
        strcmp(friend_name, user->friends->username) < 0) {
        friend->next = user->friends;
        user->friends = friend;
        friend->posts=NULL;
        return;
    }

    friend_t* current = user->friends;
    while (current->next != NULL &&
           strcmp(current->next->username, friend_name) < 0) {
        current = current->next;
    }

    friend->next = current->next;
    current->next = friend;
}


/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t* user, char* friend_name)
{
  friend_t* check = user->friends;
  friend_t* prev = NULL;

  while (check != NULL && strcmp(check->username, friend_name) != 0) {
    prev = check;
    check = check->next;
  }

  if (check == NULL) {
    printf("Invalid friend's name");
  } else {
    if (prev == NULL) {
      user->friends = check->next;
    } else {
      prev->next = check->next;
    }

    free(check);
    return 1;
  }

  return 0;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t* create_post(const char* text)
{
  post_t* new_post = malloc(sizeof(post_t));
  strcpy(new_post->content, text);

  return new_post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added
   following the stack convention (LIFO) (i.e., to the beginning of the Posts
   linked list).
*/
void add_post(user_t* user, const char* text) {
    post_t* new_post = create_post(text);


    if (user->posts == NULL) {
        user->posts = new_post; 
    } else {

        new_post->next = user->posts;
        user->posts = new_post;
    }
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t* user, int number)
{
  int delete = number - 1;
  post_t* current = user->posts->next;
  post_t* temp = user->posts;

  if (delete == 0) {
    user->posts = current;
    free(temp);
    return 1;
  }

  else {
    for (int i = 1; current != NULL && i <= delete; i++) {
      if (i == delete) {
        temp->next = current->next;
        free(current);
        return 1;

      } else {
        current = current->next;
        temp = temp->next;
      }
    }
  }

  return 0;
}

void display_user_post(user_t* user) {
    char friend_name[30];
    printf("Enter the name of the friend to display their posts: ");
    scanf("%s", friend_name);

    user_t *friend_user = find_user(user, friend_name);

    if (friend_user != NULL) {
        friend_t* friend = friend_user->friends;
        while (friend != NULL) {
            if (strcmp(friend->username, friend_name) == 0) {
                printf("\nFound friend '%s'.\n", friend_name);
                if (friend->posts != NULL) {
                    printf("\n%s's Posts:\n", friend->username);
                    post_t** friend_posts = friend->posts;
                    while (*friend_posts != NULL) {
                        printf("- %s\n", (*friend_posts)->content);
                        friend_posts = &((*friend_posts)->next);
                    }
                } else {
                    printf("\n%s has no posts.\n", friend->username);
                }
                return;
            }
            friend = friend->next;
        }
    }
    printf("\nFriend '%s' not found or has no posts.\n", friend_name);
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t* user)
{

  post_t* currentPost = user->posts;

  if (user->posts->content == NULL) {
    printf("No posts available for %s\n", user->username);
  } else {
    for (int i = 1; currentPost != NULL; i++) {
      printf("%d- %s: %s\n", i, user->username, currentPost->content);
      currentPost = currentPost->next;
    }
  }
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t* user)
{

  printf("\nList of %s's friends:", user->username);

  friend_t* current = user->friends;

  if (user->friends == NULL) {
    printf("\nNo friends available for %s.\n", user->username);
  }

  else {
    for (int i = 1; current != NULL; i++) {
      printf("\n%d- %s", i, current->username);
      current = current->next;
    }
  }
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t* users)
{

  user_t* current = users;
  
  char next2 = 'Y';

  
   while (current != NULL && (next2 == 'Y' || next2 == 'y')) {
      int i;
      for (i = 0; i < 2 && current != NULL; i++) {
         display_user_posts(current);
         current = current->next;
      }

      if (current == NULL) {
          printf("All posts have been displayed\n");
      } else {
         printf("\nDo you want to display next 2 users' posts? (Y/N): ");
         scanf(" %c", &next2);
         printf("\n");
         while (getchar() != '\n');
        }
    
}
}
/*
   Fucntion that free all users from the database before quitting the
   application.
*/
void teardown(user_t* users) {
    user_t* current_user = users;
    while (current_user != NULL) {
   
        friend_t* current_friend = current_user->friends;
        while (current_friend != NULL) {
            friend_t* temp_friend = current_friend;
            current_friend = current_friend->next;
            free(temp_friend);
        }

        post_t* current_post = current_user->posts;
        while (current_post != NULL) {
            post_t* temp_post = current_post;
            current_post = current_post->next;
            free(temp_post);
        }

        user_t* temp_user = current_user;
        current_user = current_user->next;
        free(temp_user);
    }
}

/*
   Function that prints the main menu with a list of options for the user to
   choose from
*/
void print_menu()
{
  printf(
    "\n1. Manage a user's profile (change password)\n2. "
    "Manage a user's posts (display/add/remove)\n3. Manage a user's friends "
    "(display/add/remove)\n4. Display All Posts\n5. Logout\n");
}


void print_main_menu() {
    printf("\n***********************************************\n");
    printf("                  Main Menu:\n");
    printf("***********************************************\n");
    printf("1. Register a new User\n");
    printf("2. Login with existing user's information\n");
    printf("3. Exit\n");
}

user_t* login_user(user_t* users, char* currentUsername) {
    char username[30];
    char password[15];

    printf("\nEnter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    user_t* currentUser = find_user(users, username);

    if (currentUser != NULL && strcmp(currentUser->password, password) == 0) {
        strcpy(currentUsername, currentUser->username);
          printf("\n***********************************************\n");
          printf("              Welcome %s\n", currentUsername);

          printf("***********************************************\n");

        return currentUser; 
    }

    return NULL; // Invalid username/password combination
}

//i am using a double pointer for this function to modify the original list of users
void register_user(user_t** users) {
    char username[30];
    char password[15];

    printf("\nEnter a username: ");
    scanf("%s", username);

    if (find_user(*users, username) == NULL) {
        printf("Enter a password (up to 15 characters): ");
        scanf("%s", password);
        
        *users = add_user(*users, username, password);
        printf("User registered successfully!\n");
    } else {
        printf("Username already exists. Please choose a different username.\n");
    }
}

user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
