// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
//
// libwebsocket client wrapper. Slightly modified version from the HTML5Networking plugin
//
#pragma  once
#include "ROSBridgePrivate.h"
#include "Core.h"
#if !PLATFORM_HTML5
#include "Runtime/Sockets/Private/BSDSockets/SocketSubsystemBSD.h"
#define USE_LIBWEBSOCKET 1
#else
#include <netinet/in.h>
#define USE_LIBWEBSOCKET 0
#endif

class FROSWebSocket
{

public:

	// Initialize as client side socket.
	FROSWebSocket(const FInternetAddr& ServerAddress);

#if USE_LIBWEBSOCKET
	// Initialize as server side socket.
	FROSWebSocket(WebSocketInternalContext* InContext, WebSocketInternal* Wsi);
#endif

	// clean up.
	~FROSWebSocket();

	void Connect();

	void Destroy();

	/************************************************************************/
	/* Set various callbacks for Socket Events								*/
	/************************************************************************/
	void SetConnectedCallBack(FROSWebsocketInfoSignature CallBack);
	void SetErrorCallBack(FROSWebsocketInfoSignature CallBack);
	void SetRecieveCallBack(FROSWebsocketPacketRecievedSignature CallBack);

	/** Send raw data to remote end point. */
	bool Send(uint8* Data, uint32 Size);  // Send Binary
	bool SendText(uint8* Data, uint32 Size); // Send Text
	bool Send(const FString& StringData);

	/** service libwebsocket.			   */
	void Tick();
	/** service libwebsocket until outgoing buffer is empty */
	void Flush();

	/** Helper functions to describe end points. */
	FString RemoteEndPoint(bool bAppendPort);
	FString LocalEndPoint(bool bAppendPort);
	struct sockaddr_in* GetRemoteAddr();

// this was made public because of cross-platform build issues
public:

	void HandlePacket();
	void OnRawRecieve(void* Data, uint32 Size, bool isBinary = true);
	void OnRawWebSocketWritable(WebSocketInternal* wsi);

	/************************************************************************/
	/*	Various Socket callbacks											*/
	/************************************************************************/
	FROSWebsocketPacketRecievedSignature  OnRecieved;
	FROSWebsocketInfoSignature OnConnection;
	FROSWebsocketInfoSignature OnError;

	/**  Recv and Send Buffers, serviced during the Tick */
	TArray<uint8> RecievedBuffer;
	TArray<TArray<uint8>> OutgoingBuffer;
	TArray<uint8> OutgoingBufferType;

	/** Critical Section */
	FCriticalSection CriticalSection;

#if USE_LIBWEBSOCKET
	/** libwebsocket internal context*/
	WebSocketInternalContext* Context;

	/** libwebsocket web socket */
	WebSocketInternal* Wsi;

	/** libwebsocket Protocols that can be serviced by this implemenation*/
	WebSocketInternalProtocol* Protocols;
#else // ! USE_LIBWEBSOCKET -- HTML5 uses BSD network API
	int SockFd;
#endif

	// Server address as string without port
	FString ServerAddressAsString;

	// Server port nr
	int32 PortNr;

	struct sockaddr_in RemoteAddr;

	/** Server side socket or client side*/
	bool IsServerSide;

	/** Is the client destroyed? */ 
	bool IsDestroyed; 

	friend class FWebSocketServer;
};
