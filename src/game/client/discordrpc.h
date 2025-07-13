//========= Copyright Generalisk, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef DISCORDRPC_H
#define DISCORDRPC_H
#ifdef _WIN32
#pragma once
#endif



#include "discord_rpc.h"
#include <time.h>



// TODO: Find out A way for VPC to allow string preprocessors so I don't have to do shit like this again...
#if defined( TF_CLIENT_DLL )
#define DISCORD_APPID	"1393214771741851758" // Team Fortress 2 AppID
#elif defined( HL2MP )
#define DISCORD_APPID	"1393214722727215115" // Half-Life 2 Deathmatch AppID
#elif defined( HL2_CLIENT_DLL )
#define DISCORD_APPID	"1393214662392152094" // Half-Life 2 AppID
#else
#define DISCORD_APPID	"1393214575846887477" // Base SDK AppID
#endif



static ConVar cl_discord_appid("cl_discord_appid", DISCORD_APPID, FCVAR_DEVELOPMENTONLY | FCVAR_CHEAT);
static int64_t startTimestamp = time(0);



static class DiscordRPC
{
public:
	void Init();
	void Shutdown();

	void SetStatus( DiscordRichPresence discordPresence );
	void SetStatus_Map( const char* pMapName );
	void SetStatus_Menu();
};



#endif // CDLL_DISCORDRPC_H
