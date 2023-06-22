/*
      Program 2: Wumpus, version 2 (dynamic array)
      Player, wumpus, and both pits and both bats start in random rooms.
      Player can move to rooms adjacent to their room.
      Player must shoot arrow at wumpus' room to kill wumpus and win the game
*/
#include <ctype.h>   // for tolower
#include <stdbool.h> // for booleans
#include <stdio.h>
#include <stdlib.h> // for srand
#include <time.h>   // for time functions

//--------------------------------------------------------------------------------
// displayCave(): This function displays the map, shows which rooms are adjacent
//                to each room. Displayed when player enters 'p'
//--------------------------------------------------------------------------------
void displayCave() {
  printf("\n");
  printf("       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
}
//--------------------------------------------------------------------------------
// displayInstructions(): This function displays the instructions, the rules,
//                        and the commands the player can use.
//--------------------------------------------------------------------------------
void displayInstructions() {
  displayCave();
  printf("Hunt the Wumpus:                                             \n"
         "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
         "room has 3 tunnels leading to other rooms.                   \n"
         "                                                             \n"
         "Hazards:                                                     \n"
         "1. Two rooms have bottomless pits in them.  If you go there you fall "
         "and die.   \n"
         "2. Two other rooms have super-bats.  If you go there, the bats grab "
         "you and     \n"
         "   fly you to some random room, which could be troublesome.  Then "
         "those bats go \n"
         "   to a new room different from where they came from and from the "
         "other bats.   \n"
         "3. The Wumpus is not bothered by the pits or bats, as he has sucker "
         "feet and    \n"
         "   is too heavy for bats to lift.  Usually he is asleep.  Two things "
         "wake       \n"
         "    him up: Anytime you shoot an arrow, or you entering his room.  "
         "The Wumpus   \n"
         "    will move into the lowest-numbered adjacent room anytime you "
         "shoot an arrow.\n"
         "    When you move into the Wumpus' room, then he wakes and moves if "
         "he is in an \n"
         "    odd-numbered room, but stays still otherwise.  After that, if he "
         "is in your \n"
         "    room, he snaps your neck and you die!                            "
         "           \n"
         "                                                                     "
         "           \n"
         "Moves:                                                               "
         "           \n"
         "On each move you can do the following, where input can be upper or "
         "lower-case:  \n"
         "1. Move into an adjacent room.  To move enter 'M' followed by a "
         "space and       \n"
         "   then a room number.                                               "
         "           \n"
         "2. Shoot your guided arrow through a list of up to three adjacent "
         "rooms, which  \n"
         "   you specify.  Your arrow ends up in the final room.               "
         "           \n"
         "   To shoot enter 'S' followed by the number of rooms (1..3), and "
         "then the      \n"
         "   list of the desired number (up to 3) of adjacent room numbers, "
         "separated     \n"
         "   by spaces. If an arrow can't go a direction because there is no "
         "connecting   \n"
         "   tunnel, it ricochets and moves to the lowest-numbered adjacent "
         "room and      \n"
         "   continues doing this until it has traveled the designated number "
         "of rooms.   \n"
         "   If the arrow hits the Wumpus, you win! If the arrow hits you, you "
         "lose. You  \n"
         "   automatically pick up the arrow if you go through a room with the "
         "arrow in   \n"
         "   it.                                                               "
         "           \n"
         "3. Enter 'R' to reset the person and hazard locations, useful for "
         "testing.      \n"
         "4. Enter 'C' to cheat and display current board positions.           "
         "           \n"
         "5. Enter 'D' to display this set of instructions.                    "
         "           \n"
         "6. Enter 'P' to print the maze room layout.                          "
         "           \n"
         "7. Enter 'X' to exit the game.                                       "
         "           \n"
         "                                                                     "
         "           \n"
         "Good luck!                                                           "
         "           \n"
         " \n\n");
}
//--------------------------------------------------------------------------------
// roomTaken(): This is a helper function for the random room generation,
//              checks all previous rooms if they are the same as current room
//       input: the location array as a pointer, the number of rooms to check
//      output: true if there is a duplicate room, false if there is not.
//--------------------------------------------------------------------------------
bool roomTaken(int *arr, int k) {
  for (int i = 0; i < k; i++) {
    if (arr[i] == arr[k])
      return true;
  }
  return false;
}
//--------------------------------------------------------------------------------
// generateGame(): This function generates the room numbers of all notable rooms
//                 Notable rooms: Player, Wumpus, Pit1/2, Bats1/2
//                 Uses roomTaken() to generate non duplicate room numbers
//          input: the location array as a pointer
//         output: updates location array with room numbers of notable rooms
//--------------------------------------------------------------------------------
void generateGame(int *arr, int **mat) {
  for (int i = 0; i < 7; i++) {
    arr[i] = rand() % 20 + 1;
    while (i > 0 && roomTaken(arr, i)) {
      arr[i] = rand() % 20 + 1;
    }
  }
  // adjacent rooms arrays
  int adjMat[20][3] = {{2, 5, 8},    {1, 3, 10},  {2, 4, 12},   {3, 5, 14},
                       {1, 4, 6},    {5, 7, 15},  {6, 8, 17},   {1, 7, 9},
                       {8, 10, 18},  {2, 9, 11},  {10, 12, 19}, {3, 11, 13},
                       {12, 14, 20}, {4, 13, 15}, {6, 14, 16},  {15, 17, 20},
                       {7, 16, 18},  {9, 17, 19}, {11, 18, 20}, {13, 16, 19}};
  // set allocated array values equal to adjacent room values
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 3; j++) {
      mat[i][j] = adjMat[i][j];
    }
  }
}
//--------------------------------------------------------------------------------
// resetGame(): This function resets the room numbers of the notable rooms
//              User enters numbers for each room
//       input: the location array as a pointer
//      output: updates location array with user generated room numbers
//--------------------------------------------------------------------------------
void resetGame(int *arr) {
  printf(
      "Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, "
      "bats2, and arrow: \n");
  scanf(" %d", &arr[0]);
  scanf(" %d", &arr[1]);
  scanf(" %d", &arr[2]);
  scanf(" %d", &arr[3]);
  scanf(" %d", &arr[4]);
  scanf(" %d", &arr[5]);
  scanf(" %d", &arr[6]);
}
//--------------------------------------------------------------------------------
//     cheat(): This function displays the room numbers of each notable room.
//              Alligns room number below room contents
//       input: the location array as a pointer
//      output: displays contents of location array
//--------------------------------------------------------------------------------
void cheat(int *arr) {
  printf("Cheating! Game elements are in the following rooms: \n"
         "Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
         "%4d %5d %6d %5d %5d %5d %5d \n\n",
         arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);
}
//--------------------------------------------------------------------------------
//     guess(): This function is called when user wants to guess wumpus location
//              player wins if correct, else loses
//       input: the location array as a pointer
//      output: displays whether or not user wins/loses
//--------------------------------------------------------------------------------
void guess(int *arr) {
  int roomGuess = 0;
  printf("Enter room (1..20) you think Wumpus is in: ");
  scanf(" %d", &roomGuess);

  if (roomGuess == arr[1]) {
    printf("You won!\n");
  } else {
    printf("You lost.\n");
  }
}
//  updateBatRoom(): This function checks whether the arrow can travel through
//  the
//                player input rooms, and determines what do do in each room
//       input: location array, room matrix
//      output:
//--------------------------------------------------------------------------------
void updateBatRoom(int *arr, int **mat) {
  int curr = 0;
  int old = 0;
  if (arr[0] == arr[4]) {
    old = arr[0];
    arr[0] = rand() % 20 + 1;
    while (arr[0] == old) {
      arr[0] = rand() % 20 + 1;
    }
    curr = arr[4];
    printf("Woah... you're flying! \n");
    printf("You've just been transported by bats to room %d.\n", arr[0]);
    arr[4] = rand() % 20 + 1;
    // set new location for bat that isn't other bat or old location
    while (arr[4] == arr[5] || arr[4] == curr)
      arr[4] = rand() % 20 + 1;
  } else if (arr[0] == arr[5]) {
    old = arr[0];
    arr[0] = rand() % 20 + 1;
    while (arr[0] == old) {
      arr[0] = rand() % 20 + 1;
    }
    curr = arr[5];
    printf("Woah... you're flying! \n");
    printf("You've just been transported by bats to room %d.\n", arr[0]);
    // set new location for bat that isn't other bat or old location
    while (arr[4] == arr[5] || arr[5] == curr)
      arr[5] = rand() % 20 + 1;
  }
}
//--------------------------------------------------------------------------------
//  checkDeath(): This function checks whether the player is in a wumpus or pit
//  room
//       input: room numbers, room matrix
//      output: exit bool is changed to TRUE if player dies
//--------------------------------------------------------------------------------
void checkDeath(int *arr, int **mat, bool *exit) {
  if (arr[0] == arr[1]) {
    if (arr[1] % 2 != 0) {
      printf("You hear a slithering sound, as the Wumpus slips away. \n"
             "Whew, that was close! \n");
      arr[1] = mat[arr[1] - 1][0];
    } else {
      printf(
          "You briefly feel a slimy tentacled arm as your neck is snapped. \n"
          "It is over.\n");
      *exit = true;
    }
  } else if (arr[0] == arr[2] || arr[0] == arr[3]) {
    printf("Aaaaaaaaahhhhhh....   \n");
    printf("    You fall into a pit and die. \n");
    *exit = true;
  }
}
//--------------------------------------------------------------------------------
//  checkAdj(): This function checks whether the players room is adjacent to
//              a another room.
//       input: 2 room numbers, pointer to adjacenty array
//      output: true if room 1 is adjacent to room 2, else false
//--------------------------------------------------------------------------------
bool checkAdj(int room1, int room2, int **mat) {
  for (int i = 0; i < 3; i++) {
    if (room1 == mat[room2 - 1][i])
      return true;
  }
  return false;
}
//--------------------------------------------------------------------------------
// checkRoom(): This function determines what to do when player enters a room.
//       input: the location array as a pointer, pointer to adj. matrix, end
//       bool
//      output: sets bool to True if game is over, else displays room info
//--------------------------------------------------------------------------------
void checkRoom(int *arr, int **mat, bool *exit) {
  checkDeath(arr, mat, exit);
  if (arr[0] == arr[4] || arr[0] == arr[5]) {
    updateBatRoom(arr, mat);
    checkDeath(arr, mat, exit);
  }
  if (!*exit) {
    if (arr[0] == arr[6]) {
      printf("Congratulations, you found the arrow and can"
             " once again shoot.\n");
      arr[6] = -1;
    }
    printf("You are in room %d. ", arr[0]);
    if (checkAdj(arr[0], arr[1], mat)) {
      printf("You smell a stench. ");
    }
    if (checkAdj(arr[0], arr[2], mat) || checkAdj(arr[0], arr[3], mat)) {
      printf("You feel a draft. ");
    }
    if (checkAdj(arr[0], arr[4], mat) || checkAdj(arr[0], arr[5], mat)) {
      printf("You hear rustling of bat wings. ");
    }
    printf("\n\n");
  }
}
//--------------------------------------------------------------------------------
// movePlayer(): This is a helper function for the random room generation,
//              checks all previous rooms if they are the same as current room
//        input: the location array as a pointer, pointer to adj. matrix,
//        count
//       output: updates player location with desired move if adjacent and
//               count++,
//--------------------------------------------------------------------------------
void movePlayer(int *arr, int **mat, int *count) {
  int toRoom = 0;
  scanf(" %d", &toRoom);
  if (checkAdj(toRoom, arr[0], mat)) {
    arr[0] = toRoom;
    *count += 1;
  } else {
    printf("Invalid move.  Please retry. \n");
  }
}
//--------------------------------------------------------------------------------
//  shootArrow(): This function checks begins the process of shooting an arrow
//                Asks for user input to rooms, checks rooms if the are valid
//                Moves arrow thorugh input rooms, or richochets if invlad
//                room
//       input: location array, room matrix, count
//      output: can kill player/wumpus, moves arrow location to final room
//              count++
//--------------------------------------------------------------------------------
void shootArrow(int *arr, int **mat, bool *exit, int *count) {
  int size = 0;
  *exit = false;
  if (arr[6] != -1) {
    printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
  } else {
    // Prompt user to enter input
    printf("Enter the number of rooms (1..3) into which you want to shoot,"
           " followed by the rooms themselves: ");
    scanf(" %d", &size);
    if (size > 3) {
      printf(
          "Sorry, the max number of rooms is 3.  Setting that value to 3.\n");
      size = 3;
    }
    size += 1;
    int *arrowPath = (int *)malloc((size) * sizeof(int));
    arrowPath[0] =
        arr[0]; // arrow's inital room (player room) is starting point
    for (int i = 1; i < size; i++) {
      scanf(" %d", &arrowPath[i]);
    }
    for (int i = 1; i < size && !*exit; i++) {
      // check if user input room is adj to current arrow room, else ricochet
      if (checkAdj(arrowPath[i], arrowPath[i - 1], mat)) {
        arr[6] = arrowPath[i];
        if (arr[6] == arr[0]) {
          printf("You just shot yourself.  \n"
                 "Maybe Darwin was right.  You're dead.\n");
          *exit = true;
        }
        if (arr[6] == arr[1]) {
          printf("Wumpus has just been pierced by your deadly arrow! \n"
                 "Congratulations on your victory, you awesome hunter you.\n");
          *exit = true;
        }
      } else { // ricochet
        printf("Room %d is not adjacent.  Arrow ricochets...\n", arrowPath[i]);
        // arrow location becomes lowest # adj room to curr arrow room
        arr[6] = mat[arrowPath[i - 1] - 1][0];
        if (arr[6] == arr[0]) {
          printf("You just shot yourself, and are dying.\n"
                 "It didn't take long, you're dead.\n");
          *exit = true;
        }
        if (arr[6] == arr[1]) {
          printf("Your arrow ricochet killed the Wumpus, you lucky dog!\n"
                 "Accidental victory, but still you win!\n");
          *exit = true;
        }
      }
    }
    arr[1] = mat[arr[1] - 1][0];
  }
  *count += 1;
}
//--------------------------------------------------------------------------------
int main(void) {
  // Seed the random number generator.  Change seed to time(0) to change
  // output each time.
  // srand(time(0));
  srand(1);

  char userIn = 'a';
  bool gameover = false;
  int count = 1;
  int toRoom = 0;
  int *locations = (int *)malloc(7 * sizeof(int));
  // {player, wumpus, pit1, pit2, bat1, bat2}
  for (int i = 0; i < 7; i++) {
    // set all initial loactoins to 0;
    locations[i] = 0;
  }
  // matrix that stores all the adjacent rooms
  // adjMat[currentRoom-1] = {adjacent rooms}
  // dynamically allcated with preset size
  int **roomArr = (int **)malloc(20 * sizeof(int *));
  for (int i = 0; i < 20; i++) {
    roomArr[i] = (int *)malloc(3 * sizeof(int));
  }

  generateGame(locations, roomArr);

  while (userIn != 'x') {

    checkRoom(locations, roomArr, &gameover);

    // prompt user to enter command
    if (!gameover) {
      printf("%d. Enter your move (or 'D' for directions): ", count);
      scanf(" %c", &userIn);
      userIn = tolower(userIn);
    }
    if (gameover)
      userIn = 'x';
    if (userIn == 'r') {
      resetGame(locations);
    } else if (userIn == 'c') {
      cheat(locations);
    } else if (userIn == 'd') {
      displayInstructions();
    } else if (userIn == 'p') {
      displayCave();
    } else if (userIn == 's') {
      shootArrow(locations, roomArr, &gameover, &count);
    } else if (userIn == 'm') {
      movePlayer(locations, roomArr, &count);
    }

    if (userIn == 'x') {
      printf("\nExiting Program ...\n");
    }
  }
  for (int i = 0; i < 20; i++) {
    free(roomArr[i]);
  }
  free(roomArr);
  free(locations);
  return 0;
}