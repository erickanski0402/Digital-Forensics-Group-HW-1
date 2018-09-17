#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct SuperblockInfo{
	long totalInodes;
	long sizeInBlocks;
	long reservedBlocks;
	long freeBlocks;
	long freeInodes;
	long firstUsefulBlock;
	long blockSize;
	long blocksPerGroup;
	long inodesPerGroup;
	char *magicSignature;
	long onDiskInode;
	long groupNumber;
	long preallocate;
} superblock;

void parseInfo(char*);

int main(int arc, char *argv[]){
	char command[50] = "sudo dumpe2fs -h ";
	strcat(command, argv[1]);
	// system(command);

	FILE *fp;
	char path[1035];
	fp = popen(command, "r");
	if(fp == NULL){
		printf("Failed to run command");
		exit(1);
	}

	while(fgets(path, sizeof(path) - 1, fp) != NULL){
		parseInfo(path);
	}

	pclose(fp);

	return 0;
}

void parseInfo(char path[1035]){
	char *ptr;
	char *str = (char *)malloc(1035);

	if(strstr(path, "Inode count:")){

		str = strncpy(str, path + 26, 1035);
		superblock.totalInodes = strtol(str, &ptr, 10);
		printf("Total inodes: %ld\n", superblock.totalInodes);

	}else if(strstr(path, "Block count:")){

		str = strncpy(str, path + 26, 1035);
		superblock.sizeInBlocks = strtol(str, &ptr, 10);
		printf("Total blocks in system: %ld\n", superblock.sizeInBlocks);

	}else if(strstr(path, "Reserved block count:")){

		str = strncpy(str, path + 26, 1035);
		superblock.reservedBlocks = strtol(str, &ptr, 10);
		printf("Number of reserved blocks: %ld\n", superblock.reservedBlocks);

	}else if(strstr(path, "Free blocks:")){

		str = strncpy(str, path + 26, 1035);
		superblock.freeBlocks = strtol(str, &ptr, 10);
		printf("Number of free blocks: %ld\n", superblock.freeBlocks);

	}else if(strstr(path, "Free inodes:")){

		str = strncpy(str, path + 26, 1035);
		superblock.freeInodes = strtol(str, &ptr, 10);
		printf("Number of free inodes: %ld\n", superblock.freeInodes);

	}else if(strstr(path, "First block:")){

		str = strncpy(str, path + 26, 1035);
		superblock.firstUsefulBlock = strtol(str, &ptr, 10);
		printf("First useful block: %ld\n", superblock.firstUsefulBlock);

	}else if(strstr(path, "Block size:")){

		str = strncpy(str, path + 26, 1035);
		superblock.blockSize = strtol(str, &ptr, 10);
		printf("System block size: %ld\n", superblock.blockSize);

	}else if(strstr(path, "Blocks per group:")){

		str = strncpy(str, path + 26, 1035);
		superblock.blocksPerGroup = strtol(str, &ptr, 10);
		printf("Number of blocks per group: %ld\n", superblock.blocksPerGroup);

	}else if(strstr(path, "Inodes per group:")){

		str = strncpy(str, path + 26, 1035);
		superblock.inodesPerGroup = strtol(str, &ptr, 10);
		printf("Number of inodes per group: %ld\n", superblock.inodesPerGroup);

	}else if(strstr(path, "Filesystem magic number:")){

		superblock.magicSignature = strncpy(str, path + 26, 1035);
		printf("System magic signature: %s", superblock.magicSignature);

	}
}
