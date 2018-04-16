state Telnet::RemoteConnection.ReceivingData () is
buffer: Socket::data;
readfds: set of integer;
emptyfds: set of integer;
retval: integer;
begin

  // select for input data
  readfds := integer(this.socket_id);
  retval := Socket::select( readfds, emptyfds, emptyfds, Socket::durationtotimeval( @PT0S@ ) );
  if ( retval < 0 ) then
    raise Socket::SocketException;
  elsif( retval = 0 ) then
    schedule this.ticker generate ready() to this delay Connections.default().tick;
  else

    // receive data
    if ( Socket::recv( this.socket_id, buffer, 1024, 0 ) < 0 ) then
      raise Socket::SocketException;
    end if;
  
    // no data means the peer has closed the connection
    if ( buffer'length > 0 ) then

      // log data
      Logger::information( "Telnet::RemoteConnection: Received data: " & Socket::datatostring( buffer ) );
  
      // repeat
      generate ready() to this;
  
    else
      generate close() to this;
    end if;

  end if;

exception when Socket::SocketException =>
  generate error( ( "Error " & Socket::geterror()'image & ": " & Socket::strerror(), SOCKETERR ) ) to this;

end state;
