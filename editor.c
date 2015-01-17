/*
 * Module "External Editor" -- Say messages via external editor.
 *
 * Copyright 2015 Egor Kovetskiy
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#include <mcabber/logprint.h>
#include <mcabber/commands.h>
#include <mcabber/compl.h>
#include <mcabber/hooks.h>
#include <mcabber/screen.h>
#include <mcabber/settings.h>
#include <mcabber/modules.h>
#include <mcabber/config.h>

static void editor_init   (void);
static void editor_uninit (void);

module_info_t info_editor = {
        .branch          = MCABBER_BRANCH,
        .api             = MCABBER_API_VERSION,
        .version         = MCABBER_VERSION,
        .description     = "Say messages via external editor",
        .requires        = NULL,
        .init            = editor_init,
        .uninit          = editor_uninit,
        .next            = NULL,
};

static void do_esay(char *arg) {
 // TODO: check errors through GError
 gchar *editor = (gchar *)g_getenv("EDITOR");

 gchar *file_path = NULL;
 gint file_tmp = g_file_open_tmp("mcabber.esay.XXXXXXX", &(file_path), NULL);
 close(file_tmp);

 gchar *spawn_argv[] = { editor, file_path };

 // TODO: check exit status
 g_spawn_sync(NULL, spawn_argv, NULL, G_SPAWN_CHILD_INHERITS_STDIN,
 NULL, NULL, NULL, NULL, NULL, NULL);

 GMappedFile *file = g_mapped_file_new(file_path, FALSE, NULL);
 gint file_size = g_mapped_file_get_length(file);

 // +1 for '\0'
 gint message_len = file_size + 1;
 gchar *message = g_new0(gchar, message_len);

 g_memmove(message, g_mapped_file_get_contents(file), file_size);
 message[message_len - 1] = '\0';

 cmd *saycmd = cmd_get("say");
 saycmd->func(message);

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

/* vim: set et cindent cinoptions=>2\:2(0 ts=2 sw=2:  For Vim users... */
