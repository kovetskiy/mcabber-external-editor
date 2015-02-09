/*
 * Module "Editor"
 *
 * Copyright 2015 Egor Kovetskiy
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <mcabber/logprint.h>
#include <mcabber/commands.h>
#include <mcabber/screen.h>
#include <mcabber/settings.h>
#include <mcabber/modules.h>
#include <mcabber/config.h>

static void editor_init   (void);
static void editor_uninit (void);

module_info_t info_editor = {
    .branch          = MCABBER_BRANCH,
    .api             = MCABBER_API_VERSION,
    .version         = "2.2",
    .description     = "Say messages using external editor",
    .requires        = NULL,
    .init            = editor_init,
    .uninit          = editor_uninit,
    .next            = NULL,
};

char* get_editor() {
    char *editor = settings_opt_get("editor");

    if (editor) {
        return editor;
    } else {
        return getenv("EDITOR");
    }
}

static void do_esay(char *arg) {
    char *editor = get_editor();
    if (!editor) {
        scr_LogPrint(LPRINT_NORMAL, "Could not find editor");
        return;
    }

    char temp_file_path[] = "/tmp/mcabber-XXXXXX";
    int temp_file_fd = mkstemp(temp_file_path);
    if (!temp_file_fd) {
        scr_LogPrint(LPRINT_NORMAL, strerror(errno));
        return;
    }

    pid_t child = fork();
    if (child == 0) {
        execlp(editor, editor, temp_file_path, NULL);
        scr_LogPrint(LPRINT_NORMAL, strerror(errno));
        return;
    } else {
        waitpid(child, NULL, 0);
    }

    struct stat temp_file_stat;
    fstat(temp_file_fd, &temp_file_stat);

    if (temp_file_stat.st_size == 0) {
        scr_LogPrint(LPRINT_NORMAL, "Empty message file, no message sent.");
        cmd_get("screen_refresh")->func("");
        return;
    }

    char *message = mmap(
        0, temp_file_stat.st_size, PROT_READ, MAP_PRIVATE, temp_file_fd, 0);

    cmd_get("say")->func(message);
    cmd_get("screen_refresh")->func("");
    munmap(message, temp_file_stat.st_size);
    unlink(temp_file_path);
}

static void editor_init(void) {
    cmd_add("esay",
        "Say something to the selected buddy using external edtor",
        0, 0, do_esay, NULL);
}

static void editor_uninit(void) {
    cmd_del("esay");
}
