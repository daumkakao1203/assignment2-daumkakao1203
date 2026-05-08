#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    openlog(NULL, 0, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments: %d. Expected 2.", argc - 1);
        syslog(LOG_ERR, "Usage: %s <file_path> <text_string>", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error opening file %s: %s", writefile, strerror(errno));
        closelog();
        return 1;
    }

    if (fprintf(file, "%s", writestr) < 0) {
        syslog(LOG_ERR, "Error writing to file %s: %s", writefile, strerror(errno));
        fclose(file);
        closelog();
        return 1;
    }

    fclose(file);
    closelog();
    return 0;
}
