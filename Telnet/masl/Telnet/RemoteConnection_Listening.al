state Telnet::RemoteConnection.Listening () is
sock: Socket::socketfd;
remoteaddr: Socket::sockaddr;
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
  
  // accept a connection
  sock := Socket::accept( this.socket_id, remoteaddr );
  if ( sock < 0 ) then
    raise Socket::SocketException;
  else
    this.socket_id := sock;
    this.remote_address := remoteaddr;
    generate done() to this;
  end if;
  
exception when Socket::SocketException =>
  generate error( ( "Error " & Socket::geterror()'image & ": " & Socket::strerror(), SOCKETERR ) ) to this;

end state;
