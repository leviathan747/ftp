state Telnet::RemoteConnection.ReceivingData () is
buffer: Socket::data;
begin

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

exception when Socket::SocketException =>
  generate error( ( "Error " & Socket::geterror()'image & ": " & Socket::strerror(), SOCKETERR ) ) to this;

end state;
