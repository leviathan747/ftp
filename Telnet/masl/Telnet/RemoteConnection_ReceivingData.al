state Telnet::RemoteConnection.ReceivingData () is
buffer: Socket::data;
begin

  // receive data
  if ( Socket::recv( this.socket_id, buffer, 1024, 0 ) < 0 ) then
    raise Socket::SocketException;
  end if;
  
  // print data
  console << "Received data: " << Socket::datatostring( buffer ) << endl;
  
  // repeat
  generate done() to this;

exception when Socket::SocketException =>
  generate error( ( "Error " & Socket::geterror()'image & ": " & Socket::strerror(), SOCKETERR ) ) to this;

end state;
