/*******************************************************************************
 * Copyright (c) 2012, Jean-David Gadina <macmade@eosgarden.com>
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/* $Id$ */

/*!
 * @header          ...
 * @author          Jean-David Gadina <macmade@eosgarden>
 * @copyright       (c) 2012, eosgarden
 * @abstract        ...
 */

#import <Foundation/Foundation.h>
#import "EOSFTPServerDelegate.h"

FOUNDATION_EXPORT NSString * const EOSFTPServerException;

typedef NSUInteger       EOSFTPServerReplyCode;
typedef NSString * const EOSFTPServerCommand;

/*
 * RFC 959 commands
 */
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandUSER;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandPASS;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandACT;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandCWD;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandCDUP;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandSMNT;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandREIN;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandQUIT;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandPORT;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandPASV;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandTYPE;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandSTRU;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandMODE;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandRETR;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandSTOR;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandSTOU;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandAPPE;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandALLO;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandREST;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandRNFR;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandRNTO;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandABOR;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandDELE;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandRMD;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandMKD;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandPWD;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandLIST;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandNLST;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandSITE;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandSYST;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandSTAT;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandHELP;
FOUNDATION_EXPORT EOSFTPServerCommand EOSFTPServerCommandNOOP;

@class EOSFTPServerUser;
@class EOSFTPServerConnection;
@class AsyncSocket;

@interface EOSFTPServer: NSObject
{
@protected
    
    NSUInteger                  _port;
    NSUInteger                  _maxConnections;
    BOOL                        _running;
    NSDate                    * _startDate;
    NSString                  * _name;
    NSString                  * _versionString;
    NSString                  * _welcomeMessage;
    NSString                  * _quitMessage;
    NSMutableArray            * _users;
    BOOL                        _chroot;
    NSString                  * _rootDirectory;
    BOOL                        _allowAnonymousUsers;
    NSMutableArray            * _connections;
    NSMutableArray            * _connectedSockets;
    AsyncSocket               * _listenSocket;
    NSNetService              * _netService;
    NSStringEncoding            _encoding;
    id < EOSFTPServerDelegate > _delegate;
    
@private
    
    id _EOSFTPServer_Reserved[ 5 ] __attribute__( ( unused ) );
}

@property( atomic, readonly          ) NSUInteger                   port;
@property( atomic, readwrite, assign ) NSUInteger                   maxConnections;
@property( atomic, readonly          ) BOOL                         running;
@property( atomic, readwrite, copy   ) NSDate                     * startDate;
@property( atomic, readwrite, copy   ) NSString                   * name;
@property( atomic, readwrite, copy   ) NSString                   * versionString;
@property( atomic, readwrite, copy   ) NSString                   * welcomeMessage;
@property( atomic, readwrite, copy   ) NSString                   * quitMessage;
@property( atomic, readonly          ) NSArray                    * connectedUsers;
@property( atomic, readwrite, assign ) BOOL                         chroot;
@property( atomic, readwrite, copy   ) NSString                   * rootDirectory;
@property( atomic, readwrite, assign ) BOOL                         allowAnonymousUsers;
@property( atomic, readonly          ) NSStringEncoding             encoding;
@property( atomic, readwrite, assign ) id < EOSFTPServerDelegate >  delegate;

- ( id )initWithPort: ( NSUInteger )port;
- ( BOOL )start;
- ( BOOL )stop;
- ( BOOL )restart;
- ( void )addUser: ( EOSFTPServerUser * )user;
- ( BOOL )userIsConnected: ( EOSFTPServerUser * )user;
- ( BOOL )userCanLogin: ( NSString * )username;
- ( BOOL )authenticateUser: ( EOSFTPServerUser * )user;
- ( NSString * )helpForCommand: ( NSString * )command;
- ( NSString * )messageForReplyCode: ( EOSFTPServerReplyCode )code;
- ( void )processCommand: ( NSString * )command connection: ( EOSFTPServerConnection * )connection;

@end
