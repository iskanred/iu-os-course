#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

#define DIRECTORY_BUFFER 20
typedef struct dirent dirent;

int main() {
        DIR* pDir;
        dirent *pDirents[DIRECTORY_BUFFER];

        // try to open directory
        pDir = opendir("tmp/");

        if (pDir == NULL) { // cannot open directory
                printf("cannot open tmp/\n");
                return EXIT_SUCCESS;
        }
        // After here means directory was opened successfuly

        int pDirentsSize = 0;
        while(1) { // save dirents to array
                pDirents[pDirentsSize] = readdir(pDir);
		// no dirents to read
		if (pDirents[pDirentsSize] == NULL)
			break;
		++pDirentsSize;
	 }

        // close directory
        closedir(pDir);

        printf("File\t--\tHard Links\n");

        // Search for coincide links
        for (int i = 0; i < pDirentsSize; ++i) {
                int numOfLinksToINode = 0; // count number of links to current i-node

                for (int j = 0; j < pDirentsSize; ++j) {
                        if (pDirents[i]->d_ino == pDirents[j]->d_ino) {
                                ++numOfLinksToINode;
                        }
                }

                // if number of links to current i-node >= 2 then print file and links names
                if (numOfLinksToINode >= 2) {
                        printf("%s\t--\t", pDirents[i]->d_name);

                        for (int j = 0; j < pDirentsSize; ++j) {
                                if (pDirents[i]->d_ino == pDirents[j]->d_ino) {
                                       printf("%s ", pDirents[j]->d_name);
                                }
                        }
					printf("\n");
                }
        }
		
        return EXIT_SUCCESS;
}
