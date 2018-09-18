#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char *argv[]){
  FILE *fp;
  char *line;
  int vals[8192];

  if(argc == 2){
    //opens user specified partition
    fp = fopen(argv[1], "r");
  }

  if(fp == NULL){
    //if the file is unreachable/doesnt exist
    printf("Error: could not open partition\n");
    //the program errors out and exits
    exit(EXIT_FAILURE);
  }

  //seeks the location of the primary superblock
  fseek(fp, 1024, SEEK_SET);
  //reads the whole block
  fread(vals, 512, 1, fp);
  //close file pointer
  fclose(fp);

  //prints out desired values at their assumed locations within the superblock
  printf("Total Inodes:           %d\n", vals[0]);
  printf("Total Blocks:           %d\n", vals[1]);
  printf("Reserved Blocks:        %d\n", vals[2]);
  printf("Free blocks:            %d\n", vals[3]);
  printf("Free inodes:            %d\n", vals[4]);
  printf("First useful block:     %d\n", vals[5]);
  printf("Block size:             %lf\n", pow(2, 10 + vals[6]));
  printf("Blocks per group:       %d\n", vals[9]);
  printf("Inodes per group:       %d\n", vals[10]);
  printf("Magic Signature:        %02x\n", vals[14]);
  printf("Size of inode structure:%d\n", vals[22]);
  printf("Block group number:     %d\n", vals[17]);
  printf("Blocks to preallocate:  %d\n", vals[18]);

  return 0;
}
