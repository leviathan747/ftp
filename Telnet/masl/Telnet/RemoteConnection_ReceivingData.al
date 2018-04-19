state Telnet::RemoteConnection.ReceivingData () is
buffer: sequence of byte;
readfds: set of integer;
emptyfds: set of integer;
retval: integer;
printer: instance of Printer;
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
    if ( Socket::recv( this.socket_id, buffer, Connections.default().buffer_size, 0 ) < 0 ) then
      raise Socket::SocketException;
    end if;
  
    // no data means the peer has closed the connection
    if ( buffer'length > 0 ) then

      // store data
      //Logger::information( "Telnet::RemoteConnection: Received data: " & Socket::datatostring( buffer ) );
      printer := this->R3.provides_communication_channel_for.NetworkVirtualTerminal->R1.outputs_data_on.Printer;
      printer.buffer := printer.buffer & buffer;
      generate Printer.data() to printer;
  
      // repeat
      generate ready() to this;
  
    else
      generate close() to this;
    end if;

  end if;

exception when Socket::SocketException =>
  generate error( ( "Error " & Socket::geterror()'image & ": " & Socket::strerror(), SOCKETERR ) ) to this;

end state;
