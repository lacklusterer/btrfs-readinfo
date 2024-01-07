#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/btrfs.h>

uint64_t getInodeNumber() {
    uint64_t inode_number;
    printf("Enter the inode number: ");
    if (scanf("%llu", &inode_number) != 1) {
        perror("Error reading inode number");
        exit(EXIT_FAILURE);
    }
    return inode_number;
}

int main(int argc, char *argv[]) {
    char *BTRFS_DEVICE;

    if (argc != 2) {
        printf("Usage: %s <device_path>\n", argv[0]);
        return 1;
    }

    BTRFS_DEVICE = argv[1];
    printf("BTRFS device set to: %s\n", BTRFS_DEVICE);

    int fd = open(BTRFS_DEVICE, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return 1;
        exit(EXIT_FAILURE);
    }

    struct btrfs_ioctl_fs_info_args fi_args;
    struct btrfs_ioctl_ino_lookup_args il_args = { .objectid = getInodeNumber() };

    printf("Btrfs UUID: %llu\n", fi_args.fsid);
    printf("Btrfs max id: %llu\n", fi_args.max_id);
    printf("Btrfs node size: %llu\n", fi_args.nodesize);
    printf("Btrfs sector size: %llu\n", fi_args.sectorsize);

    printf("Inode number: %llu\n", il_args.treeid);
    printf("Objectid: %llu\n", il_args.objectid);
    printf("Name: %llu\n", il_args.name);

    close(fd);
    return 0;
}

