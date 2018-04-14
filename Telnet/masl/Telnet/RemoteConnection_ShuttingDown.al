terminal state Telnet::RemoteConnection.ShuttingDown () is
begin

  // gracefully close the socket
  if ( Socket::close( integer(this.socket_id) ) < 0 ) then end if;
  
  // unlink from terminal
  unlink this R3 this->R3.provides_communication_channel_for.NetworkVirtualTerminal;
  
  // delete self
  delete this;
  
end state;
