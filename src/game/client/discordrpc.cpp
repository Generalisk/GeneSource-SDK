//========= Copyright Generalisk, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "discordrpc.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"



static void HandleDiscordReady(const DiscordUser* connectedUser)
{
	DevMsg("Discord: Connected to user %s#%s - %s\n",
		connectedUser->username,
		connectedUser->discriminator,
		connectedUser->userId);
}

static void HandleDiscordDisconnected(int errcode, const char* message)
{
	DevMsg("Discord: Disconnected (%d: %s)\n", errcode, message);
}

static void HandleDiscordError(int errcode, const char* message)
{
	DevMsg("Discord: Error (%d: %s)\n", errcode, message);
}

static void HandleDiscordJoin(const char* secret)
{
	// TODO: Impliment
}

static void HandleDiscordSpectate(const char* secret)
{
	// TODO: Impliment
}

static void HandleDiscordJoinRequest(const DiscordUser* request)
{
	// TODO: Impliment
}



void DiscordRPC::Init()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));

	handlers.ready = HandleDiscordReady;
	handlers.disconnected = HandleDiscordDisconnected;
	handlers.errored = HandleDiscordError;
	handlers.joinGame = HandleDiscordJoin;
	handlers.spectateGame = HandleDiscordSpectate;
	handlers.joinRequest = HandleDiscordJoinRequest;

	char appid[255];
	sprintf(appid, "%d", engine->GetAppID());
	Discord_Initialize(cl_discord_appid.GetString(), &handlers, 1, appid);

	if (!g_bTextMode)
	{
		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));

		discordPresence.state = "In-Game";
		discordPresence.details = "Main Menu";
		discordPresence.startTimestamp = startTimestamp;
		discordPresence.largeImageKey = "GameLogo";
		discordPresence.smallImageKey = "";
		Discord_UpdatePresence(&discordPresence);
	}
}

void DiscordRPC::Shutdown()
{
	Discord_Shutdown();
}

void DiscordRPC::LevelInit( const char* pMapName )
{
	if (!g_bTextMode)
	{
		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));

		char buffer[256];
		discordPresence.state = "In-Game";
		sprintf(buffer, "Map: %s", pMapName);
		discordPresence.details = buffer;
		discordPresence.largeImageKey = pMapName;
		discordPresence.smallImageKey = "GameLogo";
		Discord_UpdatePresence(&discordPresence);
	}
}

void DiscordRPC::LevelShutdown()
{
	if (!g_bTextMode)
	{
		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));

		discordPresence.state = "In-Game";
		discordPresence.details = "Main Menu";
		discordPresence.startTimestamp = startTimestamp;
		discordPresence.largeImageKey = "GameLogo";
		discordPresence.smallImageKey = "";
		Discord_UpdatePresence(&discordPresence);
	}
}
