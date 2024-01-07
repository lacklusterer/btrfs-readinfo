#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/btrfs.h>

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
    }

    struct btrfs_ioctl_fs_info_args fi_args;

    printf("Btrfs UUID: %llu\n", fi_args.fsid);
    printf("Btrfs max id: %llu\n", fi_args.max_id);
    printf("Btrfs node size: %llu\n", fi_args.nodesize);
    printf("Btrfs sector size: %llu\n", fi_args.sectorsize);

    close(fd);
    return 0;
}

