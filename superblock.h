#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>

#include"cmntdfs.h"

#define SUPERBLOCK_SIZE 512
#define SUPERBLOCK_OFFSET 1024

struct superblockValues{
  UINT4 totalInodes;
  UINT4 totalBlocks;
  UINT4 reservedBlocks;
  UINT4 freeBlocks;
  UINT4 freeInodes;
  UINT2 firstUsefulBlock;
  UINT4 blockSize;
  UINT4 blocksPerGroup;
  UINT4 inodesPerGroup;
  UINT4 magicSignature;
  UINT4 inodeStructure;
  UINT4 group;
  UINT4 preallocate;
};

struct superblockValues gSuperblock;

INT1 superblockInit(FILE*);
UINT4* superblockGetSuperblockValues(FILE*, UINT4*);
INT1 superblockSetSuperblockValues(UINT4*);
UINT4 superblockGetTotalInodes();
UINT4 superblockGetTotalBlocks();
UINT4 superblockGetReservedBlocks();
UINT4 superblockGetFreeBlocks();
UINT4 superblockGetFreeInodes();
UINT2 superblockGetFirstUsefulBlock();
UINT4 superblockGetBlockSize();
UINT4 superblockGetBlocksPerGroup();
UINT4 superblockGetInodesPerGroup();
UINT4 superblockGetMagicSignature();
UINT4 superblockGetSizeOfInodeStructure();
UINT4 superblockGetBlockGroup();
UINT4 superblockGetBlocksToPreallocate();
INT1 superblockPrintSuperblock();
