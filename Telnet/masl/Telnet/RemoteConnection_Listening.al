state Telnet::RemoteConnection.Listening () is
sock: Socket::socketfd;
remoteaddr: Socket::sockaddr;
readfds: set of integer;
emptyfds: set of integer;
retval: integer;
begin

  // if the socket does not exist, create it
  if ( this.socket_id < 0 ) then

    // create a server socket
    this.socket_id := Socket::socket( Socket::SOCK_STREAM, Socket::IPPROTO_TCP );
    if ( this.socket_id < 0 ) then
      raise Socket::SocketException;
    end if;
     
    // bind to the locally specified port
    if ( Socket::bind( this.socket_id, this.local_address ) < 0 ) then
      raise Socket::SocketException;
    end if;
    
    // start listening
    if ( Socket::listen( this.socket_id, 1 ) < 0 ) then
      raise Socket::SocketException;
    end if;
    
  end if;
  
  // select for incoming connections
  readfds := integer(this.socket_id);
  retval := Socket::select( readfds, emptyfds, emptyfds, Socket::durationtotimeval( @PT0S@ ) );
  if ( retval < 0 ) then
    raise Socket::SocketException;
  elsif( retval = 0 ) then
    if ( Connections.default().default_timeout > this.retries * Connections.default().tick ) then
      schedule this.ticker generate listen() to this delay Connections.default().tick;
      this.retries := this.retries + 1;
    else
      generate error( ( "Listen operation timed out.", SOCKETERR ) ) to this;
    end if;
  else
  
    // accept a connection
    sock := Socket::accept( this.socket_id, remoteaddr );
    if ( sock < 0 ) then
      raise Socket::SocketException;
    else
      this.socket_id := sock;
      this.remote_address := remoteaddr;
      this.connected := true;
      generate ready() to this;
    end if;

  end if;
  
exception when Socket::SocketException =>
  generate error( ( "Error " & Socket::geterror()'image & ": " & Socket::strerror(), SOCKETERR ) ) to this;

end state;
