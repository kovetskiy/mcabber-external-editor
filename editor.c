/*
 * Module "Editor"
 *
 * Copyright 2015 Egor Kovetskiy
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

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
    .version         = "2.1",
    .description     = "Say messages via external editor",
    .requires        = NULL,
    .init            = editor_init,
    .uninit          = editor_uninit,
    .next            = NULL,
};

gchar* get_editor() {
    gchar *editor = (gchar *)settings_opt_get("external_editor");
    if (!editor) {
        editor = (gchar *)g_getenv("EDITOR");
    }
}

gint get_tmp_file(gchar **file_path, GError **err) {
    return g_file_open_tmp("mcabber.editor.XXXXXXX", file_path, err);
}

static void do_esay(char *arg) {
    GError *err = NULL;

    gchar *editor = get_editor();
    if (!editor) {
        scr_LogPrint(LPRINT_NORMAL, "Could not find editor");
        return;
    }

    gchar *file_path = NULL;
    gint file_tmp = get_tmp_file(&file_path, &err);
    if (file_tmp == -1) {
        scr_LogPrint(LPRINT_NORMAL, err->message);
        return;
    }
    close(file_tmp);

    gchar *spawn_argv[] = {
        editor,
        file_path
    };

    gboolean *edit = g_spawn_sync(NULL, spawn_argv, NULL,
        G_SPAWN_CHILD_INHERITS_STDIN, NULL, NULL, NULL, NULL,
        NULL, &err);
    if (!edit) {
        scr_LogPrint(LPRINT_NORMAL, err->message);
        return;
    }

    GMappedFile *file = g_mapped_file_new(file_path, FALSE, &err);
    if (file == NULL) {
        scr_LogPrint(LPRINT_NORMAL, err->message);
        return;
    }

    gint file_size = g_mapped_file_get_length(file);

    gint message_len = file_size + 1;
    gchar *message = g_new0(gchar, message_len);

    g_memmove(message, g_mapped_file_get_contents(file), file_size);
    message[message_len - 1] = '\0';

    do_say(message);
    do_screen_refresh();
}

 void do_say(char *arg) {
    cmd *saycmd = cmd_get("say");
    saycmd->func(arg);
}

 void do_screen_refresh() {
    cmd *refresh = cmd_get("screen_refresh");
    refresh->func("");
}

static void editor_init(void)
{
    cmd_add("esay",
        "Say something to the selected buddy using external edtor",
        0, 0, do_esay, NULL);
}

static void editor_uninit(void)
{
    cmd_del("esay");
}
