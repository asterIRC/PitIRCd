/*
 * Originally account extban by jilles
 * Now used for WEBIRCNAME by janicez
 */

#include "stdinc.h"
#include "modules.h"
#include "client.h"
#include "ircd.h"

static int _modinit(void);
static void _moddeinit(void);
static int eb_webirc(const char *data, struct Client *client_p, struct Channel *chptr, long mode_type);

DECLARE_MODULE_AV1(extb_webirc, _modinit, _moddeinit, NULL, NULL, NULL, "$Revision: 1299 $");

static int
_modinit(void)
{
	extban_table['w'] = eb_webirc;

	return 0;
}

static void
_moddeinit(void)
{
	extban_table['w'] = NULL;
}

static int eb_webirc(const char *data, struct Client *client_p,
		struct Channel *chptr, long mode_type)
{

	(void)chptr;
	struct Metadata *metadatum = user_metadata_find(client_p, "WEBIRCNAME");
	if (metadatum == NULL) return EXTBAN_NOMATCH;
	if (data == NULL) return EXTBAN_MATCH;
	if (!irccmp(metadatum->value, data)) return EXTBAN_MATCH;
	return EXTBAN_NOMATCH;
}
