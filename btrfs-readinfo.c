#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/btrfs.h>

#define BTRFS_DEVICE "/dev/sda2"

int main() {
    int fd = open(BTRFS_DEVICE, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return 1;
    }

    struct btrfs_ioctl_fs_info_args fi_args;

    printf("Btrfs filesystem UUID: %llu\n", fi_args.fsid);
    printf("Btrfs filesystem mad id: %llu\n", fi_args.max_id);
    printf("Btrfs filesystem node size: %llu\n", fi_args.nodesize);
    printf("Btrfs filesystem sector size: %llu\n", fi_args.sectorsize);

    close(fd);
    return 0;
}

