#include"superblock.h"

INT1 main(UINT1 argc, CHAR** argv){
  FILE* pFp;

  if(argc != 2)
  {
    printf("Error: No partition specified\n");
    return -1;
  }

  //opens user specified partition
  pFp = fopen(argv[1], "rb");

  if(pFp < 0)
  {
    printf("Error: Cannot open specified location\n");
    return -1;
  }

  superblockInit(pFp);
  fclose(pFp);

  return 0;
}
