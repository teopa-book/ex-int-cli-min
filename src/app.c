#include "argtable3.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    arg_lit_t *debug = arg_lit0("D", "debug", "enable debug mode");
    arg_lit_t *help = arg_lit0("h", "help", "print help info and quit");
    arg_lit_t *version = arg_lit0("v", "version", "print version info and quit");
    arg_int_t *level = arg_int0("l", "log-level", "<n>", "set logging level");
    arg_file_t *o = arg_file0("o", NULL, "<file>", "set output file");
    arg_file_t *file = arg_filen(NULL, NULL, "<file>", 1, 100, "input files");
    arg_end_t *end = arg_end(20);
    void *argtable[] = {
        help, version, level, debug, o, file, end,
    };

    int exitcode = 0;
    const char *progname = "climin";

    int nerrors = arg_parse(argc, argv, argtable);

    /* special case: '--help' takes precedence over version and error reporting */
    if (argc == 1 || help->count > 0) {
        printf("Usage: %s", progname);
        arg_print_syntax(stdout, argtable, "\n");
        printf("Demonstrate command-line parsing in argtable3.\n\n");
        arg_print_glossary(stdout, argtable, "  %-25s %s\n");
        exitcode = 0;
        goto exit;
    }

    /* special case: '--version' takes precedence over error reporting */
    if (version->count > 0) {
        printf("1.0.0\n");
        exitcode = 0;
        goto exit;
    }

    /* If the parser returned any errors then display them and exit */
    if (nerrors > 0) {
        /* Display the error details contained in the arg_end struct.*/
        arg_print_errors(stdout, end, progname);
        printf("Try '%s --help' for more information.\n", progname);
        exitcode = 1;
        goto exit;
    }

    if (file->count > 0) {
        printf("number of files: %d\n", file->count);
        for (int i = 0; i < file->count; i++) {
            if (strcmp(file->filename[i], "-") == 0) {
                printf("[%d] stdin/stdout\n", i);
            } else {
                printf("[%d] %s\n", i, file->filename[i]);
            }
        }
    }

exit:
    /* deallocate each non-null entry in argtable[] */
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
    return exitcode;
}
