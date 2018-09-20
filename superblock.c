#include"superblock.h"

INT1 superblockInit(FILE* pFp){
  UINT4 *aVals;

  if(pFp == NULL)
  {
    //if the file is unreachable/doesnt exist
    printf("Error: could not open partition\n");
    //the program errors out and exits
    return -1;
  }

  //allocates memory to the integer array to store the superblock
  aVals = malloc(sizeof(UINT4)*SUPERBLOCK_SIZE);
  //stores the superblock into individual integer values
  superblockGetSuperblockValues(pFp, aVals);

  //each value requested in the superblock is found in its predefined location
  //as per ext4 superblock format
  superblockSetSuperblockValues(aVals);

  //prints out desired values at their assumed locations within the superblock
  superblockPrintSuperblock(gSuperblock);

  return 0;
}

UINT4* superblockGetSuperblockValues(FILE* pFp, UINT4* aVals){
  //seeks the location of the primary superblock
  fseek(pFp, SUPERBLOCK_OFFSET, SEEK_SET);
  //reads the whole block
  fread(aVals, SUPERBLOCK_SIZE, 1, pFp);
  //close file pointer
  fclose(pFp);
}

INT1 superblockSetSuperblockValues(UINT4 *aVals){
 gSuperblock.totalInodes = aVals[0];
 gSuperblock.totalBlocks = aVals[1];
 gSuperblock.reservedBlocks = aVals[2];
 gSuperblock.freeBlocks = aVals[3];
 gSuperblock.freeInodes = aVals[4];
 gSuperblock.firstUsefulBlock = aVals[5];
 gSuperblock.blockSize = pow(2, 10 + aVals[6]);
 gSuperblock.blocksPerGroup = aVals[9];
 gSuperblock.inodesPerGroup = aVals[10];
 gSuperblock.magicSignature = aVals[14];
 gSuperblock.inodeStructure = aVals[22];
 gSuperblock.group = aVals[17];
 gSuperblock.preallocate = aVals[18];

 return 1;
}

UINT4 superblockGetTotalInodes(){
  return gSuperblock.totalInodes;
}

UINT4 superblockGetTotalBlocks(){
  return gSuperblock.totalBlocks;
}

UINT4 superblockGetReservedBlocks(){
  return gSuperblock.reservedBlocks;
}

UINT4 superblockGetFreeBlocks(){
  return gSuperblock.freeBlocks;
}

UINT4 superblockGetFreeInodes(){
  return gSuperblock.freeInodes;
}

UINT2 superblockGetFirstUsefulBlock(){
  return gSuperblock.firstUsefulBlock;
}

UINT4 superblockGetBlockSize(){
  return gSuperblock.blockSize;
}

UINT4 superblockGetBlocksPerGroup(){
  return gSuperblock.blocksPerGroup;
}

UINT4 superblockGetInodesPerGroup(){
  return gSuperblock.inodesPerGroup;
}

UINT4 superblockGetMagicSignature(){
  return gSuperblock.magicSignature;
}

UINT4 superblockGetSizeOfInodeStructure(){
  return gSuperblock.inodeStructure;
}

UINT4 superblockGetBlockGroup(){
  return gSuperblock.group;
}

UINT4 superblockGetBlocksToPreallocate(){
  return gSuperblock.preallocate;
}

INT1 superblockPrintSuperblock(){
  printf("Total Inodes:           %d\n", superblockGetTotalInodes());
  printf("Total Blocks:           %d\n", superblockGetTotalBlocks());
  printf("Reserved Blocks:        %d\n", superblockGetReservedBlocks());
  printf("Free blocks:            %d\n", superblockGetFreeBlocks());
  printf("Free inodes:            %d\n", superblockGetFreeInodes());
  printf("First useful block:     %d\n", superblockGetFirstUsefulBlock());
  printf("Block size:             %d\n", superblockGetBlockSize());
  printf("Blocks per group:       %d\n", superblockGetBlocksPerGroup());
  printf("Inodes per group:       %d\n", superblockGetInodesPerGroup());
  printf("Magic Signature:        %02x\n", superblockGetMagicSignature());
  printf("Size of inode structure:%d\n", superblockGetSizeOfInodeStructure());
  printf("Block group number:     %d\n", superblockGetBlockGroup());
  printf("Blocks to preallocate:  %d\n", superblockGetBlocksToPreallocate());

  return 1;
}
