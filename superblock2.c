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
} superblock;

FILE* openPartition(char*);
int* getSuperblockValues(FILE*, int*);
void setSuperblockValues(int*);
int getTotalInodes();
int getTotalBlocks();
int getReservedBlocks();
int getFreeBlocks();
int getFreeInodes();
int getFirstUsefulBlock();
int getBlockSize();
int getBlocksPerGroup();
int getInodesPerGroup();
int getMagicSignature();
int getSizeOfInodeStructure();
int getBlockGroup();
int getBlocksToPreallocate();
void printSuperblock();

int main(int argc, char *argv[]){
  FILE *fp;
  char *line;
  int *vals;

  if(argc < 2){
    printf("No parition specified");
    exit(EXIT_FAILURE);
  }else{
    //opens user specified partition
    fp = openPartition(argv[1]);
  }

  if(fp == NULL){
    //if the file is unreachable/doesnt exist
    printf("Error: could not open partition\n");
    //the program errors out and exits
    exit(EXIT_FAILURE);
  }

  //allocates memory to the integer array to store the superblock
  vals = malloc(sizeof(int)*superblockSize);
  //stores the superblock into individual integer values
  getSuperblockValues(fp, vals);

  //each value requested in the superblock is found in its predefined location
  //as per ext4 superblock format
  setSuperblockValues(vals);

  //prints out desired values at their assumed locations within the superblock
  printSuperblock(superblock);

  return 0;
}

FILE* openPartition(char* partition){
  //attempts to open the specified partition returning the file pointer to it
  return fopen(partition, "r");
}

int* getSuperblockValues(FILE* fp, int* vals){
  //seeks the location of the primary superblock
  fseek(fp, superblockOffset, SEEK_SET);
  //reads the whole block
  fread(vals, superblockSize, 1, fp);
  //close file pointer
  fclose(fp);
}

void setSuperblockValues(int *vals){
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
}

int getTotalInodes(){
  return superblock.totalInodes;
}

int getTotalBlocks(){
  return superblock.totalBlocks;
}

int getReservedBlocks(){
  return superblock.reservedBlocks;
}

int getFreeBlocks(){
  return superblock.freeBlocks;
}

int getFreeInodes(){
  return superblock.freeInodes;
}

int getFirstUsefulBlock(){
  return superblock.firstUsefulBlock;
}

int getBlockSize(){
  return superblock.blockSize;
}

int getBlocksPerGroup(){
  return superblock.blocksPerGroup;
}

int getInodesPerGroup(){
  return superblock.inodesPerGroup;
}

int getMagicSignature(){
  return superblock.magicSignature;
}

int getSizeOfInodeStructure(){
  return superblock.inodeStructure;
}

int getBlockGroup(){
  return superblock.group;
}

int getBlocksToPreallocate(){
  return superblock.preallocate;
}

void printSuperblock(){
  printf("Total Inodes:           %d\n", getTotalInodes());
  printf("Total Blocks:           %d\n", getTotalBlocks());
  printf("Reserved Blocks:        %d\n", getReservedBlocks());
  printf("Free blocks:            %d\n", getFreeBlocks());
  printf("Free inodes:            %d\n", getFreeInodes());
  printf("First useful block:     %d\n", getFirstUsefulBlock());
  printf("Block size:             %d\n", getBlockSize());
  printf("Blocks per group:       %d\n", getBlocksPerGroup());
  printf("Inodes per group:       %d\n", getInodesPerGroup());
  printf("Magic Signature:        %02x\n", getMagicSignature());
  printf("Size of inode structure:%d\n", getSizeOfInodeStructure());
  printf("Block group number:     %d\n", getBlockGroup());
  printf("Blocks to preallocate:  %d\n", getBlocksToPreallocate());
}
