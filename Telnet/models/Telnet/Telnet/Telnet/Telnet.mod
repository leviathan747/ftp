//!This is an implementation of the Telnet protocol as defined in RFC 854. It is a
//!simple implementation that only implements the NVT and does not support any
//!additional options.
domain Telnet is
  object Connections;
  object CharacterSequences;
  object RemoteConnection;
  object Printer;
  object NetworkVirtualTerminal;
  object Keyboard;
  public type termid is integer
  ;
  public type telnetcmd is enum (SE, NOP, DM, BRK, IP, AO, AYT, EC, EL, GA, SB, WILL, WONT, DO, DONT, IAC)
  ;
  public type errorcode is enum (OK, TERMINVAL, TERMBUSY, HOSTINVAL, PORTINVAL, SOCKETERR)
  ;
  public type error is structure
  message: string;
  code: errorcode;
end structure
  ;
//!NAME
//!    create_terminal -- create a new Telnet terminal instance.
//!    
//!SYNOPSIS
//!    public service create_terminal( termid: out termid );
//!    
//!DESCRIPTION
//!
//!    The 'create_terminal' service is used to create a new Telnet terminal
//!    instance with its own printer and keyboard.
//!
//!    'termid' is set to the identifier of the created terminal instance.
//! 
//!RETURN VALUES
//!    N/A
//!    
//!ERRORS
//!    N/A
    public service create_terminal (
        termid : out termid    );
//!NAME
//!    sendtext -- send ASCII text on a specified terminal instance.
//!    
//!SYNOPSIS
//!    public service sendtext( termid: in termid,
//!                             text:   in string );
//!    
//!DESCRIPTION
//!
//!    The 'sendtext' service is used to queue ASCII text to be sent on a specified
//!    terminal instance.
//!
//!    'termid' is an identifier specifying the terminal instance which to
//!    send the text from.
//!    
//!    'text' is an ASCII text string.
//!    
//!RETURN VALUES
//!    N/A
//!    
//!ERRORS
//!    The call will fail and send an 'error' message on the Printer terminator if:
//!    
//!    [TERMINVAL]     'termid' is a non-existent or invalid terminal. Also
//!                    returned if the terminal is not attached to a peer.
    public service sendtext (
        termid : in termid,        text : in string    );
//!NAME
//!    command -- send a Telnet command on a specified terminal instance.
//!    
//!SYNOPSIS
//!    public service command( termid: in termid,
//!                            cmd:    in telnetcmd );
//!    
//!DESCRIPTION
//!
//!    The 'command' service is used to queue Telnet commands to be sent on a
//!    specified terminal instance.
//!    
//!    'termid' is an identifier specifying the terminal instance which to
//!    send the command from.
//!    
//!    'cmd' is a command code defined in the enumerated type telnetcmd. See the
//!    datatype definition for descriptions of available commands.
//! 
//!RETURN VALUES
//!    N/A
//!    
//!ERRORS
//!    The call will fail and send an 'error' message on the Printer terminator if:
//!    
//!    [TERMINVAL]     'termid' is a non-existent or invalid terminal. Also
//!                    returned if the terminal is not attached to a peer.
    public service command (
        termid : in termid,        cmd : in telnetcmd    );
//!NAME
//!    attach -- attach a Telnet terminal instance to another Telnet terminal.
//!    
//!SYNOPSIS
//!    public service attach( termid: in termid,
//!                           host:   in string,
//!                           port:   in integer );
//!    
//!DESCRIPTION
//!
//!    The 'attach' service is used to attach a Telnet terminal instance to another
//!    Telnet terminal specified by 'host' and 'port'.
//!
//!    'termid' is an identifier specifying the terminal instance which to
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
//!RETURN VALUES
//!    N/A
//!    
//!ERRORS
//!    The call will fail and send an 'error' message on the Printer terminator if:
//!    
//!    [TERMINVAL]     'termid' is a non-existent or invalid terminal.
//!
//!    [TERMBUSY]      'termid' is already attached or already listening for
//!                    connections.
//!    
//!    [HOSTINVAL]     'host' does not represent a valid host as specified above.
//!    
//!    [PORTINVAL]     'port' does not represent a valid port as specified above.
//!    
//!    [SOCKETERR]     The call results in a socket error.
    public service attach (
        termid : in termid,        host : in string,        port : in integer    );
//!NAME
//!    listen -- set a terminal instance to listen for a TCP connection on a local
//!    port.
//!    
//!SYNOPSIS
//!    public service listen( termid: in termid,
//!                           port:   in integer );
//!    
//!DESCRIPTION
//!
//!    The 'listen' service is used to initiate a terminal instance to listen for a
//!    TCP connection on a local port.
//!
//!    'termid' is an identifier specifying the terminal instance which to execute
//!    the listen operation against.
//!
//!    'port' is an integer ranging from 0-65535 representing the port on which to
//!    listen.
//!    
//!RETURN VALUES
//!    N/A
//!    
//!ERRORS
//!    The call will fail and send an 'error' message on the Printer terminator if:
//!    
//!    [TERMINVAL]     'termid' is a non-existent or invalid terminal.
//!
//!    [TERMBUSY]      'termid' is already attached or already listening for
//!                    connections.
//!    
//!    [PORTINVAL]     'port' does not represent a valid port as specified above.
//!    
//!    [SOCKETERR]     The call results in a socket error.
    public service listen (
        termid : in termid,        port : in integer    );
    private service test1 (
    );
pragma scenario ( 1 ); pragma test_only ( true ); 
    private service test2 (
    );
pragma scenario ( 2 ); pragma test_only ( true ); 
    private service address_is_valid (
        address : in string    ) return boolean;
    private service port_is_valid (
        port : in integer    ) return boolean;
    private service sigurg_handler (
    );
pragma signal_handler ( SIGURG ); 
  terminator Print is
//!NAME
//!    print -- post data from a specified Telnet terminal instance.
//!    
//!SYNOPSIS
//!    public service print( termid: in termid,
//!                          text:   in string );
//!    
//!DESCRIPTION
//!
//!    The 'print' service is used to notify listeners of data received at a
//!    specified Telnet terminal instance.
//!    
//!    'termid' is an identifier specifying the terminal instance which the data
//!    was received at.
//!    
//!    'text' is an ASCII string representing the data that was received.
//! 
//!RETURN VALUES
//!    N/A
//!    
//!ERRORS
//!    N/A
    public service print (
        termid : in termid,        text : in string    );
//!NAME
//!    command -- post a Telnet command from a specified terminal instance.
//!    
//!SYNOPSIS
//!    public service command( termid: in termid,
//!                            cmd:    in telnetcmd );
//!    
//!DESCRIPTION
//!
//!    The 'command' service is used to notify listeners of commands received at a
//!    specified Telnet terminal instance.
//!    
//!    'termid' is an identifier specifying the terminal instance which the command
//!    was received at.
//!    
//!    'cmd' is a command code defined in the enumerated type telnetcmd. See the
//!    datatype definition for descriptions of available commands.
//! 
//!RETURN VALUES
//!    N/A
//!    
//!ERRORS
//!    N/A
    public service command (
        termid : in termid,        cmd : in telnetcmd    );
//!NAME
//!    error -- post a Telnet error.
//!    
//!SYNOPSIS
//!    public service error( error:  in error );
//!    
//!DESCRIPTION
//!
//!    The 'error' service is used to notify listeners of error that have occurred.
//!    
//!    'error' is an error code defined in the enumerated type error. See the
//!    datatype definition for descriptions of errors.
//! 
//!RETURN VALUES
//!    N/A
//!    
//!ERRORS
//!    N/A
    public service error (
        error : in error    );
  end terminator;
  relationship R1 is NetworkVirtualTerminal unconditionally outputs_data_on one Printer,
    Printer unconditionally displays_output_for one NetworkVirtualTerminal;
  relationship R2 is NetworkVirtualTerminal unconditionally receives_input_from one Keyboard,
    Keyboard unconditionally passes_input_to one NetworkVirtualTerminal;
  relationship R3 is NetworkVirtualTerminal conditionally communicates_through one RemoteConnection,
    RemoteConnection unconditionally provides_communication_channel_for one NetworkVirtualTerminal;
  object Connections is
    default_timeout :   duration := @PT30S@;
    tick :   duration := @PT0.001S@;
    id : preferred  integer;
    buffer_size :   integer := 256;
    public  service default (
    ) return instance of Connections;
  end object;
  object CharacterSequences is
    id : preferred  integer;
    CRLF :   sequence of byte := 13 & 10;
    SE :   byte := 240;
    NOP :   byte := 241;
    DM :   byte := 242;
    BRK :   byte := 243;
    IP :   byte := 244;
    AO :   byte := 245;
    AYT :   byte := 246;
    EC :   byte := 247;
    EL :   byte := 248;
    GA :   byte := 249;
    SB :   byte := 250;
    WILL :   byte := 251;
    WONT :   byte := 252;
    DO :   byte := 253;
    DONT :   byte := 254;
    IAC :   byte := 255;
    public  service default (
    ) return instance of CharacterSequences;
  end object;
  object RemoteConnection is
    nvt_id : preferred  referential ( R3.provides_communication_channel_for.NetworkVirtualTerminal.id ) termid;
    socket_id :   Socket::socketfd := -1;
    local_address :   Socket::sockaddr;
    remote_address :   Socket::sockaddr;
    ticker :   timer;
    connected :   boolean := false;
    retries :   integer := 1;
     state Idle();
     state Listening();
     state ReportingError(        error : in error);
     state ReceivingData();
     state Connecting();
     state SendingData();
    terminal state ShuttingDown();
     event listen();
     event error(        error : in error);
     event ready();
     event connect();
     event read();
     event write();
     event close();
     transition is
      Non_Existent (
        listen => Cannot_Happen,
        error => Cannot_Happen,
        ready => Cannot_Happen,
        connect => Cannot_Happen,
        read => Cannot_Happen,
        write => Cannot_Happen,
        close => Cannot_Happen      ); 
      Idle (
        listen => Listening,
        error => Cannot_Happen,
        ready => Cannot_Happen,
        connect => Connecting,
        read => Cannot_Happen,
        write => Cannot_Happen,
        close => Cannot_Happen      ); 
      Listening (
        listen => Listening,
        error => ReportingError,
        ready => ReceivingData,
        connect => Cannot_Happen,
        read => Cannot_Happen,
        write => Cannot_Happen,
        close => Cannot_Happen      ); 
      ReportingError (
        listen => Cannot_Happen,
        error => Cannot_Happen,
        ready => Cannot_Happen,
        connect => Cannot_Happen,
        read => Cannot_Happen,
        write => Cannot_Happen,
        close => ShuttingDown      ); 
      ReceivingData (
        listen => Cannot_Happen,
        error => ReportingError,
        ready => ReceivingData,
        connect => Cannot_Happen,
        read => Cannot_Happen,
        write => SendingData,
        close => ShuttingDown      ); 
      Connecting (
        listen => Cannot_Happen,
        error => ReportingError,
        ready => ReceivingData,
        connect => Cannot_Happen,
        read => Cannot_Happen,
        write => Cannot_Happen,
        close => Cannot_Happen      ); 
      SendingData (
        listen => Cannot_Happen,
        error => ReportingError,
        ready => SendingData,
        connect => Cannot_Happen,
        read => ReceivingData,
        write => Cannot_Happen,
        close => Cannot_Happen      ); 
      ShuttingDown (
        listen => Cannot_Happen,
        error => Cannot_Happen,
        ready => Cannot_Happen,
        connect => Cannot_Happen,
        read => Cannot_Happen,
        write => Cannot_Happen,
        close => Cannot_Happen      ); 
    end transition;
  end object;
  object Printer is
    nvt_id : preferred  referential ( R1.displays_output_for.NetworkVirtualTerminal.id ) termid;
    buffer :   sequence of byte;
     state Idle();
     event data();
     transition is
      Non_Existent (
        data => Cannot_Happen      ); 
      Idle (
        data => Ignore      ); 
    end transition;
  end object;
  object NetworkVirtualTerminal is
    id : preferred  termid;
     state Idle();
     state Connected();
     state Synching();
     event connected();
     event synch();
     event data();
     transition is
      Non_Existent (
        connected => Cannot_Happen,
        synch => Cannot_Happen,
        data => Cannot_Happen      ); 
      Idle (
        connected => Connected,
        synch => Cannot_Happen,
        data => Cannot_Happen      ); 
      Connected (
        connected => Cannot_Happen,
        synch => Synching,
        data => Cannot_Happen      ); 
      Synching (
        connected => Cannot_Happen,
        synch => Cannot_Happen,
        data => Cannot_Happen      ); 
    end transition;
  end object;
  object Keyboard is
    nvt_id : preferred  referential ( R2.passes_input_to.NetworkVirtualTerminal.id ) termid;
    buffer :   sequence of byte;
  end object;
end domain;
