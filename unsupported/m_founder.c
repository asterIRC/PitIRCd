// PitIRCd: A versatile IRCd with auto-founderop-on-join to founder users.

#include "stdinc.h"

#include "send.h"
#include "channel.h"
#include "client.h"
#include "common.h"
#include "config.h"
#include "ircd.h"
#include "numeric.h"
#include "s_conf.h"
#include "s_newconf.h"
#include "s_serv.h"
#include "hash.h"
#include "msg.h"
#include "parse.h"
#include "modules.h"
#include "whowas.h"
#include "monitor.h"

static int mc_founder(struct Client *, struct Client *, int, const char **);

struct Message founder_msgtab = {
	"FOUNDER", 0, 0, 0, MFLG_SLOW,
	{mg_ignore, {mc_founder, 2}, mg_ignore, mg_ignore, mg_ignore, mg_ignore}
};

mapi_clist_av1 founder_clist[] = {
	&founder_msgtab, NULL
};

DECLARE_MODULE_AV1(founder, NULL, NULL, founder_clist, NULL, NULL, "$Revision$");


/*
** m_metadata - User set channel metadata
** I seriously fucking did this -- janicez
*/
static int
mc_founder(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	if(!check_channel_name(parv[2]))
	{
		sendto_one_numeric(source_p, ERR_BADCHANNAME, form_str(ERR_BADCHANNAME), parv[3]);
		return 0;
	}

	struct Channel *chptr;
	struct membership *msptr;
	if((chptr = find_channel(parv[2])) == NULL)
	{
		sendto_one_numeric(source_p, ERR_NOSUCHCHANNEL,
				   form_str(ERR_NOSUCHCHANNEL), parv[2]);
		return 0;
	}
	struct Metadata *md;
	if(!irccmp(parv[1], "SHOW")) {
		md = channel_metadata_find(chptr, "FOUNDER");
		if (md != NULL)
		{
			sendto_one(source_p, ":%s NOTICE %s :METADATA %s %s :%s", me.name, source_p->name, parv[2], md->name, md->value);
			return 0;
		} else {
			sendto_one(source_p, ":%s NOTICE %s :METADATA %s FOUNDER :Metadatum nonexistant", me.name, source_p->name, parv[2]);
			return 0;
		}
	}

	// Uhhh.... rizight. I don't think this is gonna work (mumble mumble) -- janicez
	if ((msptr = find_channel_membership(chptr, source_p)) == NULL)
	{
		sendto_one_numeric(source_p, ERR_NOTONCHANNEL,
				   form_str(ERR_NOTONCHANNEL), parv[2]);
		return 0;
	}

	// Yeah. No. --janicez
	if (!is_any_op(msptr) && !IsOverride(source_p))
	{
		sendto_one(source_p, form_str(ERR_CHANOPRIVSNEEDED),
				me.name, source_p->name, parv[2]);
		return 0;
	}

	md = channel_metadata_find(chptr, "FOUNDER");
	if (!is_founder(msptr) || (md == NULL && !is_owner(msptr)))
	{
		sendto_one(source_p, ":%s NOTICE %s :METADATA ERROR %s %s :FOUNDER modification prohibited -- you are not owner, or FOUNDER is already set and you are not founder.", me.name, source_p->name, parv[2], parv[3]);
		return 0;
	}

	// And here we are. If the user isn't querying, but adding or deleting, set, and if the channel is global (#) XXX NOT CHECKING THIS XXX, propagate.
	if(!irccmp(parv[1], "SET") && parv[3] != NULL)
		channel_metadata_add(chptr, "FOUNDER", parv[3], 1);
	if(!irccmp(parv[1], "DELETE"))
		channel_metadata_delete(chptr, "FOUNDER", 1);
	sendto_one(source_p, ":%s NOTICE %s :METADATA %s %s FOUNDER %s", me.name, source_p->name, parv[1], parv[2], parv[3]);
	return 0;
}
