#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

//A function that generates a random number by reading in
//the correct number of bytes from /dev/random

int randomly(){
  int i = open("/dev/urandom", O_RDONLY);
  int num;
  //check for error
  read(i, &num, sizeof(int));
  if(errno){
    printf("Yikes!\nError number: %d\t Error message: %s\n", errno, strerror(errno));
  }
  close(i);

  return i;
}

int main(){
//Populates an array with 10 random numbers generated by your random function (print out each value)
  int randArray[10];
  printf("Populating the array..\n");
  int i;
  printf("Original array: [");
  for(i = 0; i < 10; i++){
    randArray[i] = randomly();
    if(i != 9){
      printf("%d, ", randArray[i]);
    }
    else{
      printf("%d]", randArray[i]);
      printf("\n+++++++++++++++++++++\n\n");
    }
  }

//Writes the array to a file
  printf("Writing the array to a file...\n");
  int writing = open("testing.txt", O_CREAT | O_WRONLY, 0644);
  if(errno){
    printf("Yikes!\nError number: %d\t Error message: %s\n", errno, strerror(errno));
  }
  write(writing, &randArray, sizeof(randArray));

//Reads that file into a different array
  printf("Now let's read the file into a different array...\n");
  int diffArray[10];
  int reading = open("testing.txt", O_RDONLY);
  if(errno){
    printf("Yikes!\nError number: %d\t Error message: %s\n", errno, strerror(errno));
  }
  read(reading, &diffArray, sizeof(diffArray));

  //Prints out the contents of the second array to verify the random numbers are the same from step 1
  printf("Verification that written values were the same:\n");
  int wee;
  printf("Second array: [");
  for(wee = 0; wee < 10; wee++){
    if(wee != 9){
      printf("%d, ", randArray[i]);
    }
    else{
      printf("%d]", randArray[i]);
    }
  }
  return 0;
}
