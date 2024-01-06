/********* main.c *********/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{

    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
 
  printf("\n***********************************************\n");
  printf("        Welcome to Text-Based Facebook\n");

  printf("***********************************************\n");

  int user_choice = 0;
      char currentUsername[30];

      while (user_choice != 3) {
          print_main_menu();
          printf("\nEnter your choice: ");
          scanf("%d", &user_choice);
          getchar();
          if (user_choice == 3) {
              
              printf("\n***********************************************\n");
              printf("   Thank you for using Text-Based Facebook\n");
              printf("               Goodbye!\n");
              printf("***********************************************\n");
              teardown(users);
          } 

          else if (user_choice == 1) {
              register_user(&users);
          } else if (user_choice == 2) {
              if (login_user(users, currentUsername) != NULL) {
                int userchoice = 0;
  while (userchoice != 5) {
    print_menu();

    char userpass[50];

    printf("\nEnter your choice: ");
    scanf("%d", &userchoice);
    if (userchoice <= 0 || userchoice > 6) {
      printf("Invalid choice. Please try again.\n");
    }

 else if (userchoice == 1) {
    printf("Enter a new password that is up to 15 characters: ");
    scanf("%s", userpass);


    user_t* current = find_user(users, currentUsername);

    if (current != NULL) {
        strcpy(current->password, userpass);
        printf("\n**** Password changed! ****\n");
    } else {
        printf("\nUser not found. Password not changed.\n");
    }
}


    else if (userchoice == 2) {

        int userchoicePost = 0;
        while (userchoicePost != 3) {

          printf("\n----------------------------------------------\n");
          printf("            %s's posts\n", currentUsername);
          display_user_posts(find_user(users, currentUsername));
          printf("----------------------------------------------\n");
          printf("\n1. Add a new user post\n");
          printf("2. Remove a users post\n");
          printf("3. Return to main menu\n\n");
          printf("Your choice is: ");
          scanf("%d", &userchoicePost);

          if (userchoicePost == 1) {
            char usertext[250];
            printf("Enter your post content: ");
            getchar(); 
            fgets(usertext,sizeof(usertext),stdin); 
            usertext[strcspn(usertext, "\n")] = '\0'; 
            add_post(find_user(users, currentUsername), usertext);
            printf("Post added to your profile.");

          }

          else if (userchoicePost == 2) {
            int postdelete;
            printf("Which post do you want to delete? ");
            scanf("%d", &postdelete);
            post_t* count = find_user(users, currentUsername)->posts;

            int leng = 0;
            while (count != NULL) {
              count = count->next;
              leng++;
            }

            if (postdelete <= 0 || postdelete > leng) {
              printf("Invalid post's number");

            } else {
              delete_post(find_user(users, currentUsername), postdelete);
              printf("Post %i was deleted successfully!", postdelete);
            }
          }
        
      }

    }

    else if (userchoice == 3) {

   
        int userchoicefriends = 0;
        while (userchoicefriends != 4) {
          printf("\n-----------------------------------------------\n");
          printf("              %s's friends", currentUsername);
          printf("\n-----------------------------------------------\n");

          printf("\n1. Display all user's friends\n");
          printf("2. Add a new friend\n");
          printf("3. Delete a friend\n");
          printf("4. Display a friend's posts\n");
          printf("5. Return to main menu\n");

          printf("\nYour choice: ");
          scanf("%d", &userchoicefriends);

          if (userchoicefriends == 1) {
            display_user_friends(find_user(users, currentUsername));
          } else if (userchoicefriends == 2) {
            char friendname[50];
            printf("Enter a new friends' name: ");
            scanf("%s", friendname);
            user_t* friend_user = find_user(users, friendname);

            if (friend_user == NULL) {
                printf("User '%s' does not exist. Cannot add as a friend.\n", friendname);
            }

            else {add_friend(find_user(users, currentUsername), friendname);
            
            printf("Friend added to the list.\n");
            }
          } else if (userchoicefriends == 3) {
            char friendname[250];
            display_user_friends(find_user(users, currentUsername));
            printf("\n\nEnter a friend's name to delete: ");
            scanf("%s", friendname);
            user_t* current_user = find_user(users, currentUsername);
            delete_friend(current_user, friendname);

            display_user_friends(current_user);
          }

          else if (userchoicefriends == 4){
            
            char friend_name[50];
            printf("Enter the name of the friend to display their posts: ");
            scanf("%s", friend_name);

            user_t *user1= malloc(sizeof(user_t));
            user1 = find_user(users, currentUsername);

            user_t* friend_user = find_user(users, friend_name);

            if (friend_user != NULL) {
                user1->friends->posts = &(friend_user->posts);
                if (user1->friends->posts != NULL){
                }
            } else {
                user1->posts = NULL; // if friend is not found set posts to NULL
            }

            user_t *friend_user1 = find_user(users, friend_name);

            if (user1->friends->posts != NULL) {

              display_user_posts(find_user(users, friend_name));
            }
            else {
              printf("\nFriend '%s' not found or has no posts.\n", friend_name);
          
                  }
                
          }
      }
    } else if (userchoice == 4) {

      display_all_posts(users);

    } 
  }
                 
              } else {
                  printf("Invalid username/password combination. Please try again.\n");
              }
          } 
          else {
              printf("Invalid choice. Please try again.\n");
          }
    }




  
}

   

   






