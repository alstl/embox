/**
 * @file
 * @brief
 *
 * @author  Anton Kozlov
 * @date    04.10.2012
 */

#include <fcntl.h>
#include <kernel/task/idx.h>
#include <util/array.h>
#include <fs/posix.h>
#include <fs/core.h>

int open(const char *path, int __oflag, ...) {
	char mode[] = "-";
	struct file_desc *kfile;

	if ((O_RDWR == __oflag) || (O_WRONLY == __oflag)) {
		mode[0] = 'w';
	}
	else {
		mode[0] = 'r';
	}

	kfile = kopen(path, (const char *)&mode[0]);

	if (NULL == kfile) {
		return -1;
	}

	return task_self_idx_alloc(&task_idx_ops_file, kfile);
}

