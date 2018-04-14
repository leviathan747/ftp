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
    schedule this.timer generate ready() to this delay @PT1S@; // TODO get delay from a constant
  else

    // receive data
    if ( Socket::recv( this.socket_id, buffer, 1024, 0 ) < 0 ) then
      raise Socket::SocketException;
    end if;
  
    // no data means the peer has closed the connection
    if ( buffer'length > 0 ) then

      // print data
      console << "Received data: " << Socket::datatostring( buffer ) << endl;
  
      // repeat
      generate ready() to this;
  
    else
      generate close() to this;
    end if;

  end if;

exception when Socket::SocketException =>
  generate error( ( "Error " & Socket::geterror()'image & ": " & Socket::strerror(), SOCKETERR ) ) to this;

end state;
