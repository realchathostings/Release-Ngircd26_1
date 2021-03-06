/*
 * ngIRCd -- The Next Generation IRC Daemon
 * Copyright (c)2001,2002 by Alexander Barton (alex@barton.de)
 *
 * Dieses Programm ist freie Software. Sie koennen es unter den Bedingungen
 * der GNU General Public License (GPL), wie von der Free Software Foundation
 * herausgegeben, weitergeben und/oder modifizieren, entweder unter Version 2
 * der Lizenz oder (wenn Sie es wuenschen) jeder spaeteren Version.
 * Naehere Informationen entnehmen Sie bitter der Datei COPYING. Eine Liste
 * der an ngIRCd beteiligten Autoren finden Sie in der Datei AUTHORS.
 *
 * $Id: client.h,v 1.27 2002/03/25 19:11:01 alex Exp $
 *
 * client.h: Konfiguration des ngircd (Header)
 */


#ifndef __client_h__
#define __client_h__

#include "conn.h"


typedef enum
{
	CLIENT_UNKNOWN,			/* Verbindung mit (noch) unbekanntem Typ */
	CLIENT_GOTPASS,			/* Client hat PASS gesendet */
	CLIENT_GOTNICK,			/* Client hat NICK gesendet */
	CLIENT_GOTUSER,			/* Client hat USER gesendet */
	CLIENT_USER,			/* Client ist ein Benutzer (USER wurde gesendet) */
	CLIENT_UNKNOWNSERVER,		/* unregistrierte Server-Verbindung */
	CLIENT_GOTPASSSERVER,		/* Client hat PASS nach "Server-Art" gesendet */
	CLIENT_SERVER,			/* Client ist ein Server */
	CLIENT_SERVICE			/* Client ist ein Service */
} CLIENT_TYPE;


#if defined(__client_c__) | defined(S_SPLINT_S)

#include "defines.h"

typedef struct _CLIENT
{
	CHAR id[CLIENT_ID_LEN];		/* Nick (User) bzw. ID (Server) */
	UINT32 hash;			/* Hash ueber die (kleingeschriebene) ID */
	POINTER *next;			/* Zeiger auf naechste Client-Struktur */
	CLIENT_TYPE type;		/* Typ des Client, vgl. CLIENT_TYPE */
	CONN_ID conn_id;		/* ID der Connection (wenn lokal) bzw. NONE (remote) */
	struct _CLIENT *introducer;	/* ID des Servers, der die Verbindung hat */
	struct _CLIENT *topserver;	/* Toplevel-Servers (nur gueltig, wenn Client ein Server ist) */
	CHAR pwd[CLIENT_PASS_LEN];	/* Passwort, welches der Client angegeben hat */
	CHAR host[CLIENT_HOST_LEN];	/* Hostname des Client */
	CHAR user[CLIENT_USER_LEN];	/* Benutzername ("Login") */
	CHAR info[CLIENT_INFO_LEN];	/* Langer Benutzername (User) bzw. Infotext (Server) */
	CHAR modes[CLIENT_MODE_LEN];	/* Client Modes */
	INT hops, token, mytoken;	/* "Hops" und "Token" (-> SERVER-Befehl) */
	BOOLEAN oper_by_me;		/* IRC-Operator-Status durch diesen Server? */
	CHAR away[CLIENT_AWAY_LEN];	/* AWAY-Text, wenn Mode 'a' gesetzt */
} CLIENT;

#else

typedef POINTER CLIENT;

#endif


GLOBAL VOID Client_Init( VOID );
GLOBAL VOID Client_Exit( VOID );

GLOBAL CLIENT *Client_NewLocal( CONN_ID Idx, CHAR *Hostname, INT Type, BOOLEAN Idented );
GLOBAL CLIENT *Client_NewRemoteServer( CLIENT *Introducer, CHAR *Hostname, CLIENT *TopServer, INT Hops, INT Token, CHAR *Info, BOOLEAN Idented );
GLOBAL CLIENT *Client_NewRemoteUser( CLIENT *Introducer, CHAR *Nick, INT Hops, CHAR *User, CHAR *Hostname, INT Token, CHAR *Modes, CHAR *Info, BOOLEAN Idented );
GLOBAL CLIENT *Client_New( CONN_ID Idx, CLIENT *Introducer, CLIENT *TopServer, INT Type, CHAR *ID, CHAR *User, CHAR *Hostname, CHAR *Info, INT Hops, INT Token, CHAR *Modes, BOOLEAN Idented );

GLOBAL VOID Client_Destroy( CLIENT *Client, CHAR *LogMsg, CHAR *FwdMsg, BOOLEAN SendQuit );

GLOBAL CLIENT *Client_ThisServer( VOID );

GLOBAL CLIENT *Client_GetFromConn( CONN_ID Idx );
GLOBAL CLIENT *Client_GetFromToken( CLIENT *Client, INT Token );

GLOBAL CLIENT *Client_Search( CHAR *ID );
GLOBAL CLIENT *Client_First( VOID );
GLOBAL CLIENT *Client_Next( CLIENT *c );

GLOBAL INT Client_Type( CLIENT *Client );
GLOBAL CONN_ID Client_Conn( CLIENT *Client );
GLOBAL CHAR *Client_ID( CLIENT *Client );
GLOBAL CHAR *Client_Mask( CLIENT *Client );
GLOBAL CHAR *Client_Info( CLIENT *Client );
GLOBAL CHAR *Client_User( CLIENT *Client );
GLOBAL CHAR *Client_Hostname( CLIENT *Client );
GLOBAL CHAR *Client_Password( CLIENT *Client );
GLOBAL CHAR *Client_Modes( CLIENT *Client );
GLOBAL CLIENT *Client_Introducer( CLIENT *Client );
GLOBAL BOOLEAN Client_OperByMe( CLIENT *Client );
GLOBAL INT Client_Hops( CLIENT *Client );
GLOBAL INT Client_Token( CLIENT *Client );
GLOBAL INT Client_MyToken( CLIENT *Client );
GLOBAL CLIENT *Client_TopServer( CLIENT *Client );
GLOBAL CLIENT *Client_NextHop( CLIENT *Client );
GLOBAL CHAR *Client_Away( CLIENT *Client );

GLOBAL BOOLEAN Client_HasMode( CLIENT *Client, CHAR Mode );

GLOBAL VOID Client_SetHostname( CLIENT *Client, CHAR *Hostname );
GLOBAL VOID Client_SetID( CLIENT *Client, CHAR *Nick );
GLOBAL VOID Client_SetUser( CLIENT *Client, CHAR *User, BOOLEAN Idented );
GLOBAL VOID Client_SetInfo( CLIENT *Client, CHAR *Info );
GLOBAL VOID Client_SetPassword( CLIENT *Client, CHAR *Pwd );
GLOBAL VOID Client_SetType( CLIENT *Client, INT Type );
GLOBAL VOID Client_SetHops( CLIENT *Client, INT Hops );
GLOBAL VOID Client_SetToken( CLIENT *Client, INT Token );
GLOBAL VOID Client_SetOperByMe( CLIENT *Client, BOOLEAN OperByMe );
GLOBAL VOID Client_SetModes( CLIENT *Client, CHAR *Modes );
GLOBAL VOID Client_SetIntroducer( CLIENT *Client, CLIENT *Introducer );
GLOBAL VOID Client_SetAway( CLIENT *Client, CHAR *Txt );

GLOBAL BOOLEAN Client_ModeAdd( CLIENT *Client, CHAR Mode );
GLOBAL BOOLEAN Client_ModeDel( CLIENT *Client, CHAR Mode );

GLOBAL BOOLEAN Client_CheckNick( CLIENT *Client, CHAR *Nick );
GLOBAL BOOLEAN Client_CheckID( CLIENT *Client, CHAR *ID );

GLOBAL INT Client_UserCount( VOID );
GLOBAL INT Client_ServiceCount( VOID );
GLOBAL INT Client_ServerCount( VOID );
GLOBAL INT Client_OperCount( VOID );
GLOBAL INT Client_UnknownCount( VOID );
GLOBAL INT Client_MyUserCount( VOID );
GLOBAL INT Client_MyServiceCount( VOID );
GLOBAL INT Client_MyServerCount( VOID );

GLOBAL BOOLEAN Client_IsValidNick( CHAR *Nick );


#endif


/* -eof- */
