state Telnet::RemoteConnection.SendingData () is
buffer: anonymous sequence of byte;
writefds: set of integer;
emptyfds: set of integer;
retval: integer;
keyboard: instance of Keyboard;
emptybuffer: sequence of byte;
begin

  // select to assure the socket is writable
  writefds := integer(this.socket_id);
  retval := Socket::select( emptyfds, writefds, emptyfds, Socket::durationtotimeval( @PT0S@ ) );
  if ( retval < 0 ) then
    raise Socket::SocketException;
  elsif( retval = 0 ) then
    schedule this.ticker generate ready() to this delay Connections.default().tick;
  else
    
    // get data to send
    keyboard := this->R3.provides_communication_channel_for.NetworkVirtualTerminal->R2.receives_input_from.Keyboard;
    if ( keyboard.buffer'length < Connections.default().buffer_size ) then
      buffer := keyboard.buffer;
    else
      buffer := keyboard.buffer[1..Connections.default().buffer_size];
    end if;

    // send data
    retval := Socket::send( this.socket_id, buffer, buffer'length, 0 );
    if ( retval < 0 ) then
      raise Socket::SocketException;
    else

      Logger::information( "Telnet::RemoteConnection: Sent " & retval'image & " bytes of data." );

      // update keyboard buffer
      if ( retval < keyboard.buffer'length ) then
        keyboard.buffer := keyboard.buffer[retval+1..keyboard.buffer'last];
        generate ready() to this; // keyboard still has contents
      else
        keyboard.buffer := emptybuffer;
        generate read() to this; // keyboard empty, go back to reading
      end if;

    end if;

  end if;

exception when Socket::SocketException =>
  generate error( ( "Error " & Socket::geterror()'image & ": " & Socket::strerror(), SOCKETERR ) ) to this;

end state;
