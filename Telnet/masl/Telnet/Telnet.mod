//!This is an implementation of the Telnet protocol as defined in RFC 854. It is a
//!simple implementation that only implements the NVT and does not support any
//!additional options.
domain Telnet is
  
  public type termid is integer;   
  public type telnetcmd is enum ( SE, NOP, DM, BRK, IP, AO, AYT, EC, EL, GA, SB, WILL, WONT, DO, DONT, IAC );   
  public type error is enum ( OK, TERMINVAL, TERMBUSY, HOSTINVAL, PORTINVAL, SOCKETERR );   
  
  //!NAME
  //!    create_terminal -- create a new Telnet terminal instance.
  //!    
  //!SYNOPSIS
  //!    public service create_terminal( terminal: out termid,
  //!                                    error:    out error );
  //!    
  //!DESCRIPTION
  //!
  //!    The 'create_terminal' service is used to create a new Telnet terminal
  //!    instance with its own printer and keyboard.
  //!
  //!    'terminal' is set to the identifier of the created terminal instance or the
  //!    constant NULTERM if the operation results in an error. See the
  //!    'TerminalConstants' class.
  //!
  //!    'error' is an error code set by the attach operation or OK if successful.
  //! 
  //!RETURN VALUES
  //!    N/A
  //!    
  //!ERRORS
  //!    N/A
  private service create_terminal ( termid: out termid );   
  private service sendtext ( termid: in termid,
                             text: in integer );   
  //!NAME
  //!    command -- send a Telnet command on a specified terminal instance.
  //!    
  //!SYNOPSIS
  //!    public service command( terminal: in termid,
  //!                            cmd:      in telnetcmd );
  //!    
  //!DESCRIPTION
  //!
  //!    The 'command' service is used to queue Telnet commands to be sent on a
  //!    specified terminal instance.
  //!    
  //!    'terminal' is an identifier specifying the terminal instance which to
  //!    send the command from.
  //!    
  //!    'cmd' is a command code defined in the enumerated type telnetcmd. See the
  //!    datatype definition for descriptions of available commands.
  //! 
  //!RETURN VALUES
  //!    N/A
  //!    
  //!ERRORS
  //!    The call will fail and set the 'error' code if:
  //!    
  //!    [TERMINVAL]     'terminal' is a non-existent or invalid terminal. Also
  //!                    returned if the terminal is not attached to a peer.
  private service command ( termid: in termid,
                            cmd: in telnetcmd );   
  //!NAME
  //!    attach -- attach a Telnet terminal instance to another Telnet terminal.
  //!    
  //!SYNOPSIS
  //!    public service attach( terminal: in  termid,
  //!                           host:     in  string,
  //!                           port:     in  integer,
  //!                           error:    out error );
  //!    
  //!DESCRIPTION
  //!
  //!    The 'attach' service is used to attach a Telnet terminal instance to another
  //!    Telnet terminal specified by 'host' and 'port'.
  //!
  //!    'terminal' is an identifier specifying the terminal instance which to
  //!    execute the attach operation against.
  //!
  //!    'host' is a string representation of an IPv4 address in the form
  //!    "<byte>.<byte>.<byte>.<byte>" where <byte> is a string representing a
  //!    decimal integer from 0-255. "localhost" is also accepted as a value for
  //!    'host'. Any other string is invalid and will result in an error.
  //!    
  //!    'port' is an integer ranging from 0-65535 representing the port on which the
  //!    foreign Telnet terminal is listening.
  //!    
  //!    'error' is an error code set by the attach operation or OK if successful.
  //! 
  //!RETURN VALUES
  //!    N/A
  //!    
  //!ERRORS
  //!    The call will fail and set the 'error' code if:
  //!    
  //!    [TERMINVAL]     'terminal' is a non-existent or invalid terminal.
  //!
  //!    [TERMBUSY]      'terminal' is already attached or already listening for
  //!                    connections.
  //!    
  //!    [HOSTINVAL]     'host' does not represent a valid host as specified above.
  //!    
  //!    [PORTINVAL]     'port' does not represent a valid port as specified above.
  //!    
  //!    [SOCKETERR]     The call results in a socket error.
  private service attach ( termid: in termid,
                           host: in string,
                           port: in integer );   
  //!NAME
  //!    listen -- set a terminal instance to listen for a TCP connection on a local
  //!    port.
  //!    
  //!SYNOPSIS
  //!    public service listen( terminal: in  termid,
  //!                           port:     in  integer,
  //!                           error:    out error );
  //!    
  //!DESCRIPTION
  //!
  //!    The 'listen' service is used to initiate a terminal instance to listen for a
  //!    TCP connection on a local port.
  //!
  //!    'terminal' is an identifier specifying the terminal instance which to
  //!    execute the listen operation against.
  //!
  //!    'port' is an integer ranging from 0-65535 representing the port on which to
  //!    listen.
  //!    
  //!    'error' is an error code set by the listen operation or OK if successful.
  //! 
  //!RETURN VALUES
  //!    N/A
  //!    
  //!ERRORS
  //!    The call will fail and set the 'error' code if:
  //!    
  //!    [TERMINVAL]     'terminal' is a non-existent or invalid terminal.
  //!
  //!    [TERMBUSY]      'terminal' is already attached or already listening for
  //!                    connections.
  //!    
  //!    [PORTINVAL]     'port' does not represent a valid port as specified above.
  //!    
  //!    [SOCKETERR]     The call results in a socket error.
  private service listen ( termid: in termid,
                           port: in integer );   
  
  
  terminator Printer is
  end terminator;
  
  
end domain;
