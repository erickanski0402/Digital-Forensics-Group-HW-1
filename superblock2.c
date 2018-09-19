#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define superblockSize 512
#define superblockOffset 1024

struct superblockValues{
  int totalInodes;
  int totalBlocks;
  int reservedBlocks;
  int freeBlocks;
  int freeInodes;
  int firstUsefulBlock;
  int blockSize;
  int blocksPerGroup;
  int inodesPerGroup;
  int magicSignature;
  int inodeStructure;
  int group;
  int preallocate;
};

void printSuperblock(struct superblockValues);

int main(int argc, char *argv[]){
  FILE *fp;
  char *line;
  int vals[superblockSize];
  struct superblockValues superblock;

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
  fseek(fp, superblockOffset, SEEK_SET);
  //reads the whole block
  fread(vals, superblockSize, 1, fp);
  //close file pointer
  fclose(fp);

  //each value requested in the superblock is found in its predefined location
  //as per ext4 superblock format
  superblock.totalInodes = vals[0];
  superblock.totalBlocks = vals[1];
  superblock.reservedBlocks = vals[2];
  superblock.freeBlocks = vals[3];
  superblock.freeInodes = vals[4];
  superblock.firstUsefulBlock = vals[5];
  superblock.blockSize = pow(2, 10 + vals[6]);
  superblock.blocksPerGroup = vals[9];
  superblock.inodesPerGroup = vals[10];
  superblock.magicSignature = vals[14];
  superblock.inodeStructure = vals[22];
  superblock.group = vals[17];
  superblock.preallocate = vals[18];

  //prints out desired values at their assumed locations within the superblock
  printSuperblock(superblock);

  return 0;
}

void printSuperblock(struct superblockValues superblock){
  printf("Total Inodes:           %d\n", superblock.totalInodes);
  printf("Total Blocks:           %d\n", superblock.totalBlocks);
  printf("Reserved Blocks:        %d\n", superblock.reservedBlocks);
  printf("Free blocks:            %d\n", superblock.freeBlocks);
  printf("Free inodes:            %d\n", superblock.freeInodes);
  printf("First useful block:     %d\n", superblock.firstUsefulBlock);
  printf("Block size:             %d\n", superblock.blockSize);
  printf("Blocks per group:       %d\n", superblock.blocksPerGroup);
  printf("Inodes per group:       %d\n", superblock.inodesPerGroup);
  printf("Magic Signature:        %02x\n", superblock.magicSignature);
  printf("Size of inode structure:%d\n", superblock.inodeStructure);
  printf("Block group number:     %d\n", superblock.group);
  printf("Blocks to preallocate:  %d\n", superblock.preallocate);
}
